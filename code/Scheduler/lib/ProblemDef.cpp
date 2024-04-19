#include "Scdl_Structure.h"

// *****************************************************************************
// Generate a list with all scheduling problem kinds
// *****************************************************************************

VecLPSTR ProblemKindList ()
{
    LPSTR PbKind;
    VecLPSTR PbKindList;

    PbKind = "Flow shop";
    PbKindList.push_back (PbKind);

    PbKind = "Job shop";
    PbKindList.push_back (PbKind);

    return PbKindList;
}

// ***** Class ScdlProblem

// *****************************************************************************
// Generate a list with all scheduling problems
// *****************************************************************************

VecScdlProblem ScdlProblem :: ScdlProblemList ()
{
    VecScdlProblem SPList;

    ScdlProblem SP;

    SPList.clear();

    SP.SP_Name = "ABZ5";
    SP.SP_PathName = "bcmk/ABZ5.txt";

    SPList.push_back(SP);

    SP.SP_Name = "FT6";
    SP.SP_PathName = "bcmk/FT6.txt";

    SPList.push_back(SP);

    SP.SP_Name = "FT10";
    SP.SP_PathName = "bcmk/FT10.txt";

    SPList.push_back(SP);

    SP.SP_Name = "FT20";
    SP.SP_PathName = "bcmk/FT20.txt";

    SPList.push_back(SP);

    return SPList;
}

// *****************************************************************************
// Functions to set the value of the private variables
// *****************************************************************************

void ScdlProblem :: Class (const UINT &Class)
{
    SP_Class = Class;
}

void ScdlProblem :: Kind (const UINT &Kind)
{
    SP_Kind = Kind;
}

// *****************************************************************************
// Functions to return the value of the private variables
// *****************************************************************************

char* ScdlProblem :: Name ()
{
    return SP_Name;
}

char* ScdlProblem :: PathName ()
{
    return SP_PathName;
}

UINT ScdlProblem :: Class ()
{
    return SP_Kind;
}

UINT ScdlProblem :: Kind ()
{
    return SP_Kind;
}

UINT ScdlProblem :: NJob ()
{
    return SP_NJob;
}

UINT ScdlProblem :: NMcn ()
{
    return SP_NMcn;
}

float ScdlProblem :: Best_Makespan_Known ()
{
    return SP_Best_Makespan_Known;
}

// ***** Class JS_ScdlProblem

// *****************************************************************************
// Generate a list of job shop scheduling problems
// *****************************************************************************

VecLPSTR JS_ScdlProblem :: BenchmarkClassList ()
{
    LPSTR BcmkClass;
    VecLPSTR BcmkClList;

    BcmkClass = "ABZ";
    BcmkClList.push_back (BcmkClass);

    BcmkClass = "FT";
    BcmkClList.push_back (BcmkClass);

    return BcmkClList;
}

VecJS_ScdlProblem JS_ScdlProblem :: JS_ScdlProblemList ()
{
    VecJS_ScdlProblem JSPList;

    JS_ScdlProblem JSP;

    JSPList.clear();

    JSP.SP_Name = "ABZ5";
    JSP.SP_PathName = "bcmk/ABZ5.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "ABZ6";
    JSP.SP_PathName = "bcmk/ABZ6.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "ABZ7";
    JSP.SP_PathName = "bcmk/ABZ7.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "ABZ8";
    JSP.SP_PathName = "bcmk/ABZ8.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "ABZ9";
    JSP.SP_PathName = "bcmk/ABZ9.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "FT6";
    JSP.SP_PathName = "bcmk/FT6.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "FT10";
    JSP.SP_PathName = "bcmk/FT10.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "FT20";
    JSP.SP_PathName = "bcmk/FT20.txt";

    JSPList.push_back(JSP);

    return JSPList;
}

