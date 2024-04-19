#include "Scdl_Structure.h"

// *****************************************************************************
// Function to generate a list of perturbation methods
// *****************************************************************************

VecLPSTR PerturbationMethodList ()
{
    LPSTR PMethod;
    VecLPSTR PMethodList;

    PMethod = "M1";
    PMethodList.push_back (PMethod);

    return PMethodList;
}

// *****************************************************************************
// Function to generate a list of exploitation methods
// *****************************************************************************

VecLPSTR ExploitationMethodList ()
{
    LPSTR EMethod;
    VecLPSTR EMethodList;

    EMethod = "Taboo Search";
    EMethodList.push_back (EMethod);

    return EMethodList;
}

// ***** Class ScdlProblem

// *****************************************************************************
// Functions to set the value of the protected variables
// *****************************************************************************

void ScdlProblem :: PerturbationMethod (const UINT &PMethod)
{
    SP_PerturbationMethod = PMethod;
}

void ScdlProblem :: ExploitationMethod (const UINT &EMethod)
{
    SP_ExploitationMethod = EMethod;
}

void ScdlProblem :: PCNMaxIte (const UINT &NMaxIte)
{
    SP_PCNMaxIte = NMaxIte;
}

// *****************************************************************************
// Functions to return the value of the protected variables
// *****************************************************************************

UINT ScdlProblem :: PerturbationMethod ()
{
    return SP_PerturbationMethod;
}

UINT ScdlProblem :: ExploitationMethod ()
{
    return SP_ExploitationMethod;
}

UINT ScdlProblem :: PCNMaxIte ()
{
    return SP_PCNMaxIte;
}

// ***** Class ScdlProblem

bool JS_ScdlProblem :: Perturbation ()
{
    switch (SP_PerturbationMethod)
    {
        case PM_M1:

            M1_Operator (SP_SRWPC);

            TSC_by_WPC ();
            Scdl_by_TSC ();

            SP_NSolutionsEvaluated++;

            break;

        default:
            MessageBox (NULL, "The Perturbation Method is not valible !", "Error", MB_OK | MB_ICONINFORMATION);
            return FALSE;
    }

    return TRUE;
}

bool JS_ScdlProblem :: Exploitation ()
{
    switch (SP_ExploitationMethod)
    {
        case EM_TABOO_SEARCH:
            TabooSearch ();
            break;

        default:
            MessageBox (NULL, "The Exploitation Method is not valible !", "Error", MB_OK | MB_ICONINFORMATION);
    }

    return TRUE;
}

bool JS_ScdlProblem :: Scattering (const float &ScatteringPercent)
{
    float rnd = rand()%(100) / 100.00;

    if (ScatteringPercent > rnd)
    {
        RandomInitialSolution ();
        SP_NSolutionsEvaluated++;
    }
    else
    {
        Exploitation ();
    }

    return TRUE;
}

bool JS_ScdlProblem :: ParticleCollision ()
{
    float OldMakespan = SP_Makespan,
          BestMakespan = SP_Makespan,
          ScatteringPercent;

    MatInt OldScdl = SP_SRScdl,
           BestScdl = SP_SRScdl;

    if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
    {
        fprintf (file_out, "\n\n Convergence Analysis:\n");
        fprintf (file_out, "\n %4d\t%10.0f", 0, SP_Makespan);
    }

    for (UINT i=0; i<SP_PCNMaxIte; i++)
    {
        Perturbation ();

        if (SP_Makespan < OldMakespan)
        {
            Exploitation ();
        }
        else
        {
            ScatteringPercent = 1.0 - BestMakespan/SP_Makespan;
            Scattering (ScatteringPercent);
        }

        OldScdl = SP_SRScdl;
        OldMakespan = SP_Makespan;

        if (SP_Makespan < BestMakespan)
        {
            BestMakespan = SP_Makespan;
            BestScdl = SP_SRScdl;
        }

        if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
        {
            fprintf (file_out, "\n %4d\t%10.0f", i+1, BestMakespan);
        }

        if (SP_Extra_Criterion_Mode == EC_BEST_MAKESPAN_FOUND)
        {
            if (SP_Makespan <= SP_Best_Makespan_Known)
            break;
        }
    }

    if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
    {
        fprintf (file_out, "\n\n Final results:\n\n");
    }

    SP_SRScdl = BestScdl;
    TimingScdlSR (SP_SRTSC);
    WPC_by_TSC ();

    FindCriticalPath ();
    BlocksOnCriticalPath ();

    OldScdl.clear();
    BestScdl.clear();

    return TRUE;
}

// *****************************************************************************
// The following function apply the Parallel Particle Collision algorithm
// *****************************************************************************

bool JS_ScdlProblem :: ParallelParticleCollision ()
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
        if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
        {
            fprintf (file_out, "\n\n Solution: %4d", i+1);
        }

        SP_SRScdl = VecScdl[i];
        TimingScdlSR ();

        ParticleCollision ();

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
