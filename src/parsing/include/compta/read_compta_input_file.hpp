//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//-----------------------------------------------------------------------el-

#ifndef COMPTA_READ_INPUT_FILE_H
#define COMPTA_READ_INPUT_FILE_H

//Compta
#include "compta/compta_obj.hpp"
#include "compta/parsing_def.hpp"
#include "compta/string_utils.hpp"

//C++
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cmath>

namespace Compta{

  void read_forecast(Forecast & forecast,
                        const std::string &file);

  void read_accounts(ComptaObj &compte,
                        const std::string &file);

  void read_data(ComptaObj &compte,
                        const std::string &file);

///////////////////////////////////
/// inline functions
///////////////////////////////////

  inline 
  void parse_input_file(ComptaObj & compte,
                        const std::string &forecast_file,
                        const std::string &accounts_file,
                        const std::string &data_file)
  {

//The first category to be parsed is the forecast
      Forecast forecast;
      read_forecast(forecast,forecast_file);
      compte.set_forecast(forecast);

//Then the accounts description
      read_accounts(compte,accounts_file);

//Finally the data
      read_data(compte,data_file);
  }

  inline
  void read_forecast(Forecast & forecast,
                        const std::string &file)
  {
      std::ifstream data(file.c_str());
      if(!data.is_open())compta_file_error(file);
      std::string line;
      if(!getline(data,line))compta_error();
      if(!getline(data,line))compta_error();
      shave_string(line);
      Money money(line);
      forecast.set_currency(money.money());

      while(!data.eof())
      {
          getline(data,line);
          if(line.empty())continue;
          if(line[0] == '#')continue;
          std::string first_word;
          shave_string(line);
          std::stringstream datass(line);
          datass >> first_word;
          std::streampos  fwp = datass.tellg();
          if(first_word != ForecastParsing::forecast())continue; // not forecast

          line.erase(0,first_word.size());
// the line is  "Category" "Amount" "Margin" "subcat","automatic","start","end", "period"
// from subcat all is optional: "cat", "not automatic", "date_min", "date_max", "1"

          std::string cat, desc;
          float amount, margin;
          datass >> cat >> amount >> margin;
          line.erase(0,datass.tellg() - fwp);

          shave_string(line);
          desc = line;
          if(desc.empty())desc = cat;
          std::vector<std::string> out;
          SplitString(desc,ForecastParsing::delimiter(),out,true);
          unsigned int nstr = out.size();
          if(nstr == 0)out.push_back(desc);
          if(out.size() > 5)compta_reading_error("Error in forecast, this part is not well defined\n" + desc);

          shave_string(out);
          std::string name_op = out[0];
          bool au(false);   
          Date date_start(DateUtils::date_min());
          Date date_end(DateUtils::date_max());
          unsigned int period(1);
          if(out.size() > 1)au = (out[1] == ForecastParsing::automatic());
          if(out.size() > 2)date_start.set_date(out[2]);
          if(out.size() > 3)date_end.set_date(out[3]);
          if(out.size() > 4)period = (unsigned int)(std::atof(out[4].c_str()));

          //building the operation now
          Operation new_op(name_op,amount,margin,au,date_start,date_end,period);
          //if we don't have the category, we build it
          if(!forecast.forecast().operations_map().count(cat)) //building
          {
              ForecastCategory new_cat(cat);
              forecast.add_forecast_category(new_cat);
          }
          //now we add the operation
          forecast.add_operation(cat,new_op);
       }
       data.close();

  }

