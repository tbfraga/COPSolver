#include "Scdl_Structure.h"
#include <Float.h>

// ***** Class ScdlProblem

// *****************************************************************************
// Functions to set the value of the protected variables
// *****************************************************************************

void ScdlProblem :: Tenure (const UINT &Tenure)
{
    SP_Tenure = Tenure;
}

void ScdlProblem :: TSNMaxIte (const UINT &NMaxIte)
{
    SP_TSNMaxIte = NMaxIte;
}

void ScdlProblem :: FtTenure (const UINT &Tenure)
{
    SP_FtTenure = Tenure;
}

void ScdlProblem :: FtTSNMaxIte (const UINT &NMaxIte)
{
    SP_FtTSNMaxIte = NMaxIte;
}

void ScdlProblem :: ScTenure (const UINT &Tenure)
{
    SP_ScTenure = Tenure;
}

void ScdlProblem :: ScTSNMaxIte (const UINT &NMaxIte)
{
    SP_ScTSNMaxIte = NMaxIte;
}

void ScdlProblem :: ThTenure (const UINT &Tenure)
{
    SP_ThTenure = Tenure;
}

void ScdlProblem :: ThTSNMaxIte (const UINT &NMaxIte)
{
    SP_ThTSNMaxIte = NMaxIte;
}

// *****************************************************************************
// Functions to return the value of the protected variables
// *****************************************************************************

UINT ScdlProblem :: NghMethod ()
{
    return SP_NghMethod;
}

UINT ScdlProblem :: Tenure ()
{
    return SP_Tenure;
}

UINT ScdlProblem :: TSNMaxIte ()
{
    return SP_TSNMaxIte;
}

UINT ScdlProblem :: FtNghMethod ()
{
    return SP_FtNghMethod;
}

UINT ScdlProblem :: FtTenure ()
{
    return SP_FtTenure;
}

UINT ScdlProblem :: FtTSNMaxIte ()
{
    return SP_FtTSNMaxIte;
}

UINT ScdlProblem :: ScNghMethod ()
{
    return SP_ScNghMethod;
}

UINT ScdlProblem :: ScTenure ()
{
    return SP_ScTenure;
}

UINT ScdlProblem :: ScTSNMaxIte ()
{
    return SP_ScTSNMaxIte;
}

UINT ScdlProblem :: ThNghMethod ()
{
    return SP_ThNghMethod;
}

UINT ScdlProblem :: ThTenure ()
{
    return SP_ThTenure;
}

UINT ScdlProblem :: ThTSNMaxIte ()
{
    return SP_ThTSNMaxIte;
}

// ***** Class JS_ScdlProblem

// *****************************************************************************
// The following function apply the Taboo Search method
// *****************************************************************************

