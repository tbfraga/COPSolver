#include "Scdl_Structure.h"

// *****************************************************************************
// Generate a list with the method modes
// *****************************************************************************

VecLPSTR MethodModeList ()
{
    LPSTR MtMode;
    VecLPSTR MtModeList;

    MtMode = "Single";
    MtModeList.push_back (MtMode);

    MtMode = "Hybrid";
    MtModeList.push_back (MtMode);

    return MtModeList;
}

// *****************************************************************************
// Generate a list with the hybrid models
// *****************************************************************************

VecLPSTR HybridModelList ()
{
    LPSTR HybridModel;
    VecLPSTR HbModelList;

    HybridModel = "Hybrid Successive Application";
    HbModelList.push_back (HybridModel);

    HybridModel = "Hybrid Neighborhood";
    HbModelList.push_back (HybridModel);

    HybridModel = "Hybrid Improved Neighborhood";
    HbModelList.push_back (HybridModel);

    return HbModelList;
}

// *****************************************************************************
// Generate a list with the solving methods
// *****************************************************************************

VecLPSTR MethodList ()
{
    LPSTR Method;
    VecLPSTR MethodList;

    Method = "Taboo Search";
    MethodList.push_back (Method);

    Method = "Particle Collision";
    MethodList.push_back (Method);

    Method = "Parallel Taboo Search";
    MethodList.push_back (Method);

    Method = "Parallel Particle Collision";
    MethodList.push_back (Method);

    Method = "Similar Particle Swarm";
    MethodList.push_back (Method);

    return MethodList;
}

// ***** Class ScdlProblem

// *****************************************************************************
// Functions to set the value of the protected variables
// *****************************************************************************

void ScdlProblem :: MethodMode (const int &MethodMode)
{
    SP_MethodMode = MethodMode;
}

void ScdlProblem :: HybridModel (const int &HybridModel)
{
    SP_HybridModel = HybridModel;
}

void ScdlProblem :: NCycles (const UINT &NCycles)
{
    SP_NCycles = NCycles;
}

void ScdlProblem :: Method (const UINT &Method)
{
    SP_Method = Method;
}

void ScdlProblem :: FtMethod (const UINT &Method)
{
    SP_FtMethod = Method;
}

void ScdlProblem :: ScMethod (const UINT &Method)
{
    SP_ScMethod = Method;
}

void ScdlProblem :: ThMethod (const UINT &Method)
{
    SP_ThMethod = Method;
}

void ScdlProblem :: Sensibility_Analysis_Initial_Value (const UINT &SA_Initial_Value)
{
    SP_Sensibility_Analysis_Initial_Value = SA_Initial_Value;
}

void ScdlProblem :: Sensibility_Analysis_Final_Value (const UINT &SA_Final_Value)
{
    SP_Sensibility_Analysis_Final_Value = SA_Final_Value;
}

void ScdlProblem :: Sensibility_Analysis_Increase_Value (const UINT &SA_Increase_Value)
{
    SP_Sensibility_Analysis_Increase_Value = SA_Increase_Value;
}

void ScdlProblem :: Sensibility_Analysis_Increase_Mode (const UINT &SA_Increase_Mode)
{
    SP_Sensibility_Analysis_Increase_Mode = SA_Increase_Mode;
}

void ScdlProblem :: Sensibility_Analysis_Repetitions (const UINT &SA_Repetitions)
{
    SP_Sensibility_Analysis_Repetitions = SA_Repetitions;
}

void ScdlProblem :: Sensibility_Analysis_Parameter (const UINT &SA_Parameter)
{
    SP_Sensibility_Analysis_Parameter = SA_Parameter;
}

void ScdlProblem :: Sensibility_Analysis_Print_Parameter (const UINT &SA_Print_Parameter)
{
    SP_Sensibility_Analysis_Print_Parameter = SA_Print_Parameter;
}

void ScdlProblem :: Sensibility_Analysis_Convergence_Mode (const UINT &SA_Convergence_Mode)
{
    SP_Convergence_Analysis_Mode = SA_Convergence_Mode;
}

void ScdlProblem :: Sensibility_Analysis_Extra_Criterion_Mode (const UINT &SA_Extra_Criterion_Mode)
{
    SP_Extra_Criterion_Mode = SA_Extra_Criterion_Mode;
}
// *****************************************************************************
// Functions to return the value of the protected variables
// *****************************************************************************

int ScdlProblem :: MethodMode ()
{
    return SP_MethodMode;
}

UINT ScdlProblem :: NCycles ()
{
    return SP_NCycles;
}

UINT ScdlProblem :: Method ()
{
    return SP_Method;
}

UINT ScdlProblem :: FtMethod ()
{
    return SP_FtMethod;
}

UINT ScdlProblem :: ScMethod ()
{
    return SP_ScMethod;
}

