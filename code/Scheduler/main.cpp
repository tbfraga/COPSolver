#include <windows.h>
#include <Windowsx.h>

#include "lib\Scdl_Structure.h"

/*  Make the class and the window name into a global variable  */

LPCSTR szClassName = "Scheduler";
LPCSTR szWindowName = "Scheduler";

// Auxiliary variables

bool ShowStatus = FALSE;

HWND ControlScdl = NULL;
LRESULT lResult;

// Dialogs

HWND SensibilityAnalysisDialog = NULL,
     SetPopulationSizeDialog = NULL,
     SetCyclesNumberDialog = NULL,
     ScdlDialog = NULL,
     TSDialog = NULL,
     ScTSDialog = NULL,
     ThTSDialog = NULL,
     PCDialog = NULL,
     PCTSDialog = NULL,
     PTSDialog = NULL,
     ScPTSDialog = NULL,
     ThPTSDialog = NULL,
     PSDialog = NULL,
     ScPSDialog = NULL,
     ThPSDialog = NULL,
     SolutionGanttDialog = NULL,
     NeighborhoodGanttDialog = NULL,
     Message = NULL;

// Lists

JS_ScdlProblem JSP;
VecJS_ScdlProblem JSPList = JSP.JS_ScdlProblemList ();

VecLPSTR PbKindList = ProblemKindList ();
VecLPSTR BcmkClassList = JSP.BenchmarkClassList ();
VecLPSTR MtModeList = MethodModeList ();
VecLPSTR HbModelList = HybridModelList ();
VecLPSTR MtdList = MethodList ();
VecLPSTR ISList = InitialSolutionList ();
VecLPSTR ISVecList = InitialSolutionVectorList ();
VecLPSTR CPOperatorList = CP_OperatorList ();
VecLPSTR CrossoverMtdList = CrossoverMethodList ();
VecLPSTR MutationMtdList = MutationMethodList ();
VecLPSTR PerturbationMtdList = PerturbationMethodList ();
VecLPSTR ExploitationMtdList = ExploitationMethodList ();

/*  Declare the windows procedures  */

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ProblemDefinerDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK SensibilityAnalysisDlgProc (HWND hDlgWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK SetPopulationSizeDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK SetCyclesNumberDlgProc (HWND hDlgWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ScdlDlgProc (HWND hDlgWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK TSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ScTSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ThTSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK PCDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK PCTSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK PTSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ScPTSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ThPTSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK PSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ScPSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ThPSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK SolutionGanttProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK SolutionGanttVecProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK SolutionGanttN5Proc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK MessageProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);

bool SensibilityAnalysisDlg_WM_SHOWWINDOW ();
bool ID_FILE_SA_CYCLES_NUMBER_SELECTION (HWND hWnd);
bool IDET_SENSIBILITY_ANALYSIS_INITIAL_VALUE_EN_CHANGE ();
bool IDET_SENSIBILITY_ANALYSIS_FINAL_VALUE_EN_CHANGE ();
bool IDET_SENSIBILITY_ANALYSIS_INCREASE_VALUE_EN_CHANGE ();
bool IDET_SENSIBILITY_ANALYSIS_REPETITIONS_NUMBER_EN_CHANGE ();
bool IDC_SENSITIVITY_ANALYSIS_BN_CLICKED ();

bool ID_FILE_CPV_POPSIZE_SELECTION (HWND hWnd);
bool SetPopulationSizeDlg_WM_SHOWWINDOW ();
bool IDET_POPULATION_SIZE_EN_CHANGE (HWND hWnd);

bool ID_FILE_CPV_NCYCLES_SELECTION (HWND hWnd);
bool SetCyclesNumberDlg_WM_SHOWWINDOW ();
bool IDET_CYCLES_NUMBER_EN_CHANGE (HWND hWnd);

bool Create_ScdlDlg (HWND hWnd);
bool Close_ScdlDlg (HWND hWnd);

bool ScdlDlgProc_WM_INITDIALOG (HWND hWnd);
bool IDCB_BCMK_KIND_CBN_SELENDOK ();
bool IDCB_BCMK_CLASS_CBN_SELENDOK ();
bool IDCB_BCMK_CBN_SELENDOK ();
bool IDCB_METHOD_MODE_CBN_SELENDOK ();
bool IDCB_HYBRID_MODEL_CBN_SELENDOK ();
bool IDCB_METHOD01_CBN_SELENDOK ();
bool IDCB_METHOD02_CBN_SELENDOK ();
bool IDCB_METHOD03_CBN_SELENDOK ();
bool IDC_SCHEDULER_BN_CLICKED ();
bool IDC_SHOW_NGH_GANTT_BN_CLICKED ();

bool ICDB_SOLUTION_INDEX_CBN_SELENDOK (HWND hWnd);

bool TSDlgProc_WM_INITDIALOG (HWND hWnd);
bool TSDlgProc_WM_SHOWWINDOW ();
bool IDCB_TS01_INITIAL_SOLUTION_CBN_SELENDOK ();
bool IDCB_TS01_CRITICAL_PATH_CBN_SELENDOK ();
bool IDCB_TS01_NGH_METHOD_CBN_SELENDOK ();
bool IDCB_TS01_TENURE_EN_CHANGE ();
bool IDCB_TS01_MAXITE_EN_CHANGE ();

bool PCDlgProc_WM_INITDIALOG (HWND hWnd);
bool PCDlgProc_WM_SHOWWINDOW ();
bool IDCB_PC01_INITIAL_SOLUTION_CBN_SELENDOK ();
bool IDCB_PC01_MAXITE_EN_CHANGE ();

bool PCTSDlgProc_WM_INITDIALOG (HWND hWnd);
bool PCTSDlgProc_WM_SHOWWINDOW ();
bool IDCB_TSPC_CRITICAL_PATH_CBN_SELENDOK ();
bool IDCB_TSPC_NGH_METHOD_CBN_SELENDOK ();
bool IDCB_TSPC_TENURE_EN_CHANGE ();
bool IDCB_TSPC_MAXITE_EN_CHANGE ();

bool PTSDlgProc_WM_INITDIALOG (HWND hWnd);
bool PTSDlgProc_WM_SHOWWINDOW ();
bool IDCB_PTS01_INITIAL_SOLUTION_CBN_SELENDOK ();
bool IDET_PTS01_POPULATION_SIZE_EN_CHANGE ();
bool IDCB_PTS01_CRITICAL_PATH_CBN_SELENDOK ();
bool IDCB_PTS01_NGH_METHOD_CBN_SELENDOK ();
bool IDET_PTS01_TENURE_EN_CHANGE ();
bool IDET_PTS01_MAXITE_EN_CHANGE ();

bool ScPTSDlgProc_WM_INITDIALOG (HWND hWnd);
bool ScPTSDlgProc_WM_SHOWWINDOW ();
bool IDCB_PTS02_NGH_METHOD_CBN_SELENDOK ();
bool IDET_PTS02_TENURE_EN_CHANGE ();
bool IDET_PTS02_MAXITE_EN_CHANGE ();

bool ThPTSDlgProc_WM_INITDIALOG (HWND hWnd);
bool ThPTSDlgProc_WM_SHOWWINDOW ();
bool IDCB_PTS03_NGH_METHOD_CBN_SELENDOK ();
bool IDET_PTS03_TENURE_EN_CHANGE ();
bool IDET_PTS03_MAXITE_EN_CHANGE ();

bool PSDlgProc_WM_INITDIALOG (HWND hWnd);
bool PSDlgProc_WM_SHOWWINDOW ();
bool IDCB_PS_INITIAL_SOLUTION_CBN_SELENDOK ();
bool IDET_PS01_MUTATION_PERCENT_EN_CHANGE ();
bool IDET_PS01_POPULATION_SIZE_EN_CHANGE ();
bool IDET_PS01_MAXITE_EN_CHANGE ();

bool ScPSDlgProc_WM_INITDIALOG (HWND hWnd);
bool ScPSDlgProc_WM_SHOWWINDOW ();
bool IDET_PS02_MUTATION_PERCENT_EN_CHANGE ();
bool IDET_PS02_MAXITE_EN_CHANGE ();

bool ThPSDlgProc_WM_INITDIALOG (HWND hWnd);
bool ThPSDlgProc_WM_SHOWWINDOW ();
bool IDET_PS03_MUTATION_PERCENT_EN_CHANGE ();
bool IDET_PS03_MAXITE_EN_CHANGE ();

void HideAllMethodsDialogBox ();
void HideSecondAndThirdMethodsDialogBoxes ();
void HideThirdMethodsDialogBoxes ();
void HideAllInformation ();
void GenerateTabooSearchInitialSolution ();
void GenerateVectorOfInitialSolutions ();
void GenerateAndShowInitialVectorOfSolutions (HWND hWnd, const int &CriticalPathComboBoxID);
void ShowGantt (HWND hWnd);
void ShowNeighborhoodGantt (HWND hWnd);
void ShowN5Gantt (HWND hWnd);

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hWnd;              /* This is the handle for our window */
    MSG Msg;                /* Here messages to the application are saved */
    WNDCLASSEX WndClsEx;    /* Data structure for the windowclass */

    /* The Window structure */

    WndClsEx.hInstance = hThisInstance;
    WndClsEx.lpszClassName = szClassName;
    WndClsEx.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    WndClsEx.style = CS_DBLCLKS;                 /* Catch double-clicks */
    WndClsEx.cbSize = sizeof (WNDCLASSEX);
    WndClsEx.hIcon = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_SCDL));
    WndClsEx.hIconSm = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_SCDL));
    WndClsEx.hCursor = LoadCursor (NULL, IDC_ARROW);
    WndClsEx.lpszMenuName = MAKEINTRESOURCE (IDR_SCDL_MENU);
    WndClsEx.cbClsExtra = 0;                      /* No extra bytes after the window class */
    WndClsEx.cbWndExtra = 0;                      /* structure or the window instance */
    WndClsEx.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */

    if (!RegisterClassEx (&WndClsEx))
    {
        MessageBox (NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    /* The class is registered, let's create the program*/
    hWnd = CreateWindowEx (
           WS_EX_OVERLAPPEDWINDOW,  /* Extended possibilites for variation */
           szClassName,             /* Classname */
           szWindowName,            /* Title Text */
           WS_OVERLAPPEDWINDOW,     /* default window */
           0,                       /* Windows decides the position */
           0,                                   /* where the window ends up on the screen */
           GetSystemMetrics(SM_CXSCREEN),       /* The programs width */
           GetSystemMetrics(SM_CYSCREEN),       /* and height in pixels */
           HWND_DESKTOP,                        /* The window is a child-window to desktop */
           NULL,                    /* No menu */
           hThisInstance,           /* Program Instance handler */
           NULL                     /* No Window Creation data */
           );

    if (hWnd == NULL)
    {
        MessageBox (NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    /* Make the window visible on the screen */
    ShowWindow (hWnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&Msg, NULL, 0, 0) > 0)
    {
        if (!IsDialogMessage (ScdlDialog, &Msg))
        {
            /* Translate virtual-key messages into character messages */
            TranslateMessage(&Msg);
            /* Send message to WindowProcedure */
            DispatchMessage(&Msg);
        }
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return Msg.wParam;
}

/*  The window procedure. This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)                          /* handle the messages */
    {
        case WM_CREATE:
        break;

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case ID_FILE_BENCHMARK_SCHEDULER:

                    // Generate a new Scheduler Dialog Box

                    Create_ScdlDlg (hWnd);
                    break;

                case ID_FILE_CLOSE:

                    Close_ScdlDlg (hWnd);
                    break;

                case ID_FILE_EXIT:
                    PostMessage (hWnd, WM_CLOSE, 0, 0);
                    break;

                case ID_FILE_CREATE_GANTT:
                    break;

                case ID_FILE_CREATE_N5:
                    ShowN5Gantt (ScdlDialog);
                    break;

                case ID_FILE_CPV_POPSIZE:
                    return ID_FILE_CPV_POPSIZE_SELECTION (hWnd);

                case ID_FILE_CPV_NCYCLES:
                    return ID_FILE_CPV_NCYCLES_SELECTION (hWnd);

                case ID_FILE_SA_CYCLES_NUMBER:
                    return ID_FILE_SA_CYCLES_NUMBER_SELECTION (hWnd);

                case ID_FILE_SA_TSFM_TENURE:

                    JSP.Sensibility_Analysis_Parameter (SA_TSFTM_TENURE);

                    // Generate the Sensibility Analysis Dialog Box

                    JSP.Sensibility_Analysis_Initial_Value (6);
                    JSP.Sensibility_Analysis_Final_Value (15);
                    JSP.Sensibility_Analysis_Increase_Value (1);
                    JSP.Sensibility_Analysis_Increase_Mode (SUM);
                    JSP.Sensibility_Analysis_Convergence_Mode (CA_NONE);
                    JSP.Sensibility_Analysis_Extra_Criterion_Mode (EC_NO_EXTRA_CRITERION);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        DestroyWindow (SensibilityAnalysisDialog);
                    }

                    SensibilityAnalysisDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SENSIBILITY_ANALYSIS), hWnd,
                    SensibilityAnalysisDlgProc);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        ShowWindow (SensibilityAnalysisDialog, SW_SHOW);
                    }
                    else
                    {
                        MessageBox (hWnd, "Create SensibilityAnalysisDialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
                    }

                    break;

                case ID_FILE_SA_TSFM_MAXITE:

                    JSP.Sensibility_Analysis_Parameter (SA_TSFTM_MAXITE);

                    // Generate the Sensibility Analysis Dialog Box

                    JSP.Sensibility_Analysis_Initial_Value (100);
                    JSP.Sensibility_Analysis_Final_Value (100000);
                    JSP.Sensibility_Analysis_Increase_Value (10);
                    JSP.Sensibility_Analysis_Increase_Mode (MULTIPLICATION);
                    JSP.Sensibility_Analysis_Convergence_Mode (CA_NONE);
                    JSP.Sensibility_Analysis_Extra_Criterion_Mode (EC_NO_EXTRA_CRITERION);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        DestroyWindow (SensibilityAnalysisDialog);
                    }

                    SensibilityAnalysisDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SENSIBILITY_ANALYSIS), hWnd,
                    SensibilityAnalysisDlgProc);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        ShowWindow (SensibilityAnalysisDialog, SW_SHOW);
                    }
                    else
                    {
                        MessageBox (hWnd, "Create SensibilityAnalysisDialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
                    }

                    break;

                case ID_FILE_SA_TSSM_TENURE:

                    JSP.Sensibility_Analysis_Parameter (SA_TSSCM_TENURE);

                    // Generate the Sensibility Analysis Dialog Box

                    JSP.Sensibility_Analysis_Initial_Value (6);
                    JSP.Sensibility_Analysis_Final_Value (15);
                    JSP.Sensibility_Analysis_Increase_Value (1);
                    JSP.Sensibility_Analysis_Increase_Mode (SUM);
                    JSP.Sensibility_Analysis_Convergence_Mode (CA_NONE);
                    JSP.Sensibility_Analysis_Extra_Criterion_Mode (EC_NO_EXTRA_CRITERION);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        DestroyWindow (SensibilityAnalysisDialog);
                    }

                    SensibilityAnalysisDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SENSIBILITY_ANALYSIS), hWnd,
                    SensibilityAnalysisDlgProc);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        ShowWindow (SensibilityAnalysisDialog, SW_SHOW);
                    }
                    else
                    {
                        MessageBox (hWnd, "Create SensibilityAnalysisDialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
                    }

                    break;

                case ID_FILE_SA_TSSM_MAXITE:

                    JSP.Sensibility_Analysis_Parameter (SA_TSSCM_MAXITE);

                    // Generate the Sensibility Analysis Dialog Box

                    JSP.Sensibility_Analysis_Initial_Value (100);
                    JSP.Sensibility_Analysis_Final_Value (100000);
                    JSP.Sensibility_Analysis_Increase_Value (10);
                    JSP.Sensibility_Analysis_Increase_Mode (MULTIPLICATION);
                    JSP.Sensibility_Analysis_Convergence_Mode (CA_NONE);
                    JSP.Sensibility_Analysis_Extra_Criterion_Mode (EC_NO_EXTRA_CRITERION);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        DestroyWindow (SensibilityAnalysisDialog);
                    }

                    SensibilityAnalysisDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SENSIBILITY_ANALYSIS), hWnd,
                    SensibilityAnalysisDlgProc);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        ShowWindow (SensibilityAnalysisDialog, SW_SHOW);
                    }
                    else
                    {
                        MessageBox (hWnd, "Create SensibilityAnalysisDialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
                    }

                    break;

                case ID_FILE_SA_PCFM_MAXITE:

                    JSP.Sensibility_Analysis_Parameter (SA_PCFTM_MAXITE);

                    // Generate the Sensibility Analysis Dialog Box

                    JSP.Sensibility_Analysis_Initial_Value (100);
                    JSP.Sensibility_Analysis_Final_Value (100);
                    JSP.Sensibility_Analysis_Increase_Value (10);
                    JSP.Sensibility_Analysis_Increase_Mode (MULTIPLICATION);
                    JSP.Sensibility_Analysis_Convergence_Mode (CA_BY_CYCLE);
                    JSP.Sensibility_Analysis_Extra_Criterion_Mode (EC_BEST_MAKESPAN_FOUND);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        DestroyWindow (SensibilityAnalysisDialog);
                    }

                    SensibilityAnalysisDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SENSIBILITY_ANALYSIS), hWnd,
                    SensibilityAnalysisDlgProc);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        ShowWindow (SensibilityAnalysisDialog, SW_SHOW);
                    }
                    else
                    {
                        MessageBox (hWnd, "Create SensibilityAnalysisDialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
                    }

                    break;

                case ID_FILE_SA_SPSFM_MPERC:

                    JSP.Sensibility_Analysis_Initial_Value (0);
                    JSP.Sensibility_Analysis_Final_Value (100);
                    JSP.Sensibility_Analysis_Increase_Value (10);
                    JSP.Sensibility_Analysis_Increase_Mode (SUM);
                    JSP.Sensibility_Analysis_Convergence_Mode (CA_NONE);
                    JSP.Sensibility_Analysis_Extra_Criterion_Mode (EC_NO_EXTRA_CRITERION);

                    JSP.Sensibility_Analysis_Parameter (SA_SPSFTM_MPERC);

                    // Generate the Sensibility Analysis Dialog Box

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        DestroyWindow (SensibilityAnalysisDialog);
                    }

                    SensibilityAnalysisDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SENSIBILITY_ANALYSIS), hWnd,
                    SensibilityAnalysisDlgProc);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        ShowWindow (SensibilityAnalysisDialog, SW_SHOW);
                    }
                    else
                    {
                        MessageBox (hWnd, "Create SensibilityAnalysisDialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
                    }

                    break;

                case ID_FILE_SA_SPSSM_MPERC:

                    JSP.Sensibility_Analysis_Parameter (SA_SPSSCM_MPERC);

                    // Generate the Sensibility Analysis Dialog Box

                    JSP.Sensibility_Analysis_Initial_Value (0);
                    JSP.Sensibility_Analysis_Final_Value (100);
                    JSP.Sensibility_Analysis_Increase_Value (10);
                    JSP.Sensibility_Analysis_Increase_Mode (SUM);
                    JSP.Sensibility_Analysis_Convergence_Mode (CA_NONE);
                    JSP.Sensibility_Analysis_Extra_Criterion_Mode (EC_NO_EXTRA_CRITERION);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        DestroyWindow (SensibilityAnalysisDialog);
                    }

                    SensibilityAnalysisDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SENSIBILITY_ANALYSIS), hWnd,
                    SensibilityAnalysisDlgProc);

                    if (SensibilityAnalysisDialog != NULL)
                    {
                        ShowWindow (SensibilityAnalysisDialog, SW_SHOW);
                    }
                    else
                    {
                        MessageBox (hWnd, "Create SensibilityAnalysisDialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
                    }

                    break;

                case ID_FILE_PRINT_TIME_SLOT:
                    JSP.PrintOnScreenSlotOfTime ();
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage (WM_QUIT);    /* send a WM_QUIT to the message queue */
        break;

        default:                          /* for messages that we don't deal with */
            return DefWindowProc (hWnd, Msg, wParam, lParam);
    }

    return 0;
}

