#include "Scdl_Structure.h"

// *****************************************************************************
// Generate a list with the critical path operators
// *****************************************************************************

VecLPSTR CP_OperatorList ()
{
    LPSTR CP_Operator;
    VecLPSTR CP_OperatorList;

    CP_Operator = "N5";
    CP_OperatorList.push_back (CP_Operator);

    return CP_OperatorList;
}

// *****************************************************************************
// Functions to set the value of the private variables
// *****************************************************************************

void ScdlProblem :: CriticalPathIndex (const int &CriticalPathIndex)
{
    SP_CriticalPathIndex = CriticalPathIndex;
}

// *****************************************************************************
// Functions to return the value of the private variables
// *****************************************************************************

MatInt ScdlProblem :: CriticalPath ()
{
    return SP_CriticalPath;
}

// ***** Class JS_ScdlProblem

// *****************************************************************************
// Functions to return the value of the private variables
// *****************************************************************************

TriInt JS_ScdlProblem :: Neighborhood ()
{
    return SP_Neighborhood;
}

// *****************************************************************************
// The following function generates a vector of all critical paths of the
// current scheduling (solution).
// *****************************************************************************

bool JS_ScdlProblem :: FindCriticalPath ()
{
    bool aux = false;

    float TimeOfJob,
          TimeOfMcn;

    VecInt CP;

    SP_CriticalPath.clear ();
    SP_CriticalPath.reserve (SP_NTTask);

    for (UINT i=0; i<SP_LastTaskOfScdl.size(); i++)
    {
        CP.clear ();
        CP.push_back(SP_LastTaskOfScdl[i]);
        SP_CriticalPath.push_back (CP);
    }

    CP.clear();

    aux = false;

    for (UINT i=0; i<SP_CriticalPath.size(); i++)
    {
        aux = false;
        while (aux == false)
        {
            if (SP_PrevTaskOnMcn[SP_CriticalPath[i].back()] == -1 && SP_PrevTaskOnJob[SP_CriticalPath[i].back()] == -1)
            {
                aux = true;
            }
            else
            {
                if (SP_PrevTaskOnMcn[SP_CriticalPath[i].back()] == -1)
                {
                    SP_CriticalPath[i].push_back(SP_PrevTaskOnJob[SP_CriticalPath[i].back()]);
                }
                else if (SP_PrevTaskOnJob[SP_CriticalPath[i].back()] == -1)
                {
                    SP_CriticalPath[i].push_back(SP_PrevTaskOnMcn[SP_CriticalPath[i].back()]);
                }
                else
                {
                    TimeOfJob = SP_FinalTimeOfTask[SP_PrevTaskOnJob[SP_CriticalPath[i].back()]];

                    TimeOfMcn = SP_FinalTimeOfTask[SP_PrevTaskOnMcn[SP_CriticalPath[i].back()]];

                    if (TimeOfJob > (TimeOfMcn + 0.005))
                    {
                        SP_CriticalPath[i].push_back(SP_PrevTaskOnJob[SP_CriticalPath[i].back()]);
                    }else if (TimeOfJob < (TimeOfMcn - 0.005))
                    {
                        SP_CriticalPath[i].push_back(SP_PrevTaskOnMcn[SP_CriticalPath[i].back()]);
                    }else
                    {
                        CP = SP_CriticalPath[i];
                        CP.push_back(SP_PrevTaskOnMcn[SP_CriticalPath[i].back()]);
                        SP_CriticalPath.push_back(CP);

                        SP_CriticalPath[i].push_back(SP_PrevTaskOnJob[SP_CriticalPath[i].back()]);
                    }
                }
            }
        }
    }

    CP.clear();

    return TRUE;
}

// *****************************************************************************
// The following function generates a vector with the block of tasks in a
// defined critical path of the current scheduling.
// *****************************************************************************

