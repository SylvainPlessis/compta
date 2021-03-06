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

// Compta
#include "compta/string_utils.hpp"
#include "compta/static_error_variables.hpp"

// C++
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

namespace Compta
{
  
  bool check_BOM(const char* p)
  {
    const unsigned char* pu = reinterpret_cast<const unsigned char*>(p);
    if( *(pu+0) == 0xefU &&
        *(pu+1) == 0xbbU && 
        *(pu+2) == 0xbfU)//BOM found
    {
        return true;
    }
    return false;
  }

  void shave_string(std::string &str)
  {
    //suppress BOM, if any
    if(check_BOM( &(str[0]) ))str.erase(0,3);

    // Trim from the left
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::iscntrl))));

    // Trim from the right
    str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::iscntrl))).base(), str.end());

    // Trim from the left
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));

    // Trim from the right
    str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());

  }


  void shave_string(std::vector<std::string> &customer)
  {
     for(unsigned int i = 0; i < customer.size(); i++)
     {
       shave_string(customer[i]);
     }
  }

  int SplitString(const std::string& input, 
		  const std::string& delimiter, 
		  std::vector<std::string>& results, 
		  bool includeEmpties)
  {
    using std::vector;
    using std::string;
    
    int iPos = 0;
    int newPos = -1;
    int sizeS2 = (int)delimiter.size();
    int isize = (int)input.size();
    
    if( 
       ( isize == 0 )
       ||
       ( sizeS2 == 0 )
	)
      {
	return 0;
      }

    vector<int> positions;

    newPos = input.find (delimiter, 0);

    if( newPos < 0 )
      { 
	return 0; 
      }

    int numFound = 0;

    while( newPos >= iPos )
      {
	numFound++;
	positions.push_back(newPos);
	iPos = newPos;
	newPos = input.find (delimiter, iPos+sizeS2);
      }

    if( numFound == 0 )
      {
	return 0;
      }

    for( int i=0; i <= static_cast<int>(positions.size()); ++i )
      {
	string s("");
	if( i == 0 ) 
	  { 
	    s = input.substr( i, positions[i] ); 
	  }
	else
	  {
	    int offset = positions[i-1] + sizeS2;
	    if( offset < isize )
	      {
		if( i == static_cast<int>(positions.size()) )
		  {
		    s = input.substr(offset);
		  }
		else if( i > 0 )
		  {
		    s = input.substr( positions[i-1] + sizeS2, 
				      positions[i] - positions[i-1] - sizeS2 );
		  }
	      }
	  }
	if( includeEmpties || ( s.size() > 0 ) )
	  {
	    results.push_back(s);
	  }
      }
    return numFound;
  }

  int ascii_getline(std::istream & buf, std::string & line)
  {
     line = "Couldn't parse this line...";

     if(buf.good())
     {
       char c('a');
       line.clear();
       while(!buf.eof())
       {
          c = buf.get();
          if(c == '\n' || c == '\r')break;
          line += c;
       }
       char n = buf.peek();
     /* never trust ascii files, they may come from
        Windows, suppodedly \n\r, but let's not
        underestimate Windows's viciousness
      */
       if((c == '\n' && n == '\r') ||
          (n == '\n' && c == '\r')){
         c = buf.get();
      }
     }

     FilesParsing::add_current_line();
     FilesParsing::set_raw_line(line);

     return buf.good() || buf.eof();
  }

} // end namespace Compta
