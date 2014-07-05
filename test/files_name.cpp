//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//-----------------------------------------------------------------------el-

#include "compta/compta_options.hpp"

int main(int argc, char ** argv)
{
 Compta::ComptaOptions options(argc,argv);

 if(!options.valid())
 {
    return 1;
 }

 if(options.forecast_file() != "forecast" && 
    options.accounts_file().empty() && 
    options.data_file().empty())return 1;

 return 0;

}