bool JS_ScdlProblem :: BlocksOnCriticalPath ()
{
    if (SP_CriticalPathIndex >= 0 && (UINT)SP_CriticalPathIndex >= SP_CriticalPath.size())
    {
        printf ("\n\n Warning: Error in BlockOnCriticalPath function !!!");
        return FALSE;
    }

    VecInt CP = SP_CriticalPath[0];

    VecInt Bk;
    Bk.clear();
    Bk.reserve (SP_NTTask);

    SP_BlocksOnCriticalPath.clear();

    Bk.push_back(CP[0]);

    for (UINT i=1; i<CP.size(); i++)
    {
        if (SP_McnOfTask[CP[i-1]] == SP_McnOfTask[CP[i]])
        {
            Bk.push_back(CP[i]);
        }else
        {
            SP_BlocksOnCriticalPath.push_back(Bk);
            Bk.clear();
            Bk.push_back(CP[i]);
        }
    }

    SP_BlocksOnCriticalPath.push_back(Bk);

    CP.clear();
    Bk.clear();

    return TRUE;
}

// *****************************************************************************
// The following function generates a vector with the tasks witch wold to be
// changed to generate the N5 neighborhood.
// *****************************************************************************

bool JS_ScdlProblem :: N5_TaskList (VecInt &A, VecInt &B)
{
    A.clear();
    B.clear();

    for (UINT i=0; i<SP_BlocksOnCriticalPath.size(); i++)
    {
        if (i == 0)
        {
            if (SP_BlocksOnCriticalPath[0].size() >= 2)
            {
                A.push_back(SP_BlocksOnCriticalPath[0][SP_BlocksOnCriticalPath[0].size()-1]);
                B.push_back(SP_BlocksOnCriticalPath[0][SP_BlocksOnCriticalPath[0].size()-2]);
            }
            else continue;
        }
        else if(i == SP_BlocksOnCriticalPath.size()-1)
        {
            if (SP_BlocksOnCriticalPath[i].size() >= 2)
            {
                A.push_back(SP_BlocksOnCriticalPath[i][1]);
                B.push_back(SP_BlocksOnCriticalPath[i][0]);
            }
            else continue;
        }
        else
        {
            if (SP_BlocksOnCriticalPath[i].size() == 2)
            {
                A.push_back(SP_BlocksOnCriticalPath[i][1]);
                B.push_back(SP_BlocksOnCriticalPath[i][0]);
            }
            else if(SP_BlocksOnCriticalPath[i].size() > 2)
            {
                A.push_back(SP_BlocksOnCriticalPath[i][1]);
                B.push_back(SP_BlocksOnCriticalPath[i][0]);
                A.push_back(SP_BlocksOnCriticalPath[i][SP_BlocksOnCriticalPath[i].size()-1]);
                B.push_back(SP_BlocksOnCriticalPath[i][SP_BlocksOnCriticalPath[i].size()-2]);
            }
            else continue;
        }
    }

    return TRUE;
}

// *****************************************************************************
// The following function generates the N5 neighborhood for a defined critical
// path of the current scheduling.
// *****************************************************************************

bool JS_ScdlProblem :: N5_Ngh (VecInt &A, VecInt &B)
{
    MatInt Scdl = SP_SRScdl;

    N5_TaskList(A, B);

    if (A.size() == 0)
    {
        printf ("\n\n Solucao otima encontrada !!!");

        Scdl.clear();
        return FALSE;
    }

    SP_Neighborhood.clear();
    SP_Neighborhood.reserve (A.size());

    for (UINT i=0; i<A.size(); i++)
    {
        SP_SRScdl = Scdl;

        Swap(A[i], B[i]);

        SP_Neighborhood.push_back(SP_SRScdl);
    }

    SP_SRScdl = Scdl;
    TimingScdlSR(SP_SRTSC);

    Scdl.clear();
    return TRUE;
}

// *****************************************************************************
// The following function swaps the position of two defined tasks.
// *****************************************************************************

bool JS_ScdlProblem :: Swap (const int &a, const int &b)
{
    int aux,
        mcn,
        pos_a,
        pos_b;

    mcn = SP_McnOfTask[a];

    for (UINT i=0; i<SP_SRScdl[mcn].size(); i++)
    {
        if (SP_SRScdl[mcn][i] == b)
        {
            pos_b = i;
        }

        if (SP_SRScdl[mcn][i] == a)
        {
            pos_a = i;
        }
    }

    aux = SP_SRScdl[mcn][pos_a];
    SP_SRScdl[mcn][pos_a] = SP_SRScdl[mcn][pos_b];
    SP_SRScdl[mcn][pos_b] = aux;

    return TRUE;
}

