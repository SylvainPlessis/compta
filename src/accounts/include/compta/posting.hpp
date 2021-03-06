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

#ifndef COMPTA_POSTING_H
#define COMPTA_POSTING_H

//Compta
#include "compta/date.hpp"
#include "compta/posting_enum.hpp"
#include "compta/parsing_def.hpp"
#include "compta/operation.hpp"

//C++
#include <map>
#include <string>

namespace Compta{

  class Posting{
     public:
        Posting();
        Posting(const std::string &cat, const Date &date, const std::string &desc, 
                const float amount, bool acc=true, const PostingType::PostingType &id = PostingType::B);
        Posting(const Posting &rhs);
        ~Posting();

        //!sets the category
        void set_category(const std::string &category);
        //!sets the date
        void set_date(const Date &date);
        //!sets the description
        void set_description(const std::string &description);
        //!sets the amount
        void set_amount(float amount);
        //!sets the accounted state
        void set_accounted(bool acc);
        //!sets the identifiers
        void set_identifier(const PostingType::PostingType &identifier);

        //!\return the category
        const std::string category() const;
        //!\return the date
        const Date date() const;
        //!\return the description
        const std::string description() const;
        //!\return the amount
        const float amount() const;
        //!\return the accounted state
        bool accounted() const;
        //!\return the identifier
        const PostingType::PostingType identifier() const;

        //! prints the posting in human form
        void print(std::ostream& out = std::cout) const;

        //! Formatted print.
        friend std::ostream& operator << (std::ostream& os, const Posting &line)
        {
          line.print(os);
          return os;
        }

        //! Minus
        Posting operator-() const;

        //! operator
        Posting &operator=(const Posting &rhs);

        //! comparison to a forecast Operation
        bool operator==(const Operation &op) const;


     private:
        std::string _category;
        Date _date;
        std::string _description;
        float _amount;
        bool _accounted;
        PostingType::PostingType _identifier;
  };

}

#endif
