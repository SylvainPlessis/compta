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

}

#endif