// *** Sensibility Analysis Dialog Procedure

BOOL CALLBACK ProblemDefinerDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_INITDIALOG:
            break;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK SensibilityAnalysisDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_SHOWWINDOW:

            SensibilityAnalysisDlg_WM_SHOWWINDOW ();
            return TRUE;

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDET_INITIAL_VALUE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_SENSIBILITY_ANALYSIS_INITIAL_VALUE_EN_CHANGE ();

                    break;

                case IDET_FINAL_VALUE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_SENSIBILITY_ANALYSIS_FINAL_VALUE_EN_CHANGE ();

                    break;

                case IDET_INCREASE_VALUE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_SENSIBILITY_ANALYSIS_INCREASE_VALUE_EN_CHANGE ();

                    break;

                case IDET_REPETITIONS_NUMBER:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_SENSIBILITY_ANALYSIS_REPETITIONS_NUMBER_EN_CHANGE ();

                    break;


                case IDC_SUM:

                    if (HIWORD(wParam) == BN_CLICKED)
                    JSP.Sensibility_Analysis_Increase_Mode (SUM);

                    break;

                case IDC_MULTIPLICATION:

                    if (HIWORD(wParam) == BN_CLICKED)
                    JSP.Sensibility_Analysis_Increase_Mode (MULTIPLICATION);

                    break;

                case IDC_EXPONENT:

                    if (HIWORD(wParam) == BN_CLICKED)
                    JSP.Sensibility_Analysis_Increase_Mode (EXPONENT);

                    break;

                case IDC_NO_CONVERGENCE_ANALYSIS:

                    if (HIWORD(wParam) == BN_CLICKED)
                    JSP.Sensibility_Analysis_Convergence_Mode (CA_NONE);

                    break;

                case IDC_BY_CYCLE:

                    if (HIWORD(wParam) == BN_CLICKED)
                    JSP.Sensibility_Analysis_Convergence_Mode (CA_BY_CYCLE);

                    break;

                case IDC_BY_ITERATION:

                    if (HIWORD(wParam) == BN_CLICKED)
                    JSP.Sensibility_Analysis_Convergence_Mode (CA_BY_ITERATION);

                    break;

                case IDC_NO_EXTRA_STOP_CRITERION:

                    if (HIWORD(wParam) == BN_CLICKED)
                    JSP.Sensibility_Analysis_Extra_Criterion_Mode (EC_NO_EXTRA_CRITERION);

                    break;

                case IDC_BEST_MAKESPAN_FOUND:

                    if (HIWORD(wParam) == BN_CLICKED)
                    JSP.Sensibility_Analysis_Extra_Criterion_Mode (EC_BEST_MAKESPAN_FOUND);

                    break;

                case IDC_PRINT_ALL:

                    if (HIWORD(wParam) == BN_CLICKED)
                    JSP.Sensibility_Analysis_Print_Parameter (PRINT_ALL);

                    break;

                case IDC_PRINT_BEST:

                    if (HIWORD(wParam) == BN_CLICKED)
                    JSP.Sensibility_Analysis_Print_Parameter (PRINT_BEST);

                    break;

                case IDC_SENSITIVITY_ANALYSIS:

                    if (HIWORD(wParam) == BN_CLICKED)
                    return IDC_SENSITIVITY_ANALYSIS_BN_CLICKED ();

                    break;

                case IDCANCEL:

                    if (HIWORD(wParam) == BN_CLICKED)
                    DestroyWindow (hWndDlg);
                    return TRUE;

                default:
                    return FALSE;
            }

            return TRUE;

        case WM_CLOSE:
            DestroyWindow (hWndDlg);
            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK SetPopulationSizeDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_SHOWWINDOW:

            SetPopulationSizeDlg_WM_SHOWWINDOW ();
            return TRUE;

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDET_POPULATION_SIZE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_POPULATION_SIZE_EN_CHANGE (hWndDlg);

                case IDCANCEL:

                    if (HIWORD(wParam) == BN_CLICKED)
                    DestroyWindow (hWndDlg);
                    return TRUE;

                default:
                    return FALSE;
            }

            return TRUE;

        case WM_CLOSE:
            DestroyWindow (hWndDlg);
            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK SetCyclesNumberDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_SHOWWINDOW:

            SetCyclesNumberDlg_WM_SHOWWINDOW ();
            return TRUE;

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDET_CYCLES_NUMBER:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_CYCLES_NUMBER_EN_CHANGE (hWndDlg);

                case IDCANCEL:

                    if (HIWORD(wParam) == BN_CLICKED)
                    DestroyWindow (hWndDlg);
                    return TRUE;

                default:
                    return FALSE;
            }

            return TRUE;

        case WM_CLOSE:
            DestroyWindow (hWndDlg);
            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK ScdlDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    int MsgBoxID;

    switch (Msg)
    {
        case WM_INITDIALOG:
            return ScdlDlgProc_WM_INITDIALOG (hWndDlg);

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDCB_BCMK_CLASS:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_BCMK_CLASS_CBN_SELENDOK ();

                case IDCB_BCMK_KIND:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_BCMK_KIND_CBN_SELENDOK ();

                case IDCB_BCMK:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_BCMK_CBN_SELENDOK ();

                case IDCB_METHOD_MODE:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_METHOD_MODE_CBN_SELENDOK ();

                case IDCB_HYBRID_MODEL:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_HYBRID_MODEL_CBN_SELENDOK ();

                case IDET_CYCLES_NUMBER:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_CYCLES_NUMBER_EN_CHANGE (hWndDlg);

                case IDCB_METHOD_01:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_METHOD01_CBN_SELENDOK ();

                case IDCB_METHOD_02:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_METHOD02_CBN_SELENDOK ();

                case IDCB_METHOD_03:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_METHOD03_CBN_SELENDOK ();

                case IDC_SCHEDULER:

                    if (HIWORD(wParam) == BN_CLICKED)
                    return IDC_SCHEDULER_BN_CLICKED ();

                case IDC_SHOW_NGH_GANTT:

                    if (HIWORD(wParam) == BN_CLICKED)
                    return IDC_SHOW_NGH_GANTT_BN_CLICKED ();

                case IDCANCEL:

                    if (HIWORD(wParam) == BN_CLICKED)
                    {
                        MsgBoxID = MessageBox (NULL, "Do you realy want to finish this application", "Message",
                        MB_YESNO | MB_ICONQUESTION);
                        if (MsgBoxID == IDYES) EndDialog (hWndDlg, WM_QUIT);
                    }
                    return TRUE;

                default:
                    return FALSE;
            }

            break;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK TSDlgProc (HWND hWndTSDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HWND hWndOwner = GetParent(hWndTSDlg);

    switch (Msg)
    {
        case WM_INITDIALOG:
            return TSDlgProc_WM_INITDIALOG (hWndTSDlg);

        case WM_SHOWWINDOW:
            return TSDlgProc_WM_SHOWWINDOW ();

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDCB_TS_INITIAL_SOLUTION:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_TS01_INITIAL_SOLUTION_CBN_SELENDOK ();

                case IDCB_TS01_CRITICAL_PATH:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_TS01_CRITICAL_PATH_CBN_SELENDOK ();

                case IDCB_TS01_NGH_METHOD:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_TS01_NGH_METHOD_CBN_SELENDOK ();

                case IDET_TS01_TENURE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDCB_TS01_TENURE_EN_CHANGE ();

                case IDET_TS01_MAXITE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDCB_TS01_MAXITE_EN_CHANGE ();

                case IDC_SHOW_GANTT:

                    if (HIWORD(wParam) == BN_CLICKED)
                    ShowGantt (hWndOwner);
                    return TRUE;

                default:
                    break;
            }

            break;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK ScTSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                default:
                    return FALSE;
            }

            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK ThTSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                default:
                    return FALSE;
            }
            break;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK PCDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_INITDIALOG:
            return PCDlgProc_WM_INITDIALOG (hWndDlg);

        case WM_SHOWWINDOW:
            return PCDlgProc_WM_SHOWWINDOW ();

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDCB_INITIAL_SOLUTION:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_PC01_INITIAL_SOLUTION_CBN_SELENDOK ();

                case IDET_PC01_MAXITE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDCB_PC01_MAXITE_EN_CHANGE ();

                case IDCB_SOLUTION_INDEX:
                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return ICDB_SOLUTION_INDEX_CBN_SELENDOK (hWndDlg);

                default:
                    return FALSE;
            }

            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK PCTSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_INITDIALOG:
            return PCTSDlgProc_WM_INITDIALOG (hWndDlg);

        case WM_SHOWWINDOW:
            return PCTSDlgProc_WM_SHOWWINDOW ();

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDCB_TS01_CRITICAL_PATH:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_TSPC_CRITICAL_PATH_CBN_SELENDOK ();

                case IDCB_TS01_NGH_METHOD:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_TSPC_NGH_METHOD_CBN_SELENDOK ();

                case IDET_TS01_TENURE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDCB_TSPC_TENURE_EN_CHANGE ();

                case IDET_TS01_MAXITE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDCB_TSPC_MAXITE_EN_CHANGE ();

                default:
                    break;
            }

            break;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK PTSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_INITDIALOG:
            return PTSDlgProc_WM_INITDIALOG (hWndDlg);

        case WM_SHOWWINDOW:
            return PTSDlgProc_WM_SHOWWINDOW ();

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDCB_PTS_INITIAL_SOLUTION:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_PTS01_INITIAL_SOLUTION_CBN_SELENDOK ();

                case IDET_PTS01_POPULATION_SIZE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_PTS01_POPULATION_SIZE_EN_CHANGE ();

                case IDCB_PTS01_CRITICAL_PATH:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_PTS01_CRITICAL_PATH_CBN_SELENDOK ();

                case IDCB_PTS01_NGH_METHOD:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_PTS01_NGH_METHOD_CBN_SELENDOK ();

                case IDET_PTS01_TENURE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_PTS01_TENURE_EN_CHANGE ();

                case IDET_PTS01_MAXITE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_PTS01_MAXITE_EN_CHANGE ();

                case IDCB_SOLUTION_INDEX:
                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return ICDB_SOLUTION_INDEX_CBN_SELENDOK (hWndDlg);

                default:
                    return FALSE;
            }
            break;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK ScPTSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_INITDIALOG:
            return ScPTSDlgProc_WM_INITDIALOG (hWndDlg);

        case WM_SHOWWINDOW:
            return ScPTSDlgProc_WM_SHOWWINDOW ();

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDCB_PTS02_NGH_METHOD:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_PTS02_NGH_METHOD_CBN_SELENDOK ();

                case IDET_PTS02_TENURE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_PTS02_TENURE_EN_CHANGE ();

                case IDET_PTS02_MAXITE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_PTS02_MAXITE_EN_CHANGE ();

                default:
                    return FALSE;
            }

            break;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK ThPTSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_INITDIALOG:
            return ThPTSDlgProc_WM_INITDIALOG (hWndDlg);

        case WM_SHOWWINDOW:
            return ThPTSDlgProc_WM_SHOWWINDOW ();

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDCB_PTS03_NGH_METHOD:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_PTS03_NGH_METHOD_CBN_SELENDOK ();

                case IDET_PTS03_TENURE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_PTS03_TENURE_EN_CHANGE ();

                case IDET_PTS03_MAXITE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_PTS03_MAXITE_EN_CHANGE ();

                default:
                    return FALSE;
            }

            break;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK PSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_INITDIALOG:
            return PSDlgProc_WM_INITDIALOG (hWndDlg);

        case WM_SHOWWINDOW:
            return PSDlgProc_WM_SHOWWINDOW ();

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDCB_PS_INITIAL_SOLUTION:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return IDCB_PS_INITIAL_SOLUTION_CBN_SELENDOK ();

                case IDET_PS01_POPULATION_SIZE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_PS01_POPULATION_SIZE_EN_CHANGE ();

                case IDET_PS01_MUTATION_PERCENT:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_PS01_MUTATION_PERCENT_EN_CHANGE ();

                case IDET_PS01_MAXITE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_PS01_MAXITE_EN_CHANGE ();

                case IDCB_SOLUTION_INDEX:

                    if (HIWORD(wParam) == CBN_SELENDOK)
                    return ICDB_SOLUTION_INDEX_CBN_SELENDOK (hWndDlg);

                default:
                    return FALSE;
            }

            break;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK ScPSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_INITDIALOG:
            return ScPSDlgProc_WM_INITDIALOG (hWndDlg);

        case WM_SHOWWINDOW:
            return ScPSDlgProc_WM_SHOWWINDOW ();

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDET_PS02_MAXITE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_PS02_MAXITE_EN_CHANGE ();

                default:
                    return FALSE;
            }

            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK ThPSDlgProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_INITDIALOG:
            return ThPSDlgProc_WM_INITDIALOG (hWndDlg);

        case WM_SHOWWINDOW:
            return ThPSDlgProc_WM_SHOWWINDOW ();

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
                case IDET_PS03_MAXITE:

                    if (HIWORD(wParam) == EN_CHANGE)
                    return IDET_PS03_MAXITE_EN_CHANGE ();

                default:
                    return FALSE;
            }

            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK SolutionGanttProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC hDC;
    PAINTSTRUCT PS;

    switch (Msg)
    {
        case WM_PAINT:

            hDC = BeginPaint (hWndDlg, &PS);
            JSP.PrintGanttSolution (hWndDlg, 5, 5, 265, 130);
            JSP.PrintCriticalPath (hWndDlg, 5, 5, 265, 130);
            //JSP.PrintBlocksOnCriticalPath (hWndDlg, 5, 5, 265, 130);
            EndPaint (hWndDlg, &PS);

            return TRUE;

        case WM_CLOSE:
            DestroyWindow (hWndDlg);
            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK SolutionGanttVecProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC hDC;
    PAINTSTRUCT PS;

    HICON hIcon;

    switch (Msg)
    {
        case WM_INITDIALOG:

            hIcon = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SCDL));
            SendMessage (hWndDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
            SendMessage (hWndDlg, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
            break;

        case WM_PAINT:

            hDC = BeginPaint (hWndDlg, &PS);
            JSP.PrintGanttNeighborhood (hWndDlg, 0, 0, 631, 356);
            EndPaint (hWndDlg, &PS);

            return TRUE;

        case WM_CLOSE:
            DestroyWindow (hWndDlg);
            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK SolutionGanttN5Proc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC hDC;
    PAINTSTRUCT PS;

    HICON hIcon;

    switch (Msg)
    {
        case WM_INITDIALOG:

            hIcon = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SCDL));
            SendMessage (hWndDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
            SendMessage (hWndDlg, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
            break;

        case WM_PAINT:

            hDC = BeginPaint (hWndDlg, &PS);
            JSP.PrintGanttN5 (hWndDlg, 0, 0, 631, 356);
            EndPaint (hWndDlg, &PS);

            return TRUE;

        case WM_CLOSE:
            DestroyWindow (hWndDlg);
            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK MessageProc (HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        default:
            return FALSE;
    }
}


bool SensibilityAnalysisDlg_WM_SHOWWINDOW ()
{
    // Show the initial, final and increase values, the increase mode and the repetitions number on its respectives dialog boxes

    SetDlgItemInt (SensibilityAnalysisDialog, IDET_INITIAL_VALUE, JSP.Sensibility_Analysis_Initial_Value(), FALSE);
    SetDlgItemInt (SensibilityAnalysisDialog, IDET_FINAL_VALUE, JSP.Sensibility_Analysis_Final_Value(), FALSE);
    SetDlgItemInt (SensibilityAnalysisDialog, IDET_INCREASE_VALUE, JSP.Sensibility_Analysis_Increase_Value(), FALSE);
    SetDlgItemInt (SensibilityAnalysisDialog, IDET_REPETITIONS_NUMBER, JSP.Sensibility_Analysis_Repetitions(), FALSE);

    // Check the current increase mode Radio Button

    switch (JSP.Sensibility_Analysis_Increase_Mode())
    {
        case SUM:
            CheckRadioButton (SensibilityAnalysisDialog, IDC_SUM, IDC_EXPONENT, IDC_SUM);
            break;

        case MULTIPLICATION:
            CheckRadioButton (SensibilityAnalysisDialog, IDC_SUM, IDC_EXPONENT, IDC_MULTIPLICATION);
            break;

        case EXPONENT:
            CheckRadioButton (SensibilityAnalysisDialog, IDC_SUM, IDC_EXPONENT, IDC_EXPONENT);
            break;

        default:
            MessageBox (NULL, "The defined Sensibility Analysis Increase Mode doesn't exist !!!", "Warning", MB_OK | MB_ICONINFORMATION);
            break;
    }

    // Check the current convergence mode Radio Button

    switch (JSP.Sensibility_Analysis_Convergence_Mode())
    {
        case CA_NONE:
            CheckRadioButton (SensibilityAnalysisDialog, IDC_NO_CONVERGENCE_ANALYSIS, IDC_BY_ITERATION, IDC_NO_CONVERGENCE_ANALYSIS);
            break;

        case CA_BY_CYCLE:
            CheckRadioButton (SensibilityAnalysisDialog, IDC_NO_CONVERGENCE_ANALYSIS, IDC_BY_ITERATION, IDC_BY_CYCLE);
            break;

        case CA_BY_ITERATION:
            CheckRadioButton (SensibilityAnalysisDialog, IDC_NO_CONVERGENCE_ANALYSIS, IDC_BY_ITERATION, IDC_BY_ITERATION);
            break;

        default:
            MessageBox (NULL, "The defined Sensibility Analysis Convergence Mode doesn't exist !!!", "Warning",
            MB_OK | MB_ICONINFORMATION);
            break;
    }

    // Check the extra stop criterion mode Radio Button

    switch (JSP.Sensibility_Analysis_Extra_Criterion_Mode())
    {
        case EC_NO_EXTRA_CRITERION:
            CheckRadioButton (SensibilityAnalysisDialog, IDC_NO_EXTRA_STOP_CRITERION, IDC_BEST_MAKESPAN_FOUND,
            IDC_NO_EXTRA_STOP_CRITERION);

            break;

        case EC_BEST_MAKESPAN_FOUND:
            CheckRadioButton (SensibilityAnalysisDialog, IDC_NO_EXTRA_STOP_CRITERION, IDC_BEST_MAKESPAN_FOUND,
            IDC_BEST_MAKESPAN_FOUND);

            break;

        default:
            MessageBox (NULL, "The defined Sensibility Analysis Extra Stop Criterion Mode doesn't exist !!!", "Warning",
            MB_OK | MB_ICONINFORMATION);

            break;
    }

     // Check the current print parameter Radio Button

    switch (JSP.Sensibility_Analysis_Print_Parameter())
    {
        case PRINT_ALL:
            CheckRadioButton (SensibilityAnalysisDialog, IDC_PRINT_ALL, IDC_PRINT_BEST, IDC_PRINT_ALL);
            break;

        case PRINT_BEST:
            CheckRadioButton (SensibilityAnalysisDialog, IDC_PRINT_ALL, IDC_PRINT_BEST, IDC_PRINT_BEST);
            break;

        default:
            MessageBox (NULL, "The defined Sensibility Analysis Print Parameter doesn't exist !!!", "Warning", MB_OK | MB_ICONINFORMATION);
            break;
    }

    return TRUE;
}

bool ID_FILE_SA_CYCLES_NUMBER_SELECTION (HWND hWnd)
{
    JSP.Sensibility_Analysis_Parameter (SA_NCYCLES);

    // Generate the Sensibility Analysis Dialog Box

    JSP.Sensibility_Analysis_Initial_Value (JSP.NCycles());
    JSP.Sensibility_Analysis_Final_Value (JSP.NCycles());
    JSP.Sensibility_Analysis_Increase_Value (10);
    JSP.Sensibility_Analysis_Increase_Mode (SUM);
    JSP.Sensibility_Analysis_Convergence_Mode (CA_BY_CYCLE);
    JSP.Sensibility_Analysis_Extra_Criterion_Mode (EC_BEST_MAKESPAN_FOUND);

    if (SensibilityAnalysisDialog != NULL)
    {
        DestroyWindow (SensibilityAnalysisDialog);
    }

    SensibilityAnalysisDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SENSIBILITY_ANALYSIS), hWnd, SensibilityAnalysisDlgProc);

    if (SensibilityAnalysisDialog != NULL)
    {
        ShowWindow (SensibilityAnalysisDialog, SW_SHOW);
    }
    else
    {
        MessageBox (hWnd, "Create SensibilityAnalysisDialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    return TRUE;
}

bool IDC_SENSITIVITY_ANALYSIS_BN_CLICKED ()
{
    DestroyWindow (SensibilityAnalysisDialog);

    Message = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_WAIT_MESSAGE), ScdlDialog, MessageProc);

    if (Message != NULL)
    {
        ShowWindow (Message, SW_SHOW);
    }
    else
    {
        MessageBox (ScdlDialog, "Create Message Dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    JSP.SensibilityAnalysis ();

    DestroyWindow (Message);

    return TRUE;
}

bool IDET_SENSIBILITY_ANALYSIS_INITIAL_VALUE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (SensibilityAnalysisDialog, IDET_INITIAL_VALUE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Sensibility Analysis Initial Value Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.Sensibility_Analysis_Initial_Value (lResult);
    }

    return TRUE;
}

bool IDET_SENSIBILITY_ANALYSIS_FINAL_VALUE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (SensibilityAnalysisDialog, IDET_FINAL_VALUE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Sensibility Analysis Final Value Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.Sensibility_Analysis_Final_Value (lResult);
    }

    return TRUE;
}

