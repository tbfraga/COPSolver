/*********************************************************************** LICENSE ********************************************************************************************
Important: Copies and distributions of this file must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.
******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// version: 1.0-1_20230828
// developed by Tatiana Balbi Fraga
// start date: 2023/04/26
// last modification: 2023/08/28

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
        unsigned int _NProducts; // number of products
        vector<float> _productionRate = {}; // product weight ratio (g/m^2)

        vector<unsigned int> _demand = {}; // demand per product (g)

        vector<unsigned int> _maximumInventory = {}; // maximum inventory at factory per product (g)
        unsigned int _totalMaximumInventory; // total maximum inventory at factory (g)

        vector<unsigned int> _maximumOutletInventory = {}; // maximum outlet inventory per product (g)
        unsigned int _totalMaximumOutletInventory; // total maximum outlet inventory (g)

        unsigned int _maxBatchProcessingTime; // maximum batch processing time (min)
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
