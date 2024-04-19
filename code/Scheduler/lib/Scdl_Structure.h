#include <windows.h>
#include <math.h>
#include <float.h>
#include "Resource.h"

#include <vector>
using namespace std;

typedef vector <bool> VecBool;
typedef vector <UINT> VecUInt;
typedef vector <VecUInt> MatUInt;
typedef vector <int> VecInt;
typedef vector <VecInt> MatInt;
typedef vector <MatInt> TriInt;
typedef vector <float> VecFloat;
typedef vector <VecFloat> MatFloat;
typedef vector <LPSTR> VecLPSTR;
typedef vector <COLORREF> VecCOLOR;


#ifndef _SCHEDULER_IDENTIFIERS_
#define _SCHEDULER_IDENTIFIERS_

// Problem kinds

#define FLOW_SHOP   0
#define JOB_SHOP    1

// Benchmark classes

#define ABZ         0
#define FT          1

// Execution modes

#define OPTIMALE      0
#define ANALITICAL    1
#define VISUAL        2

// Method modes

#define SINGLE      0
#define HYBRID      1

// Hybrid models

#define HYBRID_SUCCESSIVE_APPLICATION      0
#define HYBRID_NEIGHBORHOOD                1
#define HYBRID_IMPROVED_NEIGHBORHOOD       2

// Methods

#define TABOO_SEARCH                    0
#define PARTICLE_COLLISION              1
#define PARALLEL_TABOO_SEARCH           2
#define PARALLEL_PARTICLE_COLLISION     3
#define PARTICLE_SWARM                  4
#define NO_METHOD                       5

// Sensibility Analysis

#define SUM                     0
#define MULTIPLICATION          1
#define EXPONENT                2

// Print parameters of Sensibility Analysis

#define PRINT_ALL               0
#define PRINT_BEST              1

// Sensibility Analysis Parameters

#define SA_NCYCLES              0
#define SA_TSFTM_TENURE         1
#define SA_TSFTM_MAXITE         2
#define SA_TSSCM_TENURE         3
#define SA_TSSCM_MAXITE         4
#define SA_PCFTM_MAXITE         5
#define SA_SPSFTM_MPERC         6
#define SA_SPSSCM_MPERC         7

// Convergence Analysis Parameters

#define CA_NONE                 1
#define CA_BY_CYCLE             2
#define CA_BY_ITERATION         3

// Convergence Analysis Parameters

#define EC_NO_EXTRA_CRITERION   1
#define EC_BEST_MAKESPAN_FOUND  2

// Initial solutions

#define PREVIOUS_SOLUTION           0
#define CURRENT_SOLUTION            1
#define SIMPLE_ORDERLY              2
#define RANDOM_INITIAL_SOLUTION     3

// Vectors of initial solutions

#define PREVIOUS_SOLUTION_VECTOR        0
#define CURRENT_SOLUTION_VECTOR         1
#define RANDOM_INITIAL_SOLUTION_VECTOR  2

// Critical path operators

#define N5      0

// Crossover operators

#define RANDOM_C1   0

// Mutation operators

#define M1  0

// Perturbation methods

#define PM_M1     0

// Exploitation methods

#define EM_TABOO_SEARCH     0

#endif // _SCHEDULER_IDENTIFIERS_

#ifndef SCDL_STRUCTURE_H_INCLUDED
#define SCDL_STRUCTURE_H_INCLUDED

class ScdlProblem;
typedef vector <ScdlProblem> VecScdlProblem;

class JS_ScdlProblem;
typedef vector <JS_ScdlProblem> VecJS_ScdlProblem;

#ifndef _SCDL_PROBLEM_
#define _SCDL_PROBLEM_

VecLPSTR ProblemKindList ();
VecLPSTR MethodModeList ();
VecLPSTR HybridModelList ();
VecLPSTR MethodList ();
VecLPSTR CP_OperatorList ();
VecLPSTR InitialSolutionList ();
VecLPSTR InitialSolutionVectorList ();
VecLPSTR CrossoverMethodList ();
VecLPSTR MutationMethodList ();
VecLPSTR PerturbationMethodList ();
VecLPSTR ExploitationMethodList ();

class ScdlProblem
{
    protected:

    FILE *file_out;

    // Problem variables

