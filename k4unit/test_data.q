// Handy place to store data (e.g. tables) and helper functions that are too big/cumbersome to write in csv row.

// Corresponding 'all_types' table in kdb format (see 'Python/all_types.py').
.test.all_types:([]
	double:1.23 4.56 7.89;
	float:1.2 3.4 5.6e;
	str:("apple";"banana";"cherry");
	int32:-10 0 10i;
	uint16:1 2 3i;
	uint32:100 200 300;
	uint64:1000 2000 3000f;
	bool:101b;
	time32_ms:12:34:56.123 01:23:45 23:59:59;
	date32:2025.01.01 2025.06.15 2025.12.31;
	null_col:3#enlist();
	int64:1000000*-1 0 1;
	time64_micro:0D12:34:56.123456 0D01:23:45.654321 0D23:59:59.999999;
	time64_nano:0D12:34:56.123456789 0D01:23:45.987654321 0D23:59:59.999999999;
	timestamp_ms:2025.01.01D12:00:00.123 2025.02.15D18:30:00 2025.12.31D23:59:59.999;
	timestamp_ms_utc:2025.01.01D12:00:00.123 2025.02.15D18:30:00 2025.12.31D23:59:59.999;
	timestamp_us:2025.01.01D12:00:00.123456 2025.02.15D18:30:00.654321 2025.12.31D23:59:59.999999;
	timestamp_us_utc:2025.01.01D12:00:00.123456 2025.02.15D18:30:00.654321 2025.12.31D23:59:59.999999;
	timestamp_ns:2025.01.01D12:00:00.123456789 2025.02.15D18:30:00.987654321 2025.12.31D23:59:59.999999999;
	timestamp_ns_utc:2025.01.01D12:00:00.123456789 2025.02.15D18:30:00.987654321 2025.12.31D23:59:59.999999999);

// Corresponding 'all_q_types' in kdb format (see 'Python/all_q_types.p'). Used to test that writing to parquet
// correctly handles all q types.
// TODO: Implement the nyi types.
.test.all_q_types:([]
	bool:010b;
	/guid:"G"$"00000000-0000-0000-0000-00000000000",/:string til 3;
	/byte:0x0102ff;
	/short:-1 0 1h;
	int:-10 0 10i;
	long:-100 0 100;
	/real:1.2 -3.4 5.6e;
	float:1.23 -4.56 7.89;
	char:"abc";
	sym:`apple`banana`cherry;
	/str:("apple";"banana";"cherry");
	timestamp:2025.01.01D12:00:00.123456789 2025.02.15D18:30:00.987654321 2025.12.31D23:59:59.999999999;
	/month:2025.01 1990.06 2025.12m;
	date:2025.01.01 1990.06.15 2025.12.31;
	/datetime:2025.01.01D12:00:00.123 2025.02.15D18:30:00.987 2025.12.31T23:59:59.999;
	/timespan:0D12:34:56.123456789 0D01:23:45.987654321 0D23:59:59.999999999;
	/minute:00:10 00:00 12:34;
	/second:12:34:56 00:00:00 01:00:12;
	time:12:34:56.789 00:00:00.000 01:00:12.101);

// @desc `.pq.streamread` helper. Values are streamed cell by cell. This function accumulates them in a global variable,
// and constructs a table from the accumulated cells and the specified columns
// @param file	{sym}	File to stream.
// @param col	{sym[]}	Column names of table.
// @return		{table}	
.test.streamRead:{[file;col]
	.test.StreamRows:(); / Reset state (or init)
	.pq.streamread[file;`.test.streamReadCB]; / Stream
	flip col!flip .test.StreamRows / Tablify
 }

// @desc Stream reader callback (see `.test.streamRead`). Accumulates each new cell into the global `.test.StreamRows`.
// @param cell	{any}	Streamed cell.
.test.streamReadCB:{[cell]
	.test.StreamRows,:enlist cell;
 }

// @desc Convolution of `.test.all_q_types`, i.e. the (expected) result of writing it and reading it back. It's not
// quite the same table we started with.
// @return	{table}	Write/read convolution of `.test.all_q_types`.
.test.convAllQTypes:{[]
	update
		/"i"$short,
		enlist each char,
		string sym
		/"d"$month,
		/"p"$datetime,
		/"t"$minute,
		/"t"$second
		from .test.all_q_types
	}
