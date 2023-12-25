/*********************************************************************** LICENSE ********************************************************************************************
Important: Copies and distributions of this file must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.

******************************************************************************************************************************************************************************/

// COPSolver (Combinatorial Optimization Problems Solver)
// module: COPSolver: library for reading and writing formatted files
// version: vffr_ffr.0-1
// developed by Tatiana Balbi Fraga
// start date: 2023/11/10
// last modification: 2023/12/25

#ifndef FORMATTED-FILES-READING_H_INCLUDED
#define FORMATTED-FILES-READING_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <vector>
using namespace std;

namespace ffr
{
    struct sale
    {
        string code;
        double quantity;
        double price;
        struct tm date;

        friend ostream & operator << (ostream &out, const sale &s)
        {
            out << s.code << "\t";
            out << setw(8) << setprecision(2) << fixed << s.quantity;
            out << setw(14) << setprecision(2) << fixed << s.price;
            out << setw(6) << s.date.tm_year;
            out << setw(4) << s.date.tm_mon;
            out << setw(4) << s.date.tm_mday;

            return out;
        };
    };

    struct input
    {
        string file_address;
        vector<string> code;
        vector<unsigned int> lead_time;
        vector<char> ABC_class;
        vector<double> ABC_weight;

        input& clear()
        {
            file_address = "none";
            code.clear();
            lead_time.clear();
            ABC_class.clear();
            ABC_weight.clear();

            return *this;
        };

        input& alexia_config()
        {
            string s;
            double u;
            char c;
            double w;

            file_address = getenv("HOME");
            file_address += "/COPSolver/data/alexia/p_list.txt";

            fstream file;
            file.open(file_address);

            file.ignore(std::numeric_limits<std::streamsize>::max(),':');
            file.ignore(std::numeric_limits<std::streamsize>::max(),':');

            char nu[1];
            file.getline(nu, 1);

            code.clear();

            while(!file.eof())
            {
                file >> s;
                code.push_back(s);

                file >> u;
                lead_time.push_back(u);

                file >> c;
                ABC_class.push_back(c);

                file >> w;
                ABC_weight.push_back(w);
            }

            //code.erase(code.end());

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

            output_file.open(file_address + "/COPSolver/results/sales_data.txt.alexia", ios::out);

            _input.alexia_config();

            alexia_data_address();

            if (!output_file)
            {
                cerr << "File " << file_address + "/COPSolver/results/sales_data.txt.alexia" << " not created !" << endl;
                getchar();
            } else
            {
                _input.alexia_data_address();

                output_file << "code STRING, quantity DOUBLE, value DOUBLE, year UNISGNED INT, month UNISIGNED INT, day UNSIGNED INT:" << endl << endl;

                for(unsigned int s=0; s<_input.code.size(); s++)
                {
                    input_file.open(_input.file_address + _input.code[s] + ".txt");

                    if (!input_file)
                    {
                        cerr << "File " << _input.file_address + _input.code[s] + ".txt" << " do not exist !" << endl;
                        //getchar();
                        _input.code.erase(_input.code.begin() + s);
                        _input.lead_time.erase(_input.lead_time.begin() + s);
                        _input.ABC_class.erase(_input.ABC_class.begin() + s);
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
                                //cerr << endl << "!! Parsing failed in " << _input.code[s] << " ! " << dateStr << endl;
                                //it will fail after reading last sale register of each input file
                            } else
                            {
                                reg.date.tm_year += 1900;
                                reg.date.tm_mon += 1;
                                aux = 0;


                                input_file >> reg.code;

                                aux = 1;

                                unsigned int index=0;
                                do
                                {
                                    input_file.ignore(numeric_limits<std::streamsize>::max(),'U');
                                    input_file.ignore(numeric_limits<std::streamsize>::max(),'N');

                                    input_file >> dateStr;

                                    index=0;
                                    for( char c : dateStr )
                                    {
                                        if(c=='.' && index < dateStr.size()-4)
                                        {
                                            dateStr.erase(dateStr.begin() + index);
                                        } else if(c==',' && index >= dateStr.size()-4)
                                        {
                                            dateStr[index] = '.';
                                        }

                                        index++;
                                    }

                                    stringstream stream(dateStr);
                                    stream >> reg.quantity;

                                    if (stream.fail())
                                    {
                                        //cerr << dateStr << " quantity format do not match" << endl;
                                        //sometimes it will fail
                                        /*if (_input.code[s] != "2091" && _input.code[s] != "2092" && _input.code[s] != "1823" && _input.code[s] != "2350"
                                        && _input.code[s] != "2031" && _input.code[s] != "2032" && _input.code[s] != "2095"
                                        && _input.code[s] != "2096" && _input.code[s] != "1873" && _input.code[s] != "2392"
                                        && _input.code[s] != "1292" && _input.code[s] != "1701" && _input.code[s] != "2164"
                                        && _input.code[s] != "1893" && _input.code[s] != "1767" && _input.code[s] != "2156"
                                        && _input.code[s] != "1291" && _input.code[s] != "2145" && _input.code[s] != "1859"
                                        && _input.code[s] != "2163" && _input.code[s] != "2165" && _input.code[s] != "1518") getchar();*/
                                    } else
                                    {
                                        aux = 0;
                                        break;
                                    }

                                } while (aux);

                                input_file.ignore(numeric_limits<std::streamsize>::max(),' ');

                                input_file >> dateStr;

                                index=0;
                                for( char c : dateStr )
                                {
                                    if(c=='.' && index < dateStr.size()-4)
                                    {
                                        dateStr.erase(dateStr.begin() + index);
                                    } else if(c==',' && index >= dateStr.size()-4)
                                    {
                                        dateStr[index] = '.';
                                    }

                                    index++;
                                }

                                stringstream stream(dateStr);
                                stream >> reg.price;

                                input_file >> dateStr;
                                input_file >> dateStr;
                                output_file << reg << endl;
                            }
                        }
                    }

                    input_file.close();
                }
            }

            output_file.close();

            return *this;

        };
    };

    class ffrc
    {
        private:

        output out;

        public:

        bool alexia();
    };
}

#endif // FORMATTED-FILES-READING_H_INCLUDED
