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


  //!No data before this date
  // 01/01/1900
  inline
  unsigned int date_min()
  {
     return (1 + 1*100 + 1900*10000);
  }

  //!No data after this date
  // 31/12/3000
  inline
  unsigned int date_max()
  {
     return (31 + 12*100 + 3000*10000);
  }

  inline
  unsigned int days_in_months(unsigned int mois, unsigned int an)
  {
    switch(mois)
    {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
        return 31;
        break;
      case 2:
        return february_days(an);
        break;
    }
    return 30;
  }

  inline
  unsigned int february_days(unsigned int an)
  {
    time_t t = time(0);
    struct tm *now = localtime(&t);
    unsigned int cur_year = 1900 + now->tm_year;

    if((cur_year%4 == 0 && cur_year%100 != 0) || (cur_year%400 == 0))return 29;

    return 28;
  }

  inline
  std::string month_in_letter(unsigned int mois)
  {
     switch(mois)
     {
      case 1:
        return "Janvier";
        break;
      case 2:
        return "Février";
        break;
      case 3:
        return "Mars";
        break;
      case 4:
        return "Avril";
        break;
      case 5:
        return "Mai";
        break;
      case 6:
        return "Juin";
        break;
      case 7:
        return "Juillet";
        break;
      case 8:
        return "Août";
        break;
      case 9:
        return "Septembre";
        break;
      case 10:
        return "Octobre";
        break;
      case 11:
        return "Novembre";
        break;
      case 12:
        return "Décembre";
        break;
      default:
        compta_error();
        break;
     }
  }


 } //end namespace DateUtils
} //end namespace Compta

#endif
