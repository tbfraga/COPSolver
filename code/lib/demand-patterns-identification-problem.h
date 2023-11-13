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
// last modification: 2023/11/13

#ifndef DEMAND-PATTERNS-IDENTIFICATION-PROBLEM_H_INCLUDED
#define DEMAND-PATTERNS-IDENTIFICATION-PROBLEM_H_INCLUDED

#include "formatted-files-reading.h"

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

unsigned int _diffdays (struct tm tm1, struct tm tm2)
{
    unsigned int diff;

    time_t rt1, rt2;

    rt1 =  _mkgmtime(tm1);
    rt2 =  _mkgmtime(tm2);

    double s_diff = difftime(rt1, rt2);

    diff = int(abs(s_diff / 86400));

    return diff;
}

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
        vector<pattern> categorization;
        vector<sale> data;
        vector<unsigned int> lead_time;

        problem& clear()
        {
            file_list.clear();
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
            ffr::input input_file;
            ffr::output output_file;

            output_file.alexia_data_address();
            output_file.alexia_data();

            file_list = output_file._input.file_list;
            lead_time = output_file._input.lead_time;

            string file_address = getenv("HOME");
            file_address += "/COPSolver/results/CLSS_problem";

            fstream out_file, in_file;
            out_file.open(file_address, ios::out);

            file_address = getenv("HOME");
            file_address += "/COPSolver/data/alexia/";

            sale reg;

            data.clear();

            cout << endl << file_list.size();

            for(unsigned s=0; s<file_list.size(); s++)
            {
                in_file.open(file_address + "data_" + file_list[s]);

                cout << endl << file_address + "data_" + file_list[s] << endl;

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
        vector <vector<double>> dp_cnt;
        vector <vector<double>> dp_sum;
        vector <vector<double>> dp_aws;

        solution& resize(problem p)
        {
            unsigned int n = p.file_list.size();

            dp_cnt.resize(n);
            dp_sum.resize(n);
            dp_aws.resize(n);

            return *this;
        }

        solution& average_week_sales (problem p)
        {
            resize(p);

            unsigned int code_index = 0, week_index = 0, aux;

            if (p.data.size() >= 1)
            {
                dp_sum[0].push_back(p.data[0].quantity);
                dp_cnt[0].push_back(1);

                week_index = 0;
            }

            for(unsigned int s=1; s<p.data.size(); s++)
            {
                aux = floor(_diffdays(p.data[s].date, p.data[0].date)/7);

                if(p.data[s].code == p.data[s-1].code)
                {
                    if(week_index == aux)
                    {
                        dp_sum[code_index][week_index] += p.data[s].quantity;
                        dp_cnt[code_index][week_index] ++;
                    }else
                    {
                        for(unsigned int i=week_index+1; i<aux; i++)
                        {
                            dp_sum[code_index].push_back(0);
                            dp_cnt[code_index].push_back(0);
                        }

                        dp_sum[code_index].push_back(p.data[s].quantity);
                        dp_cnt[code_index].push_back(1);

                        week_index = aux;
                    }
                } else
                {
                    code_index ++;

                    for(unsigned int i=0; i<aux; i++)
                    {
                        dp_sum[code_index].push_back(0);
                        dp_cnt[code_index].push_back(0);
                    }

                    dp_sum[code_index].push_back(p.data[s].quantity);
                    dp_cnt[code_index].push_back(1);

                    week_index = aux;
                }
            }

            for(unsigned int s=0; s<dp_sum.size(); s++)
            {
                for(unsigned int i=0; i<dp_sum[s].size(); i++)
                {
                    if(dp_cnt[s][i] == 0)
                    {
                        dp_aws[s].push_back(0);
                    } else
                    {
                        dp_aws[s].push_back(dp_sum[s][i] / dp_cnt[s][i]);
                    }

                    cout << endl << dp_aws[s][i] << "\t" << dp_sum[s][i] << "\t" << dp_cnt[s][i] << endl;
                    //getchar();
                }
                cout << endl;
            }

            return *this;
        };

        solution& average_month_sales (problem p)
        {
            return *this;
        };

        solution& Williams()
        {

            return *this;
        };

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

        bool Williams()
        {
            _problem.Boylan();

            _solution.average_week_sales(_problem);

            return 0;
        };
    };
}

#endif // DEMAND-PATTERNS-IDENTIFICATION-PROBLEM_H_INCLUDED