bool JS_ScdlProblem :: TabooSearch ()
{
    TimingScdlSR (SP_SRTSC);
    FindCriticalPath ();
    BlocksOnCriticalPath ();

    bool i_TL = false, i_iCP = false, aux = false;

    int i_best;

    float BestCmax = FLT_MAX,
          OptCmax = SP_Makespan;

    VecInt A, B, C, D, E, F, TabuListA, TabuListB;

    MatInt BestScdl = SP_SRScdl,
           OptScdl = SP_SRScdl;

    TabuListA.reserve(SP_Tenure);
    TabuListB.reserve(SP_Tenure);

    if (SP_CriticalPathIndex < 0)
    {
        i_iCP = true;
    }

    if (SP_Convergence_Analysis_Mode == CA_BY_ITERATION)
    {
        fprintf (file_out, "\n Convergence Analysis:\n");
        fprintf (file_out, "\n %4d\t%10.0f", 0, SP_Makespan);
    }

    for (UINT ite=0; ite<SP_TSNMaxIte; ite++)
    {

        i_best = -1;
        BestCmax = FLT_MAX;

        if (i_iCP == true)
        {
            SP_CriticalPathIndex = rand()%(SP_CriticalPath.size());
        }

        aux = N5_Ngh (A, B);

        SP_NSolutionsEvaluated = SP_NSolutionsEvaluated + A.size();

        if (aux == FALSE) break;

        if (SP_Neighborhood.size() == 1)
        {
            i_best = 0;
            BestScdl = SP_Neighborhood[0];
        }
        else for (int i=0; i<(int)SP_Neighborhood.size(); i++)
        {
            i_TL = false;

            SP_SRScdl = SP_Neighborhood[i];
            TimingScdlSR();

            for (UINT j=0; j<TabuListA.size(); j++)
            {
                if (A[i] == TabuListA[j] && B[i] == TabuListB[j])
                {
                    i_TL = true;
                    break;
                }
            }

            if (SP_Makespan < OptCmax)
            {
                ite = 0;
                i_best = i;

                BestCmax = SP_Makespan;
                BestScdl = SP_SRScdl;

                OptCmax = SP_Makespan;
                OptScdl = SP_SRScdl;

            }
            else if (SP_Makespan < BestCmax && i_TL == false)
            {
                i_best = i;

                BestCmax = SP_Makespan;
                BestScdl = SP_SRScdl;
            }

            if (i == (int)SP_Neighborhood.size()-1 && i_best < 0 && TabuListA.size() > 0)
            {
                TabuListA.erase(TabuListA.begin());
                TabuListB.erase(TabuListB.begin());
                i = -1;
            }
        }

        SP_SRScdl = BestScdl;
        TimingScdlSR ();
        FindCriticalPath ();
        BlocksOnCriticalPath ();

        if (SP_Convergence_Analysis_Mode == CA_BY_ITERATION)
        {
            fprintf (file_out, "\n %4d\t%10.0f", ite+1, SP_Makespan);
        }

        if (i_best == -1 && TabuListA.size() > 0)
        {
            TabuListA.erase(TabuListA.begin());
            TabuListB.erase(TabuListB.begin());
        }
        else
        {
            TabuListA.push_back (B[i_best]);
            TabuListB.push_back (A[i_best]);

            if (TabuListA.size() > SP_Tenure)
            {
                TabuListA.erase(TabuListA.begin());
                TabuListB.erase(TabuListB.begin());
            }
        }
    }

    if (SP_Convergence_Analysis_Mode == CA_BY_ITERATION)
    {
        fprintf (file_out, "\n\n Final results:\n\n");
    }

    SP_SRScdl = OptScdl;
    TimingScdlSR (SP_SRTSC);
    WPC_by_TSC ();
    FindCriticalPath ();
    BlocksOnCriticalPath ();

    if (SP_Makespan < SP_BestMakespan)
    {
        SP_BestMakespan = SP_Makespan;
        SP_BestTSC = SP_SRTSC;
        SP_BestWPC = SP_SRWPC;
        SP_BestScdl = SP_SRScdl;
    }

    A.clear();
    B.clear();
    C.clear();
    D.clear();
    E.clear();
    F.clear();

    TabuListA.clear();
    TabuListB.clear();
    BestScdl.clear();
    OptScdl.clear();

    SP_Neighborhood.clear ();

    return TRUE;
}


// *****************************************************************************
// The following function apply the Parallel Taboo Search method
// *****************************************************************************

bool JS_ScdlProblem :: ParallelTabooSearch ()
{
    float BestMakespan = FLT_MAX;

    TriInt VecScdl = SP_VecScdl;

    SP_VecScdl.clear ();
    SP_VecScdl.reserve (SP_PopulationSize);

    SP_VecTSC.clear ();
    SP_VecTSC.reserve (SP_PopulationSize);

    SP_VecWPC.clear ();
    SP_VecWPC.reserve (SP_PopulationSize);

    for (UINT i=0; i<VecScdl.size(); i++)
    {
        SP_SRScdl = VecScdl[i];

        TabooSearch ();

        SP_VecScdl.push_back (SP_SRScdl);
        SP_VecTSC.push_back (SP_SRTSC);
        SP_VecWPC.push_back (SP_SRWPC);

        if (SP_Makespan < BestMakespan)
        {
            BestMakespan = SP_Makespan;
            SP_SolutionIndex = i;
        }
    }

    SP_SRScdl.clear ();
    SP_SRScdl = SP_VecScdl[SP_SolutionIndex];

    TimingScdlSR (SP_SRTSC);
    WPC_by_TSC ();
    FindCriticalPath ();
    BlocksOnCriticalPath ();

    VecScdl.clear();
    return TRUE;
}

// *****************************************************************************
// The following function prints on screen the current taboo search parameters
// *****************************************************************************

bool JS_ScdlProblem :: PrintOnScreenTabooSearchParameters ()
{
    printf ("\n\n Taboo Search parameters:");
    printf ("\n\n Neighborhood generation method:");

    switch (SP_NghMethod)
    {
        case N5:
            printf (" N5");
            break;
        default:
            printf (" No method was defined");
            break;
    }

    printf ("\n Critical path: %d", SP_CriticalPathIndex);
    printf ("\n Tenure: %d", SP_Tenure);
    printf ("\n Maximum number of iterations without upgrade: %d", SP_TSNMaxIte);

    return TRUE;
}
