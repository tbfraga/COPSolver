/*********************************************************************** LICENSE ********************************************************************************************
Important: Copies and distributions of this file must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.
******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// module: COPSolver: library for solving multi-product p-batch processing time maximization problems
// version: vco_mbptm.0-1
// developed by Tatiana Balbi Fraga
// start date: 2023/04/26
// last modification: 2023/12/21

// future improvements: use operators overloading for defined structures (will be done according to the needs).
// COPSolver: livrary for demand parttern classification problems is in the testing phase

#ifndef MULTIPRODUCT_BATCH_PROCESSING_TIME_MAXIMIZATION_PROBLEM_H_INCLUDED
#define MULTIPRODUCT_BATCH_PROCESSING_TIME_MAXIMIZATION_PROBLEM_H_INCLUDED

#include<math.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>

#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
using namespace std;

namespace mbptm
{
    struct problem{
        unsigned int NProducts; // number of products
        vector<float> productionRate = {}; // product weight ratio (g/m^2)
        vector<unsigned int> demand = {}; // demand per product (g)
        vector<unsigned int> maximumInventory = {}; // maximum inventory at factory per product (g)
        unsigned int totalMaximumInventory; // total maximum inventory at factory (g)
        vector<unsigned int> maximumOutletInventory = {}; // maximum outlet inventory per product (g)
        unsigned int totalMaximumOutletInventory; // total maximum outlet inventory (g)
        unsigned int maxBatchProcessingTime; // maximum batch processing time (min)

        problem& clear()
        {
            NProducts = 0;
            productionRate.clear();
            demand.clear();
            maximumInventory.clear();
            totalMaximumInventory = 0;
            maximumOutletInventory.clear();
            totalMaximumOutletInventory = 0;
            maxBatchProcessingTime = 0;

            return *this;
        };

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
            if(&in == &cin)
            {
                cout << endl << "error: operator >> for struct problem is only defined for geting data from file !!!" << endl << endl;
                p.clear();
            }else
            {
                in.ignore(numeric_limits<std::streamsize>::max(),':');

                in >> p.NProducts;

                p.productionRate.resize(p.NProducts,0);

                in.ignore(numeric_limits<std::streamsize>::max(),':');

                for(unsigned int i=0; i<p.NProducts; i++)
                {
                    in >> p.productionRate[i];
                }

                p.demand.resize(p.NProducts,0);

                in.ignore(numeric_limits<std::streamsize>::max(),':');

                for(unsigned int i=0; i<p.NProducts; i++)
                {
                    in >> p.demand[i];
                }

                in.ignore(numeric_limits<std::streamsize>::max(),':');

                in >> p.totalMaximumOutletInventory;

                in.ignore(numeric_limits<std::streamsize>::max(),':');

                p.maximumOutletInventory.resize(p.NProducts,0);

                for(unsigned int i=0; i<p.NProducts; i++)
                {
                    in >> p.maximumOutletInventory[i];
                }

                in.ignore(numeric_limits<std::streamsize>::max(),':');

                in >> p.totalMaximumInventory;

                p.maximumInventory.resize(p.NProducts,0);

                in.ignore(numeric_limits<std::streamsize>::max(),':');

                for(unsigned int i=0; i<p.NProducts; i++)
                {
                    in >> p.maximumInventory[i];
                }

                in.ignore(numeric_limits<std::streamsize>::max(),':');

                in >> p.maxBatchProcessingTime;
            }

            return in;
        };

        friend ostream & operator << (ostream &out, const problem &p)
        {
            out << "Multi-product batch processing time maximization problem " << endl;

            out << endl << "products: " << p.NProducts << endl;

            out << endl << "production rate:" << endl << endl;

            for(unsigned int i=0; i<p.productionRate.size(); i++)
            {
                out << setw(3) << p.productionRate[i] << "\t ";
            }
            out << endl;

            out << endl << "demand:" << endl << endl;

            for(unsigned int i=0; i<p.demand.size(); i++)
            {
                out << setw(4) <<  p.demand[i] << "\t ";
            }

            out << endl << endl << "total outlets maximum inventory: " << p.totalMaximumOutletInventory << endl;

            out << endl << "outlets maximum inventory:" << endl << endl;

            for(unsigned int i=0; i<p.maximumOutletInventory.size(); i++)
            {
                out << setw(4) << p.maximumOutletInventory[i] << "\t ";
            }

            out << endl << endl << "total fatctory maximum inventory: " << p.totalMaximumInventory << endl;

            out << endl << "fatctory maximum inventory:" << endl << endl;

            for(unsigned int i=0; i<p.maximumInventory.size(); i++)
            {
                out << setw(4) << p.maximumInventory[i] << "\t ";
            }

            out << endl << endl << "maximum batch processing time: " << p.maxBatchProcessingTime << endl;

            return out;
        };

        friend ostream & LINGO_data (ostream &out, const problem &p)
        {
            out << "! products;" << endl << endl;

            for(unsigned int i=0; i<p.productionRate.size(); i++)
            {
                out << "P" << i+1;
                if((i+1) == p.productionRate.size())
                {
                    out << " ~" << endl;
                } else if((i+1) >= 20 && (i+1)%20 == 0)
                {
                    out << endl;
                }else
                {
                    out << " ";
                }
            }

            out << endl << "! production rate;" << endl << endl;

            for(unsigned int i=0; i<p.productionRate.size(); i++)
            {
                out << p.productionRate[i];
                if((i+1) == p.productionRate.size())
                {
                    out << " ~" << endl;
                } else if((i+1) >= 20 && (i+1)%20 == 0)
                {
                    out << endl;
                } else
                {
                    out << " ";
                }
            }

            out << endl << "! demand;" << endl << endl;

            for(unsigned int i=0; i<p.demand.size(); i++)
            {
                out << p.demand[i];
                if((i+1) == p.demand.size())
                {
                    out << " ~" << endl;
                } else if((i+1) >= 20 && (i+1)%20 == 0)
                {
                    out << endl;
                } else
                {
                    out << " ";
                }
            }

            out << endl << "! total outlets free inventory;" << endl << endl;

            out << p.totalMaximumOutletInventory << " ~" << endl;

            out << endl << "! outlets free inventory;" << endl << endl;

            for(unsigned int i=0; i<p.maximumOutletInventory.size(); i++)
            {
                out << p.maximumOutletInventory[i];
                if((i+1) == p.maximumOutletInventory.size())
                {
                    out << " ~" << endl;
                } else if((i+1) >= 20 && (i+1)%20 == 0)
                {
                    out << endl;
                }else
                {
                    out << " ";
                }
            }

            out << endl << "! total factory free inventory;" << endl << endl;

            out << p.totalMaximumInventory << " ~" << endl;

            out << endl << "! factory free inventory;" << endl << endl;

            for(unsigned int i=0; i<p.maximumInventory.size(); i++)
            {
                out << p.maximumInventory[i];
                if((i+1) == p.maximumInventory.size())
                {
                    out << " ~" << endl;
                } else if((i+1) >= 20 && (i+1)%20 == 0)
                {
                    out << endl;
                }else
                {
                    out << " ";
                }
            }

            out << endl << "! processing time limite;" << endl << endl;

            out << p.maxBatchProcessingTime << " ~";

            return out;
        };
    };

    struct solution{
        unsigned int processingTime; // batch processing time (min)
        vector<unsigned int> production = {}; // production for each product
        vector<unsigned int> deliver = {}; // production delivered
        vector<unsigned int> deliverToOutlets = {}; // production delivered to outlets
        vector<unsigned int> stock = {}; // production stocked at the factory

        vector<unsigned int> unmetDemand = {};
        vector<unsigned int> freeOutletsInventory = {};
        vector<unsigned int> freeFactoryInventory = {};
        int totalFreeOutletsInventory;
        int totalFreeFactoryInventory;

        solution& clear()
        {
            processingTime = 0;
            production.clear();
            deliver.clear();
            deliverToOutlets.clear();
            stock.clear();

            unmetDemand.clear();
            freeOutletsInventory.clear();
            freeFactoryInventory.clear();

            totalFreeOutletsInventory = 0;
            totalFreeFactoryInventory = 0;

            return *this;
        };

        solution()
        {
            clear();
        }

        ~solution()
        {
            clear();
        }

        solution& start(problem p)
        {
            production.resize(p.NProducts,0);
            deliver.resize(p.NProducts,0);
            deliverToOutlets.resize(p.NProducts,0);
            stock.resize(p.NProducts,0);

            unmetDemand.resize(p.NProducts,0);
            freeOutletsInventory.resize(p.NProducts,0);
            freeFactoryInventory.resize(p.NProducts,0);

            totalFreeOutletsInventory = p.totalMaximumOutletInventory;
            totalFreeFactoryInventory = p.totalMaximumInventory;

            return *this;
        };

        solution& analyticalMethod(problem p)
        {
            cout << endl << "applying Fraga's exact method for solving MBPTM problem ..." << endl;

            string site = getenv("HOME");
            site += "/COPSolver/results/output.txt";

            ofstream file;

            file.open(site);

            file << "Analytical solution:" << endl;

            struct timespec begin_time, finish_time, diff_time;
            char buff[100];

            timespec_get(&begin_time, TIME_UTC);
            strftime(buff, sizeof buff, "%D %T", gmtime(&begin_time.tv_sec));

            cout << endl << "starting time (s): " << buff << "." << begin_time.tv_nsec <<  " UTC" << endl;
            file << endl << "starting time (s): " << buff << "." << begin_time.tv_nsec <<  " UTC" << endl;

            // ***** calculating optimal batch processing time ***** //

            unsigned int aux, sum;

            for(unsigned int i=0; i<p.NProducts; i++)
            {
                unmetDemand[i] = p.demand[i];
            }

            processingTime = floor((p.maximumInventory[0] + p.maximumOutletInventory[0] + unmetDemand[0])/p.productionRate[0]);

            for(unsigned int i=1; i<p.NProducts; i++)
            {
                aux = floor((p.maximumInventory[i] + p.maximumOutletInventory[i] + unmetDemand[i])/p.productionRate[i]);
                if(aux < processingTime) processingTime = aux;
            }

            aux = 0;
            sum = 0;

            for(unsigned int i=0; i<p.NProducts; i++)
            {
                aux += unmetDemand[i];
                sum += p.productionRate[i];
            }

            aux += p.totalMaximumInventory + p.totalMaximumOutletInventory;

            aux = floor(aux/sum);

            if(aux < processingTime) processingTime = aux;

            //processingTime = /*T1 + */T2;

            if(processingTime > p.maxBatchProcessingTime) processingTime = p.maxBatchProcessingTime;

            file << endl << "Proessing time: " << processingTime << "\t max batch processing time: " << p.maxBatchProcessingTime << endl;
            file << endl << "batch processing time: " << processingTime << endl;

            cout << endl << "Proessing time: " << processingTime << "\t max batch processing time: " << p.maxBatchProcessingTime << endl;
            cout << endl << "batch processing time: " << processingTime << endl;


            // ***** calculating and distributing production ***** //

            unsigned int pos;

            file << endl << "Production:" << endl << endl;

            for(unsigned int i=0; i<p.NProducts; i++)
            {
                production[i] = p.productionRate[i] * processingTime;

                file << "P" << i << " = " << production[i] << endl;
            }

            file << endl << "Delivered:" << endl << endl;

            for(unsigned int i=0; i<p.NProducts; i++)
            {
                if(p.demand[i] < production[i])
                {
                    deliver[i] = p.demand[i];
                } else
                {
                    deliver[i] = production[i];
                }

                file << "D" << i << " = " << deliver[i] << endl;

                production[i] -= deliver[i];
            }


            file << endl << "Delivered to outlets:" << endl << endl;

            for(unsigned int i=0; i<p.NProducts; i++)
            {
                if(p.maximumOutletInventory[i] < production[i])
                {
                    deliverToOutlets[i] = p.maximumOutletInventory[i];
                } else
                {
                    deliverToOutlets[i] = production[i];
                }

                p.maximumOutletInventory[i] -=  deliverToOutlets[i];

                totalFreeOutletsInventory -= deliverToOutlets[i];

                file << "O" << i << " = " << deliverToOutlets[i] << endl;

                production[i] -= deliverToOutlets[i];
            }

            file << endl << "Leftover inventory in outlets: " << totalFreeOutletsInventory << endl;

            file << endl << "Stocked at factory:" << endl << endl;

            for(unsigned int i=0; i<p.NProducts; i++)
            {
                stock[i] = production[i];

                p.maximumInventory[i] -= stock[i];

                totalFreeFactoryInventory -= stock[i];

                file << "I" << i << " = " << stock[i] << endl;
            }

            file << endl << "Leftover inventory in factory: " << totalFreeFactoryInventory << endl << endl;

            file << endl << "Adjusting production distribution:" << endl << endl;

            if(totalFreeOutletsInventory < 0 || totalFreeFactoryInventory < 0)
            {
                unsigned int minimum;

                for(unsigned int i=0; i<p.NProducts; i++)
                {

                    if(totalFreeOutletsInventory < 0)
                    {
                        pos = - totalFreeOutletsInventory;

                        minimum = min(min(deliverToOutlets[i], p.maximumInventory[i]), pos);

                        deliverToOutlets[i] -= minimum;
                        stock[i] += minimum;

                        totalFreeOutletsInventory += minimum;

                        file << "O" << i << " = " << deliverToOutlets[i] << endl;
                        file << "I" << i << " = " << stock[i] << endl;

                    } else if(totalFreeFactoryInventory < 0)
                    {
                        pos = - totalFreeFactoryInventory;
                        minimum = min(min(stock[i], p.maximumOutletInventory[i]), pos);

                        stock[i] -= minimum;
                        deliverToOutlets[i] += minimum;

                        totalFreeFactoryInventory += minimum;

                        file << "O" << i << " = " << deliverToOutlets[i] << endl;
                        file << "I" << i << " = " << stock[i] << endl;
                    }

                    if(totalFreeOutletsInventory >= 0 and totalFreeFactoryInventory >= 0) break;
                }

                file << endl << "Leftover inventory in outlets: " << totalFreeOutletsInventory << endl;
                file << endl << "Leftover inventory in factory: " << totalFreeFactoryInventory << endl << endl;
            }

            for(unsigned int i=0; i<p.NProducts; i++)
            {
                unmetDemand[i] = p.demand[i] - deliver[i];
                freeOutletsInventory[i] = p.maximumOutletInventory[i] - deliverToOutlets[i];
                freeFactoryInventory[i] = p.maximumInventory[i] - stock[i];
            }

            timespec_get(&finish_time, TIME_UTC);
            strftime(buff, sizeof buff, "%D %T", gmtime(&finish_time.tv_sec));

            cout << endl << "finishing time (s): " << buff << "." << finish_time.tv_nsec <<  " UTC" << endl;
            file << endl << "finishing time (s): " << buff << "." << finish_time.tv_nsec <<  " UTC" << endl;

            diff_time.tv_sec = finish_time.tv_sec - begin_time.tv_sec;
            diff_time.tv_nsec = finish_time.tv_nsec - begin_time.tv_nsec;

            cout << endl << "Analytical solution execution time (s): " << double(diff_time.tv_sec) + double(diff_time.tv_nsec)/1000000000 << endl;
            file << endl << "execution time (s): " << double(diff_time.tv_sec) + double(diff_time.tv_nsec)/1000000000 << endl;

            file.close();

            return *this;
        };

    };

    class cop
    {
        protected:

        problem _problem;
        solution _solution;

        public:

        void clear();
        bool print();
        bool generateLingoData();

        bool get();
        void set(unsigned int NProducts, vector<float> productionRate, vector<unsigned int> demand, vector<unsigned int> maximumInventory, unsigned int totalMaximumInventory,
                 vector<unsigned int> maximumOutletInventory, unsigned int totalMaximumOutletInventory, unsigned int maxBatchProcessingTime);

        //cout << endl << "after get" << endl;
        //cout << endl << "applying Fraga's exact method for solving MBPTM problem, please wait ..." << endl;

        void MBPTM_02();
        void MBPTM_03();
        void MBPTM_10();
        void random(unsigned int problemSize);

        // solving

        void start(); // this function initializes solution variables
        solution analyticalMethod(); // this function solves the reported problem through the analytical method proposed by T. B. Fraga (2023)
    };
}

#endif // MULTIPRODUCT_BATCH_PROCESSING_TIME_MAXIMIZATION_PROBLEM_H_INCLUDED
