#include "Scdl_Structure.h"
#include <float.h>

// *****************************************************************************
// Generate a list with the initial solution generating methods
// *****************************************************************************

VecLPSTR InitialSolutionList ()
{
    LPSTR InitSolution;
    VecLPSTR ISList;

    InitSolution = "Previous initial solution";
    ISList.push_back (InitSolution);

    InitSolution = "Current initial solution";
    ISList.push_back (InitSolution);

    InitSolution = "Initial solution by Simple Orderly method";
    ISList.push_back (InitSolution);

    InitSolution = "Initial solution randomly generated";
    ISList.push_back (InitSolution);

    return ISList;
}

VecLPSTR InitialSolutionVectorList ()
{
    LPSTR InitSolutionVec;
    VecLPSTR ISVecList;

    InitSolutionVec = "Previous vector of initial solutions";
    ISVecList.push_back (InitSolutionVec);

    InitSolutionVec = "Current vector of initial solutions";
    ISVecList.push_back (InitSolutionVec);

    InitSolutionVec = "Vector of initial solutions randomly generated";
    ISVecList.push_back (InitSolutionVec);

    return ISVecList;
}

// ***** Class ScdlProblem

// *****************************************************************************
// Functions to set the value of the protected variables
// *****************************************************************************

void ScdlProblem :: InitialSolutionMethod (const int &Method)
{
    SP_InitialSolutionMethod = Method;
}

void ScdlProblem :: InitialSolutionVecMethod (const int &Method)
{
    SP_InitialSolutionVecMethod = Method;
}

void ScdlProblem :: SolutionIndex (const UINT &Index)
{
    SP_SolutionIndex = Index;
}


void ScdlProblem :: TSC (const VecInt &TSC)
{
    SP_SRTSC.clear();
    SP_SRTSC = TSC;
}

void ScdlProblem :: WPC (const VecUInt &WPC)
{
    SP_SRWPC.clear();
    SP_SRWPC = WPC;
}

void ScdlProblem :: Scdl (const MatInt &Scdl)
{
    SP_SRScdl.clear();
    SP_SRScdl = Scdl;
}

void ScdlProblem :: PrevTSC (const VecInt &TSC)
{
    SP_PrevTSC.clear ();
    SP_PrevTSC = TSC;
}

void ScdlProblem :: PrevWPC (const VecUInt &WPC)
{
    SP_PrevWPC.clear ();
    SP_PrevWPC = WPC;
}

void ScdlProblem :: PrevScdl (const MatInt &Scdl)
{
    SP_PrevScdl.clear ();
    SP_PrevScdl = Scdl;
}

void ScdlProblem :: CurrentTSC (const VecInt &TSC)
{
    SP_CurrentTSC.clear ();
    SP_CurrentTSC = TSC;
}

void ScdlProblem :: CurrentWPC (const VecUInt &WPC)
{
    SP_CurrentWPC.clear ();
    SP_CurrentWPC = WPC;
}

void ScdlProblem :: CurrentScdl (const MatInt &Scdl)
{
    SP_CurrentScdl.clear ();
    SP_CurrentScdl = Scdl;
}

void ScdlProblem :: PrevVecTSC (const MatInt &VecTSC)
{
    SP_PrevVecTSC.clear ();
    SP_PrevVecTSC = VecTSC;
}

void ScdlProblem :: PrevVecWPC (const MatUInt &VecWPC)
{
    SP_PrevVecWPC.clear ();
    SP_PrevVecWPC = VecWPC;
}

void ScdlProblem :: PrevVecScdl (const TriInt &VecScdl)
{
    SP_PrevVecScdl.clear ();
    SP_PrevVecScdl = VecScdl;
}

void ScdlProblem :: CurrentVecTSC (const MatInt &VecTSC)
{
    SP_CurrentVecTSC.clear ();
    SP_CurrentVecTSC = VecTSC;
}

void ScdlProblem :: CurrentVecWPC (const MatUInt &VecWPC)
{
    SP_CurrentVecWPC.clear ();
    SP_CurrentVecWPC = VecWPC;
}

