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

#ifndef COMPTA_PARSING_DEF_H
#define COMPTA_PARSING_DEF_H

//Compta
#include "compta/posting_enum.hpp"

//C++
#include <map>
#include <string>

namespace Compta{

 namespace ForecastParsing{
     const std::string forecast();

     const std::string delimiter();

     const std::string automatic();
  }

 namespace AccountsParsing{
     const std::string bank();

     const std::string cash();

     const std::string savings();

     const std::string delimiter();

     const std::string chooser();
 }

 namespace DataParsing{
     const char bank_str();

     const char cash_str();

     const char transfer_str();

     const std::string false_str();

     const std::string delimiter();

     std::map<char, PostingType::PostingType> posting_type_map();

     std::map<PostingType::PostingType,char> posting_type_inverse_map();
  }
}

#endif
