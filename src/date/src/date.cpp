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

#include "compta/date.hpp"
#include "compta/date_utils.hpp"

namespace Compta
{

 
 Date::Date():
     _day(0),
     _month(0),
     _year(0)
 {
   return;
 }

 
 Date::Date(unsigned int jour, unsigned int mois, unsigned int an):
     _day(0),
     _month(0),
     _year(0)
 {
  this->set_date(jour,mois,an);
 }

 
 Date::Date(unsigned int date_int):
     _day(0),
     _month(0),
     _year(0)
 {
  this->set_date(date_int);
 }

 
 Date::Date(const std::string &date_str):
     _day(0),
     _month(0),
     _year(0)
 {
  this->set_date(date_str);
 }

 
 Date::Date(const Date &rhs):
     _day(0),
     _month(0),
     _year(0)
 {
   *this = rhs;
 }

 
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

 
 void Date::set_date(unsigned int date_int)
 {
    unsigned int a = std::floor(date_int/10000);
    unsigned int m = std::floor((date_int - a * 10000)/100);
    unsigned int j = date_int - a * 10000 - m * 100;
    this->set_date(j,m,a);
 }

 
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

 
 const std::string Date::date_string() const
 {
   std::stringstream s;
   if(this->count_date() == DateUtils::date_min() ||
      this->count_date() == DateUtils::date_max())
   {
    s << "."; 
   }else
   {
    s << std::setfill('0') << std::setw(2)
      << _day << "/" 
      << std::setfill('0') << std::setw(2)
      << _month << "/"
      << _year;
   }
   return s.str();
 }

 
 void Date::process_day()
 {
   if(_day < 1)compta_date_error("Day is null or negative!");
   if(_day > DateUtils::days_in_months(_month,_year))compta_date_error("Day is greater than maximum number of day in this month!");
   return;
 }

 
 void Date::process_month()
 {
  if(_month < 1)
    compta_date_error("Month is null or negative!");
  if(_month > 12)
    compta_date_error("Month is greater than 12!");
  return;
 }

 
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

 
 unsigned int Date::count_date() const
 {
   return (_day + 100*_month + 10000*_year);
 }

 
 unsigned int Date::day()   const
 {
    return _day;
 }
 
 
 unsigned int Date::month() const
 {
    return _month;
 }
 
 
 unsigned int Date::year()  const
 {
    return _year;
 }

 
 bool Date::newer(const Date &rhs) const
 {
    return (*this >= rhs);
 }

 
 bool Date::older(const Date &rhs) const
 {
   return (*this <= rhs);
 }

 
 Date &Date::operator=(unsigned int &date_int)
 {
  this->set_date(date_int);
  return *this;
 }

 
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

 
 bool Date::operator==(const std::string &rhs) const
 {
   return (*this == Date(rhs));
 }

 
 bool Date::operator==(unsigned int rhs) const
 {
   return (this->count_date() == rhs);
 }

 
 bool Date::operator==(const Date &rhs) const
 {
   return (this->count_date() == rhs.count_date());
 }


 bool Date::operator<=(const Date &rhs) const
 {
   return (this->count_date() <= rhs.count_date());
 }

 
 bool Date::operator<=(const std::string &rhs) const
 {
   return (*this <= Date(rhs));
 }

 
 bool Date::operator<=(unsigned int rhs) const
 {
   return (this->count_date() <= rhs);
 }

 
 bool Date::operator>=(const Date &rhs) const
 {
   return (this->count_date() >= rhs.count_date());
 }

 
 bool Date::operator>=(const std::string &rhs) const
 {
   return (*this >= Date(rhs));
 }

 
 bool Date::operator>=(unsigned int rhs) const
 {
   return (this->count_date() >= rhs);
 }
 
 void Date::print(std::ostream& out) const
 {
    out << this->date_string() ;
 }

 
 void Date::read(std::istream& in)
 {
    std::string date_str;
    in >> date_str;
    this->set_date(date_str);
 }
}