UINT ScdlProblem :: ThMethod ()
{
    return SP_ThMethod;
}

int ScdlProblem :: NSolutionsEvaluated ()
{
    return SP_NSolutionsEvaluated;
}

float ScdlProblem :: Makespan ()
{
    return SP_Makespan;
}

float ScdlProblem :: CPUTime ()
{
    return SP_CPUTime;
}

UINT ScdlProblem :: Sensibility_Analysis_Initial_Value ()
{
    return SP_Sensibility_Analysis_Initial_Value;
}

UINT ScdlProblem :: Sensibility_Analysis_Final_Value ()
{
    return SP_Sensibility_Analysis_Final_Value;
}

UINT ScdlProblem :: Sensibility_Analysis_Increase_Value ()
{
    return SP_Sensibility_Analysis_Increase_Value;
}

UINT ScdlProblem :: Sensibility_Analysis_Increase_Mode ()
{
    return SP_Sensibility_Analysis_Increase_Mode;
}

UINT ScdlProblem :: Sensibility_Analysis_Repetitions ()
{
    return SP_Sensibility_Analysis_Repetitions;
}

UINT ScdlProblem :: Sensibility_Analysis_Parameter ()
{
    return SP_Sensibility_Analysis_Parameter;
}

UINT ScdlProblem :: Sensibility_Analysis_Print_Parameter ()
{
    return SP_Sensibility_Analysis_Print_Parameter;
}

UINT ScdlProblem :: Sensibility_Analysis_Convergence_Mode ()
{
    return SP_Convergence_Analysis_Mode;
}

UINT ScdlProblem :: Sensibility_Analysis_Extra_Criterion_Mode ()
{
    return SP_Extra_Criterion_Mode;
}

// *****************************************************************************
// Functions to print on file the Taboo Search parameters
// *****************************************************************************

