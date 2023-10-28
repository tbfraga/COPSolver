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
// last modification: 2023/10/27

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

        vector<double> scale{0.111,0.143,0.200,0.333,1,3,5,7,9};

        double value;
        unsigned int it;

        level  operator-- (int)  // postfix --
        {
            if(it == 0)
            {
                cout << endl << "error: cannot reduce level 1/9 !" << endl;
                getchar();
            }
            else
            {
                it--;
                value = scale[it];
            }

           return *this;
        };

        level  operator++ (int)  // postfix ++
        {
            if(it == 8)
            {
                cout << endl << "error: cannot encrease value 9 !" << endl;
                getchar();
            }else
            {
                it++;
                value = scale[it];
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

    struct criteria
    {
        string criterion;
        string object;
        string operationA;
        double valueA;
        string operationB;
        double valueB;
        string operationC;
        double valueC;

        friend istream & operator >> (istream &in,  criteria &c)
        {
            in >> c.criterion;
            in >> c.object;
            in >> c.operationA;
            in >> c.valueA;
            in >> c.operationB;
            in >> c.valueB;
            in >> c.operationC;
            in >> c.valueC;
            return in;
        };

        friend ostream & operator << (ostream &out, const criteria &c)
        {
            out << c.criterion;
            return out;
        };
    };

    struct weight
    {
        double value;
        criteria criterion;

        weight& operator=(double v)
        {
            value = v;
            return *this;
        };

        friend ostream & operator << (ostream &out, const weight &w)
        {
            out << setprecision(3) << setw(6) << w.value;
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

        pairwiseMatrix& clear()
        {
            for(unsigned int s=0; s<matrix.size(); s++)
            {
                matrix[s].clear();
            }

            matrix.clear();

            mainEigenvalue = 0;
            mainEigenvector.clear();
            CR = 0;

            return *this;
        }

        pairwiseMatrix()
        {
            clear();
        }

        ~pairwiseMatrix()
        {
            clear();
        }

        pairwiseMatrix& resize(unsigned int s)
        {
            matrix.clear();
            matrix.resize(s);

            for(unsigned int i=0; i<matrix.size(); i++)
            {
                matrix[i].resize(s);
            }

            return *this;
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

            cout << "\npairwise comparison matrix it: " << endl << endl;

            for(unsigned int i=0; i<m.matrix.size(); i++)
            {
                for(unsigned int j=0; j<m.matrix[i].size(); j++)
                {
                    cout << setprecision(3) << setw(5) << m.matrix[i][j].it << "\t";
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
                m.matrix[i][i].it = 4;
                for(unsigned int j=i+1; j<m.matrix[i].size(); j++)
                {
                    in >> m.matrix[i][j];

                    for(unsigned int s=0; s<m.matrix[i][j].scale.size(); s++)
                    {
                        if(m.matrix[i][j].value >= m.matrix[i][j].scale[s] - 0.0005 && m.matrix[i][j].value <= m.matrix[i][j].scale[s] + 0.0005)
                        {
                            m.matrix[i][j].it = s;
                            m.matrix[j][i].it = 8 - s;
                            break;
                        }
                    }

                    //m.matrix[i][j].value = m.matrix[i][j].scale[m.matrix[i][j].it];
                    m.matrix[j][i].value = m.matrix[j][i].scale[m.matrix[j][i].it];
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
            double auxCR;

            while(matrix[n][g].value*matrix[g][s].value > matrix[n][s].value && matrix[n][g].it != 0)
            {
                auxCR = CR;

                matrix[n][g]--;
                matrix[g][n]++;

                consistencyRate();

                if(CR > auxCR)
                {
                    matrix[n][g]++;
                    matrix[g][n]--;

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
            double auxCR;

            while(matrix[n][g].value*matrix[g][s].value < matrix[n][s].value && matrix[n][g].it != 8)
            {
                auxCR = CR;

                matrix[n][s]++;
                matrix[s][n]--;

                consistencyRate();

                if(CR > auxCR)
                {
                    matrix[n][s]--;
                    matrix[s][n]++;

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

            if(CR > tol){
            for(unsigned int sz=3; sz<matrix.size(); sz++)
            {
                for(unsigned int j=0; j<matrix.size()-2; j++)
                {
                    for(unsigned int k=j+1; k<matrix.size()-1; k++)
                    {
                        g = 0;
                        s = 0;

                        if(matrix[sz][j].value*matrix[j][k].value > matrix[sz][k].value)
                        {
                            g = j;
                            s = k;
                        }else if(matrix[sz][j].value*matrix[j][k].value < matrix[sz][k].value)
                        {
                            g = k;
                            s = j;
                        }

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
            }}

            return *this;
        };

        //Number& operator++ ();     // prefix ++: no parameter, returns a reference
        //Number  operator++ (int);  // postfix ++: dummy parameter, returns a value
    };

    struct problem{
        unsigned int NCriteria; // number of criteria
        vector<weight> weightVector; // criteria weight vector
        pairwiseMatrix pairwiseWeight; // matrix of pairwise comparisons of the criteria
        unsigned int NData; // number of data per criterion
        vector<vector<double>> data; // data for each criterion - vector[_NCriteria, _NData]

        problem& clear()
        {
            NCriteria = 0;
            weightVector.clear();
            pairwiseWeight.clear();
            NData = 0;
            for(unsigned int s=0; s<data.size(); s++)
            {
                data[s].clear();
            }
            data.clear();

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
                cout << endl << "error: operator >> for struc problem is only defined for geting data from file !!!" << endl << endl;
                p.clear();
            }else
            {
                in.ignore(std::numeric_limits<std::streamsize>::max(),':');

                in >> p.NCriteria;

                in.ignore(std::numeric_limits<std::streamsize>::max(),':');

                p.weightVector.resize(p.NCriteria);

                for(unsigned int s=0; s<p.weightVector.size(); s++)
                {
                    in >> p.weightVector[s];
                }

                in.ignore(std::numeric_limits<std::streamsize>::max(),':');

                p.pairwiseWeight.resize(p.NCriteria);

                in >> p.pairwiseWeight;

                in.ignore(std::numeric_limits<std::streamsize>::max(),':');

                in >> p.NData;

                in.ignore(std::numeric_limits<std::streamsize>::max(),':');

                p.data.resize(p.NData);

                for(unsigned int i=0; i<p.data.size(); i++)
                {
                    p.data[i].resize(p.NCriteria);
                    for(unsigned int j=0; j<p.data[i].size(); j++)
                    {
                        in >> p.data[i][j];
                    }
                }
            }

            return in;
        };

        problem& weightNormalize()
        {
            double sum = 0;

            for(unsigned s=0; s<weightVector.size(); s++)
            {
                sum += weightVector[s].value;
            }

            for(unsigned s=0; s<weightVector.size(); s++)
            {
                weightVector[s].value = weightVector[s].value/sum;
            }

            return *this;
        };
    };

    struct solution{

        vector<vector<double>> perMatrix;
        vector<vector<unsigned int>> ABCMatrix;
        vector<vector<double>> acmSumMatrix;
        vector<double> weight;
        vector<unsigned int> classification;

        solution& clear()
        {
            for(unsigned int s=0; s<perMatrix.size(); s++)
            {
                perMatrix[s].clear();
            }

            perMatrix.clear();

            for(unsigned int s=0; s<ABCMatrix.size(); s++)
            {
                ABCMatrix[s].clear();
            }

            ABCMatrix.clear();

            weight.clear();
            classification.clear();

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

        solution& resize(problem p)
        {
            perMatrix.resize(p.NData);

            for(unsigned int i=0; i<perMatrix.size(); i++)
            {
                perMatrix[i].resize(p.NCriteria);
            }

            ABCMatrix.resize(p.NData);

            for(unsigned int i=0; i<ABCMatrix.size(); i++)
            {
                ABCMatrix[i].resize(p.NCriteria);
            }

            weight.resize(p.NData);

            return *this;
        };

        friend ostream & operator << (ostream &out, const solution &s)
        {
            cout << "--> Solution: " << endl << endl;

            cout << "percentil data matrix: " << endl << endl;

            for(unsigned int i=0; i<s.perMatrix.size(); i++)
            {
                for(unsigned int j=0; j<s.perMatrix[i].size(); j++)
                {
                    cout << setprecision(4) << setw(4) << s.perMatrix[i][j] << "\t";
                }
                cout << endl;
            }

            cout << endl << "ABC classification matrix: " << endl << endl;

            for(unsigned int i=0; i<s.ABCMatrix.size(); i++)
            {
                for(unsigned int j=0; j<s.ABCMatrix[i].size(); j++)
                {
                    cout << setprecision(4) << setw(4) << s.ABCMatrix[i][j] << "\t";
                }
                cout << endl;
            }

            cout << endl << "weight: " << endl << endl;

            for(unsigned int i=0; i<s.weight.size(); i++)
            {
                cout << setprecision(4) << setw(4) << s.weight[i] << "\t";
            }
            cout << endl;

            return out;
        };

        solution& percentilMatrix(problem p)
        {
            double sum;

            for(unsigned int c=0; c<perMatrix[0].size(); c++)
            {
                sum = 0;

                for(unsigned int d=0; d<perMatrix.size(); d++)
                {
                    sum += p.data[d][c];
                }

                for(unsigned int d=0; d<perMatrix.size(); d++)
                {
                    if(sum == 0)
                    {
                        perMatrix[d][c] = 0;
                    }else
                    {
                        perMatrix[d][c] = 100*(p.data[d][c]/sum);
                    }
                }
            }

            return *this;
        };

        solution& ABC(problem p)
        {
            unsigned int it, product;

            resize(p);
            percentilMatrix(p);

            for(unsigned int c=0; c<ABCMatrix[0].size(); c++)
            {
                for(unsigned int d=0; d<ABCMatrix.size(); d++)
                {
                    it = d;

                    for(unsigned int l=0; l<d; l++) // finding position
                    {
                        product = ABCMatrix[l][c];

                        if(perMatrix[d][c] < perMatrix[product][c])
                        {
                            it = l;

                            for(unsigned int p=d-1; p>l; p--) // relocation
                            {
                                ABCMatrix[p+1][c] = ABCMatrix[p][c];
                            }

                            ABCMatrix[l+1][c] = ABCMatrix[l][c];

                            break;
                        }
                    }

                    ABCMatrix[it][c] = d;
                }
            }

            return *this;
        };

        solution& analyticHierarchyProcess(problem p)
        {
            ABC(p);

            for(unsigned int i=0; i<perMatrix.size(); i++)
            {
                weight[i] = 0;
                for(unsigned int j=0; j<perMatrix[i].size(); j++)
                {
                    weight[i] += perMatrix[i][j]*p.weightVector[j].value;
                }
            }

            return *this;
        };
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

        //bool (unsigned int i, unsigned int j);

        bool ABC();
        bool analyticHierarchyProcess();
    };

}

#endif // CLASSIFICATION_PROBLEM_H_INCLUDED
