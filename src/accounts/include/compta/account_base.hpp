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

#ifndef COMPTA_ACCOUNT_BASE_H
#define COMPTA_ACCOUNT_BASE_H

//Compta
#include "compta/posting.hpp"
#include "compta/history.hpp"
#include "compta/money_enum.hpp"
#include "compta/date.hpp"
#include "compta/money.hpp"

//C++
#include <string>
#include <map>

namespace Compta{

  class AccountBase{
     public:
      AccountBase(const std::string &name, const Date & start_date, 
                  float amount, Currency::Currency  money);
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
      //!\return the creation amount
      float creation_amount() const;

      //!sets the name
      void set_name(const std::string &name);
      //!sets the currency
      void set_currency(const Currency::Currency &currency);

      //!adds a line
      void add_posting(const Posting &post);

      //! Operator
      AccountBase &operator=(const AccountBase &rhs);

      //! prints the history + creation
      void print(std::ostream& out = std::cout) const;

      //! Formatted print.
      friend std::ostream& operator << (std::ostream& os, const AccountBase &histoire)
      {
        histoire.print(os);
        return os;
      }

     protected:
      const Date         _creation;
      const float        _creation_amount;
      History            _records;
      std::string        _name;
      Currency::Currency _currency;

     private:
      AccountBase();
  };


}

#endif
