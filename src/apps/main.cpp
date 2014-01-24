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

#include "compta/compta_obj.hpp"
#include "compta/read_compta_input_file.hpp"
#include "compta/latex_factory.hpp"

int main(int argc, char ** argv)
{
 unsigned int iforecast(1);
 unsigned int iaccounts(1);
 unsigned int idata(1);
 unsigned int itex(1);

 if(argc != 2 && argc != 3 && argc != 5)
 {
    std::cerr << "\n\n***********************************************" << std::endl;
    std::cerr << "Program usage:" << std::endl
              << "compta forecast_file accounts_file data_file latex_file" << std::endl
              << " or " << std::endl
              << "compta global_file latex_file" << std::endl
              << " or " << std::endl
              << "compta global_file" << std::endl;
    std::cerr << "***********************************************\n\n" << std::endl;
    compta_error();
 }
 if(argc == 5)
 {
   iaccounts = 2;
   idata = 3;
   itex = 4;
 }else if(argc == 3)
 {
   itex = 2;
 }

 Compta::ComptaObj compte;

 Compta::parse_input_file(compte,argv[iforecast],argv[iaccounts],argv[idata]);

 compte.report();

 Compta::latex_report(compte,std::string(argv[itex]));

 return 0;
}
