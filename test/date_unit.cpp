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
#include "compta/date.hpp"

//C++
#include <iostream>
#include <string>
#include <vector>

int test_date_equality(const Compta::Date &date1, const Compta::Date &date2)
{
  if(date1 != date2 || 
     date1 != date2.date_string() ||
     date1 != date2.count_date())
  {
     std::cerr << date1 << " and " << date2 << " are not equal" << std::endl;
     return 1;
  }

  return 0;
}

int test_date_superior(const Compta::Date &date1, const Compta::Date &date2)
{
  if(date1 < date2 || 
     date1 < date2.date_string() || 
     date1 < date2.count_date())
  {
     std::cerr << date1 << " is not superior or equal to " << date2 << std::endl;
     return 1;
  }

  return 0;
}

int test_date_superior_strict(const Compta::Date &date1, const Compta::Date &date2)
{
  if(date1 <= date2 || 
     date1 <= date2.date_string() || 
     date1 <= date2.count_date()  ||
     date1.older(date2))
  {
     std::cerr << date1 << " is not strictly superior to " << date2 << std::endl;
     return 1;
  }

  return 0;
}

int test_date_inferior(const Compta::Date &date1, const Compta::Date &date2)
{
  if(date1 > date2 || 
     date1 > date2.date_string() || 
     date1 > date2.count_date())
  {
     std::cerr << date1 << " is not inferior or equal to " << date2 << std::endl;
     return 1;
  }

  return 0;
}

int test_date_inferior_strict(const Compta::Date &date1, const Compta::Date &date2)
{
  if(date1 >= date2 || 
     date1 >= date2.date_string() || 
     date1 >= date2.count_date()  ||
     date1.newer(date2))
  {
     std::cerr << date1 << " is not strictly inferior to " << date2 << std::endl;
     return 1;
  }

  return 0;
}

void test_part_date(unsigned int testee, unsigned int tester, int &flag, const std::string &words)
{
   if(testee != tester)
   {
      std::cerr << "date has incorrect " << words 
                << ": " << testee << " instead of " << tester << std::endl;
      flag = 1;
   }
}

int test_date_unsigned_int(const Compta::Date &date, unsigned int j, unsigned int m, unsigned int a)
{
   int return_flag(0);
   test_part_date(date.day(),j,return_flag,"day");
   test_part_date(date.month(),m,return_flag,"month");
   test_part_date(date.year(),a,return_flag,"year");
   test_part_date(date.count_date(),a * 10000 + m * 100 + j,return_flag,"count");
   return return_flag;
}

int test_date()
{
   Compta::Date date_one("02/05/2012"), 
                date_two(2,5,12),
                date_three(2,5,2012),
                date_four(20120502);
   Compta::Date copy_date(date_one);
   Compta::Date date_strict_inf("01/04/2012");
   Compta::Date date_strict_sup("01/04/2013");

   int return_flag(0);
   return_flag = return_flag ||
                 test_date_equality(date_one,date_two)    ||
                 test_date_equality(date_one,date_three)  ||
                 test_date_equality(date_one,date_four)   ||
                 test_date_equality(date_two,date_three)  ||
                 test_date_equality(date_two,date_four)   ||
                 test_date_equality(date_three,date_four) ||
                 test_date_equality(copy_date,date_one)   ||
                 test_date_superior_strict(copy_date,date_strict_inf) ||
                 test_date_inferior_strict(copy_date,date_strict_sup) ||
                 test_date_inferior(copy_date,date_strict_sup) ||
                 test_date_superior(copy_date,date_strict_inf) ||
                 test_date_inferior(copy_date,date_one) ||
                 test_date_superior(copy_date,date_one);

  return_flag = return_flag ||
                test_date_unsigned_int(date_one,2,5,2012) ||
                test_date_unsigned_int(date_two,2,5,2012) ||
                test_date_unsigned_int(date_three,2,5,2012) ||
                test_date_unsigned_int(date_four,2,5,2012);

  return return_flag;
}


int main()
{
  return test_date();
}
