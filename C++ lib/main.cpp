/*********************************************************************** LICENSE **********************************************************************************************
Important: Copies and distributions of this solver must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.
******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// version: 1.0-1_20230825
// developed by Tatiana Balbi Fraga
// start date: 2023/04/26
// last modification: 2023/08/25

#include "lib/multiproduct-batch-processing-time-maximization-problem.h"
using namespace mbptm;

#include <unistd.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

int main()
{
    /**** Multiproduct batch processing time maximization problem ****/

    // For defining a problem you can use one of the tree methods:
    // problemDefinitionMethod = 1 - taking problem from data.txt file
    // problemDefinitionMethod = 2 - taking a predefined problem
    // problemDefinitionMethod = 3 - generating a random problem

    cop _problem;

    unsigned int problemDefinitionMethod = 1;

    cout << "Thaks for using COPSolver :)))" << endl << endl;
    cout << "COPSolver was (and is being) developed by Fraga, T.B. with purpose of solving many differente combinatorial optimizations problems." << endl << endl;
    cout << "This first version, COPSolver_1.0-1, only solves the multi-product batch processing time maximization problem." << endl << endl;
    cout << "COPSolver is licenced by Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0)" << endl << endl;
    cout << "Under this licence you can:" << endl << endl;
    cout << "1) Free dowload and/or use this solver (except for comercial purpose);" << endl;
    cout << "2) Share this solver (if don't modified anyway) only if you inform a link for the original repository and for the license;" << endl;
    cout << "3) Modify the solver for personal use, but not share modified version of solver." << endl << endl;
    cout << "You cannot use COPSolver or any modified version for comercial purpose." << endl;
    cout << "If you need or want to use COPSolver for any comercial purpose, please contact tatiana.balbi@ufpe.br." << endl << endl;
    cout << "If you use this solver for work or science, please don't forget to correctly cite it on presentations and the published material." << endl << endl;
    cout << "repository: github.com/tbfraga/COPSolver" << endl;

    cout << endl << "Please, resize the window (if needed) and press enter." << endl;
    getchar();

    bool doItAgain = 1;

    do
    {
        do
        {
            cout << endl << "Please select the problem definition method." << endl;
            cout << endl << "choose:" << endl << endl;
            cout << "1 for taking the problem from data.txt file;" << endl;
            cout << "2 for using a predefined problem;" << endl;
            cout << "3 for generating a random problem; " << endl;
            cout << "0 if you want to stop the solver." << endl;

            cout << endl << "digite option and then press enter: ";
            cin >> problemDefinitionMethod;

            if(problemDefinitionMethod > 3)
            {
                cout << endl << endl << "atention: please digite 0, 1, 2 or 3 !!!" << endl;
            }
        }while(problemDefinitionMethod > 3);

        if(problemDefinitionMethod == 0)
        {
            cout << endl << "Thanks for using COPSolver !!!";
            cout << endl << "Press enter for closing this window." << endl;
            getchar();
            return 0;
        } else if(problemDefinitionMethod == 1)
        {
            _problem.get();
        } else if(problemDefinitionMethod == 2)
        {
            unsigned int preDefProblem = 1;
            do
            {
                cout << endl << "Please select the predefined problem." << endl;
                cout << endl << "choose:" << endl << endl;
                cout << "1 for taking the MBPTM_02 problem;" << endl;
                cout << "2 for taking the MBPTM_03 problem;" << endl;
                cout << "3 for taking the MBPTM_10 problem; " << endl;
                cout << "0 if you want to stop the solver." << endl;

                cout << endl << "digite option and then tecle enter: ";
                cin >> preDefProblem;

                if(preDefProblem > 3)
                {
                    cout << endl << endl << "atention: please digite 0, 1, 2 or 3 !!!" << endl;
                }

            }while(preDefProblem > 3);

            if(preDefProblem == 1)
            {
                _problem.MBPTM_02();
            } else if(preDefProblem == 2)
            {
                _problem.MBPTM_03();
            } else if(preDefProblem == 3)
            {
                _problem.MBPTM_10();
            } else if(preDefProblem == 0)
            {
                cout << endl << "Thanks for using COPSolver !!!";

                cout << endl << "Press enter for closing this window." << endl;
                getchar();
                return 0;
            }

        } else if(problemDefinitionMethod == 3)
        {
            time_t source = 0;
            unsigned int NProducts;

            cout << endl << "Please informe the source for random generation (interger value)." << endl;
            cout << endl << "digite option and then press enter: ";
            cin >> source;

            cout << endl << "Please informe number of products for random generation (interger value)." << endl;
            cout << endl << "digite option and then press enter: ";
            cin >> NProducts;

            srand((unsigned) source);
            _problem.MBPTM_rand(NProducts);
        } else
        {
            cout << endl << "error: unknow problem definition method !" << endl;
            return 0;
        }

        _problem.print();
        _problem.generateLingoData();
        _problem.start();
        _problem.analyticalMethod(0);

        _problem.clear();

        cout << endl << "Do you want to run COPSolver again ? Att: if 'yes' all output filles will be overwrited ! (press 1 for 'Yes' or press 0 for 'NO'):";
        cin >> doItAgain;

    } while(doItAgain == 1);

    cout << endl << "Thanks for using COPSolver !!!";
    cout << endl << "Press enter for closing this window." << endl << endl;

    return 0;
}
