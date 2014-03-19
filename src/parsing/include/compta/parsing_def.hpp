//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//-----------------------------------------------------------------------el-

#ifndef COMPTA_PARSING_DEF_H
#define COMPTA_PARSING_DEF_H

//Compta
#include "compta/posting_enum.hpp"

//C++
#include <map>

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
        return "->";
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
