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

#ifndef COMPTA_STRING_UTILS_H
#define COMPTA_STRING_UTILS_H

// Compta

// C++
#include <string>
#include <vector>

namespace Compta
{
  bool check_BOM(const char* p);

  //!supress blanks around string
  void shave_string(std::string &str);

  //!supress blanks around string
  void shave_string(std::vector<std::string> &customer);

  /*!
    Taken from FIN-S for XML parsing.
   */
  int SplitString(const std::string& input, 
		  const std::string& delimiter, 
		  std::vector<std::string>& results, 
		  bool includeEmpties = true);

  /*! taken from Antioch string_utils
      adapted getline, never believe ascii file for the
      formatting of end-of-line.
      end-of-line triggered by \n or \r
        - Windows     \n\r
        - Unix/Linux  \n
        - Mac         \r
   */
  int ascii_getline(std::istream & buf, std::string & line);

} // end namespace Compta

#endif // COMPTA_STRING_UTILS_H
