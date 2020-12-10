int tokdbfromparquet( NewStreamReader &os,std::string thistype, K &x) {
      int64_t int64;
      char ch;
      char char_array[400];
      int8_t int8;
      uint16_t uint16;
      int32_t int32;
      uint64_t uint64;
      uint32_t uint32;
      double dble;
      float flt;
      bool myboolean;
      std::string stringarray;
      std::chrono::milliseconds ts_ms;
      int i;
   if(thistype=="double") {
      os>>dble;
      x=kf((double)dble);
   }else if(thistype=="float")
   {  
    os>>flt;
    x=kf((float)flt);
   } else if(thistype=="int64")
   { 
     os>>int64;
     x=kj(int64);
   }else if(thistype=="string")
   {
      os>>stringarray;
      x=kpn((char*)stringarray.c_str(),stringarray.length());
   }
   else if(thistype=="int32")
   {
      os>>int32;
      x=ki(int32);
   }
   else if(thistype=="uint16")
   {
     os>>uint16;
     x=kj((long)uint16);
   }
   else if(thistype=="uint32")
   {
       os>>uint32;
       x=kj((long)uint16);
   }
   else if(thistype=="uint64")
   {
      os>>uint64;
      x=kf((float)uint16);
   }
   else if(thistype=="bool")
   {

       os>>myboolean;
       x=kb((int)myboolean);
   }
   else if(thistype=="time32[ms]")
   {
       int32_t tmp;
       os.customint32(tmp);
       x=kt(tmp);
   }
   else if(thistype=="time32[us]")
   {
       int32_t tmp;
       os.customint32(tmp);
       x=ktj(-KN,tmp);
   }
   else if(thistype=="time64[ns]")
   {
       int32_t tmp;
       x=(K)0;
       throw myexception;
   }
   else if(thistype=="timestamp[ms]")
   {  
       os>>int64;
       x=ktj(-KP,1000*int64);
   }
   else if(thistype=="timestamp[us]")
   {  
       os>>int64;
       x=ktj(-KP,int64);
   }
   else if(thistype=="date32[day]")
   {
      os.customint32(int32);
      x=kd(int32);
   }
   else if(thistype=="null")
   { 
      x=(K)(0);
      throw myexception;

   }
   else if(thistype=="decimal(2,1)")
   {

      x=(K)(0);
      throw myexception;      
   }else if(thistype=="binary")
   {

      x=(K)(0);
      throw myexception;
   }
   else
   {
       x=(K)(0);
       throw myexception;
   }
return 0;
}
