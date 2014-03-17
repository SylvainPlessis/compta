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

#ifndef COMPTA_FORECAST_H
#define COMPTA_FORECAST_H

//Compta
#include "compta/operation.hpp"
#include "compta/forecast_container.hpp"
#include "compta/money_enum.hpp"

//C++
#include <vector>
#include <map>
#include <string>

namespace Compta{

  typedef ForecastContainer<Operation> ForecastCategory;

  /*!\class Forecast

     This class contains the actual forecast: _forecast, which
     is a ForecastConstainer<ForecastConstainer<Operation> >, to
     obtain the right structure.
     The money by default is Currency::EUR
  */
  class Forecast{
      public:
        Forecast();
        Forecast(const Forecast &rhs);
        ~Forecast();

        //! adds an operation given the category
        void add_operation(const std::string &category_name, const Operation &op);

        //! adds a forecast category
        void add_forecast_category(const ForecastCategory &forecast_category);

        //! sets the currency
        void set_currency(const Currency::Currency &cur);

        //!\return the forecast
        const ForecastContainer<ForecastCategory> &forecast() const;

        //!\return the currency
        const Currency::Currency currency() const;

        //!\return writable forecast
        ForecastContainer<ForecastCategory> &forecast();

        //!operator
        Forecast &operator=(const Forecast &rhs);

        //!adds the expected operations of the month
        void expected_operations(const Date &date_month, std::vector<Operation> &op) const;

      private:
        ForecastContainer<ForecastCategory> _forecast;
        Currency::Currency _currency;
  };

  inline
  Forecast::Forecast():
     _currency(Currency::EUR)
  {
    _forecast.set_name("forecast");
    return;
  }

  inline
  Forecast::Forecast(const Forecast &rhs)
  {
    *this = rhs;
    return;
  }

  inline
  Forecast::~Forecast()
  {
    return;
  }

  inline
  Forecast &Forecast::operator=(const Forecast &rhs)
  {
     if(this != &rhs)
     {
       _forecast = rhs.forecast();
       _currency = rhs.currency();
     }
     return *this;
  }

  inline
  void Forecast::add_operation(const std::string &category_name, const Operation &op)
  {
     _forecast.operation(category_name).add_operation(op);
     _forecast.update_amount();
  }

  inline
  void Forecast::add_forecast_category(const ForecastCategory &forecast_category)
  {
     _forecast.add_operation(forecast_category);
     _forecast.set_margin(_forecast.margin() + forecast_category.margin());
  }

  inline
  const ForecastContainer<ForecastCategory> &Forecast::forecast() const
  {
     return _forecast;
  }

  inline
  ForecastContainer<ForecastCategory> &Forecast::forecast()
  {
     return _forecast;
  }

  inline
  void Forecast::set_currency(const Currency::Currency &cur)
  {
     _currency = cur;
  }

  inline
  const Currency::Currency Forecast::currency() const
  {
     return _currency;
  }

  inline
  void Forecast::expected_operations(const Date &date_month, std::vector<Operation> &op) const
  {
     _forecast.expected_operations(date_month.count_date(),op);
  }

}

#endif
