/*********************************************************************** LICENSE ********************************************************************************************
Important: Copies and distributions of this file must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.

******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// module: COPSolver: library for solving demand patterns classification problems
// version: vdpc_dpc.0-1
// developed by Tatiana Balbi Fraga
// start date: 2023/11/08
// last modification: 2023/12/18

#ifndef DEMAND-PATTERNS-IDENTIFICATION-PROBLEM_H_INCLUDED
#define DEMAND-PATTERNS-IDENTIFICATION-PROBLEM_H_INCLUDED

#include "../ffrc/formatted-files-reading.h"

time_t _mkgmtime(const struct tm *tm)
{
    // Month-to-day offset for non-leap-years.
    static const int month_day[12] =
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

    // Most of the calculation is easy; leap years are the main difficulty.
    int month = tm->tm_mon % 12;
    int year = tm->tm_year + tm->tm_mon / 12;
    if (month < 0) {   // Negative values % 12 are still negative.
        month += 12;
        --year;
    }

    // This is the number of Februaries since 1900.
    const int year_for_leap = (month > 1) ? year + 1 : year;

    time_t rt = tm->tm_sec                             // Seconds
        + 60 * (tm->tm_min                          // Minute = 60 seconds
        + 60 * (tm->tm_hour                         // Hour = 60 minutes
        + 24 * (month_day[month] + tm->tm_mday - 1  // Day = 24 hours
        + 365 * (year - 70)                         // Year = 365 days
        + (year_for_leap - 69) / 4                  // Every 4 years is     leap...
        - (year_for_leap - 1) / 100                 // Except centuries...
        + (year_for_leap + 299) / 400)));           // Except 400s.
    return rt < 0 ? -1 : rt;
}

time_t _mkgmtime(struct tm stm)
{
    // Month-to-day offset for non-leap-years.
    static const int month_day[12] =
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

    // Most of the calculation is easy; leap years are the main difficulty.
    int month = stm.tm_mon % 12;
    int year = stm.tm_year + stm.tm_mon / 12;
    if (month < 0) {   // Negative values % 12 are still negative.
        month += 12;
        --year;
    }

    // This is the number of Februaries since 1900.
    const int year_for_leap = (month > 1) ? year + 1 : year;

    time_t rt = stm.tm_sec                             // Seconds
        + 60 * (stm.tm_min                          // Minute = 60 seconds
        + 60 * (stm.tm_hour                         // Hour = 60 minutes
        + 24 * (month_day[month] + stm.tm_mday - 1  // Day = 24 hours
        + 365 * (year - 70)                         // Year = 365 days
        + (year_for_leap - 69) / 4                  // Every 4 years is     leap...
        - (year_for_leap - 1) / 100                 // Except centuries...
        + (year_for_leap + 299) / 400)));           // Except 400s.
    return rt < 0 ? -1 : rt;
}

/*unsigned int _diffdays (struct tm tm1, struct tm tm2)
{
    unsigned int diff;

    time_t rt1, rt2;

    rt1 =  _mkgmtime(tm1);
    rt2 =  _mkgmtime(tm2);

    double s_diff = difftime(rt1, rt2);

    diff = int(abs(s_diff / 86400));

    return diff;
}*/