bool IDET_SENSIBILITY_ANALYSIS_INCREASE_VALUE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (SensibilityAnalysisDialog, IDET_INCREASE_VALUE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Sensibility Analysis Increase Value Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.Sensibility_Analysis_Increase_Value (lResult);
    }

    return TRUE;
}

bool IDET_SENSIBILITY_ANALYSIS_REPETITIONS_NUMBER_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (SensibilityAnalysisDialog, IDET_REPETITIONS_NUMBER, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Sensibility Analysis Repetitions Number Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.Sensibility_Analysis_Repetitions (lResult);
    }

    return TRUE;
}


bool ID_FILE_CPV_POPSIZE_SELECTION (HWND hWnd)
{
    if (SetPopulationSizeDialog != NULL)
    {
        DestroyWindow (SetPopulationSizeDialog);
    }

    SetPopulationSizeDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SET_POPULATION_SIZE), hWnd, SetPopulationSizeDlgProc);

    if (SetPopulationSizeDialog != NULL)
    {
        ShowWindow (SetPopulationSizeDialog, SW_SHOW);
    }
    else
    {
        MessageBox (hWnd, "Create SetPopulationSizeDialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    return TRUE;
}

bool SetPopulationSizeDlg_WM_SHOWWINDOW ()
{
    // Show the initial value of the population size

    SetDlgItemInt (SetPopulationSizeDialog, IDET_POPULATION_SIZE, JSP.PopulationSize(), FALSE);

    return TRUE;
}

bool IDET_POPULATION_SIZE_EN_CHANGE (HWND hWnd)
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (hWnd, IDET_POPULATION_SIZE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Set Population Size Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.PopulationSize (lResult);
    }

    return TRUE;
}


bool ID_FILE_CPV_NCYCLES_SELECTION (HWND hWnd)
{
    if (SetCyclesNumberDialog != NULL)
    {
        DestroyWindow (SetCyclesNumberDialog);
    }

    SetCyclesNumberDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SET_CYCLES_NUMBER), hWnd, SetCyclesNumberDlgProc);

    if (SetCyclesNumberDialog != NULL)
    {
        ShowWindow (SetCyclesNumberDialog, SW_SHOW);
    }
    else
    {
        MessageBox (hWnd, "Create SetCyclesNumberDialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    return TRUE;
}

bool SetCyclesNumberDlg_WM_SHOWWINDOW ()
{
    // Show the initial value of the number of cycles

    SetDlgItemInt (SetCyclesNumberDialog, IDET_CYCLES_NUMBER, JSP.NCycles(), FALSE);

    return TRUE;
}

bool IDET_CYCLES_NUMBER_EN_CHANGE (HWND hWnd)
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (hWnd, IDET_CYCLES_NUMBER, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Set Cycles Number Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.NCycles (lResult);
    }

    return TRUE;
}