    char *SP_Name;
    char *SP_PathName;

    UINT SP_Class;
    UINT SP_Kind;
    UINT SP_NJob;
    UINT SP_NMcn;

    float SP_Best_Makespan_Known;

    int SP_NTTask;

    VecInt SP_NTaskJob;
    VecInt SP_NTaskMcn;
    VecInt SP_JobOfTask;
    VecInt SP_McnOfTask;
    VecInt SP_FirstTaskOfJob;
    VecInt SP_LastTaskOfJob;
    VecInt SP_PrevTaskOnJob;

    VecFloat SP_TimeOfTask;

    // Method variables

    int SP_ExecutionMode;
    int SP_MethodMode;
    int SP_HybridModel;

    UINT SP_Method;
    UINT SP_FtMethod;
    UINT SP_ScMethod;
    UINT SP_ThMethod;

    int SP_InitialSolutionMethod;
    int SP_InitialSolutionVecMethod;

    UINT SP_NCycles;

    // Sensibility Analysis variables

    UINT SP_Sensibility_Analysis_Initial_Value,
         SP_Sensibility_Analysis_Final_Value,
         SP_Sensibility_Analysis_Increase_Value,
         SP_Sensibility_Analysis_Increase_Mode,
         SP_Sensibility_Analysis_Repetitions,
         SP_Sensibility_Analysis_Parameter;

    UINT SP_Sensibility_Analysis_Print_Parameter;
    UINT SP_Convergence_Analysis_Mode;
    UINT SP_Extra_Criterion_Mode;

    // Solution and solution representation variables

    UINT SP_SolutionIndex;

    int SP_NSolutionsEvaluated;

    float SP_Makespan,
          SP_BestMakespan,
          SP_CPUTime;

    VecInt SP_SRTSC;
    VecUInt SP_SRWPC;
    MatInt SP_SRScdl;

    VecInt SP_PrevTSC;
    VecUInt SP_PrevWPC;
    MatInt SP_PrevScdl;

    VecInt SP_CurrentTSC;
    VecUInt SP_CurrentWPC;
    MatInt SP_CurrentScdl;

    VecInt SP_BestTSC;
    VecUInt SP_BestWPC;
    MatInt SP_BestScdl;

    MatInt SP_VecTSC;
    MatUInt SP_VecWPC;
    TriInt SP_VecScdl;

    MatInt SP_PrevVecTSC;
    MatUInt SP_PrevVecWPC;
    TriInt SP_PrevVecScdl;

    MatInt SP_CurrentVecTSC;
    MatUInt SP_CurrentVecWPC;
    TriInt SP_CurrentVecScdl;

    VecInt SP_PrevTaskOnMcn;
    VecInt SP_LastTaskOfScdl;
    VecFloat SP_StartTimeOfTask;
    VecFloat SP_FinalTimeOfTask;

    // CriticalPath operators variables

    int SP_CriticalPathIndex;

    MatInt SP_CriticalPath;
    MatInt SP_BlocksOnCriticalPath;

    bool N5_TaskList (VecInt &A, VecInt &B);

    // Taboo Search variables

    UINT SP_NghMethod;
    UINT SP_Tenure;
    UINT SP_TSNMaxIte;

    UINT SP_FtNghMethod;
    UINT SP_FtTenure;
    UINT SP_FtTSNMaxIte;

    UINT SP_ScNghMethod;
    UINT SP_ScTenure;
    UINT SP_ScTSNMaxIte;

    UINT SP_ThNghMethod;
    UINT SP_ThTenure;
    UINT SP_ThTSNMaxIte;

    TriInt SP_Neighborhood;

    bool PrintOnFileTabooSearchMethodParameters (FILE *file_out);
    bool PrintOnFileTabooSearchFirstMethodParameters (FILE *file_out);
    bool PrintOnFileTabooSearchSecondMethodParameters (FILE *file_out);
    bool PrintOnFileTabooSearchThirdMethodParameters (FILE *file_out);

    bool PrintOnFileParallelTabooSearchFirstMethodParameters (FILE *file_out);
    bool PrintOnFileParallelTabooSearchSecondMethodParameters (FILE *file_out);
    bool PrintOnFileParallelTabooSearchThirdMethodParameters (FILE *file_out);

