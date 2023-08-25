/*********************************************************************** LICENSE **********************************************************************************************
Important: Copies and distributions of this solver must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.
******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// version: 1.0-1 adapted to codeocean
// developed by Tatiana Balbi Fraga
// start date: 2023/08/25
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
    _problem.get();
    _problem.print();
    _problem.generateLingoData();
    _problem.start();
    _problem.analyticalMethod();
    _problem.clear();

    return 0;
}
