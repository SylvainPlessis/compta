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

namespace Compta{

  enum Options{//
/* helpers, boolean values */
               VERSION = 0,
               HELP,
/* files */
               FORECAST_FILE,
               ACCOUNTS_FILE,
               DATA_FILE,
               LATEX_FILE,
/* print options, boolean values*/
               PRINT_ALL,
               PRINT_FORECAST,
               PRINT_BANK,
               PRINT_CASH,
/* output file*/
               GENERATE_TEX,
               COMPILE_TEX
              };

// only the printing
  enum PrintOptions{
                ALL = 0,
                FORECAST,
                BANK,
                CASH
              };

}

#endif
