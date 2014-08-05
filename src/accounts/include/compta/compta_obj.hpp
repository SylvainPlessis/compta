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

#ifndef COMPTA_COMPTA_OBJET_H
#define COMPTA_COMPTA_OBJET_H

//compta
#include "compta/string_utils.hpp"
#include "compta/forecast.hpp"
#include "compta/cash.hpp"
#include "compta/bank.hpp"
#include "compta/savings.hpp"
#include "compta/parsing_def.hpp"
#include "compta/money.hpp"
#include "compta/monthly_report.hpp"

//C++
#include <vector>
#include <map>
#include <cstdlib> //atof
#include <cmath> //abs
#include <iomanip>

namespace Compta{

  class ComptaObj{
    public:
      ComptaObj();
      ComptaObj(const ComptaObj &rhs);
      ~ComptaObj();

      //!print
      void report(std::ostream &out = std::cout) const;

      //!print also
      friend std::ostream &operator<< (std::ostream &out, const ComptaObj &obj)
      {
          obj.report(out);
          return out;
      }

      //!new bank account
      void add_bank_account(const Bank &ban, const bool &main);
      //!new saving account attached to a bank account
      void add_savings_account(const Savings &epa, const std::string &name, const std::string &ref);
      //!new cash account
      void add_cash_account(const Cash &liq, const bool &main);
      //!sets the forecast
      void set_forecast(const Forecast &prev);

      //!sets the title
      void set_title(const std::string &title);

      //!\return the bank map
      const std::map<std::string,unsigned int> banque_map() const;
      //!\return the bank accounts
      const std::vector<Bank> banque()                      const;
      //!\return the cash accounts
      const std::vector<Cash> liquide()                     const;
      //!\return the forecast
      const Forecast previsionnel()                         const;
      //!\return the title
      const std::string title()                             const;

      //!adds a posting
      void add_posting(Posting &post);

      //!build the report objects
      void report_compta(std::vector<MonthlyReport> &rep) const;

      //!report a month, date is in the MonthlyReport object
      void report_compta(MonthlyReport &rep) const;

      //!operator
      ComptaObj &operator=(const ComptaObj &rhs);

    private:
      //!adding root templated function for both bank and cash
      template<typename Ac>
      void add_account(const Ac &account, const bool &main, 
                       std::vector<Ac> &target, std::map<std::string,unsigned int> &map);

      //!adding post root templated function for both bank and cash
      template<typename Ac>
      void add_posting(Posting &post, std::vector<Ac> &target, std::map<std::string,unsigned int> &map,
                       const std::string &decl, std::vector<std::string> &out);

      /*!higher-level tranfert management method
       *
       * Declares the matrix between source and target,
       * then pass on to the lower-level methods
       */
      void add_transfert(Posting &post, const std::vector<std::string> &out);

      //! fills the matrix between source and target
      void find_src_and_trg(unsigned int &n_end, std::vector<std::vector<int> > & ends, const std::vector<std::string> &out) const;

      //! checks the map contains source and/or target
      void check_src_and_trg(int &src, int &trg, unsigned int &counter, const std::vector<std::string> &out, 
                             const std::map<std::string, unsigned int> &cur_map) const;

      //! \returns a posting of minus the value, in another currency if declared
      const Posting convert_posting_currency(const Posting &source,const Currency::Currency &mon) const;

      //! preprocess the matrix
      void preprocess_matrix_and_add(unsigned int counter, std::vector<std::vector<int> > & corres, Posting &post);

      //! treat the source
      void posting_someone_to_someone(const std::vector<int> &sources,const std::vector<int> &targets, Posting &post);

      //! treat the target if source is a bank
      void posting_bank_to_someone(Bank & source, const std::vector<int> &map, Posting &post);

      //! treat the target if source is a cash
      void posting_cash_to_someone(Cash & source, const std::vector<int> &map, Posting &post);

      //! actually adds the posting to source and target
      template<typename AccountTypeSrc, typename AccountTypeTrg>
      void posting_account_to_account(AccountTypeSrc &src, AccountTypeTrg &trg, Posting &post);

      Forecast _previsionnel;
      std::vector<Cash> _liquide;
      std::vector<Bank> _banque;
      std::map<std::string,unsigned int> _banque_map;
      std::map<std::string,unsigned int> _liquide_map;
      std::string _title;
  };


}

#endif
