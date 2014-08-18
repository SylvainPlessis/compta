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
}

#endif
