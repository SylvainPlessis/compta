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

#ifndef COMPTA_LATEX_FACTORY_H
#define COMPTA_LATEX_FACTORY_H

//Compta
#include "compta/compta_obj.hpp"

//C++
#include <fstream>
#include <string>
#include <iomanip>

namespace Compta{

  //! prints the .tex output
  void latex_report(const ComptaObj &compte, std::string file);
  //! preamble
  const std::string latex_report_head();
  //! end of the document
  const std::string latex_report_foot();
  //! forecast
  void latex_forecast(std::ofstream &out, const Forecast &prev);
  //! bank account
  void latex_account(std::ofstream &out, const History &acc, const std::string & name, const Currency::Currency &money);
  //! details by month
  void latex_data(std::ofstream &out, const ComptaObj &compte);
  //! details for a month
  void latex_month(std::ofstream &out, const MonthlyReport &month_report, const Money &money);
  //!color
  void add_color(float amount, float thres, float mar, std::ostream &out); 

}

#endif
