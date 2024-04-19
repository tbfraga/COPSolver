#include "Scdl_Structure.h"

// ***** Class JS_ScdlProblem

// *****************************************************************************
// The following function generates a new solution by the defined crossover
// operator
// *****************************************************************************

bool JS_ScdlProblem :: Crossover (const VecUInt &WPC_1, const VecUInt &WPC_2)
{
    switch (SP_CrossoverMethod)
    {
        case RANDOM_C1:
            return RandomC1 (WPC_1, WPC_2);

        default:
            return FALSE;
    }
    return TRUE;
}

// *****************************************************************************
// The following function applies the random C1 crossover operator
// *****************************************************************************

bool JS_ScdlProblem :: RandomC1 (const VecUInt &WPC_1, const VecUInt &WPC_2)
{
    if (WPC_1.size() != WPC_2.size())
    {
        printf ("\n\n Warning: diferent size of the cromossomes !!!");
        return FALSE;
    }

    if (WPC_1.size() < 2)
    {
        printf ("\n\n Warning: size of the cromossomes smaller than 2!!!");
        return FALSE;
    }

    UINT CP1 = 0;
    UINT CP2 = rand()%(WPC_1.size());

    float PartialMakespan;

    VecUInt WPC,
            Aux = WPC_2;

    // First crossover

    for (UINT i=CP1; i<=CP2; i++)
    {
        for (UINT j=0; j<Aux.size(); j++)
        {
            if (WPC_1[i] == Aux[j])
            {
                Aux.erase(Aux.begin()+j);
                break;
            }
        }
    }

    SP_SRWPC = WPC_1;

    UINT aux = 0;
    for (UINT i=CP2+1; i<WPC_1.size(); i++)
    {
        SP_SRWPC[i] = Aux[aux];
        aux++;
    }

    Timing_WPC();

    WPC = SP_SRWPC;
    PartialMakespan = SP_Makespan;

    // Second crossover

    Aux.clear();
    Aux = WPC_1;

    for (UINT i=0; i<=CP2; i++)
    {
        for (UINT j=0; j<Aux.size(); j++)
        {
            if (WPC_2[i] == Aux[j])
            {
                Aux.erase(Aux.begin()+j);
                break;
            }
        }
    }

    SP_SRWPC.clear ();
    SP_SRWPC = WPC_2;

    aux = 0;
    for (UINT i=CP2+1; i<WPC_2.size(); i++)
    {
        SP_SRWPC[i] = Aux[aux];
        aux++;
    }

    Timing_WPC();

    if (PartialMakespan < SP_Makespan)
    {
        SP_SRWPC = WPC;
        Timing_WPC();
    }

    Aux.clear();
    WPC.clear();

    return TRUE;
}
