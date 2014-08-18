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
               << "-h, --help:                 this message\n"
               << "-v, --version:              program version\n"
               << "--generate-latex (yes/no):  generate a LaTeX file (default = yes)\n"
               << "--compile-latex  (yes/no):  compile the LaTeX file (default = yes)\n"
               << "--forecast:                 forecast file\n"
               << "--data:                     data file (default = same as forecast)\n"
               << "--accounts:                 accounts file (default = same as forecast)\n"
               << "--latex:                    LaTeX file (default = same as forecast)\n"
               << "--print-all:                print all on screen (default)\n"
               << "--print-forecast:           print forecast info on screen\n"
               << "--print-bank:               print bank info on screen\n"
               << "--print-cash:               print cash info on screen\n"
               << std::endl;
               
  }


}
