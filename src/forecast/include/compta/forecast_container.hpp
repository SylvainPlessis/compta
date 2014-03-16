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

#ifndef COMPTA_FORECAST_CONTAINER_H
#define COMPTA_FORECAST_CONTAINER_H

//Compta
#include "compta/operation.hpp"

//C++
#include <vector>
#include <string>
#include <map>

namespace Compta{

  /*!\class ForecastConstainer

      This templated class contains categories, which makes
      it to be used at the two needed levels of the forecast,
      one level containing a ForecastContainer, another containing
      Operation.

      This class needs to be able to cope with all the needed operations
      of the forecast, categories and sub-categories. So it needs
      to be able to send the amount and margin at each month, for each
      category and each operation, depending on the level asked.
   */
  template <typename Containee>
  class ForecastContainer{
        public:
          ForecastContainer();
          ForecastContainer(const std::string &name);
          ForecastContainer(const ForecastContainer<Containee> &rhs);
          ~ForecastContainer();

          //!
          void add_operation(const Containee &op);

          //!\return the operations map
          const std::map<std::string,unsigned int> operations_map() const; 
          //!\return the operations list
          const std::vector<Containee> operations_list() const; 
          //!\return the name of the category
          const std::string name() const; 
          //!\return the amount
          float amount() const; 
          //!\return the margin
          float margin() const; 

          //!\return the amount of the asked month
          float amount_this_month(unsigned int date) const;
          //!\return the margin of the asked month
          float margin_this_month(unsigned int date) const;

        

          //!\return the number of operations
          unsigned int n_objects() const;

          //!recalculates the amount
          void update_amount();

          //!\return writable operation
          Containee &operation(const std::string &name_operation);

          //!\return const ref to operation
          const Containee &operation(const std::string &name_operation) const;

          //!add expected operations of given month to the vector
          void expected_operations(unsigned int month, std::vector<const Operation*> &op) const;

          //!sets the margin
          void set_margin(float margin);

          //!sets the name
          void set_name(const std::string &name);

          //!Operator
          ForecastContainer<Containee> &operator=(const ForecastContainer<Containee> &rhs);

        private:


          std::string _name;
          std::vector<Containee> _operations_list;
          std::map<std::string,unsigned int> _operations_map;
          float _amount;
          float _margin;
  };

  template <typename Containee>
  inline
  ForecastContainer<Containee>::ForecastContainer():
     _amount(0.),
     _margin(0.)
  {
     return;
  }

  template <typename Containee>
  inline
  ForecastContainer<Containee>::ForecastContainer(const std::string &name):
     _amount(0.),
     _margin(0.)
  {
     _name = name;
     return;
  }

  template <typename Containee>
  inline
  ForecastContainer<Containee>::ForecastContainer(const ForecastContainer<Containee> &rhs)
  {
     *this = rhs;
  }

  template <typename Containee>
  inline
  ForecastContainer<Containee> &ForecastContainer<Containee>::operator=(const ForecastContainer<Containee> &rhs)
  {
     if(this != &rhs)
     {
       _name = rhs.name(); 
       _operations_list = rhs.operations_list();
       _operations_map = rhs.operations_map();
       _amount = rhs.amount();
       _margin = rhs.margin();
     }
     return *this;
  }

  template <typename Containee>
  inline
  ForecastContainer<Containee>::~ForecastContainer()
  {
    return;
  }

  template <typename Containee>
  inline
  void ForecastContainer<Containee>::add_operation(const Containee &op)
  {
     _operations_list.push_back(op);
     _amount += op.amount();
     _margin += op.margin();
     _operations_map[op.name()] = _operations_list.size() - 1;
  }

  template <typename Containee>
  inline
  Containee &ForecastContainer<Containee>::operation(const std::string &name_operation)
  {
     return _operations_list[_operations_map.at(name_operation)];
  }

  template <typename Containee>
  inline
  const Containee &ForecastContainer<Containee>::operation(const std::string &name_operation) const
  {
     return _operations_list[_operations_map.at(name_operation)];
  }

  template <typename Containee>
  inline
  unsigned int ForecastContainer<Containee>::n_objects() const
  {
     return _operations_list.size();
  }

  template <typename Containee>
  inline
  const std::map<std::string,unsigned int> ForecastContainer<Containee>::operations_map() const
  {
     return _operations_map;
  }

  template <typename Containee>
  inline
  const std::vector<Containee> ForecastContainer<Containee>::operations_list() const
  {
     return _operations_list;
  }

  template <typename Containee>
  inline
  const std::string ForecastContainer<Containee>::name() const
  {
     return _name;
  }

  template <typename Containee>
  inline
  float ForecastContainer<Containee>::amount() const
  {
     return _amount;
  }

  template <typename Containee>
  inline
  float ForecastContainer<Containee>::amount_this_month(unsigned int date) const
  {
     float this_month_amount(0.L);
     for(unsigned int iop = 0; iop < _operations_list.size(); iop++)
     {
        this_month_amount += _operations_list[iop].amount_this_month(date);
     }
     return this_month_amount;
  }

  template <typename Containee>
  inline
  float ForecastContainer<Containee>::margin_this_month(unsigned int date) const
  {
     float this_month_margin(0.L);
     for(unsigned int iop = 0; iop < _operations_list.size(); iop++)
     {
        this_month_margin += _operations_list[iop].margin_this_month(date);
     }
     return this_month_margin;
  }

  template <typename Containee>
  inline
  float ForecastContainer<Containee>::margin() const
  {
     return _margin;
  }

  template <typename Containee>
  inline
  void ForecastContainer<Containee>::set_margin(float margin)
  {
     _margin = margin;
  }

  template <typename Containee>
  inline
  void ForecastContainer<Containee>::set_name(const std::string &name)
  {
     _name = name;
  }

  template <typename Containee>
  inline
  void ForecastContainer<Containee>::update_amount()
  {
     _amount = 0.;
     for(unsigned int i = 0; i < _operations_list.size(); i++)
     {
       _amount += _operations_list[i].amount();
     }
  }

  template <typename Containee>
  inline
  void ForecastContainer<Containee>::expected_operations(unsigned int month, std::vector<const Operation*> &op) const
  {
     for(unsigned int ic = 0; ic < _operations_list.size(); ic++)
     {
        _operations_list[ic].expected_operations(month,op);
     }
  }

}

#endif
