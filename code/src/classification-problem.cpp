/*********************************************************************** LICENSE ********************************************************************************************
Important: Copies and distributions of this file must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.
******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// version: COPSolver: library for solving classification problems
// developed by Tatiana Balbi Fraga
// start date: 2023/10/18
// last modification: 2023/11/20

#include "../lib/classification-problem.h"

namespace clss
{
    void clssp::clear()
    {
        _problem.clear();
        _solution.clear();
    };

    bool clssp::get()
    {
        clear();

        string site = getenv("HOME");
        site += "/COPSolver/data/data.txt";

        fstream file;
        file.open(site);

        file >> _problem;

        file.close();

        return 0;
    };

    bool clssp::ABC()
    {
        _solution.ABC(_problem);

        cout << endl << "ABC classification: " << endl;
        cout << endl << _solution << endl;

        return 0;
    };

    bool clssp::analyticHierarchyProcess()
    {
        get();

        string site = getenv("HOME");
        site += "/COPSolver/results/AHP_problem_org.txt";

        fstream file;

        file.open(site, ios::out);

        file << "--> Data:\n\n";

        _problem.pairwiseWeight.consistencyRate();

        file << _problem;

        file.close();

        if(_problem.pairwiseWeight.CR > 0.1)
        {
            _problem.pairwiseWeight.forceConsistency();
        }

        for(unsigned int s=0; s<_problem.pairwiseWeight.mainEigenvector.size(); s++)
        {
            _problem.weightVector[s] = _problem.pairwiseWeight.mainEigenvector[s];
        }

        _problem.weightNormalize();

        site = getenv("HOME");
        site += "/COPSolver/results/AHP_problem_adj.txt";

        file.open(site, ios::out);

        file << "--> Adjusted data:\n\n";

        file << _problem;

        file.close();

        _solution.analyticHierarchyProcess(_problem);

        site = getenv("HOME");
        site += "/COPSolver/results/AHP_solution.txt";

        file.open(site, ios::out);

        file << _solution;

        file.close();

        return 0;
    };
}
