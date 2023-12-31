/*********************************************************************** LICENSE ********************************************************************************************
Important: Copies and distributions of this file must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.

******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// module: COPSolver: library for solving the demand pattern classification problem
// version: vdpc_dpc.0-1
// developed by Tatiana Balbi Fraga
// start date: 2023/11/08
// last modification: 2023/12/26

#ifndef DEMAND-PATTERNS-CLASSIFICATION_PROBLEM_H_INCLUDED
#define DEMAND-PATTERNS-CLASSIFICATION_PROBLEM_H_INCLUDED

#include <math.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <vector>
using namespace std;

/*time_t _mkgmtime(const struct tm *tm)
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
}*/

/*time_t _mkgmtime(struct tm stm)
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
}*/

namespace dpc
{
    struct pattern
    {
        string name;
        string description;
        double frequency;
        double frequencyA;
        double frequencyB;
        double frequencyC;

        friend ostream & operator << (ostream &out, const pattern &p)
        {
            cout << p.name << "\t" << p.description;
            return out;
        };
    };

    struct sale
    {
        string code;
        double quantity;
        double price;
        struct tm date;

        friend istream & operator >> (istream &in,  sale &s)
        {
            int st;
            string dateStr;

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
            out << setw(8) << setprecision(2) << fixed << s.quantity;
            out << setw(14) << setprecision(2) << fixed << s.price;
            out << setw(6) << s.date.tm_year;
            out << setw(4) << s.date.tm_mon;
            out << setw(4) << s.date.tm_mday;

            return out;
        };
    };

    struct problem
    {
        unsigned int NProducts;
        vector<string> code;
        vector<unsigned int> lead_time;
        vector<char> ABC_class;
        vector<unsigned int> ABC_ord;
        vector<double> ABC_weight;
        vector<sale> data;

        problem& clear()
        {
            NProducts = 0;

            code.clear();
            lead_time.clear();
            ABC_class.clear();
            ABC_ord.clear();
            ABC_weight.clear();
            data.clear();

            return *this;
        }

        problem()
        {
            clear();
        }

        ~problem()
        {
            clear();
        }

