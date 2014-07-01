//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// Compta - A simple terminal based comptability software
//
// Copyright (C) 2013 Sylvain Plessis
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor,
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-

#ifndef OPTIONS_ENUM_H
#define OPTIONS_ENUM_H

//Compta
#include "compta/compta_version.hpp"

//C++
#include <iostream>
#include <cmath>

namespace Compta{

  enum Options{//
               VERSION = 0,
               HELP,
               FORECAST_FILE,
               ACCOUNTS_FILE,
               DATA_FILE,
               LATEX_FILE,
               GENERATE_TEX,
               COMPILE_TEX
              };

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
               << "-h, --help:               this message\n"
               << "-v, --version:            program version\n"
               << "--generate_tex (yes/no):  generate a LaTeX file (default = yes)\n"
               << "--compile_tex  (yes/no):  compile the LaTeX file (default = yes)\n"
               << "--forecast:               forecast file\n"
               << "--data:                   data file (default = same as forecast)\n"
               << "--accounts:               accounts file (default = same as forecast)\n"
               << "--latex:                  LaTeX file (default = same as forecast)\n"
               << std::endl;
               
  }
}

#endif
