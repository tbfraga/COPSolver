#include "Scdl_Structure.h"

// *****************************************************************************
// Generate a list with the Crossover methods
// *****************************************************************************

VecLPSTR CrossoverMethodList ()
{
    LPSTR CMethod;
    VecLPSTR CMethodList;

    CMethod = "Rnd C1";
    CMethodList.push_back (CMethod);

    return CMethodList;
}

VecLPSTR MutationMethodList ()
{
    LPSTR MMethod;
    VecLPSTR MMethodList;

    MMethod = "M1";
    MMethodList.push_back (MMethod);

    return MMethodList;
}

// ***** Class ScdlProblem

// *****************************************************************************
// Functions to set the value of the protected variables
// *****************************************************************************

void ScdlProblem :: PopulationSize (const UINT PopulationSize)
{
    SP_PopulationSize = PopulationSize;
}

void ScdlProblem :: CrossoverMethod (const UINT CrossoverMethod)
{
    SP_CrossoverMethod = CrossoverMethod;
}

void ScdlProblem :: MutationMethod (const UINT MutationMethod)
{
    SP_MutationMethod = MutationMethod;
}

void ScdlProblem :: MutationPercent (const UINT MutationPercent)
{
    SP_MutationPercent = MutationPercent;
}

void ScdlProblem :: SPSNMaxIte (const UINT &NMaxIte)
{
    SP_SPSNMaxIte = NMaxIte;
}

void ScdlProblem :: FtCrossoverMethod (const UINT CrossoverMethod)
{
    SP_FtCrossoverMethod = CrossoverMethod;
}

void ScdlProblem :: FtMutationMethod (const UINT MutationMethod)
{
    SP_FtMutationMethod = MutationMethod;
}

void ScdlProblem :: FtMutationPercent (const UINT MutationPercent)
{
    SP_FtMutationPercent = MutationPercent;
}

void ScdlProblem :: FtSPSNMaxIte (const UINT &NMaxIte)
{
    SP_FtSPSNMaxIte = NMaxIte;
}

void ScdlProblem :: ScCrossoverMethod (const UINT CrossoverMethod)
{
    SP_ScCrossoverMethod = CrossoverMethod;
}

void ScdlProblem :: ScMutationMethod (const UINT MutationMethod)
{
    SP_ScMutationMethod = MutationMethod;
}

void ScdlProblem :: ScMutationPercent (const UINT MutationPercent)
{
    SP_ScMutationPercent = MutationPercent;
}

void ScdlProblem :: ScSPSNMaxIte (const UINT &NMaxIte)
{
    SP_ScSPSNMaxIte = NMaxIte;
}

void ScdlProblem :: ThCrossoverMethod (const UINT CrossoverMethod)
{
    SP_ThCrossoverMethod = CrossoverMethod;
}

void ScdlProblem :: ThMutationMethod (const UINT MutationMethod)
{
    SP_ThMutationMethod = MutationMethod;
}

void ScdlProblem :: ThMutationPercent (const UINT MutationPercent)
{
    SP_ThMutationPercent = MutationPercent;
}

void ScdlProblem :: ThSPSNMaxIte (const UINT &NMaxIte)
{
    SP_ThSPSNMaxIte = NMaxIte;
}

// *****************************************************************************
// Functions to return the value of the protected variables
// *****************************************************************************

UINT ScdlProblem :: PopulationSize ()
{
    return SP_PopulationSize;
}

UINT ScdlProblem :: CrossoverMethod ()
{
    return SP_CrossoverMethod;
}

UINT ScdlProblem :: MutationMethod ()
{
    return SP_MutationMethod;
}

UINT ScdlProblem :: MutationPercent ()
{
    return SP_MutationPercent;
}

UINT ScdlProblem :: SPSNMaxIte ()
{
    return SP_SPSNMaxIte;
}

UINT ScdlProblem :: FtCrossoverMethod ()
{
    return SP_FtCrossoverMethod;
}

UINT ScdlProblem :: FtMutationMethod ()
{
    return SP_FtMutationMethod;
}

UINT ScdlProblem :: FtMutationPercent ()
{
    return SP_FtMutationPercent;
}

UINT ScdlProblem :: FtSPSNMaxIte ()
{
    return SP_FtSPSNMaxIte;
}

UINT ScdlProblem :: ScCrossoverMethod ()
{
    return SP_ScCrossoverMethod;
}

UINT ScdlProblem :: ScMutationMethod ()
{
    return SP_ScMutationMethod;
}

UINT ScdlProblem :: ScMutationPercent ()
{
    return SP_ScMutationPercent;
}

UINT ScdlProblem :: ScSPSNMaxIte ()
{
    return SP_ScSPSNMaxIte;
}

UINT ScdlProblem :: ThCrossoverMethod ()
{
    return SP_ThCrossoverMethod;
}

UINT ScdlProblem :: ThMutationMethod ()
{
    return SP_ThMutationMethod;
}

