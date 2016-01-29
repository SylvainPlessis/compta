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

#include "compta/history.hpp"

namespace Compta
{

  
  History::History(float creation_amount):
    _starting_state(creation_amount),
    _current_state(creation_amount),
    _expected_state(creation_amount)
  {
    today = DateUtils::today();
  }


  
  History::History(const History &rhs):
    _starting_state(rhs.starting_state())
  {
     today = DateUtils::today();
     *this = rhs;
     return;
  }

  
  History::~History()
  {
     return;
  }

  
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

  
  void History::print(const Date & from, const Date & to, std::ostream &out) const
  {

     for(unsigned int i = 0; i < _history.size(); i++)
     {
        if(_history[i].date() >= from &&
           _history[i].date() <= to)
                out << _history[i] << std::endl;
     }

     if(!_in_waiting.empty())
     {
       out << "\n# Pas encore pris en compte\n" << std::endl;

       for(unsigned int i = 0; i < _in_waiting.size(); i++)
       {
          out << _in_waiting[i] << std::endl;
       }
    }
  }

  
  const std::vector<Posting> History::history() const
  {
     return _history;
  }
  
  
  const std::vector<Posting> History::in_waiting() const
  {
     return _in_waiting;
  }
 
         
  const float & History::starting_state() const
  {
     return _starting_state;
  }

  
  float History::current_state() const
  {
     return _current_state;
  }

  
  float History::expected_state() const
  {
     return _expected_state;
  }

  
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

  
  void History::history_of_month(const Date &month, std::vector<Posting> &out) const
  {
     Date start(1,month.month(),month.year());
     Date end(DateUtils::days_in_months(month.month(),month.year()),month.month(),month.year());
     this->posting_between_dates(start,end,_history,out);
     return;
  }

  //keep track of all waiting stuff
  
  void History::in_waiting_of_month(const Date &month, std::vector<Posting> &out) const
  {
     Date start(this->start_date());
     Date end(DateUtils::days_in_months(month.month(),month.year()),month.month(),month.year());
     this->posting_between_dates(start,end,_in_waiting,out);
     return;
  }

  
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

  
  bool History::empty() const
  {
     return (_history.empty() && _in_waiting.empty());
  }

  bool History::done_empty() const
  {
     return _history.empty();
  }

  bool History::expected_empty() const
  {
     return _in_waiting.empty();
  }
}
