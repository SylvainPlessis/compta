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

#ifndef COMPTA_ASSERTS_H
#define COMPTA_ASSERTS_H

// Compta
#include "compta/compta_exceptions.hpp"

// C++
#include <iostream>
#include <iomanip>

#define compta_here()     do { std::cerr << "\ntrace is:\n\t" << __FILE__ << ", line " << __LINE__ << ", compiled " << __DATE__ << " at " << __TIME__ << std::endl; } while (0)

//!\file compta_asserts.hpp
//
//All in here is taken from Antioch standards

// The compta_assert() macro acts like C's assert(), but throws a
// compta_error() (including stack trace, etc) instead of just exiting

#define compta_error()                     do { compta_here(); COMPTA_THROW(Compta::LogicError()); }                   while(0)
#define compta_not_implemented()           do { compta_here(); COMPTA_THROW(Compta::NotImplemented()); }               while(0)
#define compta_file_error(filename)        do { compta_here(); COMPTA_THROW(Compta::FileError(filename)); }            while(0)
#define compta_date_error(description)     do { compta_here(); COMPTA_THROW(Compta::DateError(description)); }         while(0)
#define compta_bank_error(description)     do { compta_here(); COMPTA_THROW(Compta::BankError(description)); }         while(0)
#define compta_savings_error(description)  do { compta_here(); COMPTA_THROW(Compta::SavingsError(description)); }      while(0)
#define compta_money_error(description)    do { compta_here(); COMPTA_THROW(Compta::MoneyError(description)); }        while(0)
#define compta_reading_error(description)  do { compta_here(); COMPTA_THROW(Compta::ReadError(description)); }         while(0)
#define compta_forecast_error(description) do { compta_here(); COMPTA_THROW(Compta::ForecastError(description)); }     while(0)
#define compta_report_error(description)   do { compta_here(); COMPTA_THROW(Compta::ReportError(description)); }       while(0)
#define compta_option_error(description)   do { compta_here(); COMPTA_THROW(Compta::OptionError(description)); }       while(0)
#define compta_LaTeX_error(description)    do { compta_here(); COMPTA_THROW(Compta::CompileLaTeXError(description)); } while(0)
// The compta_deprecated macro warns that you are using obsoleted code,
// savagely copy/pasted from libmesh
#define compta_deprecated() \
          do  {std::cerr << "\n*** Warning, This code is deprecated, and likely to be removed in future library versions!\n" \
                         << __FILE__ << ", line " << __LINE__ << ", compiled " << __DATE__ << " at " << __TIME__ << " ***" << std::endl;} while(0)

#endif // COMPTA_ASSERTS_H
