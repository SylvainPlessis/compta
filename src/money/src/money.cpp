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

#include "compta/money.hpp"

namespace Compta
{


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


void Money::set_money(const std::string &money)
{
   if(!_money_read_map.count(money))
          compta_money_error("This money enum is not supported: " + money);
   _str_currency  = money;
   _enum_currency = _money_read_map.at(_str_currency);
   _tex_currency  = _money_write_tex_map.at(_enum_currency);
}


void Money::set_money(const Currency::Currency &money)
{
   if(!_money_write_map.count(money))
          compta_money_error("This money is not supported: " + money);
   _enum_currency = money;
   _str_currency  = _money_write_map.at(money);
   _tex_currency  = _money_write_tex_map.at(_enum_currency);
}


Money::~Money()
{
  return;
}


const std::string Money::str_money() const
{
  return _str_currency;
}


const std::string Money::tex_money() const
{
  return _tex_currency;
}


const Currency::Currency Money::money() const
{
  return _enum_currency;
}

}
