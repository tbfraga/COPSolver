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
// last modification: 2023/10/25

#ifndef CLASSIFICATION_PROBLEM_H_INCLUDED
#define CLASSIFICATION_PROBLEM_H_INCLUDED

#include<vector>
#include <string>
#include <iterator>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "Eigen/Eigenvalues"
using namespace Eigen;
using namespace std;

namespace classp
{
    struct level{

        double value;

        level&  operator-- (int)  // postfix --
        {

            if(value <= 1/9)
            {
                cout << endl << "error: cannot reduce value <= 1/8 !" << endl;
                //getchar();
            }
           if(value >= 3)
            {
                value -= 2;
                cout << ">=3 -- new value: " << value << endl;
                //getchar();
            }else if(value <= 2)
            {
                value = 1/((1/value) + 2);
                cout << "<=1 -- new value: " << value << endl;
                //getchar();
            }
           return *this;
        };

        level  operator++ (int)  // postfix ++
        {
            if(value >= 9)
            {
                cout << endl << "error: cannot encrease value >= 8 !" << endl;
                //getchar();
            }else if(value >= 0.95)
            {
                value += 2;
                cout << ">=1 -- new value: " << value << endl;
            }else if(value < 1)
            {
                value = 1/((1/value) - 2);
                cout << "<1 -- new value: " << value << endl;
            }

            return *this;
        };

        level& operator=(double v)
        {
            value = v;
            return *this;
        };

        level& operator=(level v)
        {
            value = v.value;
            return *this;
        };

        friend ostream & operator << (ostream &out, const level &w)
        {
            out << w.value;
            return out;
        };

        friend istream & operator >> (istream &in,  level &w)
        {
            in >> w.value;
            return in;
        };
    };

    struct weight
    {
        double value;
        string criterion;

        friend ostream & operator << (ostream &out, const weight &w)
        {
            out << w.value;
            out << "\t" << w.criterion << endl;
            return out;
        };

        friend istream & operator >> (istream &in,  weight &w)
        {
            in >> w.value;
            in >> w.criterion;
            return in;
        };
    };

    struct pairwiseMatrix{
        vector<vector<level>> matrix;
        double mainEigenvalue;
        vector <double> mainEigenvector;
        double CR;

        double tol = 0.1;

        pairwiseMatrix()
        {
            mainEigenvalue = 0;
            CR = 0;

            mainEigenvector.clear();

            for(unsigned int s=0; s<matrix.size(); s++)
            {
                matrix[s].clear();
            }
            matrix.clear();
        }

        ~pairwiseMatrix()
        {
            mainEigenvalue = 0;
            CR = 0;

            mainEigenvector.clear();

            for(unsigned int s=0; s<matrix.size(); s++)
            {
                matrix[s].clear();
            }
            matrix.clear();
        }

        pairwiseMatrix resize(unsigned int s)
        {
            matrix.clear();
            matrix.resize(s);

            for(unsigned int i=0; i<matrix.size(); i++)
            {
                matrix[i].resize(s);
            }
        }

        friend ostream & operator << (ostream &out, const pairwiseMatrix &m)
        {
            cout << "pairwise comparison matrix: " << endl << endl;

            for(unsigned int i=0; i<m.matrix.size(); i++)
            {
                for(unsigned int j=0; j<m.matrix[i].size(); j++)
                {
                    cout << setprecision(3) << setw(5) << m.matrix[i][j] << "\t";
                }
                cout << endl;
            }

            cout << endl << "main eigenvalue: " << m.mainEigenvalue << endl;
            cout << endl << "main eigenvector: ";
            for(unsigned int s=0; s<m.mainEigenvector.size(); s++)
            {
                cout << setprecision(3) << m.mainEigenvector[s] << "\t";
            }
            cout << endl;

            cout << endl << "consistency rate: " << m.CR;

            if(m.CR <= 0.1)
            {
                cout << "\n\nCongratulations, your matrix of pairwise comparation is consistent !!! \n";
            }else
            {
                cout << "\n\nSorry, your matrix of pairwise comparation is inconsistent !!! \n";
            }

            return out;
        };

        friend istream & operator >> (istream &in,  pairwiseMatrix &m)
        {
            for(unsigned int i=0; i<m.matrix.size(); i++)
            {
                m.matrix[i][i].value = 1;
                for(unsigned int j=i+1; j<m.matrix[i].size(); j++)
                {
                    in >> m.matrix[i][j];

                    m.matrix[j][i].value = 1/(m.matrix[i][j].value);
                }
            }
            return in;
        };

        pairwiseMatrix& eigen()
        {
            vector<double> v;

            v.clear();

            for(unsigned int i=0; i<matrix.size(); i++)
            {
                for(unsigned int j=0; j<matrix[i].size(); j++)
                {
                    v.push_back(matrix[i][j].value);
                }
            }

            Eigen::MatrixXd m = Eigen::MatrixXd::Map(v.data(), matrix.size(), matrix.size()); // create matrix

            v.clear();

            Eigen::EigenSolver<Eigen::MatrixXd> X_eigen(m); // the instance X_eigen(m) includes the eigensystem

            Eigen::VectorXd eigen_values = X_eigen.eigenvalues().real();

            vector<double> values(eigen_values.size());
            Eigen::Map<Eigen::MatrixXd>(values.data(), eigen_values.rows(), eigen_values.cols()) = eigen_values;

            Eigen::MatrixXd eigen_vectors = X_eigen.eigenvectors().real();

            vector<double> vectors(eigen_vectors.size());
            Eigen::Map<Eigen::MatrixXd>(vectors.data(), eigen_vectors.rows(), eigen_vectors.cols()) = eigen_vectors;

            mainEigenvalue = values[0];
            mainEigenvector.assign (vectors.begin(),vectors.begin()+matrix.size());

            values.clear();
            vectors.clear();

            return *this;
        }

