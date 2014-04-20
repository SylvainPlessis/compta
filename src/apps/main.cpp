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

#include "compta/compta_options.hpp"
#include "compta/read_compta_input_file.hpp"

int main(int argc, char ** argv)
{
 Compta::ComptaOptions options(argc,argv);

 if(!options.valid())
 {
    std::cerr << "\n\n***********************************************" << std::endl;
    std::cerr << "Program usage:" << std::endl
              << "compta [options] forecast_file accounts_file data_file latex_file" << std::endl
              << " or " << std::endl
              << "compta [options] global_file latex_file" << std::endl
              << " or " << std::endl
              << "compta [options] global_file" << std::endl;
    std::cerr << "***********************************************\n\n" << std::endl;
    compta_error();
 }

 Compta::ComptaObj compte;

 Compta::parse_input_file(compte,options.forecast_file(),options.accounts_file(),options.data_file());

 options.report(compta);

 return 0;
}
