#include "Scdl_Structure.h"

// ***** Class JS_ScdlProblem

// *****************************************************************************
// The following function generates a new solution by the defined mutation
// operator
// *****************************************************************************

bool JS_ScdlProblem :: Mutation (const VecUInt WPC)
{
    switch (SP_MutationMethod)
    {
        case M1:
            return M1_Operator(WPC);

        default:
            return FALSE;
    }
    return TRUE;
}

// *****************************************************************************
// The following function applies the M1 mutation operator
// *****************************************************************************

bool JS_ScdlProblem :: M1_Operator (const VecUInt WPC)
{
    UINT aux, MP1, MP2;

    VecUInt Aux;

    MP1 = rand()%(WPC.size());
    MP2 = rand()%(WPC.size());

    if (MP2 < MP1)
    {
        aux = MP1;
        MP1 = MP2;
        MP2 = aux;
    }

    Aux.assign(WPC.begin()+MP1, WPC.begin()+MP2+1);

    SP_SRWPC = WPC;

    SP_SRWPC.erase(SP_SRWPC.begin()+MP1, SP_SRWPC.begin()+MP2+1);

    MP1 = rand()%(SP_SRWPC.size()+1);

    SP_SRWPC.insert(SP_SRWPC.begin()+MP1, Aux.begin(), Aux.end());

    Timing_WPC ();

    Aux.clear ();

    return TRUE;
}
