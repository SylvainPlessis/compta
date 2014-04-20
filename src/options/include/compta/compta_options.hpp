//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//-----------------------------------------------------------------------el-

#ifndef COMPTA_OPTIONS_H
#define COMPTA_OPTIONS_H

//Compta
#include "compta/compta_obj.hpp"
#include "compta/latex_factory.hpp"
#include "compta/options_enum.hpp"

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

        bool _valid;

        std::map<std::string,Options::Options> _options_map;
        std::map<Options::Options,bool>        _options_value_map;

        void build_map();

        int pass_options(int pos, char **opts);

  };

  ComptaOptions::~ComptaOptions()
  {
      return;
  }

  ComptaOptions::ComptaOptions(int argc, char **argv):
     _valid(true)
  {
      this->build_map();
      for(int i = 1; i < argc; i++)
      {
          std::string argument(argv[i]);
          if(argument[0] == '-')
          {
             i = this->pass_options(i,argv);
          }else
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
              }
          }
      }

      if(_forecast_file.empty())_valid = false;
      if(_accounts_file.empty())
      {
         _accounts_file = _forecast_file;
      }
      if(_data_file.empty())
      {
         _data_file = _forecast_file;
      }

      return;
  }

  void ComptaOptions::build_map()
  {
      _options_map["--version"]      = Options::VERSION;
      _options_map["-v"]             = Options::VERSION;
      _options_map["--help"]         = Options::HELP;
      _options_map["-h"]             = Options::HELP;
      _options_map["--generate_tex"] = Options::GENERATE_TEX;
      _options_map["-g"]             = Options::GENERATE_TEX;
      _options_map["--compile_tex"]  = Options::COMPILE_TEX;
      _options_map["-c"]             = Options::COMPILE_TEX;

      _options_value_map[Options::VERSION]       = false;
      _options_value_map[Options::HELP]          = false;
      _options_value_map[Options::GENERATE_TEX]  = true;
      _options_value_map[Options::COMPILE_TEX]   = true;
  }

  bool ComptaOptions::valid() const
  {
      return _valid;
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
      if(_options_value_map.at(_options_map.at(keyword)))
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

      return pos;
  }

  void ComptaOptions::unvalid_invocation(std::ostream & out, const std::string & prog) const
  {
    out << "Invalid invocation" << std::endl;
    out << "For help: " << prog << " --help" << std::endl;
    compta_error();
  }


}

#endif
