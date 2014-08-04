//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//-----------------------------------------------------------------------el-

#ifndef COMPTA_STATIC_ERROR_VARIABLES
#define COMPTA_STATIC_ERROR_VARIABLES

//Compta

//C++
#include <string>

namespace Compta
{

 namespace FilesParsing{
   static unsigned int current_line(0);
   static std::string  raw_line;
   static std::string  error_message;
 }

}

#endif