        friend istream & operator >> (istream &in,  problem &p)
        {
            string s;
            double u;
            char c;

            sale sl;

            in.ignore(std::numeric_limits<std::streamsize>::max(),':');

            in >> p.NProducts;

            in.ignore(std::numeric_limits<std::streamsize>::max(),':');

            //in >> s;

            for(unsigned int i=0; i<p.NProducts; i++)
            {
                in >> s;
                p.code.push_back(s);

                in >> u;
                p.lead_time.push_back(u);

                in >> c;
                p.ABC_class.push_back(c);

                in >> u;
                p.ABC_weight.push_back(u);
            }

            in.ignore(std::numeric_limits<std::streamsize>::max(),':');


            while(!in.eof())
            {
                in >> sl;
                if(!in.eof())
                {
                    p.data.push_back(sl);
                }
            }

            return in;
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

        solution& clear()
        {
            code.clear();
            sum.clear();
            aws.clear();
            var.clear();
            cv.clear();

            smo.clear();
            awo.clear();

            lt.clear();
            cls.clear();

            mltn.clear();
            lump.clear();

            categorization.clear();

            cutoff_1 = 0;
            cutoff_2 = 0;
            cutoff_3 = 0;

            return *this;
        }

        solution()
        {
            clear();
        }

        ~solution()
        {
            clear();
        }

        friend ostream & operator << (ostream &out, const solution &sol)
        {
            out << "// statistic: " << endl << endl;

            out << setw(14) << sol.categorization[0].name << ":\t" << setw(6) << setprecision(2) << fixed << sol.categorization[0].frequency * 100 << " %";
            out << "; A: " << setw(6) << setprecision(2) << fixed << sol.categorization[0].frequencyA * 100 << " %";
            out << "; B: " << setw(6) << setprecision(2) << fixed << sol.categorization[0].frequencyB * 100 << " %";
            out << "; C: " << setw(6) << setprecision(2) << fixed << sol.categorization[0].frequencyC * 100 << " %" << endl;
            out << setw(14) << sol.categorization[1].name << ":\t" << setw(6) << setprecision(2) << fixed << sol.categorization[1].frequency * 100 << " %";
            out << "; A: " << setw(6) << setprecision(2) << fixed << sol.categorization[1].frequencyA * 100 << " %";
            out << "; B: " << setw(6) << setprecision(2) << fixed << sol.categorization[1].frequencyB * 100 << " %";
            out << "; C: " << setw(6) << setprecision(2) << fixed << sol.categorization[1].frequencyC * 100 << " %" << endl;
            out << setw(14) << sol.categorization[2].name << ":\t" << setw(6) << setprecision(2) << fixed << sol.categorization[2].frequency * 100 << " %";
            out << "; A: " << setw(6) << setprecision(2) << fixed << sol.categorization[2].frequencyA * 100 << " %";
            out << "; B: " << setw(6) << setprecision(2) << fixed << sol.categorization[2].frequencyB * 100 << " %";
            out << "; C: " << setw(6) << setprecision(2) << fixed << sol.categorization[2].frequencyC * 100 << " %" << endl << endl;

            out << "// code\t" << setw(7) << "mltn" << setw(10) << "lump"  << setw(16) << "pattern"  << setw(8) << "lt" << setw(4) << "cls" << ":" << endl << endl;

            for(unsigned int s=0; s<sol.lt.size(); s++)
            {
                out << sol.code[s] << "\t";
                out << setprecision(2) << fixed << setw(7) << sol.mltn[s];
                out << setprecision(2) << fixed << setw(10) << sol.lump[s];
                out << setw(16) << sol.dp[s];
                out << setprecision(2) << fixed << setw(8) << sol.lt[s];
                out << setw(4) << sol.cls[s] << endl;
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

            categorization[0].frequency = 0;
            categorization[1].frequency = 0;
            categorization[2].frequency = 0;

            categorization[0].frequencyA = 0;
            categorization[1].frequencyA = 0;
            categorization[2].frequencyA = 0;

            categorization[0].frequencyB = 0;
            categorization[1].frequencyB = 0;
            categorization[2].frequencyB = 0;

            categorization[0].frequencyC = 0;
            categorization[1].frequencyC = 0;
            categorization[2].frequencyC = 0;

            unsigned int total = 0, totalA = 0, totalB = 0, totalC = 0;
            for(unsigned int s=0; s<lt.size(); s++)
            {
                mltn.push_back(1/(awo[s]*lt[s]));
                lump.push_back(mltn[s] * pow(cv[s],2)) ;

                if(mltn[s] <= cutoff_1)
                {
                    dp.push_back(categorization[0].name);
                    categorization[0].frequency++;
                    total++;
                    if(cls[s] == 'A')
                    {
                        categorization[0].frequencyA++;
                        totalA++;
                    } else if(cls[s] == 'B')
                    {
                        categorization[0].frequencyB++;
                        totalB++;
                    } else if(cls[s] == 'C')
                    {
                        categorization[0].frequencyC++;
                        totalC++;
                    }

                } else if (mltn[s] <= cutoff_2 && lump[s] >= cutoff_3)
                {
                    dp.push_back(categorization[0].name);
                    categorization[0].frequency++;
                    total++;

                    if(cls[s] == 'A')
                    {
                        categorization[0].frequencyA++;
                        totalA++;
                    } else if(cls[s] == 'B')
                    {
                        categorization[0].frequencyB++;
                        totalB++;
                    } else if(cls[s] == 'C')
                    {
                        categorization[0].frequencyC++;
                        totalC++;
                    }
                } else if (lump[s] <= cutoff_3)
                {
                    dp.push_back(categorization[1].name);
                    categorization[1].frequency++;
                    total++;

                    if(cls[s] == 'A')
                    {
                        categorization[1].frequencyA++;
                        totalA++;
                    } else if(cls[s] == 'B')
                    {
                        categorization[1].frequencyB++;
                        totalB++;
                    } else if(cls[s] == 'C')
                    {
                        categorization[1].frequencyC++;
                        totalC++;
                    }
                } else
                {
                    dp.push_back(categorization[2].name);
                    categorization[2].frequency++;
                    total++;

                    if(cls[s] == 'A')
                    {
                        categorization[2].frequencyA++;
                        totalA++;
                    } else if(cls[s] == 'B')
                    {
                        categorization[2].frequencyB++;
                        totalB++;
                    } else if(cls[s] == 'C')
                    {
                        categorization[2].frequencyC++;
                        totalC++;
                    }
                }
            }

            categorization[0].frequency = categorization[0].frequency/total;
            categorization[1].frequency = categorization[1].frequency/total;
            categorization[2].frequency = categorization[2].frequency/total;

            categorization[0].frequencyA = categorization[0].frequencyA/totalA;
            categorization[1].frequencyA = categorization[1].frequencyA/totalA;
            categorization[2].frequencyA = categorization[2].frequencyA/totalA;

            categorization[0].frequencyB = categorization[0].frequencyB/totalB;
            categorization[1].frequencyB = categorization[1].frequencyB/totalB;
            categorization[2].frequencyB = categorization[2].frequencyB/totalB;

            categorization[0].frequencyC = categorization[0].frequencyC/totalC;
            categorization[1].frequencyC = categorization[1].frequencyC/totalC;
            categorization[2].frequencyC = categorization[2].frequencyC/totalC;

            return *this;
        };
    };

    class dpcp
    {
        protected:

        problem _problem;
        solution _solution;

        public:

        void clear();

        friend istream & operator >> (istream &in,  dpcp &dp)
        {
            dp.clear();
            in >> dp._problem;
            return in;
        };

        friend ostream & operator << (ostream &out, const dpcp &dp)
        {
            out << dp._solution;
            return out;
        };

        bool get();

        bool williams();
    };
}

#endif // DEMAND-PATTERNS-CLASSIFICATION-PROBLEM_H_INCLUDED
