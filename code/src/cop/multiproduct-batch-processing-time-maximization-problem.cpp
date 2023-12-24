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

#include "../../lib/cop/multiproduct-batch-processing-time-maximization-problem.h"

namespace mbptm
{
    void cop::clear()
    {
        _problem.clear();
        _solution.clear();
    };

    bool cop::print()
    {
        string site = getenv("HOME");
        site += "/COPSolver/results/problem.txt";

        ofstream file;

        file.open(site);

        if (!file)
        {
                cerr << "Cannot open output file " << site << " !" << endl;
                return 1;
        } else
        {
            file << _problem;
        }



        file.close();

        return 0;
    };

    bool cop::generateLingoData()
    {
        cout << endl << "generating LINGO data ..." << endl;

        string site = getenv("HOME");
        site += "/COPSolver/LINGOSolver/MBPTM/data.ldt";

        ofstream file;

        file.open(site);

        if (!file)
        {
                cerr << "Cannot open output file " << site << " !" << endl;
                return 1;
        } else
        {
            LINGO_data(file, _problem) ;
            file.close();
        }

        return 0;
    };

    bool cop::get()
    {
        clear();

        string site = getenv("HOME");
        site += "/COPSolver/data/data.txt";

        fstream file;

        file.open(site);

        if (!file)
        {
                cerr << "Cannot open file " << site << " !" << endl;
                return 1;
        } else
        {
            file >> _problem;
            file.close();
        }

        return 0;
    };

    void cop::set(unsigned int NProducts, vector<float> productionRate, vector<unsigned int> demand, vector<unsigned int> maximumInventory,
                  unsigned int totalMaximumInventory, vector<unsigned int> maximumOutletInventory, unsigned int totalMaximumOutletInventory, unsigned int maxBatchProcessingTime)
    {
        clear();

        _problem.NProducts = NProducts;
        _problem.productionRate = productionRate;
        _problem.demand = demand;
        _problem.maximumInventory = maximumInventory;
        _problem.totalMaximumInventory = totalMaximumInventory;
        _problem.maximumOutletInventory = maximumOutletInventory;
        _problem.totalMaximumOutletInventory = totalMaximumOutletInventory;
        _problem.maxBatchProcessingTime = maxBatchProcessingTime;
    };

    void cop::MBPTM_02()
    {
        /**************************************************************************************************************************
        Small problem developed to test the solver.
        **************************************************************************************************************************/
        clear();

        _problem.NProducts = 2;
        _problem.productionRate = {60,40};
        _problem.demand = {1000,500};
        _problem.maximumOutletInventory = {600,600};
        _problem.totalMaximumOutletInventory = 1000;
        _problem.maximumInventory = {3000,2000};
        _problem.totalMaximumInventory = 3000;
        _problem.maxBatchProcessingTime = 100;
    };

    void cop::MBPTM_03()
    {
        /**************************************************************************************************************************
        Small problem developed to test the solver.
        **************************************************************************************************************************/
        clear();

        _problem.NProducts = 3;
        _problem.productionRate = {60,40,50};
        _problem.demand = {1000,500,800};
        _problem.maximumOutletInventory = {600,600,600};
        _problem.totalMaximumOutletInventory = 1500;
        _problem.maximumInventory = {3000,2000,1000};
        _problem.totalMaximumInventory = 3500;
        _problem.maxBatchProcessingTime = 100;
    };

    void cop::MBPTM_10()
    {
        /**************************************************************************************************************************
        Small problem developed to test the solver.
        **************************************************************************************************************************/
        clear();

        _problem.NProducts = 10;
        _problem.productionRate = {60,40,50,40,30,50,60,10,20,40};
        _problem.demand = {1000,500,800,500,400,500,2000,300,500,1000};
        _problem.maximumOutletInventory = {600,600,600,1500,300,200,500,800,0,200};
        _problem.totalMaximumOutletInventory = 3000;
        _problem.maximumInventory = {3000,2000,1000,800,3000,1000,400,300,200,0};
        _problem.totalMaximumInventory = 5000;
        _problem.maxBatchProcessingTime = 100;
    };

    void cop::random(unsigned int problemSize)
    {
        clear();

        _problem.NProducts = problemSize;

        _problem.productionRate.resize(_problem.NProducts,0);
        _problem.demand.resize(_problem.NProducts,0);
        _problem.maximumInventory.resize(_problem.NProducts,0);
        _problem.maximumOutletInventory.resize(_problem.NProducts,0);

        unsigned int seed1 = rand()%3000 + 500;
        unsigned int seed2 = rand()%5000 + 1000;

        _problem.totalMaximumOutletInventory = (_problem.NProducts/2)*seed1;
        _problem.totalMaximumInventory = (_problem.NProducts/2)*seed2;

        for(unsigned int p=0; p<_problem.NProducts; p++)
        {
            _problem.productionRate[p] = rand()%30 + 10;
            _problem.demand[p] = rand()%3000 + 800;
            _problem.maximumOutletInventory[p] = rand()%(seed1-500) + 500;
            _problem.maximumInventory[p] = rand()%(seed2 - 1000) + 1000;
        }

        _problem.maxBatchProcessingTime = 100;
    };

    void cop::start()
    {
        _solution.start(_problem);
    };

    solution cop::analyticalMethod()
    {
        _solution.analyticalMethod(_problem);

        return _solution;
    };
}
