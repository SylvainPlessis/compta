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
        void print(std::ostream& out = std::cout) const;

        //! Formatted print.
        friend std::ostream& operator << (std::ostream& os, const History &histoire)
        {
          histoire.print(os);
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

  inline
  History::History(float creation_amount):
    _starting_state(creation_amount),
    _current_state(creation_amount),
    _expected_state(creation_amount)
  {
    today = DateUtils::today();
  }


  inline
  History::History(const History &rhs):
    _starting_state(rhs.starting_state())
  {
     today = DateUtils::today();
     *this = rhs;
     return;
  }

  inline
  History::~History()
  {
     return;
  }

  inline
  void History::add_posting(const Posting &post)
  {
     if(post.date() <= today && post.accounted())
     {
        unsigned int i;
        for(i = 0; i < _history.size(); i++)
        {
           if(_history[i].date() >= post.date())break;
        }
        _history.insert(_history.begin() + i,post);
        _current_state += post.amount();
     }else
     {
        if(post.accounted())
        {
          std::cerr << "In what universe can a not-yet-passed posting be accounted for?\n"
                    << "I will proceed, but you might want to look at this one:\n"
                    << post << std::endl;
        }
        unsigned int i;
        for(i = 0; i < _in_waiting.size(); i++)
        {
           if(_in_waiting[i].date() >= post.date())break;
        }
        _in_waiting.insert(_in_waiting.begin() + i,post);
     }
//whatever happens, it adds here
     _expected_state += post.amount();
  }

  inline
  void History::print(std::ostream &out) const
  {

     for(unsigned int i = 0; i < _history.size(); i++)
     {
        out << _history[i] << std::endl;
     }

     if(!_in_waiting.empty())
     {
       out << "# Pas encore pris en compte" << std::endl;

       for(unsigned int i = 0; i < _in_waiting.size(); i++)
       {
          out << _in_waiting[i] << std::endl;
       }
    }
  }

  inline
  const std::vector<Posting> History::history() const
  {
     return _history;
  }
  
  inline
  const std::vector<Posting> History::in_waiting() const
  {
     return _in_waiting;
  }
 
  inline       
  const float & History::starting_state() const
  {
     return _starting_state;
  }

  inline
  float History::current_state() const
  {
     return _current_state;
  }

  inline
  float History::expected_state() const
  {
     return _expected_state;
  }

  inline
  History &History::operator=(const History &rhs)
  {
    if(this != &rhs)
    {
       _history        = rhs.history();
       _in_waiting     = rhs.in_waiting();
       _current_state  = rhs.current_state();
       _expected_state = rhs.expected_state();
    }
    return *this;
  }

  inline
  void History::posting_between_dates(const Date &start, const Date &end, const std::vector<Posting> &storage, std::vector<Posting> &out) const
  {
//Posting are sorted by date
     out.clear();
     for(unsigned int ip = 0; ip < storage.size(); ip++)
     {
        if(storage[ip].date() < start)continue;
        if(storage[ip].date() > end)break;
        out.push_back(storage[ip]);
     }

     return;
  }

  inline
  void History::history_of_month(const Date &month, std::vector<Posting> &out) const
  {
     Date start(1,month.month(),month.year());
     Date end(DateUtils::days_in_months(month.month(),month.year()),month.month(),month.year());
     this->posting_between_dates(start,end,_history,out);
     return;
  }

  //keep track of all waiting stuff
  inline
  void History::in_waiting_of_month(const Date &month, std::vector<Posting> &out) const
  {
     Date start(this->start_date());
     Date end(DateUtils::days_in_months(month.month(),month.year()),month.month(),month.year());
     this->posting_between_dates(start,end,_in_waiting,out);
     return;
  }

  inline
  const Date History::start_date() const
  {
 //    if(_history.empty())compta_error();

     Date out_date(DateUtils::date_min());

     if(!_history.empty() && !_in_waiting.empty())
     {
        out_date = (_history.front().date() < _in_waiting.front().date())?_history.front().date():_in_waiting.front().date();
     }else if(!_history.empty())
     {
        out_date = _history.front().date();
     }else if(!_in_waiting.empty())
     {
        out_date = _in_waiting.front().date();
     }

     return out_date;
  }

  inline
  const Date History::end_date() const
  {
//     if(_history.empty())compta_error();

     Date out_date(DateUtils::date_min());

     if(!_history.empty() && !_in_waiting.empty())
     {
        out_date = (_history.back().date() > _in_waiting.back().date())?_history.back().date():_in_waiting.back().date();
     }else if(!_history.empty())
     {
        out_date = _history.back().date();
     }else if(!_in_waiting.empty())
     {
        out_date = _in_waiting.back().date();
     }

     return out_date;

  }

  inline
  bool History::empty() const
  {
     return (_history.empty() && _in_waiting.empty());
  }

  
}

#endif
