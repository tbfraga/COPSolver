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
Common questions about the MPL2 are answered in the official MPL2 FAQ.
For more details see https://eigen.tuxfamily.org/

******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// module: COPSolver: library for reading formatted files
// version: v2.0-1
// developed by Tatiana Balbi Fraga
// start date: 2023/11/10
// last modification: 2023/11/17

#ifndef FORMATTED-FILES-READING_H_INCLUDED
#define FORMATTED-FILES-READING_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <chrono>
#include <cstdlib>
using namespace std;

template<typename T>
bool isValid(string num)
{
    T  value;
    stringstream stream(num);
    stream >> value;

    // If the stream is already in the error state peak will not change it.
    // Otherwise stream should be good and there should be no more data
    // thus resulting in a peek returning an EOF
    return (stream) &&
           stream.peek() == char_traits<typename stringstream::char_type>::eof();
}

/*int main()
{
    isValid<double>("55");
}*/

namespace ffr
{
    struct sale
    {
        string code;
        unsigned int quantity;
        double price;
        struct tm date;

        friend ostream & operator << (ostream &out, const sale &s)
        {
            out << s.code << "\t";
            out << setw(3) << s.quantity << "\t";
            out << setw(6) << s.price << "\t";
            out << setw(4) << s.date.tm_year << "\t";
            out << setw(2) << s.date.tm_mon << "\t";
            out << setw(2) << s.date.tm_mday << "\t";

            return out;
        };
    };

    struct input
    {
        string file_address;
        vector<string> code;
        vector<unsigned int> lead_time;
        vector<char> ABC_class;
        vector<unsigned int> ABC_ord;
        vector<double> ABC_weight;

        input& clear()
        {
            file_address = "none";
            code.clear();
            lead_time.clear();
            ABC_class.clear();
            ABC_ord.clear();

            return *this;
        }; //

        friend istream & operator >> (istream &in,  input &i)
        {
            string s;

            in.ignore(std::numeric_limits<std::streamsize>::max(),':');

            i.code.clear();
            while(!in.eof())
            {
                in >> s;
                i.code.push_back(s);
            }

            return in;
        };

        input& alexia_config()
        {
            cout << endl << "reading alexia config data, please wait..." << endl;
            string s;
            double u;
            char c;
            double w;

            file_address = getenv("HOME");
            file_address += "/COPSolver/data/alexia/config.txt";

            fstream file;
            file.open(file_address);

            file.ignore(std::numeric_limits<std::streamsize>::max(),':');

            code.clear();

            while(!file.eof())
            {
                file >> s;
                code.push_back(s);

                file >> u;
                lead_time.push_back(u);

                file >> c;
                ABC_class.push_back(c);

                file >> u;
                ABC_ord.push_back(u);

                file >> w;
                ABC_weight.push_back(w);
            }

            code.erase(code.end());

            file.close();

            return *this;
        };

        input& alexia_data_address()
        {
            file_address = getenv("HOME");
            file_address += "/COPSolver/data/alexia/";
            return *this;
        };
    };

    struct output
    {
        input _input;
        string file_address;

        output& alexia_data_address()
        {
            file_address = getenv("HOME");
            file_address += "/COPSolver/data/alexia/";
            return *this;
        };

        output& alexia_data()
        {
            string dateStr;
            fstream input_file;
            fstream data_file;

            fstream output_file;

            bool aux;

            sale reg;

            file_address = getenv("HOME");

            output_file.open(file_address + "/COPSolver/results/dp_clssf_problem.txt", ios::out);

            _input.alexia_config();

            alexia_data_address();
            cout << endl << file_address << endl;

            if (!output_file)
            {
                cerr << "File not created!";
            } else
            {
                _input.alexia_data_address();

                for(unsigned int s=0; s<_input.code.size(); s++)
                {
                    cout << endl << _input.code[s] << endl;

                    input_file.open(_input.file_address + _input.code[s] + ".txt");
                    data_file.open(_input.file_address + "/data_" + _input.code[s] + ".txt", ios::out);

                    if (!input_file)
                    {
                        cerr << "File do not exist!";
                        _input.code.erase(_input.code.begin() + s);
                        _input.lead_time.erase(_input.lead_time.begin() + s);
                        _input.ABC_class.erase(_input.ABC_class.begin() + s);
                        _input.ABC_ord.erase(_input.ABC_ord.begin() + s);
                        _input.ABC_weight.erase(_input.ABC_weight.begin() + s);
                        s--;
                    } else
                    {
                        while(!input_file.eof())
                        {
                            input_file >> dateStr;
                            input_file >> dateStr;

                            istringstream ss(dateStr);

                            ss >> get_time(&reg.date, "%d/%m/%Y");

                            if (ss.fail())
                            {
                                cerr << endl << "Parsing failed in " << _input.code[s] << " !" << endl;
                            } else
                            {
                                cout << endl << reg.date.tm_year << "\t" << _input.code[s];

                                reg.date.tm_year += 1900;
                                reg.date.tm_mon += 1;

                                input_file >> reg.code;

                                aux = 1;

                                do
                                {
                                    input_file.ignore(60,'U');
                                    input_file.ignore(60,'N');

                                    input_file >> dateStr;

                                    stringstream stream(dateStr);
                                    stream >> reg.quantity;

                                    if (stream.fail())
                                    {
                                        cout << endl << "fail" << endl;
                                    } else
                                    {
                                        aux = 0;
                                        break;
                                    }

                                    cout << endl << dateStr << "\t" << reg.quantity << endl;

                                } while (aux);

                                //reg.quantity = strtoul(dateStr.c_str(), NULL, 0);

                                input_file.ignore(60,' ');

                                input_file >> reg.price;

                                input_file >> dateStr;
                                input_file >> dateStr;
                                input_file >> dateStr;

                                data_file << reg << endl;
                                output_file << reg << endl;
                            }
                        }
                    }

                    data_file.close();
                    input_file.close();
                }
            }

            output_file.close();

            return *this;
        };
    };
}

#endif // FORMATTED-FILES-READING_H_INCLUDED
