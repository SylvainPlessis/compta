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

#include "compta/forecast.hpp"

namespace Compta
{

  
  Forecast::Forecast():
     _currency(Currency::EUR)
  {
    _forecast.set_name("forecast");
    return;
  }

  
  Forecast::Forecast(const Forecast &rhs)
  {
    *this = rhs;
    return;
  }

  
  Forecast::~Forecast()
  {
    return;
  }

  
  Forecast &Forecast::operator=(const Forecast &rhs)
  {
     if(this != &rhs)
     {
       _forecast = rhs.forecast();
       _currency = rhs.currency();
     }
     return *this;
  }

  
  void Forecast::add_operation(const std::string &category_name, const Operation &op)
  {
     _forecast.operation(category_name).add_operation(op);
     _forecast.update_amount();
  }

  
  void Forecast::add_forecast_category(const ForecastCategory &forecast_category)
  {
     _forecast.add_operation(forecast_category);
     _forecast.set_margin(_forecast.margin() + forecast_category.margin());
  }

  
  const ForecastContainer<ForecastCategory> &Forecast::forecast() const
  {
     return _forecast;
  }

  
  ForecastContainer<ForecastCategory> &Forecast::forecast()
  {
     return _forecast;
  }

  
  void Forecast::set_currency(const Currency::Currency &cur)
  {
     _currency = cur;
  }

  
  const Currency::Currency Forecast::currency() const
  {
     return _currency;
  }

  
  void Forecast::expected_operations(const Date &date_month, std::vector<Operation> &op) const
  {
     _forecast.expected_operations(date_month.count_date(),op);
  }

}
