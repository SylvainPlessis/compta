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

#ifndef COMPTA_OPERATION_H
#define COMPTA_OPERATION_H

//Compta
#include "compta/date.hpp"

//C++
#include <string>
#include <vector>
#include <cmath>

namespace Compta{

  //!\class Operation
  // A class to store forecasted operations
  //
  // The forecasted operations are divided into
  // two categories, the automated ones and the
  // non automated ones.
  //
  // An automated operation will happen every month,
  // at a given date. A non automated will happen only
  // if a corresponding operation is found while reading
  // the data.
  //
  // An automated operation has a period and will therefore
  // be expected or not depending on the month asked: the
  // months where to expect an operation will be the
  // months such as 
  //
  //
  //
  // This class contains a name, an amount, a boolean for
  // the automatic state, and two dates, a starting date and
  // an ending date. In the case of an automated operation,
  // the starting date gives the expected day of payment.
  class Operation{
    public:
        Operation();
        Operation(const std::string &name, const float &amount, const float &margin,
                  const bool &automatic,
                  const Date &start = Date(DateUtils::date_min()), 
                  const Date &end   = Date(DateUtils::date_max()),
                  const unsigned int &period = 1);
        Operation(const Operation &rhs);
        ~Operation();

        //! sets the starting date
        void set_start_date(const Date &start_date);
        //! sets the ending date
        void set_end_date(const Date &end_date);
        //! sets the name
        void set_name(const std::string &name);
        //! sets the amount
        void set_amount(float &amount);
        //! sets the margin
        void set_margin(float &margin);
        //! sets the auto
        void set_automatic(bool &automatic);
        //! sets the period
        void set_period(unsigned int &period);
        //! sets everything
        void set_operation(const std::string &name, const float &amount, const float &margin,
                           const Date &start, const Date &end,
                           const bool &automatic, const unsigned int &period);

        //!\return the name
        const std::string name()   const;
        //!\return the amount
        float amount()             const;
        //!\return the margin
        float margin()             const;
        //!\return the starting date
        const Date starting_date() const;
        //!\return the ending date
        const Date ending_date()   const;
        //!\return the automatic
        bool automatic()           const;
        //!\return the period
        unsigned int period()      const;

        //!\return the amount if expected this month
        float amount_this_month(unsigned int &date)  const;
        //!\return the margin if expected this month
        float margin_this_month(unsigned int &date)  const;

        //!adds this to the vector if concerned
        //
        // The month is given in the form
        // year * 10000 + month * 100
        // as it is stripped down with std::floor operation
        // (anything below 100 is ignored)
        // the method unsigned int Date::count_date() const is
        // usable.
        void expected_operations(unsigned int &month, std::vector<Operation> &op) const;

        //!operator
        Operation &operator=(const Operation &rhs);

        //! prints the posting in human form
        void print(std::ostream& out = std::cout) const;

        //! Formatted print.
        friend std::ostream& operator << (std::ostream& os, const Operation &line)
        {
          line.print(os);
          return os;
        }

    private:

        bool happening_this_month(unsigned int &month) const;

        std::string _name;
        float _amount;
        float _margin;
        Date  _start_date;
        Date  _end_date;
        bool  _automatic;
        unsigned int _period;
  };

  inline
  Operation::Operation():
     _amount(0.),
     _margin(0.),
     _automatic(false),
     _period(1)
  {
    return;
  }

  inline
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

  inline
  Operation::Operation(const Operation &rhs)
  {
    *this = rhs;
  }
  
  inline
  Operation &Operation::operator=(const Operation &rhs)
  {
     if(this != &rhs)
     {
       this->set_operation(rhs.name(),rhs.amount(),rhs.margin(),
                           rhs.starting_date(),rhs.ending_date(),
                           rhs.automatic(),
                           rhs.period());
     }
     return *this;
  }

  inline
  Operation::~Operation()
  {
    return;
  }

  inline
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

  inline
  void Operation::set_start_date(const Date &start_date)
  {
     _start_date = start_date;
  }

  inline
  void Operation::set_end_date(const Date &end_date)
  {
     _end_date = end_date;
  }

  inline
  void Operation::set_name(const std::string &name)
  {
     _name = name;
  }

  inline
  void Operation::set_amount(float &amount)
  {
     _amount = amount;
  }

  inline
  void Operation::set_margin(float &margin)
  {
     _margin = margin;
  }

  inline
  void Operation::set_automatic(bool &automatic)
  {
     _automatic = automatic;
  }

  inline
  void Operation::set_period(unsigned int &period)
  {
     _period = period;
  }

  inline
  const std::string Operation::name() const
  {
     return _name;
  }

  inline
  float Operation::amount() const
  {
     return _amount;
  }

  inline
  float Operation::margin() const
  {
     return _margin;
  }

  inline
  const Date Operation::starting_date() const
  {
     return _start_date;
  }

  inline
  const Date Operation::ending_date() const
  {
     return _end_date;
  }

  inline
  bool Operation::automatic() const
  {
     return _automatic;
  }

  inline
  unsigned int Operation::period() const
  {
     return _period;
  }

  inline 
  bool Operation::happening_this_month(unsigned int &month) const
  {
    unsigned int a = std::floor(month/10000);
    unsigned int m = std::floor((month - a * 10000)/100);
    unsigned int distance = 12 * (a - _start_date.year()) + m - _start_date.month();
    return ((distance%_period == 0) && _automatic);
  }

  inline
  void Operation::expected_operations(unsigned int &month, std::vector<Operation> &op) const
  {
    if(this->happening_this_month(month))op.push_back(*this); 
  }

  inline
  float Operation::amount_this_month(unsigned int &date)  const
  {
     return (this->happening_this_month(date))?_amount:0.L;
  }
  
  inline
  float Operation::margin_this_month(unsigned int &date)  const
  {
     return (this->happening_this_month(date))?_margin:0.L;
  }

  inline
  void Operation::print(std::ostream &out) const
  {
    out << _name       << ": " 
        << _amount     << " +/- " << _margin << " "
        << _start_date << " - "   << _end_date;
    if(_automatic)out <<  ", automatique tous les " << _period << " mois" << std::endl;
   out << "." << std::endl;
  }
}
#endif
