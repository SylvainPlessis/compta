//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//-----------------------------------------------------------------------el-

// Compta
#include "compta/compta_help.hpp"
#include "compta/compta_version.hpp"

//C++
#include <iostream>
#include <cmath>

namespace Compta{

  void compta_help_stdout()
  {
     int version = get_compta_version();
     int major = std::floor(version/10000);
     int minor = std::floor((version - major * 10000)/100);
     int micro = version - major * 10000 - minor * 100;

     std::cout << "Compta " << major << "." << minor << "." << micro << std::endl
               << std::endl
               << "Program to perform comptability operations\n"
               << "compta file\n"
               << "\n"
               << "Options are:\n\n"
               << "-h, --help                 this message\n"
               << "-v, --version              program version\n"
               << "--generate-latex (yes/no)  generate a LaTeX file (default = yes)\n"
               << "-g                         shorthand for --generate-latex=yex\n"
               << "--compile-latex  (yes/no)  compile the LaTeX file (default = yes)\n"
               << "-c                         shorthand for --compile-latex=yex\n"
               << "--write                    LaTeX file (default = same as forecast)\n"
               << "--write-from               start date for latex report (DD/MM/YYYY, default 01/01/1900)\n"
               << "--write-to                 end date for latex report (SS/MM/YYYY, default 31/12/3000)\n"
               << "--forecast                 forecast file\n"
               << "--data                     data file (default = same as forecast)\n"
               << "--accounts                 accounts file (default = same as forecast)\n"
               << "--print (yes/no)           print all on screen (default = no)\n"
               << "--print-forecast           print forecast info on screen\n"
               << "--print-bank               print bank info on screen\n"
               << "--print-cash               print cash info on screen\n"
               << "--print-from               start date for screen report (DD/MM/YYYY, default 01/01/1900)\n"
               << "--print-to                 end date for screen report (SS/MM/YYYY, default 31/12/3000)\n"
               << std::endl;
               
  }


}
