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

#ifndef COMPTA_OPTIONS_H
#define COMPTA_OPTIONS_H

//Compta
#include "compta/compta_asserts.hpp"
#include "compta/compta_version.hpp"
#include "compta/options_enum.hpp"
#include "compta/compta_obj.hpp"
#include "compta/latex_factory.hpp"

//C++
#include <iostream>
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

  ComptaOptions::~ComptaOptions()
  {
      return;
  }

  ComptaOptions::ComptaOptions(int argc, char **argv):
     _valid(true),
     _more(true)
  {
      this->build_map();
      for(int i = 1; i < argc; i++)
      {
          std::string argument(argv[i]);
          if(argument[0] == '-') // options
          {
             i = this->pass_options(i,argv);
          }else // file
          {
              if(_forecast_file.empty())
              {
                  _forecast_file = argument;
              }else if(_accounts_file.empty())
              {
                  _accounts_file = argument;
              }else if(_data_file.empty())
              {
                  _data_file = argument;
              }else if(_latex_file.empty())
              {
                  _latex_file = argument;
              }
          }
      }

      if(_forecast_file.empty() && _more)_valid = false;

      if(_accounts_file.empty())_accounts_file = _forecast_file;

      if(_data_file.empty())_data_file = _forecast_file;

      if(_latex_file.empty())_latex_file = _forecast_file + ".tex";

      return;
  }

  void ComptaOptions::build_map()
  {
      _options_map["--version"]      = VERSION;
      _options_map["-v"]             = VERSION;
      _options_map["--help"]         = HELP;
      _options_map["-h"]             = HELP;
      _options_map["--generate_tex"] = GENERATE_TEX;
      _options_map["-g"]             = GENERATE_TEX;
      _options_map["--compile_tex"]  = COMPILE_TEX;
      _options_map["-c"]             = COMPILE_TEX;
      _options_map["--forecast"]     = FORECAST_FILE;
      _options_map["--accounts"]     = ACCOUNTS_FILE;
      _options_map["--data"]         = DATA_FILE;
      _options_map["--latex"]        = LATEX_FILE;

      _options_value_map[GENERATE_TEX]  = true;
      _options_value_map[COMPILE_TEX]   = true;
  }

  bool ComptaOptions::valid() const
  {
      return _valid;
  }

  bool ComptaOptions::more() const
  {
      return _more;
  }

  const std::string ComptaOptions::forecast_file() const
  {
      return _forecast_file;
  }

  const std::string ComptaOptions::accounts_file() const
  {
      return _accounts_file;
  }

  const std::string ComptaOptions::data_file() const
  {
      return _data_file;
  }

  int ComptaOptions::pass_options(int pos, char **opts)
  {
      std::string keyword(opts[pos]);
      std::string value;
      if(!_options_map.count(keyword))compta_option_error(keyword);

      if((_options_map.count(keyword) != VERSION) && // value if not help nor version
         _options_map.count(keyword) != HELP)
      {
        if(std::string(opts[pos+1]) == "=")
        {
          pos += 2;
        }else
        {
          pos++;
        }
        value = std::string(opts[pos]);
      }

      this->process_option(_options_map.at(keyword),value);

      return pos;
  }

  void ComptaOptions::process_option(Options opt ,const std::string & value)
  {
     switch(opt)
     {
        case FORECAST_FILE:
        {
           _forecast_file = value;
           break;
        }
        case ACCOUNTS_FILE:
        {
           _accounts_file = value;
           break;
        }
        case DATA_FILE:
        {
           _data_file = value;
           break;
        }
        case LATEX_FILE:
        {
           _latex_file = value;
           if(_latex_file.find(".tex") != std::string::npos)_latex_file += ".tex";
           break;
        }
        case GENERATE_TEX:
        {
           bool gtex = (value == "yes");
           _options_value_map[GENERATE_TEX]  = gtex;
           break;
        }
        case COMPILE_TEX:
        {
           bool ctex = (value == "yes");
           _options_value_map[COMPILE_TEX]   = ctex;
           break;
        }
        case HELP:
        {
           compta_help_stdout();
           _more = false;
           _valid = true;
           break;
        }
        case VERSION:
        {
           compta_version_stdout();
           _more = false;
           _valid = true;
           break;
        }
     }
  }

  void ComptaOptions::report(ComptaObj & compte) const
  {
//on screen report
     std::cout << compte << std::endl;

//LaTeX report
     if(_options_value_map.at(GENERATE_TEX))
     {
        latex_report(compte,_latex_file);
     }
     if(_options_value_map.at(COMPILE_TEX))
     {
        const std::string commands("pdflatex --halt-on-error " + _latex_file + " > /dev/null");
        if(system(commands.c_str()))compta_LaTeX_error(commands); 
        if(system(commands.c_str()))compta_LaTeX_error(commands); 
        if(system(commands.c_str()))compta_LaTeX_error(commands); 
        if(system(commands.c_str()))compta_LaTeX_error(commands); 
     }

  }

  void ComptaOptions::unvalid_invocation(std::ostream & out, const std::string & prog) const
  {
    out << "Invalid invocation" << std::endl;
    out << "For help: " << prog << " --help" << std::endl 
                                             << std::endl;
    compta_error();
  }


}

#endif
