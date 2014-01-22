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
#include "compta/operation.hpp"
#include "compta/forecast_container.hpp"

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
                const std::string &name, float amount, float margin, unsigned int n)
{
   float eps(1e-3);
   return    check(cat.amount() - amount < eps,"Category amount")
          || check(cat.margin() - margin < eps,"Category margin")
          || check(cat.n_objects() == n,"Category number of objects")
          || check(cat.name() == name,"Category name");
}

int tester()
{
  Compta::Operation op11("1.1",12.00,1.00,false,20120502,20201231);
  Compta::Operation op12("1.2",120.00,10.00,false,20120502,20201231);//cat 1, amount = 132.00
  Compta::ForecastContainer<Compta::Operation> cat1;
  cat1.set_name("cat1");
  cat1.add_operation(op11);
  cat1.add_operation(op12);//margin is suppodedly 11.00

  Compta::Operation op21("2.1",150.00,10.00,false,20120502,20201231);
  Compta::Operation op22("2.2",950.00,100.00,false,20120502,20201231);
  Compta::Operation op23("2.3",275.56,1.00,false,20120502,20201231);//cat 2, amount = 1375.56
  Compta::ForecastContainer<Compta::Operation> cat2;
  cat2.set_name("cat2");
  cat2.add_operation(op21);
  cat2.add_operation(op22);
  cat2.add_operation(op23);//margin is 111.00

  Compta::ForecastContainer<Compta::ForecastContainer<Compta::Operation> > forecast_container;
  forecast_container.set_name("container");
  forecast_container.add_operation(cat1);
  forecast_container.add_operation(cat2); //amount is 1507.56

  Compta::ForecastContainer<Compta::ForecastContainer<Compta::Operation> > copy_container(forecast_container);
  
  int return_flag(0);

  return_flag = return_flag || check_cat(forecast_container.operations_list()[0],"cat1",132.00,11.00,2)
                            || check_cat(forecast_container.operations_list()[1],"cat2",1375.56,111.00,3)
                            || check_cat(forecast_container,"container",1507.56,122.00,2)
                            || check_cat(copy_container,"container",1507.56,122.00,2);


  return return_flag;
}


int main()
{
  return tester();
}