bool Create_ScdlDlg (HWND hWnd)
{
    if (ScdlDialog != NULL)
    {
        int msgboxID = MessageBox (hWnd, "Do you really want to finish this application ?", "Warning", MB_YESNO);

        switch (msgboxID)
        {
            case IDYES:

                DestroyWindow (ScdlDialog);

                ScdlDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SCDL_BOX), hWnd, ScdlDlgProc);

                if (ScdlDialog != NULL)
                {
                    ShowWindow (ScdlDialog, SW_SHOW);
                }
                else
                {
                    MessageBox (hWnd, "CreateDialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
                    return false;
                }

                break;

            case IDNO:
                break;
        }
    }
    else
    {

        ScdlDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SCDL_BOX), hWnd, ScdlDlgProc);

        if (ScdlDialog != NULL)
        {
            ShowWindow (ScdlDialog, SW_SHOW);
        }
        else
        {
            MessageBox (hWnd, "CreateDialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
            return false;
        }
    }

    return true;
}

bool Close_ScdlDlg (HWND hWnd)
{
    if (ScdlDialog != NULL)
    {
        int msgboxID = MessageBox (hWnd, "Do you really want to finish this application ?", "Warning", MB_YESNO);

        switch (msgboxID)
        {
            case IDYES:

                DestroyWindow (ScdlDialog);
                break;

            case IDNO:
                break;
        }
    }

    return true;
}

bool ScdlDlgProc_WM_INITDIALOG (HWND hWnd)
{
    // Check the Optimale Radio Button

    CheckRadioButton (hWnd, IDC_OPTIMALE, IDC_VISUAL, IDC_OPTIMALE);

    // Generate the list of the Benchmark Kind Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_BCMK_KIND);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  --  Select the problem kind  --");

    for (UINT count=0; count<PbKindList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)PbKindList[count]);
    }

    // Disable de Benchmark Class Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_BCMK_CLASS);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)" Benchmark Classes");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable de Benchmark Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_BCMK);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  --  Benchmark List  --");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Method Mode Combo Box and generate its list

    ControlScdl = GetDlgItem (hWnd, IDCB_METHOD_MODE);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ----  Method Mode  ----");
    ComboBox_Enable (ControlScdl, FALSE);

    for (UINT count=0; count<MtModeList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)MtModeList[count]);
    }

    // Disable the Hybrid Model Combo Box and generate its list

    ControlScdl = GetDlgItem (hWnd, IDCB_HYBRID_MODEL);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ---------------  Hybrid Model  --------------");
    ComboBox_Enable (ControlScdl, FALSE);

    for (UINT count=0; count<HbModelList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)HbModelList[count]);
    }

    // Disable the Cycles Number Edit Text

    ControlScdl = GetDlgItem (hWnd, IDET_CYCLES_NUMBER);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"    NCycles ");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the First Method Combo Box and generate its list

    ControlScdl = GetDlgItem (hWnd, IDCB_METHOD_01);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  First Method  -----");
    ComboBox_Enable (ControlScdl, FALSE);

    for (UINT count=0; count<MtdList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)MtdList[count]);
    }

    // Disable the Second Method Combo Box and generate its list

    ControlScdl = GetDlgItem (hWnd, IDCB_METHOD_02);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ---  Second Method  ---");
    ComboBox_Enable (ControlScdl, FALSE);

    for (UINT count=0; count<MtdList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)MtdList[count]);
    }

    SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"  ---------  None  --------");

    // Disable the Third Method Combo Box and generate its list

    ControlScdl = GetDlgItem (hWnd, IDCB_METHOD_03);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  Third Method  ----");
    ComboBox_Enable (ControlScdl, FALSE);

    for (UINT count=0; count<MtdList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)MtdList[count]);
    }

    SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"  ---------  None  --------");

    // Generate the First Taboo Search Dialog Box

    TSDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TABOO_SEARCH_1), hWnd, TSDlgProc);

    if (TSDialog == NULL)
    {
        MessageBox (ScdlDialog, "CreateDialog for Taboo Search Dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    // Generate the Second Taboo Search Dialog Box

    ScTSDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TABOO_SEARCH_2), hWnd, ScTSDlgProc);

    if (ScTSDialog == NULL)
    {
        MessageBox (ScdlDialog, "CreateDialog for the Second Taboo Search Dialog returned NULL !", "Warning",
        MB_OK | MB_ICONINFORMATION);
    }

    // Generate the Third Taboo Search Dialog Box

    ThTSDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TABOO_SEARCH_3), hWnd, ThTSDlgProc);

    if (ThTSDialog == NULL)
    {
        MessageBox (ScdlDialog, "CreateDialog for the Third Taboo Search Dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    // Generate the First Particle Collision Dialog Box

    PCDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PARTICLE_COLLISION_01), hWnd, PCDlgProc);

    if (PCDialog == NULL)
    {
        MessageBox (ScdlDialog, "CreateDialog for Particle Collision Dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    // Generate the Taboo Search of Particle Collision Dialog Box

    PCTSDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TABOO_SEARCH_PC), hWnd, PCTSDlgProc);

    if (PCTSDialog == NULL)
    {
        MessageBox (ScdlDialog, "CreateDialog for Taboo Search of Particle Collision Dialog returned NULL !", "Warning",
        MB_OK | MB_ICONINFORMATION);
    }

    // Generate the First Parallel Taboo Search Dialog Box

    PTSDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PARALLEL_TABOO_SEARCH_01), hWnd, PTSDlgProc);

    if (PTSDialog == NULL)
    {
        MessageBox (ScdlDialog, "CreateDialog for Parallel Taboo Search Dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    // Generate the Second Parallel Taboo Search Dialog Box

    ScPTSDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PARALLEL_TABOO_SEARCH_02), hWnd, ScPTSDlgProc);

    if (ScPTSDialog == NULL)
    {
        MessageBox (ScdlDialog, "CreateDialog for the Second Parallel Taboo Search Dialog returned NULL !", "Warning",
        MB_OK | MB_ICONINFORMATION);
    }

    // Generate the Third Parallel Taboo Search Dialog Box

    ThPTSDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PARALLEL_TABOO_SEARCH_03), hWnd, ThPTSDlgProc);

    if (ThPTSDialog == NULL)
    {
        MessageBox (ScdlDialog, "CreateDialog for the Third Parallel Taboo Search dialog returned NULL !", "Warning",
        MB_OK | MB_ICONINFORMATION);
    }

    // Generate the First Similar Particle Swarm Dialog Box

    PSDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PARTICLE_SWARM_01), hWnd, PSDlgProc);

    if (PSDialog == NULL)
    {
        MessageBox (ScdlDialog, "CreateDialog for Particle Swarm Dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    // Generate the Second Similar Particle Swarm Dialog Box

    ScPSDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PARTICLE_SWARM_02), hWnd, ScPSDlgProc);

    if (ScPSDialog == NULL)
    {
        MessageBox (ScdlDialog, "CreateDialog for Particle Swarm Dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    // Generate the Third Similar Particle Swarm Dialog Box

    ThPSDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PARTICLE_SWARM_03), hWnd, ThPSDlgProc);

    if (ThPSDialog == NULL)
    {
        MessageBox (ScdlDialog, "CreateDialog for Particle Swarm Dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    // Disable the Scheduler button

    ControlScdl = GetDlgItem (hWnd, IDC_SCHEDULER);
    Button_Enable (ControlScdl, FALSE);

    return TRUE;
}

bool IDCB_BCMK_KIND_CBN_SELENDOK ()
{
    // Hide all Method Dialogs

    HideAllMethodsDialogBox ();

    // Hide all the information shown on Scheduler Dialog

    HideAllInformation ();

    // Disable de Benchmark Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_BCMK);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  --  Benchmark List  --");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Method Mode Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_MODE);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ----  Method Mode  ----");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Hybrid Model Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_HYBRID_MODEL);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ---------------  Hybrid Model  --------------");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Cycles Number Edit Text

    ControlScdl = GetDlgItem (ScdlDialog, IDET_CYCLES_NUMBER);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"    NCycles ");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the First Method Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_01);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  First Method  -----");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Second Method Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_02);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ---  Second Method  ---");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Third Method Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_03);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  Third Method  ----");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Scheduler Button

    ControlScdl = GetDlgItem (ScdlDialog, IDC_SCHEDULER);
    Button_Enable (ControlScdl, FALSE);

    // Get the selected item and generate the Benchmark Combo Box list

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_BCMK_KIND);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);

    switch (lResult)
    {
        case FLOW_SHOP:

            ControlScdl = GetDlgItem (ScdlDialog, IDCB_BCMK_CLASS);
            SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)" -  No item to select  -");
            ComboBox_Enable (ControlScdl, FALSE);

            return TRUE;

        case JOB_SHOP:

            ControlScdl = GetDlgItem (ScdlDialog, IDCB_BCMK_CLASS);
            SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  --  Select a class  --");
            ComboBox_Enable (ControlScdl, TRUE);

            for (UINT count=0; count<BcmkClassList.size(); count++)
            {
                SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)BcmkClassList[count]);
            }

            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

bool IDCB_BCMK_CLASS_CBN_SELENDOK ()
{
    // Hide all Method Dialogs

    HideAllMethodsDialogBox ();

    // Hide all the information shown on Scheduler Dialog

    HideAllInformation ();

    // Disable the Method Mode Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_MODE);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ----  Method Mode  ----");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Hybrid Model Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_HYBRID_MODEL);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ---------------  Hybrid Model  --------------");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Cycles Number Edit Text

    ControlScdl = GetDlgItem (ScdlDialog, IDET_CYCLES_NUMBER);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"    NCycles ");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the First Method Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_01);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  First Method  -----");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Second Method Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_02);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ---  Second Method  ---");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Third Method Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_03);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  Third Method  ----");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Scheduler Button

    ControlScdl = GetDlgItem (ScdlDialog, IDC_SCHEDULER);
    Button_Enable (ControlScdl, FALSE);

    // Get the selected item and generate the Benchmark Combo Box list

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_BCMK_KIND);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);

    switch (lResult)
    {
        case FLOW_SHOP:
            return TRUE;

        case JOB_SHOP:

            // Get the selected item and generate the Benchmark Combo Box list

            ControlScdl = GetDlgItem (ScdlDialog, IDCB_BCMK_CLASS);
            lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);

            switch (lResult)
            {
                case ABZ:

                    // Enable the Benckmark Combo Box

                    ControlScdl = GetDlgItem (ScdlDialog, IDCB_BCMK);
                    SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);
                    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  Select a benchmark");
                    ComboBox_Enable (ControlScdl, TRUE);

                    JSPList.clear ();
                    JSPList = JSP.JS_ABZList ();
                    for (UINT count=0; count<JSPList.size(); count++)
                    {
                        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)JSPList[count].Name());
                    }

                    return TRUE;

                case FT:

                    // Enable the Benckmark Combo Box

                    ControlScdl = GetDlgItem (ScdlDialog, IDCB_BCMK);
                    SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);
                    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  Select a benchmark");
                    ComboBox_Enable (ControlScdl, TRUE);

                    JSPList.clear ();
                    JSPList = JSP.JS_FTList ();
                    for (UINT count=0; count<JSPList.size(); count++)
                    {
                        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)JSPList[count].Name());
                    }

                    return TRUE;

                default:
                    return FALSE;
            }
            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

bool IDCB_BCMK_CBN_SELENDOK ()
{
    // Hide all Method Dialogs

    HideAllMethodsDialogBox ();

    // Hide all the information shown on Scheduler Dialog

    HideAllInformation ();

    // Enable the Method Mode Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_MODE);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  Select method mode");
    ComboBox_Enable (ControlScdl, TRUE);

    // Disable the Hybrid Model Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_HYBRID_MODEL);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ---------------  Hybrid Model  --------------");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Cycles Number Edit Text

    ControlScdl = GetDlgItem (ScdlDialog, IDET_CYCLES_NUMBER);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"    NCycles ");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the First Method Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_01);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  First Method  -----");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Second Method Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_02);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ---  Second Method  ---");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Third Method Combo Box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_03);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  Third Method  ----");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Scheduler button

    ControlScdl = GetDlgItem (ScdlDialog, IDC_SCHEDULER);
    Button_Enable (ControlScdl, FALSE);

    // Get the selected item and update the problem variables

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_BCMK_KIND);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);

    switch (lResult)
    {
        case FLOW_SHOP:
            break;

        case JOB_SHOP:

            ControlScdl = GetDlgItem (ScdlDialog, IDCB_BCMK);
            lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);

            if (!JSP.GetProblem (JSPList[lResult].PathName())) return FALSE;

            ControlScdl = GetDlgItem (ScdlDialog, IDSC_PROBLEM_NAME);
            SetWindowText (ControlScdl, JSPList[lResult].Name());

            ControlScdl = GetDlgItem (ScdlDialog, IDSC_PROBLEM_KIND);
            SetWindowText (ControlScdl, PbKindList[JSP.Kind()]);

            SetDlgItemInt (ScdlDialog, IDSC_JOB_NUMBER, JSP.NJob(), FALSE);
            SetDlgItemInt (ScdlDialog, IDSC_MCN_NUMBER, JSP.NMcn(), FALSE);
            SetDlgItemInt (ScdlDialog, IDSC_BEST_MKP_KNOW, (INT)JSP.Best_Makespan_Known(), FALSE);

            break;

        default:
            break;
    }

    // Generate a vector of random initial solutions

    JSP.InitialSolutionVecMethod (RANDOM_INITIAL_SOLUTION_VECTOR);
    GenerateVectorOfInitialSolutions ();

    return TRUE;
}

bool IDCB_METHOD_MODE_CBN_SELENDOK ()
{
    HideAllMethodsDialogBox ();

    // Delete the text of the Initial Solution static control

    ControlScdl = GetDlgItem (ScdlDialog, IDSC_INITIAL_SOLUTION);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

    // Disable the Second Method combo box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_02);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ---  Second Method  ---");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Third Method combo box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_03);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  Third Method  ----");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Scheduler button

    ControlScdl = GetDlgItem (ScdlDialog, IDC_SCHEDULER);
    Button_Enable (ControlScdl, FALSE);

    // Get the selected item and update the method mode

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_MODE);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);

    switch (lResult)
    {
        case SINGLE:

            // Update de text of the First Method group box

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_1);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"First method parameters");

            // Update the text of the Second Method group box

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_2);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"Not available");

            // Update the text of the Third Method group box

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_3);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"Not available");

            // Disable the Hybrid Model combo box

            ControlScdl = GetDlgItem (ScdlDialog, IDCB_HYBRID_MODEL);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ---------------  Not available  --------------");
            ComboBox_Enable (ControlScdl, FALSE);

            // Disable the Cycles Number edit text

            ControlScdl = GetDlgItem (ScdlDialog, IDET_CYCLES_NUMBER);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"    NCycles ");
            ComboBox_Enable (ControlScdl, FALSE);

            // Enable the First Method combo box

            ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_01);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  --  Select a method  --");
            ComboBox_Enable (ControlScdl, TRUE);

            // Update de method mode variable

            ControlScdl = GetDlgItem (ScdlDialog, IDSC_METHOD);
            SetWindowText (ControlScdl, "Single");
            JSP.MethodMode(SINGLE);

            return TRUE;

        case HYBRID:

            // Update de text of the First Method group box

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_1);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"First method parameters");

            // Update the text of the Second Method group box

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_2);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"Second method parameters");

            // Update the text of the Third Method group box

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_3);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"Third method parameters");

            // Enable the Hybrid Model combo box

            ControlScdl = GetDlgItem (ScdlDialog, IDCB_HYBRID_MODEL);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -------  Select the hybrid model  -------");
            ComboBox_Enable (ControlScdl, TRUE);

            // Enable and update the Cycles Number edit text

            ControlScdl = GetDlgItem (ScdlDialog, IDET_CYCLES_NUMBER);
            ComboBox_Enable (ControlScdl, TRUE);
            SetDlgItemInt (ScdlDialog, IDET_CYCLES_NUMBER, JSP.NCycles(), FALSE);

            // Disable the First method combo Box

            ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_01);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  First Method  -----");
            ComboBox_Enable (ControlScdl, FALSE);

            // Update de method mode static control text

            ControlScdl = GetDlgItem (ScdlDialog, IDSC_METHOD);
            SetWindowText (ControlScdl, "Hybrid");

            JSP.MethodMode(HYBRID);

            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

