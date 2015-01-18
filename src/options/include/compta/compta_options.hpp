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

#ifndef COMPTA_OPTIONS_H
#define COMPTA_OPTIONS_H

//Compta
#include "compta/compta_obj.hpp"
#include "compta/options_enum.hpp"

//C++
#include <iostream>
#include <string>
#include <map>

namespace Compta{

  class ComptaOptions
  {
      public:
        ComptaOptions(int argc, char **argv);
        ~ComptaOptions();

        bool valid() const;

        bool more() const;

        void report(const ComptaObj & compte) const;

        const std::string forecast_file() const;

        const std::string accounts_file() const;

        const std::string data_file() const;

        const Date from_stdout() const;

        const Date to_stdout() const;

        const Date from_file() const;

        const Date to_file() const;

        void unvalid_invocation(std::ostream & out, const std::string & prog) const;

      private:
        ComptaOptions();

       // GENERAL
       // READ
        std::string _forecast_file;
        std::string _accounts_file;
        std::string _data_file;
       // PRINT
        bool _print;
        bool _print_forecast;
        bool _print_bank;
        bool _print_cash;
        Date _from_stdout;
        Date _to_stdout;
       // WRITE
        bool        _write_tex;
        bool        _compile_tex;
        std::string _latex_file;
        Date        _from_file;
        Date        _to_file;

        bool _valid;
        bool _more;

       // GENERAL
        std::map<std::string, GENERAL::Options > _general_options_map;
       // READ
        std::map<std::string, READ::Options >    _read_options_map;
       // PRINT
        std::map<std::string, PRINT::Options >   _print_options_map;
       // WRITE
        std::map<std::string, WRITE::Options >   _write_options_map;

        void build_maps();

        // GENERAL
         void general_options(const std::string & keyword);
        // READ
         void read_options   (const std::string & keyword, const std::string & value);
        // PRINT
         void print_options  (const std::string & keyword, const std::string & value);
        // WRITE
         void write_options  (const std::string & keyword, const std::string & value);
        // manage options
         void pass_options(int pos, char **opts);

  };

}

#endif
