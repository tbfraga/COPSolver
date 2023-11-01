/*********************************************************************** LICENSE **********************************************************************************************
Important: Copies and distributions of this solver must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.
******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// version: 1.0-1_20230829
// developed by Tatiana Balbi Fraga
// start date: 2023/04/26
// last modification: 2023/08/29

#include "lib/multiproduct-batch-processing-time-maximization-problem.h"
using namespace mbptm;

int main()
{
    /**** multi-product batch processing time maximization problem ****/

    cout << endl << "COPSolver was (and is being) developed by Fraga, T.B. with purpose of solving many differente combinatorial optimizations problems, ";
    cout << "and other management issues." << endl << endl;
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

    string site = getenv("HOME");
    site += "/COPSolver/data/config.txt";

    fstream file;

    unsigned int problem_type, problem_definition_method, predefined_problem, products;
    time_t source = 0;

    cop _problem;

    file.open(site);
    file.ignore(std::numeric_limits<std::streamsize>::max(),':');
    file.ignore(std::numeric_limits<std::streamsize>::max(),'.');

    file >> problem_type;

    if(problem_type != 1)
    {
        cout << endl << "error: there is an error in the config.txt file - problem is not configured correctly." << endl;
    }

    file.ignore(std::numeric_limits<std::streamsize>::max(),':');
    file.ignore(std::numeric_limits<std::streamsize>::max(),';');
    file.ignore(std::numeric_limits<std::streamsize>::max(),';');
    file.ignore(std::numeric_limits<std::streamsize>::max(),'.');

    file >> problem_definition_method;

    if(problem_definition_method != 1 && problem_definition_method != 2 && problem_definition_method != 3)
    {
        cout << endl << "error: there is an error in the config.txt file - problem definition method is not configured correctly." << endl;
    }

    file.ignore(std::numeric_limits<std::streamsize>::max(),':');
    file.ignore(std::numeric_limits<std::streamsize>::max(),';');
    file.ignore(std::numeric_limits<std::streamsize>::max(),';');
    file.ignore(std::numeric_limits<std::streamsize>::max(),'.');

    file >> predefined_problem;

    if(predefined_problem != 1 && predefined_problem != 2 && predefined_problem != 3)
    {
        cout << endl << "error: there is an error in the config.txt file - predefined problem is not configured correctly." << endl;
    }

    if(problem_definition_method == 3)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(),':');
        file >> source;
        file.ignore(std::numeric_limits<std::streamsize>::max(),':');
        file >> products;
    }

    file.close();

    if(problem_definition_method == 1)
    {
        _problem.get();
    } else if(problem_definition_method == 2)
    {
        if(predefined_problem == 1)
        {
            _problem.MBPTM_02();
        } else if(predefined_problem == 2)
        {
            _problem.MBPTM_03();
        } else if(predefined_problem == 3)
        {
            _problem.MBPTM_10();
        }
    } else if(problem_definition_method == 3)
    {
        srand((unsigned) source);
        _problem.random(products);
    }

    _problem.print();
    _problem.generateLingoData();
    _problem.start();
    _problem.analyticalMethod(0);

    _problem.clear();

    cout << endl << "Thanks for using COPSolver !!!";
    cout << endl << "Press enter for closing this window." << endl << endl;

    return 0;
}
