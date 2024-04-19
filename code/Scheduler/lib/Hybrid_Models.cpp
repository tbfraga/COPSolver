#include "Scdl_Structure.h"

// ***** Class JS_ScdlProblem

// *****************************************************************************
// This function schedule the selected problem with the hybrid selected method
// *****************************************************************************

bool JS_ScdlProblem :: HybridScheduler ()
{
    time_t start, end;

    SP_BestMakespan = SP_Makespan;
    SP_BestScdl = SP_SRScdl;
    SP_BestTSC = SP_SRTSC;
    SP_BestWPC = SP_SRWPC;

    SP_PrevTSC = SP_SRTSC;
    SP_PrevWPC = SP_SRWPC;
    SP_PrevScdl = SP_SRScdl;

    SP_PrevVecScdl = SP_VecScdl;
    SP_PrevVecTSC = SP_VecTSC;
    SP_PrevVecWPC = SP_VecWPC;

    switch (SP_ExecutionMode)
    {
        case OPTIMALE:
        {
            SP_NSolutionsEvaluated = 0;
            time (&start);

            switch (SP_HybridModel)
            {
                case HYBRID_SUCCESSIVE_APPLICATION:
                    HybridSuccessiveApplication ();
                    break;

                case HYBRID_NEIGHBORHOOD:
                    HybridNeighborhood ();
                    break;

                case HYBRID_IMPROVED_NEIGHBORHOOD:
                    HybridImprovedNeighborhood ();
                    break;

                default:
                    MessageBox (NULL, "This hybrid model is not valible !", "Error", MB_OK | MB_ICONINFORMATION);
                    return FALSE;
            }

            time (&end);
            SP_CPUTime = difftime (end, start);
        }
        break;

        case ANALITICAL:
            break;

        case VISUAL:
            break;

        default:
            return FALSE;
    }

    SP_SRScdl = SP_BestScdl;
    SP_SRTSC = SP_BestTSC;
    SP_SRWPC = SP_BestWPC;

    TimingScdlSR ();
    FindCriticalPath ();
    BlocksOnCriticalPath ();

    SP_CurrentTSC = SP_SRTSC;
    SP_CurrentWPC = SP_SRWPC;
    SP_CurrentScdl = SP_SRScdl;

    SP_CurrentVecScdl = SP_VecScdl;
    SP_CurrentVecTSC = SP_VecTSC;
    SP_CurrentVecWPC = SP_VecWPC;

    return TRUE;
}

bool JS_ScdlProblem :: HybridSuccessiveApplication()
{
    if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
    {
        fprintf (file_out, "\n Convergence Analysis:\n");
        fprintf (file_out, "\n %4d\t%10.0f", 0, SP_Makespan);
    }

    for (UINT i=0; i<SP_NCycles; i++)
    {
        switch (SP_Method)
        {
            case PARALLEL_TABOO_SEARCH:

                SP_NghMethod = SP_FtNghMethod;
                SP_Tenure = SP_FtTenure;
                SP_TSNMaxIte = SP_FtTSNMaxIte;

                ParallelTabooSearch ();

                break;

            case PARTICLE_SWARM:

                SP_CrossoverMethod = SP_FtCrossoverMethod;
                SP_MutationMethod = SP_FtMutationMethod;
                SP_MutationPercent = SP_FtMutationPercent;
                SP_SPSNMaxIte = SP_FtSPSNMaxIte;

                SimilarParticleSwarm ();

                break;

            default:
                break;
        }

        switch (SP_ScMethod)
        {
            case PARALLEL_TABOO_SEARCH:

                SP_NghMethod = SP_ScNghMethod;
                SP_Tenure = SP_ScTenure;
                SP_TSNMaxIte = SP_ScTSNMaxIte;

                ParallelTabooSearch ();

                break;

            case PARTICLE_SWARM:

                SP_CrossoverMethod = SP_ScCrossoverMethod;
                SP_MutationMethod = SP_ScMutationMethod;
                SP_MutationPercent = SP_ScMutationPercent;
                SP_SPSNMaxIte = SP_ScSPSNMaxIte;

                SimilarParticleSwarm ();

                break;

            case NO_METHOD:
                break;

            default:
                break;
        }

        switch (SP_ThMethod)
        {
            case PARALLEL_TABOO_SEARCH:

                SP_NghMethod = SP_ThNghMethod;
                SP_Tenure = SP_ThTenure;
                SP_TSNMaxIte = SP_ThTSNMaxIte;

                ParallelTabooSearch ();

                break;

            case PARTICLE_SWARM:

                SP_CrossoverMethod = SP_ThCrossoverMethod;
                SP_MutationMethod = SP_ThMutationMethod;
                SP_MutationPercent = SP_ThMutationPercent;
                SP_SPSNMaxIte = SP_ThSPSNMaxIte;

                SimilarParticleSwarm ();

                break;

            case NO_METHOD:
                break;

            default:
                break;
        }

        if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
        {
            fprintf (file_out, "\n %4d\t%10.0f", i+1, SP_BestMakespan);
        }

        if (SP_Extra_Criterion_Mode == EC_BEST_MAKESPAN_FOUND)
        {
            if (SP_BestMakespan <= SP_Best_Makespan_Known)
            break;
        }
    }

    if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
    {
        fprintf (file_out, "\n\n Final results:\n\n");
    }

    SP_SRTSC = SP_BestTSC;
    SP_SRWPC = SP_BestWPC;
    SP_SRScdl = SP_BestScdl;

    TimingScdlSR ();

    FindCriticalPath ();
    BlocksOnCriticalPath ();

    SP_NghMethod = SP_FtNghMethod;
    SP_Tenure = SP_FtTenure;
    SP_TSNMaxIte = SP_FtTSNMaxIte;

    SP_CrossoverMethod = SP_FtCrossoverMethod;
    SP_MutationMethod = SP_FtMutationMethod;
    SP_MutationPercent = SP_FtMutationPercent;
    SP_SPSNMaxIte = SP_FtSPSNMaxIte;

    return TRUE;
}

