/*********************************************************************** LICENSE ********************************************************************************************
Important: Copies and distributions of this file must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.
******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// version:
// developed by Tatiana Balbi Fraga
// start date: 2023/10/18
// last modification: 2023/10/18

#include "../lib/classification-problem.h"

namespace classp
{
    void clssp::clear()
    {
        _problem._Criteria.clear();

        _problem._Weight.clear();

        for(unsigned int s; s<_problem._pairwiseWeight.size(); s++)
        {
            _problem._pairwiseWeight[s].clear();
        }

        _problem._pairwiseWeight.clear();

        for(unsigned int s; s<_problem._Data.size(); s++)
        {
            _problem._Data[s].clear();
        }

        _problem._Data.clear();

    };

    bool clssp::get()
    {
        clear();

        string site = getenv("HOME");
        site += "/COPSolver/data/data.txt";

        fstream file;
        file.open(site);

        file.ignore(std::numeric_limits<std::streamsize>::max(),':');

        file >> _problem._NCriteria;

        file.ignore(std::numeric_limits<std::streamsize>::max(),':');

        _problem._Criteria.resize(_problem._NCriteria);

        for(unsigned int s=0; s<_problem._Criteria.size(); s++)
        {
            file >> _problem._Criteria[s];
        }

        file.ignore(std::numeric_limits<std::streamsize>::max(),':');

        _problem._Weight.resize(_problem._NCriteria);

        for(unsigned int s=0; s<_problem._Weight.size(); s++)
        {
            file >> _problem._Weight[s];

            if( isnan(_problem._Weight[s]))
            {
                _problem._Weight[s] = 0;
                break;
            }
        }

        file.ignore(std::numeric_limits<std::streamsize>::max(),':');

        _problem._pairwiseWeight.resize(_problem._NCriteria);

        for(unsigned int s=0; s<_problem._pairwiseWeight.size(); s++)
        {
            _problem._pairwiseWeight[s].resize(_problem._NCriteria);

            for(unsigned int ss=0; ss<_problem._pairwiseWeight[s].size(); ss++)
            {
                file >> _problem._pairwiseWeight[s][ss];
                cout << _problem._pairwiseWeight[s][ss] << "\t";
            }
        }

        file.ignore(std::numeric_limits<std::streamsize>::max(),':');

        file >> _problem._NData;

        _problem._Data.resize(_problem._NCriteria);

        file.ignore(std::numeric_limits<std::streamsize>::max(),':');

        for(unsigned int s=0; s<_problem._Data.size(); s++)
        {
            _problem._Data[s].resize(_problem._NData);

            for(unsigned int ss=0; ss<_problem._Data[s].size(); ss++)
            {
                file >> _problem._Data[s][ss];
            }
        }

        file.close();

        return 0;
    };

    bool clssp::print()
    {
        cout << "number of criteria: " << _problem._NCriteria << endl << endl;

        cout << "criteria: " << endl << endl;

        for(unsigned int s=0; s<_problem._Criteria.size(); s++)
        {
            cout << _problem._Criteria[s] << "  ";
        }

        cout << endl << endl;

        cout << "weight: " << endl << endl;

        for(unsigned int s=0; s<_problem._Weight.size(); s++)
        {
            cout << _problem._Weight[s] << "\t";
        }

        cout << endl << endl;

        cout << "pairwise comparison weight: " << endl << endl;

        for(unsigned int s=0; s<_problem._pairwiseWeight.size(); s++)
        {
            for(unsigned int ss=0; ss<_problem._pairwiseWeight[s].size(); ss++)
            {
                cout << _problem._pairwiseWeight[s][ss] << "\t";
            }

            cout << endl;
        }

        cout << endl;

        cout << "number of data per criterion: " << _problem._NData << endl << endl;

        cout << "data: " << endl << endl;

        for(unsigned int s=0; s<_problem._Data.size(); s++)
        {
            for(unsigned int ss=0; ss<_problem._Data[s].size(); ss++)
            {
                cout << _problem._Data[s][ss] << "\t";
            }

            cout << endl;
        }

        cout << endl;

        return 0;
    };

    bool clssp::consistency()
    {
        // Calculates eigenvalue and eigenvector for the pairwise comparation matrix, normalizes the eigenvector, and checks if the matrix is consistent.

        std::vector<double> v;

        vector<double> RI{0, 0, 0.58, 0.9, 1.12, 1.24, 1.32, 1.41, 1.45, 1.49};

        v.clear();
        for(unsigned int s=0; s<_problem._pairwiseWeight.size(); s++)
        {
            v.insert(v.end(),_problem._pairwiseWeight[s].begin(),_problem._pairwiseWeight[s].end());
        }

        Eigen::MatrixXd m = Eigen::MatrixXd::Map(v.data(), _problem._NCriteria, _problem._NCriteria); // create matrix

        Eigen::EigenSolver<Eigen::MatrixXd> X_eigen(m); // the instance X_eigen(m) includes the eigensystem

        cout << "\nm:\n\n" << m << "\n\neigenvalues:\n\n" << X_eigen.eigenvalues() << endl;
        cout << "\n\neigenvectors:\n\n" << X_eigen.eigenvectors() << endl;

        /*cout << "eigenvalues:" << endl;
        cout << X_eigen.eigenvalues()(0) << endl;
        cout << "eigenvectors=" << endl;
        cout << X_eigen.eigenvectors() << endl;*/

        Eigen::VectorXd eigen_values = X_eigen.eigenvalues().real();

        vector<double> values(eigen_values.size());
        Eigen::Map<Eigen::MatrixXd>(values.data(), eigen_values.rows(), eigen_values.cols()) = eigen_values;

        Eigen::MatrixXd eigen_vectors = X_eigen.eigenvectors().real();

        vector<double> vectors(eigen_vectors.size());
        Eigen::Map<Eigen::MatrixXd>(vectors.data(), eigen_vectors.rows(), eigen_vectors.cols()) = eigen_vectors;

        /*cout << "\nAutovalores: \n\n";

        for (const auto& x : values)
        cout << x << ", ";
        cout << "\n";

        cout << "\nAutovetores: \n\n";

        for (const auto& z : vectors)
        cout << z << ", ";
        cout << "\n";*/

        double eigenvalue = values[0];

        vector<double> eingenvector;
        eingenvector.assign (vectors.begin(),vectors.begin()+_problem._NCriteria);


        cout << "\nautovalor escolhido: " << eigenvalue << "\n";

        cout << "\nautovetor escolhido: \n\n";

        for (const auto& x : eingenvector)
        cout << x << ", ";
        cout << "\n";

        double sum = 0;

        for(unsigned int s=0; s<eingenvector.size(); s++)
        {
            sum += eingenvector[s];
        }

        cout << "\nsoma dos elementos do autovetor: " << sum << "\n";

        for(unsigned int s=0; s<eingenvector.size(); s++)
        {
            eingenvector[s] = eingenvector[s]/sum;
        }

        cout << "\nautovetor normalizado: \n\n";

        for (const auto& x : eingenvector)
        cout << x << ", ";
        cout << "\n";

        double CI = (eigenvalue - _problem._NCriteria) / (_problem._NCriteria - 1);

        cout << "\nCI: " << CI << "\n";
        cout << "\nRI[" << _problem._NCriteria << "]: " << RI[_problem._NCriteria-1] << "\n";

        double CR = CI / RI[_problem._NCriteria-1];

        cout << "\nCR: " << CR << "\n";

        if(CR <= 0.1)
        {
            cout << "\nCongratulations, your matrix of pairwise comparation is consistent !!! \n";
        }else
        {
            cout << "\nSorry, your matrix of pairwise comparation is inconsistent !!! \n";
        }

        return 0;
    };
}
