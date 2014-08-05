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

  inline
  AccountBase::AccountBase(const std::string &name, const Date & start_date, float amount, Currency::Currency mon):
      _creation(start_date),
      _creation_amount(amount),
      _records(_creation_amount),
      _name(name),
      _currency(mon)
  {
     return;
  }

  inline
  AccountBase::AccountBase(const AccountBase &rhs):
      _creation(rhs.creation()),
      _creation_amount(rhs.creation_amount()),
      _records(_creation_amount)
  {
     *this = rhs;
     return;
  }

  inline
  AccountBase::~AccountBase()
  {
     return;
  }

  inline
  void AccountBase::add_posting(const Posting &post)
  {
     _records.add_posting(post);
  }

  inline
  const std::string AccountBase::name() const
  {
      return _name;
  }

  inline
  const Currency::Currency AccountBase::currency() const
  {
      return _currency;
  }

  inline
  const History AccountBase::records() const
  {
     return _records;
  }

  inline
  const Date AccountBase::creation() const
  {
     return _creation;
  }

  inline
  float AccountBase::creation_amount() const
  {
     return _creation_amount;
  }

  inline
  void AccountBase::set_name(const std::string &name)
  {
     _name = name;
  }

  inline
  void AccountBase::set_currency(const Currency::Currency &currency)
  {
     _currency = currency;
  }

  inline
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

  inline
  void AccountBase::print(std::ostream& out) const
  {
      Money cur(_currency);
      out << "Creation, le " << _creation << " avec " << _creation_amount << " " << cur.str_money() << std::endl;
      out << _records;
  }


}
