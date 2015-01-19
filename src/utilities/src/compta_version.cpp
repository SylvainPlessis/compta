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
#include "compta/compta_version.hpp"

namespace Compta{


  void compta_version_stdout()
  {
    compta_version(std::cout).flush();
  }

  int get_compta_version()
  {
    /* Note: return format follows the versioning convention xx.yy.zz where

       xx = major version number
       yy = minor version number
       zz = micro version number

       For example:
       v.   0.23  -> 002300 = 2300
       v   0.23.1 -> 002301 = 2301
       v. 10.23.2 -> 102302         */

    int major_version = 0;
    int minor_version = 0;
    int micro_version = 0;

#ifdef COMPTA_MAJOR_VERSION
    major_version = COMPTA_MAJOR_VERSION;
#endif

#ifdef COMPTA_MINOR_VERSION
    minor_version = COMPTA_MINOR_VERSION;
#endif

#ifdef COMPTA_MICRO_VERSION
    micro_version = COMPTA_MICRO_VERSION;
#endif

    return major_version*10000 + minor_version*100 + micro_version;
  }

}
