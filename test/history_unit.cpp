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
#include "compta/history.hpp"

//C++
#include <iostream>
#include <string>
#include <ctime>

int check(bool test, const std::string &words)
{
  if(test)return 0;
  std::cout << "Error in test " << words << std::endl;
  return 1;
}

int tester()
{
  time_t t = time(0);
  struct tm *now = localtime(&t);
  Compta::Date today(now->tm_mday, now->tm_mon + 1, 1900 + now->tm_year);
  std::string cat("category"), description("some description here");
  Compta::Date date(20120904);
  Compta::Date expected_date(today.count_date() + 10000); //next year
  Compta::Date expected_date_two(today.count_date() + 20000); //following year

  Compta::Posting history_one(cat,date,description,10.00,true);
  Compta::Posting history_two(cat,20130904,description,15.00,true); //state is 25.00
  
  Compta::Posting expected_one(cat,expected_date,description,5.00,false);
  Compta::Posting expected_two(cat,expected_date_two,description,8.32,false);//expected is 38.32
  Compta::History hist;
  hist.add_posting(history_two);
  hist.add_posting(expected_one);
  hist.add_posting(history_one);
  hist.add_posting(expected_two);
  int return_flag(0);

  float eps(1e-3);
  return_flag = return_flag || check((hist.history().size() == 2),"Number of history posting")
                            || check((hist.in_waiting().size() == 2),"Number of expected posting")
                            || check((hist.current_state() - 25.00 < eps),"current state amount")
                            || check((hist.expected_state() - 38.32 < eps),"expected state amount")
                            || check((hist.history()[0].date() == date),"sorting history")
                            || check((hist.in_waiting()[0].date() == expected_date),"sorting expected posting");

  Compta::History history(hist);

  return_flag = return_flag || check((history.history().size() == 2),"Number of history posting, copied")
                            || check((history.in_waiting().size() == 2),"Number of expected posting, copied")
                            || check((history.current_state() - 25.00L < eps),"current state amount, copied")
                            || check((history.expected_state() - 38.32L < eps),"expected state amount, copied")
                            || check((history.history()[0].date() == date),"sorting history, copied")
                            || check((history.in_waiting()[0].date() == expected_date),"sorting expected posting, copied");

  return return_flag;
}


int main()
{
  return tester();
}
