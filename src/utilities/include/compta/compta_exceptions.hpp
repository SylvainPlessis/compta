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

#ifndef COMPTA_EXCEPTIONS_H
#define COMPTA_EXCEPTIONS_H

// C++
#include <stdexcept>
#include <string>

namespace Compta
{
  /*!
   * A class to represent the internal "this should never happen"
   * errors, to be thrown by "compta_error();"
   */
  class LogicError : public std::logic_error
  {
  public:
    LogicError() : std::logic_error( "Error in Compta internal logic" ) {}
  };

  /*!
   * A class to stub for features that should be in Compta, but
   * haven't been written yet, to be thrown by
   * "compta_not_implemented();"
   */
  class NotImplemented : public std::logic_error
  {
    public:
    NotImplemented() : std::logic_error( "Error: not implemented!" ) {}
  };
  
  /*!
   * A class representing a failed attempt by the library to open a
   * file (or construct an fstream, etc), to be thrown by
   * "compta_file_error(filename);" For ease of debugging, "filename"
   * should include any (absolute or relative or implicit) pathname
   * that was part of the failed open.
   */
  class FileError : public std::runtime_error
  {
  public:
    FileError(const std::string& filename) : std::runtime_error( "Error accessing file: " + filename ) {}
  };

  
  /*!
   * A class representing a date error
   */
  class DateError : public std::runtime_error
  {
  public:
    DateError(const std::string& description) : std::runtime_error( "Error while processing a date: " + description) {}
  };

  /*!
   * A class representing a bank error
   */
  class BankError : public std::runtime_error
  {
  public:
    BankError(const std::string& description) : std::runtime_error( "Error while processing a bank account: " + description) {}
  };

  /*!
   * A class representing a savings error
   */
  class SavingsError : public std::runtime_error
  {
  public:
    SavingsError(const std::string& description) : std::runtime_error( "Error while processing a savings account: " + description) {}
  };

  /*!
   * A class representing a reading error
   */
  class ReadError : public std::runtime_error
  {
  public:
    ReadError(const std::string& description) : std::runtime_error( "Error while processing an input file: " + description) {}
  };

  /*!
   * A class representing a money error
   */
  class MoneyError : public std::runtime_error
  {
  public:
    MoneyError(const std::string& description) : std::runtime_error( "Error in money: " + description) {}
  };


} // end namespace Compta

#define COMPTA_THROW(e) do { throw e; } while (0)

#endif // COMPTA_EXCEPTIONS_H
