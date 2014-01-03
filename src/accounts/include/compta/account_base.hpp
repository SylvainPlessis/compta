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

#ifndef COMPTA_ACCOUNT_BASE_H
#define COMPTA_ACCOUNT_BASE_H

//Compta
#include "compta/posting.hpp"
#include "compta/history.hpp"
#include "compta/money_enum.hpp"
#include "compta/date.hpp"

//C++
#include <string>
#include <map>

namespace Compta{

  class AccountBase{
     public:
      AccountBase();
      AccountBase(const AccountBase &rhs);
      ~AccountBase();

      //!\return the name
      const std::string name() const;
      //!\return the history
      const History records() const;
      //!\return the currency
      const Currency::Currency currency() const;
      //!\return the creation date
      const Date creation() const;

      //!sets the name
      void set_name(const std::string &name);
      //!sets the currency
      void set_currency(const Currency::Currency &currency);
      //!sets the date
      void set_creation(const Date &creation);

      //!adds a line
      void add_posting(const Posting &post);

      //! Operator
      AccountBase &operator=(const AccountBase &rhs);

     protected:
      History            _records;
      std::string        _name;
      Currency::Currency _currency;
      Date               _creation;
  };

  inline
  AccountBase::AccountBase():
      _currency(Currency::EUR)
  {
     return;
  }

  inline
  AccountBase::AccountBase(const AccountBase &rhs)
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
  void AccountBase::set_creation(const Date &creation)
  {
     _creation = creation;
  }

  inline
  AccountBase &AccountBase::operator=(const AccountBase &rhs)
  {
     if(this != &rhs)
     {
       _records = rhs.records();
       _name = rhs.name();
       _currency = rhs.currency();
       _creation = rhs.creation();
     }
     return *this;
  }

}

#endif