VecJS_ScdlProblem JS_ScdlProblem :: JS_ABZList ()
{
    VecJS_ScdlProblem JSPList;

    JS_ScdlProblem JSP;

    JSPList.clear();

    JSP.SP_Name = "ABZ5";
    JSP.SP_PathName = "bcmk/ABZ5.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "ABZ6";
    JSP.SP_PathName = "bcmk/ABZ6.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "ABZ7";
    JSP.SP_PathName = "bcmk/ABZ7.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "ABZ8";
    JSP.SP_PathName = "bcmk/ABZ8.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "ABZ9";
    JSP.SP_PathName = "bcmk/ABZ9.txt";

    JSPList.push_back(JSP);

    return JSPList;
}

VecJS_ScdlProblem JS_ScdlProblem :: JS_FTList ()
{
    VecJS_ScdlProblem JSPList;

    JS_ScdlProblem JSP;

    JSPList.clear();

    JSP.SP_Name = "FT6";
    JSP.SP_PathName = "bcmk/FT6.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "FT10";
    JSP.SP_PathName = "bcmk/FT10.txt";

    JSPList.push_back(JSP);

    JSP.SP_Name = "FT20";
    JSP.SP_PathName = "bcmk/FT20.txt";

    JSPList.push_back(JSP);

    return JSPList;
}

// *****************************************************************************
// Initialize the problem
// *****************************************************************************

bool JS_ScdlProblem :: GetProblem (char *path_name)
{
    FILE *bcm_file;

    bcm_file = fopen (path_name, "r");

    if (bcm_file == NULL)
    {
        MessageBox (NULL, "The program can not load this benchmark !\nPlease"
        " chose another one.", "Error", MB_ICONEXCLAMATION | MB_OK);

        return FALSE;
    }

    fscanf (bcm_file, "%s", &SP_Name);
    fscanf (bcm_file, "%d", &SP_Kind);
    fscanf (bcm_file, "%d", &SP_NJob);
    fscanf (bcm_file, "%d", &SP_NMcn);

    fscanf (bcm_file, "%f", &SP_Best_Makespan_Known);

    SP_FirstTaskOfJob.resize(SP_NJob);
    SP_LastTaskOfJob.resize(SP_NJob);
    SP_NTaskJob.resize(SP_NJob);

    SP_NTTask = 0;

    for(UINT count=0; count<SP_NJob; count++)
    {
        SP_FirstTaskOfJob[count] = SP_NTTask;
        fscanf (bcm_file, "%d", &SP_NTaskJob[count]);
        SP_NTTask = SP_NTTask + SP_NTaskJob[count];
        SP_LastTaskOfJob[count] = SP_NTTask - 1;
    }

    SP_NTaskMcn.resize (SP_NMcn);

    for(UINT count=0; count<SP_NMcn; count++)
    {
        fscanf (bcm_file, "%d", &SP_NTaskMcn[count]);
    }

    SP_McnOfTask.resize (SP_NTTask);
    SP_PrevTaskOnMcn.resize (SP_NTTask);
    SP_TimeOfTask.resize (SP_NTTask);

    for (int count=0; count<SP_NTTask; count++)
    {
        fscanf (bcm_file, "%d", &SP_McnOfTask[count]);
        fscanf (bcm_file, "%f", &SP_TimeOfTask[count]);
    }

    fclose(bcm_file);

    SP_JobOfTask.resize (SP_NTTask);
    SP_PrevTaskOnJob.resize (SP_NTTask);

    int opt = 0;
    for (UINT i=0; i<SP_NJob; i++)
    {
        SP_JobOfTask[opt] = i;
        SP_PrevTaskOnJob[opt] = -1;
        opt++;

        for (int j=1; j<SP_NTaskJob[i]; j++)
        {
            SP_JobOfTask[opt] = i;
            SP_PrevTaskOnJob[opt] = opt-1;
            opt++;
        }
    }

    SP_StartTimeOfTask.resize (SP_NTTask);
    SP_FinalTimeOfTask.resize (SP_NTTask);
    SP_LastTaskOfScdl.reserve (SP_NTTask);

    return TRUE;
}
