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

#ifndef COMPTA_CATEGORY_REPORT_H
#define COMPTA_CATEGORY_REPORT_H

//Compta
#include "compta/date.hpp"
#include "compta/posting.hpp"
#include "compta/forecast_container.hpp"
#include "compta/operation.hpp"

//C++
#include <string>

namespace Compta
{

  /*!\class CategoryReport
   * 
   * This class stores references to Posting s
   * and Operation s and compares the actual expenses with the
   * forecast threshold. It also takes into account Operation s that
   * are yet to pass.
   */
  class CategoryReport
  {
      public:
        //!default constructor
        CategoryReport();
        //!constructor
        CategoryReport(const Date & date, const ForecastContainer<Operation> &forcat); // = ForecastCategory
        //!copy constructor
        CategoryReport(const CategoryReport &rhs);
        //!destructor
        ~CategoryReport();

        //!initializes the object
        void initialize(const Date &date, const ForecastContainer<Operation> &forcat);

        //!adds a posting, update the infos
        void add_posting(const Posting &post);

        //! assignement operator
        CategoryReport &operator=(const CategoryReport &rhs);

        //!\return the name
        const std::string& name() const;
        //!\return the date
        const Date& date()        const;
        //!\return the forecast amount
        float forecast_amount()   const;
        //!\return the forecast margin
        float forecast_margin()   const;
        //!\return the amount
        float amount()            const;
        //!\return the expected amount
        float expected_amount()   const;

        //!\return Posting s
        const std::vector<Posting> &   done() const;
        //!\return Posting s
        const std::vector<Posting> &   not_done() const;
        //!\return Operation s
        const std::vector<Operation> & waiting() const;

        //!compares and report
        void report() const;

      private:
        std::string _name;
        Date  _date;
        float _forecast_amount;
        float _forecast_margin;
        float _amount;
        float _expected_amount;
        std::vector<Posting>   _done_this_month;
        std::vector<Posting>   _not_done_this_month;
        std::vector<Operation> _not_done_yet_this_month;

  };

  inline
  CategoryReport::CategoryReport():
    _date(DateUtils::tomonth()),
    _forecast_amount(-1.),
    _forecast_margin(-1.),
    _amount(0.),
    _expected_amount(0.)
  {
    return;
  }

  inline
  CategoryReport::CategoryReport(const Date &date, const ForecastContainer<Operation> &forecast_cat):
     _amount(0.),
     _expected_amount(0.)
  {
     this->initialize(date,forecast_cat);
  }

  inline
  CategoryReport::CategoryReport(const CategoryReport &rhs)
  {
     *this = rhs;
  }

  inline
  CategoryReport::~CategoryReport()
  {
     return;
  }

  inline
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

  inline
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

  inline
  const std::string &CategoryReport::name() const
  {
     return _name;
  }
  
  inline
  const Date & CategoryReport::date() const
  {
     return _date;
  }
  
  inline
  float CategoryReport::forecast_amount()   const
  {
     return _forecast_amount;
  }
  
  inline
  float CategoryReport::forecast_margin()   const
  {
     return _forecast_margin;
  }
  
  inline
  float CategoryReport::amount() const
  {
     return _amount;
  }
  
  inline
  float CategoryReport::expected_amount() const
  {
     return _expected_amount + _amount;
  }

  inline
  const std::vector<Posting> & CategoryReport::done() const
  {
     return _done_this_month;
  }

  inline
  const std::vector<Posting> & CategoryReport::not_done() const
  {
     return _not_done_this_month;
  }

  inline
  const std::vector<Operation> & CategoryReport::waiting() const
  {
     return _not_done_yet_this_month;
  }

  inline
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

#endif
