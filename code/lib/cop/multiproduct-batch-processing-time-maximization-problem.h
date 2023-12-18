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
// last modification: 2023/12/18

// future improvements: use operators overloading for defined structures. (will be done according to the needs)

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
        unsigned int _processingTime; // batch processing time (min)
        vector<unsigned int> _production = {}; // production for each product
        vector<unsigned int> _deliver = {}; // production delivered
        vector<unsigned int> _deliverToOutlets = {}; // production delivered to outlets
        vector<unsigned int> _stock = {}; // production stocked at the factory

        vector<unsigned int> _unmetDemand = {};
        vector<unsigned int> _freeOutletsInventory = {};
        vector<unsigned int> _freeFactoryInventory = {};
        int _totalFreeOutletsInventory;
        int _totalFreeFactoryInventory;
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
        unsigned int analyticalMethod(); // this function solves the reported problem through the analytical method proposed by T. B. Fraga (2023)
        solution analyticalMethod(unsigned int T1); // this function solves the reported problem through the analytical method proposed by T. B. Fraga (2023)
    };
}

#endif // MULTIPRODUCT_BATCH_PROCESSING_TIME_MAXIMIZATION_PROBLEM_H_INCLUDED