  inline
  void read_accounts(ComptaObj &compte,
                        const std::string &file)
  {
      std::ifstream data(file.c_str());
      if(!data.is_open())compta_file_error(file);
      std::string line;
      if(!getline(data,line))compta_error();
      shave_string(line);
      compte.set_title(line);
      if(!getline(data,line))compta_error();
      shave_string(line);
      Money money(line);
      Currency::Currency default_currency(money.money());

      while(!data.eof())
      {
          std::string first_word;
          data >> first_word;
          if(first_word.length() == 0)continue; //empty line
          if(first_word[0] == '#')
          {
             getline(data,line);
             continue;
          }

          if(first_word != AccountsParsing::bank() &&
             first_word != AccountsParsing::cash() &&
             first_word != AccountsParsing::savings())
          {
             getline(data,line);
             continue;
          }

//line is  "Account"       "dependance"         "amount"  "start_date"   "name"            , "currency (if different)"
          Money current_money;
          std::string dependance,name,currency;
          Date start_date;
          float amount;

          data >> dependance >> amount >> start_date;
          getline(data,name);
          shave_string(name);
          std::vector<std::string> out;
          int nstr = SplitString(name,AccountsParsing::delimiter(),out,false);
          if(nstr == 0)out.push_back(name);
          if(out.size() > 2)
          {
              compta_reading_error("I don't understand this account description:\n" + name);
          }
          if(out.size() != 0)name = out[0];
          shave_string(name);
          if(out.size() == 2)
          {
            currency = out[1];
            shave_string(currency);
            current_money.set_money(currency);
          }

          if(first_word == AccountsParsing::bank())
          {
             Bank bank(name,start_date,amount);
             (currency.empty())?bank.set_currency(default_currency):
                                bank.set_currency(current_money.money());
             compte.add_bank_account(bank,(dependance == AccountsParsing::chooser()));
                
          }else if(first_word == AccountsParsing::cash())
          {
             Cash cash(name,start_date,amount);
             (currency.empty())?cash.set_currency(default_currency):
                                cash.set_currency(current_money.money());
             compte.add_cash_account(cash,(dependance == AccountsParsing::chooser()));

          }else if(first_word == AccountsParsing::savings())
          {
             Savings saving;
             saving.add_posting(Posting("creation",start_date,"creation",amount,true));
             compte.add_savings_account(saving,name,dependance);
          }
      }
      data.close();
  }

  inline
  void read_data(ComptaObj &compte,
                        const std::string &file)
  {
      std::ifstream data(file.c_str());
      if(!data.is_open())compta_file_error(file);
      std::string line;
      if(!getline(data,line))compta_error();
      shave_string(line);
      compte.set_title(line);
      if(!getline(data,line))compta_error();
      while(!data.eof())
      {
          std::string first_word;
          data >> first_word;
          if(first_word.length() == 0)continue; //empty line
          if(first_word[0] == '#')
          {
             getline(data,line);
             continue; // comment
          }
          if(first_word.find("/") == std::string::npos)
          {
             getline(data,line);
             continue;
          }

//line is "category" "debit" "credit" "identifier" "description"
          std::string cat,id,descr;
          float deb,cred;
          data >> cat >> deb >> cred >> id;
          getline(data,descr);
          shave_string(descr);
//formatting tests
          if(cred != 0. && deb != 0.) //one operation at a time
                compta_reading_error("Debit and credit cannot be both non zero");
          if(id.size() > 2) //identifier format
                compta_reading_error("Identifier should be one or two character(s)");
          if(cred < 0. || deb < 0.)
          {
              std::cerr << "Negative amounts are permitted, but are ridiculous...\n"
                        << "Note that a negative credit is a debit, and a negative debit is a credit, "
                        << "who needs negative numbers?" << std::endl;
          }
//
          Date date_post;
          date_post.set_date(first_word);
          char identifier = id[0];
          float amount = (cred > deb)?cred:-deb;
          bool accounted = !(id.size() == 2);
          Posting post(cat,date_post,descr,amount,accounted);
          if(!DataParsing::posting_type_map().count(identifier))
                compta_reading_error(std::string("This identifier is not supported: " + identifier));
          post.set_identifier(DataParsing::posting_type_map().at(identifier));
          compte.add_posting(post);
      }
      data.close();
  }

}

#endif
