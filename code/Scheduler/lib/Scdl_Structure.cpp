#include "Scdl_Structure.h"

// *****************************************************************************
// *** Mathematic operators
// *****************************************************************************

// *****************************************************************************
// Constructive and destructive functions
// *****************************************************************************

ScdlProblem :: ScdlProblem ()
{
    SP_ExecutionMode = OPTIMALE;
    SP_Convergence_Analysis_Mode = CA_NONE;
    SP_Extra_Criterion_Mode = EC_NO_EXTRA_CRITERION;
    SP_InitialSolutionMethod = SIMPLE_ORDERLY;

    SP_Method = TABOO_SEARCH;
    SP_ScMethod = NO_METHOD;
    SP_ThMethod = NO_METHOD;

    SP_NghMethod = N5;
    SP_Tenure = 8;
    SP_TSNMaxIte = 100;

    SP_FtNghMethod = N5;
    SP_FtTenure = 8;
    SP_FtTSNMaxIte = 100;

    SP_ScNghMethod = N5;
    SP_ScTenure = 8;
    SP_ScTSNMaxIte = 100;

    SP_ThNghMethod = N5;
    SP_ThTenure = 8;
    SP_ThTSNMaxIte = 100;

    SP_InitialSolutionVecMethod = RANDOM_INITIAL_SOLUTION_VECTOR;
    SP_NCycles = 10;

    SP_PopulationSize = 12;
    SP_CrossoverMethod = RANDOM_C1;
    SP_MutationMethod = M1;
    SP_MutationPercent = 20;
    SP_SPSNMaxIte = 1;

    SP_FtCrossoverMethod = RANDOM_C1;
    SP_FtMutationMethod = M1;
    SP_FtMutationPercent = 20;
    SP_FtSPSNMaxIte = 1;

    SP_ScCrossoverMethod = RANDOM_C1;
    SP_ScMutationMethod = M1;
    SP_ScMutationPercent = 20;
    SP_ScSPSNMaxIte = 1;

    SP_ThCrossoverMethod = RANDOM_C1;
    SP_ThMutationMethod = M1;
    SP_ThMutationPercent = 20;
    SP_ThSPSNMaxIte = 1;

    SP_PerturbationMethod = PM_M1;
    SP_ExploitationMethod = EM_TABOO_SEARCH;
    SP_PCNMaxIte = 10;

    SP_SolutionIndex = 0;

    SP_Sensibility_Analysis_Initial_Value = 100;
    SP_Sensibility_Analysis_Final_Value = 10000;
    SP_Sensibility_Analysis_Increase_Value = 10;
    SP_Sensibility_Analysis_Repetitions = 5;
    SP_Sensibility_Analysis_Increase_Mode = MULTIPLICATION;
    SP_Sensibility_Analysis_Parameter = SA_TSFTM_MAXITE;
    SP_Sensibility_Analysis_Print_Parameter = PRINT_BEST;

    SP_NTaskJob.clear();
    SP_NTaskMcn.clear();
    SP_JobOfTask.clear();
    SP_McnOfTask.clear();
    SP_FirstTaskOfJob.clear();
    SP_LastTaskOfJob.clear();
    SP_PrevTaskOnJob.clear();
    SP_PrevTaskOnMcn.clear();
    SP_TimeOfTask.clear();

    SP_SRTSC.clear();
    SP_SRWPC.clear();
    SP_SRScdl.clear();

    SP_PrevTSC.clear();
    SP_PrevWPC.clear();
    SP_PrevScdl.clear();

    SP_CurrentTSC.clear();
    SP_CurrentWPC.clear();
    SP_CurrentScdl.clear();

    SP_BestTSC.clear();
    SP_BestWPC.clear();
    SP_BestScdl.clear();

    SP_VecTSC.clear();
    SP_VecWPC.clear();
    SP_VecScdl.clear();

    SP_CriticalPath.clear();
    SP_Neighborhood.clear();
}

ScdlProblem :: ~ScdlProblem ()
{
    SP_NTaskJob.clear();
    SP_NTaskMcn.clear();
    SP_JobOfTask.clear();
    SP_McnOfTask.clear();
    SP_FirstTaskOfJob.clear();
    SP_LastTaskOfJob.clear();
    SP_PrevTaskOnJob.clear();
    SP_PrevTaskOnMcn.clear();
    SP_TimeOfTask.clear();

    SP_SRTSC.clear();
    SP_SRWPC.clear();
    SP_SRScdl.clear();

    SP_PrevTSC.clear();
    SP_PrevWPC.clear();
    SP_PrevScdl.clear();

    SP_CurrentTSC.clear();
    SP_CurrentWPC.clear();
    SP_CurrentScdl.clear();

    SP_BestTSC.clear();
    SP_BestWPC.clear();
    SP_BestScdl.clear();

    SP_VecTSC.clear();
    SP_VecWPC.clear();
    SP_VecScdl.clear();

    SP_CriticalPath.clear();
    SP_Neighborhood.clear();
}

// ***** Class JS_ScdlProblem

// *****************************************************************************
// Constructive and destructive functions
// *****************************************************************************

JS_ScdlProblem :: JS_ScdlProblem ()
{
}

JS_ScdlProblem :: ~JS_ScdlProblem ()
{
}
