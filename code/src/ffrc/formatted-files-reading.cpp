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
// start date: 2023/10/18
// last modification: 2023/02/28

#include "../../lib/ffrc/formatted-files-reading.h"

namespace ffr
{
    bool ffrc::alexia()
    {
        cout << endl << "creating alexia sales data file ... " << endl << endl;
        out.alexia_data();

        return 0;
    };

    bool ffrc::alexia_rewrite()
    {
        cout << endl << "rewriting alexia data ... " << endl << endl;
        out.alexia_rewrite();

        return 0;
    };
}
