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

}

#endif
