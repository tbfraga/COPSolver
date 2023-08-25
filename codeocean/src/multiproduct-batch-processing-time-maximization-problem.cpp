/*********************************************************************** LICENSE ********************************************************************************************
Important: Copies and distributions of this file must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.
******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// version: 1.0-1 adapted to codeocean
// developed by Tatiana Balbi Fraga
// start date: 2023/08/25
// last modification: 2023/08/25

#include "../lib/multiproduct-batch-processing-time-maximization-problem.h"

namespace mbptm
{
    void cop::clear()
    {
        _problem._productionRate.clear();
        _problem._demand.clear();
        _problem._maximumInventory.clear();
        _problem._maximumOutletInventory.clear();

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
        string site = "results/problem.txt";

        ofstream file;

        file.open(site);

        file << "Multi-product batch processing time maximization problem " << endl;

        file << endl << "products: " << _problem._NProducts << endl;

        file << endl << "production rate:" << endl << endl;

        for(unsigned int p=0; p<_problem._productionRate.size(); p++)
        {
            file << setw(3) << _problem._productionRate[p] << "\t ";
        }
        file << endl;

        file << endl << "demand:" << endl << endl;

        for(unsigned int p=0; p<_problem._demand.size(); p++)
        {
            file << setw(4) <<  _problem._demand[p] << "\t ";
        }

        file << endl << endl << "total outlets maximum inventory: " << _problem._totalMaximumOutletInventory << endl;

        file << endl << "outlets maximum inventory:" << endl << endl;

        for(unsigned int p=0; p<_problem._maximumOutletInventory.size(); p++)
        {
            file << setw(4) << _problem._maximumOutletInventory[p] << "\t ";
        }

        file << endl << endl << "total fatctory maximum inventory: " << _problem._totalMaximumInventory << endl;

        file << endl << "fatctory maximum inventory:" << endl << endl;

        for(unsigned int p=0; p<_problem._maximumInventory.size(); p++)
        {
            file << setw(4) << _problem._maximumInventory[p] << "\t ";
        }

        file << endl << endl << "maximum batch processing time: " << _problem._maxBatchProcessingTime << endl;

        file.close();

        return 0;
    };

    bool cop::generateLingoData()
    {
        string site = "LINGOSolver/MBPTM/data.ldt";

        ofstream file;

        file.open(site);

        file << "! products;" << endl << endl;

        for(unsigned int p=0; p<_problem._productionRate.size(); p++)
        {
            file << "P" << p+1;
            if((p+1) == _problem._productionRate.size())
            {
                file << " ~" << endl;
            } else if((p+1) >= 20 && (p+1)%20 == 0)
            {
                file << endl;
            }else
            {
                file << " ";
            }
        }

        file << endl << "! production rate;" << endl << endl;

        for(unsigned int p=0; p<_problem._productionRate.size(); p++)
        {
            file << _problem._productionRate[p];
            if((p+1) == _problem._productionRate.size())
            {
                file << " ~" << endl;
            } else if((p+1) >= 20 && (p+1)%20 == 0)
            {
                file << endl;
            } else
            {
                file << " ";
            }
        }

        file << endl << "! demand;" << endl << endl;

        for(unsigned int p=0; p<_problem._demand.size(); p++)
        {
            file << _problem._demand[p];
            if((p+1) == _problem._demand.size())
            {
                file << " ~" << endl;
            } else if((p+1) >= 20 && (p+1)%20 == 0)
            {
                file << endl;
            } else
            {
                file << " ";
            }
        }

        file << endl << "! total outlets free inventory;" << endl << endl;

        file << _problem._totalMaximumOutletInventory << " ~" << endl;

        file << endl << "! outlets free inventory;" << endl << endl;

        for(unsigned int p=0; p<_problem._maximumOutletInventory.size(); p++)
        {
            file << _problem._maximumOutletInventory[p];
            if((p+1) == _problem._maximumOutletInventory.size())
            {
                file << " ~" << endl;
            } else if((p+1) >= 20 && (p+1)%20 == 0)
            {
                file << endl;
            }else
            {
                file << " ";
            }
        }

        file << endl << "! total factory free inventory;" << endl << endl;

        file << _problem._totalMaximumInventory << " ~" << endl;

        file << endl << "! factory free inventory;" << endl << endl;

        for(unsigned int p=0; p<_problem._maximumInventory.size(); p++)
        {
            file << _problem._maximumInventory[p];
            if((p+1) == _problem._maximumInventory.size())
            {
                file << " ~" << endl;
            } else if((p+1) >= 20 && (p+1)%20 == 0)
            {
                file << endl;
            }else
            {
                file << " ";
            }
        }

        file << endl << "! processing time limite;" << endl << endl;

        file << _problem._maxBatchProcessingTime << " ~";

        file.close();

        return 0;
    };

    bool cop::get()
    {
        clear();

        string site = "data/data.txt";

        fstream file;

        file.open(site);

        file >> _problem._NProducts;

        _problem._productionRate.resize(_problem._NProducts,0);

        for(unsigned int p=0; p<_problem._NProducts; p++)
        {
            file >> _problem._productionRate[p];
        }

        _problem._demand.resize(_problem._NProducts,0);

        for(unsigned int p=0; p<_problem._NProducts; p++)
        {
            file >> _problem._demand[p];
        }

        file >> _problem._totalMaximumOutletInventory;

       _problem._maximumOutletInventory.resize(_problem._NProducts,0);

        for(unsigned int p=0; p<_problem._NProducts; p++)
        {
            file >> _problem._maximumOutletInventory[p];
        }

        file >> _problem._totalMaximumInventory;

        _problem._maximumInventory.resize(_problem._NProducts,0);

        for(unsigned int p=0; p<_problem._NProducts; p++)
        {
            file >> _problem._maximumInventory[p];
        }

        file >> _problem._maxBatchProcessingTime;

        file.close();

        return 0;
    };

    void cop::set(unsigned int NProducts, vector<float> productionRate, vector<unsigned int> demand, vector<unsigned int> maximumInventory,
                  unsigned int totalMaximumInventory, vector<unsigned int> maximumOutletInventory, unsigned int totalMaximumOutletInventory, unsigned int maxBatchProcessingTime)
    {
        clear();

        _problem._NProducts = NProducts;
        _problem._productionRate = productionRate;
        _problem._demand = demand;
        _problem._maximumInventory = maximumInventory;
        _problem._totalMaximumInventory = totalMaximumInventory;
        _problem._maximumOutletInventory = maximumOutletInventory;
        _problem._totalMaximumOutletInventory = totalMaximumOutletInventory;
        _problem._maxBatchProcessingTime = maxBatchProcessingTime;
    };

    void cop::start()
    {
        _solution._production.resize(_problem._NProducts,0);
        _solution._deliver.resize(_problem._NProducts,0);
        _solution._deliverToOutlets.resize(_problem._NProducts,0);
        _solution._stock.resize(_problem._NProducts,0);

        _solution._unmetDemand.resize(_problem._NProducts,0);
        _solution._freeOutletsInventory.resize(_problem._NProducts,0);
        _solution._freeFactoryInventory.resize(_problem._NProducts,0);

        _solution._totalFreeOutletsInventory = _problem._totalMaximumOutletInventory;
        _solution._totalFreeFactoryInventory = _problem._totalMaximumInventory;
    };

    solution cop::analyticalMethod()
    {
        string site = "results/output.txt";

        ofstream file;

        file.open(site);

        file << "Fraga's exact method for solving MBPTM problem..." << endl;

        file << endl << "Analytical solution:" << endl;

        struct timespec begin_time, finish_time, diff_time;
        char buff[100];

        timespec_get(&begin_time, TIME_UTC);
        strftime(buff, sizeof buff, "%D %T", gmtime(&begin_time.tv_sec));

        file << endl << "starting time (s): " << buff << "." << begin_time.tv_nsec <<  " UTC" << endl;

        // ***** calculating optimal batch processing time ***** //

        unsigned int aux, sum;

        for(unsigned int p=0; p<_problem._NProducts; p++)
        {
            _solution._unmetDemand[p] = _problem._demand[p];
        }

        _solution._processingTime = floor((_problem._maximumInventory[0] + _problem._maximumOutletInventory[0] + _solution._unmetDemand[0])/_problem._productionRate[0]);

        for(unsigned int p=1; p<_problem._NProducts; p++)
        {
            aux = floor((_problem._maximumInventory[p] + _problem._maximumOutletInventory[p] + _solution._unmetDemand[p])/_problem._productionRate[p]);
            if(aux < _solution._processingTime) _solution._processingTime = aux;
        }

        aux = 0;
        sum = 0;

        for(unsigned int p=0; p<_problem._NProducts; p++)
        {
            aux += _solution._unmetDemand[p];
            sum += _problem._productionRate[p];
        }

        aux += _problem._totalMaximumInventory + _problem._totalMaximumOutletInventory;

        aux = floor(aux/sum);

        if(aux < _solution._processingTime) _solution._processingTime = aux;

        if(_solution._processingTime > _problem._maxBatchProcessingTime) _solution._processingTime = _problem._maxBatchProcessingTime;

        file << endl << "batch processing time: " << _solution._processingTime << endl;

        // ***** calculating and distributing production ***** //

        unsigned int pos;

        file << endl << "Production:" << endl << endl;

        for(unsigned int p=0; p<_problem._NProducts; p++)
        {
            _solution._production[p] = _problem._productionRate[p] * _solution._processingTime;

            file << "P" << p << " = " << _solution._production[p] << endl;
        }

        file << endl << "Delivered:" << endl << endl;

        for(unsigned int p=0; p<_problem._NProducts; p++)
        {
            if(_problem._demand[p] < _solution._production[p])
            {
                _solution._deliver[p] = _problem._demand[p];
            } else
            {
                _solution._deliver[p] = _solution._production[p];
            }

            file << "D" << p << " = " << _solution._deliver[p] << endl;

            _solution._production[p] -= _solution._deliver[p];
        }


        file << endl << "Delivered to outlets:" << endl << endl;

        for(unsigned int p=0; p<_problem._NProducts; p++)
        {
            if(_problem._maximumOutletInventory[p] < _solution._production[p])
            {
                _solution._deliverToOutlets[p] = _problem._maximumOutletInventory[p];
            } else
            {
                _solution._deliverToOutlets[p] = _solution._production[p];
            }

            _problem._maximumOutletInventory[p] -=  _solution._deliverToOutlets[p];

            _solution._totalFreeOutletsInventory -= _solution._deliverToOutlets[p];

            file << "O" << p << " = " << _solution._deliverToOutlets[p] << endl;

            _solution._production[p] -= _solution._deliverToOutlets[p];
        }

        file << endl << "Leftover inventory in outlets: " << _solution._totalFreeOutletsInventory << endl;

        file << endl << "Stocked at factory:" << endl << endl;

        for(unsigned int p=0; p<_problem._NProducts; p++)
        {
            _solution._stock[p] = _solution._production[p];

            _problem._maximumInventory[p] -= _solution._stock[p];

            _solution._totalFreeFactoryInventory -= _solution._stock[p];

            file << "I" << p << " = " << _solution._stock[p] << endl;
        }

        file << endl << "Leftover inventory in factory: " << _solution._totalFreeFactoryInventory << endl << endl;

        file << endl << "Adjusting production distribution:" << endl << endl;

        if(_solution._totalFreeOutletsInventory < 0 || _solution._totalFreeFactoryInventory < 0)
        {
            unsigned int minimum;

            for(unsigned int p=0; p<_problem._NProducts; p++)
            {

                if(_solution._totalFreeOutletsInventory < 0)
                {
                    pos = - _solution._totalFreeOutletsInventory;

                    minimum = min(min(_solution._deliverToOutlets[p],_problem._maximumInventory[p]), pos);

                    _solution._deliverToOutlets[p] -= minimum;
                    _solution._stock[p] += minimum;

                    _solution._totalFreeOutletsInventory += minimum;

                    file << "O" << p << " = " << _solution._deliverToOutlets[p] << endl;
                    file << "I" << p << " = " << _solution._stock[p] << endl;

                } else if(_solution._totalFreeFactoryInventory < 0)
                {
                    pos = - _solution._totalFreeFactoryInventory;
                    minimum = min(min(_solution._stock[p], _problem._maximumOutletInventory[p]), pos);

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

        for(unsigned int p=0; p<_problem._NProducts; p++)
        {
            _solution._unmetDemand[p] = _problem._demand[p] - _solution._deliver[p];
            _solution._freeOutletsInventory[p] = _problem._maximumOutletInventory[p] - _solution._deliverToOutlets[p];
            _solution._freeFactoryInventory[p] = _problem._maximumInventory[p] - _solution._stock[p];
        }

        timespec_get(&finish_time, TIME_UTC);
        strftime(buff, sizeof buff, "%D %T", gmtime(&finish_time.tv_sec));

        file << endl << "finishing time (s): " << buff << "." << finish_time.tv_nsec <<  " UTC" << endl;

        diff_time.tv_sec = finish_time.tv_sec - begin_time.tv_sec;
        diff_time.tv_nsec = finish_time.tv_nsec - begin_time.tv_nsec;

        file << endl << "execution time (s): " << double(diff_time.tv_sec) + double(diff_time.tv_nsec)/1000000000 << endl;


        file << "Thaks for using COPSolver :)))" << endl << endl;
        file << "COPSolver was (and is being) developed by Fraga, T.B. with purpose of solving many differente combinatorial optimizations problems." << endl << endl;
        file << "COPSolver is licenced by Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0)" << endl << endl;
        file << "Under this licence you can:" << endl << endl;
        file << "1) Free dowload and/or use this solver (except for comercial purpose);" << endl;
        file << "2) Share this solver (if don't modified anyway) only if you inform a link for the original repository and for the license;" << endl;
        file << "3) Modify the solver for personal use, but not share modified version of solver." << endl << endl;
        file << "You cannot use COPSolver or any modified version for comercial purpose." << endl;
        file << "If you need or want to use COPSolver for any comercial purpose, please contact tatiana.balbi@ufpe.br." << endl << endl;
        file << "If you use this solver for work or science, please don't forget to correctly cite it on presentations and the published material." << endl << endl;
        file << "repository: github.com/tbfraga/COPSolver" << endl;

        file.close();

        return _solution;
    };
}
