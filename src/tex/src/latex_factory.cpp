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

#include "compta/latex_factory.hpp"

namespace Compta
{
  
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

  
  const std::string latex_report_foot()
  {
     return "\\end{document}";
  }

  
  void latex_forecast(std::ofstream &out, const Forecast &prev)
  {
     Money money(prev.currency());
     out << std::setprecision(2) << std::fixed;
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
                << "\\numprint{" << prev.forecast().operations_list()[ic].operations_list()[isc].raw_amount() << "}  (\\numprint{"
                                 << prev.forecast().operations_list()[ic].operations_list()[isc].raw_margin() << "}) & \\tt "
                << prev.forecast().operations_list()[ic].operations_list()[isc].starting_date().date_string() << "\\ \\textendash\\ "//rule[3pt]{12pt}{0.6pt}"
                << prev.forecast().operations_list()[ic].operations_list()[isc].ending_date().date_string() << "\\hfill\\sf "
                << prev.forecast().operations_list()[ic].operations_list()[isc].period() << " \\\\" << std::endl;
         }
     }
     out << "\\bottomrule\\addlinespace" << std::endl;
     out << "\\bf\\large Total & \\large\\bf";
     if(prev.forecast().amount() < 0.)
     {
       out << "\\color{green!60!black}\\numprint{" << - prev.forecast().amount();
     }else
     {
       out << "\\color{red}\\numprint{" << prev.forecast().amount();
     }
     out << "} +/- \\numprint{" << prev.forecast().margin()
         << "} " << money.tex_money() << "\\\\\\bottomrule" << std::endl;
     out << "\\end{longtable}" << std::endl;
  }

  
  void latex_account(std::ofstream &out, const Date & from, const Date & to, const History &acc, const std::string & name, const Currency::Currency &money)
  {
     if(acc.empty())return;

     Money cur(money);
     const std::string currency(cur.tex_money());

     Date cur_month = acc.start_date(); //first date
     cur_month.set_date(1, cur_month.month(), cur_month.year()); //at the start of the month

        // rescaling if need be
     if(cur_month < from) cur_month = from;

     out << std::setprecision(2) << std::fixed;
     out << "\\chapter{" << name << "}" << std::endl;
     out << std::endl;
     out << "\\begin{longtable}{p{8cm}>{\\tt}cr<{~" << currency << "}r<{~" << currency << "}}\\toprule" << std::endl;
     out << "Description & Date & Montant & Bilan \\\\\\midrule\\endhead" << std::endl;

        // find starting state at date cur_month
     unsigned int ips(0);
     float courant(acc.starting_state());
     if(!acc.done_empty())
     {
       while(cur_month > acc.history()[ips].date())
       {
         courant += acc.history()[ips].amount();
         ips++;
       }
     }

     out << "\\'Etat initial & " << cur_month.date_string() << " & & \\numprint{" << courant << "}\\\\[5pt]" << std::endl;
     for(unsigned int ip = ips; ip < acc.history().size(); ip++)
     {
        courant += acc.history()[ip].amount();
        out << acc.history()[ip].description() << " & " 
            << acc.history()[ip].date()        << " & "
            << "\\numprint{" << 
                acc.history()[ip].amount()     << "} & "
            << "\\numprint{" << courant                  << "}\\\\" << std::endl;
     }
     out << "\\midrule" << std::endl;
     out << "\\'Etat actuel & \\today & & \\numprint{" << acc.current_state() << "}\\\\" << std::endl;

     if(!acc.expected_empty())
     {
       out << "\\midrule\\addlinespace[10pt]" << std::endl;
       out << "\\underline{Opération(s) en attente}\\\\[3pt]" << std::endl;
       for(unsigned int ip = 0; ip < acc.in_waiting().size(); ip++)
       {
        courant += acc.in_waiting()[ip].amount();
        out << acc.in_waiting()[ip].description() << " & " 
            << acc.in_waiting()[ip].date()        << " & "
            << "\\numprint{" << 
                acc.in_waiting()[ip].amount()     << "} & "
            << "\\numprint{" <<  courant                    << "}\\\\" << std::endl;
       }
       out << "\\midrule" << std::endl;
       out << "\\'Etat attendu & \\today & & \\numprint{" << acc.expected_state() << "}\\\\" << std::endl;
     }  

     out << "\\bottomrule" << std::endl;
     out << "\\end{longtable}" << std::endl << std::endl;
  }

  
  void latex_data(std::ofstream &out, const Date & from, const Date & to, const ComptaObj &compte)
  {
       out << std::setprecision(2) << std::fixed;
       std::vector<MonthlyReport> report;
       compte.report_compta(report,from,to);
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

  
  void latex_month(std::ofstream &out, const MonthlyReport &month_report, const Money &money)
  {
     out << std::setprecision(2) << std::fixed;
     out << "\\begin{longtable}{p{6cm}cr}\\toprule" << std::endl;
     out << "\\textbf{\\underline{Catégorie}} & \\sl Montant dépensé & \\bf Prévisionnel \\\\" << std::endl;
     out << "\\hspace{12pt}Operation & Date & Montant \\\\\\midrule\\endhead" << std::endl;

     for(unsigned int icat = 0; icat < month_report.report().size(); icat++)
     {
        const CategoryReport & cat = month_report.report()[icat];

        out << "\\addlinespace\\raggedright\\textbf{\\underline{" << cat.name() << "}} & "
            << "\\sl{";
        add_color(cat.amount(),cat.forecast_amount(),cat.forecast_margin(),out);
        out <<"\\numprint{" << cat.amount() << "}} ";
        if(std::abs(cat.expected_amount() - cat.amount()) >= 0.01)
        {
          out << " ({";
          add_color(cat.expected_amount(), cat.forecast_amount(), cat.forecast_margin(),out);
          out << "\\numprint{" << cat.expected_amount() << "}}) ";
        }
        out << money.tex_money() << " & \\bf"
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
               << "\\numprint{" << cat.done()[ipo].amount() << "} " << money.tex_money() << "\\\\" << std::endl; 
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
               << "\\numprint{" << cat.not_done()[ipo].amount() << "} " << money.tex_money() << "\\\\" << std::endl; 
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
               << "\\numprint{"  << - cat.waiting()[ipo].amount() << "} " << money.tex_money() << "\\\\" << std::endl; 
        }
        out << "\\addlinespace\\cmidrule(r{2cm}l{5cm}){1-2}" << std::endl;
     }

     out << "\\addlinespace Dépenses totales   & ";
     out << "\\numprint{" << month_report.amount_no_income() << "} " << money.tex_money() << " & \\numprint{" 
         << month_report.forecast_amount_no_income() << "} +/- \\numprint{"
         << "NULL" //month_report.forecast_margin_no_income() 
         << "} " << money.tex_money() << "\\\\\\bottomrule" 
         << std::endl;

     out << "Attendu & ";
     out << "\\numprint{" << month_report.expected_amount_no_income() << "} " << money.tex_money() << " & \\\\\\bottomrule" 
         << std::endl;

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


  
  void latex_report(const ComptaObj &compte, const Date & from, const Date & to, std::string file)
  {
     if(file.find(".tex") == std::string::npos)file += ".tex";
     std::ofstream out(file.c_str());

     out << std::setprecision(2) << std::fixed;
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
       latex_account(out,from,to,compte.banque()[ib].records(),compte.banque()[ib].name(),compte.banque()[ib].currency());
        for(unsigned int s = 0; s < compte.banque()[ib].savings().size(); s++)
        {
         latex_account(out,from,to,compte.banque()[ib].savings()[s],compte.banque()[ib].savings_list()[s],compte.banque()[ib].currency());
        }
     }

     for(unsigned int ic = 0; ic < compte.liquide().size(); ic++)
     {
       latex_account(out, from, to, compte.liquide()[ic].records(), compte.liquide()[ic].name(),compte.liquide()[ic].currency());
     }

     out << "\\part{Détail}" << std::endl;

     latex_data(out, from, to, compte);

     out << latex_report_foot() << std::endl;

     out.close();
  }

  
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