bool ScdlProblem :: PrintOnFileTabooSearchMethodParameters (FILE *file_out)
{
    fprintf (file_out, "Taboo Search");

    fprintf (file_out, "\n\n With the following fixed parameters:");

    fprintf (file_out, "\n\n\t Neighborhood generation method:");

    switch (SP_NghMethod)
    {
        case 0:
            fprintf (file_out, " N5");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Tenure: %d", SP_Tenure);
    fprintf (file_out, "\n\t Maximum number of iterations without upgrade: %d", SP_TSNMaxIte);

    return true;
}

bool ScdlProblem :: PrintOnFileTabooSearchFirstMethodParameters (FILE *file_out)
{
    fprintf (file_out, "Taboo Search");

    fprintf (file_out, "\n\n With the following fixed parameters:");

    fprintf (file_out, "\n\n\t Neighborhood generation method:");

    switch (SP_FtNghMethod)
    {
        case 0:
            fprintf (file_out, " N5");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Tenure: %d", SP_FtTenure);
    fprintf (file_out, "\n\t Maximum number of iterations without upgrade: %d", SP_FtTSNMaxIte);

    return true;
}

bool ScdlProblem :: PrintOnFileTabooSearchSecondMethodParameters (FILE *file_out)
{
    fprintf (file_out, "Taboo Search");

    fprintf (file_out, "\n\n With the following fixed parameters:");

    fprintf (file_out, "\n\n\t Neighborhood generation method:");

    switch (SP_ScNghMethod)
    {
        case 0:
            fprintf (file_out, " N5");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Tenure: %d", SP_ScTenure);
    fprintf (file_out, "\n\t Maximum number of iterations without upgrade: %d", SP_ScTSNMaxIte);

    return true;
}

bool ScdlProblem :: PrintOnFileTabooSearchThirdMethodParameters (FILE *file_out)
{
    fprintf (file_out, "Taboo Search");

    fprintf (file_out, "\n\n With the following fixed parameters:");

    fprintf (file_out, "\n\n\t Neighborhood generation method:");

    switch (SP_ThNghMethod)
    {
        case 0:
            fprintf (file_out, " N5");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Tenure: %d", SP_ThTenure);
    fprintf (file_out, "\n\t Maximum number of iterations without upgrade: %d", SP_ThTSNMaxIte);

    return true;
}

// *****************************************************************************
// Functions to print on file the Similar Particle Collision parameters
// *****************************************************************************

bool ScdlProblem :: PrintOnFileSimilarParticleCollisionFirstMethodParameters (FILE *file_out)
{
    fprintf (file_out, "Similar Particle Collision");

    fprintf (file_out, "\n\n with the following fixed parameters:");

    fprintf (file_out, "\n\t Perturbation method:");

    switch (SP_PerturbationMethod)
    {
        case PM_M1:

            fprintf (file_out, " M1");
            break;

        default:

            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Exploitation method: ");

    switch (SP_ExploitationMethod)
    {
        case EM_TABOO_SEARCH:

            PrintOnFileTabooSearchMethodParameters (file_out);
            break;

        default:

            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\n\t Number of iterations: %d", SP_PCNMaxIte);
    return true;
}

// *****************************************************************************
// Functions to print on file the Parallel Taboo Search parameters
// *****************************************************************************

bool ScdlProblem :: PrintOnFileParallelTabooSearchFirstMethodParameters (FILE *file_out)
{
    fprintf (file_out, "Parallel Taboo Search");

    fprintf (file_out, "\n\n With the following fixed parameters:");

    fprintf (file_out, "\n\n\t Population size: %d", SP_PopulationSize);

    fprintf (file_out, "\n\t Neighborhood generation method:");

    switch (SP_FtNghMethod)
    {
        case 0:
            fprintf (file_out, " N5");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Tenure: %d", SP_FtTenure);
    fprintf (file_out, "\n\t Maximum number of iterations without upgrade: %d", SP_FtTSNMaxIte);

    return true;
}

bool ScdlProblem :: PrintOnFileParallelTabooSearchSecondMethodParameters (FILE *file_out)
{
    fprintf (file_out, "Parallel Taboo Search");

    fprintf (file_out, "\n\n With the following fixed parameters:");

    fprintf (file_out, "\n\n\t Population size: %d", SP_PopulationSize);

    fprintf (file_out, "\n\t Neighborhood generation method:");

    switch (SP_ScNghMethod)
    {
        case 0:
            fprintf (file_out, " N5");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Tenure: %d", SP_ScTenure);
    fprintf (file_out, "\n\t Maximum number of iterations without upgrade: %d", SP_ScTSNMaxIte);

    return true;
}

bool ScdlProblem :: PrintOnFileParallelTabooSearchThirdMethodParameters (FILE *file_out)
{
    fprintf (file_out, "Parallel Taboo Search");

    fprintf (file_out, "\n\n With the following fixed parameters:");

    fprintf (file_out, "\n\n\t Population size: %d", SP_PopulationSize);

    fprintf (file_out, "\n\t Neighborhood generation method:");

    switch (SP_ThNghMethod)
    {
        case 0:
            fprintf (file_out, " N5");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Tenure: %d", SP_ThTenure);
    fprintf (file_out, "\n\t Maximum number of iterations without upgrade: %d", SP_ThTSNMaxIte);

    return true;
}

// *****************************************************************************
// Functions to print on file the Multi Similar Particle Collision parameters
// *****************************************************************************

bool ScdlProblem :: PrintOnFileMultiSimilarParticleCollisionFirstMethodParameters (FILE *file_out)
{
    fprintf (file_out, "Similar Particle Collision");

    fprintf (file_out, "\n\n with the following fixed parameters:");

    fprintf (file_out, "\n\n\t Population size: %d", SP_PopulationSize);

    fprintf (file_out, "\n\t Perturbation method:");

    switch (SP_PerturbationMethod)
    {
        case PM_M1:

            fprintf (file_out, " M1");
            break;

        default:

            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Exploitation method: ");

    switch (SP_ExploitationMethod)
    {
        case EM_TABOO_SEARCH:

            PrintOnFileTabooSearchMethodParameters (file_out);
            break;

        default:

            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\n\t Number of iterations: %d", SP_PCNMaxIte);
    return true;
}

// *****************************************************************************
// Functions to print on file the Similar Particle Swarm parameters
// *****************************************************************************

bool ScdlProblem :: PrintOnFileSimilarParticleSwarmFirstMethodParameters (FILE *file_out)
{
    fprintf (file_out, "Similar Particle Swarm");

    fprintf (file_out, "\n\n with the following fixed parameters:");

    fprintf (file_out, "\n\n\t Population size: %d", SP_PopulationSize);
    fprintf (file_out, "\n\t Crossover method:");

    switch (SP_FtCrossoverMethod)
    {
        case 0:
            fprintf (file_out, " C1 with 1 floating point");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Mutation method:");

    switch (SP_FtMutationMethod)
    {
        case 0:
            fprintf (file_out, " M1");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Mutation percentage: %d", SP_FtMutationPercent);
    fprintf (file_out, "\n\t Number of iterations: %d", SP_FtSPSNMaxIte);

    return true;
}

bool ScdlProblem :: PrintOnFileSimilarParticleSwarmSecondMethodParameters (FILE *file_out)
{
    fprintf (file_out, "Similar Particle Swarm");

    fprintf (file_out, "\n\n with the following fixed parameters:");

    fprintf (file_out, "\n\n\t Population size: %d", SP_PopulationSize);
    fprintf (file_out, "\n\t Crossover method:");

    switch (SP_ScCrossoverMethod)
    {
        case 0:
            fprintf (file_out, " C1 with 1 floating point");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Mutation method:");

    switch (SP_ScMutationMethod)
    {
        case 0:
            fprintf (file_out, " M1");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Mutation percentage: %d", SP_ScMutationPercent);
    fprintf (file_out, "\n\t Number of iterations: %d", SP_ScSPSNMaxIte);

    return true;
}

bool ScdlProblem :: PrintOnFileSimilarParticleSwarmThirdMethodParameters (FILE *file_out)
{
    fprintf (file_out, "Similar Particle Swarm");

    fprintf (file_out, "\n\n with the following fixed parameters:");

    fprintf (file_out, "\n\n\t Population size: %d", SP_PopulationSize);
    fprintf (file_out, "\n\t Crossover method:");

    switch (SP_ThCrossoverMethod)
    {
        case 0:
            fprintf (file_out, " C1 with 1 floating point");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Mutation method:");

    switch (SP_ThMutationMethod)
    {
        case 0:
            fprintf (file_out, " M1");
            break;

        default:
            fprintf (file_out, " Unknow");
            break;
    }

    fprintf (file_out, "\n\t Mutation percentage: %d", SP_ThMutationPercent);
    fprintf (file_out, "\n\t Number of iterations: %d", SP_ThSPSNMaxIte);

    return true;
}

// ***** Class JS_ScdlProblem

// *****************************************************************************
// This function schedule the selected problem with a single method
// *****************************************************************************

bool JS_ScdlProblem :: Scheduler ()
{
    time_t start, end;

    switch (SP_ExecutionMode)
    {
        case OPTIMALE:

            switch (SP_Method)
            {
                case TABOO_SEARCH:

                    SP_PrevTSC = SP_SRTSC;
                    SP_PrevWPC = SP_SRWPC;
                    SP_PrevScdl = SP_SRScdl;

                    SP_NSolutionsEvaluated = 0;
                    time (&start);

                    TabooSearch ();

                    time (&end);
                    SP_CPUTime = difftime (end, start);

                    SP_CurrentTSC = SP_SRTSC;
                    SP_CurrentWPC = SP_SRWPC;
                    SP_CurrentScdl = SP_SRScdl;

                    return TRUE;

                case PARTICLE_COLLISION:

                    SP_PrevTSC = SP_SRTSC;
                    SP_PrevWPC = SP_SRWPC;
                    SP_PrevScdl = SP_SRScdl;

                    SP_PrevVecScdl = SP_VecScdl;
                    SP_PrevVecTSC = SP_VecTSC;
                    SP_PrevVecWPC = SP_VecWPC;

                    SP_SRTSC = SP_VecTSC[SP_SolutionIndex];
                    SP_SRWPC = SP_VecWPC[SP_SolutionIndex];
                    SP_SRScdl = SP_VecScdl[SP_SolutionIndex];

                    SP_NSolutionsEvaluated = 0;
                    time (&start);

                    ParticleCollision ();

                    time (&end);
                    SP_CPUTime = difftime (end, start);

                    SP_VecTSC[SP_SolutionIndex] = SP_SRTSC;
                    SP_VecWPC[SP_SolutionIndex] = SP_SRWPC;
                    SP_VecScdl[SP_SolutionIndex] = SP_SRScdl;

                    SP_CurrentVecScdl = SP_VecScdl;
                    SP_CurrentVecTSC = SP_VecTSC;
                    SP_CurrentVecWPC = SP_VecWPC;

                    SP_CurrentTSC = SP_SRTSC;
                    SP_CurrentWPC = SP_SRWPC;
                    SP_CurrentScdl = SP_SRScdl;

                    return TRUE;

                case PARALLEL_TABOO_SEARCH:

                    SP_PrevTSC = SP_SRTSC;
                    SP_PrevWPC = SP_SRWPC;
                    SP_PrevScdl = SP_SRScdl;

                    SP_PrevVecScdl = SP_VecScdl;
                    SP_PrevVecTSC = SP_VecTSC;
                    SP_PrevVecWPC = SP_VecWPC;

                    SP_NSolutionsEvaluated = 0;
                    time (&start);

                    ParallelTabooSearch ();

                    time (&end);
                    SP_CPUTime = difftime (end, start);

                    SP_CurrentVecScdl = SP_VecScdl;
                    SP_CurrentVecTSC = SP_VecTSC;
                    SP_CurrentVecWPC = SP_VecWPC;

                    SP_CurrentTSC = SP_SRTSC;
                    SP_CurrentWPC = SP_SRWPC;
                    SP_CurrentScdl = SP_SRScdl;

                    return TRUE;

                case PARALLEL_PARTICLE_COLLISION:

                    SP_PrevTSC = SP_SRTSC;
                    SP_PrevWPC = SP_SRWPC;
                    SP_PrevScdl = SP_SRScdl;

                    SP_PrevVecScdl = SP_VecScdl;
                    SP_PrevVecTSC = SP_VecTSC;
                    SP_PrevVecWPC = SP_VecWPC;

                    SP_SRTSC = SP_VecTSC[SP_SolutionIndex];
                    SP_SRWPC = SP_VecWPC[SP_SolutionIndex];
                    SP_SRScdl = SP_VecScdl[SP_SolutionIndex];

                    SP_NSolutionsEvaluated = 0;
                    time (&start);

                    ParallelParticleCollision ();

                    time (&end);
                    SP_CPUTime = difftime (end, start);

                    SP_VecTSC[SP_SolutionIndex] = SP_SRTSC;
                    SP_VecWPC[SP_SolutionIndex] = SP_SRWPC;
                    SP_VecScdl[SP_SolutionIndex] = SP_SRScdl;

                    SP_CurrentVecScdl = SP_VecScdl;
                    SP_CurrentVecTSC = SP_VecTSC;
                    SP_CurrentVecWPC = SP_VecWPC;

                    SP_CurrentTSC = SP_SRTSC;
                    SP_CurrentWPC = SP_SRWPC;
                    SP_CurrentScdl = SP_SRScdl;

                    return TRUE;

                case PARTICLE_SWARM:

                    SP_PrevTSC = SP_SRTSC;
                    SP_PrevWPC = SP_SRWPC;
                    SP_PrevScdl = SP_SRScdl;

                    SP_PrevVecScdl = SP_VecScdl;
                    SP_PrevVecTSC = SP_VecTSC;
                    SP_PrevVecWPC = SP_VecWPC;

                    SP_NSolutionsEvaluated = 0;
                    time (&start);

                    SimilarParticleSwarm ();

                    time (&end);
                    SP_CPUTime = difftime (end, start);

                    SP_CurrentVecScdl = SP_VecScdl;
                    SP_CurrentVecTSC = SP_VecTSC;
                    SP_CurrentVecWPC = SP_VecWPC;

                    SP_CurrentTSC = SP_SRTSC;
                    SP_CurrentWPC = SP_SRWPC;
                    SP_CurrentScdl = SP_SRScdl;

                    return TRUE;

                default:
                    return FALSE;
            }
            break;

        case ANALITICAL:
            break;

        case VISUAL:
            break;

        default:
            return FALSE;
    }

    return TRUE;
}

// *****************************************************************************
// This function make a sensibility analysis of the selected problem with the
// selected method and parameters
// *****************************************************************************

bool JS_ScdlProblem :: SensibilityAnalysis ()
{
    file_out = fopen("SensibilityAnalysis.txt", "w");

    fprintf (file_out, "\n Sensibility Analysis parameter: ");

    switch (SP_Sensibility_Analysis_Parameter)
    {
        case SA_NCYCLES:
            fprintf (file_out, "Hybrid Models - Number of cycles");
            break;

        case SA_TSFTM_TENURE:
            fprintf (file_out, "Taboo Search - First method - Tenure");
            break;

        case SA_TSFTM_MAXITE:
            fprintf (file_out, "Taboo Search - First method - Maximun number of iterations without upgrade");
            break;

        case SA_TSSCM_TENURE:
            fprintf (file_out, "Taboo Search - Second method - Tenure");
            break;

        case SA_TSSCM_MAXITE:
            fprintf (file_out, "Taboo Search - Second method - Maximun number of iterations without upgrade");
            break;

        case SA_PCFTM_MAXITE:
            fprintf (file_out, "Particle Collision - First method - Maximun number of iterations");
            break;

        case SA_SPSFTM_MPERC:
            fprintf (file_out, "Similar Particle Swarm - First method - Mutation percent");
            break;

        case SA_SPSSCM_MPERC:
            fprintf (file_out, "Similar Particle Swarm - Second method - Mutation percent");
            break;

        default:
            fprintf (file_out, "\n Unknow sensibility analysis parameter:");
            break;
    }

    fprintf (file_out, "\n\n Problem: %s", &SP_Name);
    fprintf (file_out, "\n\n Method : ");

    switch (SP_MethodMode)
    {
        case SINGLE:

            fprintf (file_out, "Single ");

            switch (SP_Method)
            {
                case TABOO_SEARCH:

                    PrintOnFileTabooSearchFirstMethodParameters (file_out);
                    break;

                case PARTICLE_COLLISION:

                    PrintOnFileSimilarParticleCollisionFirstMethodParameters (file_out);
                    break;

                case PARALLEL_TABOO_SEARCH:

                    PrintOnFileParallelTabooSearchFirstMethodParameters (file_out);
                    break;

                case PARALLEL_PARTICLE_COLLISION:

                    PrintOnFileMultiSimilarParticleCollisionFirstMethodParameters (file_out);
                    break;

                case PARTICLE_SWARM:

                    PrintOnFileSimilarParticleSwarmFirstMethodParameters (file_out);
                    break;

                default:
                    fprintf (file_out, "Unknow method");
                    break;
            }

            break;

        case HYBRID:

            switch (SP_HybridModel)
            {
                case HYBRID_SUCCESSIVE_APPLICATION:
                    fprintf (file_out, "Hybrid Successive Application");
                    break;

                case HYBRID_NEIGHBORHOOD:
                    fprintf (file_out, "Hybrid Neighborhood");
                    break;

                case HYBRID_IMPROVED_NEIGHBORHOOD:
                    fprintf (file_out, "Hybrid Improved Neighborhood");
                    break;

                default:
                    fprintf (file_out, "Unknow hybrid model");
                    break;
            }

            fprintf (file_out, " (%d cycles)", SP_NCycles);

            switch (SP_FtMethod)
            {
                case TABOO_SEARCH:

                    fprintf (file_out, "\n\n\n First operator: ");
                    PrintOnFileTabooSearchFirstMethodParameters (file_out);
                    break;

                case PARTICLE_COLLISION:

                    fprintf (file_out, "\n\n\n First operator: ");
                    PrintOnFileSimilarParticleCollisionFirstMethodParameters (file_out);
                    break;

                case PARALLEL_TABOO_SEARCH:

                    fprintf (file_out, "\n\n\n First operator: ");
                    PrintOnFileParallelTabooSearchFirstMethodParameters (file_out);
                    break;

                case PARALLEL_PARTICLE_COLLISION:

                    fprintf (file_out, "\n\n\n First operator: ");
                    PrintOnFileMultiSimilarParticleCollisionFirstMethodParameters (file_out);
                    break;

                case PARTICLE_SWARM:

                    fprintf (file_out, "\n\n\n First operator: ");
                    PrintOnFileSimilarParticleSwarmFirstMethodParameters (file_out);
                    break;

                default:
                    fprintf (file_out, "\n\n\n Unknow operator");
                    break;
            }

            switch (SP_ScMethod)
            {
                case TABOO_SEARCH:

                    fprintf (file_out, "\n\n\n Second operator: ");
                    PrintOnFileTabooSearchSecondMethodParameters (file_out);
                    break;

                case PARTICLE_COLLISION:
                    MessageBox (NULL, "Sorry, Similar Particle Collision can't be defined as second method !!!", "ERROR",
                    MB_ICONERROR|MB_OK);
                    break;

                case PARALLEL_TABOO_SEARCH:

                    fprintf (file_out, "\n\n\n Second operator: ");
                    PrintOnFileParallelTabooSearchSecondMethodParameters (file_out);
                    break;

                case PARALLEL_PARTICLE_COLLISION:
                    MessageBox (NULL, "Sorry, Paralles Similar Particle Collision can't be defined as second method !!!", "ERROR",
                    MB_ICONERROR|MB_OK);
                    break;

                case PARTICLE_SWARM:

                    fprintf (file_out, "\n\n\n Second operator: ");
                    PrintOnFileSimilarParticleSwarmSecondMethodParameters (file_out);
                    break;

                case NO_METHOD:
                    break;

                default:
                    fprintf (file_out, "\n\n\n Unknow operator");
                    break;
            }

            switch (SP_ThMethod)
            {
                case TABOO_SEARCH:

                    fprintf (file_out, "\n\n\n Third operator: ");
                    PrintOnFileTabooSearchThirdMethodParameters (file_out);
                    break;

                case PARTICLE_COLLISION:
                    MessageBox (NULL, "Sorry, Similar Particle Collision can't be defined as third method !!!", "ERROR",
                    MB_ICONERROR|MB_OK);
                    break;

                case PARALLEL_TABOO_SEARCH:

                    fprintf (file_out, "\n\n\n Third operator: ");
                    PrintOnFileParallelTabooSearchThirdMethodParameters (file_out);
                    break;

                case PARALLEL_PARTICLE_COLLISION:
                    MessageBox (NULL, "Sorry, Multi Similar Particle Collision can't be defined as third method !!!", "ERROR",
                    MB_ICONERROR|MB_OK);
                    break;

                case PARTICLE_SWARM:

                    fprintf (file_out, "\n\n\n Third operator: ");
                    PrintOnFileSimilarParticleSwarmThirdMethodParameters (file_out);
                    break;

                case NO_METHOD:
                    break;

                default:
                    fprintf (file_out, "\n\n\n Unknow operator");
                    break;
            }

            break;

        default:
            fprintf (file_out, "Unknow method mode");
            break;
    }

    fprintf (file_out, "\n\n\n Results:\n\n");

    switch (SP_Sensibility_Analysis_Increase_Mode)
    {
        case SUM:

            for (UINT i=SP_Sensibility_Analysis_Initial_Value; i <= SP_Sensibility_Analysis_Final_Value;
            i = i+SP_Sensibility_Analysis_Increase_Value)
            {
                switch (SP_Sensibility_Analysis_Parameter)
                {
                    case SA_NCYCLES:

                        SP_NCycles = i;

                        break;

                    case SA_TSFTM_TENURE:

                        SP_Tenure = i;
                        SP_FtTenure = i;

                        break;

                    case SA_TSFTM_MAXITE:

                        SP_TSNMaxIte = i;
                        SP_FtTSNMaxIte = i;

                        break;

                    case SA_TSSCM_TENURE:

                        SP_ScTenure = i;

                        break;

                    case SA_TSSCM_MAXITE:

                        SP_ScTSNMaxIte = i;

                        break;

                    case SA_PCFTM_MAXITE:

                        SP_PCNMaxIte = i;

                        break;

                    case SA_SPSFTM_MPERC:

                        SP_MutationPercent = i;
                        SP_FtMutationPercent = i;

                        break;

                    case SA_SPSSCM_MPERC:

                        SP_ScMutationPercent = i;

                        break;

                    default:

                        MessageBox (NULL, "The program desn't know the specified Sensibility Analysis Parameter", "Error",
                        MB_OK | MB_ICONINFORMATION);

                        return FALSE;
                }

                for (UINT j=0; j<SP_Sensibility_Analysis_Repetitions; j++)
                {
                    switch (SP_MethodMode)
                    {
                        case SINGLE:

                            Scheduler ();
                            break;

                        case HYBRID:

                            HybridScheduler ();
                            break;

                        default:
                            MessageBox (NULL, "The program doesn't know the specified Method Mode", "Error", MB_OK | MB_ICONINFORMATION);
                            return FALSE;
                    }

                    printf ("\n%d", i);

                    fprintf (file_out, " %10.0d %10.0f %15.0d %10.0f\n", i, SP_Makespan, SP_NSolutionsEvaluated, SP_CPUTime);

                    switch (SP_Sensibility_Analysis_Print_Parameter)
                    {
                        case PRINT_ALL:

                            for (UINT k=0; k<SP_VecScdl.size(); k++)
                            {
                                SP_SRScdl = SP_VecScdl[k];
                                TimingScdlSR ();

                                fprintf (file_out, "\n %10.0d %10.0f", k+1, SP_Makespan);
                            }

                            fprintf (file_out, "\n\n");

                            break;

                        case PRINT_BEST:
                            break;

                        default:

                            MessageBox (NULL, "The program desn't know the specified Sensibility Analysis Print Parameter", "Error",
                            MB_OK | MB_ICONINFORMATION);

                            break;
                    }


                    SP_InitialSolutionVecMethod = PREVIOUS_SOLUTION_VECTOR;
                    InitialSolutionVector ();
                }
            }

            break;

        case MULTIPLICATION:

            for (UINT i=SP_Sensibility_Analysis_Initial_Value; i <= SP_Sensibility_Analysis_Final_Value;
            i = i*SP_Sensibility_Analysis_Increase_Value)
            {
                printf ("\n%d", i);

                switch (SP_Sensibility_Analysis_Parameter)
                {
                    case SA_NCYCLES:

                        SP_NCycles = i;

                        break;

                    case SA_TSFTM_TENURE:

                        SP_Tenure = i;
                        SP_FtTenure = i;

                        break;

                    case SA_TSFTM_MAXITE:

                        SP_TSNMaxIte = i;
                        SP_FtTSNMaxIte = i;

                        break;

                    case SA_TSSCM_TENURE:

                        SP_ScTenure = i;

                        break;

                    case SA_TSSCM_MAXITE:

                        SP_ScTSNMaxIte = i;

                        break;

                    case SA_PCFTM_MAXITE:

                        SP_PCNMaxIte = i;

                        break;

                    case SA_SPSFTM_MPERC:

                        SP_MutationPercent = i;
                        SP_FtMutationPercent = i;

                        break;

                    case SA_SPSSCM_MPERC:

                        SP_ScMutationPercent = i;

                        break;

                    default:

                        MessageBox (NULL, "The program desn't know the specified Sensibility Analysis Parameter", "Error",
                        MB_OK | MB_ICONINFORMATION);

                        return FALSE;
                }

                for (UINT j=0; j<SP_Sensibility_Analysis_Repetitions; j++)
                {
                    switch (SP_MethodMode)
                    {
                        case SINGLE:

                            Scheduler ();
                            break;

                        case HYBRID:

                            HybridScheduler ();
                            break;

                        default:
                            MessageBox (NULL, "The program doesn't know the specified Method Mode", "Error", MB_OK | MB_ICONINFORMATION);
                            return FALSE;
                    }

                    printf ("\n%d", i);

                    fprintf (file_out, "\n %10.0d %10.0f %15.0d %10.0f\n", i, SP_Makespan, SP_NSolutionsEvaluated, SP_CPUTime);

                    switch (SP_Sensibility_Analysis_Print_Parameter)
                    {
                        case PRINT_ALL:

                            for (UINT k=0; k<SP_VecScdl.size(); k++)
                            {
                                SP_SRScdl = SP_VecScdl[k];
                                TimingScdlSR ();

                                fprintf (file_out, "\n %10.0d %10.0f", k+1, SP_Makespan);
                            }

                            fprintf (file_out, "\n");

                            break;

                        case PRINT_BEST:
                            break;

                        default:

                            MessageBox (NULL, "The program desn't know the specified Sensibility Analysis Print Parameter", "Error",
                            MB_OK | MB_ICONINFORMATION);

                            break;
                    }


                    SP_InitialSolutionVecMethod = PREVIOUS_SOLUTION_VECTOR;
                    InitialSolutionVector ();
                }
            }

            break;

        case EXPONENT:

            for (UINT i=SP_Sensibility_Analysis_Initial_Value; i <= SP_Sensibility_Analysis_Final_Value;
            i = (UINT) pow (i, SP_Sensibility_Analysis_Increase_Value))
            {
                printf ("\n%d", i);

                switch (SP_Sensibility_Analysis_Parameter)
                {
                    case SA_NCYCLES:

                        SP_NCycles = i;

                        break;

                    case SA_TSFTM_TENURE:

                        SP_Tenure = i;
                        SP_FtTenure = i;

                        break;

                    case SA_TSFTM_MAXITE:

                        SP_TSNMaxIte = i;
                        SP_FtTSNMaxIte = i;

                        break;

                    case SA_TSSCM_TENURE:

                        SP_ScTenure = i;

                        break;

                    case SA_TSSCM_MAXITE:

                        SP_ScTSNMaxIte = i;

                        break;

                    case SA_PCFTM_MAXITE:

                        SP_PCNMaxIte = i;

                        break;

                    case SA_SPSFTM_MPERC:

                        SP_MutationPercent = i;
                        SP_FtMutationPercent = i;

                        break;

                    case SA_SPSSCM_MPERC:

                        SP_ScMutationPercent = i;

                        break;

                    default:

                        MessageBox (NULL, "The program desn't know the specified Sensibility Analysis Parameter", "Error",
                        MB_OK | MB_ICONINFORMATION);

                        return FALSE;
                }

                for (UINT j=0; j<SP_Sensibility_Analysis_Repetitions; j++)
                {
                    switch (SP_MethodMode)
                    {
                        case SINGLE:

                            Scheduler ();
                            break;

                        case HYBRID:

                            HybridScheduler ();
                            break;

                        default:
                            MessageBox (NULL, "The program doesn't know the specified Method Mode", "Error", MB_OK | MB_ICONINFORMATION);
                            return FALSE;
                    }

                    printf ("\n%d", i);

                    fprintf (file_out, "\n %10.0d %10.0f %15.0d %10.0f\n", i, SP_Makespan, SP_NSolutionsEvaluated, SP_CPUTime);

                    switch (SP_Sensibility_Analysis_Print_Parameter)
                    {
                        case PRINT_ALL:

                            for (UINT k=0; k<SP_VecScdl.size(); k++)
                            {
                                SP_SRScdl = SP_VecScdl[k];
                                TimingScdlSR ();

                                fprintf (file_out, "\n %10.0d %10.0f", k+1, SP_Makespan);
                            }

                            fprintf (file_out, "\n");
                            break;

                        case PRINT_BEST:
                            break;

                        default:

                            MessageBox (NULL, "The program desn't know the specified Sensibility Analysis Print Parameter", "Error",
                            MB_OK | MB_ICONINFORMATION);

                            break;
                    }


                    SP_InitialSolutionVecMethod = PREVIOUS_SOLUTION_VECTOR;
                    InitialSolutionVector ();
                }
            }

            break;

        default:

            MessageBox (NULL, "The program desn't know the specified Sensibility Analysis Increase Mode", "Error",
            MB_OK | MB_ICONINFORMATION);

            return FALSE;
    }

    fclose(file_out);

    printf ("\n\n Sensitivity Analysis finished");

    return TRUE;
}


bool JS_ScdlProblem :: PrintOnScreenSlotOfTime ()
{
    printf ("\n\n Time: \n");

    for (int i=0; i<SP_NTTask; i++)
    {
        printf ("\n %10.0d %10.0f %10.0f", i+1, SP_StartTimeOfTask[i], SP_FinalTimeOfTask[i]);
    }

    return true;
}
