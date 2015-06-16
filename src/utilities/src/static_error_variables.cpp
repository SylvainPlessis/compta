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

// Compta
#include "compta/static_error_variables.hpp"

// C++
#include <sstream>

namespace Compta
{
 namespace FilesParsing{
   static unsigned int _current_line(0);
   static std::string  _raw_line;
   static std::string  _error_message;
   static std::string  _current_file;

   unsigned int current_line()
   {
     return _current_line;
   }

   void set_current_line(unsigned int nline)
   {
     _current_line = nline;
   }

   void add_current_line(unsigned int nline)
   {
     _current_line += nline;
   }

   std::string  raw_line()
   {
      return _raw_line;
   }

   void set_raw_line(const std::string &line)
   {
      _raw_line = line;
   }

   std::string raw_error_message()
   {
      std::stringstream oss;
      oss << "Line #" << current_line() << " of file " << current_file() << "\n"
          << raw_line() << std::endl;
      return oss.str();
   }

   std::string error_message()
   {
      return (_error_message.empty())?raw_error_message():_error_message;
   }

   void set_error_message(const std::string & err)
   {
      _error_message = err;
   }

   void clear_error_message()
   {
      _error_message.clear();
   }

   std::string current_file()
   {
     return _current_file;
   }

   void set_current_file(const std::string & file)
   {
     _current_file = file;
   }
 }
}

