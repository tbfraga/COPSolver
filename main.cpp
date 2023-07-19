/*********************************************************************** LICENSE **********************************************************************************************
Important: Copies and distributions of this solver must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.
******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// version: V01_20230719
// developed by Tatiana Balbi Fraga
// start date: 2023/04/26
// last modification: 2023/07/19

#include "lib/multiproduct-batch-processing-time-maximization-problem.h"
using namespace mpbptmp;

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

    MPBPTMP mpbptmp_problem;

    unsigned int problemDefinitionMethod = 1;

    cout << "Thaks for using COPSolver :)))" << endl << endl;
    cout << "COPSolver was (and is being) developed by Fraga, T.B. with purpose of solving many differente combinatorial optimizations problems." << endl << endl;
    cout << "This first version, V01_20230719, only solves the Multi-product batch processing time maximization problem." << endl << endl;
    cout << "COPSolver is licenced by Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0)" << endl << endl;
    cout << "Under this licence you can:" << endl << endl;
    cout << "1) Free dowload and/or use this solver;" << endl;
    cout << "2) Share this solver (if don't modified anyway) only if you inform a link for the original repository and for the license;" << endl;
    cout << "3) Modify the solver for personal use, but not share modified version of solver." << endl << endl;
    cout << "You cannot use COPSolver or any modified version for comercial purpose." << endl;
    cout << "If you need or want to use COPSolver for any comercial purpose, please contact tatiana.balbi@ufpe.br." << endl << endl;
    cout << "If you use this solver for work or science, please don't forget to correctly cite it on presentations and the published material." << endl << endl;
    cout << "repository: github.com/tbfraga/COPSolver" << endl;

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("\nCurrent working dir: %s\n", cwd);
    } else {
       perror("getcwd() error");
       //return 1;
    }

    // Creating a directory
    if (mkdir("Documents", 0777) == -1){}
    else
        cout << endl << "Documents directory created" << endl;

    if (mkdir("Documents/COPSolver", 0777) == -1){}
       // cerr << "Error :  " << strerror(errno) << endl;
    else
        cout << endl << "Documents/COPSolver directory created" << endl;

    if (mkdir("Documents/COPSolver/LINGOSolver", 0777) == -1){}
       // cerr << "Error :  " << strerror(errno) << endl;
    else
        cout << endl << "Documents/COPSolver/LINGOSolver directory created" << endl;

    if (mkdir("Documents/COPSolver/LINGOSolver/MPBPTMP", 0777) == -1){}
       // cerr << "Error :  " << strerror(errno) << endl;
    else
        cout << endl << "Documents/COPSolver/LINGOSolver/MPBPTMP directory created" << endl;

    cout << endl << "Please, resize the window (if needed) and press enter." << endl;
    getchar();

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
        cout << endl << "See you..." << endl;

        cout << endl << "Press enter for closing this window." << endl;
        getchar();
        return 0;
    } else if(problemDefinitionMethod == 1)
    {
        mpbptmp_problem.get();
    } else if(problemDefinitionMethod == 2)
    {
        unsigned int preDefProblem = 1;
        do
        {
            cout << endl << "Please select the predefined problem." << endl;
            cout << endl << "choose:" << endl << endl;
            cout << "1 for taking the MPBPTMP001;" << endl;
            cout << "2 for taking the MPBPTMP002;" << endl;
            cout << "3 for taking the MPBPTMP003; " << endl;
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
            mpbptmp_problem.MPBPTMP001();
        } else if(preDefProblem == 2)
        {
            mpbptmp_problem.MPBPTMP002();
        } else if(preDefProblem == 3)
        {
            mpbptmp_problem.MPBPTMP003();
        } else if(preDefProblem == 0)
        {
            cout << endl << "Thanks for using COPSolver !!!";
            cout << endl << "See you..." << endl;

            cout << endl << "Press enter for closing this window." << endl;
            getchar();
            return 0;
        }

    } else if(problemDefinitionMethod == 3)
    {
        time_t source = 0;
        unsigned int NProducts = 10;

        cout << endl << "Please informe the source for random generation (interger value)." << endl;
        cout << endl << "digite option and then press enter: ";
        cin >> source;

        cout << endl << "Please informe number of products for random generation (interger value)." << endl;
        cout << endl << "digite option and then press enter: ";
        cin >> NProducts;

        srand((unsigned) source);
        mpbptmp_problem.randomMPBPTMP(NProducts);
    } else
    {
        cout << endl << "error: unknow problem definition method !" << endl;
        return 0;
    }

    mpbptmp_problem.print();
    mpbptmp_problem.generateLingoData();

    solution mpbptmp_solution;

    mpbptmp_solution.start(mpbptmp_problem);
    mpbptmp_solution.analyticalMethod();

    mpbptmp_problem.clear();
    mpbptmp_solution.clear();

    cout << endl << "Thanks for using COPSolver !!!";
    cout << endl << "See you..." << endl;

    cout << endl << "Press enter for closing this window." << endl << endl;

    return 0;
}