UINT ScdlProblem :: ThMutationPercent ()
{
    return SP_ThMutationPercent;
}

UINT ScdlProblem :: ThSPSNMaxIte ()
{
    return SP_ThSPSNMaxIte;
}

// *****************************************************************************
// The following function apply the Similar Particle Swarm Method
// *****************************************************************************

bool JS_ScdlProblem :: SimilarParticleSwarm ()
{
    //printf ("\n\n Wait... SPSO - Similar Particle Swarm Optimization method "
    //        "by Lian et al. (2006)");

    UINT aux;

    UINT NParticlesInMutation;

    float BestGlobalMakespan = FLT_MAX;

    VecUInt Velocity,
            BestGlobalPosition,
            ParticleIndex,
            MutationIndex;

    MatUInt ParticlePosition,
            ParticleBestPosition;

    VecFloat MakespanParticleBestPosition;

    Velocity.reserve (SP_NTTask);
    BestGlobalPosition.reserve (SP_NTTask);

    ParticleIndex.resize (SP_PopulationSize);
    MutationIndex.resize (SP_PopulationSize);
    ParticlePosition.resize (SP_PopulationSize);
    ParticleBestPosition.resize (SP_PopulationSize);

    MakespanParticleBestPosition.resize (SP_PopulationSize);

    for (UINT i=0; i<ParticleIndex.size(); i++)
    {
        ParticleIndex[i] = i;
    }

    NParticlesInMutation = UINT(SP_MutationPercent*SP_PopulationSize/100);

    for (UINT i=0; i<SP_VecWPC.size(); i++)
    {
        SP_SRWPC = SP_VecWPC[i];
        Timing_WPC();

        ParticlePosition[i] = SP_SRWPC;
        ParticleBestPosition[i] = ParticlePosition[i];

        MakespanParticleBestPosition[i] = SP_Makespan;

        if (SP_Makespan < BestGlobalMakespan)
        {
            BestGlobalMakespan = SP_Makespan;
            BestGlobalPosition = ParticleBestPosition[i];
        }
    }

    for (UINT i=0; i<SP_SPSNMaxIte; i++)
    {
        MutationIndex = ParticleIndex;

        while (MutationIndex.size() > NParticlesInMutation)
        {
            aux = rand()%MutationIndex.size();
            MutationIndex.erase(MutationIndex.begin() + aux);
        }

        aux = 0;

        for (UINT j=0; j<SP_VecWPC.size(); j++)
        {

            Crossover (ParticleBestPosition[j], BestGlobalPosition);

            if (aux < MutationIndex.size() && j == MutationIndex[aux])
            {
                Mutation (SP_SRWPC);
            }

            Velocity = SP_SRWPC;

            Crossover (ParticlePosition[j], Velocity);

            if (aux < MutationIndex.size() && j == MutationIndex[aux])
            {
                Mutation (SP_SRWPC);
                aux++;
            }

            ParticlePosition[j] = SP_SRWPC;
            Timing_WPC();

            if (SP_Makespan <= MakespanParticleBestPosition[j])
            {
                MakespanParticleBestPosition[j] = SP_Makespan;
                ParticleBestPosition[j] = SP_SRWPC;

                if (SP_Makespan <= BestGlobalMakespan)
                {
                    BestGlobalMakespan = SP_Makespan;
                    BestGlobalPosition = SP_SRWPC;
                }
            }
        }
    }

    SP_VecScdl.clear ();
    SP_VecScdl.reserve (SP_PopulationSize);
    SP_VecTSC.clear ();
    SP_VecTSC.reserve (SP_PopulationSize);
    SP_VecWPC.clear ();
    SP_VecWPC = ParticlePosition;

    for (UINT i=0; i<SP_VecWPC.size(); i++)
    {
        SP_SRWPC = SP_VecWPC[i];
        TSC_by_WPC ();
        Scdl_by_TSC ();

        SP_VecScdl.push_back (SP_SRScdl);
        SP_VecTSC.push_back (SP_SRTSC);
    }

    SP_SRWPC = BestGlobalPosition;
    TSC_by_WPC ();
    Scdl_by_TSC ();

    TimingScdlSR ();

    FindCriticalPath ();
    SP_CriticalPathIndex = 0;
    BlocksOnCriticalPath ();

    SP_NSolutionsEvaluated = SP_NSolutionsEvaluated + int(SP_PopulationSize*SP_SPSNMaxIte*(4 + 2.0*SP_MutationPercent/100));

    if (SP_Makespan < SP_BestMakespan)
    {
        SP_BestMakespan = SP_Makespan;
        SP_BestTSC = SP_SRTSC;
        SP_BestWPC = SP_SRWPC;
        SP_BestScdl = SP_SRScdl;
    }

    Velocity.clear ();
    BestGlobalPosition.clear ();
    ParticleIndex.clear ();
    MutationIndex.clear ();
    ParticlePosition.clear ();
    ParticleBestPosition.clear ();

    return TRUE;
}
