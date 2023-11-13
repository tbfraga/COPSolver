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
// version: v3.0-1
// developed by Tatiana Balbi Fraga
// start date: 2023/11/10
// last modification: 2023/11/10

#ifndef FORMATTED-FILES-READING_H_INCLUDED
#define FORMATTED-FILES-READING_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <chrono>
using namespace std;

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
        vector<string> file_list;
        vector<unsigned int> lead_time;

        input& clear()
        {
            file_address = "none";
            file_list.clear();
            return *this;
        };

        friend istream & operator >> (istream &in,  input &i)
        {
            string s;

            in.ignore(std::numeric_limits<std::streamsize>::max(),':');

            i.file_list.clear();
            while(!in.eof())
            {
                in >> s;
                i.file_list.push_back(s);
            }

            return in;
        };

        input& alexia_config()
        {
            string s;
            unsigned int u;

            file_address = getenv("HOME");
            file_address += "/COPSolver/data/alexia/config.txt";

            fstream file;
            file.open(file_address);

            file.ignore(std::numeric_limits<std::streamsize>::max(),':');

            file_list.clear();
            while(!file.eof())
            {
                file >> s;
                file_list.push_back(s);

                file >> u;
                lead_time.push_back(u);
            }

            file_list.erase(file_list.end());

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
            fstream output_file;

            sale reg;

            _input.alexia_config();

            alexia_data_address();
            cout << endl << file_address << endl;

            if (!output_file)
            {
                cerr << "File not created!";
            } else
            {
                _input.alexia_data_address();

                for(unsigned int s=0; s<_input.file_list.size(); s++)
                {
                    output_file.open(file_address + "data_" + _input.file_list[s], ios::out);
                    cout << endl << _input.file_list[s] << endl;

                    input_file.open(_input.file_address + _input.file_list[s]);

                    if (!input_file)
                    {
                        cerr << "File do not exist!";
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
                                cerr << "Parsing failed!" << endl;
                                //getchar();
                            } else
                            {
                                reg.date.tm_year += 1900;
                                reg.date.tm_mon += 1;

                                input_file >> reg.code;

                                input_file.ignore(60,'U');
                                input_file.ignore(60,'N');

                                input_file >> reg.quantity;

                                input_file.ignore(60,' ');

                                input_file >> reg.price;

                                input_file >> dateStr;
                                input_file >> dateStr;
                                input_file >> dateStr;

                                output_file << reg << endl;
                            }
                        }

                        output_file.close();

                        input_file.close();
                    }
                }
            }

            return *this;
        };
    };
}

#endif // FORMATTED-FILES-READING_H_INCLUDED