    // Particle Collision variables

    UINT SP_PerturbationMethod;
    UINT SP_ExploitationMethod;
    UINT SP_PCNMaxIte;

    bool PrintOnFileSimilarParticleCollisionFirstMethodParameters (FILE *file_out);
    bool PrintOnFileSimilarParticleCollisionSecondMethodParameters (FILE *file_out);
    bool PrintOnFileSimilarParticleCollisionThirdMethodParameters (FILE *file_out);

    bool PrintOnFileMultiSimilarParticleCollisionFirstMethodParameters (FILE *file_out);
    bool PrintOnFileMultiSimilarParticleCollisionSecondMethodParameters (FILE *file_out);
    bool PrintOnFileMultiSimilarParticleCollisionThirdMethodParameters (FILE *file_out);

    // Particle Swarm variables

    UINT SP_PopulationSize;
    UINT SP_CrossoverMethod;
    UINT SP_MutationMethod;
    UINT SP_MutationPercent;
    UINT SP_SPSNMaxIte;

    UINT SP_FtCrossoverMethod;
    UINT SP_FtMutationMethod;
    UINT SP_FtMutationPercent;
    UINT SP_FtSPSNMaxIte;

    UINT SP_ScCrossoverMethod;
    UINT SP_ScMutationMethod;
    UINT SP_ScMutationPercent;
    UINT SP_ScSPSNMaxIte;

    UINT SP_ThCrossoverMethod;
    UINT SP_ThMutationMethod;
    UINT SP_ThMutationPercent;
    UINT SP_ThSPSNMaxIte;

    bool PrintOnFileSimilarParticleSwarmFirstMethodParameters (FILE *file_out);
    bool PrintOnFileSimilarParticleSwarmSecondMethodParameters (FILE *file_out);
    bool PrintOnFileSimilarParticleSwarmThirdMethodParameters (FILE *file_out);

    public:

    ScdlProblem ();
    ~ScdlProblem ();

    // ProbleDef.cpp

    char* Name ();
    char* PathName ();

    UINT Class ();
    UINT Kind ();
    UINT NJob ();
    UINT NMcn ();

    void Class (const UINT &Class);
    void Kind (const UINT &Kind);

    float Best_Makespan_Known ();

    VecScdlProblem ScdlProblemList ();

    // MethodDef.cpp

    void MethodMode (const int &MethodMode);
    void HybridModel (const int &HybridModel);
    void NCycles (const UINT &Ncycles);

    void Method (const UINT &Method);
    void FtMethod (const UINT &Method);
    void ScMethod (const UINT &Method);
    void ThMethod (const UINT &Method);

    void Sensibility_Analysis_Initial_Value (const UINT &SA_Initial_Value);
    void Sensibility_Analysis_Final_Value (const UINT &SA_Final_Value);
    void Sensibility_Analysis_Increase_Value (const UINT &SA_Increase_Value);
    void Sensibility_Analysis_Increase_Mode (const UINT &SA_Increase_Mode);
    void Sensibility_Analysis_Repetitions (const UINT &SA_Repetitions);
    void Sensibility_Analysis_Parameter (const UINT &SA_Parameter);
    void Sensibility_Analysis_Print_Parameter (const UINT &SA_Print_Parameter);
    void Sensibility_Analysis_Convergence_Mode (const UINT &SA_Convergence_Mode);
    void Sensibility_Analysis_Extra_Criterion_Mode (const UINT &SA_Extra_Criterion_Mode);

    int MethodMode ();

    UINT NCycles ();

    UINT Method ();
    UINT FtMethod ();
    UINT ScMethod ();
    UINT ThMethod ();

    UINT Sensibility_Analysis_Initial_Value ();
    UINT Sensibility_Analysis_Final_Value ();
    UINT Sensibility_Analysis_Increase_Value ();
    UINT Sensibility_Analysis_Increase_Mode ();
    UINT Sensibility_Analysis_Repetitions ();
    UINT Sensibility_Analysis_Parameter ();
    UINT Sensibility_Analysis_Print_Parameter ();
    UINT Sensibility_Analysis_Convergence_Mode ();
    UINT Sensibility_Analysis_Extra_Criterion_Mode ();


    // ContructiveHeuristic.cpp

    void SolutionIndex (const UINT &Index);

