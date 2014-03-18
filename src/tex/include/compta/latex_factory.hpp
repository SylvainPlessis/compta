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
  void latex_bank(std::ofstream &out, const Bank &bank);
  //! details by month
  void latex_data(std::ofstream &out, const ComptaObj &compte);
  //! details for a month
  void latex_month(std::ofstream &out, const MonthlyReport &month_report, const Money &money);
  //!color
  void add_color(float amount, float thres, float mar, std::ostream &out); 

  inline
  const std::string latex_report_head()
  {
     std::string head("\\documentclass[french]{report}\n");
     head += "\\usepackage{booktabs,multicol,longtable}\%beaux tableaux\n";
     head += "\\usepackage{geometry}\n";
     head += "\\usepackage[T1]{fontenc}\n";
     head += "\\usepackage[utf8]{inputenc}\n";
     head += "\\usepackage{babel}\n";
     head += "\\usepackage{xcolor}\n";
     head += "\\usepackage{marvosym}\n";
     head += "\\usepackage[autolanguage]{numprint}\n";
     head += "\\usepackage[linkcolor=black,colorlinks=true]{hyperref}\n";
     head += "\\begin{document}\n";
     head += "\\renewcommand{\\chaptername}{}\n";
     head += "\\renewcommand{\\thechapter}{}\n";
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
     Money money(prev.currency());
     out << "\\centering" << std::endl;
     out << "\\renewcommand{\\arraystretch}{1.2}" << std::endl;
     out << "\\begin{longtable}{lccc}\\toprule" << std::endl;
     out << "Catégorie & Débit provisionnel & \\multicolumn{2}{c}{Fixe} \\\\\\cmidrule{3-4}" << std::endl;
     out << "          &                    &  Montant  & Date de début de prise en compte/\\\\" << std::endl
         << "          &                    & (marge)   & fin de prise en compte/\\\\" << std::endl
         << "          &                    &           & période en mois \\\\\\cmidrule{2-3}" << std::endl;
     out << "          & \\multicolumn{2}{c}{" << money.tex_money() << "}     &  \\\\" << std::endl;
     for(unsigned int ic = 0; ic < prev.forecast().n_objects(); ic++) //categories
     {
       out << std::fixed << std::setprecision(2) 
           << "\\midrule" << std::endl
           << "\\underline{" << prev.forecast().operations_list()[ic].name() << "} &\\bf\\small " 
           << "\\numprint{"  << prev.forecast().operations_list()[ic].amount() << "} (\\numprint{" 
                             << prev.forecast().operations_list()[ic].margin() << "}) & "  
           <<  "\\\\" << std::endl;
         for(unsigned int isc = 0; isc < prev.forecast().operations_list()[ic].n_objects(); isc++)
         {
            out << std::fixed << std::setprecision(2)
                << "\\multicolumn{2}{l}{\\hspace{12pt} " << prev.forecast().operations_list()[ic].operations_list()[isc].name() << "} & "
                << "\\numprint{" << prev.forecast().operations_list()[ic].operations_list()[isc].amount() << "}  (\\numprint{"
                                 << prev.forecast().operations_list()[ic].operations_list()[isc].margin() << "}) & \\tt "
                << prev.forecast().operations_list()[ic].operations_list()[isc].starting_date().date_string() << "\\ \\textendash\\ "//rule[3pt]{12pt}{0.6pt}"
                << prev.forecast().operations_list()[ic].operations_list()[isc].ending_date().date_string() << "\\hfill\\sf "
                << prev.forecast().operations_list()[ic].operations_list()[isc].period() << " \\\\" << std::endl;
         }
     }
     out << "\\bottomrule" << std::endl;
     out << "\\end{longtable}" << std::endl;
  }

  inline
  void latex_bank(std::ofstream &out, const Bank &bank)
  {
     if(bank.records().history().empty())return;
     Money money(bank.currency());

     Date cur_month = bank.records().history().back().date(); //last date
     cur_month.set_date(1, cur_month.month(), cur_month.year()); //last month

     out << "\\chapter{" << bank.name() << "}" << std::endl;
     out << std::endl;
     out << "\\begin{longtable}{p{8cm}>{\\tt}cr<{~" << money.tex_money() << "}}\\toprule" << std::endl;
     out << "Description & Date & Montant \\\\\\midrule\\endhead" << std::endl;
     unsigned int ips(0);
     float start(0.L);
     while(cur_month > bank.records().history()[ips].date())
     {
        ips++;
        start += bank.records().history()[ips].amount();
     }
     out << "\\'Etat initial & " << cur_month.date_string() << " & \\numprint{" << start << "}\\\\[5pt]" << std::endl;
     for(unsigned int ip = ips; ip < bank.records().history().size(); ip++)
     {
        out << bank.records().history()[ip].description() << " & " 
            << bank.records().history()[ip].date()        << " & "
            << "\\numprint{" << 
                bank.records().history()[ip].amount()      << "}\\\\" << std::endl;
     }
     out << "\\midrule" << std::endl;
     out << "\\'Etat actuel & \\today & \\numprint{" << bank.records().current_state() << "}\\\\" << std::endl;

     if(!bank.records().in_waiting().empty())
     {
       out << "\\midrule\\addlinespace[10pt]" << std::endl;
       out << "\\underline{Opération(s) en attente}\\\\[3pt]" << std::endl;
       for(unsigned int ip = 0; ip < bank.records().in_waiting().size(); ip++)
       {
        out << bank.records().in_waiting()[ip].description() << " & " 
            << bank.records().in_waiting()[ip].date()        << " & "
            << "\\numprint{" << 
                        bank.records().in_waiting()[ip].amount()    << "}\\\\" << std::endl;
       }
       out << "\\midrule" << std::endl;
       out << "\\'Etat attendu & \\today & \\numprint{" << bank.records().expected_state() << "}\\\\" << std::endl;
     }  

     out << "\\bottomrule" << std::endl;
     out << "\\end{longtable}" << std::endl << std::endl;
  }

  inline
  void latex_data(std::ofstream &out, const ComptaObj &compte)
  {
       std::vector<MonthlyReport> report;
       compte.report_compta(report);
       Money money;
       if(!compte.banque().empty())
       {
          money.set_money(compte.banque().front().currency());
       }
       else if(!compte.liquide().empty())
       {
          money.set_money(compte.liquide().front().currency());
       }

       for(unsigned int imo = 0; imo < report.size(); imo++)
       {
          out << "\\chapter{" << DateUtils::month_in_letter(report[imo].date().month()) << " " 
                              << report[imo].date().year() << "}" << std::endl;

          latex_month(out,report[imo],money);
       }
  }

  inline
  void latex_month(std::ofstream &out, const MonthlyReport &month_report, const Money &money)
  {
     out << "\\begin{longtable}{p{6cm}cr}\\toprule" << std::endl;
     out << "Operation & Date & Montant " << money.tex_money() << "\\\\\\midrule" << std::endl;

     for(unsigned int icat = 0; icat < month_report.report().size(); icat++)
     {
        const CategoryReport & cat = month_report.report()[icat];

        out << "\\addlinespace\\raggedright\\textbf{\\underline{" << cat.name() << "}} & "
            << "\\sl{";
        add_color(cat.amount(),cat.forecast_amount(),cat.forecast_margin(),out);
        out <<"\\numprint{" << cat.amount() << "}} ({";
        add_color(cat.expected_amount(), cat.forecast_amount(), cat.forecast_margin(),out);
        out << "\\numprint{" << cat.expected_amount() << "}}) "
                        << money.tex_money() << " & \\bf"
            << "\\numprint{" << cat.forecast_amount() << "} +/- \\numprint{" << cat.forecast_margin() <<   "} "
                        << money.tex_money() << "\\\\*" << std::endl;
//passed
        if(!cat.done().empty())
        {
           out << "\\addlinespace[3pt]\\raggedleft\\small\\sf\\underline{Opération(s) passée(s)} & &\\\\*[3pt]" << std::endl; 
        }
        for(unsigned int ipo = 0; ipo < cat.done().size(); ipo++)
        {
           out << "\\hspace{12pt}"
               << cat.done()[ipo].description() << " & " 
               << cat.done()[ipo].date()        << " & " 
               << "\\numprint{" << cat.done()[ipo].amount() << "}\\\\" << std::endl; 
        }
//posting not passed
        if(!cat.not_done().empty())
        {
           out << "\\addlinespace[3pt]\\raggedleft\\small\\sf\\underline{Opération(s) en attente} & &\\\\*[3pt]" << std::endl; 
        }
        for(unsigned int ipo = 0; ipo < cat.not_done().size(); ipo++)
        {
           out << "\\hspace{12pt}\\it "
               << cat.not_done()[ipo].description() << " &\\it " 
               << cat.not_done()[ipo].date()        << " &\\it " 
               << "\\numprint{" << cat.not_done()[ipo].amount() << "}\\\\" << std::endl; 
        }
//operation not passed, sign convention is the other (because of forecast printing)
        if(!cat.waiting().empty())
        {
           out << "\\addlinespace[3pt]\\raggedleft\\small\\sf\\underline{Opération(s) automatique(s) en attente} & &\\\\*[3pt]" << std::endl; 
        }
        for(unsigned int ipo = 0; ipo < cat.waiting().size(); ipo++)
        {
           out << "\\hspace{12pt}\\it " 
               << cat.waiting()[ipo].name() << " & &\\it "
               << "\\numprint{"         << - cat.waiting()[ipo].amount() << "}\\\\" << std::endl; 
        }
        out << "\\addlinespace\\cmidrule(r{2cm}l{5cm}){1-2}" << std::endl;
     }

     out << "\\addlinespace Total   & {";
     add_color(month_report.amount(),month_report.forecast_amount(),month_report.forecast_margin(),out);
     out << "\\numprint{" << month_report.amount() << "}} " << money.tex_money() << " & \\numprint{" 
         << month_report.forecast_amount() << "} +/- \\numprint{"
         << month_report.forecast_margin() << "} " << money.tex_money() << "\\\\\\bottomrule" 
         << std::endl;

     out << "Attendu & {";
     add_color(month_report.expected_amount(),month_report.forecast_amount(),month_report.forecast_margin(),out);
     out << "\\numprint{" << month_report.expected_amount() << "}} " << money.tex_money() << " & \\\\\\bottomrule" 
         << std::endl;

     out << "\\end{longtable}" << std::endl;
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
  
     for(unsigned int ib = 0; ib < compte.banque().size(); ib++)
     {
       latex_bank(out,compte.banque()[ib]);
     }

     out << "\\part{Détail}" << std::endl;

     latex_data(out,compte);

     out << latex_report_foot() << std::endl;

     out.close();
  }

  inline
  void add_color(float amount, float thres, float mar, std::ostream &out)
  {
      if(amount > thres + mar)
      {
         out << "\\color{red}";
      }else if(amount > thres)
      {
         out << "\\color{orange}";
      }
      return;
  }

}

#endif