bool IDCB_HYBRID_MODEL_CBN_SELENDOK ()
{
    HideAllMethodsDialogBox ();

    // Enable the First Method combo box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_01);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  --  Select a method  --");
    ComboBox_Enable (ControlScdl, TRUE);

    // Disable the Second Method combo box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_02);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  ---  Second Method  ---");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Third Method combo box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_03);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  Third Method  ----");
    ComboBox_Enable (ControlScdl, FALSE);

    // Disable the Scheduler button

    ControlScdl = GetDlgItem (ScdlDialog, IDC_SCHEDULER);
    Button_Enable (ControlScdl, FALSE);

    // Get the selected item and update the method mode

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_HYBRID_MODEL);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);

    // Update de Method Mode and the Method Mode static control variables

    switch (lResult)
    {
        case HYBRID_SUCCESSIVE_APPLICATION:

            ControlScdl = GetDlgItem (ScdlDialog, IDSC_METHOD);
            SetWindowText (ControlScdl, "Hybrid Successive Application");
            JSP.HybridModel (HYBRID_SUCCESSIVE_APPLICATION);
            return TRUE;

        case HYBRID_NEIGHBORHOOD:

            ControlScdl = GetDlgItem (ScdlDialog, IDSC_METHOD);
            SetWindowText (ControlScdl, "Hybrid Neighborhood");
            JSP.HybridModel(HYBRID_NEIGHBORHOOD);
            return TRUE;

        case HYBRID_IMPROVED_NEIGHBORHOOD:
            ControlScdl = GetDlgItem (ScdlDialog, IDSC_METHOD);
            SetWindowText (ControlScdl, "Hybrid Improved Neighborhood");
            JSP.HybridModel(HYBRID_IMPROVED_NEIGHBORHOOD);
            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

bool IDCB_METHOD01_CBN_SELENDOK ()
{
    HideAllMethodsDialogBox ();

    if (JSP.MethodMode() == SINGLE)
    {
        // Enable the Scheduler button

        ControlScdl = GetDlgItem (ScdlDialog, IDC_SCHEDULER);
        Button_Enable (ControlScdl, TRUE);

    }
    else if (JSP.MethodMode() == HYBRID)
    {
        // Enable the Second Method combo box

        ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_02);
        SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  --  Select a method  --");
        ComboBox_Enable (ControlScdl, TRUE);

        // Disable the Third Method combo box

        ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_03);
        SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  Third Method  ----");
        ComboBox_Enable (ControlScdl, FALSE);

        // Disable the Scheduler button

        ControlScdl = GetDlgItem (ScdlDialog, IDC_SCHEDULER);
        Button_Enable (ControlScdl, FALSE);
    }

    // Get the selected item and update the method variable

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_01);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);
    JSP.Method (lResult);

    if (JSP.MethodMode() == HYBRID)
    {
        JSP.FtMethod (lResult);
    }

    switch (lResult)
    {
        case TABOO_SEARCH:

            // Update the Method Static Control text

            if (JSP.MethodMode() == SINGLE)
            {
                ControlScdl = GetDlgItem (ScdlDialog, IDSC_METHOD);
                SetWindowText (ControlScdl, "Single Taboo Search");
            }

            // Set the default value for the initial solution static control

            ControlScdl = GetDlgItem (ScdlDialog, IDSC_INITIAL_SOLUTION);
            SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)ISList[JSP.InitialSolutionMethod()]);

            // Update the First Method Group Box text

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_1);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Taboo Search parameters");

            // Show the Taboo Search dialog box and update its parameters

            if (TSDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (TSDialog, SW_SHOW);
            }

            // Show the solution and the specified critical path in a Gantt graph

            ShowGantt (ScdlDialog);

            return TRUE;

        case PARTICLE_COLLISION:

            // Update the Method Static Control text

            if (JSP.MethodMode() == SINGLE)
            {
                ControlScdl = GetDlgItem (ScdlDialog, IDSC_METHOD);
                SetWindowText (ControlScdl, "Single Particle Collision");
            }

            // Set the default value for the initial solution static control

            ControlScdl = GetDlgItem (ScdlDialog, IDSC_INITIAL_SOLUTION);
            SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)ISList[JSP.InitialSolutionMethod()]);

            // Update the First Method Group Box text

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_1);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Particle Collision parameters");

            // Show the Particle Collision Dialog Box

            if (PCDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (PCDialog, SW_SHOW);
            }

            // Show the Taboo Search of Particle Collision Dialog Box

            if (PCTSDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (PCTSDialog, SW_SHOW);
            }

            // Show the solution and the specified critical path in a Gantt graph

            ShowGantt (ScdlDialog);

            return TRUE;

        case PARALLEL_TABOO_SEARCH:

            // Set the default value for the initial solution static control

            ControlScdl = GetDlgItem (ScdlDialog, IDSC_INITIAL_SOLUTION);
            SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)ISVecList[JSP.InitialSolutionVecMethod()]);

            // Update the first method group box text

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_1);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Parallel Taboo Search parameters");

            // Update the first method static control text

            if (JSP.MethodMode() == SINGLE)
            {
                ControlScdl = GetDlgItem (ScdlDialog, IDSC_METHOD);
                SetWindowText (ControlScdl, "Single Parallel Taboo Search");
            }

            // Show the Parallel Taboo Search dialog box and update its parameters

            if (PTSDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (PTSDialog, SW_SHOW);
            }

            return TRUE;


        case PARALLEL_PARTICLE_COLLISION:

            // Update the Method Static Control text

            if (JSP.MethodMode() == SINGLE)
            {
                ControlScdl = GetDlgItem (ScdlDialog, IDSC_METHOD);
                SetWindowText (ControlScdl, "Single Parallel Particle Collision");
            }

            // Create the list and set the default value for the initial solution static control

            ControlScdl = GetDlgItem (ScdlDialog, IDSC_INITIAL_SOLUTION);
            SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)ISList[JSP.InitialSolutionMethod()]);

            // Update the First Method Group Box text

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_1);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Particle Collision parameters");

            // Show the Particle Collision Dialog Box

            if (PCDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (PCDialog, SW_SHOW);
            }

            // Show the Taboo Search of Particle Collision Dialog Box

            if (PCTSDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (PCTSDialog, SW_SHOW);
            }

            // Show the solution and the specified critical path in a Gantt graph

            ShowGantt (ScdlDialog);

            return TRUE;

        case PARTICLE_SWARM:

            // Set the default value for the initial solution static control

            ControlScdl = GetDlgItem (ScdlDialog, IDSC_INITIAL_SOLUTION);
            SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)ISVecList[JSP.InitialSolutionVecMethod()]);

            // Update the first method group box text

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_1);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Particle Swarm parameters");

            // Update the first method static control text

            if (JSP.MethodMode() == SINGLE)
            {
                ControlScdl = GetDlgItem (ScdlDialog, IDSC_METHOD);
                SetWindowText (ControlScdl, "Single Particle Swarm");
            }

            if (PSDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (PSDialog, SW_SHOW);
            }

            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

bool IDCB_METHOD02_CBN_SELENDOK ()
{
    HideSecondAndThirdMethodsDialogBoxes ();

    // Enable the Third Method combo box

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_03);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"  -----  Third Method  ----");
    ComboBox_Enable (ControlScdl, TRUE);

    // Disable the Scheduler button

    ControlScdl = GetDlgItem (ScdlDialog, IDC_SCHEDULER);
    Button_Enable (ControlScdl, FALSE);

    // Get the selected item and update the method variable

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_02);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);
    JSP.ScMethod (lResult);

    switch (lResult)
    {
        case TABOO_SEARCH:

            // Update the second method group box text

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_2);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Taboo Search parameters");

            // Show the Second Taboo Search Dialog Box

            if (ScTSDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (ScTSDialog, SW_SHOW);
            }

            return TRUE;

        case PARALLEL_TABOO_SEARCH:

            // Update the second method group box text

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_2);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Parallel Taboo Search parameters");

            // Show the Second Parallel Taboo Search Dialog Box

            if (ScPTSDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (ScPTSDialog, SW_SHOW);
            }

            return TRUE;

        case PARTICLE_SWARM:

            // Update the second method group box text

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_2);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Similar Particle Swarm parameters");

            // Show the Second Similar Particle Swarm Dialog Box

            if (ScPSDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (ScPSDialog, SW_SHOW);
            }

            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

bool IDCB_METHOD03_CBN_SELENDOK ()
{
    HideThirdMethodsDialogBoxes ();

    // Enable the Scheduler button

    ControlScdl = GetDlgItem (ScdlDialog, IDC_SCHEDULER);
    Button_Enable (ControlScdl, TRUE);

    // Get the selected item and update the third method variable

    ControlScdl = GetDlgItem (ScdlDialog, IDCB_METHOD_03);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);
    JSP.ThMethod (lResult);

    switch (lResult)
    {
        case TABOO_SEARCH:

            // Update the Third Method Group Box text

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_3);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Taboo Search parameters");

            // Show the Third Taboo Search Dialog Box

            if (ThTSDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (ThTSDialog, SW_SHOW);
            }

            return TRUE;

        case PARALLEL_TABOO_SEARCH:

            // Update the Third Method Group Box text

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_3);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Parallel Taboo Search parameters");

            // Show the Third Parallel Taboo Search Dialog Box

            if (ThPTSDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (ThPTSDialog, SW_SHOW);
            }

            return TRUE;

        case PARTICLE_SWARM:

            // Update the Third Method Group Box text

            ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_3);
            SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Similar Particle Swarm parameters");

            // Show the Third Similar Particle Swarm Dialog Box

            if (ThPSDialog != NULL)
            {
                ShowStatus = TRUE;
                ShowWindow (ThPSDialog, SW_SHOW);
            }

            return TRUE;

        default:
            return FALSE;
    }

    return TRUE;
}

bool IDC_SCHEDULER_BN_CLICKED ()
{
    Message = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_WAIT_MESSAGE), ScdlDialog, MessageProc);

    if (Message != NULL)
    {
        ShowWindow (Message, SW_SHOW);
    }
    else
    {
        MessageBox (ScdlDialog, "CreateDialog for Taboo Search dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    // Update the previous makespan static control text

    SetDlgItemInt (ScdlDialog, IDSC_PREVIOUS_MAKESPAN, (int)JSP.Makespan(), FALSE);

    switch (JSP.MethodMode())
    {
        case SINGLE:
            JSP.Scheduler ();
            break;

        case HYBRID:
            JSP.HybridScheduler ();
            break;

        default:
            MessageBox (ScdlDialog, "The Method Mode is not valide !", "Warning", MB_OK | MB_ICONINFORMATION);
            break;
    }

    DestroyWindow (Message);

    // Update the results texts

    SetDlgItemInt (ScdlDialog, IDSC_MAKESPAN, (int)JSP.Makespan(), FALSE);
    SetDlgItemInt (ScdlDialog, IDSC_SOLUTIONS_EVAL, JSP.NSolutionsEvaluated(), FALSE);
    SetDlgItemInt (ScdlDialog, IDSC_COPUTING_TIME, (int)JSP.CPUTime(), FALSE);

    if (SolutionGanttDialog != NULL)
    {
        DestroyWindow (SolutionGanttDialog);
    }

    SolutionGanttDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SOLUTION_GANTT), ScdlDialog, SolutionGanttProc);

    if (SolutionGanttDialog != NULL)
    {
        SetWindowText (SolutionGanttDialog, "Gantt Solution");
        ShowWindow (SolutionGanttDialog, SW_SHOW);
    }else
    {
        MessageBox (ScdlDialog, "CreateDialog for solution dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }

    // Set the Initial Solution and the Vector of Initial Solutions to current

    if (JSP.Method() == TABOO_SEARCH)
    {
        JSP.InitialSolutionMethod (CURRENT_SOLUTION);
        ControlScdl = GetDlgItem (TSDialog, IDCB_TS_INITIAL_SOLUTION);
        ComboBox_SetCurSel (ControlScdl, JSP.InitialSolutionMethod());
    }
    else
    {
        JSP.InitialSolutionMethod (CURRENT_SOLUTION);
        ControlScdl = GetDlgItem (TSDialog, IDCB_TS_INITIAL_SOLUTION);
        ComboBox_SetCurSel (ControlScdl, JSP.InitialSolutionMethod());

        JSP.InitialSolutionVecMethod (CURRENT_SOLUTION_VECTOR);
        ControlScdl = GetDlgItem (PSDialog, IDCB_PS_INITIAL_SOLUTION);
        ComboBox_SetCurSel (ControlScdl, JSP.InitialSolutionVecMethod());

        ControlScdl = GetDlgItem (PTSDialog, IDCB_PTS_INITIAL_SOLUTION);
        ComboBox_SetCurSel (ControlScdl, JSP.InitialSolutionVecMethod());

        // Update the Solution Index Combo Box list

        ControlScdl = GetDlgItem (PTSDialog, IDCB_SOLUTION_INDEX);
        ComboBox_SetCurSel (ControlScdl, JSP.SolutionIndex());

        ControlScdl = GetDlgItem (PSDialog, IDCB_SOLUTION_INDEX);
        ComboBox_SetCurSel (ControlScdl, JSP.SolutionIndex());
    }

    return TRUE;
}

bool IDC_SHOW_NGH_GANTT_BN_CLICKED ()
{
    ShowNeighborhoodGantt (ScdlDialog);
    return TRUE;
}

bool ICDB_SOLUTION_INDEX_CBN_SELENDOK (HWND hWnd)
{
    char text[33];
    HWND hWndOwner = GetParent(hWnd);

    // Get the selected item and update the Solution Index variable

    ControlScdl = GetDlgItem (hWnd, IDCB_SOLUTION_INDEX);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);

    JSP.SolutionIndex (lResult);

    // Update the solution

    JSP.Scdl (JSP.VecScdl()[JSP.SolutionIndex()]);
    JSP.TSC (JSP.VecTSC()[JSP.SolutionIndex()]);
    JSP.WPC (JSP.VecWPC()[JSP.SolutionIndex()]);

    JSP.TimingScdlSR ();
    JSP.FindCriticalPath ();
    JSP.CriticalPathIndex (0);

    // Update the Critical Path Combo Box List

    ControlScdl = GetDlgItem (PTSDialog, IDCB_PTS01_CRITICAL_PATH);
    SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

    for (UINT count=0; count<JSP.CriticalPath().size(); count++)
    {
        itoa (count, text, 10);
        ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
    }

    ComboBox_SetCurSel (ControlScdl, 0);

    JSP.BlocksOnCriticalPath ();

    ShowGantt (hWndOwner);

    return TRUE;
}


