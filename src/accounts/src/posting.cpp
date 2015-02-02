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

// this class
#include "compta/posting.hpp"

// C++
#include <iomanip>

namespace Compta
{

  
  Posting::Posting():
        _amount(0.),
        _accounted(true),
        _identifier(PostingType::B)
  {
    return;
  }

  
  Posting::Posting(const Posting &rhs)
  {
    *this = rhs;
  }

  
  Posting &Posting::operator=(const Posting &rhs)
  {
    if(this != &rhs)
    {
      _category    = rhs.category();
      _date        = rhs.date();
      _description = rhs.description();
      _amount      = rhs.amount();
      _accounted   = rhs.accounted();
      _identifier  = rhs.identifier();
    }
    return *this;
  }

  
  Posting::Posting(const std::string &cat, const Date &date, const std::string &desc, 
                   const float amount, bool acc, const PostingType::PostingType &id):
        _category(cat),
        _date(date),
        _description(desc),
        _amount(amount),
        _accounted(acc),
        _identifier(id)
  {
    return;
  }

  
  Posting::~Posting()
  {
    return;
  }

  
  void Posting::set_category(const std::string &category)
  {
     _category = category;
  }

  
  void Posting::set_date(const Date &date)
  {
     _date = date;
  }

  
  void Posting::set_description(const std::string &description)
  {
     _description = description;
  }

  
  void Posting::set_amount(float amount)
  {
     _amount = amount;
  }

  
  void Posting::set_accounted(bool acc)
  {
     _accounted = acc;
  }

  
  void Posting::set_identifier(const PostingType::PostingType &identifier)
  {
     _identifier = identifier;
  }

  
  const std::string Posting::category() const
  {
     return _category;
  }

  
  const Date Posting::date() const
  {
     return _date;
  }

  
  const std::string Posting::description() const
  {
     return _description;
  }

  
  const float Posting::amount() const
  {
     return _amount;
  }

  
  bool Posting::accounted() const
  {
     return _accounted;
  }

  
  const PostingType::PostingType Posting::identifier() const
  {
     return _identifier;
  }

  
  void Posting::print(std::ostream& out) const
  {
      out.setf(std::ios::left, std::ios::adjustfield);
      out << std::setw(15)
          << _category    << ", le "
          << _date        << ",    "
          << std::setw(10) 
          << _amount      << " "
          << _description;
  }

  
  Posting Posting::operator-() const
  {
     return Posting(this->category(), this->date(), this->description(), -this->amount(), this->accounted(), this->identifier());
  }


  
  bool Posting::operator==(const Operation &op) const
  {
      return (_description.find(op.name()) != std::string::npos);
  }


}
