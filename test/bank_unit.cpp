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

//Compta
#include "compta/bank.hpp"

//C++
#include <iostream>
#include <string>

int check(bool test, const std::string &words)
{
  if(test)return 0;
  std::cout << "Error in test " << words << std::endl;
  return 1;
}

int tester()
{
  Compta::Bank account("an account",Compta::Date("01/09/2013"),0.,Compta::Currency::EUR);
  Compta::Posting operation("category",std::string("12/11/2013"),"Some operation",15.25,true);
  Compta::Savings epargne;
  std::string namesav("savings");

  account.add_savings_account(epargne,namesav);
  account.add_posting(operation,0);
  Compta::Bank copy_account(account);
  int return_flag(0);

  return_flag = return_flag || check((account.name() == "an account"),"account name")
                            || check((account.currency() == Compta::Currency::EUR),"account currency")
                            || check((account.currency() == Compta::Currency::EUR),"account name")
                            || check((account.creation() == "01/09/2013"),"account creation")
                            || check((account.savings_map().at(namesav) == 0),"savings index");


  return_flag = return_flag || check((copy_account.name() == "an account"),"account name")
                            || check((copy_account.currency() == Compta::Currency::EUR),"account currency")
                            || check((copy_account.currency() == Compta::Currency::EUR),"account name")
                            || check((copy_account.creation() == "01/09/2013"),"account creation");

  return return_flag;
}


int main()
{
  return tester();
}