    void InitialSolutionMethod (const int &Method);
    void InitialSolutionVecMethod (const int &Method);

    void TSC (const VecInt &TSC);
    void WPC (const VecUInt &WPC);
    void Scdl (const MatInt &Scdl);

    void PrevTSC (const VecInt &TSC);
    void PrevWPC (const VecUInt &WPC);
    void PrevScdl (const MatInt &Scdl);

    void CurrentTSC (const VecInt &TSC);
    void CurrentWPC (const VecUInt &WPC);
    void CurrentScdl (const MatInt &Scdl);

    void PrevVecTSC (const MatInt &VecTSC);
    void PrevVecWPC (const MatUInt &VecWPC);
    void PrevVecScdl (const TriInt &VecScdl);

    void CurrentVecTSC (const MatInt &VecTSC);
    void CurrentVecWPC (const MatUInt &VecWPC);
    void CurrentVecScdl (const TriInt &VecScdl);

    UINT SolutionIndex ();

    int InitialSolutionMethod ();
    int InitialSolutionVecMethod ();

    int NSolutionsEvaluated ();
    float Makespan ();
    float CPUTime ();

    VecInt TSC ();
    VecUInt WPC ();
    MatInt Scdl ();

    MatInt VecTSC ();
    MatUInt VecWPC ();
    TriInt VecScdl ();

    // TabooSearch.cpp

    UINT NghMethod ();
    UINT Tenure ();
    UINT TSNMaxIte ();

    UINT FtNghMethod ();
    UINT FtTenure ();
    UINT FtTSNMaxIte ();

    UINT ScNghMethod ();
    UINT ScTenure ();
    UINT ScTSNMaxIte ();

    UINT ThNghMethod ();
    UINT ThTenure ();
    UINT ThTSNMaxIte ();

    MatInt CriticalPath ();

    void CriticalPathIndex (const int &CriticalPathIndex);

    void Tenure (const UINT &Tenure);
    void TSNMaxIte (const UINT &NMaxIte);

    void FtTenure (const UINT &Tenure);
    void FtTSNMaxIte (const UINT &NMaxIte);

    void ScTenure (const UINT &Tenure);
    void ScTSNMaxIte (const UINT &NMaxIte);

    void ThTenure (const UINT &Tenure);
    void ThTSNMaxIte (const UINT &NMaxIte);

    // SimilarParticleSwarm.cpp

    UINT PopulationSize ();
    UINT CrossoverMethod ();
    UINT MutationMethod ();
    UINT MutationPercent ();
    UINT SPSNMaxIte ();

    UINT FtCrossoverMethod ();
    UINT FtMutationMethod ();
    UINT FtMutationPercent ();
    UINT FtSPSNMaxIte ();

    UINT ScCrossoverMethod ();
    UINT ScMutationMethod ();
    UINT ScMutationPercent ();
    UINT ScSPSNMaxIte ();

    UINT ThCrossoverMethod ();
    UINT ThMutationMethod ();
    UINT ThMutationPercent ();
    UINT ThSPSNMaxIte ();

    void PopulationSize (const UINT PopolationSize);
    void CrossoverMethod (const UINT CrossoverMethod);
    void MutationMethod (const UINT MutationMethod);
    void MutationPercent (const UINT MutationPercent);
    void SPSNMaxIte (const UINT &NMaxIte);

    void FtCrossoverMethod (const UINT CrossoverMethod);
    void FtMutationMethod (const UINT MutationMethod);
    void FtMutationPercent (const UINT MutationPercent);
    void FtSPSNMaxIte (const UINT &NMaxIte);

    void ScCrossoverMethod (const UINT CrossoverMethod);
    void ScMutationMethod (const UINT MutationMethod);
    void ScMutationPercent (const UINT MutationPercent);
    void ScSPSNMaxIte (const UINT &NMaxIte);

    void ThCrossoverMethod (const UINT CrossoverMethod);
    void ThMutationMethod (const UINT MutationMethod);
    void ThMutationPercent (const UINT MutationPercent);
    void ThSPSNMaxIte (const UINT &NMaxIte);

    // Particle_Collision.cpp

    UINT PerturbationMethod ();
    UINT ExploitationMethod ();
    UINT PCNMaxIte ();