namespace dpc
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

            s.date.tm_hour = 0;
            s.date.tm_min = 0;
            s.date.tm_sec = 0;

            return in;
        };

        friend ostream & operator << (ostream &out, const sale &s)
        {
            out << s.code << "\t";
            out << setw(3) << s.quantity << "\t";
            out << setw(5) << s.price << "\t";
            out << setw(4) << s.date.tm_year << "\t";
            out << setw(2) << s.date.tm_mon << "\t";
            out << setw(2) << s.date.tm_mday << "\t";

            return out;
        };
    };

    struct problem
    {
        vector<string> file_list;
        vector<sale> data;
        vector<unsigned int> lead_time;
        vector<char> ABC_class;
        vector<unsigned int> ABC_ord;
        vector<double> ABC_weight;

        problem& clear()
        {
            file_list.clear();
            data.clear();
            lead_time.clear();
            ABC_class.clear();
            ABC_ord.clear();
            ABC_weight.clear();

            return *this;
        }

        /*friend istream & operator >> (istream &in,  problem &p)
        {
            sale s;

            while(!in.eof())
            {
                in >> s;
                p.data.push_back(s);
            }

            return in;
        };*/


        problem& alexia()
        {
            //ffr::input input_file;
            ffr::output output_file;

            output_file.alexia_data_address();
            output_file.alexia_data();

            file_list = output_file._input.code;
            lead_time = output_file._input.lead_time;
            ABC_class = output_file._input.ABC_class;

            string file_address = getenv("HOME");
            file_address += "/COPSolver/results/CLSS_problem";

            fstream out_file, in_file;
            out_file.open(file_address, ios::out);

            file_address = getenv("HOME");
            file_address += "/COPSolver/data/alexia/";

            cout << endl << "reading and formating alexia data, please wait" << endl;

            sale reg;

            data.clear();

            for(unsigned s=0; s<file_list.size(); s++)
            {
                in_file.open(file_address + "data_" + file_list[s] + ".txt");

                while(!in_file.eof())
                {
                    in_file >> reg;

                    out_file << reg << endl;

                    data.push_back(reg);
                }

                in_file.close();
            }

            out_file.close();

            return *this;
        };

    };

    struct solution
    {
        vector <string> code;

        vector <double> sum; // total quantity sold in the period evaluated
        vector <double> aws; // average quantities sold
        vector <double> var; // variance of the quantities sold
        vector <double> cv;  // coefficient of variation of the quantities sold

        vector <double> smo; // total number of requests in the period evaluated
        vector <double> awo; // average number of requests

        vector <double> lt;  // lead_time
        vector <char> cls;   // multi-criteria ABC classification

        vector<double> mltn; // mean number of lead times between demands
        vector<double> lump; // lumpiness

        vector<pattern> categorization;

        double cutoff_1;
        double cutoff_2;
        double cutoff_3;

        vector<string> dp; // demand pattern;

        friend ostream & operator << (ostream &out, const solution &sol)
        {
            out << "code" << setw(7) << "mltn" << "\t" << setw(7) << "lump" << "\t"  << setw(12) << "pattern" << "\t"  << setw(5) << "lt" << setw(3) << "\t" << "cls :" << endl << endl;

            for(unsigned int s=0; s<sol.lt.size(); s++)
            {
                out << sol.code[s] << setprecision(2) << fixed << setw(7) << sol.mltn[s] << "\t";
                out << setprecision(2) << fixed << setw(7) << sol.lump[s] << "\t" << setw(12) << sol.dp[s] << "\t";
                out << setprecision(2) << fixed << setw(5) << sol.lt[s] << "\t";
                out << setw(3) << sol.cls[s] << endl;
            }

            return out;
        };

        solution& calculate_monthly_data (problem p)
        {
            unsigned int idx;
            int months;
            string i_code;

            code.clear();
            sum.clear();
            aws.clear();
            var.clear();
            smo.clear();
            awo.clear();
            lt.clear();
            cls.clear();

            if (p.data.size() >= 1)
            {
                idx = 0;
                i_code = p.data[0].code;
                code.push_back(i_code);
                sum.push_back(p.data[0].quantity);
                smo.push_back(1);

                lt.push_back(double(p.lead_time[idx])/30);
                cls.push_back(p.ABC_class[idx]);

                months = - 12*p.data[0].date.tm_year - p.data[0].date.tm_mon + 1;
            }

            for(unsigned int s=1; s<p.data.size(); s++)
            {
                if(p.data[s].code == p.data[s-1].code)
                {
                    sum[idx] += p.data[s].quantity;
                    smo[idx] ++;
                } else
                {
                    //months += 12*p.data[s-1].date.tm_year + p.data[s-1].date.tm_mon; // final sale date for collected data
                    months += 12*2022 + 8; // final date for collected data
                    aws.push_back(sum[idx]/months);
                    awo.push_back(smo[idx]/months);

                    idx++;

                    i_code = p.data[s].code;
                    code.push_back(i_code);
                    sum.push_back(p.data[s].quantity);
                    smo.push_back(1);

                    months = - 12*p.data[s].date.tm_year - p.data[s].date.tm_mon + 1;

                    lt.push_back(double(p.lead_time[idx])/30);
                    cls.push_back(p.ABC_class[idx]);
                }
            }

            months += 12*p.data.back().date.tm_year + p.data.back().date.tm_mon;

            aws.push_back(sum[idx]/months);
            awo.push_back(smo[idx]/months);

            if (p.data.size() >= 1)
            {
                idx = 0;

                var.push_back(pow((p.data[0].quantity - aws[0]),2.0));
            }

             for(unsigned int s=1; s<p.data.size(); s++)
            {
                if(p.data[s].code == p.data[s-1].code)
                {
                    var[idx] += pow((p.data[s].quantity - aws[idx]),2.0);
                } else
                {
                    var[idx] = var[idx]/smo[idx];
                    cv.push_back(sqrt(var[idx])/aws[idx]);

                    idx ++;
                    var.push_back(pow((p.data[s].quantity - aws[idx]),2.0));
                }
            }

            var[idx] = var[idx]/smo[idx];
            cv.push_back(sqrt(var[idx])/aws[idx]);

            return *this;
        };

        solution& williams_categorization()
        {
            cutoff_1 = 0.7;
            cutoff_2 = 2.8;
            cutoff_3 = 0.5;

            pattern p;

            categorization.clear();

            p.name = "smooth";
            p.description = "continous_demand";

            categorization.push_back(p);

            p.name = "slow-moving";
            p.description = "low_average_demand_per_period";

            categorization.push_back(p);

            p.name = "sporadic";
            p.description = "no_more_than_1_DDL";

            categorization.push_back(p);

            return *this;
        };

        solution& boylan_categorization()
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

        solution& williams(problem p)
        {
            williams_categorization();

            calculate_monthly_data(p);

            mltn.clear();
            lump.clear();

            dp.clear();

            for(unsigned int s=0; s<lt.size(); s++)
            {
                mltn.push_back(1/(awo[s]*lt[s]));
                lump.push_back(mltn[s] * pow(cv[s],2)) ;

                if(mltn[s] <= cutoff_1)
                {
                    dp.push_back("smooth");
                } else if (mltn[s] <= cutoff_2 && lump[s] >= cutoff_3)
                {
                    dp.push_back("smooth");
                } else if (lump[s] <= cutoff_3)
                {
                    dp.push_back("slow-moving");
                } else
                {
                    dp.push_back("sporadic");
                }
            }

            return *this;
        };

    };

    class dpcp
    {
        protected:

        problem _problem;
        solution _solution;

        public:

        void clear()
        {
            _problem.clear();
        };

        friend istream & operator >> (istream &in,  dpcp &dp)
        {/*
            dp.clear();
            in >> dp._problem;*/
            return in;
        };

        friend ostream & operator << (ostream &out, const dpcp &dp)
        {
//            out << dp._problem;
            return out;
        };

        bool get()
        {/*
            string site = getenv("HOME");
            site += "/COPSolver/data/data.txt";

            fstream file;
            file.open(site);

            file.ignore(std::numeric_limits<std::streamsize>::max(),':');

            file >> _problem;

            file.close();*/

            return 0;
        };

        void alexia()
        {
            _problem.alexia();
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

        bool williams()
        {
            string site = getenv("HOME");
            site += "/COPSolver/results/willians_solution.txt";

            fstream file;

            _solution.williams(_problem);

            file.open(site, ios::out);

            file << _solution;

            file.close();

            return 0;
        };
    };
}

#endif // DEMAND-PATTERNS-IDENTIFICATION-PROBLEM_H_INCLUDED
