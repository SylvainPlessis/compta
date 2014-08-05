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

#ifndef COMPTA_DATE_H
#define COMPTA_DATE_H

//Compta
#include "compta/compta_asserts.hpp"

//C++
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <ctime>

namespace Compta{


 /*!\class Date

      This class deals with the different needed form
      of a date: three integers, a string or one integer.
      The three integers are year, month and day, the string
      is of the european form dd/mm/yyyy and the integer
      form is year * 10000 + month * 100 + day.
  */
 class Date{ 
  public:
    //! default constructor
    Date();
    //! Copy constructor
     Date(const Date &rhs);
    //! Constructor with three unsigned int
    Date(unsigned int jour, 
         unsigned int mois, 
         unsigned int an);
    //! Constructor with one unsigned int
     Date(unsigned int int_date);
    //! Constructor with a string
     Date(const std::string &date_str);
    //! Destructor
    ~Date(){}

    //! Sets the date with three unsigned int
    void set_date(unsigned int jour,unsigned int mois,unsigned int an);
    //! Sets the date with a string
    void set_date(std::string date_str);
    //! Sets the date with one unsigned int
    void set_date(unsigned int sum_date);

    //! \return the day
    unsigned int day()   const;
    //! \return the month
    unsigned int month() const;
    //! \return the year
    unsigned int year()  const;

    //! \return the date in string format
    const std::string date_string() const;

    //! \return the day in integer format (d + 100 * m + 10000 * y = yyyymmdd)
    unsigned int count_date()    const;

    //! Comparator
    bool newer(const Date &rhs) const;
    //! Comparator
    bool older(const Date &rhs) const;

    //! Assignement operator
    Date &operator=(const Date &rhs);
    //! Assignement operator
    Date &operator=(unsigned int &date);


/* fully expanded comparators
 *
 */
    //! Comparator
    bool operator==(const Date &rhs) const;
    //! Comparator
    bool operator==(const std::string &rhs) const;
    //! Comparator
    bool operator==(unsigned int rhs) const;

    //! Comparator
    bool operator<=(const Date &rhs) const;
    //! Comparator
    bool operator<=(const std::string &rhs) const;
    //! Comparator
    bool operator<=(unsigned int rhs) const;

    //! Comparator
    bool operator>=(const Date &rhs) const;
    //! Comparator
    bool operator>=(const std::string &rhs) const;
    //! Comparator
    bool operator>=(unsigned int rhs) const;


/* templated comparator, defined with respect
 * to another
 *
 */
    //! Comparator
    template<typename CompType>
    bool operator!=(const CompType &rhs) const;
    //! Comparator
    template<typename CompType>
    bool operator> (const CompType &rhs) const;
    //! Comparator
    template<typename CompType>
    bool operator< (const CompType &rhs) const;

    //! prints the date
    void print(std::ostream& out = std::cout) const;

    //! Formatted print.
    friend std::ostream& operator << (std::ostream& os, const Date &date)
    {
      date.print(os);
      return os;
    }

    //! reads the date
    void read(std::istream& in = std::cin);

    //! Formatted reading
    friend std::istream& operator >> (std::istream& is, Date &date)
    {
      date.read(is);
      return is;
    }

  private:
    //!
    void process_day();
    //!
    void process_month();
    //!
    void process_year();

    unsigned int _day;
    unsigned int _month;
    unsigned int _year;
 };

 template<typename CompType>
 bool Date::operator!=(const CompType &rhs) const
 {
   return !(*this == rhs);
 }

 template<typename CompType>
 bool Date::operator> (const CompType &rhs) const
 {
   return !(*this <= rhs);
 }

 template<typename CompType>
 bool Date::operator< (const CompType &rhs) const
 {
   return !(*this >= rhs);
 }

}
#endif
