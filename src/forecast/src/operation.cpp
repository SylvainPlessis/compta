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

#include "compta/operation.hpp"

namespace Compta
{

  
  Operation::Operation():
     _amount(0.),
     _margin(0.),
     _automatic(false),
     _period(1)
  {
    return;
  }

  
  Operation::Operation(const std::string &name, const float &amount, const float &margin,
                       const bool &automatic,
                       const Date &start, const Date &end,
                       const unsigned int &period):
        _name(name),
        _amount(amount),
        _margin(margin),
        _start_date(start),
        _end_date(end),
        _automatic(automatic),
        _period(period)
  {
    return;
  }

  
  Operation::Operation(const Operation &rhs)
  {
    *this = rhs;
  }
  
  
  Operation &Operation::operator=(const Operation &rhs)
  {
     if(this != &rhs)
     {
       this->set_operation(rhs.name(),rhs.amount() * (float)rhs.period(),rhs.margin() * (float)rhs.period(),
                           rhs.starting_date(),rhs.ending_date(),
                           rhs.automatic(),
                           rhs.period());
     }
     return *this;
  }

  
  Operation::~Operation()
  {
    return;
  }

  
  void Operation::set_operation(const std::string &name, const float &amount, const float &margin,
                                const Date &start, const Date &end,
                                const bool &automatic, const unsigned int &period)
  {
      _name = name;
      _amount = amount;
      _margin = margin;
      _start_date = start;
      _end_date = end;
      _automatic = automatic;
      _period = period;
  }

  
  void Operation::set_start_date(const Date &start_date)
  {
     _start_date = start_date;
  }

  
  void Operation::set_end_date(const Date &end_date)
  {
     _end_date = end_date;
  }

  
  void Operation::set_name(const std::string &name)
  {
     _name = name;
  }

  
  void Operation::set_amount(float &amount)
  {
     _amount = amount;
  }

  
  void Operation::set_margin(float &margin)
  {
     _margin = margin;
  }

  
  void Operation::set_automatic(bool &automatic)
  {
     _automatic = automatic;
  }

  
  void Operation::set_period(unsigned int &period)
  {
     _period = period;
  }

  
  const std::string Operation::name() const
  {
     return _name;
  }

  
  float Operation::amount() const
  {
     return _amount/(float)_period;
  }

  
  float Operation::margin() const
  {
     return _margin/(float)_period;
  }

  
  const Date Operation::starting_date() const
  {
     return _start_date;
  }

  
  const Date Operation::ending_date() const
  {
     return _end_date;
  }

  
  bool Operation::automatic() const
  {
     return _automatic;
  }

  
  unsigned int Operation::period() const
  {
     return _period;
  }

  
  float Operation::raw_amount() const
  {
     return _amount;
  }
  
  
  float Operation::raw_margin() const
  {
     return _margin;
  }

   
  bool Operation::happening_this_month(unsigned int &date) const
  {
    unsigned int a = std::floor(date/10000);
    unsigned int m = std::floor((date - a * 10000)/100);
    unsigned int distance = (_start_date.count_date() > date)?12 * (_start_date.year() - a) - m + _start_date.month():
                                                              12 * (a - _start_date.year()) + m - _start_date.month();
    unsigned int date_month_end   = a * 10000 + m * 100 + DateUtils::days_in_months(m,a);
    unsigned int date_month_start = a * 10000 + m * 100 + 1;

    return (distance%_period == 0)                        && 
           (date_month_end   >= _start_date.count_date()) &&
           (date_month_start <= _end_date.count_date());
  }

  
  void Operation::expected_operations(unsigned int &month, std::vector<Operation> &op) const
  {
    if(this->happening_this_month(month) && _automatic)op.push_back(*this); 
  }

  
  float Operation::amount_this_month(unsigned int &date)  const
  {
     return (this->happening_this_month(date))?_amount:0.L;
  }
  
  
  float Operation::margin_this_month(unsigned int &date)  const
  {
     return (this->happening_this_month(date))?_margin:0.L;
  }

  
  void Operation::print(std::ostream &out) const
  {
    out << _name       << ": " 
        << _amount     << " +/- " << _margin << " "
        << _start_date << " - "   << _end_date;
    if(_automatic)out <<  ", automatique tous les " << _period << " mois";
  }
}