bool JS_ScdlProblem :: HybridNeighborhood()
{
    int rnd;

    MatUInt VecWPC;
    TriInt VecScdl;
    TriInt Neighborhood;

    VecWPC.reserve (SP_PopulationSize);
    VecScdl.reserve (SP_PopulationSize);

    Neighborhood.reserve (3*SP_PopulationSize);

    if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
    {
        fprintf (file_out, "\n Convergence Analysis:\n");
        fprintf (file_out, "\n %4d\t%10.0f", 0, SP_Makespan);
    }

    for (UINT i=0; i<SP_NCycles; i++)
    {
        VecScdl.clear ();
        VecScdl = SP_VecScdl;

        VecWPC.clear ();
        VecWPC = SP_VecWPC;

        switch (SP_Method)
        {
            case PARALLEL_TABOO_SEARCH:

                SP_NghMethod = SP_FtNghMethod;
                SP_Tenure = SP_FtTenure;
                SP_TSNMaxIte = SP_FtTSNMaxIte;

                ParallelTabooSearch ();

                break;

            case PARTICLE_SWARM:

                SP_CrossoverMethod = SP_FtCrossoverMethod;
                SP_MutationMethod = SP_FtMutationMethod;
                SP_MutationPercent = SP_FtMutationPercent;
                SP_SPSNMaxIte = SP_FtSPSNMaxIte;

                SimilarParticleSwarm ();

                break;

            default:
                MessageBox (NULL, "This is not a valible method !", "Error", MB_OK | MB_ICONINFORMATION);
                return FALSE;
        }

        Neighborhood.assign (SP_VecScdl.begin(), SP_VecScdl.end());

        switch (SP_ScMethod)
        {
            case PARALLEL_TABOO_SEARCH:

                SP_NghMethod = SP_ScNghMethod;
                SP_Tenure = SP_ScTenure;
                SP_TSNMaxIte = SP_ScTSNMaxIte;

                SP_VecScdl.clear();
                SP_VecScdl = VecScdl;

                ParallelTabooSearch ();

                Neighborhood.insert (Neighborhood.end(), SP_VecScdl.begin(), SP_VecScdl.end());

                break;

            case PARTICLE_SWARM:

                SP_CrossoverMethod = SP_ScCrossoverMethod;
                SP_MutationMethod = SP_ScMutationMethod;
                SP_MutationPercent = SP_ScMutationPercent;
                SP_SPSNMaxIte = SP_ScSPSNMaxIte;

                SP_VecWPC.clear();
                SP_VecWPC = VecWPC;

                SimilarParticleSwarm ();

                Neighborhood.insert (Neighborhood.end(), SP_VecScdl.begin(), SP_VecScdl.end());

                break;

            case NO_METHOD:
                break;

            default:
                MessageBox (NULL, "This is not a valible method !", "Error", MB_OK | MB_ICONINFORMATION);
                return FALSE;
        }

        switch (SP_ThMethod)
        {
            case PARALLEL_TABOO_SEARCH:

                SP_NghMethod = SP_ThNghMethod;
                SP_Tenure = SP_ThTenure;
                SP_TSNMaxIte = SP_ThTSNMaxIte;

                SP_VecScdl.clear();
                SP_VecScdl = VecScdl;

                ParallelTabooSearch ();

                Neighborhood.insert (Neighborhood.end(), SP_VecScdl.begin(), SP_VecScdl.end());

                break;

            case PARTICLE_SWARM:

                SP_CrossoverMethod = SP_ThCrossoverMethod;
                SP_MutationMethod = SP_ThMutationMethod;
                SP_MutationPercent = SP_ThMutationPercent;
                SP_SPSNMaxIte = SP_ThSPSNMaxIte;

                SP_VecWPC.clear();
                SP_VecWPC = VecWPC;

                SimilarParticleSwarm ();

                Neighborhood.insert (Neighborhood.end(), SP_VecScdl.begin(), SP_VecScdl.end());

                break;

            case NO_METHOD:
                break;

            default:
                MessageBox (NULL, "This is not a valible method !", "Error", MB_OK | MB_ICONINFORMATION);
                return FALSE;
        }

        if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
        {
            fprintf (file_out, "\n %4d\t%10.0f", i+1, SP_BestMakespan);
        }

        while (Neighborhood.size() > SP_PopulationSize)
        {
            rnd = rand()%(Neighborhood.size());
            Neighborhood.erase(Neighborhood.begin() + rnd);
        }

        SP_VecScdl = Neighborhood;

        SP_VecTSC.clear ();
        SP_VecWPC.clear ();

        SP_VecTSC.reserve (SP_PopulationSize);
        SP_VecWPC.reserve (SP_PopulationSize);

        for (UINT i=0; i<SP_PopulationSize; i++)
        {
            SP_SRScdl = SP_VecScdl[i];

            TimingScdlSR (SP_SRTSC);
            WPC_by_TSC ();

            SP_VecTSC.push_back (SP_SRTSC);
            SP_VecWPC.push_back (SP_SRWPC);
        }

        if (SP_Extra_Criterion_Mode == EC_BEST_MAKESPAN_FOUND)
        {
            if (SP_BestMakespan <= SP_Best_Makespan_Known)
            break;
        }

    }

    if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
    {
        fprintf (file_out, "\n\n Final results:\n\n");
    }

    SP_SRTSC = SP_BestTSC;
    SP_SRWPC = SP_BestWPC;
    SP_SRScdl = SP_BestScdl;

    TimingScdlSR ();
    FindCriticalPath ();
    BlocksOnCriticalPath ();

    SP_NghMethod = SP_FtNghMethod;
    SP_Tenure = SP_FtTenure;
    SP_TSNMaxIte = SP_FtTSNMaxIte;

    SP_CrossoverMethod = SP_FtCrossoverMethod;
    SP_MutationMethod = SP_FtMutationMethod;
    SP_MutationPercent = SP_FtMutationPercent;
    SP_SPSNMaxIte = SP_FtSPSNMaxIte;

    VecScdl.clear ();
    VecWPC.clear ();
    Neighborhood.clear ();

    return TRUE;
}