bool TSDlgProc_WM_INITDIALOG (HWND hWnd)
{
    // Generate the list of the Initial Solution combo box

    ControlScdl = GetDlgItem (hWnd, IDCB_TS_INITIAL_SOLUTION);

    for (UINT count=0; count<ISList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)ISList[count]);
    }

    // Generate the list of the Neighborhood Method Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_TS01_NGH_METHOD);

    for (UINT count=0; count<CPOperatorList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)CPOperatorList[count]);
    }

    return TRUE;
}

bool TSDlgProc_WM_SHOWWINDOW ()
{
    if (ShowStatus == TRUE)
    {
        // Update the the neighborhood combo box text with the current value

        ControlScdl = GetDlgItem (TSDialog, IDCB_TS01_NGH_METHOD);
        ComboBox_SetCurSel (ControlScdl, JSP.NghMethod());

        // Show the tenure and the max number of iterations current values

        SetDlgItemInt (TSDialog, IDET_TS01_TENURE, JSP.Tenure(), FALSE);
        SetDlgItemInt (TSDialog, IDET_TS01_MAXITE, JSP.TSNMaxIte(), FALSE);

        // Update the Critical Path Combo Box List

        ControlScdl = GetDlgItem (TSDialog, IDCB_TS01_CRITICAL_PATH);
        SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

        char text[33];

        for (UINT count=0; count<JSP.CriticalPath().size(); count++)
        {
            itoa (count, text, 10);
            ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
        }

        ComboBox_SetCurSel (ControlScdl, 0);
    }
    else
    {
        ControlScdl = GetDlgItem (TSDialog, IDCB_TS_INITIAL_SOLUTION);
        ComboBox_SetCurSel (ControlScdl, CURRENT_SOLUTION);

        JSP.InitialSolutionMethod (CURRENT_SOLUTION);
    }

    return TRUE;
}

bool IDCB_TS01_INITIAL_SOLUTION_CBN_SELENDOK ()
{
    HWND hWndOwner = GetParent(TSDialog);

    // Get the selected item and update the method variable

    ControlScdl = GetDlgItem (TSDialog, IDCB_TS_INITIAL_SOLUTION);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);
    JSP.InitialSolutionMethod (lResult);

    // Set the default value four the initial solution text

    ControlScdl = GetDlgItem (hWndOwner, IDSC_INITIAL_SOLUTION);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)ISList[JSP.InitialSolutionMethod()]);

    // Generate an initial solution by the defined method
    // Find all critical paths for this solution
    // Update the Critical Path combo box list
    // Update the critical path index
    // Find the blocks of the specified critical path

    GenerateTabooSearchInitialSolution ();

    // Show the solution and the specified critical path in a Gantt graph

    ShowGantt (hWndOwner);

    return TRUE;
}

bool IDCB_TS01_CRITICAL_PATH_CBN_SELENDOK ()
{
    HWND hWndOwner = GetParent(TSDialog);

    // Update the critical path index

    ControlScdl = GetDlgItem (TSDialog, IDCB_TS01_CRITICAL_PATH);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);
    JSP.CriticalPathIndex(lResult);

    // Find the blocks of the specified critical path

    JSP.BlocksOnCriticalPath ();

    // Show the solution and the specified critical path in a Gantt graph

    ShowGantt (hWndOwner);

    return TRUE;
}

bool IDCB_TS01_NGH_METHOD_CBN_SELENDOK ()
{
    return TRUE;
}

bool IDCB_TS01_TENURE_EN_CHANGE ()
{
    BOOL lpTranslated;

    UINT lResult =  GetDlgItemInt (TSDialog, IDET_TS01_TENURE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Tenure of Taboo Search Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.Tenure (lResult);
    }

    return TRUE;
}

bool IDCB_TS01_MAXITE_EN_CHANGE ()
{
    BOOL lpTranslated;

    UINT lResult =  GetDlgItemInt (TSDialog, IDET_TS01_MAXITE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Max Number of Iterations Whithout Upgrade of Taboo Search Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.TSNMaxIte (lResult);
    }

    return TRUE;
}


bool PCDlgProc_WM_INITDIALOG (HWND hWnd)
{
    // Generate the list of the Initial Solution combo box

    ControlScdl = GetDlgItem (hWnd, IDCB_INITIAL_SOLUTION);

    for (UINT count=0; count<ISList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)ISList[count]);
    }

    // Generate the list of the Perturbation Method Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_PC01_PERTURBATION_METHOD);

    for (UINT count=0; count<PerturbationMtdList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)PerturbationMtdList[count]);
    }

    // Generate the list of the Exploitation Method Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_PC01_EXPLOITATION_METHOD);

    for (UINT count=0; count<ExploitationMtdList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)ExploitationMtdList[count]);
    }

    return TRUE;
}

bool PCDlgProc_WM_SHOWWINDOW ()
{
    char text[33];

    if (ShowStatus == TRUE)
    {
        // Update the the Initial Solution Combo Box text with the current value

        ControlScdl = GetDlgItem (PCDialog, IDCB_INITIAL_SOLUTION);
        ComboBox_SetCurSel (ControlScdl, JSP.InitialSolutionMethod());

        // Update the the Perturbation Method Combo Box text with the current value

        ControlScdl = GetDlgItem (PCDialog, IDCB_PC01_PERTURBATION_METHOD);
        ComboBox_SetCurSel (ControlScdl, JSP.PerturbationMethod());

        // Update the the Exploitation Method Combo Box text with the current value

        ControlScdl = GetDlgItem (PCDialog, IDCB_PC01_EXPLOITATION_METHOD);
        ComboBox_SetCurSel (ControlScdl, JSP.ExploitationMethod());

        // Show the Max Number of Iterations current value

        SetDlgItemInt (PCDialog, IDET_PC01_MAXITE, JSP.PCNMaxIte(), FALSE);

        // Update the Solution Index Combo Box list

        ControlScdl = GetDlgItem (PCDialog, IDCB_SOLUTION_INDEX);
        SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

        for (UINT count=0; count<JSP.PopulationSize(); count++)
        {
            itoa (count, text, 10);
            ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
        }

        ComboBox_SetCurSel (ControlScdl, JSP.SolutionIndex());
    }
    else
    {
        ControlScdl = GetDlgItem (PCDialog, IDCB_INITIAL_SOLUTION);
        ComboBox_SetCurSel (ControlScdl, CURRENT_SOLUTION);

        JSP.InitialSolutionMethod (CURRENT_SOLUTION);
    }

    return TRUE;
}

bool IDCB_PC01_INITIAL_SOLUTION_CBN_SELENDOK ()
{
    HWND hWndOwner = GetParent(PCDialog);

    // Get the selected item and update the method variable

    ControlScdl = GetDlgItem (PCDialog, IDCB_INITIAL_SOLUTION);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);
    JSP.InitialSolutionMethod (lResult);

    // Set the default value four the initial solution text

    ControlScdl = GetDlgItem (hWndOwner, IDSC_INITIAL_SOLUTION);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)ISList[JSP.InitialSolutionMethod()]);

    // Generate an initial solution by the defined method
    // Find all critical paths for this solution
    // Update the Critical Path combo box list
    // Update the critical path index
    // Find the blocks of the specified critical path

    GenerateTabooSearchInitialSolution ();

    // Show the solution and the specified critical path in a Gantt graph

    ShowGantt (hWndOwner);

    return TRUE;
}

bool IDCB_PC01_MAXITE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (PCDialog, IDET_PC01_MAXITE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Max Number of Iterations of Particle Collision Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.PCNMaxIte (lResult);
    }

    return TRUE;
}


bool PCTSDlgProc_WM_INITDIALOG (HWND hWnd)
{
    // Generate the list of the Neighborhood Method Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_TS01_NGH_METHOD);

    for (UINT count=0; count<CPOperatorList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)CPOperatorList[count]);
    }

    return TRUE;
}

bool PCTSDlgProc_WM_SHOWWINDOW ()
{
    if (ShowStatus == TRUE)
    {
        // Update the the neighborhood combo box text with the current value

        ControlScdl = GetDlgItem (PCTSDialog, IDCB_TS01_NGH_METHOD);
        ComboBox_SetCurSel (ControlScdl, JSP.NghMethod());

        // Show the tenure and the max number of iterations current values

        SetDlgItemInt (PCTSDialog, IDET_TS01_TENURE, JSP.Tenure(), FALSE);
        SetDlgItemInt (PCTSDialog, IDET_TS01_MAXITE, JSP.TSNMaxIte(), FALSE);

        // Update the Critical Path Combo Box List

        ControlScdl = GetDlgItem (PCTSDialog, IDCB_TS01_CRITICAL_PATH);
        SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

        char text[33];

        for (UINT count=0; count<JSP.CriticalPath().size(); count++)
        {
            itoa (count, text, 10);
            ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
        }

        ComboBox_SetCurSel (ControlScdl, 0);
    }

    return TRUE;
}

bool IDCB_TSPC_CRITICAL_PATH_CBN_SELENDOK ()
{
    HWND hWndOwner = GetParent(PCTSDialog);

    // Update the critical path index

    ControlScdl = GetDlgItem (PCTSDialog, IDCB_TS01_CRITICAL_PATH);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);
    JSP.CriticalPathIndex(lResult);

    // Find the blocks of the specified critical path

    JSP.BlocksOnCriticalPath ();

    // Show the solution and the specified critical path in a Gantt graph

    ShowGantt (hWndOwner);

    return TRUE;
}

bool IDCB_TSPC_NGH_METHOD_CBN_SELENDOK ()
{
    return TRUE;
}

bool IDCB_TSPC_TENURE_EN_CHANGE ()
{
    BOOL lpTranslated;

    UINT lResult =  GetDlgItemInt (PCTSDialog, IDET_TS01_TENURE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Tenure of Taboo Search Exploitation Method Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.Tenure (lResult);
    }

    return TRUE;
}

bool IDCB_TSPC_MAXITE_EN_CHANGE ()
{
    BOOL lpTranslated;

    UINT lResult =  GetDlgItemInt (PCTSDialog, IDET_TS01_MAXITE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Max Number of Iterations Whithout Upgrade of Taboo Search Exploitation Method Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.TSNMaxIte (lResult);
    }

    return TRUE;
}


bool PTSDlgProc_WM_INITDIALOG (HWND hWnd)
{
    // Generate the list of the Initial Solution Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_PTS_INITIAL_SOLUTION);

    for (UINT count=0; count<ISVecList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)ISVecList[count]);
    }

    // Generate the list of the Neighborhood Method Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_PTS01_NGH_METHOD);

    for (UINT count=0; count<CPOperatorList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)CPOperatorList[count]);
    }

    return TRUE;
}

bool PTSDlgProc_WM_SHOWWINDOW ()
{
    char text[33];
    HWND hWndOwner = GetParent(PTSDialog);

    if (ShowStatus == TRUE)
    {
        // Update the neighborhood combo box with the current value

        ControlScdl = GetDlgItem (PTSDialog, IDCB_PTS01_NGH_METHOD);
        ComboBox_SetCurSel (ControlScdl, JSP.NghMethod());

        // Show the tenure and the max number of iterations current values

        SetDlgItemInt (PTSDialog, IDET_PTS01_TENURE, JSP.Tenure(), FALSE);
        SetDlgItemInt (PTSDialog, IDET_PTS01_MAXITE, JSP.TSNMaxIte(), FALSE);

        // Generate or update the solution by the specifyed method

        JSP.InitialSolutionVector ();

        // Find all critical paths

        JSP.FindCriticalPath ();
        JSP.CriticalPathIndex(0);

        // Update the Critical Path Combo Box List

        ControlScdl = GetDlgItem (PTSDialog, IDCB_PTS01_CRITICAL_PATH);
        SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

        for (UINT count=0; count<JSP.CriticalPath().size(); count++)
        {
            itoa (count, text, 10);
            ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
        }

        ComboBox_SetCurSel (ControlScdl, 0);

        // Find de blocks on the selected critical path

        JSP.BlocksOnCriticalPath ();

        // Show the population size current value

        SetDlgItemInt (PTSDialog, IDET_PTS01_POPULATION_SIZE, JSP.PopulationSize(), FALSE);

        // Disable the Population Size Combo Box

        ControlScdl = GetDlgItem (PTSDialog, IDET_PTS01_POPULATION_SIZE);
        Edit_Enable (ControlScdl, FALSE);

        // Update the Solution Index Combo Box list

        ControlScdl = GetDlgItem (PTSDialog, IDCB_SOLUTION_INDEX);
        SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

        for (UINT count=0; count<JSP.PopulationSize(); count++)
        {
            itoa (count, text, 10);
            ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
        }

        ComboBox_SetCurSel (ControlScdl, JSP.SolutionIndex());

        // Show the solution in the Gantt Graph

        ShowGantt (hWndOwner);
    }
    else
    {
        ControlScdl = GetDlgItem (PTSDialog, IDCB_PTS_INITIAL_SOLUTION);
        ComboBox_SetCurSel (ControlScdl, CURRENT_SOLUTION_VECTOR);

        JSP.InitialSolutionVecMethod (CURRENT_SOLUTION_VECTOR);
    }

    return TRUE;
}

bool IDCB_PTS01_INITIAL_SOLUTION_CBN_SELENDOK ()
{
    HWND hWndOwner = GetParent(PTSDialog);

    // Get the selected item and update the method variable

    ControlScdl = GetDlgItem (PTSDialog, IDCB_PTS_INITIAL_SOLUTION);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);
    JSP.InitialSolutionVecMethod (lResult);

    // Set the default value four the initial solution text

    ControlScdl = GetDlgItem (hWndOwner, IDSC_INITIAL_SOLUTION);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)ISVecList[JSP.InitialSolutionVecMethod()]);

    // Enable or disable the Population Size Combo Box

    ControlScdl = GetDlgItem (PTSDialog, IDET_PTS01_POPULATION_SIZE);

    switch (JSP.InitialSolutionVecMethod())
    {
        case RANDOM_INITIAL_SOLUTION_VECTOR:
            Edit_Enable (ControlScdl, TRUE);
            break;

        default:
            Edit_Enable (ControlScdl, FALSE);
            break;
    }

    // Generate a vector of initial solutions by the defined method and show the best solution of this vector

    GenerateAndShowInitialVectorOfSolutions (PTSDialog, IDCB_PTS01_CRITICAL_PATH);

    // Update the popualtion size current value

    SetDlgItemInt (PTSDialog, IDET_PTS01_POPULATION_SIZE, JSP.PopulationSize(), FALSE);

    // Update the Solution Index Combo Box text

    ControlScdl = GetDlgItem (PTSDialog, IDCB_SOLUTION_INDEX);
    ComboBox_SetCurSel (ControlScdl, JSP.SolutionIndex());

    return TRUE;
}

