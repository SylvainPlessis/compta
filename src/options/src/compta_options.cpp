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

//Compta
#include "compta/compta_asserts.hpp"
#include "compta/compta_version.hpp"
#include "compta/latex_factory.hpp"
#include "compta/compta_options.hpp"
#include "compta/compta_help.hpp"

//C++

namespace Compta
{

  ComptaOptions::~ComptaOptions()
  {
      return;
  }

  ComptaOptions::ComptaOptions(int argc, char **argv):
     _print_choice(ALL),
     _valid(true),
     _more(true)
  {
      this->build_maps();
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

      if(_forecast_file.empty() && _more)
      {
         std::cerr << "\nPlease provide at least one file name" << std::endl;
         _valid = false;
      }

      if(_accounts_file.empty())_accounts_file = _forecast_file;

      if(_data_file.empty())_data_file = _forecast_file;

      if(_latex_file.empty())_latex_file = _forecast_file + ".tex";

      return;
  }

  void ComptaOptions::build_maps()
  {
      _options_map["--version"]        = VERSION;
      _options_map["-v"]               = VERSION;
      _options_map["--help"]           = HELP;
      _options_map["-h"]               = HELP;
      _options_map["--generate-latex"] = GENERATE_TEX;
      _options_map["-g"]               = GENERATE_TEX;
      _options_map["--compile-latex"]  = COMPILE_TEX;
      _options_map["-c"]               = COMPILE_TEX;
      _options_map["--forecast"]       = FORECAST_FILE;
      _options_map["--accounts"]       = ACCOUNTS_FILE;
      _options_map["--data"]           = DATA_FILE;
      _options_map["--latex"]          = LATEX_FILE;
      _options_map["--print-all"]      = PRINT_ALL;
      _options_map["--print-forecast"] = PRINT_FORECAST;
      _options_map["--print-bank"]     = PRINT_BANK;
      _options_map["--print-cash"]     = PRINT_CASH;

      _options_value_map[GENERATE_TEX]  = true;
      _options_value_map[COMPILE_TEX]   = true;

      _options_files_map[FORECAST_FILE] = &_forecast_file;
      _options_files_map[DATA_FILE]     = &_data_file;
      _options_files_map[LATEX_FILE]    = &_latex_file;
      _options_files_map[ACCOUNTS_FILE] = &_accounts_file;

      _options_print_map[PRINT_ALL]      = ALL;
      _options_print_map[PRINT_FORECAST] = FORECAST;
      _options_print_map[PRINT_BANK]     = BANK;
      _options_print_map[PRINT_CASH]     = CASH;
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
      if(keyword.find('=') != std::string::npos)
      {
        value = keyword.substr(keyword.find('=') + 1, std::string::npos);
        keyword = keyword.substr(0,keyword.find('='));
      }
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
// file options
        case FORECAST_FILE:
        case ACCOUNTS_FILE:
        case DATA_FILE:
        case LATEX_FILE:
        {
          this->manage_file(opt,value);
        }
// LaTeX related options
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
// print options
        case PRINT_ALL:
        case PRINT_FORECAST:
        case PRINT_BANK:
        case PRINT_CASH:
        {
           this->manage_print(opt);
           break;
        }
// help and version
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
     compte.report(_print_choice);

//LaTeX report
     if(_options_value_map.at(GENERATE_TEX))
     {
        latex_report(compte,_latex_file);
       if(_options_value_map.at(COMPILE_TEX))
       {
          const std::string commands("pdflatex --halt-on-error " + _latex_file + " > /dev/null");
          if(!system(NULL))compta_LaTeX_error("Failed to find preprocessor"); 
          std::cout << "Compiling using pdflatex, please wait" << std::endl;
          if(system(commands.c_str()))compta_LaTeX_error(commands); 
          std::cout << "Compiling using pdflatex, please wait" << std::endl;
          if(system(commands.c_str()))compta_LaTeX_error(commands); 
          std::cout << "Compiling using pdflatex, please wait" << std::endl;
          if(system(commands.c_str()))compta_LaTeX_error(commands); 
          std::cout << "Compiling using pdflatex, please wait" << std::endl;
          if(system(commands.c_str()))compta_LaTeX_error(commands); 
          std::cout << "Compilation ended" << std::endl;
       }
     }

  }

  void ComptaOptions::manage_file(Options opt, const std::string& value)
  {
     *(_options_files_map.at(opt)) = value;
     if(!_latex_file.empty() && _latex_file.find(".tex") != std::string::npos)_latex_file += ".tex";
     return;
  }

  void ComptaOptions::manage_print(Options opt)
  {
     _print_choice = _options_print_map.at(opt);
     return;
  }

  void ComptaOptions::unvalid_invocation(std::ostream & out, const std::string & prog) const
  {
    for(unsigned int i=0;i<50;i++)out << "*";
    out << std::endl << std::endl;
    out << "Invalid invocation" << std::endl;
    out << "Minimum invocation is:\n\t" << prog << " *file_name*" << std::endl << std::endl;
    out << "For help: " << prog << " --help" << std::endl;
    out << std::endl;
    for(unsigned int i=0;i<50;i++)out << "*";
    out << std::endl;
    compta_error();
  }

}
