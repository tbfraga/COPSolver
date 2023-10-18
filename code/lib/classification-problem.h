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
// last modification: 2023/10/18

#ifndef CLASSIFICATION_PROBLEM_H_INCLUDED
#define CLASSIFICATION_PROBLEM_H_INCLUDED

#include<vector>
#include <string>
#include <iterator>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "Eigen/Eigenvalues"
using namespace Eigen;
using namespace std;

namespace classp
{
    struct problem{
        unsigned int _NCriteria; // number of criteria
        vector<string> _Criteria; // name of the criteria used, ordered according to _Data matrix
        vector<int> _Weight; // criteria weight vector
        vector<vector<double>> _pairwiseWeight; // matrix of pairwise comparisons of the criteria
        unsigned int _NData; // number of data per criterion
        vector<vector<float>> _Data; // data for each criterion - vector[_NCriteria, _NData]
    };

    class clssp
    {
        protected:

        problem _problem;

        public:

        void clear();
        bool get();
        bool print();

        bool consistency();

        void ABC();
    };

}

#endif // CLASSIFICATION_PROBLEM_H_INCLUDED
