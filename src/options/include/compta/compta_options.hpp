//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//-----------------------------------------------------------------------el-

#ifndef COMPTA_OPTIONS_H
#define COMPTA_OPTIONS_H

//Compta
#include "compta/compta_obj.hpp"
#include "compta/latex_factory.hpp"

//C++
#include <iostream>

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

      private:
        ComptaOptions();

        std::string _forecast_file;
        std::string _accounts_file;
        std::string _data_file;

        bool _valid;

        int pass_options(int pos, char **opts);

  };

  ComptaOptions::~ComptaOptions()
  {
      return;
  }

  ComptaOptions::ComptaOptions(int argc, char **argv):
     _valid(true)
  {
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

  bool ComptaOptions::valid() const
  {
      return _valid;
  }

  const std::string ComptaOptions::forecast_file() const
  {
      return _forecast_file;
  }

  const std::string accounts_file() const
  {
      return _accounts_file;
  }

  const std::string data_file() const
  {
      return _data_file;
  }


}

#endif
