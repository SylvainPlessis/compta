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

  inline
  ComptaObj::ComptaObj()
  {
      return;
  }

  inline
  ComptaObj::ComptaObj(const ComptaObj &rhs)
  {
      *this = rhs;
      return;
  }

  inline
  ComptaObj::~ComptaObj()
  {
      return;
  }

  inline
  ComptaObj &ComptaObj::operator=(const ComptaObj &rhs)
  {
     if(this != &rhs)
     {
       _previsionnel = rhs.previsionnel();
       _liquide = rhs.liquide();
       _banque = rhs.banque();
       _banque_map = rhs.banque_map();
     }
     return *this;
  }

  inline
  const std::map<std::string,unsigned int> ComptaObj::banque_map() const
  {
    return _banque_map;
  }
  
  inline
  const std::vector<Bank> ComptaObj::banque() const
  {
    return _banque;
  }

  inline
  const std::vector<Cash> ComptaObj::liquide() const
  {
    return _liquide;
  }
  
  inline
  const Forecast ComptaObj::previsionnel() const
  {
    return _previsionnel;
  }

  inline
  const std::string ComptaObj::title() const
  {
    return _title;
  }


  inline
  void ComptaObj::add_bank_account(const Bank &ban, const bool &main)
  {
      this->add_account<Bank>(ban, main, this->_banque, this->_banque_map);
  }

  template<typename Ac>
  inline
  void ComptaObj::add_account(const Ac &src, const bool &main, std::vector<Ac> &target, std::map<std::string,unsigned int> &map)
  {
     if(target.empty() || !main)
     {
       target.push_back(src);
       map[src.name()] = target.size() - 1;
     }else
     {
       target.insert(target.begin(),src);
       map.clear();
       for(unsigned int i = 0; i < target.size(); i++)
       {
          map[target[i].name()] = i;
       }
     }
  }
  
  inline
  void ComptaObj::add_savings_account(const Savings &epa, const std::string &sname, const std::string &ref)
  {
     if(!_banque_map.count(ref))
                compta_savings_error(std::string("This savings account " + sname + " has not bank account reference,\n" + 
                                      ref + " does not exist. See your input file, is the order ok?"));
     _banque[_banque_map[ref]].add_savings_account(epa,sname);
  }
  
  inline
  void ComptaObj::add_cash_account(const Cash &liq, const bool &main)
  {
      this->add_account<Cash>(liq, main, this->_liquide, this->_liquide_map);
  }
  
  inline
  void ComptaObj::set_forecast(const Forecast &prev)
  {
     _previsionnel = prev;
  }

  inline
  void ComptaObj::set_title(const std::string &title)
  {
    if(_title.empty())
    {
      _title = title;
    }else
    {
       if(_title != title)compta_reading_error(std::string("Different titles are given for the same comptability.\n" + FilesParsing::error_message));
    }
  }

  inline
  void ComptaObj::add_posting(Posting &post)
  {
     std::vector<std::string> out;
     SplitString(post.description(),DataParsing::delimiter(), out, false);
     if(out.empty())out.push_back(post.description());
     if(post.identifier() == PostingType::B)
     {
         this->add_posting(post, this->_banque, this->_banque_map, "bank", out);
     }else if(post.identifier() == PostingType::L)
     {
         this->add_posting(post, this->_liquide, this->_liquide_map, "cash", out);
     }else if(post.identifier() == PostingType::V)
     {
        shave_string(out);
        this->add_transfert(post,out);
     }else
     {

        compta_error();
     }
  }

  inline
  void ComptaObj::add_transfert(Posting &post, const std::vector<std::string> &out)
  {      
        unsigned int n_end(0);
        std::vector< std::vector<int> > ends; //[src|trg][ban|epa|cas]
        ends.resize(2); //[src|trg]
        ends[0].resize(3,-1);//[src][ban|epa|cas]
        ends[1].resize(3,-1);//[trg][ban|epa|cas]

        this->find_src_and_trg(n_end,ends,out);

        this->preprocess_matrix_and_add(n_end,ends,post);

  }

  void ComptaObj::check_src_and_trg(int &src, int &trg, unsigned int &count,
                                       const std::vector<std::string>  &out, 
                                       const std::map<std::string, unsigned int> &cur_map) const
  {
    for(unsigned int i = 0; i < out.size(); i++)
    {
      if(cur_map.count(out[i]))
      {
        if(count == 0) 
        {
          src = (int)cur_map.at(out[i]);
        }else
        {
          trg = (int)cur_map.at(out[i]);
        }
        count++;
      }
    }

    return; 
  }

  void ComptaObj::find_src_and_trg(unsigned int &n_ends, std::vector<std::vector<int> > & ends, const std::vector<std::string> &out) const
  {

    unsigned int src(0),trg(1);
    unsigned int ban(0),epa(1),cas(2);

// is there a bank?
    this->check_src_and_trg(ends[src][ban],ends[trg][ban],n_ends,out,_banque_map);
// is there a cash?
    this->check_src_and_trg(ends[src][cas],ends[trg][cas],n_ends,out,_liquide_map);

// if there's a bank, is there a savings?
// weak form, we do not check if there's already a target
   if(ends[src][ban] < 0) //might be default bank to savings
   {
      this->check_src_and_trg(ends[src][epa],ends[trg][epa],n_ends,out,_banque.front().savings_map());
   }else //then might be between custom bank and savings
   {
      this->check_src_and_trg(ends[src][epa],ends[trg][epa],n_ends,out,_banque[ends[src][ban]].savings_map());
   }

   return;
 }

 template<typename AccountTypeSrc, typename AccountTypeTrg>
 inline
 void ComptaObj::posting_account_to_account(AccountTypeSrc &src, AccountTypeTrg &trg, Posting &post)
 {
   src.add_posting(post);
   trg.add_posting(this->convert_posting_currency(post,trg.currency()));
 }


 inline
 void ComptaObj::posting_bank_to_someone(Bank & source, const std::vector<int> &map, Posting &post)
 {
//0: bank
//1: savings
//2: cash
   if(map[0] >= 0)// to bank
   {
      this->posting_account_to_account(source,_banque[map[0]],post);
   }else if(map[1] >= 0)//to savings
   {
      source.add_posting(post,(unsigned int)map[1]);
   }else if(map[2] >= 0)//to cash
   {

      this->posting_account_to_account(source,_liquide[map[2]],post);
   }else//???
   {
      std::cerr << "you want to transfert from bank account " << source.name()
                << " to who exactly?\n"
                << post.description() << std::endl;
      compta_error();
   }
   return;
 }

 inline
 void ComptaObj::posting_cash_to_someone(Cash & source, const std::vector<int> &map, Posting &post)
 {
//0: bank
//1: savings, no savings possible with cash
//2: cash
   if(map[0] >= 0)// to bank
   {
      this->posting_account_to_account(source,_banque[map[0]],post);
   }else if(map[2] >= 0)//to cash
   {

      this->posting_account_to_account(source,_liquide[map[2]],post);
   }else//???
   {
      std::cerr << "you want to transfert from cash account " << source.name()
                << " to who exactly?\n"
                << post.description() << std::endl;
      compta_error();
   }
   return;
 }

 inline
 void ComptaObj::posting_someone_to_someone(const std::vector<int> &sources,const std::vector<int> &targets,Posting &post)
 {
    if(sources[0] >= 0)
    {
         this->posting_bank_to_someone(_banque[sources[0]],targets,post); 

    }else if(sources[2] >=0)
    {
         this->posting_cash_to_someone(_liquide[sources[2]],targets,post); 
    }else//???
    {
         compta_error();
    }
 }

 inline
 void ComptaObj::preprocess_matrix_and_add(unsigned int counter, std::vector<std::vector<int> > & corres, Posting &post)
 {

//preprocess matrix
     switch(counter)// counter = 0, from main bank to main cash
     {
       case 0: 
       {
         corres[0][0] = 0;
         corres[1][2] = 0;
         break;
       }
       case 1: // counter = 1, from main bank to someone (bank, savings or cash)
       {

         corres[1] = corres[0];
         corres[0][0] = 0;
         corres[0][1] = -1;
         corres[0][2] = -1;
         break;

      }
      case 2: // counter = 2, explicit
      {
       break;
      }
      default:
      {
       compta_error();
      }
    }//end switch

    this->posting_someone_to_someone(corres[0],corres[1],post);

    return;

  }

  inline
  const Posting ComptaObj::convert_posting_currency(const Posting &source,const Currency::Currency &trg) const
  {
    Posting post(-source);
    Money money_trgt(trg);

    std::vector<std::string> tmp;
    SplitString(post.description()," ", tmp, false);

    for(unsigned int i = 1; i < tmp.size(); i++)
    {
      if(money_trgt.str_money() == tmp[i])
      {
        post.set_amount(-std::atof(tmp[i-1].c_str()) * std::abs(post.amount())/post.amount());
        break;
      }
    }

    return post;

  }


  template<typename Ac>
  inline
  void ComptaObj::add_posting(Posting &post, std::vector<Ac> &target, std::map<std::string,unsigned int> &map,
                              const std::string &decl, std::vector<std::string> &out)
  {
        if(out.size() == 1)
        {
           target[0].add_posting(post);
        }else if(out.size() == 2)
        {
           shave_string(out);
           if(!map.count(out[0]) &&
              !map.count(out[1]))
                  compta_reading_error(std::string("I do not have this " + decl + " account:\n\"" + out[0] + "\" or \"" + out[1] + "\"" + "\n" + FilesParsing::error_message));
           unsigned int where = (map.count(out[0]))?0:1;
           post.set_description(out[1-where]);
           target[where].add_posting(post);
        }else
        {
           compta_reading_error(std::string("I don't understand this posting description:\n" + post.description() + "\n" + FilesParsing::error_message));
        }
   }

   inline
   void ComptaObj::report(std::ostream &out) const
   {
       out << std::setprecision(2) << std::fixed;
       Money bifton(_previsionnel.currency());
       out << "\n\nRapport de la comptabilité << " << _title << " >>\n" <<  std::endl;

       out << "Forecast" << std::endl
           << "  le forecast contient "              << _previsionnel.forecast().n_objects() << " catégories," << std::endl
           << "  la limite globale mensualisée est " << _previsionnel.forecast().amount()    << " " << bifton.str_money() << " "
           << "plus ou moins "                       << _previsionnel.forecast().margin()    << " " << bifton.str_money() << std::endl;

      out << "\nBanque"; 
      if(_banque.size() > 1)out << "s";
      out << std::endl;
      for(unsigned int ib = 0; ib < _banque.size(); ib++)
      {
          bifton.set_money(_banque[ib].currency());
          out << " * compte : "        << _banque[ib].name()                                                  << std::endl
              << "\tétat du compte : " << _banque[ib].records().current_state()  << " " << bifton.str_money() << std::endl
              << "\tétat attendu : "   << _banque[ib].records().expected_state() << " " << bifton.str_money() << std::endl;
          if(!_banque[ib].records().in_waiting().empty())
          {
             for(unsigned int ie = 0; ie < _banque[ib].records().in_waiting().size(); ie++)
             {
                 out << "\t  +++ " << _banque[ib].records().in_waiting()[ie] << " " << bifton.str_money() << std::endl;
             }
          }
          if(!_banque[ib].savings().empty())
          {
             out << std::endl;
             for(unsigned int is = 0; is < _banque[ib].savings().size(); is++)
             {
                out << "\t** épargne "            << _banque[ib].savings_list()[is]                                          << std::endl
                    << "\t\tétat de l'épargne : " << _banque[ib].savings()[is].current_state()  << " " << bifton.str_money() << std::endl
                    << "\t\tétat attendu : "      << _banque[ib].savings()[is].expected_state() << " " << bifton.str_money() << std::endl;
             }
          }else
          {
             out << "Il n'y a pas d'épargne associée à ce compte." << std::endl;
          }
          out << std::endl;
      }

      out << "Liquide"; 
      if(_liquide.size() > 1)out << "s";
      out << std::endl;
      for(unsigned int ic = 0; ic < _liquide.size(); ic++)
      {
          bifton.set_money(_liquide[ic].currency());
          out << " * liquide : " << _liquide[ic].name() << std::endl
              << "\tétat du compte : " << _liquide[ic].records().current_state()  << " " << bifton.str_money() << std::endl
              << "\tétat attendu : "   << _liquide[ic].records().expected_state() << " " << bifton.str_money() << std::endl;
          out << std::endl;
          if(!_liquide[ic].records().in_waiting().empty())
          {
             for(unsigned int ie = 0; ie < _liquide[ic].records().in_waiting().size(); ie++)
             {
                 out << "\t  +++ " << _liquide[ic].records().in_waiting()[ie] << " " << bifton.str_money() << std::endl;
             }
          }
      }
   }

  inline
  void ComptaObj::report_compta(std::vector<MonthlyReport> &rep) const
  {
    // no need for nothing in this case
    if(_banque.empty() && _liquide.empty())return;

    Date cur_date;
    if(!_banque.empty()  && !_banque[0].records().empty())cur_date = _banque[0].records().start_date();
    if(!_liquide.empty() && !_liquide[0].records().empty())
        if(_liquide[0].records().start_date() < cur_date)cur_date = _liquide[0].records().start_date();

    Date end_date;
    if(!_banque.empty()  && !_banque[0].records().empty())end_date = _banque[0].records().end_date();
    if(!_liquide.empty() && !_liquide[0].records().empty())
        if(_liquide[0].records().end_date() > end_date)end_date = _liquide[0].records().end_date();

    while(cur_date <= end_date)
    {
       MonthlyReport month_report(_previsionnel,cur_date);
       this->report_compta(month_report);
       rep.push_back(month_report);
       unsigned int mon = cur_date.month() + 1;
       unsigned int yea = cur_date.year();
       if(mon > 12)
       {
          mon = 1;
          yea++;
       }
       cur_date.set_date(1,mon,yea);
    }

    return;
  }

  inline
  void ComptaObj::report_compta(MonthlyReport &rep) const
  {
     std::vector<Posting> b_history,b_in_waiting;

     if(!_banque.empty())
     {
       _banque[0].records().history_of_month(rep.date(),b_history); //adds bank history
       _banque[0].records().in_waiting_of_month(rep.date(),b_in_waiting);//adds bank in waiting
     }


     std::vector<Posting> c_history,c_in_waiting;
     if(!_liquide.empty())
     {
       _liquide[0].records().history_of_month(rep.date(),c_history);//adds cash history
       _liquide[0].records().in_waiting_of_month(rep.date(),c_in_waiting);//adds cash in waiting
     }

     rep.add_posting(b_history);
     rep.add_posting(c_history);
     rep.add_posting(b_in_waiting);
     rep.add_posting(c_in_waiting);

     return;
  }

}

#endif
