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

#include "../../lib/cop/multiproduct-batch-processing-time-maximization-problem.h"

namespace mbptm
{
    void cop::clear()
    {
        _problem.clear();

        _solution._production.clear();
        _solution._deliver.clear();
        _solution._deliverToOutlets.clear();
        _solution._stock.clear();

        _solution._unmetDemand.clear();
        _solution._freeOutletsInventory.clear();
        _solution._freeFactoryInventory.clear();
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
        _solution._production.resize(_problem.NProducts,0);
        _solution._deliver.resize(_problem.NProducts,0);
        _solution._deliverToOutlets.resize(_problem.NProducts,0);
        _solution._stock.resize(_problem.NProducts,0);

        _solution._unmetDemand.resize(_problem.NProducts,0);
        _solution._freeOutletsInventory.resize(_problem.NProducts,0);
        _solution._freeFactoryInventory.resize(_problem.NProducts,0);

        _solution._totalFreeOutletsInventory = _problem.totalMaximumOutletInventory;
        _solution._totalFreeFactoryInventory = _problem.totalMaximumInventory;
    };

    unsigned int cop::analyticalMethod()
    {
        cout << endl << "applying Fraga's exact method for solving MBPTM problem, please wait ..." << endl;

        string site = getenv("HOME");
        site += "/COPSolver/results/output.txt";

        ofstream file;

        file.open(site);

        cout << endl << endl << "Analytical solution:" << endl;
        file << "Analytical solution:" << endl << endl;

        unsigned int aux, sum, T1, T2;

        T1 = floor(_problem.demand[0]/_problem.productionRate[0]);

        for(unsigned int p=1; p<_problem.NProducts; p++)
        {
            aux = floor(_problem.demand[p]/_problem.productionRate[p]);
            if(aux < T1) T1 = aux;
        }

        vector<unsigned int> S;
        S.resize(_problem.NProducts,0);

        for(unsigned int p=0; p<_problem.NProducts; p++)
        {
            S[p] = _problem.demand[p] - T1*_problem.productionRate[p];
        }

        T2 = floor((_problem.maximumInventory[0] + _problem.maximumOutletInventory[0] + S[0])/_problem.productionRate[0]);

        for(unsigned int p=1; p<_problem.NProducts; p++)
        {
            aux = floor((_problem.maximumInventory[p] + _problem.maximumOutletInventory[p] + S[p])/_problem.productionRate[p]);
            if(aux < T2) T2 = aux;
        }

        aux = 0;
        sum = 0;

        for(unsigned int p=0; p<_problem.NProducts; p++)
        {
            aux += S[p];
            sum += _problem.productionRate[p];
        }

        aux += _problem.totalMaximumInventory + _problem.totalMaximumOutletInventory;

        aux = floor(aux/sum);

        if(aux < T2) T2 = aux;

        _solution._processingTime = T1 + T2;

        if(_solution._processingTime > _problem.maxBatchProcessingTime) _solution._processingTime = _problem.maxBatchProcessingTime;

        file << "T': " << T1 << "\t T'': " << T2 << "\t max batch processing time: " << _problem.maxBatchProcessingTime << endl;
        file << endl << "batch processing time: " << _solution._processingTime << endl;

        cout << endl << "T': " << T1 << "\t T'': " << T2 << "\t max batch processing time: " << _problem.maxBatchProcessingTime << endl;
        cout << endl << "batch processing time: " << _solution._processingTime << endl << endl;

        S.clear();
        file.close();

        return _solution._processingTime;
    };

    solution cop::analyticalMethod(unsigned int T1)
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

        unsigned int aux, sum, T2;

        if (T1 > floor(_problem.demand[0]/_problem.productionRate[0]))
        {
            T1 = floor(_problem.demand[0]/_problem.productionRate[0]);

            for(unsigned int p=1; p<_problem.NProducts; p++)
            {
                aux = floor(_problem.demand[p]/_problem.productionRate[p]);
                if(aux < T1) T1 = aux;
            }
        }

        for(unsigned int p=0; p<_problem.NProducts; p++)
        {
            _solution._unmetDemand[p] = _problem.demand[p] - T1*_problem.productionRate[p];
        }

        T2 = floor((_problem.maximumInventory[0] + _problem.maximumOutletInventory[0] + _solution._unmetDemand[0])/_problem.productionRate[0]);

        for(unsigned int p=1; p<_problem.NProducts; p++)
        {
            aux = floor((_problem.maximumInventory[p] + _problem.maximumOutletInventory[p] + _solution._unmetDemand[p])/_problem.productionRate[p]);
            if(aux < T2) T2 = aux;
        }

        aux = 0;
        sum = 0;

        for(unsigned int p=0; p<_problem.NProducts; p++)
        {
            aux += _solution._unmetDemand[p];
            sum += _problem.productionRate[p];
        }

        aux += _problem.totalMaximumInventory + _problem.totalMaximumOutletInventory;

        aux = floor(aux/sum);

        if(aux < T2) T2 = aux;

