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
#include "compta/options_enum.hpp"
#include "compta/compta_obj.hpp"

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

        void report(ComptaObj & compte) const;

        const std::string forecast_file() const;

        const std::string accounts_file() const;

        const std::string data_file() const;

        void unvalid_invocation(std::ostream & out, const std::string & prog) const;

      private:
        ComptaOptions();

        std::string _forecast_file;
        std::string _accounts_file;
        std::string _data_file;
        std::string _latex_file;

        bool _valid;
        bool _more;

        std::map<std::string,Options> _options_map;
        std::map<Options,bool>        _options_value_map;

        void build_map();

        int pass_options(int pos, char **opts);

        void process_option(Options opt ,const std::string & value);

  };

}

#endif