void ScdlProblem :: CurrentVecScdl (const TriInt &VecScdl)
{
    SP_CurrentVecScdl.clear ();
    SP_CurrentVecScdl = VecScdl;
}

// *****************************************************************************
// Functions to return the value of the protected variables
// *****************************************************************************

UINT ScdlProblem :: SolutionIndex ()
{
    return SP_SolutionIndex;
}

int ScdlProblem :: InitialSolutionMethod ()
{
    return SP_InitialSolutionMethod;
}

int ScdlProblem :: InitialSolutionVecMethod ()
{
    return SP_InitialSolutionVecMethod;
}

VecInt ScdlProblem :: TSC ()
{
    return SP_SRTSC;
}

VecUInt ScdlProblem :: WPC ()
{
    return SP_SRWPC;
}

MatInt ScdlProblem :: Scdl ()
{
    return SP_SRScdl;
}

MatInt ScdlProblem :: VecTSC ()
{
    return SP_VecTSC;
}

MatUInt ScdlProblem :: VecWPC ()
{
    return SP_VecWPC;
}

TriInt ScdlProblem :: VecScdl ()
{
    return SP_VecScdl;
}

// ***** Class JS_ScdlProblem

// *****************************************************************************
// The following function generates a initial solution by the selected method
// *****************************************************************************

bool JS_ScdlProblem :: InitialSolution ()
{
    switch (SP_InitialSolutionMethod)
    {
        case PREVIOUS_SOLUTION:

            SP_SRScdl.clear ();
            SP_SRTSC.clear ();
            SP_SRWPC.clear ();

            SP_SRScdl = SP_PrevScdl;
            SP_SRTSC = SP_PrevTSC;
            SP_SRWPC = SP_PrevWPC;

            TimingScdlSR ();
            return TRUE;

        case CURRENT_SOLUTION:

            SP_SRScdl.clear ();
            SP_SRTSC.clear ();
            SP_SRWPC.clear ();

            SP_SRScdl = SP_CurrentScdl;
            SP_SRTSC = SP_CurrentTSC;
            SP_SRWPC = SP_CurrentWPC;

            TimingScdlSR ();
            return TRUE;

        case SIMPLE_ORDERLY:
            return SimpleOrderly ();

        case RANDOM_INITIAL_SOLUTION:
            return RandomInitialSolution ();

        default:
            return FALSE;
    }

    return TRUE;
}

