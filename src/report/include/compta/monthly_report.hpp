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

        //!sets the caterories, using the Forecast reference
        void set_categories();

        std::vector<CategoryReport> _report;
        const Forecast *            _forecast; 
        Date                        _date;

        float                       _forecast_amount;
        float                       _forecast_margin;
  };

  inline
  const Forecast & MonthlyReport::forecast() const
  {
     return *_forecast;
  }

  inline
  const Date & MonthlyReport::date() const
  {
     return _date;
  }

  inline
  MonthlyReport::MonthlyReport(const Forecast &forecast, const Date & date):
    _forecast(&forecast),
    _date(date),
    _forecast_amount(0.),
    _forecast_margin(0.)
  {
    this->set_categories();
    return;
  }

  inline
  MonthlyReport::MonthlyReport(const MonthlyReport &rhs):
    _forecast((&rhs.forecast())),
    _date(rhs.date()),
    _forecast_amount(rhs.forecast_amount()),
    _forecast_margin(rhs.forecast_margin())
  {
    _report = rhs.report();
    return;
  }

  inline
  MonthlyReport::~MonthlyReport()
  {
    return;
  }

  inline
  void MonthlyReport::set_categories()
  {
     for(unsigned int ip = 0; ip < _forecast->forecast().operations_list().size(); ip++)
     {
        _report.push_back(CategoryReport(_date,_forecast->forecast().operations_list()[ip]));
        _forecast_amount += _report.back().forecast_amount();
        _forecast_margin += _report.back().forecast_margin();
     }
  }

  inline
  void MonthlyReport::add_posting(const std::vector<Posting> &post)
  {
     for(unsigned int ip = 0; ip < post.size(); ip++)
     {
        this->add_posting(post[ip]);
     }
  }

  inline
  void MonthlyReport::add_posting(const Posting &post)
  {
     for(unsigned int ic= 0; ic < _report.size(); ic++)
     {
        if(post.category() == _report[ic].name())
        {
           _report[ic].add_posting(post);
           return;
        }
     }

     std::cerr << "This posting has an unknown category:\n"
               << post << std::endl;
     compta_error();
  }

  inline
  const std::vector<CategoryReport> & MonthlyReport::report() const
  {
     return _report;
  }

  inline
  float MonthlyReport::amount() const
  {
    float amount(0.);
    for(unsigned int ic = 0; ic < _report.size(); ic++)
    {
        amount += _report[ic].amount();
    }
    return amount;
  }

  inline
  float MonthlyReport::expected_amount() const
  {
    float amount(0.);
    for(unsigned int ic = 0; ic < _report.size(); ic++)
    {
        amount += _report[ic].expected_amount();
    }
    return amount;
  }

  inline
  float MonthlyReport::forecast_amount() const
  {
    return _forecast_amount;
  }

  inline
  float MonthlyReport::forecast_margin() const
  {
    return _forecast_margin;
  }

}
#endif
