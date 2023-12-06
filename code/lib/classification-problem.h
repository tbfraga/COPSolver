/*********************************************************************** LICENSE ********************************************************************************************
Important: Copies and distributions of this file must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.

'COPSolver: library for solving classification problems' uses Eigen library.
For this reason, COPSolver repository contains a copy of the Eigen library.
Eigen is Free Software. Starting from the 3.1.1 version, it is licensed under the MPL2, which is a simple weak copyleft license.
For more details see https://eigen.tuxfamily.org/

******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// module: COPSolver: library for solving classification problems
// version: v2.0-1
// developed by Tatiana Balbi Fraga
// start date: 2023/10/18
// last modification: 2023/12/06

#ifndef CLASSIFICATION_PROBLEM_H_INCLUDED
#define CLASSIFICATION_PROBLEM_H_INCLUDED

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

#include <vector>
#include <iterator>
#include <bits/stdc++.h>
#include "Eigen/Eigenvalues"
using namespace Eigen;
using namespace std;

namespace clss
{
    struct level
    {
        vector<double> scale{0.111,0.143,0.200,0.333,1,3,5,7,9};

        double value;
        unsigned int it;

        level  operator-- (int)  // postfix --
        {
            if(it == 0)
            {
                cout << endl << "error: cannot reduce level " << scale[0] << " !" << endl;
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
            if(it == scale.size()-1)
            {
                cout << endl << "error: cannot encrease level " << scale[scale.size()-1] << " !" << endl;
                getchar();
            }else
            {
                it++;
                value = scale[it];
            }

            return *this;
        };

        level& findIt()
        {
            const unsigned int scaleMaxIt = scale.size() - 1;

            for(unsigned int s=0; s<scale.size(); s++)
            {
                if (scaleMaxIt == 0)
                {
                    it = 0;
                } else if(value >= scale[scaleMaxIt])
                {
                    it = scaleMaxIt;
                } else if(value <= scale[0])
                {
                    it = 0;
                } else if(s > 0 && s < scaleMaxIt && value >= (scale[s] + scale[s-1])/2 && value <= (scale[s] + scale[s+1])/2)
                {
                    it = s;
                    break;
                } else if(s == 0 && s < scaleMaxIt && value <= (scale[0] + scale[1])/2)
                {
                    it = 0;
                } else if(s > 0 && s == scaleMaxIt && value >= (scale[s] + scale[s-1])/2)
                {
                    it = scaleMaxIt;
                }
            }
            return *this;
        };

        level& operator=(double v)
        {
            value = v;
            findIt();
            value = scale[it];
            return *this;
        };

        level& operator=(unsigned int i)
        {
            it = i;
            value = scale[it];
            return *this;
        };

        level& operator=(level v)
        {
            value = v.value;
            findIt();
            value = scale[it];
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
            w.findIt();
            return in;
        };
    };

    struct criteria
    {
        string name;
        string mode;
        double valueA;
        double valueB;
        double valueC;

        friend istream & operator >> (istream &in,  criteria &c)
        {
            in >> c.name;
            in >> c.mode;
            in >> c.valueA;
            in >> c.valueB;
            in >> c.valueC;
            return in;
        };

        friend ostream & operator << (ostream &out, const criteria &c)
        {
            out << c.name << "\t" << c.mode << "\t" << c.valueA << "\t" << c.valueB << "\t" << c.valueC;
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

    struct pairwiseMatrix{ // Saaty(1987)
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
            matrix.resize(s);

            for(unsigned int i=0; i<matrix.size(); i++)
            {
                matrix[i].resize(s);
            }

            return *this;
        }

        friend ostream & operator << (ostream &out, const pairwiseMatrix &m)
        {
            out << "pairwise comparisons matrix: " << endl << endl;

            for(unsigned int i=0; i<m.matrix.size(); i++)
            {
                for(unsigned int j=0; j<m.matrix[i].size(); j++)
                {
                    out << setprecision(2) << fixed << setw(6) << m.matrix[i][j];
                }
                out << endl;
            }

            out << "\npairwise comparison matrix index: " << endl << endl;

            for(unsigned int i=0; i<m.matrix.size(); i++)
            {
                for(unsigned int j=0; j<m.matrix[i].size(); j++)
                {
                    out << setw(6) << m.matrix[i][j].it;
                }
                out << endl;
            }

            out << endl << "main eigenvalue: " << setprecision(3) << fixed  << m.mainEigenvalue << endl;

            out << endl << "main eigenvector: ";
            for(unsigned int s=0; s<m.mainEigenvector.size(); s++)
            {
                out << setprecision(3) << fixed << setw(7) << m.mainEigenvector[s];
            }
            out << endl;

            out << endl << "consistency rate: " << m.CR;

            if(m.CR <= m.tol)
            {
                out << "\n\nCongratulations, your matrix of pairwise comparation is consistent !!! \n";
            }else
            {
                out << "\n\nSorry, your matrix of pairwise comparation is inconsistent !!! \n";
            }

            return out;
        };

        friend istream & operator >> (istream &in,  pairwiseMatrix &m)
        {
            const unsigned int scaleMaxIt = m.matrix[0][0].scale.size() - 1;

            for(unsigned int i=0; i<m.matrix.size(); i++)
            {
                m.matrix[i][i].value = 1;
                m.matrix[i][i].it = floor(scaleMaxIt/2);

                for(unsigned int j=i+1; j<m.matrix[i].size(); j++)
                {
                    in >> m.matrix[i][j];

                    m.matrix[j][i].value = 1/m.matrix[i][j].value;
                    m.matrix[j][i].it = scaleMaxIt - m.matrix[i][j].it;
                }
            }
            return in;
        };

        pairwiseMatrix& eigen()
        {
            vector<double> v;

            v.clear();

            for(unsigned int j=0; j<matrix.size(); j++)
            {
                for(unsigned int i=0; i<matrix[j].size(); i++)
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

        pairwiseMatrix& consistencyRate() // Saaty(1987)
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

            while(matrix[n][g].value*matrix[g][s].value < matrix[n][s].value && matrix[n][g].it != (matrix[n][g].scale.size() - 1))
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
        vector<vector<double>> data; // data for each criterion - vector[_NData, _NCriteria]
        vector<string> code; // product code - vector[_NData]
        unsigned int leadTimeIndex = 0;
        bool leadTimeVar = 0;

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
            code.clear();

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
                in.ignore(std::numeric_limits<std::streamsize>::max(),':');

                in >> p.NCriteria;

                in.ignore(std::numeric_limits<std::streamsize>::max(),':');

                p.weightVector.resize(p.NCriteria);

                for(unsigned int s=0; s<p.weightVector.size(); s++)
                {
                    in >> p.weightVector[s];
                }

                in.ignore(std::numeric_limits<std::streamsize>::max(),':');

                in >> p.leadTimeIndex;

                in.ignore(std::numeric_limits<std::streamsize>::max(),':');

                in >> p.leadTimeVar;

                in.ignore(std::numeric_limits<std::streamsize>::max(),':');

                p.pairwiseWeight.resize(p.NCriteria);

                in >> p.pairwiseWeight;

                in.ignore(std::numeric_limits<std::streamsize>::max(),':');

                in >> p.NData;

                in.ignore(std::numeric_limits<std::streamsize>::max(),':');

                p.data.resize(p.NData);
                p.code.resize(p.NData,"0");

                for(unsigned int i=0; i<p.data.size(); i++)
                {
                    p.data[i].resize(p.NCriteria);

                    in >> p.code[i];

                    for(unsigned int j=0; j<p.data[i].size(); j++)
                    {
                        in >> p.data[i][j];
                    }
                }
            }

            return in;
        };

        friend ostream & operator << (ostream &out, const problem &p)
        {
            out << "number of criteria: " << p.NCriteria << endl << endl;

            out << p.pairwiseWeight << endl;

            out << "weight: " << endl << endl;

            for(unsigned int s=0; s<p.weightVector.size(); s++)
            {
                out << p.weightVector[s] << endl;
            }

            out << endl;

            out << "number of data per criterion: " << p.NData << endl << endl;

            out << "data: " << endl << endl;

            for(unsigned int i=0; i<p.data.size(); i++)
            {
                out << p.code[i] << "\t";

                for(unsigned int j=0; j<p.data[i].size(); j++)
                {
                    out << setprecision(2) << fixed << setw(10) << p.data[i][j];
                }

                out << endl;
            }

            return out;
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

        // ABC
        vector<vector<double>> perMatrix;
        vector<vector<unsigned int>> orderedMatrix;
        vector<vector<char>> ABCMatrix;

        // multicriteria
        vector<double> weight;
        vector<unsigned int> classf;
        vector<char> ABCClassf;
        vector<string> code; // product code (ordered) - vector[_NData]
        vector<vector<double>> data; // data for each criterion (ordered) - matrix[_NData, _NCriteria]

        problem prob;

        solution& clear()
        {
            for(unsigned int s=0; s<perMatrix.size(); s++)
            {
                perMatrix[s].clear();
            }

            perMatrix.clear();

            for(unsigned int s=0; s<orderedMatrix.size(); s++)
            {
               orderedMatrix[s].clear();
            }

            orderedMatrix.clear();

            for(unsigned int s=0; s<ABCMatrix.size(); s++)
            {
                ABCMatrix[s].clear();
            }

            ABCMatrix.clear();

            weight.clear();
            classf.clear();
            ABCClassf.clear();

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
            prob = p;
            perMatrix.resize(prob.NData);

            for(unsigned int i=0; i<perMatrix.size(); i++)
            {
                perMatrix[i].resize(prob.NCriteria,0.0);
            }

            orderedMatrix.resize(prob.NData);

            for(unsigned int i=0; i<orderedMatrix.size(); i++)
            {
                orderedMatrix[i].resize(prob.NCriteria,0);
            }

            ABCMatrix.resize(prob.NData);

            for(unsigned int i=0; i<ABCMatrix.size(); i++)
            {
                ABCMatrix[i].resize(prob.NCriteria,'C');
            }

            weight.resize(prob.NData,0.0);
            classf.resize(prob.NData,0);
            ABCClassf.resize(prob.NData,'C');

            return *this;
        };

        friend ostream & operator << (ostream &out, const solution &s)
        {
            double sum = 0;

            out << "Number of data :" << endl << endl;

            out << s.prob.NData << endl << endl;

            out << "--> ABC multi-criteria classification (with Saat's Analytic Hierarchy Process)" << endl << endl;

            out << setw(4) << "code" << setw(11) << "lead time" << setw(4) << "ABC" << setw(8) << "weight" << setw(10) << "sum" << setw(8) << "order :" << endl << endl;

            for(unsigned int i=0; i<s.prob.code.size(); i++)
            {
                sum += s.weight[i];
                out << s.code[i];
                out << setprecision(2) << fixed << setw(11) << s.data[i][s.prob.leadTimeIndex];
                out << setw(4) << s.ABCClassf[i];
                out << setprecision(2) << fixed << setw(6) << s.weight[i]*100 << " %";
                out << setprecision(2) << fixed << setw(8) << sum*100 << " %";
                out << setw(6) << s.classf[i];
                out << endl;

            }

            out << endl << "--> ABC matrix (by criterion) " << endl << endl;

            out << setw(4) << "code";

            for(unsigned int i=0; i<s.prob.weightVector.size(); i++)
            {
                out << setw(18) << s.prob.weightVector[i].criterion.name << ", " << setprecision(2) << fixed << setw(4) << s.prob.weightVector[i].value;
            }

            out << " :" << endl << endl;

            for(unsigned int i=0; i<s.ABCMatrix.size(); i++)
            {
                out << s.prob.code[i];

                for(unsigned int j=0; j<s.ABCMatrix[i].size(); j++)
                {
                    out << setw(10) << s.ABCMatrix[i][j] << setprecision(2) << fixed << setw(12) << s.perMatrix[i][j] * 100 << " %";
                }
                out << endl;
            }

            return out;
        };

        solution& percentilMatrix()
        {
            double sum;

            for(unsigned int c=0; c<perMatrix[0].size(); c++)
            {
                sum = 0;

                for(unsigned int d=0; d<perMatrix.size(); d++)
                {
                    sum += prob.data[d][c];
                }

                for(unsigned int d=0; d<perMatrix.size(); d++)
                {
                    if(sum == 0)
                    {
                        perMatrix[d][c] = 0;
                    }else
                    {
                        perMatrix[d][c] = prob.data[d][c]/sum;
                    }
                }
            }

            return *this;
        };

        solution& ABC(problem p)
        {
            unsigned int it, product;
            double sum;

            resize(p);
            percentilMatrix();

            // ordering

            for(unsigned int c=0; c<orderedMatrix[0].size(); c++) // criterion
            {
                for(unsigned int d=0; d<orderedMatrix.size(); d++) // data
                {
                    it = d;

                    for(unsigned int l=0; l<d; l++) // finding position
                    {
                        product = orderedMatrix[l][c];

                        if(perMatrix[d][c] > perMatrix[product][c])
                        {
                            it = l;

                            for(unsigned int i=d-1; i>l; i--) // relocation
                            {
                                orderedMatrix[i+1][c] = orderedMatrix[i][c];
                            }

                            orderedMatrix[l+1][c] = orderedMatrix[l][c];

                            break;
                        }
                    }

                    orderedMatrix[it][c] = d;
                }
            }

            // ABC classification

            for(unsigned int c=0; c<orderedMatrix[0].size(); c++) // criterion
            {
                sum = 0;

                for(unsigned int d=0; d<orderedMatrix.size(); d++) // data
                {
                    product = orderedMatrix[d][c];

                    if(prob.weightVector[c].criterion.mode == "value")
                    {
                        if(prob.data[product][c] == prob.weightVector[c].criterion.valueA)
                        {
                            ABCMatrix[product][c] = 'A';
                        } else if(prob.data[product][c] == prob.weightVector[c].criterion.valueB)
                        {
                            ABCMatrix[product][c] = 'B';
                        } else if(prob.data[product][c] == prob.weightVector[c].criterion.valueC)
                        {
                            ABCMatrix[product][c] = 'C';
                        }
                    } else if(prob.weightVector[c].criterion.mode == "acmSum")
                    {
                        sum += perMatrix[product][c];

                        if(d == 0 && sum >= prob.weightVector[c].criterion.valueA)
                        {
                            ABCMatrix[product][c] = 'A';
                        } else if(d == 1 && sum >= prob.weightVector[c].criterion.valueB)
                        {
                            ABCMatrix[product][c] = 'B';
                        } else if(sum <= prob.weightVector[c].criterion.valueA)
                        {
                            ABCMatrix[product][c] = 'A';
                        } else if(sum <= prob.weightVector[c].criterion.valueB)
                        {
                            ABCMatrix[product][c] = 'B';
                        } else
                        {
                            ABCMatrix[product][c] = 'C';
                        }
                    }
                }
            }

            return *this;
        };

        solution& classification()
        {
            vector<unsigned int>::iterator it;
            double sum;

            double ALim = 0.15,
                   BLim = 0.25;

            classf.clear();
            classf.push_back(0);

            bool aux = 0;

            for(unsigned int s=1; s<weight.size(); s++) // data
            {
                aux = 0;

                for(unsigned int l=0; l<s; l++) // finding position
                {
                    if(weight[classf[l]] < weight[s])
                    {
                        it = classf.begin() + l;
                        classf.insert(it, s);
                        aux = 1;
                        break;
                    }
                }

                if(aux == 0)
                {
                    classf.push_back(s);
                }
            }

            sum = 0;
            for(unsigned int s=0; s<classf.size(); s++)
            {
                ABCClassf[classf[s]] = 'D';

                sum += weight[classf[s]];
                if(s==0 && sum > ALim)
                {
                    ABCClassf[classf[s]] = 'A';
                } else if(s==1 && sum > BLim)
                {
                    ABCClassf[classf[s]] = 'B';
                } if(sum <= ALim)
                {
                    ABCClassf[classf[s]] = 'A';
                } else if(sum <= BLim)
                {
                    ABCClassf[classf[s]] = 'B';
                } else
                {
                    ABCClassf[classf[s]] = 'C';
                }
            }

            return *this;
        };


        solution& order()
        {
            vector<char> aux_ABC;
            vector<double> aux_weight;

            aux_ABC.clear();
            aux_weight.clear();

            code.clear();
            for(unsigned int s=0; s<data.size(); s++)
            {
                data[s].clear();
            }
            data.clear();

            ABCClassf.clear();
            weight.clear();

            for(unsigned int s=0; s<classf.size(); s++)
            {
                code.push_back(prob.code[classf[s]]);
                data.push_back(prob.data[classf[s]]);
                aux_ABC.push_back(ABCClassf[classf[s]]);
                aux_weight.push_back(weight[classf[s]]);

                classf[s] = s;
            }

            ABCClassf = aux_ABC;
            weight = aux_weight;

            aux_ABC.clear();
            aux_weight.clear();

            return *this;
        }

        solution& analyticHierarchyProcess(problem p)
        {
            ABC(p);

            for(unsigned int i=0; i<perMatrix.size(); i++)
            {
                weight[i] = 0;
                for(unsigned int j=0; j<perMatrix[i].size(); j++)
                {
                    weight[i] += perMatrix[i][j]*prob.weightVector[j].value;
                }
            }

            classification();

            order();

            return *this;
        };

        friend ostream& createList(ostream &out, const solution &s)
        {
            out << "Number of data :" << endl << endl;

            out << s.prob.NData << endl << endl;

            out << "// list for demand patter clss (code | lead time | ABC clssf | ABC ord | weigh):" << endl << endl;

            for(unsigned int i=0; i<s.prob.code.size(); i++)
            {
                out << s.code[i];
                out << setprecision(2) << fixed << setw(11) << s.data[i][s.prob.leadTimeIndex];
                out << setw(4) << s.ABCClassf[i];
                 out << setw(6) << s.classf[i];
                out << setprecision(4) << fixed << setw(8) << s.weight[i];
                out << endl;
            }

            return out;
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

        bool ABC();
        bool analyticHierarchyProcess();

        bool format_classification_data();
    };

}

#endif // CLASSIFICATION_PROBLEM_H_INCLUDED
