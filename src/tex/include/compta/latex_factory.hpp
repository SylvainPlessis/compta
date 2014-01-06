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

#ifndef COMPTA_LATEX_FACTORY_H
#define COMPTA_LATEX_FACTORY_H

//Compta
#include "compta/compta_obj.hpp"

//C++
#include <fstream>
#include <string>

namespace Compta{

  //! prints the .tex output
  void latex_report(const ComptaObj &compte, std::string file);
  //! preamble
  const std::string latex_report_head();
  //! end of the document
  const std::string latex_report_foot();

  inline
  const std::string latex_report_head()
  {
     std::string head("\\documentclass[french]{report}");
     return head;
  }

  inline
  const std::string latex_report_foot()
  {
     return "\\end{document}";
  }

  inline
  void latex_report(const ComptaObj &compte, std::string file)
  {
     if(file.find(".tex") == std::string::npos)file += ".tex";
     std::ofstream out(file.c_str());

     out << latex_report_head() << std::endl;

     out << "\\title{" << compte.title() << "}" << std::endl;
     out << "\\author{Mélanie}" << std::endl;
     out << "\\date{\\today}" << std::endl << std::endl;

     out << "\\part{Prévisionnel}" << std::endl;

     out.close();
  }

}

#endif