        _solution._processingTime = T1 + T2;

        if(_solution._processingTime > _problem.maxBatchProcessingTime) _solution._processingTime = _problem.maxBatchProcessingTime;

        file << endl << "T': " << T1 << "\t T'': " << T2 << "\t max batch processing time: " << _problem.maxBatchProcessingTime << endl;
        file << endl << "batch processing time: " << _solution._processingTime << endl;

        cout << endl << "T': " << T1 << "\t T'': " << T2 << "\t max batch processing time: " << _problem.maxBatchProcessingTime << endl;
        cout << endl << "batch processing time: " << _solution._processingTime << endl;


        // ***** calculating and distributing production ***** //

        unsigned int pos;

        file << endl << "Production:" << endl << endl;

        for(unsigned int p=0; p<_problem.NProducts; p++)
        {
            _solution._production[p] = _problem.productionRate[p] * _solution._processingTime;

            file << "P" << p << " = " << _solution._production[p] << endl;
        }

        file << endl << "Delivered:" << endl << endl;

        for(unsigned int p=0; p<_problem.NProducts; p++)
        {
            if(_problem.demand[p] < _solution._production[p])
            {
                _solution._deliver[p] = _problem.demand[p];
            } else
            {
                _solution._deliver[p] = _solution._production[p];
            }

            file << "D" << p << " = " << _solution._deliver[p] << endl;

            _solution._production[p] -= _solution._deliver[p];
        }


        file << endl << "Delivered to outlets:" << endl << endl;

        for(unsigned int p=0; p<_problem.NProducts; p++)
        {
            if(_problem.maximumOutletInventory[p] < _solution._production[p])
            {
                _solution._deliverToOutlets[p] = _problem.maximumOutletInventory[p];
            } else
            {
                _solution._deliverToOutlets[p] = _solution._production[p];
            }

            _problem.maximumOutletInventory[p] -=  _solution._deliverToOutlets[p];

            _solution._totalFreeOutletsInventory -= _solution._deliverToOutlets[p];

            file << "O" << p << " = " << _solution._deliverToOutlets[p] << endl;

            _solution._production[p] -= _solution._deliverToOutlets[p];
        }

        file << endl << "Leftover inventory in outlets: " << _solution._totalFreeOutletsInventory << endl;

        file << endl << "Stocked at factory:" << endl << endl;

        for(unsigned int p=0; p<_problem.NProducts; p++)
        {
            _solution._stock[p] = _solution._production[p];

            _problem.maximumInventory[p] -= _solution._stock[p];

            _solution._totalFreeFactoryInventory -= _solution._stock[p];

            file << "I" << p << " = " << _solution._stock[p] << endl;
        }

        file << endl << "Leftover inventory in factory: " << _solution._totalFreeFactoryInventory << endl << endl;

        file << endl << "Adjusting production distribution:" << endl << endl;

        if(_solution._totalFreeOutletsInventory < 0 || _solution._totalFreeFactoryInventory < 0)
        {
            unsigned int minimum;

            for(unsigned int p=0; p<_problem.NProducts; p++)
            {

                if(_solution._totalFreeOutletsInventory < 0)
                {
                    pos = - _solution._totalFreeOutletsInventory;

                    minimum = min(min(_solution._deliverToOutlets[p],_problem.maximumInventory[p]), pos);

                    _solution._deliverToOutlets[p] -= minimum;
                    _solution._stock[p] += minimum;

                    _solution._totalFreeOutletsInventory += minimum;

                    file << "O" << p << " = " << _solution._deliverToOutlets[p] << endl;
                    file << "I" << p << " = " << _solution._stock[p] << endl;

                } else if(_solution._totalFreeFactoryInventory < 0)
                {
                    pos = - _solution._totalFreeFactoryInventory;
                    minimum = min(min(_solution._stock[p], _problem.maximumOutletInventory[p]), pos);

                    _solution._stock[p] -= minimum;
                    _solution._deliverToOutlets[p] += minimum;

                    _solution._totalFreeFactoryInventory += minimum;

                    file << "O" << p << " = " << _solution._deliverToOutlets[p] << endl;
                    file << "I" << p << " = " << _solution._stock[p] << endl;
                }
                if(_solution._totalFreeOutletsInventory >= 0 and _solution._totalFreeFactoryInventory >= 0) break;
            }

            file << endl << "Leftover inventory in outlets: " << _solution._totalFreeOutletsInventory << endl;
            file << endl << "Leftover inventory in factory: " << _solution._totalFreeFactoryInventory << endl << endl;
        }

        for(unsigned int p=0; p<_problem.NProducts; p++)
        {
            _solution._unmetDemand[p] = _problem.demand[p] - _solution._deliver[p];
            _solution._freeOutletsInventory[p] = _problem.maximumOutletInventory[p] - _solution._deliverToOutlets[p];
            _solution._freeFactoryInventory[p] = _problem.maximumInventory[p] - _solution._stock[p];
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

        return _solution;
    };
}
