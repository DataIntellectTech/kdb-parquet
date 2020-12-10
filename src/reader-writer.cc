// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements. See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership. The ASF liceses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the License for the
// specific language governing permissions and limitations
// under the License.

#include "library.h"
#include <typeinfo>
#include <iostream>
#include <arrow/api.h>
#include <arrow/io/api.h>
#include "arrow/io/file.h"
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>
#include <parquet/exception.h>
#include "parquet/stream_reader.h"

#include "Kx/k.h"
class NewStreamReader:public parquet::StreamReader
{
public:
    NewStreamReader(std::unique_ptr<parquet::ParquetFileReader> reader)
            : parquet::StreamReader{std::move(reader)} {}
    NewStreamReader& customint32(int32_t& v) {
        //CheckColumn(Type::INT64, ConvertedType::TIMESTAMP_MILLIS);
        int32_t tmp;
        Read<parquet::Int32Reader>(&tmp);
        v = tmp;
        return *this;
    }

};
arrow::Status s;
std::exception myexception;
#include "tokdbfromarrow.hpp"
#include "fromkdbtoarrow.hpp"
#include "tokdbfromparquet.hpp"

int arrowtabletokdb( K &ns, std::shared_ptr<arrow::Table> &table);
arrow::Status getschema(std::string file, std::shared_ptr<arrow::Schema> &table);
// #0 Build dummy data to pass around
// To have some input data, we first create an Arrow Table that holds
// some data.
std::shared_ptr<arrow::Table> generate_table() {
  arrow::Int64Builder i64builder;
  PARQUET_THROW_NOT_OK(i64builder.AppendValues({1, 2, 3, 4, 5}));
  std::shared_ptr<arrow::Array> i64array;
  PARQUET_THROW_NOT_OK(i64builder.Finish(&i64array));

  arrow::StringBuilder strbuilder;
  PARQUET_THROW_NOT_OK(strbuilder.Append("some"));
  PARQUET_THROW_NOT_OK(strbuilder.Append("string"));
  PARQUET_THROW_NOT_OK(strbuilder.Append("content"));
  PARQUET_THROW_NOT_OK(strbuilder.Append("in"));
  PARQUET_THROW_NOT_OK(strbuilder.Append("rows"));
  std::shared_ptr<arrow::Array> strarray;
  PARQUET_THROW_NOT_OK(strbuilder.Finish(&strarray));

  std::shared_ptr<arrow::Schema> schema = arrow::schema(
      {arrow::field("int", arrow::int64()), arrow::field("str", arrow::utf8())});

  return arrow::Table::Make(schema, {i64array, strarray});
}

// #1 Write out the data as a Parquet file
void write_parquet_file(const arrow::Table& table) {
  std::shared_ptr<arrow::io::FileOutputStream> outfile;
  PARQUET_ASSIGN_OR_THROW(
      outfile,
      arrow::io::FileOutputStream::Open("parquet-arrow-example.parquet"));
  // The last argument to the function call is the size of the RowGroup in
  // the parquet file. Normally you would choose this to be rather large but
  // for the example, we use a small value to have multiple RowGroups.
  PARQUET_THROW_NOT_OK(
      parquet::arrow::WriteTable(table, arrow::default_memory_pool(), outfile, 3));
}

// #2: Fully read in the file
void read_whole_file() {
  std::cout << "Reading parquet-arrow-example.parquet at once" << std::endl;
  std::shared_ptr<arrow::io::ReadableFile> infile;
  PARQUET_ASSIGN_OR_THROW(
      infile,
      arrow::io::ReadableFile::Open("parquet-arrow-example.parquet",
                                    arrow::default_memory_pool()));

  std::unique_ptr<parquet::arrow::FileReader> reader;
  PARQUET_THROW_NOT_OK(
      parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader));
  std::shared_ptr<arrow::Table> table;
  PARQUET_THROW_NOT_OK(reader->ReadTable(&table));
  std::cout << "Loaded " << table->num_rows() << " rows in " << table->num_columns()
            << " columns." << std::endl;
}

// #3: Read only a single RowGroup of the parquet file
void read_single_rowgroup() {
  std::cout << "Reading first RowGroup of parquet-arrow-example.parquet" << std::endl;
  std::shared_ptr<arrow::io::ReadableFile> infile;
  PARQUET_ASSIGN_OR_THROW(
      infile,
      arrow::io::ReadableFile::Open("parquet-arrow-example.parquet",
                                    arrow::default_memory_pool()));

  std::unique_ptr<parquet::arrow::FileReader> reader;
  PARQUET_THROW_NOT_OK(
      parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader));
  std::shared_ptr<arrow::Table> table;
  PARQUET_THROW_NOT_OK(reader->RowGroup(0)->ReadTable(&table));
  std::cout << "Loaded " << table->num_rows() << " rows in " << table->num_columns()
            << " columns." << std::endl;
}

