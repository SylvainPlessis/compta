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

#ifndef COMPTA_MONEY_H
#define COMPTA_MONEY_H

//Compta
#include "compta/money_enum.hpp"
#include "compta/compta_asserts.hpp"

//C++
#include <map>
#include <string>

namespace Compta{

  class Money{
     public:
        Money();
        Money(const std::string &money);
        Money(const Currency::Currency &money);
        ~Money();

        //!initializes
        void set_money(const std::string &money);

        //!initializes
        void set_money(const Currency::Currency &money);

        //! TeX output string
        const std::string tex_money() const;
        //! enum output
        const Currency::Currency money() const;
        //! string output
        const std::string str_money() const;

     private:
        std::map<std::string,Currency::Currency> _money_read_map;
        std::map<Currency::Currency,std::string> _money_write_map;
        std::map<Currency::Currency,std::string> _money_write_tex_map;

        std::string _tex_currency;
        std::string _str_currency;
        Currency::Currency  _enum_currency;
  };

inline
Money::Money()
{
//
  _money_read_map["EUR"] = Currency::EUR;
  _money_read_map["USD"] = Currency::USD;
//
  _money_write_map[Currency::EUR] = "EUR";
  _money_write_map[Currency::USD] = "USD";
//
  _money_write_tex_map[Currency::EUR] = "\\EUR";
  _money_write_tex_map[Currency::USD] = "\\$";
}

inline
Money::Money(const Currency::Currency &money)
{
  _money_read_map["EUR"] = Currency::EUR;
  _money_read_map["USD"] = Currency::USD;
//
  _money_write_map[Currency::EUR] = "EUR";
  _money_write_map[Currency::USD] = "USD";
//
  _money_write_tex_map[Currency::EUR] = "\\EUR";
  _money_write_tex_map[Currency::USD] = "\\$";

   this->set_money(money);
}


inline
Money::Money(const std::string &money)
{
  _money_read_map["EUR"] = Currency::EUR;
  _money_read_map["USD"] = Currency::USD;
//
  _money_write_map[Currency::EUR] = "EUR";
  _money_write_map[Currency::USD] = "USD";
//
  _money_write_tex_map[Currency::EUR] = "\\EUR";
  _money_write_tex_map[Currency::USD] = "\\$";

   this->set_money(money);
}

inline
void Money::set_money(const std::string &money)
{
   if(!_money_read_map.count(money))
          compta_money_error("This money enum is not supported: " + money);
   _str_currency  = money;
   _enum_currency = _money_read_map.at(_str_currency);
   _tex_currency  = _money_write_tex_map.at(_enum_currency);
}

inline
void Money::set_money(const Currency::Currency &money)
{
   if(!_money_write_map.count(money))
          compta_money_error("This money is not supported: " + money);
   _enum_currency = money;
   _str_currency  = _money_write_map.at(money);
   _tex_currency  = _money_write_tex_map.at(_enum_currency);
}

inline
Money::~Money()
{
  return;
}

inline
const std::string Money::str_money() const
{
  return _str_currency;
}

inline
const std::string Money::tex_money() const
{
  return _tex_currency;
}

inline
const Currency::Currency Money::money() const
{
  return _enum_currency;
}

}

#endif
