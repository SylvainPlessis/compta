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
#include "compta/forecast.hpp"

//C++
#include <iostream>
#include <string>
#include <vector>

int check(bool test, const std::string &words)
{
  if(test)return 0;
  std::cout << "Error in test: " << words << std::endl;
  return 1;
}

template <typename Containee>
int check_cat(const Compta::ForecastContainer<Containee> &cat,
              const std::string &name, float amount, float margin, unsigned int n,
              const std::string &more_words)
{
   float eps(1e-3);
   return    check(cat.amount() - amount < eps,"Category amount" + more_words)
          || check(cat.margin() - margin < eps,"Category margin" + more_words)
          || check(cat.n_objects() == n,"Category number of objects" + more_words)
          || check(cat.name() == name,"Category name" + more_words);
}

int tester()
{
  Compta::Operation op11("1.1",12.00,1.0,false,20120502,20201231);
  Compta::Operation op12("1.2",120.00,10.0,false,20120502,20201231);
  Compta::ForecastContainer<Compta::Operation> cat1;
  cat1.set_name("cat1");
  cat1.add_operation(op11);//cat 1, amount = 12.00, margin is 11.00

  Compta::Operation op21("2.1",150.00,1.00,false,20120502,20201231);
  Compta::Operation op22("2.2",950.00,2.00,false,20120502,20201231);
  Compta::Operation op23("2.3",275.56,3.00,false,20120502,20201231);
  Compta::ForecastContainer<Compta::Operation> cat2;
  cat2.set_name("cat2");
  cat2.add_operation(op21);
  cat2.add_operation(op22);
  cat2.add_operation(op23);//cat 2, amount = 1375.56, margin = 6.00

  Compta::Forecast forecast;
  forecast.add_forecast_category(cat1);
  forecast.add_forecast_category(cat2); 
  forecast.add_operation("cat1",op12);//amount is 1507.56, margin is 17.00
  forecast.set_currency(Compta::Currency::EUR);
  Compta::Forecast copy_forecast(forecast);
  
  int return_flag(0);

  return_flag = return_flag || check_cat(forecast.forecast().operations_list()[0],"cat1",132.00,11.02,2," in category 1")
                            || check_cat(forecast.forecast().operations_list()[1],"cat2",1375.56,6.00,3," in category 2")
                            || check_cat(forecast.forecast(),"forecast",1507.56,17.00,2," in forecast")
                            || check((forecast.currency() == Compta::Currency::EUR),"forecast currency");
  return_flag = return_flag || check_cat(copy_forecast.forecast(),"forecast",1507.56,17.00,2," in copy forecast")
                            || check((copy_forecast.currency() == Compta::Currency::EUR),"copy forecast currency");



  return return_flag;
}


int main()
{
  return tester();
}