// #4: Read only a single column of the whole parquet file
void read_single_column() {
  std::cout << "Reading first column of parquet-arrow-example.parquet" << std::endl;
  std::shared_ptr<arrow::io::ReadableFile> infile;
  PARQUET_ASSIGN_OR_THROW(
      infile,
      arrow::io::ReadableFile::Open("parquet-arrow-example.parquet",
                                    arrow::default_memory_pool()));

  std::unique_ptr<parquet::arrow::FileReader> reader;
  PARQUET_THROW_NOT_OK(
      parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader));
  std::shared_ptr<arrow::ChunkedArray> array;
  PARQUET_THROW_NOT_OK(reader->ReadColumn(0, &array));
  PARQUET_THROW_NOT_OK(arrow::PrettyPrint(*array, 4, &std::cout));
  std::cout << std::endl;
}

// #5: Read only a single column of a RowGroup (this is known as ColumnChunk)
//     from the Parquet file.
void read_single_column_chunk() {
  std::cout << "Reading first ColumnChunk of the first RowGroup of "
               "parquet-arrow-example.parquet"
            << std::endl;
  std::shared_ptr<arrow::io::ReadableFile> infile;
  PARQUET_ASSIGN_OR_THROW(
      infile,
      arrow::io::ReadableFile::Open("parquet-arrow-example.parquet",
                                    arrow::default_memory_pool()));

  std::unique_ptr<parquet::arrow::FileReader> reader;
  PARQUET_THROW_NOT_OK(
      parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader));
  std::shared_ptr<arrow::ChunkedArray> array;
  PARQUET_THROW_NOT_OK(reader->RowGroup(0)->Column(0)->Read(&array));
  PARQUET_THROW_NOT_OK(arrow::PrettyPrint(*array, 4, &std::cout));
  std::cout << std::endl;
}

void print_schema(std::shared_ptr<arrow::Table>  table)
{

    const std::vector<std::string> &l = table->schema()->field_names();
    int n=table->schema()->field_names().size();

    std::cout <<     table->schema()->HasMetadata() << std::endl;

    for (int i = 0; i <n ; ++i) {
        std::cout <<    table->schema()->field_names().at(i) << std::endl;
        std::cout <<    table->schema()->fields().at(i)->type()->ToString() << std::endl;
        std::cout <<    table->column(i)->length()<< std::endl;
    }


}


arrow::Status readfile(std::string file, std::vector<int> indicies,std::shared_ptr<arrow::Table> &table)
{
    arrow::Status s;
    std::exception e;
    std::shared_ptr<arrow::io::ReadableFile> infile;
    auto p = (arrow::io::ReadableFile::Open(file, arrow::default_memory_pool()));
    if(!p.ok()){throw e;}
    infile = std::move(p).ValueOrDie();
    std::unique_ptr<parquet::arrow::FileReader> reader;
    parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader);
    if(NULL==reader.get()){throw e;}
    s=reader->ReadTable(indicies,&table);
    if(!s.ok()){throw e;}
    return s;
}


int writeparquetfile(std::string file,const arrow::Table& table) {
    std::shared_ptr<arrow::io::FileOutputStream> outfile;
    //auto p = (arrow::io::ReadableFile::Open(file, arrow::default_memory_pool()));
            auto p=arrow::io::FileOutputStream::Open(file, arrow::default_memory_pool());
            if(!p.ok()){throw myexception;}
            outfile = std::move(p).ValueOrDie();
            arrow::Status s=parquet::arrow::WriteTable(table, arrow::default_memory_pool(), outfile, savechunksize);
            if(!s.ok()){
                throw myexception;}

           return 0;

}

int ksettabletofile(K tab,std::string file)
{
    std::shared_ptr<arrow::Table> table;
    kdbtoarrow(tab,table);
    writeparquetfile(file,*table);
    return 0;
}
//Get a simple table and all fields.
int kgetfile(K &ns,std::string file) {
    std::shared_ptr<arrow::Table> table;
    std::shared_ptr<arrow::Schema> schema;
    s=getschema(file,schema);
    std::vector<int> ivec(schema->num_fields());
    std::iota (std::begin(ivec), std::end(ivec), 0);

    s=readfile(file,ivec,table);
    arrowtabletokdb(ns,table);

    return 0;
}
int kgetfilebycols(K &ns,std::vector<std::string> cols,std::string file) {
    std::shared_ptr<arrow::Table> table;
    std::shared_ptr<arrow::Schema> schema;
    s=getschema(file,schema);
    std::vector<int> ivec(0);
    //std::iota (std::begin(ivec), std::end(ivec), 0);
    for(std::vector<std::string>::iterator it = cols.begin(); it != cols.end(); ++it) {
        ivec.push_back( schema->GetFieldIndex(*it) );
    }
   s=readfile(file,ivec,table);
    arrowtabletokdb(ns,table);

    return 0;
}

