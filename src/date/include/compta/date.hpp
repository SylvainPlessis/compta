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

#ifndef COMPTA_DATE_H
#define COMPTA_DATE_H

//Compta
#include "compta/date_utils.hpp"
#include "compta/compta_asserts.hpp"

//C++
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

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

    //! Comparator
    Date &operator=(const Date &rhs);


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

 inline
 Date::Date():
     _day(0),
     _month(0),
     _year(0)
 {
   return;
 }

 inline
 Date::Date(unsigned int jour, unsigned int mois, unsigned int an)
 {
  this->set_date(jour,mois,an);
 }

 inline
 Date::Date(unsigned int date_int)
 {
  this->set_date(date_int);
 }

 inline
 Date::Date(const std::string &date_str)
 {
  this->set_date(date_str);
 }

 inline
 Date::Date(const Date &rhs)
 {
   *this = rhs;
 }

 inline
 void Date::set_date(std::string date_s)
 {
//dd/mm/yy or dd/mm/yyyy
    if(date_s.find("/") == std::string::npos)
         compta_date_error("Date \"" + date_s + "\" is badly defined, please use the notation dd/mm/yyyy or dd/mm/yy");
         
    date_s.replace(date_s.find("/"),1," "); //dd mm/yyyy

    if(date_s.find("/") == std::string::npos)
         compta_date_error("Date \"" + date_s + "\" is badly defined, please use the notation dd/mm/yyyy or dd/mm/yy");
         
    date_s.replace(date_s.find("/"),1," "); //dd mm yyyy
    if(date_s.find("/") != std::string::npos)
         compta_date_error("Date \"" + date_s + "\" is badly defined, please use the notation dd/mm/yyyy or dd/mm/yy");

    std::stringstream tmp(date_s);
    tmp >> _day >> _month >> _year;
 }

 inline
 void Date::set_date(unsigned int date_int)
 {
    unsigned int a = std::floor(date_int/10000);
    unsigned int m = std::floor((date_int - a * 10000)/100);
    unsigned int j = date_int - a * 10000 - m * 100;
    this->set_date(j,m,a);
 }

 inline
 void Date::set_date(unsigned int jour,unsigned int mois,unsigned int an)
 {
   _year  = an;
   _month = mois;
   _day   = jour;
//the order is important
   process_year();
   process_month();
   process_day();
 }

 inline
 const std::string Date::date_string() const
 {
   std::stringstream s;
   s << std::setfill('0') << std::setw(2)
     << _day << "/" << std::setfill('0') << std::setw(2)
     << _month << "/"
     << _year;
   return s.str();
 }

 inline
 void Date::process_day()
 {
   if(_day < 1)compta_date_error("Day is null or negative!");
   if(_day > DateUtils::days_in_months(_month,_year))compta_date_error("Day is greater than maximum number of day in this month!");
   return;
 }

 inline
 void Date::process_month()
 {
  if(_month < 1)compta_date_error("Month is null or negative!");
  if(_month > 12)compta_date_error("Month is greater than 12!");
  return;
 }

 inline
 void Date::process_year()
 {
  if(_year < 0)compta_date_error("Year is negative!");

  if(_year < 100)
  {
    time_t t = time(0);
    struct tm *now = localtime(&t);
    if(static_cast<int>(_year) <= (now->tm_year - 100))
    {
        _year += 2000;
    }else
    {
        _year += 1900;
    }
  }
  return;
 }

 inline
 unsigned int Date::count_date() const
 {
   return (_day + 100*_month + 10000*_year);
 }

 inline
 unsigned int Date::day()   const
 {
    return _day;
 }
 
 inline
 unsigned int Date::month() const
 {
    return _month;
 }
 
 inline
 unsigned int Date::year()  const
 {
    return _year;
 }

 inline
 bool Date::newer(const Date &rhs) const
 {
    return (*this >= rhs);
 }

 inline
 bool Date::older(const Date &rhs) const
 {
   return (*this <= rhs);
 }

 inline
 Date &Date::operator=(const Date &rhs)
 {
  if(this != &rhs)
  {
    _day = 0;
    _month = 0;
    _year = 0;
    if(rhs.count_date() != 0)this->set_date(rhs.count_date()); //if not a default
  }

  return *this;
 }

 inline
 bool Date::operator==(const std::string &rhs) const
 {
   return (*this == Date(rhs));
 }

 inline
 bool Date::operator==(unsigned int rhs) const
 {
   return (this->count_date() == rhs);
 }

 inline
 bool Date::operator==(const Date &rhs) const
 {
   return (this->count_date() == rhs.count_date());
 }

 template<typename CompType>
 inline
 bool Date::operator!=(const CompType &rhs) const
 {
   return !(*this == rhs);
 }

 inline
 bool Date::operator<=(const Date &rhs) const
 {
   return (this->count_date() <= rhs.count_date());
 }

 inline
 bool Date::operator<=(const std::string &rhs) const
 {
   return (*this <= Date(rhs));
 }

 inline
 bool Date::operator<=(unsigned int rhs) const
 {
   return (this->count_date() <= rhs);
 }

 inline
 bool Date::operator>=(const Date &rhs) const
 {
   return (this->count_date() >= rhs.count_date());
 }

 inline
 bool Date::operator>=(const std::string &rhs) const
 {
   return (*this >= Date(rhs));
 }

 inline
 bool Date::operator>=(unsigned int rhs) const
 {
   return (this->count_date() >= rhs);
 }

 template<typename CompType>
 inline
 bool Date::operator> (const CompType &rhs) const
 {
   return !(*this <= rhs);
 }

 template<typename CompType>
 inline
 bool Date::operator< (const CompType &rhs) const
 {
   return !(*this >= rhs);
 }

 inline
 void Date::print(std::ostream& out) const
 {
    out << this->date_string() ;
 }

 inline
 void Date::read(std::istream& in)
 {
    std::string date_str;
    in >> date_str;
    this->set_date(date_str);
 }


}
#endif