    void PerturbationMethod (const UINT &PMethod);
    void ExploitationMethod (const UINT &EMethod);
    void PCNMaxIte (const UINT &NMaxIte);
};

#ifndef _JS_SCDL_PROBLEM_
#define _JS_SCDL_PROBLEM_

class JS_ScdlProblem : public ScdlProblem
{
    public:

    JS_ScdlProblem ();
    ~JS_ScdlProblem ();

    // ProblemDef.cpp

    VecLPSTR BenchmarkClassList ();
    VecJS_ScdlProblem JS_ScdlProblemList ();
    VecJS_ScdlProblem JS_ABZList ();
    VecJS_ScdlProblem JS_FTList ();

    bool GetProblem (char *path_name);

    // ConstructiveHeuristic.cpp --> The following functions generate initial solutions

    bool InitialSolution ();
    bool SimpleOrderly ();
    bool RandomInitialSolution ();

    bool InitialSolutionVector ();
    bool RandomInitialSolutionVector ();

    bool TimingScdlSR (VecInt &TSC);
    bool TimingScdlSR ();
    bool Timing_WPC ();
    bool Timing_TSC ();
    bool AdjustMPrevOnScdlSR ();
    bool WPC_by_TSC ();
    bool TSC_by_WPC ();
    bool Scdl_by_TSC ();

    bool PrintOnScreenCurrentSolutionSpecification ();
    bool PrintOnScreenSlotOfTime ();

    // CriticalPath_Operators.cpp --> The following functions generate a neighborhood based on changes
    // of the position of the operations on critical paths.

    TriInt Neighborhood ();

    bool FindCriticalPath ();
    bool BlocksOnCriticalPath ();

    bool N5_TaskList (VecInt &A, VecInt &B);
    bool N5_Ngh (VecInt &A, VecInt &B);

    bool Swap (const int &a, const int &b);

    // Crossover_Operators.cpp --> The following functions generate a neighborhood by crossover
    // operations.

    bool Crossover (const VecUInt &WPC_1, const VecUInt &WPC_2);
    bool RandomC1 (const VecUInt &WPC_1, const VecUInt &WPC_2);

    // Mutation_Operators.cpp --> The following functions generate a neigborhood by crossover
    // operations

    bool Mutation (const VecUInt WPC);
    bool M1_Operator (const VecUInt WPC);

    // MethodDef.cpp --> The following function schedule the selected problem by a selected function

    bool Scheduler ();
    bool HybridScheduler ();
    bool SensibilityAnalysis ();

    // TabooSearch.cpp --> The following function schedule the selected problem by Taboo Search method

    bool TabooSearch ();
    bool ParallelTabooSearch ();
    bool PrintOnScreenTabooSearchParameters ();

    // ParticleSwarm.cpp --> The following function schedule the selected problem by Similar Particle Swarm method

    bool SimilarParticleSwarm ();

    // Hybrid_Models.cpp

    bool HybridSuccessiveApplication ();
    bool HybridNeighborhood ();
    bool HybridImprovedNeighborhood ();

    // Particle_Collision.cpp

    bool Perturbation ();
    bool Exploitation ();
    bool Scattering (const float &ScatteringPercent);

    bool ParticleCollision ();
    bool ParallelParticleCollision ();

    // Gantt.cpp --> The following function print the Gantt graphics of a given solution or a vector of solutions

    bool PrintGanttSolution (HWND hWnd, const int &xi, const int &yi, const int &width, const int &height);
    bool PrintCriticalPath (HWND hWnd, const int &Xi, const int &Yi, const int &Width, const int &Height);
    bool PrintBlocksOnCriticalPath (HWND hWnd, const int &Xi, const int &Yi, const int &Width, const int &Height);
    bool PrintContourTask (HWND hWnd, const int &Xi, const int &Yi, const int &Width, const int &Height, const int &Task);

    bool PrintGanttNeighborhood (HWND hWnd, const int &xi, const int &yi, const int &width, const int &height);
    bool PrintGanttN5 (HWND hWnd, const int &xi, const int &yi, const int &width, const int &height);
};

#endif // _JS_SCDL_PROBLEM

#endif // _SCDL_PROBLEM_

#endif // SCDL_STRUCTURE_H_INCLUDED
