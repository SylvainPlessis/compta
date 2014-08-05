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

#ifndef COMPTA_STATIC_ERROR_VARIABLES
#define COMPTA_STATIC_ERROR_VARIABLES

//Compta

//C++
#include <string>

namespace Compta
{

 namespace FilesParsing{
   //! current line while reading input file
   unsigned int current_line();

   //! set line while reading input file
   void set_current_line(unsigned int nline);

   //! add to line while reading input file
   void add_current_line(unsigned int nline = 1);

   //!current line from read input file
   std::string  raw_line();

   //! set line while reading input file
   void set_raw_line(const std::string &line);

   //!error message giving line number and line
   std::string  error_message();
 }

}

#endif
