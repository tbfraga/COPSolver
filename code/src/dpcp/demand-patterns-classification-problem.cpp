/*********************************************************************** LICENSE ********************************************************************************************
Important: Copies and distributions of this file must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.

******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// module: COPSolver: library for solving the demand pattern classification problem
// version: vdpc_dpc.0-1
// developed by Tatiana Balbi Fraga
// start date: 2023/11/08
// last modification: 2023/12/26

#include "../../lib/dpcp/demand-patterns-classification-problem.h"

namespace dpc
{
    void dpcp::clear()
    {
        _problem.clear();
        _solution.clear();
    };

    bool dpcp::get()
    {
        string file_address = getenv("HOME");
        file_address += "/COPSolver/data/data.txt";

        fstream file;
        file.open(file_address);

        if(!file)
        {
            cerr << "File " << file_address << " not oppened !" << endl;
            return 0;
        } else
        {
            file >> _problem;
        }

        file.close();

        return 1;
    };

    bool dpcp::williams()
    {
        cout << endl << "applying williams method for demand pattern classification ... " << endl;

        if (!get())
        {
            cout << endl << "Sorry, it was not possible to take the problem, Willians's method won't be applied !!!" << endl;
            return 0;
        } else
        {
            string file_address = getenv("HOME");
            file_address += "/COPSolver/results/williams_solution.txt";

            fstream file;

            _solution.williams(_problem);

            file.open(file_address, ios::out);

            if(!file)
            {
                cerr << "File " << file_address << " not created !" << endl;
                return 0;
            } else
            {
                file << _solution;
            }

            file.close();

            return 1;
        }
    };
}
