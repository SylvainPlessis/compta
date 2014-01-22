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
  void latex_bank(std::ofstream &out, const std::vector<Bank> &bank);

  inline
  const std::string latex_report_head()
  {
     std::string head("\\documentclass[french]{report}\n");
     head += "\\usepackage{booktabs,multicol}\%beaux tableaux\n";
     head += "\\usepackage{geometry}\n";
     head += "\\usepackage[T1]{fontenc}\n";
     head += "\\usepackage[utf8]{inputenc}\n";
     head += "\\usepackage{babel}\n";
     head += "\\usepackage{xcolor}\n";
     head += "\\usepackage{marvosym}\n";
     head += "\\usepackage[autolanguage]{numprint}\n";
     head += "\\usepackage[linkcolor=black,colorlinks=true]{hyperref}\n";
     head += "\\begin{document}\n";
     return head;
  }

  inline
  const std::string latex_report_foot()
  {
     return "\\end{document}";
  }

  inline
  void latex_forecast(std::ofstream &out, const Forecast &prev)
  {
     out << "\\centering" << std::endl;
     out << "\\begin{tabular}{lccc}\\toprule" << std::endl;
     out << "Catégorie & Débit provisionnel & \\multicolumn{2}{c}{Fixe} \\\\\\cmidrule{3-4}" << std::endl;
     out << "          &                    &  Montant  & Date de début de prise en compte/\\\\" << std::endl
         << "          &                    &           & fin de prise en compte/\\\\" << std::endl
         << "          &                    &           & période en mois \\\\\\cmidrule{2-3}" << std::endl;
     out << "          & \\multicolumn{2}{c}{\\EUR}     &  \\\\" << std::endl;
     for(unsigned int ic = 0; ic < prev.forecast().n_objects(); ic++) //categories
     {
       out << std::fixed << std::setprecision(2) 
           << "\\midrule" << std::endl
           << prev.forecast().operations_list()[ic].name() << " & " 
           << "\\numprint{" << prev.forecast().operations_list()[ic].amount() << "} +/- \\numprint{" 
                            << prev.forecast().operations_list()[ic].margin() << "} & "  
           <<  "\\\\" << std::endl;
         for(unsigned int isc = 0; isc < prev.forecast().operations_list()[ic].n_objects(); isc++)
         {
            out << std::fixed << std::setprecision(2)
                << "\\multicolumn{2}{l}{\\hspace{12pt} " << prev.forecast().operations_list()[ic].operations_list()[isc].name() << "} & "
                << "\\numprint{" << prev.forecast().operations_list()[ic].operations_list()[isc].amount() << "} +/- \\numprint{"
                                 << prev.forecast().operations_list()[ic].operations_list()[isc].margin() << "} & "
                << prev.forecast().operations_list()[ic].operations_list()[isc].starting_date().date_string() << ", "
                << prev.forecast().operations_list()[ic].operations_list()[isc].ending_date().date_string() << ", "
                << prev.forecast().operations_list()[ic].operations_list()[isc].period() << " \\\\" << std::endl;
         }
     }
     out << "\\bottomrule" << std::endl;
     out << "\\end{tabular}" << std::endl;
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
     out << "\\maketitle" << std::endl << std::endl;

     out << "\\part{Prévisionnel}" << std::endl;

     latex_forecast(out,compte.previsionnel());

     out << "\\part{Comptes}" << std::endl;

     //latex_bank(out,compte.banque());

     out << latex_report_foot() << std::endl;

     out.close();
  }

}

#endif
