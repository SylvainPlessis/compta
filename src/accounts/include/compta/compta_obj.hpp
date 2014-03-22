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
      void add_posting(const Posting &post, const char &identifier);

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
      void add_posting(const Posting &post, std::vector<Ac> &target, std::map<std::string,unsigned int> &map,
                       const std::string &decl, std::vector<std::string> &out);

      void add_transfert(Posting &post, const std::vector<std::string> &out);

      void find_src_and_trg(unsigned int &n_end, std::vector<std::vector<int> > & ends, const std::vector<std::string> > &out) const;

      void check_src_and_trg(int &src, int &trg, const std::vector<std::string> > &out, const std::map<std::string, unsigned int> &cur_map) const;

      const Posting convert_posting_currency(const Posting &source,unsigned int bansrc) const;

      void add_posting(unsigned int counter, const std::vector<std::vector<unsigned int> > & corres, const Posting &post);

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
       if(_title != title)compta_reading_error(std::string("Different titles are given for the same comptability."));
    }
  }

  inline
  void ComptaObj::add_posting(const Posting &post, const char &identifier)
  {
     if(!DataParsing::posting_type_map().count(identifier))
                compta_reading_error(std::string("This identifier is not supported: " + identifier));
     post.set_identifier(DataParsing::posting_type_map().at(identifier));

     std::vector<std::string> out;
     SplitString(post.description(),DataParsing::delimiter(), out, false);
     if(out.empty())out.push_back(post.description());
     if(identifier == DataParsing::bank_str())
     {
         this->add_posting(post, this->_banque, this->_banque_map, "bank", out);
     }else if(identifier == DataParsing::cash_str())
     {
         this->add_posting(post, this->_liquide, this->_liquide_map, "cash", out);
     }else if(identifier == DataParsing::transfer_str())
     {
     }else //end transfert
     {
        shave_string(out);
        this->add_transfert(post,out);
        compta_error();
     }
  }

  inline
  void ComptaObject::add_transfert(Posting &post, const std::vector<std::string> &out)
  {      
        int bansrc(-1),bantrgt(-1);
        int epasrc(-1);
        int cassrc(-1),castrgt(-1);
        unsigned int n_end(0);
        std::vector< std::vector<int> > ends; //[src|trg][ban|epa|cas]
        ends.resize(2); //[src|trg]
        ends[0].resize(3,-1);//[src][ban|epa|cas]
        ends[0].resize(3,-1);//[trg][ban|epa|cas]

        this->find_src_and_trg(n_end,ends,out);

        this->add_posting(n_end,ends,post);

  }

  void ComptaObject::check_src_and_trg(int &src, int &trg,
                                       const std::vector<std::string> > &out, 
                                       const std::map<std::string, unsigned int> &cur_map) const
  {
    for(unsigned int i = 0; i < out.size(); i++)
    {
      if(cur_map.count(out[i])) //bank and bank
      {
        if(src == -1) 
        {
          src = (int)cur_map.at(out[i]);
        }else
        {
          trg = (int)cur_map.at(out[i]);
        }
      }
    }

    return; 
  }

  void ComptaObject::find_src_and_trg(unsigned int &n_ends, std::vector<std::vector<int> > & ends, const std::vector<std::string> > &out) const
  {

    unsigned int src(0),trg(1);
    unsigned int ban(0),epa(1),cas(2);

// is there a bank?
    this->check_src_and_trg(ends[src][ban],ends[trg][ban],out,_banque_map);
// is there a cash
    this->check_src_and_trg(ends[src][cas],ends[trg][cas],out,_liquide_map);

// if there's a bank, is there a savings?
// weak form, we do not check if there's already a target
   if(ends[src][ban] < 0) //might be default bank to savings
   {
      this->check_src_and_trg(ends[src][epa],ends[trg][epa],out,_banque.front().savings_map());
   }else //then might be between custom bank and savings
   {
      this->check_src_and_trg(ends[src][epa],ends[trg][epa],out,_banque[ends[src][ban]].savings_map());
   }

   n_ends = 0;
   for(unsigned int i = 0; i < 2; i++) //[src|trg]
   {
     for(unsigned int j = 0; j < 3; j++) //[ban|epa|cas]
     {
        if(ends[i][j] >= 0)n_ends++;
     }
   }

   return;
 }

 inline
 void ComptaObject::add_posting(unsigned int counter, const std::vector<std::vector<unsigned int> > & corres, const Posting &post)
 {
     switch(counter)
     {
       case 0: // counter = 0, from main bank to main cash
       {
         _banque.front().add_posting(post);
         _liquide.front().add_posting(-post);
         break;
       }
       case 1: // counter = 1, from main bank to someone (bank, savings or cash)
       {

         if(corres[0][0] > 0)// from main bank to bank
         {
           _banque[0].add_posting(post);
           _banque[bansrc].add_posting(this->convert_posting_currency(post,corres[0][0]));

         }else if(corres[0][1] >= 0)//from main bank to savings
         {
          _banque[0].add_posting(post,(unsigned int)corres[0][1]);

         }else if(corres[0][2] >= 0)//from main bank to cash
         {
           _banque[0].add_posting(post);
           _liquide[cassrc].add_posting(-post);
         }else//???
         {
           std::cerr << "counter is " << counter << ", what did you do on this line?" << std::endl
                     << post.description() << std::endl;
           compta_error();
          }
          break;

      }
      case 2: // counter = 2, explicit
      {

        if(out.size() > 2) //in case of change of currency, adapted amount is given here
        {
         std::vector<std::string> tmp;
         Money money_trgt(_banque[bantrgt].currency());
         SplitString(post.description()," ", tmp, false);
         for(unsigned int i = 1; i < tmp.size(); i++)
         {
           if(money_trgt.str_money() == tmp[i])
           {
             converted_amount = -std::atof(tmp[i-1].c_str()) * std::abs(post.amount())/post.amount();
             break;
           }
         }
        }
        if(bansrc != -1 && epasrc != -1)//bank to bank_savings
        {
          _banque[bansrc].add_posting(post,(unsigned int)epasrc); 
        }else if(bansrc != -1 && bantrgt != -1)//bank to bank
        {
          _banque[bansrc].add_posting(post);
          post.set_amount(converted_amount);
          _banque[bantrgt].add_posting(post);
        }else if(bansrc != -1 && cassrc != -1)//bank to cash
        {
         _banque[bansrc].add_posting(post);
         post.set_amount(converted_amount);
         _liquide[cassrc].add_posting(post);
        }else if(cassrc != -1 && castrgt != -1)//cash to cash, no real sense...
        {
         _liquide[cassrc].add_posting(post);
         post.set_amount(converted_amount);
         _liquide[cassrc].add_posting(post);
        }else//???
        {
         compta_error();
        }
       break;
      }
      default:
      {
       compta_error();
      }
    }//end switch
  }

  inline
  const Posting ComptaObject::convert_posting_currency(const Posting &source,unsigned int bansrc) const
  {
    Posting post(source);
    Money money_trgt(_banque[bansrc].currency());

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
                  compta_reading_error(std::string("I do not have this " + decl + " account:\n\t" + out[0] + "\nor\n\t" + out[1]));
           unsigned int where = (map.count(out[0]))?0:1;
           post.set_description(out[1-where]);
           target[where].add_posting(post);
        }else
        {
           compta_reading_error(std::string("I don't understand this posting description:\n" + post.description()));
        }
   }

   inline
   void ComptaObj::report(std::ostream &out) const
   {
       out << std::setprecision(2) << std::fixed;
       Money bifton(_previsionnel.currency());
       out << "\n\nRapport de la comptabilité << " << _title << " >>\n" <<  std::endl;

       out << "Forecast" << std::endl
           << "  le forecast contient "  << _previsionnel.forecast().n_objects() << " catégories," << std::endl
           << "  la limite globale est " << _previsionnel.forecast().amount()    << " " << bifton.str_money() << " "
                << "plus ou moins "         << _previsionnel.forecast().margin()    << " " << bifton.str_money() << std::endl;

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
      }
   }

  inline
  void ComptaObj::report_compta(std::vector<MonthlyReport> &rep) const
  {
    // no need for nothing in this case
    if(_banque.empty() && _liquide.empty())return;

    Date cur_date;
    if(!_banque.empty() && !_banque[0].records().empty())cur_date = _banque[0].records().start_date();
    if(!_liquide.empty() && !_liquide[0].records().empty())
        if(_liquide[0].records().start_date() < cur_date)cur_date = _liquide[0].records().start_date();

    Date end_date;
    if(!_banque.empty() && !_banque[0].records().empty())end_date = _banque[0].records().end_date();
    if(!_liquide.empty() && !_liquide[0].records().empty())
        if(_liquide[0].records().end_date() > end_date)end_date = _liquide[0].records().end_date();

    while(cur_date < end_date)
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
