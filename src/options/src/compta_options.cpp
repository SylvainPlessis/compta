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
#include <algorithm> //tolower

namespace Compta
{

  ComptaOptions::~ComptaOptions()
  {
      return;
  }


/*
  - 1 : GENERAL
  - 2 : READ
  - 3 : PRINT
  - 4 : WRITE
*/
  ComptaOptions::ComptaOptions(int argc, char **argv):
     _print_forecast(false),
     _print_bank(false),
     _print_cash(false),
     _from_stdout(DateUtils::date_min()),
     _to_stdout(DateUtils::date_max()),
     _write_tex(true),
     _compile_tex(true),
     _from_file(DateUtils::date_min()),
     _to_file(DateUtils::date_max()),
     _valid(true),
     _more(true),
     YES("yes"),
     NO("no")
  {
      this->build_maps();
      for(int i = 1; i < argc; i++)
      {
        if(argv[i][0] == '-')
        {
          this->pass_options(i,argv,argc-1);
        }else // providing names is implicit
        {
           if(_forecast_file.empty())
           {
              _forecast_file = std::string(argv[i]);
           }else if(_accounts_file.empty())
           {
              _accounts_file = std::string(argv[i]);
           }else if(_data_file.empty())
           {
              _data_file = std::string(argv[i]);
           }else if(_latex_file.empty())
           {
              _latex_file = std::string(argv[i]);
           }else
           {
             _valid=false;
           }
        }
      }

      if(_forecast_file.empty() && _more)
      {
         std::cerr << "\nPlease provide at least one file name" << std::endl;
         _valid = false;
      }

      if(_accounts_file.empty())_accounts_file = _forecast_file;

      if(_data_file.empty())    _data_file     = _forecast_file;

      if(_latex_file.empty())   _latex_file    = _forecast_file + ".tex";

      return;
  }

