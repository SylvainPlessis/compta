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

#include "compta/category_report.hpp"

namespace Compta
{

  
  CategoryReport::CategoryReport():
    _date(DateUtils::tomonth()),
    _forecast_amount(-1.),
    _forecast_margin(-1.),
    _amount(0.),
    _expected_amount(0.)
  {
    return;
  }

  
  CategoryReport::CategoryReport(const Date &date, const ForecastContainer<Operation> &forecast_cat):
     _amount(0.),
     _expected_amount(0.)
  {
     this->initialize(date,forecast_cat);
  }

  
  CategoryReport::CategoryReport(const CategoryReport &rhs)
  {
     *this = rhs;
  }

  
  CategoryReport::~CategoryReport()
  {
     return;
  }

  
  void CategoryReport::initialize(const Date & date, const ForecastContainer<Operation> &forcat)
  {
      _date = date;
      _name = forcat.name();
      _forecast_amount = forcat.amount_this_month(_date.count_date());
      _forecast_margin = forcat.margin_this_month(_date.count_date());
      forcat.expected_operations(date.count_date(),_not_done_yet_this_month);
      for(unsigned int ind = 0; ind < _not_done_yet_this_month.size(); ind++)
      {
         _expected_amount += _not_done_yet_this_month[ind].amount();
      }
  }

  
  CategoryReport &CategoryReport::operator=(const CategoryReport &rhs)
  {
      if(this != &rhs)
      {
         _name                    = rhs.name();
         _date                    = rhs.date();
         _forecast_amount         = rhs.forecast_amount();
         _forecast_margin         = rhs.forecast_margin();
         _amount                  = rhs.amount();
         _expected_amount         = rhs.expected_amount() - rhs.amount();
         _done_this_month         = rhs.done();
         _not_done_this_month     = rhs.not_done();
         _not_done_yet_this_month = rhs.waiting();
      }

      return *this;
  }

  
  const std::string &CategoryReport::name() const
  {
     return _name;
  }
  
  
  const Date & CategoryReport::date() const
  {
     return _date;
  }
  
  
  float CategoryReport::forecast_amount()   const
  {
     return _forecast_amount;
  }
  
  
  float CategoryReport::forecast_margin()   const
  {
     return _forecast_margin;
  }
  
  
  float CategoryReport::amount() const
  {
     return _amount;
  }
  
  
  float CategoryReport::expected_amount() const
  {
     return _expected_amount + _amount;
  }

  
  const std::vector<Posting> & CategoryReport::done() const
  {
     return _done_this_month;
  }

  
  const std::vector<Posting> & CategoryReport::not_done() const
  {
     return _not_done_this_month;
  }

  
  const std::vector<Operation> & CategoryReport::waiting() const
  {
     return _not_done_yet_this_month;
  }

  
  void CategoryReport::add_posting(const Posting &post)
  {
     if(post.accounted())
     {
       _done_this_month.push_back(post);
       _amount -= post.amount();
       for(unsigned int o = 0; o < _not_done_yet_this_month.size(); o++)
       {
         if(post == _not_done_yet_this_month[o])
         {
             _expected_amount += post.amount();
             _not_done_yet_this_month.erase(_not_done_yet_this_month.begin() + o);
             break;
         }
       }
     }else
     {
       _not_done_this_month.push_back(post);
       _expected_amount -= post.amount();
     }

     return;

  }
}
