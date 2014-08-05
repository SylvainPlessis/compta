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

#ifndef COMPTA_READ_INPUT_FILE_H
#define COMPTA_READ_INPUT_FILE_H

//Compta
#include "compta/compta_obj.hpp"
#include "compta/forecast.hpp"

//C++
#include <string>

namespace Compta{

  void read_forecast(Forecast & forecast,
                        const std::string &file);

  void read_accounts(ComptaObj &compte,
                        const std::string &file);

  void read_data(ComptaObj &compte,
                        const std::string &file);

  void parse_input_file(ComptaObj & compte,
                        const std::string &forecast_file,
                        const std::string &accounts_file,
                        const std::string &data_file);

}

#endif
