/*********************************************************************** LICENSE ********************************************************************************************
Important: Copies and distributions of this file must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.
******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// version:
// developed by Tatiana Balbi Fraga
// start date: 2023/10/18
// last modification: 2023/10/25

#include "../lib/classification-problem.h"

namespace classp
{
    void clssp::clear()
    {/*
        _problem._criteria.clear();

        _problem._weight.clear();

        for(unsigned int s; s<_problem._pairwiseWeight.size(); s++)
        {
            _problem._pairwiseWeight[s].clear();
        }

        _problem._pairwiseWeight.clear();

        for(unsigned int s; s<_problem._data.size(); s++)
        {
            _problem._data[s].clear();
        }

        _problem._data.clear();*/

    };

    bool clssp::get()
    {
        clear();

        string site = getenv("HOME");
        site += "/COPSolver/data/data.txt";

        fstream file;
        file.open(site);

        file.ignore(std::numeric_limits<std::streamsize>::max(),':');

        file >> _problem._NCriteria;

        file.ignore(std::numeric_limits<std::streamsize>::max(),':');

       _problem._weight.resize(_problem._NCriteria);

        for(unsigned int s=0; s<_problem._weight.size(); s++)
        {
            file >> _problem._weight[s];
        }

        file.ignore(std::numeric_limits<std::streamsize>::max(),':');

        _problem._pairwiseWeight.resize(_problem._NCriteria);

        file >> _problem._pairwiseWeight;

        /*

        file.ignore(std::numeric_limits<std::streamsize>::max(),':');

        file >> _problem._NData;

        _problem._data.resize(_problem._NCriteria);

        file.ignore(std::numeric_limits<std::streamsize>::max(),':');

        for(unsigned int s=0; s<_problem._data.size(); s++)
        {
            _problem._data[s].resize(_problem._NData);

            for(unsigned int ss=0; ss<_problem._data[s].size(); ss++)
            {
                file >> _problem._data[s][ss];
            }
        }*/

        file.close();

        _problem._pairwiseWeight.consistencyRate();

        print();

        cout << endl;

        if(_problem._pairwiseWeight.CR > 0.1)
        {
            _problem._pairwiseWeight.forceConsistency();
        }

        print();

        return 0;
    };

    bool clssp::print()
    {
        cout << "number of criteria: " << _problem._NCriteria << endl << endl;

        cout << _problem._pairwiseWeight << endl << endl;

        cout << "weight: " << endl << endl;

        for(unsigned int s=0; s<_problem._weight.size(); s++)
        {
            cout << _problem._weight[s] << endl;
        }

        /*

        cout << "weight: " << endl << endl;

        for(unsigned int s=0; s<_problem._weight.size(); s++)
        {
            cout << _problem._weight[s] << "\t";
        }

        cout << endl << endl;

        cout << "pairwise comparison weight: " << endl << endl;

        for(unsigned int s=0; s<_problem._pairwiseWeight.size(); s++)
        {
            for(unsigned int ss=0; ss<_problem._pairwiseWeight[s].size(); ss++)
            {
                cout << _problem._pairwiseWeight[s][ss] << "\t";
            }

            cout << endl;
        }

        cout << endl;

        cout << "number of data per criterion: " << _problem._NData << endl << endl;

        cout << "data: " << endl << endl;

        for(unsigned int s=0; s<_problem._data.size(); s++)
        {
            for(unsigned int ss=0; ss<_problem._data[s].size(); ss++)
            {
                cout << _problem._data[s][ss] << "\t";
            }

            cout << endl;
        }*/

        cout << endl;

        return 0;
    };

    bool clssp::reduce(double tol, unsigned int n, unsigned int g, unsigned int s)
    {
        return 0;
    };


}