        pairwiseMatrix& consistencyRate()
        {
            eigen();

            vector<double> RI{0, 0, 0.58, 0.9, 1.12, 1.24, 1.32, 1.41, 1.45, 1.49};

            double CI = (mainEigenvalue - matrix.size()) / (matrix.size() - 1);
            CR = CI / RI[matrix.size()-1];

            RI.clear();

            return *this;
        };

        pairwiseMatrix& reduce(unsigned int n, unsigned int g, unsigned int s)
        {
            cout << endl << "reducing..." << endl;
            getchar();
            double auxCR;

            while(matrix[n][g].value*matrix[g][s].value > matrix[n][s].value)
            {
                cout << "1: " << matrix[n][g].value << "  2: " << matrix[n][s].value << endl;
                auxCR = CR;
                cout << endl << "CR: " << CR << endl;

                cout << "before --" << matrix[n][g].value << endl;

                matrix[n][g]--;
                matrix[g][n]++;

                cout << "after --" << matrix[n][g].value << endl;
                getchar();

                //getchar();

                eigen();
                consistencyRate();
                cout << endl << "CR: " << CR << endl;

                if(CR > auxCR)
                {
                    cout << endl << "undoing" << endl;
                    matrix[n][g]++;
                    matrix[g][n]--;

                    eigen();
                    consistencyRate();
                    break;
                }else if(CR <= tol)
                {
                    break;
                }
            }

            return *this;
        };

        pairwiseMatrix& encrease(unsigned int n, unsigned int g, unsigned int s)
        {
            cout << endl << "encreasing..." << endl;
            getchar();
            double auxCR;

            while(matrix[n][g].value*matrix[g][s].value < matrix[n][s].value)
            {
                cout << "1: " << matrix[n][g].value << "  2: " << matrix[n][s].value << endl;
                auxCR = CR;
                cout << endl << "CR: " << CR << endl;

                cout << "before ++" << matrix[n][s].value << endl;

                matrix[n][s]++;
                matrix[s][n]--;

                cout << "after --" << matrix[n][s].value << endl;
                getchar();

                //getchar();

                eigen();
                consistencyRate();
                cout << endl << "CR: " << CR << endl;

                if(CR > auxCR)
                {
                    cout << endl << "undoing" << endl;
                    matrix[n][s]--;
                    matrix[s][n]++;

                    eigen();
                    consistencyRate();
                    break;
                }else if(CR <= tol)
                {
                    break;
                }
            }

            return *this;
        };

        pairwiseMatrix& forceConsistency()
        {
            unsigned int g, s;

            consistencyRate();

            cout << endl << "CR: " << CR << endl;

            for(unsigned int sz=3; sz<matrix.size(); sz++)
            {
                for(unsigned int j=0; j<matrix.size()-2; j++)
                {
                    for(unsigned int k=j+1; k<matrix.size()-1; k++)
                    {
                        g = 0;
                        s = 0;

                        cout << endl << "a_nj: " << matrix[sz][j].value << "  a_nk: " << matrix[sz][k].value << "  a_jk: " << matrix[j][k].value << endl;


                        if(matrix[sz][j].value*matrix[j][k].value > matrix[sz][k].value)
                        {
                            g = j;
                            s = k;
                        }else if(matrix[sz][j].value*matrix[j][k].value < matrix[sz][k].value)
                        {
                            g = k;
                            s = j;
                        }

                        cout << endl << "g: " << g << "   s: " << s << endl;

                        if(g > 0 || s > 0)
                        {
                            reduce(sz,g,s);

                            if(CR <= tol)
                            {
                                break;
                            }else if(matrix[sz][g].value > matrix[sz][s].value)
                            {
                                encrease(sz,g,s);

                                if(CR <= tol)
                                {
                                    break;
                                }
                            }
                        }
                    }

                    if(CR <= tol)break;
                }
                if(CR <= tol)break;
            }

            return *this;
        };



        //Number& operator++ ();     // prefix ++: no parameter, returns a reference
        //Number  operator++ (int);  // postfix ++: dummy parameter, returns a value
    };

    struct problem{
        unsigned int _NCriteria; // number of criteria
        vector<weight> _weight; // criteria weight vector
        pairwiseMatrix _pairwiseWeight; // matrix of pairwise comparisons of the criteria
        unsigned int _NData; // number of data per criterion
        vector<vector<float>> _data; // data for each criterion - vector[_NCriteria, _NData]
    };

    struct solution{
        double CR;
    };

    class clssp
    {
        protected:

        problem _problem;
        solution _solution;

        public:

        void clear();
        bool get();
        bool print();

        double consistencyRate();
        bool constructivelyForceConsistency(double tol);
        bool forceConsistency(double tol, unsigned int k);
        bool reduce(double tol, unsigned int n, unsigned int g, unsigned int s);
        //bool (unsigned int i, unsigned int j);

        void ABC();
    };

}

#endif // CLASSIFICATION_PROBLEM_H_INCLUDED
