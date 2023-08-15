/*********************************************************************** LICENSE **********************************************************************************************
Important: Copies and distributions of this solver must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.
******************************************************************************************************************************************************************************/

// COPSolver installer
// version: V01_20230814
// developed by Tatiana Balbi Fraga
// start date: 2023/08/15
// last modification: 2023/08/15

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

int main()
{
    // https://en.cppreference.com/w/cpp/filesystem/copy
    // https://en.cppreference.com/w/cpp/filesystem/copy_options

    fs::create_directories("/opt/COPSolver");
    fs::copy("COPSolver", "/opt/COPSolver/COPSolver"); // copy file

    const auto copyOptions = fs::copy_options::overwrite_existing
                           | fs::copy_options::create_symlinks
                           ;

    fs::copy("/opt/COPSolver/COPSolver", "/bin/COPSolver", copyOptions);
    fs::copy("/opt/COPSolver/COPSolver", "/usr/bin/COPSolver", copyOptions);
    fs::copy("COPSolver.desktop", "/usr/share/applications/COPSolver.desktop"); // copy file

    cout << endl << "Thanks for installing COPSolver !!!";
    cout << endl << "See you..." << endl;

    cout << endl << "Press enter for closing this window." << endl << endl;

    return 0;
}
