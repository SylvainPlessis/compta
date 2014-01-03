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

#ifndef COMPTA_HISTORY_H
#define COMPTA_HISTORY_H

//Compta
#include "compta/posting.hpp"

//C++
#include <iostream>
#include <vector>
#include <ctime>

namespace Compta{

  class History{
     public:
        History();
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

        //! \return the current state
        const float current_state() const;
        //! \return the expected state
        const float expected_state() const;

        //!operator
        History &operator=(const History &rhs);

     private:
        std::vector<Posting> _history;
        std::vector<Posting> _in_waiting;
        float _current_state;
        float _expected_state;
        Date today;
        std::vector<float> _monthly_state;
  };

  inline
  History::History():
    _current_state(0.),
    _expected_state(0.)
  {
    time_t t = time(0);
    struct tm *now = localtime(&t);
    today.set_date(now->tm_mday, now->tm_mon + 1, 1900 + now->tm_year);
  }


  inline
  History::History(const History &rhs)
  {
     time_t t = time(0);
     struct tm *now = localtime(&t);
     today.set_date(now->tm_mday, now->tm_mon + 1, 1900 + now->tm_year);
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
  const float History::current_state() const
  {
     return _current_state;
  }

  inline
  const float History::expected_state() const
  {
     return _expected_state;
  }

  inline
  History &History::operator=(const History &rhs)
  {
    if(this != &rhs)
    {
       _history = rhs.history();
       _in_waiting = rhs.in_waiting();
       _current_state = rhs.current_state();
       _expected_state = rhs.expected_state();
    }
    return *this;
  }
  
}

#endif
