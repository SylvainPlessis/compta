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

#ifndef COMPTA_MONTHLY_REPORT_H
#define COMPTA_MONTHLY_REPORT_H

//compta
#include "compta/category_report.hpp"
#include "compta/date.hpp"
#include "compta/forecast.hpp"

//C++
#include <vector>

namespace Compta
{

  /*!\class MonthlyReport
   *
   * This class stores CategoryReport
   * for each Forecast category.
   * It concerns only operation relevant
   * to a given month. 
   *  
   */
  class MonthlyReport
  {
     public:
        //!constructor
        MonthlyReport(const Forecast &forecast, const Date & date);
        //!copy constructor
        MonthlyReport(const MonthlyReport &rhs);
        //!destructor
        ~MonthlyReport();

        //!add a line, update state
        void add_posting(const Posting &post);

        //!add lines, update state
        void add_posting(const std::vector<Posting> &post);

        const Forecast & forecast() const;

        const Date &     date()     const;

        const std::vector<CategoryReport> & report() const;

        float amount()          const;
        float expected_amount() const;
        float forecast_amount() const;
        float forecast_margin() const;

     private:

        //!sets the categories, using the Forecast reference
        void set_categories();

        std::vector<CategoryReport> _report;
        const Forecast *            _forecast; 
        Date                        _date;

        float                       _forecast_amount;
        float                       _forecast_margin;
  };

}
#endif
