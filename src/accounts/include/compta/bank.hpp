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

#ifndef COMPTA_BANK_H
#define COMPTA_BANK_H

//Compta
#include "compta/account_base.hpp"
#include "compta/posting.hpp"
#include "compta/savings.hpp"

//C++
#include <string>
#include <vector>
#include <map>

namespace Compta{

  class Bank:public AccountBase{
     public:
      Bank(const std::string &name = "Account", const Date & start_date = Date(1,1,1900), 
                  float amount = 0., Currency::Currency  money = Currency::EUR);
      Bank(const Bank &rhs);
      ~Bank();

      //!adds a posting, test if savings concerned
      void add_posting(const Posting &post, const unsigned int &sav = -1);

      //!adds a saving account
      void add_savings_account(const Savings &saving, const std::string &sname);

      //!\return the savings
      const std::vector<Savings> savings() const;

      //!\return the savings name
      const std::vector<std::string> savings_list() const;

      //! \return the savings map
      const std::map<std::string,unsigned int> savings_map() const;

      //!Operator
      Bank &operator=(const Bank &rhs);

     private:
      std::vector<Savings> _savings;
      std::vector<std::string> _savings_list;
      std::map<std::string,unsigned int> _savings_map;
      
  };

  inline
  Bank::Bank(const std::string &name, const Date & start_date, float amount, Currency::Currency money):
        AccountBase(name,start_date,amount,money)
  {
     return;
  }

  inline
  Bank::Bank(const Bank &rhs):
      AccountBase(*(static_cast<const AccountBase*>(&rhs)))
  {
     *this = rhs;
     return;
  }

  inline
  Bank::~Bank()
  {
     return;
  }

  inline
  void Bank::add_posting(const Posting &post, const unsigned int &sav)
  {
     _records.add_posting(post);
     if((int)sav != -1)
     {
        if(sav >= _savings.size())
                        compta_bank_error("Savings account requested does not exist");
        _savings[sav].add_posting(-post);
     }
  }

  inline
  void Bank::add_savings_account(const Savings &saving, const std::string &sname)
  {
     _savings.push_back(saving);
     _savings_list.push_back(sname);
     _savings_map[sname] = _savings.size() - 1;
  }

  inline
  const std::vector<Savings> Bank::savings() const
  {
      return _savings;
  }

  inline
  const std::map<std::string,unsigned int> Bank::savings_map() const
  {
      return _savings_map;
  }

  inline
  Bank &Bank::operator=(const Bank &rhs)
  {
      if(this != &rhs)
      {
        _savings = rhs.savings();
        _savings_map = rhs.savings_map();
        _savings_list = rhs.savings_list();
      }
      return *this;
  }

  inline
  const std::vector<std::string> Bank::savings_list() const
  {
     return _savings_list;
  }

}

#endif
