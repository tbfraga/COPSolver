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



#include "formatted-files-reading.h"

namespace dpi
{
    struct pattern
    {
        string name;
        string description;

        friend ostream & operator << (ostream &out, const pattern &p)
        {
            cout << p.name << "\t" << p.description;
            return out;
        };
    };

    struct sale
    {
        string code;
        unsigned int quantity;
        double price;
        struct tm date;

        friend istream & operator >> (istream &in,  sale &s)
        {
            in >> s.code;
            in >> s.quantity;
            in >> s.price;
            in >> s.date.tm_year;
            in >> s.date.tm_mon;
            in >> s.date.tm_mday;

            cout << endl << s.code << "\t" << s.quantity << endl;

            s.date.tm_hour = 0;
            s.date.tm_min = 0;
            s.date.tm_sec = 0;

            return in;
        };

        friend ostream & operator << (ostream &out, const sale &s)
        {
            out << s.code << "\t";
            out << s.quantity << "\t";
            out << s.price << "\t";
            out << s.date.tm_year << "\t";
            out << s.date.tm_mon << "\t";
            out << s.date.tm_mday << "\t";

            return out;
        };
    };

    struct problem
    {
        vector<pattern> categorization;
        vector<sale> data;

        problem& clear()
        {
            categorization.clear();
            data.clear();

            return *this;
        }

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

            return *this;
        };

        friend istream & operator >> (istream &in,  problem &p)
        {
            sale s;

            p.Boylan();

            while(!in.eof())
            {
                in >> s;
                p.data.push_back(s);
            }

            return in;
        };

        friend ostream & operator << (ostream &out, const problem &p)
        {
            for(unsigned int s=0; s<p.categorization.size(); s++)
            {
                cout << endl << p.categorization[s] << endl;
            }
            return out;
        };


        problem& alexia()
        {

            return *this;
        };

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

        void clear()
        {
            _problem.clear();
        };

        friend istream & operator >> (istream &in,  dpip &dp)
        {
            dp.clear();
            in >> dp._problem;
            return in;
        };

        friend ostream & operator << (ostream &out, const dpip &dp)
        {
            out << dp._problem;
            return out;
        };

        bool get()
        {
            string site = getenv("HOME");
            site += "/COPSolver/data/data.txt";

            fstream file;
            file.open(site);

            file.ignore(std::numeric_limits<std::streamsize>::max(),':');

            file >> _problem;

            file.close();

            return 0;
        };

        bool alexia()
        {
            ffr::input input_file;

            ffr::output output_file;
            output_file.alexia_data_address();

            output_file.alexia_data(input_file);

            string site = getenv("HOME");
            site += "/COPSolver/data/data.txt";

            fstream file;
            file.open(site);

            file.ignore(std::numeric_limits<std::streamsize>::max(),'.');

            //file >> _problem;

            file.close();

            return 0;
        };

        bool print()
        {
            string site = getenv("HOME");
            site += "/COPSolver/results/classification.txt";

            fstream file;

            file.open(site, ios::out);

            file.close();

            return 0;
        };

        bool Williams()
        {
            //get();

            alexia();

            string site = getenv("HOME");
            site += "/COPSolver/results/problem.txt";

            fstream file;

            file.open(site, ios::out);

            //file << _problem;

            file.close();
        };
    };
}

#endif // DEMAND-PATTERNS-IDENTIFICATION-PROBLEM_H_INCLUDED
