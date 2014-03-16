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

#ifndef COMPTA_MONTHLY_REPORT_H
#define COMPTA_MONTHLY_REPORT_H

//compta
#include "compta/category_report.hpp"
#include "compta/forecast.hpp"

//C++
#include <vector>

namespace Compta
{
  /*!\class MonthlyReport
   *
   * This class stores pointers to
   * Posting s, as well as Operation s
   * that are to be expected. 
   * 
   * Everything is stored according to the
   * forecast structure, and compared to the
   * forecast numbers.
   */
  class MonthlyReport
  {
     public:
        //!default constructor
        MonthlyReport();
        //!constructor
        MonthlyReport(const Forecast &forecast);
        //!copy constructor
        MonthlyReport(const MonthlyReport &rhs);
        //!destructor
        ~MonthlyReport();

        //!add a line, update state
        void add_posting(const Posting &post);

        MonthlyReport &operator=(const MonthlyReport &rhs);        
     private:
        std::vector<CategoryReport> _report; 
  };



}
#endif
