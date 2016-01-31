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

#include "compta/monthly_report.hpp"

namespace Compta
{

  
  const Forecast & MonthlyReport::forecast() const
  {
     return *_forecast;
  }

  
  const Date & MonthlyReport::date() const
  {
     return _date;
  }

  
  MonthlyReport::MonthlyReport(const Forecast &forecast, const Date & date):
    _forecast(&forecast),
    _date(date),
    _forecast_amount(0),
    _forecast_margin(0),
    _forecast_amount_no_income(0),
    _forecast_margin_no_income(0)
  {
    this->set_categories();
    return;
  }

  
  MonthlyReport::MonthlyReport(const MonthlyReport &rhs):
    _forecast((&rhs.forecast())),
    _date(rhs.date()),
    _forecast_amount(rhs.forecast_amount()),
    _forecast_margin(rhs.forecast_margin()),
    _forecast_amount_no_income(rhs.forecast_amount_no_income()),
    _forecast_margin_no_income(rhs.forecast_margin_no_income())
  {
    _report = rhs.report();
    return;
  }

  
  MonthlyReport::~MonthlyReport()
  {
    return;
  }

  
  void MonthlyReport::set_categories()
  {
     for(unsigned int ip = 0; ip < _forecast->forecast().operations_list().size(); ip++)
     {
        _report.push_back(CategoryReport(_date,_forecast->forecast().operations_list()[ip]));
        _forecast_amount += _report.back().forecast_amount();
        _forecast_margin += _report.back().forecast_margin();
        if(_report.back().forecast_amount() > 0)
        {
          _forecast_amount_no_income += _report.back().forecast_amount();
          _forecast_margin_no_income += _report.back().forecast_margin();
        }
     }
  }

  
  void MonthlyReport::add_posting(const std::vector<Posting> &post)
  {
     for(unsigned int ip = 0; ip < post.size(); ip++)
     {
        this->add_posting(post[ip]);
     }
  }

  
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

  
  const std::vector<CategoryReport> & MonthlyReport::report() const
  {
     return _report;
  }

  
  float MonthlyReport::amount() const
  {
    float amount(0);
    for(unsigned int ic = 0; ic < _report.size(); ic++)
    {
        amount += _report[ic].amount();
    }
    return amount;
  }

  
  float MonthlyReport::expected_amount() const
  {
    float amount(0);
    for(unsigned int ic = 0; ic < _report.size(); ic++)
    {
        amount += _report[ic].expected_amount();
    }
    return amount;
  }

  float MonthlyReport::amount_no_income() const
  {
    float amount(0);
    for(unsigned int ic = 0; ic < _report.size(); ic++)
    {
        if(_report[ic].forecast_amount() < 0)continue;
        amount += _report[ic].amount();
    }
    return amount;
  }

  float MonthlyReport::expected_amount_no_income() const
  {
    float amount(0);
    for(unsigned int ic = 0; ic < _report.size(); ic++)
    {
        if(_report[ic].forecast_amount() < 0)continue;
        amount += _report[ic].expected_amount();
    }
    return amount;
  }
  
  float MonthlyReport::forecast_amount() const
  {
    return _forecast_amount;
  }

  
  float MonthlyReport::forecast_margin() const
  {
    return _forecast_margin;
  }
  
  float MonthlyReport::forecast_amount_no_income() const
  {
    return _forecast_amount_no_income;
  }

  
  float MonthlyReport::forecast_margin_no_income() const
  {
    return _forecast_margin_no_income;
  }

}