arrow::Status getschema(std::string file, std::shared_ptr<arrow::Schema> &schema)
{   std::shared_ptr<arrow::io::ReadableFile> infile;
    try {
        auto p = (arrow::io::ReadableFile::Open(file, arrow::default_memory_pool()));
        if(!p.ok()){throw myexception;}
        infile = std::move(p).ValueOrDie();
        std::unique_ptr<parquet::arrow::FileReader> reader;
        parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader);
        if(NULL==reader.get()){throw myexception;}
        s = reader->GetSchema(&schema);

        if(!s.ok()){throw myexception;}
    } catch (...) {
        std::cout << "Could not get table schema " << std::endl;
        throw(  myexception);
    }
    return s;
}

int kgetschema(K &ns, std::string file)
{
    std::shared_ptr<arrow::Schema> schema;
    try {
     s=getschema(file,schema);

    } catch (...) {
        std::cout << "Could not get table schema " << std::endl;
        throw(  myexception);
    }

    int n=schema->field_names().size();
    K names=ktn(0,n);
    K types=ktn(0,n);
    for (int i = 0; i <n; ++i) {
        //std::cout <<   l[i] << std::endl;
        //std::cout <<   table->ColumnNames()[i] << std::endl;
        std::string name=(char*)schema->field_names().at(i).data();
        std::string tps = schema->fields().at(i)->type()->ToString();
        kK(names)[i]=kpn((char*)name.c_str(),name.length());
        kK(types)[i]=kpn((char*)tps.c_str(),tps.length());  ;

    }
   K cols=ktn(KS,2);kS(cols)[0]=ss("name");kS(cols)[1]=ss("type");
    ns=xT(xD(cols,knk(2,names,types)));

    return 0;

}
int kgetinfo(K &ns, std::string file)
{
    std::shared_ptr<arrow::Schema> schema;
    try {
        s=getschema(file,schema);

    } catch (...) {
        std::cout << "Could not get table schema " << std::endl;
        throw(  myexception);
    }

    int n=schema->field_names().size();
    K names=ktn(0,n);
    K types=ktn(0,n);
    for (int i = 0; i <n; ++i) {
        //std::cout <<   l[i] << std::endl;
        //std::cout <<   table->ColumnNames()[i] << std::endl;
        std::string name=(char*)schema->field_names().at(i).data();
        std::string tps = schema->fields().at(i)->type()->ToString();
        kK(names)[i]=kpn((char*)name.c_str(),name.length());
        kK(types)[i]=kpn((char*)tps.c_str(),tps.length());  ;

    }
    K cols=ktn(KS,2);kS(cols)[0]=ss("name");kS(cols)[1]=ss("type");
    ns=xT(xD(cols,knk(2,names,types)));

    return 0;

}

int arrowtabletokdb( K &ns, std::shared_ptr<arrow::Table> &table)
{
    int n=table->num_columns();                  //num_columns
    int r=table->num_rows();                   //num_rows
    K names=ktn(KS,n);
    K values=ktn(0,n);
    for(int i=0;i<n;i++)
    {   K mydata;

        kS(names)[i]=ss((char*)table->ColumnNames().at(i).c_str());
        //Get column name
        tokdbfromarrow(mydata,table.get()->column(i));
        kK(values)[i]=mydata;
        //get column

    }
    ns=xT(xD(names,values));
    return 0;
}



int kstreamread(std::string file, std:: string callback)
{
    std::shared_ptr<arrow::io::ReadableFile> infile;
        auto p = (arrow::io::ReadableFile::Open(file, arrow::default_memory_pool()));
        if (!p.ok()) { throw myexception; }
        infile = std::move(p).ValueOrDie();
    NewStreamReader os{parquet::ParquetFileReader::Open(infile)};
    std::shared_ptr<arrow::Schema> thisschema;
    s=getschema(file,thisschema);
    thisschema.get()->fields().at(0)->type()->ToString();
    int nc=os.num_columns();
    int nr=os.num_rows();
    K field;
    for (int i = 0; !os.eof(); ++i) {
    K  row=ktn(0,nc);
	    for(int j=0;j<nc;j++)
           { 
	   try {
           tokdbfromparquet(os,thisschema.get()->fields().at(j)->type()->ToString(),field);
           kK(row)[j]=field;
	   } catch(...)
	    {
	      	    field=ktn(0,0);
		   os.SkipColumns(1);
		   kK(row)[j]=field;
	   }
       }
	k(0,ss((char*)callback.c_str()),row,(K)0);
        os >> parquet::EndRow;
    }
  return 0;
}

