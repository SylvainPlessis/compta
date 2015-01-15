//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// Compta - A simple terminal based comptability software
//
// Copyright (C) 2013, 2014 Sylvain Plessis
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

#include <string>

namespace Compta{

/*! 
   Five things here:
     - general non compta options (help, version)
     - Input/output files
     - report on screen (print options)
     - report on file (LaTeX only)
     - the state of every account
*/

/* helpers, boolean values */
  namespace GENERAL{
    enum Options{//
               VERSION = 0,
               HELP
              };
  }

/* read files */
  namespace READ{
    enum Options{
               FORECAST = 0,
               ACCOUNTS,
               DATA
              };
  }

/* print options, boolean values */
  namespace PRINT{
    enum Options{
               NOPRINT = 0,
               ALL,
               FORECAST,
               BANK,
               CASH,
               FROM,
               TO
              };
  }

/* write file */
  namespace WRITE{
    enum Options{
               GENERATE_TEX = 0,
               COMPILE_TEX,
               LATEX,
               FROM,
               TO
              };
  }

}

#endif
