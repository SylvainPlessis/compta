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

//Compta
#include "compta/posting.hpp"

//C++
#include <iostream>
#include <string>

int check(bool test, const std::string &words)
{
  if(test)return 0;
  std::cout << "Error in test " << words << std::endl;
  return 1;
}

int check_posting(const Compta::Posting &test, 
                  const std::string &cat, const Compta::Date &date, 
                  const std::string &desc, float amount, bool acc,
                  const Compta::PostingType::PostingType &id,
                  const std::string &fw)
{
  float eps(1e-3);
  return check(test.category() == cat, fw + " posting category") ||
         check(test.date() == date, fw + " posting date") ||
         check(test.description() == desc, fw + " posting description") ||
         check(test.amount() - amount < eps, fw + " posting amount") ||
         check(test.accounted() == acc, fw + " posting accounted") ||
         check(test.identifier() == id, fw + " posting type");
}

int tester()
{
  Compta::Posting default_post;
  std::string cat("category"), description("some description here");
  Compta::Date date(20120904);
  float amount(15.12);
  Compta::PostingType::PostingType pt(Compta::PostingType::V);
  Compta::Posting custom_one(cat,date,description,amount,true);
  Compta::Posting custom_two(cat,date,description,amount,false);
  custom_two.set_identifier(pt);
  int return_flag(0);

  return_flag = return_flag || check_posting(default_post,std::string(),Compta::Date(),std::string(),0.,true,Compta::PostingType::B,"default")
                            || check_posting(custom_one,cat,date,description,amount,true,Compta::PostingType::B,"custom one")
                            || check_posting(custom_two,cat,date,description,amount,false,pt,"custom two")
                            || check_posting(-custom_two,cat,date,description,-amount,false,pt,"minus custom two");

  default_post.set_description(description);
  default_post.set_category(cat);
  default_post.set_amount(amount);
  default_post.set_date(date);
  default_post.set_identifier(pt);
  default_post.set_accounted(true);
  Compta::Posting copy_post(default_post);

  return_flag = return_flag || check_posting(default_post,cat,date,description,amount,true,pt,"default changed")
                            || check_posting(copy_post,cat,date,description,amount,true,pt,"default changed");

  return return_flag;
}


int main()
{
  return tester();
}