bool JS_ScdlProblem :: HybridImprovedNeighborhood()
{
    int rnd;
    TriInt Neighborhood;

    Neighborhood.reserve (3*SP_PopulationSize);

    if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
    {
        fprintf (file_out, "\n Convergence Analysis:\n");
        fprintf (file_out, "\n %4d\t%10.0f", 0, SP_Makespan);
    }

    for (UINT i=0; i<SP_NCycles; i++)
    {
        switch (SP_Method)
        {
            case PARALLEL_TABOO_SEARCH:

                SP_NghMethod = SP_FtNghMethod;
                SP_Tenure = SP_FtTenure;
                SP_TSNMaxIte = SP_FtTSNMaxIte;

                ParallelTabooSearch ();

                break;

            case PARTICLE_SWARM:

                SP_CrossoverMethod = SP_FtCrossoverMethod;
                SP_MutationMethod = SP_FtMutationMethod;
                SP_MutationPercent = SP_FtMutationPercent;
                SP_SPSNMaxIte = SP_FtSPSNMaxIte;

                SimilarParticleSwarm ();

                break;

            default:
                MessageBox (NULL, "This is not a valible method !", "Error", MB_OK | MB_ICONINFORMATION);
                return FALSE;
        }

        Neighborhood.assign (SP_VecScdl.begin(), SP_VecScdl.end());

        switch (SP_ScMethod)
        {
            case PARALLEL_TABOO_SEARCH:

                SP_NghMethod = SP_ScNghMethod;
                SP_Tenure = SP_ScTenure;
                SP_TSNMaxIte = SP_ScTSNMaxIte;

                ParallelTabooSearch ();

                Neighborhood.insert (Neighborhood.end(), SP_VecScdl.begin(), SP_VecScdl.end());

                break;

            case PARTICLE_SWARM:

                SP_CrossoverMethod = SP_ScCrossoverMethod;
                SP_MutationMethod = SP_ScMutationMethod;
                SP_MutationPercent = SP_ScMutationPercent;
                SP_SPSNMaxIte = SP_ScSPSNMaxIte;

                SimilarParticleSwarm ();

                Neighborhood.insert (Neighborhood.end(), SP_VecScdl.begin(), SP_VecScdl.end());

                break;

            case NO_METHOD:
                break;

            default:
                MessageBox (NULL, "This is not a valible method !", "Error", MB_OK | MB_ICONINFORMATION);
                return FALSE;
        }

        switch (SP_ThMethod)
        {
            case PARALLEL_TABOO_SEARCH:

                SP_NghMethod = SP_ThNghMethod;
                SP_Tenure = SP_ThTenure;
                SP_TSNMaxIte = SP_ThTSNMaxIte;

                ParallelTabooSearch ();

                Neighborhood.insert (Neighborhood.end(), SP_VecScdl.begin(), SP_VecScdl.end());

                break;

            case PARTICLE_SWARM:

                SP_CrossoverMethod = SP_ThCrossoverMethod;
                SP_MutationMethod = SP_ThMutationMethod;
                SP_MutationPercent = SP_ThMutationPercent;
                SP_SPSNMaxIte = SP_ThSPSNMaxIte;

                SimilarParticleSwarm ();

                Neighborhood.insert (Neighborhood.end(), SP_VecScdl.begin(), SP_VecScdl.end());

                break;

            case NO_METHOD:
                break;

            default:
                MessageBox (NULL, "This is not a valible method !", "Error", MB_OK | MB_ICONINFORMATION);
                return FALSE;
        }

        if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
        {
            fprintf (file_out, "\n %4d\t%10.0f", i+1, SP_BestMakespan);
        }

        while (Neighborhood.size() > SP_PopulationSize)
        {
            rnd = rand()%(Neighborhood.size());
            Neighborhood.erase(Neighborhood.begin() + rnd);
        }

        SP_VecScdl = Neighborhood;

        SP_VecTSC.clear ();
        SP_VecWPC.clear ();

        SP_VecTSC.reserve (SP_PopulationSize);
        SP_VecWPC.reserve (SP_PopulationSize);

        for (UINT i=0; i<SP_PopulationSize; i++)
        {
            SP_SRScdl = SP_VecScdl[i];

            TimingScdlSR (SP_SRTSC);
            WPC_by_TSC ();

            SP_VecTSC.push_back (SP_SRTSC);
            SP_VecWPC.push_back (SP_SRWPC);
        }

        if (SP_Extra_Criterion_Mode == EC_BEST_MAKESPAN_FOUND)
        {
            if (SP_BestMakespan <= SP_Best_Makespan_Known)
            break;
        }
    }

    if (SP_Convergence_Analysis_Mode == CA_BY_CYCLE)
    {
        fprintf (file_out, "\n\n Final results:\n\n");
    }

    SP_SRTSC = SP_BestTSC;
    SP_SRWPC = SP_BestWPC;
    SP_SRScdl = SP_BestScdl;

    TimingScdlSR ();
    FindCriticalPath ();
    BlocksOnCriticalPath ();

    SP_NghMethod = SP_FtNghMethod;
    SP_Tenure = SP_FtTenure;
    SP_TSNMaxIte = SP_FtTSNMaxIte;

    SP_CrossoverMethod = SP_FtCrossoverMethod;
    SP_MutationMethod = SP_FtMutationMethod;
    SP_MutationPercent = SP_FtMutationPercent;
    SP_SPSNMaxIte = SP_FtSPSNMaxIte;

    Neighborhood.clear ();

    return TRUE;
}
