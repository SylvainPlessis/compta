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

#include "compta/account_base.hpp"

namespace Compta{

  
  AccountBase::AccountBase(const std::string &name, const Date & start_date, float amount, Currency::Currency mon):
      _creation(start_date),
      _creation_amount(amount),
      _records(_creation_amount),
      _name(name),
      _currency(mon)
  {
     return;
  }

  
  AccountBase::AccountBase(const AccountBase &rhs):
      _creation(rhs.creation()),
      _creation_amount(rhs.creation_amount()),
      _records(_creation_amount)
  {
     *this = rhs;
     return;
  }

  
  AccountBase::~AccountBase()
  {
     return;
  }

  
  void AccountBase::add_posting(const Posting &post)
  {
     _records.add_posting(post);
  }

  
  const std::string AccountBase::name() const
  {
      return _name;
  }

  
  const Currency::Currency AccountBase::currency() const
  {
      return _currency;
  }

  
  const History AccountBase::records() const
  {
     return _records;
  }

  
  const Date AccountBase::creation() const
  {
     return _creation;
  }

  
  float AccountBase::creation_amount() const
  {
     return _creation_amount;
  }

  
  void AccountBase::set_name(const std::string &name)
  {
     _name = name;
  }

  
  void AccountBase::set_currency(const Currency::Currency &currency)
  {
     _currency = currency;
  }

  
  AccountBase &AccountBase::operator=(const AccountBase &rhs)
  {
     if(this != &rhs)
     {
       _records = rhs.records();
       _name = rhs.name();
       _currency = rhs.currency();
     }
     return *this;
  }

  
  void AccountBase::print(const Date & from, const Date & to, std::ostream& out) const
  {
      Money cur(_currency);
      for(unsigned int i = 0; i < 31; i++)out << "*";
      out << std::setprecision(2) << std::fixed;
      out << "\nCompte " << _name << std::endl;
      out << "Creation, le " << _creation << " avec " << _creation_amount << " " << cur.str_money() << std::endl << std::endl;
      _records.print(from,to,out);
      for(unsigned int i = 0; i < 31; i++)out << "*";
      out << std::endl;
  }

}
