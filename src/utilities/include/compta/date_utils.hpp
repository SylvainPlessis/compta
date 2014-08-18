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

#ifndef COMPTA_DATE_UTILS_H
#define COMPTA_DATE_UTILS_H

//compta
#include "compta/compta_asserts.hpp"
#include "compta/date.hpp"

//C++
#include <ctime>
#include <string>

namespace Compta{

 namespace DateUtils{

  //!\return the number of days in february given the year
  unsigned int february_days(unsigned int an);

  //\return the number of days given a month
  unsigned int days_in_months(unsigned int mois, unsigned int an);

  //\return the month's name
  std::string month_in_letter(unsigned int mois);

  //!\return the current date dd/mm/yyyy
  const Date today();
        
  //!\return the current date 01/mm/yyyy
  const Date tomonth();

  //!\return the current date 01/01/yyyy
  const Date toyear();

  //!No data before this date
  // 01/01/1900
  unsigned int date_min();

  //!No data after this date
  // 31/12/3000
  unsigned int date_max();

 } //end namespace DateUtils
} //end namespace Compta

#endif