bool JS_ScdlProblem :: InitialSolutionVector ()
{
    float BestMakespan = FLT_MAX;

    switch (SP_InitialSolutionVecMethod)
    {
        case PREVIOUS_SOLUTION_VECTOR:

            SP_VecWPC.clear();
            SP_VecWPC = SP_PrevVecWPC;
            SP_PopulationSize = SP_VecWPC.size();

            SP_VecTSC.clear ();
            SP_VecTSC.reserve (SP_PopulationSize);

            SP_VecScdl.clear ();
            SP_VecScdl.reserve (SP_PopulationSize);

            for (UINT i=0; i<SP_VecWPC.size(); i++)
            {
                SP_SRWPC = SP_VecWPC[i];
                Timing_WPC ();

                if (SP_Makespan < BestMakespan)
                {
                    BestMakespan = SP_Makespan;
                    SP_SolutionIndex = i;
                }

                SP_VecTSC.push_back (SP_SRTSC);
                SP_VecScdl.push_back (SP_SRScdl);
            }

            SP_SRScdl = SP_VecScdl[SP_SolutionIndex];
            SP_SRTSC = SP_VecTSC[SP_SolutionIndex];
            SP_SRWPC = SP_VecWPC[SP_SolutionIndex];

            TimingScdlSR ();

            return TRUE;

        case CURRENT_SOLUTION_VECTOR:

            SP_VecWPC.clear();
            SP_VecWPC = SP_CurrentVecWPC;
            SP_PopulationSize = SP_VecWPC.size();

            SP_VecTSC.clear ();
            SP_VecTSC.reserve (SP_PopulationSize);

            SP_VecScdl.clear ();
            SP_VecScdl.reserve (SP_PopulationSize);

            for (UINT i=0; i<SP_VecWPC.size(); i++)
            {
                SP_SRWPC = SP_VecWPC[i];
                Timing_WPC ();

                if (SP_Makespan < BestMakespan)
                {
                    BestMakespan = SP_Makespan;
                    SP_SolutionIndex = i;
                }

                SP_VecTSC.push_back (SP_SRTSC);
                SP_VecScdl.push_back (SP_SRScdl);
            }

            SP_SRScdl = SP_VecScdl[SP_SolutionIndex];
            SP_SRTSC = SP_VecTSC[SP_SolutionIndex];
            SP_SRWPC = SP_VecWPC[SP_SolutionIndex];

            TimingScdlSR ();

            return TRUE;

        case RANDOM_INITIAL_SOLUTION_VECTOR:

            RandomInitialSolutionVector ();

            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

// *****************************************************************************
// The following function prints on screen what is the current solution
// *****************************************************************************

bool JS_ScdlProblem :: PrintOnScreenCurrentSolutionSpecification ()
{
    printf ("\n\n Initial Solution:");

    switch (SP_InitialSolutionMethod)
    {
        case PREVIOUS_SOLUTION:
            printf (" Previus solution.");
            break;

        case SIMPLE_ORDERLY:
            printf (" By Simple Orderly method.");
            break;

        case RANDOM_INITIAL_SOLUTION:
            printf (" Random Initial Solution.");

        default:
            printf (" No method was defined.");
            break;
    }

    return TRUE;
}

// *****************************************************************************
// The following function generates a initial solution by Simple Orderly method
// *****************************************************************************

bool JS_ScdlProblem :: SimpleOrderly ()
{
    SP_SRScdl.clear ();
    SP_SRScdl.resize (SP_NMcn);

    for (UINT i = 0; i < SP_SRScdl.size(); i++)
    {
        SP_SRScdl[i].reserve(SP_NTaskMcn[i]);
    }

    for (int count=0; count<SP_NTTask; count++)
    {
        SP_SRScdl[SP_McnOfTask[count]].push_back(count);
    }

    TimingScdlSR (SP_SRTSC);
    WPC_by_TSC ();

    return TRUE;
}

// *****************************************************************************
// The following function generates a random initial solution.
// *****************************************************************************

bool JS_ScdlProblem :: RandomInitialSolution ()
{
    int rnd;

    VecInt VecJob;

    VecJob.reserve (SP_NJob);

    for (UINT k=0; k<SP_NMcn; k++)
    {
        for (UINT i=0; i<SP_NJob; i++)
        {
            VecJob.push_back (i);
        }
    }

    SP_SRWPC.clear();
    SP_SRWPC.reserve (SP_NTTask);

    while (VecJob.size() != 0)
    {
        rnd = rand()%(VecJob.size());
        SP_SRWPC.push_back(VecJob[rnd]);
        VecJob.erase(VecJob.begin() + rnd);
    }

    TSC_by_WPC ();
    Scdl_by_TSC ();

    TimingScdlSR ();

    VecJob.clear();
    return TRUE;
}


// *****************************************************************************
// The following function generates a vector of random initial solutions.
// *****************************************************************************

bool JS_ScdlProblem :: RandomInitialSolutionVector ()
{
    float best_makespan = FLT_MAX;

    SP_VecTSC.clear ();
    SP_VecWPC.clear ();
    SP_VecScdl.clear ();

    for (UINT i=0; i<SP_PopulationSize; i++)
    {
        RandomInitialSolution ();

        SP_VecTSC.push_back (SP_SRTSC);
        SP_VecWPC.push_back (SP_SRWPC);
        SP_VecScdl.push_back (SP_SRScdl);

        if (SP_Makespan < best_makespan)
        {
            SP_SolutionIndex = i;
            best_makespan = SP_Makespan;
        }
    }

    SP_SRScdl = SP_VecScdl[SP_SolutionIndex];
    SP_SRTSC = SP_VecTSC[SP_SolutionIndex];
    SP_SRWPC = SP_VecWPC[SP_SolutionIndex];

    TimingScdlSR ();

    return TRUE;
}

// *****************************************************************************
// The following function adjusts the time parameters of a standard scheduling
// solution representation.
// *****************************************************************************

bool JS_ScdlProblem :: TimingScdlSR (VecInt &TSC)
{
    bool aux = false;
    int count, opt, LastTask;

    VecBool Status;
    Status.resize (SP_NTTask, false);

    VecUInt Pont;
    Pont.resize(SP_NMcn, 0);

    TSC.clear();
    TSC.reserve(SP_NTTask);

    AdjustMPrevOnScdlSR ();

    SP_Makespan = 0;

    count=0;
    while (count < SP_NTTask)
    {
        aux = false;

        for(UINT k=0; k<SP_NMcn; k++)
        {
            if (SP_SRScdl[k].size() == 0) continue;

            if (Pont[k] < SP_SRScdl[k].size())
            {
                opt = SP_SRScdl[k][Pont[k]];

                if (SP_PrevTaskOnJob[opt] == -1)
                {
                    if (Pont[k] == 0)
                    {
                        SP_StartTimeOfTask[opt] = 0;
                    }
                    else
                    {
                        SP_StartTimeOfTask[opt] = SP_FinalTimeOfTask[SP_PrevTaskOnMcn[opt]];
                    }

                    SP_FinalTimeOfTask[opt] = SP_StartTimeOfTask[opt] + SP_TimeOfTask[opt];

                    if (SP_FinalTimeOfTask[opt] > SP_Makespan)
                    {
                        SP_Makespan = SP_FinalTimeOfTask[opt];
                        LastTask = opt;
                        SP_LastTaskOfScdl.clear();
                        SP_LastTaskOfScdl.push_back(LastTask);
                    }
                    else if (SP_FinalTimeOfTask[opt] > SP_Makespan - 0.005 && SP_FinalTimeOfTask[opt] < SP_Makespan + 0.005)
                    {
                        SP_LastTaskOfScdl.push_back(opt);
                    }

                    Pont[k]++;
                    count++;
                    Status[opt] = true;
                    TSC.push_back(opt);
                    aux = true;

                }
                else if (Status[SP_PrevTaskOnJob[opt]] == true)
                {
                    if (Pont[k] == 0)
                    {
                        SP_StartTimeOfTask[opt] = SP_FinalTimeOfTask[SP_PrevTaskOnJob[opt]];
                    }
                    else
                    {
                        SP_StartTimeOfTask[opt] = max(SP_FinalTimeOfTask[SP_PrevTaskOnJob[opt]],
                        SP_FinalTimeOfTask[SP_PrevTaskOnMcn[opt]]);
                    }

                    SP_FinalTimeOfTask[opt] = SP_StartTimeOfTask[opt] + SP_TimeOfTask[opt];

                    if (SP_FinalTimeOfTask[opt] > SP_Makespan)
                    {
                        SP_Makespan = SP_FinalTimeOfTask[opt];
                        LastTask = opt;
                        SP_LastTaskOfScdl.clear();
                        SP_LastTaskOfScdl.push_back(LastTask);
                    }
                    else if (SP_FinalTimeOfTask[opt] > SP_Makespan - 0.005 && SP_FinalTimeOfTask[opt] < SP_Makespan + 0.005)
                    {
                        SP_LastTaskOfScdl.push_back(opt);
                    }

                    Pont[k]++;
                    Status[opt] = true;
                    TSC.push_back(opt);
                    count++;
                    aux = true;
                }
            }
        }

        if (aux == false) // Seqüenciamento não é viável
        {
            printf ("\n\n Warning !!! Scheduling not feasible !!!\n\n");
            SP_Makespan = FLT_MAX;
            return FALSE;
        }
    }

    Pont.clear();
    Status.clear();

    return TRUE;
}

bool JS_ScdlProblem :: TimingScdlSR ()
{
    bool aux = false;
    int count, opt, LastTask;

    VecBool Status;
    Status.resize (SP_NTTask, false);

    VecUInt Pont;
    Pont.resize(SP_NMcn, 0);

    AdjustMPrevOnScdlSR ();

    SP_Makespan = 0;

    count=0;
    while (count < SP_NTTask)
    {
        aux = false;

        for(UINT k=0; k<SP_NMcn; k++)
        {
            if (SP_SRScdl[k].size() == 0) continue;

            if (Pont[k] < SP_SRScdl[k].size())
            {
                opt = SP_SRScdl[k][Pont[k]];

                if (SP_PrevTaskOnJob[opt] == -1)
                {
                    if (Pont[k] == 0)
                    {
                        SP_StartTimeOfTask[opt] = 0;
                    }
                    else
                    {
                        SP_StartTimeOfTask[opt] = SP_FinalTimeOfTask[SP_PrevTaskOnMcn[opt]];
                    }

                    SP_FinalTimeOfTask[opt] = SP_StartTimeOfTask[opt] + SP_TimeOfTask[opt];

                    if (SP_FinalTimeOfTask[opt] > SP_Makespan)
                    {
                        SP_Makespan = SP_FinalTimeOfTask[opt];
                        LastTask = opt;
                        SP_LastTaskOfScdl.clear();
                        SP_LastTaskOfScdl.push_back(LastTask);
                    }
                    else if (SP_FinalTimeOfTask[opt] > SP_Makespan - 0.005 && SP_FinalTimeOfTask[opt] < SP_Makespan + 0.005)
                    {
                        SP_LastTaskOfScdl.push_back(opt);
                    }

                    Pont[k]++;
                    count++;
                    Status[opt] = true;
                    aux = true;

                }
                else if (Status[SP_PrevTaskOnJob[opt]] == true)
                {
                    if (Pont[k] == 0)
                    {
                        SP_StartTimeOfTask[opt] = SP_FinalTimeOfTask[SP_PrevTaskOnJob[opt]];
                    }
                    else
                    {
                        SP_StartTimeOfTask[opt] = max(SP_FinalTimeOfTask[SP_PrevTaskOnJob[opt]],
                        SP_FinalTimeOfTask[SP_PrevTaskOnMcn[opt]]);
                    }

                    SP_FinalTimeOfTask[opt] = SP_StartTimeOfTask[opt] + SP_TimeOfTask[opt];

                    if (SP_FinalTimeOfTask[opt] > SP_Makespan)
                    {
                        SP_Makespan = SP_FinalTimeOfTask[opt];
                        LastTask = opt;
                        SP_LastTaskOfScdl.clear();
                        SP_LastTaskOfScdl.push_back(LastTask);
                    }
                    else if (SP_FinalTimeOfTask[opt] > SP_Makespan - 0.005 && SP_FinalTimeOfTask[opt] < SP_Makespan + 0.005)
                    {
                        SP_LastTaskOfScdl.push_back(opt);
                    }

                    Pont[k]++;
                    Status[opt] = true;
                    count++;
                    aux = true;
                }
            }
        }

        if (aux == false) // Seqüenciamento não é viável
        {
            printf ("\n\n Warning !!! Scheduling not feasible !!!\n\n");
            SP_Makespan = FLT_MAX;
            return FALSE;
        }
    }

    Pont.clear();
    Status.clear();

    return TRUE;
}

// *****************************************************************************
// The following function adjusts the time parameters of a work procedure code
// solution representation.
// *****************************************************************************

bool JS_ScdlProblem :: Timing_WPC()
{
  TSC_by_WPC();
  Timing_TSC();

  return TRUE;
}

// *****************************************************************************
// The following function adjusts the time parameters of a task sequence code
// solution representation.
// *****************************************************************************

bool JS_ScdlProblem :: Timing_TSC()
{
  int opt;

  Scdl_by_TSC();

  SP_Makespan = 0;

  for (UINT i=0; i<SP_SRTSC.size(); i++)
  {
    opt = SP_SRTSC[i];

    if (SP_PrevTaskOnMcn[opt] == -1)
    {
      if (SP_PrevTaskOnJob[opt] == -1)
      {
        SP_StartTimeOfTask[opt] = 0;
      }else
      {
        SP_StartTimeOfTask[opt] = SP_FinalTimeOfTask[SP_PrevTaskOnJob[opt]];
      }
    }else if (SP_PrevTaskOnJob[opt] == -1)
    {
      SP_StartTimeOfTask[opt] = SP_FinalTimeOfTask[SP_PrevTaskOnMcn[opt]];
    }else
    {
      SP_StartTimeOfTask[opt] = max(SP_FinalTimeOfTask[SP_PrevTaskOnMcn[opt]], SP_FinalTimeOfTask[SP_PrevTaskOnJob[opt]]);
    }

    SP_FinalTimeOfTask[opt] = SP_StartTimeOfTask[opt] + SP_TimeOfTask[opt];

    if (SP_FinalTimeOfTask[opt] > SP_Makespan)
    {
      SP_Makespan = SP_FinalTimeOfTask[opt];
      SP_LastTaskOfScdl.clear();
      SP_LastTaskOfScdl.push_back(opt);
    }else if (SP_FinalTimeOfTask[opt]>SP_Makespan - 0.005 && SP_FinalTimeOfTask[opt]<SP_Makespan + 0.005)
    {
      SP_LastTaskOfScdl.push_back(opt);
    }
  }

  return TRUE;
}

// *****************************************************************************
// The following function adjusts the machine sequence index of the current
// standard scheduling solution representation.
// *****************************************************************************

bool JS_ScdlProblem :: AdjustMPrevOnScdlSR()
{
    for (UINT i=0; i<SP_SRScdl.size(); i++)
    {
        SP_PrevTaskOnMcn[SP_SRScdl[i][0]] = -1;

        for (UINT j=1; j<SP_SRScdl[i].size(); j++)
        {
            SP_PrevTaskOnMcn[SP_SRScdl[i][j]] = SP_SRScdl[i][j-1];
        }
    }

    return TRUE;
}

// *****************************************************************************
// The following function generates a work procedure code from a task sequence
// code.
// *****************************************************************************

bool JS_ScdlProblem :: WPC_by_TSC ()
{
  SP_SRWPC.clear ();
  SP_SRWPC.resize(SP_SRTSC.size());

  for (UINT count=0; count<SP_SRTSC.size(); count++)
  {
    SP_SRWPC[count] = SP_JobOfTask[SP_SRTSC[count]];
  }

  return TRUE;
}

// *****************************************************************************
// The following function generates a task sequence code from a work procedure
// code.
// *****************************************************************************

bool JS_ScdlProblem :: TSC_by_WPC()
{
  VecInt Pont;
  Pont.resize (SP_NJob, 0);

  SP_SRTSC.clear ();
  SP_SRTSC.resize (SP_SRWPC.size());

  for (UINT i=0; i<SP_SRWPC.size(); i++)
  {
    SP_SRTSC[i] = SP_FirstTaskOfJob[SP_SRWPC[i]] + Pont[SP_SRWPC[i]];
    Pont[SP_SRWPC[i]]++;
  }

  Pont.clear();

  return TRUE;
}

// *****************************************************************************
// The following function generates a standeard scheduling from a task sequence
// code.
// *****************************************************************************

bool JS_ScdlProblem ::  Scdl_by_TSC()
{
  int mcn;

  SP_SRScdl.clear();
  SP_SRScdl.resize(SP_NMcn);

  for (UINT i=0; i<SP_SRTSC.size(); i++)
  {
    mcn = SP_McnOfTask[SP_SRTSC[i]];

    if (SP_SRScdl[mcn].size() == 0)
    {
      SP_PrevTaskOnMcn[SP_SRTSC[i]] = -1;
    }else
    {
      SP_PrevTaskOnMcn[SP_SRTSC[i]] = SP_SRScdl[mcn][SP_SRScdl[mcn].size()-1];
    }

    SP_SRScdl[mcn].push_back(SP_SRTSC[i]);
  }

  return TRUE;
}