  void ComptaOptions::build_maps()
  {
     // GENERAL
      _general_options_map["--version"] = GENERAL::VERSION;
      _general_options_map["-v"]        = GENERAL::VERSION;
      _general_options_map["--help"]    = GENERAL::HELP;
      _general_options_map["-h"]        = GENERAL::HELP;

     // READ
      _read_options_map["--forecast"]   = READ::FORECAST;
      _read_options_map["--accounts"]   = READ::ACCOUNTS;
      _read_options_map["--data"]       = READ::DATA;

     // PRINT
      _print_options_map["--print"]          = PRINT::ALL;
      _print_options_map["--print-forecast"] = PRINT::FORECAST;
      _print_options_map["--print-bank"]     = PRINT::BANK;
      _print_options_map["--print-cash"]     = PRINT::CASH;
      _print_options_map["--print-from"]     = PRINT::FROM;
      _print_options_map["--print-to"]       = PRINT::TO;

     // WRITE
      _write_options_map["--write"]          = WRITE::LATEX;
      _write_options_map["--generate-latex"] = WRITE::GENERATE_TEX;
      _write_options_map["-g"]               = WRITE::GENERATE_TEX;
      _write_options_map["--compile-latex"]  = WRITE::COMPILE_TEX;
      _write_options_map["-c"]               = WRITE::COMPILE_TEX;
      _write_options_map["--write-from"]     = WRITE::FROM;
      _write_options_map["--write-to"]       = WRITE::TO;

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

  const Date ComptaOptions::from_stdout() const
  {
      return _from_stdout;
  }

  const Date ComptaOptions::to_stdout() const
  {
      return _to_stdout;
  }

  const Date ComptaOptions::from_file() const
  {
      return _from_file;
  }

  const Date ComptaOptions::to_file() const
  {
      return _to_file;
  }

  void ComptaOptions::pass_options(int pos, char **opts, int maxarg)
  {
      std::string keyword(opts[pos]);
      std::string value;
      if(keyword.find('=') != std::string::npos)
      {
         value = keyword.substr(keyword.find('=') + 1, std::string::npos);
         keyword = keyword.substr(0,keyword.find('='));
      }else if(pos < maxarg)
      {
        if(std::string(opts[pos+1]).find('=') != std::string::npos)
        {
           if(std::string(opts[pos+1]).size() == 1)
           {
             if(pos+2 >= maxarg)compta_option_error("Missing value to option " + keyword);
             value = std::string(opts[pos+2]);
           }else
           {
            value = std::string(opts[pos+1]).substr(1,std::string::npos);
           }
        }
      }
        // GENERAL
      if(_general_options_map.count(keyword))
      {
         this->general_options(keyword); // general and get out
        // READ
      }else if(_read_options_map.count(keyword))
      {
         this->read_options(keyword,value);
        // PRINT
      }else if(_print_options_map.count(keyword))
      {
         this->print_options(keyword,value);
        // WRITE
      }else if(_write_options_map.count(keyword))
      {
         this->write_options(keyword,value);
      }else
      {
         compta_option_error("Unrecognized option: " + keyword);
      }

  }

  void ComptaOptions::general_options(const std::string &keyword)
  {
     compta_assert(_general_options_map.count(keyword));
// help and version
     switch(_general_options_map.at(keyword))
     {
        case GENERAL::HELP:
        {
           compta_help_stdout();
           _more = false;
           _valid = true;
           break;
        }
        case GENERAL::VERSION:
        {
           compta_version_stdout();
           _more = false;
           _valid = true;
           break;
        }
        default: //WTF???
        {
          compta_error();
        }
     }
  }

  void ComptaOptions::read_options(const std::string & keyword, const std::string & value)
  {
        compta_assert(_read_options_map.count(keyword));
// file options
     switch(_read_options_map.at(keyword))
     {
        case READ::FORECAST:
        {
            _forecast_file = value;
            break;
        }
        case READ::ACCOUNTS:
        {
            _accounts_file = value;
            break;
        }
        case READ::DATA:
        {
            _data_file = value;
            break;
        }
        default: //WTF???
        {
          compta_error();
        }
     }
  }

  void ComptaOptions::print_options(const std::string & keyword, const std::string & value)
  {
     compta_assert(_print_options_map.count(keyword));

     switch(_print_options_map.at(keyword))
     {
        case PRINT::ALL:
        {
          std::string lvalue(value);
          std::transform(lvalue.begin(),lvalue.end(),lvalue.begin(),::tolower);
          if(lvalue == NO)
          {
             _print_forecast = false;
             _print_bank = false;
             _print_cash = false;
          }else if(lvalue == YES)
          {
             _print_forecast = true;
             _print_bank = true;
             _print_cash = true;
          }else
          {
              compta_option_error("Unrecognized value for option --print: " + value + "\nPlease use \"" + YES + "\" or \"" + NO + "\"");
          }
           break;
        }
        case PRINT::FORECAST:
        {
           _print_forecast = true;
           break;
        }
        case PRINT::BANK:
        {
           _print_bank = true;
           break;
        }
        case PRINT::CASH:
        {
           _print_cash = true;
           break;
        }
        case PRINT::FROM:
        {
           _from_stdout.set_date(value);
           break;
        }
        case PRINT::TO:
        {
           _to_stdout.set_date(value);
           break;
        }
        default: //WTF???
        {
          compta_error();
        }
     }
  }
 
  void ComptaOptions::write_options(const std::string & keyword, const std::string & value)
  {
     compta_assert(_write_options_map.count(keyword));

     switch(_write_options_map.at(keyword))
     {
        case WRITE::GENERATE_TEX:
        {
         if(value.empty()) // -g
         {
            _write_tex = true;
         }else // --generate-tex = yes/no
         {
           std::string lvalue(value);
           std::transform(lvalue.begin(),lvalue.end(),lvalue.begin(),::tolower);
           _write_tex = (lvalue == YES)?true:false;
           if(!_write_tex && lvalue != NO)compta_option_error("Please give yes or no to this option: " + keyword);
         }
          break;
        }
        case WRITE::COMPILE_TEX:
        {
         if(value.empty()) // -c
         {
            _compile_tex = true;
         }else // --compile-tex = yes/no
         {
           std::string lvalue(value);
           std::transform(lvalue.begin(),lvalue.end(),lvalue.begin(),::tolower);
           _compile_tex = (lvalue == YES)?true:false;
           if(!_compile_tex && lvalue != NO)compta_option_error("Please give yes or no to this option: " + keyword);
         }
          break;
        }
        case WRITE::LATEX:
        {
          _latex_file = value;
          break;
        }
        case WRITE::FROM:
        {
          _from_file.set_date(value);
          break;
        }
        case WRITE::TO:
        {
          _to_file.set_date(value);
          break;
        }
        default: //WTF???
        {
          compta_error();
        }
     }
  }

  void ComptaOptions::report(const ComptaObj & compte) const
  {
// on screen report
     compte.report(_from_stdout,_to_stdout,_print_forecast,_print_bank,_print_cash);

// LaTeX report
     if(_write_tex)
     {
        latex_report(compte,_from_file,_to_file,_latex_file);
       if(_compile_tex)
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
