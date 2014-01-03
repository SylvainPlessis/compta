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
  // This class contains a name, an amount, a boolean for
  // the automatic state, and two dates, a starting date and
  // an ending date. In the case of an automated operation,
  // the starting date gives the expected day of payment.
  class Operation{
    public:
        Operation();
        Operation(const std::string &name, const float &amount,
                  const bool &automatic,
                  const Date &start = Date(DateUtils::date_min()), 
                  const Date &end   = Date(DateUtils::date_max()));
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
        //! sets the auto
        void set_automatic(bool &automatic);
        //! sets everything
        void set_operation(const std::string &name, const float &amount,
                           const Date &start, const Date &end,
                           const bool &automatic);

        //!\return the name
        const std::string name() const;
        //!\return the amount
        const float amount() const;
        //!\return the starting date
        const Date starting_date() const;
        //!\return the ending date
        const Date ending_date() const;
        //!\return the automatic
        const bool automatic() const;

        //!operator
        Operation &operator=(const Operation &rhs);

    private:
        std::string _name;
        float _amount;
        Date  _start_date;
        Date  _end_date;
        bool  _automatic;
  };

  inline
  Operation::Operation():
     _amount(0.),
     _automatic(false)
  {
    return;
  }

  inline
  Operation::Operation(const std::string &name, const float &amount,
                       const bool &automatic,
                       const Date &start, const Date &end):
        _name(name),
        _amount(amount),
        _start_date(start),
        _end_date(end),
        _automatic(automatic)
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
       this->set_operation(rhs.name(),rhs.amount(),
                           rhs.starting_date(),rhs.ending_date(),
                           rhs.automatic());
     }
     return *this;
  }

  inline
  Operation::~Operation()
  {
    return;
  }

  inline
  void Operation::set_operation(const std::string &name, const float &amount,
                                const Date &start, const Date &end,
                                const bool &automatic)
  {
      _name = name;
      _amount = amount;
      _start_date = start;
      _end_date = end;
      _automatic = automatic;
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
  void Operation::set_automatic(bool &automatic)
  {
     _automatic = automatic;
  }

  inline
  const std::string Operation::name() const
  {
     return _name;
  }

  inline
  const float Operation::amount() const
  {
     return _amount;
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
  const bool Operation::automatic() const
  {
     return _automatic;
  }

}
#endif
