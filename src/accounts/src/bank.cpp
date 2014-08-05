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

#include "compta/bank.hpp"

namespace Compta
{

  
  Bank::Bank(const std::string &name, const Date & start_date, float amount, Currency::Currency money):
        AccountBase(name,start_date,amount,money)
  {
     return;
  }

  
  Bank::Bank(const Bank &rhs):
      AccountBase(*(static_cast<const AccountBase*>(&rhs)))
  {
     *this = rhs;
     return;
  }

  
  Bank::~Bank()
  {
     return;
  }

  
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

  
  void Bank::add_savings_account(const Savings &saving, const std::string &sname)
  {
     _savings.push_back(saving);
     _savings_list.push_back(sname);
     _savings_map[sname] = _savings.size() - 1;
  }

  
  const std::vector<Savings> Bank::savings() const
  {
      return _savings;
  }

  
  const std::map<std::string,unsigned int> Bank::savings_map() const
  {
      return _savings_map;
  }

  
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

  
  const std::vector<std::string> Bank::savings_list() const
  {
     return _savings_list;
  }

}