bool IDET_PTS01_POPULATION_SIZE_EN_CHANGE ()
{
    char text[33];
    BOOL lpTranslated;

    // Get the value and update the population size variable

    lResult =  GetDlgItemInt (PTSDialog, IDET_PTS01_POPULATION_SIZE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Population size of Parallel Taboo Search Dialog not updated !!!");
        return FALSE;
    }

    if (JSP.PopulationSize() != (UINT)lResult && JSP.Method() == PARALLEL_TABOO_SEARCH)
    {
        JSP.PopulationSize (lResult);

        // Generate a vector of initial solutions by the defined method and show the best solution of this vector

        GenerateAndShowInitialVectorOfSolutions (PTSDialog, IDCB_PTS01_CRITICAL_PATH);

        // Update the Solution Index Combo Box list

        ControlScdl = GetDlgItem (PTSDialog, IDCB_SOLUTION_INDEX);
        SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

        for (UINT count=0; count<JSP.PopulationSize(); count++)
        {
            itoa (count, text, 10);
            ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
        }

        ComboBox_SetCurSel (ControlScdl, JSP.SolutionIndex());

        // Update the population size values

        SetDlgItemInt (ScPTSDialog, IDET_PTS02_POPULATION_SIZE, JSP.PopulationSize(), FALSE);
        SetDlgItemInt (ThPTSDialog, IDET_PTS03_POPULATION_SIZE, JSP.PopulationSize(), FALSE);
        SetDlgItemInt (ScPSDialog, IDET_PS02_POPULATION_SIZE, JSP.PopulationSize(), FALSE);
        SetDlgItemInt (ThPSDialog, IDET_PS03_POPULATION_SIZE, JSP.PopulationSize(), FALSE);
    }

    return TRUE;
}

bool IDCB_PTS01_CRITICAL_PATH_CBN_SELENDOK ()
{
    HWND hWndOwner = GetParent(PTSDialog);

    // Update the critical path index

    ControlScdl = GetDlgItem (PTSDialog, IDCB_PTS01_CRITICAL_PATH);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);
    JSP.CriticalPathIndex(lResult);

    // Find the blocks of the specified critical path

    JSP.BlocksOnCriticalPath ();

    // Show the solution and the specified critical path in a Gantt graph

    ShowGantt (hWndOwner);

    return TRUE;
}

bool IDCB_PTS01_NGH_METHOD_CBN_SELENDOK ()
{
    return TRUE;
}

bool IDET_PTS01_TENURE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (PTSDialog, IDET_PTS01_TENURE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Tenure of Parallel Taboo Search Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.Tenure (lResult);
        JSP.FtTenure (lResult);
    }

    return TRUE;
}

bool IDET_PTS01_MAXITE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (PTSDialog, IDET_PTS01_MAXITE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Maximum number of iterations of Parallel Taboo Search dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.TSNMaxIte (lResult);
        JSP.FtTSNMaxIte (lResult);
    }

    return TRUE;
}


bool ScPTSDlgProc_WM_INITDIALOG (HWND hWnd)
{
    // Generate the list of the Second Neighborhood Method Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_PTS02_NGH_METHOD);

    for (UINT count=0; count<CPOperatorList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)CPOperatorList[count]);
    }

    return TRUE;
}

bool ScPTSDlgProc_WM_SHOWWINDOW ()
{
    char text[33];

    // Update the neighborhood combo box with the current value

    ControlScdl = GetDlgItem (ScPTSDialog, IDCB_PTS02_NGH_METHOD);
    ComboBox_SetCurSel (ControlScdl, JSP.ScNghMethod());

    // Show the tenure and the max number of iterations current values

    SetDlgItemInt (ScPTSDialog, IDET_PTS02_TENURE, JSP.ScTenure(), FALSE);
    SetDlgItemInt (ScPTSDialog, IDET_PTS02_MAXITE, JSP.ScTSNMaxIte(), FALSE);

    // Update the Critical Path Combo Box List

    ControlScdl = GetDlgItem (ScPTSDialog, IDCB_PTS02_CRITICAL_PATH);
    SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

    itoa (0, text, 10);
    ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
    ComboBox_SetCurSel (ControlScdl, 0);

    // Show the population size current value

    SetDlgItemInt (ScPTSDialog, IDET_PTS02_POPULATION_SIZE, JSP.PopulationSize(), FALSE);

    // Disable the Population Size Combo Box

    ControlScdl = GetDlgItem (ScPTSDialog, IDET_PTS02_POPULATION_SIZE);
    Edit_Enable (ControlScdl, FALSE);

    return TRUE;
}

bool IDCB_PTS02_NGH_METHOD_CBN_SELENDOK ()
{
    return TRUE;
}

bool IDET_PTS02_TENURE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (ScPTSDialog, IDET_PTS02_TENURE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Tenure of the Second Parallel Taboo Search Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.ScTenure (lResult);
    }

    return TRUE;
}

bool IDET_PTS02_MAXITE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (ScPTSDialog, IDET_PTS02_MAXITE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Maximum number of iterations of the Second Parallel Taboo Search dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.ScTSNMaxIte (lResult);
    }

    return TRUE;
}


bool ThPTSDlgProc_WM_INITDIALOG (HWND hWnd)
{
    // Generate the list of the Third Neighborhood Method Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_PTS03_NGH_METHOD);

    for (UINT count=0; count<CPOperatorList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)CPOperatorList[count]);
    }

    return TRUE;
}

bool ThPTSDlgProc_WM_SHOWWINDOW ()
{
    char text[33];

    // Update the Third Neighborhood Combo Box with the current value

    ControlScdl = GetDlgItem (ThPTSDialog, IDCB_PTS03_NGH_METHOD);
    ComboBox_SetCurSel (ControlScdl, JSP.ThNghMethod());

    // Show the tenure and the max number of iterations current values

    SetDlgItemInt (ThPTSDialog, IDET_PTS03_TENURE, JSP.ThTenure(), FALSE);
    SetDlgItemInt (ThPTSDialog, IDET_PTS03_MAXITE, JSP.ThTSNMaxIte(), FALSE);

    // Update the Critical Path Combo Box list

    ControlScdl = GetDlgItem (ThPTSDialog, IDCB_PTS03_CRITICAL_PATH);
    SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

    itoa (0, text, 10);
    ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
    ComboBox_SetCurSel (ControlScdl, 0);

    // Show the population size current value

    SetDlgItemInt (ThPTSDialog, IDET_PTS03_POPULATION_SIZE, JSP.PopulationSize(), FALSE);

    // Disable the Population Size Combo Box

    ControlScdl = GetDlgItem (ThPTSDialog, IDET_PTS03_POPULATION_SIZE);
    Edit_Enable (ControlScdl, FALSE);

    return TRUE;
}

bool IDCB_PTS03_NGH_METHOD_CBN_SELENDOK ()
{
    return TRUE;
}

bool IDET_PTS03_TENURE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (ThPTSDialog, IDET_PTS03_TENURE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Tenure of the Third Parallel Taboo Search Dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.ThTenure (lResult);
    }

    return TRUE;
}

bool IDET_PTS03_MAXITE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (ThPTSDialog, IDET_PTS03_MAXITE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Maximum number of iterations of the Third Parallel Taboo Search dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.ThTSNMaxIte (lResult);
    }

    return TRUE;
}


bool PSDlgProc_WM_INITDIALOG (HWND hWnd)
{
    // Generate the list of the Initial Vector of Solutions Method combo box

    ControlScdl = GetDlgItem (hWnd, IDCB_PS_INITIAL_SOLUTION);

    for (UINT count=0; count<ISVecList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)ISVecList[count]);
    }

    // Generate the list of the Crossover Method combo box

    ControlScdl = GetDlgItem (hWnd, IDCB_PS01_CROSSOVER_METHOD);

    for (UINT count=0; count<CrossoverMtdList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)CrossoverMtdList[count]);
    }

    // Generate the list of the Mutation Method combo box

    ControlScdl = GetDlgItem (hWnd, IDCB_PS01_MUTATION_METHOD);

    for (UINT count=0; count<MutationMtdList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)MutationMtdList[count]);
    }

    return TRUE;
}

bool PSDlgProc_WM_SHOWWINDOW ()
{
    char text[33];
    HWND hWndOwner = GetParent(PSDialog);

    if (ShowStatus == TRUE)
    {
        // Update de crossover combo box with the current value

        ControlScdl = GetDlgItem (PSDialog, IDCB_PS01_CROSSOVER_METHOD);
        ComboBox_SetCurSel (ControlScdl, JSP.CrossoverMethod());

        // Update de mutation combo box with the current value

        ControlScdl = GetDlgItem (PSDialog, IDCB_PS01_MUTATION_METHOD);
        ComboBox_SetCurSel (ControlScdl, JSP.MutationMethod());

        // Update de mutation percent edit text with the current value

        SetDlgItemInt (PSDialog, IDET_PS01_MUTATION_PERCENT, JSP.MutationPercent(), FALSE);

        // Show the max number of iterations current value

        SetDlgItemInt (PSDialog, IDET_PS01_MAXITE, JSP.SPSNMaxIte(), FALSE);

        // Generate or update the solution by the specifyed method

        JSP.InitialSolutionVector ();

        // Find all critical paths

        JSP.FindCriticalPath ();

        // Update the Critical Path index

        JSP.CriticalPathIndex(0);

        // Find de blocks on the selected critical path

        JSP.BlocksOnCriticalPath ();

        // Show the population size current value

        SetDlgItemInt (PSDialog, IDET_PS01_POPULATION_SIZE, JSP.PopulationSize(), FALSE);

        // Disable the Population Size Combo Box

        ControlScdl = GetDlgItem (PSDialog, IDET_PS01_POPULATION_SIZE);
        Edit_Enable (ControlScdl, FALSE);

        // Update the Solution Index Combo Box list

        ControlScdl = GetDlgItem (PSDialog, IDCB_SOLUTION_INDEX);
        SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

        for (UINT count=0; count<JSP.PopulationSize(); count++)
        {
            itoa (count, text, 10);
            ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
        }

        ComboBox_SetCurSel (ControlScdl, JSP.SolutionIndex());

        // Show the solution in a Gantt graph

        ShowGantt (hWndOwner);
    }
    else
    {
        ControlScdl = GetDlgItem (PSDialog, IDCB_PS_INITIAL_SOLUTION);
        ComboBox_SetCurSel (ControlScdl, CURRENT_SOLUTION_VECTOR);

        JSP.InitialSolutionVecMethod (CURRENT_SOLUTION_VECTOR);
    }

    return TRUE;
}

bool IDCB_PS_INITIAL_SOLUTION_CBN_SELENDOK ()
{
    HWND hWndOwner = GetParent(TSDialog);

    // Get the selected item and update the method variable

    ControlScdl = GetDlgItem (PSDialog, IDCB_PS_INITIAL_SOLUTION);
    lResult = SendMessage (ControlScdl, CB_GETCURSEL, 0, 0);
    JSP.InitialSolutionVecMethod (lResult);

    // Set the default value four the initial solution text

    ControlScdl = GetDlgItem (hWndOwner, IDSC_INITIAL_SOLUTION);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)ISVecList[JSP.InitialSolutionVecMethod()]);

    // Enable or disable the Population Size Combo Box

    ControlScdl = GetDlgItem (PSDialog, IDET_PS01_POPULATION_SIZE);

    switch (JSP.InitialSolutionVecMethod())
    {
        case RANDOM_INITIAL_SOLUTION_VECTOR:
            Edit_Enable (ControlScdl, TRUE);
            break;

        default:
            Edit_Enable (ControlScdl, FALSE);
            break;
    }

    // Generate a vector of initial solutions by the defined method and show the best solution of this vector

    GenerateAndShowInitialVectorOfSolutions (PSDialog, IDC_STATIC);

    // Update the Popualtion Size Edit Control text

    SetDlgItemInt (PSDialog, IDET_PS01_POPULATION_SIZE, JSP.PopulationSize(), FALSE);

    // Update the Solution Index Combo Box text

    ControlScdl = GetDlgItem (PSDialog, IDCB_SOLUTION_INDEX);
    ComboBox_SetCurSel (ControlScdl, JSP.SolutionIndex());

    return TRUE;
}

bool IDET_PS01_POPULATION_SIZE_EN_CHANGE ()
{
    char text[33];
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (PSDialog, IDET_PS01_POPULATION_SIZE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Maximum number of iterations not updated !!!");
        return FALSE;
    }

    if (JSP.PopulationSize() != (UINT)lResult && JSP.Method() == PARTICLE_SWARM)
    {
        JSP.PopulationSize (lResult);

        // Generate a vector of initial solutions by the defined method and show the best solution of this vector

        GenerateAndShowInitialVectorOfSolutions (PSDialog, IDC_STATIC);

        // Update the Solution Index Combo Box list

        ControlScdl = GetDlgItem (PSDialog, IDCB_SOLUTION_INDEX);
        SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

        for (UINT count=0; count<JSP.PopulationSize(); count++)
        {
            itoa (count, text, 10);
            ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
        }

        ComboBox_SetCurSel (ControlScdl, JSP.SolutionIndex());

        // Update the population size values

        SetDlgItemInt (ScPTSDialog, IDET_PTS02_POPULATION_SIZE, JSP.PopulationSize(), FALSE);
        SetDlgItemInt (ThPTSDialog, IDET_PTS03_POPULATION_SIZE, JSP.PopulationSize(), FALSE);
        SetDlgItemInt (ScPSDialog, IDET_PS02_POPULATION_SIZE, JSP.PopulationSize(), FALSE);
        SetDlgItemInt (ThPSDialog, IDET_PS03_POPULATION_SIZE, JSP.PopulationSize(), FALSE);
    }

    return TRUE;
}

bool IDET_PS01_MUTATION_PERCENT_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (PSDialog, IDET_PS01_MUTATION_PERCENT, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Mutation percent of Similar Particle Swarm dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.MutationPercent (lResult);
        JSP.FtMutationPercent (lResult);
    }

    return TRUE;
}

bool IDET_PS01_MAXITE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (PSDialog, IDET_PS01_MAXITE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Maximum number of iterations of Similar Particle Swarm dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.SPSNMaxIte (lResult);
        JSP.FtSPSNMaxIte (lResult);
    }

    return TRUE;
}


bool ScPSDlgProc_WM_INITDIALOG (HWND hWnd)
{
    // Generate the list of the Crossover Method Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_PS02_CROSSOVER_METHOD);

    for (UINT count=0; count<CrossoverMtdList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)CrossoverMtdList[count]);
    }

    // Generate the list of the Mutation Method Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_PS02_MUTATION_METHOD);

    for (UINT count=0; count<MutationMtdList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)MutationMtdList[count]);
    }

    return TRUE;
}

