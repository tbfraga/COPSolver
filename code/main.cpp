/*********************************************************************** LICENSE **********************************************************************************************
Important: Copies and distributions of this solver must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.

README

COPSolver was (and is being) developed by Fraga, T.B. with purpose of solving many differente combinatorial optimizations problems, and other management issues.

COPSolver is licenced by Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this licence you can:

1) Free dowload and/or use this solver (except for comercial purpose);
2) Share this solver (if don't modified anyway) only if you inform a link for the original repository and for the license;
3) Modify the solver for personal use, but not share modified version of solver.

You cannot use COPSolver or any modified version for comercial purpose.

If you need or want to use COPSolver for any comercial purpose, please contact tatiana.balbi@ufpe.br.

If you use this solver for work or science, please don't forget to correctly cite it on presentations and the published material.

repository: github.com/tbfraga/COPSolver

******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// version: 2.0-1
// developed by Tatiana Balbi Fraga
// start date: 2023/04/26
// last modification: 2023/11/07

#include "lib/classification-problem.h"
#include "lib/demand-patterns-identification-problem.h"
#include "lib/multiproduct-batch-processing-time-maximization-problem.h"
using namespace mbptm;

int main()
{
    cout << endl << "COPSolver is running now, please wait ..." << endl;

    string site = getenv("HOME");
    site += "/COPSolver/data/config.txt";

    fstream file;

    unsigned int problem_class, // 1 if classification-problem; 2 if demand-patterns-identification-problem;
                                // 3 if combinatorial-optimization-problem
                 problem_type,  // 1 if multiproduct-batch-processing-time-maximization-problem
                 problem_definition_method, // 1 if getting problem from file; 2 if getting a predefined problem;
                                            // 3 if generating a pseudo random problem
                 predefined_problem,
                 products,
                 solving_method;

    time_t source = 0;

    file.open(site);

    file.ignore(std::numeric_limits<std::streamsize>::max(),'.');
    file >> problem_class;

    if(problem_class != 1 && problem_class != 2)
    {
        cout << endl << "error: there is an error in the config.txt file - problem class is not configured correctly." << endl;
        getchar();
        file.close();
        return 1;
    }

    file.ignore(std::numeric_limits<std::streamsize>::max(),'.');
    file >> problem_type;

    file.ignore(std::numeric_limits<std::streamsize>::max(),'.');
    file >> problem_definition_method;

    file.ignore(std::numeric_limits<std::streamsize>::max(),'.');
    file >> predefined_problem;

    if(problem_definition_method == 3)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(),':');
        file >> source;
        file.ignore(std::numeric_limits<std::streamsize>::max(),':');
        file >> products;
    }

    file.ignore(std::numeric_limits<std::streamsize>::max(),'.');
    file >> solving_method;

    file.close();

    if(problem_class == 1) // if classification problems
    {
        if(problem_type != 1)
        {
            cout << endl << "error: there is an error in the config.txt file - problem is not configured correctly." << endl;
            getchar();
            return 1;
        }

        if(problem_definition_method != 1)
        {
            cout << endl << "error: there is an error in the config.txt file - problem definition method is not configured correctly." << endl;
            getchar();
            return 1;
        }

        if(solving_method != 1)
        {
            cout << endl << "error: there is an error in the config.txt file - solving method is not configured correctly." << endl;
            getchar();
            return 1;
        }

        clss::clssp _problem;

        if(solving_method == 1)
        {
            _problem.analyticHierarchyProcess();
        }

        _problem.clear();

    } else if(problem_class == 2) // if demand patterns identification problems
    {
        if(problem_type != 1)
        {
            cout << endl << "error: there is an error in the config.txt file - problem is not configured correctly." << endl;
            getchar();
            return 1;
        }

        if(problem_definition_method != 1)
        {
            cout << endl << "error: there is an error in the config.txt file - problem definition method is not configured correctly." << endl;
            getchar();
            return 1;
        }

        if(solving_method != 1)
        {
            cout << endl << "error: there is an error in the config.txt file - solving method is not configured correctly." << endl;
            getchar();
            return 1;
        }

        dpi::dpip _problem;

        if(solving_method == 1)
        {
            _problem.Williams();
        }

        _problem.clear();

    } else if(problem_class == 3) // if combinatorial optimization problems
    {
        cop _problem;

        if(problem_type != 1)
        {
            cout << endl << "error: there is an error in the config.txt file - problem is not configured correctly." << endl;
        }

        if(problem_definition_method != 1 && problem_definition_method != 2 && problem_definition_method != 3)
        {
            cout << endl << "error: there is an error in the config.txt file - problem definition method is not configured correctly." << endl;
        }

        if(problem_definition_method == 2 && predefined_problem != 1 && predefined_problem != 2 && predefined_problem != 3)
        {
            cout << endl << "error: there is an error in the config.txt file - predefined problem is not configured correctly." << endl;
        }

        if(problem_definition_method == 1) // if getting problem from file data.txt
        {
            _problem.get();
        } else if(problem_definition_method == 2) // if getting a predefined problem
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
        } else if(problem_definition_method == 3) // if generating a pseudo random problem
        {
            srand((unsigned) source);
            _problem.random(products);
        }

        _problem.print();
        _problem.generateLingoData();
        _problem.start();
        _problem.analyticalMethod(0);

        _problem.clear();
    }

    cout << endl << "Thanks for using COPSolver !!!";
    cout << endl << "Press enter for closing this window." << endl << endl;

    return 0;
}

// Note: talvez o infinito não seja bem representado por um caminho continuo e fechado que circula em torno de si mesmo, tal como o número 8.
// É possível que o infinito seja melhor representado pelo número 9. Ele termina em determinado ponto e depois recomeça em algum outro ponto de sua trajetória.
