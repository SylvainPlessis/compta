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
               << "-h, --help                                 this message\n"
               << "-v, --version                              program version\n"
               << "--generate-latex      (= yes/no)           generate a LaTeX file (default = yes)\n"
               << "-g                                         shorthand for --generate-latex=yex\n"
               << "--compile-latex       (= yes/no)           compile the LaTeX file (default = yes)\n"
               << "-c                                         shorthand for --compile-latex=yex\n"
               << "--write               (= filename)         LaTeX file (default = same as forecast)\n"
               << "--write-from          (= dd/mm/yyyy)       start date for latex report (dd/mm/yyyy, default 01/01/1900)\n"
               << "--write-to            (= dd/mm/yyyy)       end date for latex report (dd/mm/yyyy, default 31/12/3000)\n"
               << "--forecast            (= filename)         forecast file\n"
               << "--data                (= filename)         data file (default = same as forecast)\n"
               << "--accounts            (= filename)         accounts file (default = same as forecast)\n"
               << "--print               (= yes/no)           print all on screen (default = no)\n"
               << "--print-forecast                           print forecast info on screen\n"
               << "--print-bank                               print bank info on screen\n"
               << "--print-cash                               print cash info on screen\n"
               << "--print-bank-history  (= bank1, bank2,...) list bank history on screen, from date given int --print-from to date given in --print-to\n"
               << "--print-cash-history  (= cash1, cash2,...) list cash history on screen, from date given int --print-from to date given in --print-to\n"
               << "--print-from          (= dd/mm/yyyy)       start date for screen report (DD/MM/YYYY, default 01/01/1900)\n"
               << "--print-to            (= dd/mm/yyyy)       end date for screen report (SS/MM/YYYY, default 31/12/3000)\n"
               << std::endl;
               
  }


}
