/*********************************************************************** LICENSE **********************************************************************************************
Important: Copies and distributions of this solver must comply with the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0).

Under this license, it is allowed to download and share the code as long as they give credit to the original authors, and without being able to alter them in any way or use
them for commercial purposes.

Obs: You can alter this file only for personal purpose. You cannot distribute altered version.

The full license can be found in the LICENSE.md document available in this directory, or through the website: https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode.

This project with its files can be consulted at https://github.com/tbfraga/COPSolver.
******************************************************************************************************************************************************************************/

// COPSolver config file (Combinatorial Optimization Problems Solver)
// version: V01_20230823
// developed by Tatiana Balbi Fraga
// start date: 2023/08/23
// last modification: 2023/08/23

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

    string home_dir = getenv("HOME");
    home_dir += "/COPSolver";

    fs::create_directories(home_dir);

    string local_dir = fs::current_path();

    const auto copyOptions = fs::copy_options::overwrite_existing
                            | fs::copy_options::recursive;

    string source_dir = local_dir + "/LINGOSolver";
    string send_dir = home_dir + "/LINGOSolver";

    fs::copy(source_dir, send_dir, copyOptions);

    source_dir = local_dir + "/data.txt";
    send_dir = home_dir + "/data.txt";

    fs::copy(source_dir, send_dir, copyOptions);

    source_dir = local_dir + "/README";
    send_dir = home_dir + "/README";

    fs::copy(source_dir, send_dir, copyOptions);

    source_dir = local_dir + "/docs";
    send_dir = home_dir + "/docs";

    fs::copy(source_dir, send_dir, copyOptions);

    return 0;
}
