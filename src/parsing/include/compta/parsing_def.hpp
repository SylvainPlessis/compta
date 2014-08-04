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
     const std::string forecast()
     {
        return "forecast";
     }

     const std::string delimiter()
     {
        return ",";
     }

     const std::string automatic()
     {
        return "PA";
     }
  }

 namespace AccountsParsing{
     const std::string bank()
     {
        return "bank";
     }

     const std::string cash()
     {
        return "cash";
     }

     const std::string savings()
     {
        return "savings";
     }

     const std::string delimiter()
     {
        return ",";
     }

     const std::string chooser()
     {
        return "main";
     }
 }

 namespace DataParsing{
     const char bank_str()
     {
        return 'B';
     }

     const char cash_str()
     {
        return 'L';
     }

     const char transfer_str()
     {
        return 'V';
     }

     const std::string false_str()
     {
        return "n";
     }

     const std::string delimiter()
     {
        return "|";
     }

     std::map<char, PostingType::PostingType> _posting_type_map;
     std::map<PostingType::PostingType,char> _posting_type_inverse_map;

     inline
     std::map<char, PostingType::PostingType> posting_type_map()
     {
       if(_posting_type_map.empty())
       {
         _posting_type_map[bank_str()] = PostingType::B;
         _posting_type_map[cash_str()] = PostingType::L;
         _posting_type_map[transfer_str()] = PostingType::V;
       }
       return _posting_type_map;
     }
//
     inline
     std::map<PostingType::PostingType,char> posting_type_inverse_map()
     {
       if(_posting_type_inverse_map.empty())
       {
         _posting_type_inverse_map[PostingType::B] = bank_str();
         _posting_type_inverse_map[PostingType::L] = cash_str();
         _posting_type_inverse_map[PostingType::V] = transfer_str();
       }
       return _posting_type_inverse_map;
     }
  }
}

#endif
