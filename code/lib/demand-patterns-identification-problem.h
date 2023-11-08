/*********************************************************************** LICENSE ********************************************************************************************
Important: Copies and distributions of this file must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.

******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// module: COPSolver: library for solving demand patterns identification problems
// version: v3.0-1
// developed by Tatiana Balbi Fraga
// start date: 2023/11/08
// last modification: 2023/11/08

#ifndef DEMAND-PATTERNS-IDENTIFICATION-PROBLEM_H_INCLUDED
#define DEMAND-PATTERNS-IDENTIFICATION-PROBLEM_H_INCLUDED

#include <ctime>
#include <chrono>
using namespace std;

namespace dpi
{
    struct pattern
    {
        string name;
        string description;
    };

    struct sale
    {
        string code;
        unsigned int quantity;
        double price;
        tm *date;
    };

    struct problem
    {
        vector<pattern> categorization;
        vector<sale> data;

        problem& Boylan()
        {
            pattern p;

            categorization.clear();

            p.name = "normal";
            p.description = "represented_by_normal_distribution";

            categorization.push_back(p);

            p.name = "intermittent";
            p.description = "infrequent_demand_occurrences";

            categorization.push_back(p);

            p.name = "slow_moving";
            p.description = "low_average_demand_per_period";

            categorization.push_back(p);

            p.name = "erratic";
            p.description = "highly_variable_demand_size";

            categorization.push_back(p);

            p.name = "lumpy";
            p.description = "intermittent_and_erratic";

            categorization.push_back(p);

            p.name = "clumped";
            p.description = "intermittent_and_non_erratic";

            categorization.push_back(p);
        }
    };

    struct solution
    {
    };

    class dpip
    {
        protected:

        problem _problem;
        solution _solution;

        public:

        void clear();

        friend istream & operator >> (istream &in,  dpip &dp)
        {
            //in >> c._problem;
            return in;
        };
    };
}

#endif // DEMAND-PATTERNS-IDENTIFICATION-PROBLEM_H_INCLUDED
