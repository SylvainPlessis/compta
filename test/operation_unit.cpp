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
#include "compta/date.hpp"
#include "compta/operation.hpp"

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
  Compta::Date date_start_two(1,5,2013);
  Compta::Date date_end_two(31,12,2020);
  std::string name_one("test");
  std::string name_two("test again");
  float amount_one(120.25);
  float amount_two(10.0);
  float margin_one(20.50);
  float margin_two(1.0);
  bool auto_one(false);
  bool auto_two(true);
  unsigned int period_one(1);
  unsigned int period_two(3);

  Compta::Operation default_op;
  Compta::Operation operation_one(name_one,amount_one,margin_one,auto_one);
  Compta::Operation operation_two(name_two,amount_two,margin_two,auto_two,date_start_two,date_end_two,period_two);
  int return_flag(0);
  float eps(1e-3);
  return_flag = return_flag || check(default_op.name().empty(), "default name")
                            || check(default_op.amount() < eps, "default amount")
                            || check(default_op.margin() < eps, "default margin")
                            || check(default_op.starting_date().count_date() == 0, "default starting date")
                            || check(default_op.ending_date().count_date() == 0, "default ending date")
                            || check(!(default_op.automatic()), "default automatic")
                            || check(default_op.period() == period_one, "default period (1)");
  return_flag = return_flag || check(operation_one.name() == name_one, "custom name one (test)")
                            || check(operation_one.amount() - amount_one < eps, "custom amount one (120.25)")
                            || check(operation_one.margin() - margin_one < eps, "custom margin one (20.50)")
                            || check(operation_one.starting_date().count_date() == Compta::DateUtils::date_min(), "starting date one (default)")
                            || check(operation_one.ending_date().count_date() == Compta::DateUtils::date_max(), "ending date one (default)")
                            || check(operation_one.automatic() == auto_one, "custom automatic one (false)")
                            || check(operation_one.period() == period_one, "custom period one (1)");
  return_flag = return_flag || check(operation_two.name() == name_two, "custom name two (test again)")
                            || check(operation_two.amount() - amount_two < eps, "custom amount two (10.0)")
                            || check(operation_two.margin() - margin_two < eps, "custom margin two (1.0)")
                            || check(operation_two.starting_date() == date_start_two, "custom starting date (01/05/2013)")
                            || check(operation_two.ending_date() == date_end_two, "custom ending date (31/12/2020)")
                            || check(operation_two.automatic() == auto_two, "custom automatic two (true)")
                            || check(operation_two.period() == period_two, "custom period two (3)");

  return return_flag;
}


int main()
{
  return tester();
}