bool ScPSDlgProc_WM_SHOWWINDOW ()
{
    // Update de Second Crossover Combo Box with the current value

    ControlScdl = GetDlgItem (ScPSDialog, IDCB_PS02_CROSSOVER_METHOD);
    ComboBox_SetCurSel (ControlScdl, JSP.ScCrossoverMethod());

    // Update de Mutation Combo Box with the current value

    ControlScdl = GetDlgItem (ScPSDialog, IDCB_PS02_MUTATION_METHOD);
    ComboBox_SetCurSel (ControlScdl, JSP.ScMutationMethod());

    // Update de Mutation Percent Edit Text with the current value

    SetDlgItemInt (ScPSDialog, IDET_PS02_MUTATION_PERCENT, JSP.ScMutationPercent(), FALSE);

    // Show the max number of iterations current value

    SetDlgItemInt (ScPSDialog, IDET_PS02_MAXITE, JSP.ScSPSNMaxIte(), FALSE);

    // Show the popualtion size current value

    SetDlgItemInt (ScPSDialog, IDET_PS02_POPULATION_SIZE, JSP.PopulationSize(), FALSE);

    // Disable the Population Size Combo Box

    ControlScdl = GetDlgItem (ScPSDialog, IDET_PS02_POPULATION_SIZE);
    Edit_Enable (ControlScdl, FALSE);

    return TRUE;
}

bool IDET_PS02_MUTATION_PERCENT_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (ScPSDialog, IDET_PS02_MUTATION_PERCENT, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Mutation percent of the Second Similar Particle Swarm dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.ScMutationMethod (lResult);
    }

    return TRUE;
}

bool IDET_PS02_MAXITE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (ScPSDialog, IDET_PS02_MAXITE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Maximum number of iterations of the Second Similar Particle Swarm dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.ScSPSNMaxIte (lResult);
    }

    return TRUE;
}


bool ThPSDlgProc_WM_INITDIALOG (HWND hWnd)
{
    // Generate the list of the Crossover Method Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_PS03_CROSSOVER_METHOD);

    for (UINT count=0; count<CrossoverMtdList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)CrossoverMtdList[count]);
    }

    // Generate the list of the Mutation Method Combo Box

    ControlScdl = GetDlgItem (hWnd, IDCB_PS03_MUTATION_METHOD);

    for (UINT count=0; count<MutationMtdList.size(); count++)
    {
        SendMessage (ControlScdl, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)MutationMtdList[count]);
    }

    return TRUE;
}

bool ThPSDlgProc_WM_SHOWWINDOW ()
{
    // Update de Third Crossover Combo Box with the current value

    ControlScdl = GetDlgItem (ThPSDialog, IDCB_PS03_CROSSOVER_METHOD);
    ComboBox_SetCurSel (ControlScdl, JSP.ThCrossoverMethod());

    // Update de Third Mutation Combo Box with the current value

    ControlScdl = GetDlgItem (ThPSDialog, IDCB_PS03_MUTATION_METHOD);
    ComboBox_SetCurSel (ControlScdl, JSP.ThMutationMethod());

    // Update de Mutation Percent Edit Text with the current value

    SetDlgItemInt (ThPSDialog, IDET_PS03_MUTATION_PERCENT, JSP.ThMutationPercent(), FALSE);

    // Show the max number of iterations current value

    SetDlgItemInt (ThPSDialog, IDET_PS03_MAXITE, JSP.ThSPSNMaxIte(), FALSE);

    // Show the population size current value

    SetDlgItemInt (ThPSDialog, IDET_PS03_POPULATION_SIZE, JSP.PopulationSize(), FALSE);

    // Disable the Population Size Combo Box

    ControlScdl = GetDlgItem (ThPSDialog, IDET_PS03_POPULATION_SIZE);
    Edit_Enable (ControlScdl, FALSE);

    return TRUE;
}

bool IDET_PS03_MUTATION_PERCENT_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (ThPSDialog, IDET_PS03_MUTATION_PERCENT, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Mutation percent of the Third Similar Particle Swarm dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.ThMutationPercent (lResult);
    }

    return TRUE;
}

bool IDET_PS03_MAXITE_EN_CHANGE ()
{
    BOOL lpTranslated;

    lResult =  GetDlgItemInt (ThPSDialog, IDET_PS03_MAXITE, &lpTranslated, FALSE);

    if (lpTranslated == FALSE)
    {
        printf ("\n\n Warning: Maximum number of iterations of the Third Similar Particle Swarm dialog not updated !!!");
        return FALSE;
    }
    else
    {
        JSP.ThSPSNMaxIte (lResult);
    }

    return TRUE;
}


void HideAllMethodsDialogBox ()
{
    ShowStatus = FALSE;

    // Hide the Taboo Search dialog boxes

    if (TSDialog != NULL)
    {
        ShowWindow (TSDialog, SW_HIDE);
    }

    if (ScTSDialog != NULL)
    {
        ShowWindow (ScTSDialog, SW_HIDE);
    }

    if (ThTSDialog != NULL)
    {
        ShowWindow (ThTSDialog, SW_HIDE);
    }

    // Hide the Particle Collision dialog box

    if (PCDialog != NULL)
    {
        ShowWindow (PCDialog, SW_HIDE);
    }

    // Hide the Taboo Search of Particle Collision dialog box

    if (PCTSDialog != NULL)
    {
        ShowWindow (PCTSDialog, SW_HIDE);
    }

    // Hide the Parallel Taboo Search dialog boxes

    if (PTSDialog != NULL)
    {
        ShowWindow (PTSDialog, SW_HIDE);
    }

    if (ScPTSDialog != NULL)
    {
        ShowWindow (ScPTSDialog, SW_HIDE);
    }

    if (ThPTSDialog != NULL)
    {
        ShowWindow (ThPTSDialog, SW_HIDE);
    }

    // Hide the Particle Swarm dialog boxes

    if (PSDialog != NULL)
    {
        ShowWindow (PSDialog, SW_HIDE);
    }

    if (ScPSDialog != NULL)
    {
        ShowWindow (ScPSDialog, SW_HIDE);
    }

    if (ThPSDialog != NULL)
    {
        ShowWindow (ThPSDialog, SW_HIDE);
    }
}

void HideSecondAndThirdMethodsDialogBoxes ()
{
    ShowStatus = FALSE;

    // Hide the Second and Third Taboo Search dialog box

    if (ScTSDialog != NULL)
    {
        ShowWindow (ScTSDialog, SW_HIDE);
    }

    if (ThTSDialog != NULL)
    {
        ShowWindow (ThTSDialog, SW_HIDE);
    }

    // Hide the Second and Third Parallel Taboo Search dialog boxes

    if (ScPTSDialog != NULL)
    {
        ShowWindow (ScPTSDialog, SW_HIDE);
    }

    if (ThPTSDialog != NULL)
    {
        ShowWindow (ThPTSDialog, SW_HIDE);
    }

    // Hide the Second and Third Particle Swarm dialog boxes

    if (ScPSDialog != NULL)
    {
        ShowWindow (ScPSDialog, SW_HIDE);
    }

    if (ThPSDialog != NULL)
    {
        ShowWindow (ThPSDialog, SW_HIDE);
    }
}

void HideThirdMethodsDialogBoxes ()
{
    ShowStatus = FALSE;

    // Hide the Third Taboo Search dialog box

    if (ThTSDialog != NULL)
    {
        ShowWindow (ThTSDialog, SW_HIDE);
    }

    // Hide the Third Parallel Taboo Search dialog boxes

    if (ThPTSDialog != NULL)
    {
        ShowWindow (ThPTSDialog, SW_HIDE);
    }

    // Hide the Third Particle Swarm dialog box

    if (ThPSDialog != NULL)
    {
        ShowWindow (ThPSDialog, SW_HIDE);
    }
}


void GenerateTabooSearchInitialSolution ()
{
    // Generate an initial solution by the current method

    JSP.InitialSolution ();

    // Find all critical paths for this solution

    JSP.FindCriticalPath ();

    // Update the Critical Path combo box list

    ControlScdl = GetDlgItem (TSDialog, IDCB_TS01_CRITICAL_PATH);
    SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

    char text[33];

    for (UINT count=0; count<JSP.CriticalPath().size(); count++)
    {
        itoa (count, text, 10);
        ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
    }

    // Update the critical path index

    ComboBox_SetCurSel (ControlScdl, 0);
    JSP.CriticalPathIndex(0);

    // Find the blocks of the specified critical path

    JSP.BlocksOnCriticalPath ();
}

void GenerateVectorOfInitialSolutions ()
{
    // Generate a vector of random initial solutions

    JSP.InitialSolutionVector ();

    // Find all critical paths for the best solution

    JSP.FindCriticalPath ();

    // Update the critical path variable

    JSP.CriticalPathIndex(0);

    // Find the blocks of the specified critical path

    JSP.BlocksOnCriticalPath ();

    // Update the initial solution to current

    JSP.InitialSolutionMethod (CURRENT_SOLUTION);

    ControlScdl = GetDlgItem (TSDialog, IDCB_TS_INITIAL_SOLUTION);
    ComboBox_SetCurSel (ControlScdl, JSP.InitialSolutionMethod());

    JSP.InitialSolutionVecMethod (CURRENT_SOLUTION_VECTOR);

    ControlScdl = GetDlgItem (PTSDialog, IDCB_PTS_INITIAL_SOLUTION);
    ComboBox_SetCurSel (ControlScdl, JSP.InitialSolutionVecMethod());

    ControlScdl = GetDlgItem (PSDialog, IDCB_PS_INITIAL_SOLUTION);
    ComboBox_SetCurSel (ControlScdl, JSP.InitialSolutionVecMethod());

    JSP.PrevTSC (JSP.TSC());
    JSP.PrevWPC (JSP.WPC());
    JSP.PrevScdl (JSP.Scdl());

    JSP.CurrentTSC (JSP.TSC());
    JSP.CurrentWPC (JSP.WPC());
    JSP.CurrentScdl (JSP.Scdl());

    JSP.PrevVecTSC (JSP.VecTSC());
    JSP.PrevVecWPC (JSP.VecWPC());
    JSP.PrevVecScdl (JSP.VecScdl());

    JSP.CurrentVecTSC (JSP.VecTSC());
    JSP.CurrentVecWPC (JSP.VecWPC());
    JSP.CurrentVecScdl (JSP.VecScdl());
}

void GenerateAndShowInitialVectorOfSolutions (HWND hWnd, const int &CriticalPathComboBoxID)
{
    // generate a vecto of random initial solutions;

    JSP.InitialSolutionVector ();

    // Find all critical paths for the best solution

    JSP.FindCriticalPath ();

    // Update the Critical Path combo box list

    ControlScdl = GetDlgItem (hWnd, CriticalPathComboBoxID);
    SendMessage (ControlScdl, CB_RESETCONTENT, 0, 0);

    char text[33];

    for (UINT count=0; count<JSP.CriticalPath().size(); count++)
    {
        itoa (count, text, 10);
        ComboBox_AddItemData (ControlScdl, (LPARAM)(LPCTSTR)text);
    }

    // Update the critical path index

    ComboBox_SetCurSel (ControlScdl, 0);
    JSP.CriticalPathIndex(0);

    // Find the blocks of the specified critical path

    JSP.BlocksOnCriticalPath ();

    // Show the solution in a Gantt graph

    if (SolutionGanttDialog != NULL)
    {
        DestroyWindow (SolutionGanttDialog);
    }

    SolutionGanttDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SOLUTION_GANTT), ScdlDialog, SolutionGanttProc);

    if (SolutionGanttDialog != NULL)
    {
        SetWindowText (SolutionGanttDialog, "Best solution");
        ShowWindow (SolutionGanttDialog, SW_SHOW);
    }else
    {
        MessageBox (ScdlDialog, "CreateDialog for solution dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }
}

void ShowGantt (HWND hWnd)
{
    if (SolutionGanttDialog != NULL)
    {
        DestroyWindow (SolutionGanttDialog);
    }

    SolutionGanttDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SOLUTION_GANTT), hWnd, SolutionGanttProc);

    if (SolutionGanttDialog != NULL)
    {
        SetWindowText (SolutionGanttDialog, "Initial Solution");
        ShowWindow (SolutionGanttDialog, SW_SHOW);
    }else
    {
        MessageBox (hWnd, "CreateDialog for solution dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }
}

void ShowNeighborhoodGantt (HWND hWnd)
{
    if (NeighborhoodGanttDialog != NULL)
    {
        DestroyWindow (NeighborhoodGanttDialog);
    }

    NeighborhoodGanttDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SOLUTION_GANTT_VECTOR), hWnd, SolutionGanttVecProc);

    if (NeighborhoodGanttDialog != NULL)
    {
        ShowWindow (NeighborhoodGanttDialog, SW_SHOW);
    }else
    {
        MessageBox (hWnd, "CreateDialog for Neighborhood Gantt Dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }
}

void ShowN5Gantt (HWND hWnd)
{
    if (NeighborhoodGanttDialog != NULL)
    {
        DestroyWindow (NeighborhoodGanttDialog);
    }

    NeighborhoodGanttDialog = CreateDialog (GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SOLUTION_GANTT_VECTOR), hWnd, SolutionGanttN5Proc);

    if (NeighborhoodGanttDialog != NULL)
    {
        ShowWindow (NeighborhoodGanttDialog, SW_SHOW);
    }else
    {
        MessageBox (hWnd, "CreateDialog for N5 Gantt Dialog returned NULL !", "Warning", MB_OK | MB_ICONINFORMATION);
    }
}

void HideAllInformation ()
{
    if (SolutionGanttDialog != NULL)
    {
        DestroyWindow (SolutionGanttDialog);
    }

    ControlScdl = GetDlgItem (ScdlDialog, IDSC_PROBLEM_NAME);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

    ControlScdl = GetDlgItem (ScdlDialog, IDSC_PROBLEM_KIND);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

    ControlScdl = GetDlgItem (ScdlDialog, IDSC_JOB_NUMBER);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

    ControlScdl = GetDlgItem (ScdlDialog, IDSC_MCN_NUMBER);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

    ControlScdl = GetDlgItem (ScdlDialog, IDSC_BEST_MKP_KNOW);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

    ControlScdl = GetDlgItem (ScdlDialog, IDSC_PREVIOUS_MAKESPAN);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

    ControlScdl = GetDlgItem (ScdlDialog, IDSC_MAKESPAN);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

    ControlScdl = GetDlgItem (ScdlDialog, IDSC_SOLUTIONS_EVAL);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

    ControlScdl = GetDlgItem (ScdlDialog, IDSC_COPUTING_TIME);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

    ControlScdl = GetDlgItem (ScdlDialog, IDSC_METHOD);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

    ControlScdl = GetDlgItem (ScdlDialog, IDSC_INITIAL_SOLUTION);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

    // Update the methods group box texts

    ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_1);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "First method parameters");

    ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_2);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Second method parameters");

    ControlScdl = GetDlgItem (ScdlDialog, IDGB_METHOD_3);
    SendMessage (ControlScdl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "Third method parameters");
}
