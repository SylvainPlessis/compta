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

#ifndef COMPTA_HISTORY_H
#define COMPTA_HISTORY_H

//Compta
#include "compta/posting.hpp"
#include "compta/date_utils.hpp"

//C++
#include <iostream>
#include <vector>

namespace Compta{


  /*!\class History

       This class is basically a container for Posting.
       It stores the history of an account, and can
       give back any part of it between two dates, or
       of one particular month.
   */
  class History{
     public:
        History(float creation_amount = 0);
        History(const History &rhs);
        ~History();

        //! adds a line
        void add_posting(const Posting &post);
        //! prints the history
        void print(const Date & from, const Date &to, std::ostream& out = std::cout) const;

        //! Formatted print.
        friend std::ostream& operator << (std::ostream& os, const History &histoire)
        {
          histoire.print(Date(DateUtils::date_min()), Date(DateUtils::date_max()),os);
          return os;
        }

        //! \return the history
        const std::vector<Posting> history()    const;
        //! \return the expected posting
        const std::vector<Posting> in_waiting() const;

        //!\return the history of a specific month
        void history_of_month(const Date &month, std::vector<Posting> &out) const;

        //!\return the non passed operation of a specific month
        void in_waiting_of_month(const Date &month, std::vector<Posting> &out) const;

        //!\return the sub vector of Posting between dates
        void posting_between_dates(const Date &start, const Date &end, const std::vector<Posting> &storage, std::vector<Posting> &out) const;

        //!\return the first date (minus creation)
        const Date start_date() const;

        //!\return the last date
        const Date end_date() const;

        //! false if _history contains something
        bool done_empty() const;

        //! false if _in_waiting contains something
        bool expected_empty() const;

        //! false if contains something more than creation
        bool empty() const;

        //! \return the current state
        float current_state() const;
        //! \return the expected state
        float expected_state() const;

        //! \return the reference of the starting state
        const float & starting_state() const;

        //!operator
        History &operator=(const History &rhs);

     private:

        std::vector<Posting> _history;
        std::vector<Posting> _in_waiting;
        const float _starting_state;
        float _current_state;
        float _expected_state;
        Date today;
        std::vector<float> _monthly_state;
  };
  
}

#endif
