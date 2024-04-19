#include <math.h>
#include "Scdl_Structure.h"

// ***** Class JS_ScdlProblem

// *****************************************************************************
// The foloowing functions prints the solution in a Gantt graph.
// *****************************************************************************

bool JS_ScdlProblem :: PrintGanttSolution (HWND hWnd, const int &Xi, const int &Yi, const int &Width, const int &Height)
{
    HDC hDC;
    HFONT font, fontMakespan;
    HPEN hPen;
    HBRUSH NewBrush;

    float X = (2.0*Width)/1000;
    float Y = (2.0*Height)/1000;

    float Axes_Xi = 2.0*Xi + 70*X;
    float Axes_Yi = 2.0*Yi;
    float Axes_Width = 860*X;
    float Axes_Height = 970*Y;

    float Axes_Xf = Axes_Xi + Axes_Width;
    float Axes_Yf = Axes_Yi + Axes_Height;

    float Rec_Height = (Axes_Height - (SP_NMcn - 1)*2*Y - 4*Y)/SP_NMcn;

    int FontHeight = (int)(Rec_Height);
    int FontWidth = (int)(13.0*X);

    int task, job;
    int LeftRect,
        TopRect,
        RightRect,
        BottomRect;

    float BaseUnit = Axes_Width/(SP_Makespan);

    VecCOLOR Pallet;
    Pallet.resize (100);

    Pallet[0] = (RGB(250, 237, 25));
    Pallet[1] = (RGB(62, 154, 222));
    Pallet[2] = (RGB(254, 53, 249));
    Pallet[3] = (RGB(100, 250, 81));
    Pallet[4] = (RGB(255, 166, 166));
    Pallet[5] = (RGB(255,133, 72));
    Pallet[6] = (RGB(50, 0, 250));
    Pallet[7] = (RGB(150, 50, 250));
    Pallet[8] = (RGB(0, 194, 72));
    Pallet[9] = (RGB(255,63, 63));
    Pallet[10] = (RGB(255, 78, 4));
    Pallet[11] = (RGB(0, 15, 145));
    Pallet[12] = (RGB(147, 35, 147));
    Pallet[13] = (RGB(35, 92, 0));
    Pallet[14] = (RGB(95, 125, 0));
    Pallet[15] = (RGB(202, 0, 15));
    Pallet[16] = (RGB(100, 100, 100));
    Pallet[17] = (RGB(153, 103, 0));
    Pallet[18] = (RGB(243, 0, 45));


    // Draw the graphic axes

    hDC = GetDC(hWnd);
    MoveToEx(hDC, (INT)Axes_Xi, (INT)Axes_Yi, NULL);
    LineTo(hDC, (INT)Axes_Xi, (INT)Axes_Yf);
    LineTo(hDC, (INT)Axes_Xf, (INT)Axes_Yf);

    font = CreateFont(FontHeight, FontWidth, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
    "Times New Roman");

    fontMakespan = CreateFont((int)(100*Y), FontWidth, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
    "Times New Roman");

    SelectObject(hDC, font);

    // Draw the Machine indexes

    char text[41];

    for (UINT count=0; count < SP_NMcn; count++)
    {
        itoa (count+1, text, 10);

        TextOut(hDC, 2*Xi, (INT)(Axes_Yf - (Rec_Height+2*Y)*count - Rec_Height), "M", 2);
        TextOut(hDC, 2*Xi+3*FontWidth, (INT)(Axes_Yf - (Rec_Height+2*Y)*count - Rec_Height), text, 2);
    }

    DeleteObject(font);

    SelectObject(hDC, fontMakespan);

    itoa ((int)SP_Makespan, text, 10);
    TextOut(hDC, (int)Axes_Xf, (int)Axes_Yf, text, 4);

    DeleteObject(font);

    // Draw the task slot of times

    for (UINT i=0; i<SP_SRScdl.size(); i++)
    {
        for (UINT j=0; j<SP_SRScdl[i].size(); j++)
        {
            task = SP_SRScdl[i][j];
            LeftRect = (INT)(Axes_Xi + (SP_StartTimeOfTask[task])*BaseUnit);
            TopRect = (INT)(Axes_Yf - (Rec_Height+2*Y)*SP_McnOfTask[task]);
            RightRect = (INT)(Axes_Xi + (SP_FinalTimeOfTask[task])*BaseUnit);
            BottomRect = (INT)(TopRect - Rec_Height);

            job = SP_JobOfTask[task];

            hPen = CreatePen(PS_SOLID,1,Pallet[job]);
            SelectObject(hDC, hPen);

            NewBrush = CreateSolidBrush(Pallet[job]);
            SelectObject(hDC, NewBrush);

            Rectangle(hDC, LeftRect, TopRect, RightRect, BottomRect);

            DeleteObject(hPen);
            DeleteObject(NewBrush);
        }
    }

    ReleaseDC(hWnd, hDC);

    return TRUE;
}

// *****************************************************************************
// The foloowing functions prints a defined critical path in the Gantt graph.
// *****************************************************************************

bool JS_ScdlProblem :: PrintCriticalPath (HWND hWnd, const int &Xi, const int &Yi, const int &Width, const int &Height)
{
    HDC hDC = GetDC(hWnd);;

    int task, job;

    int LeftRect,
        TopRect,
        RightRect,
        BottomRect;

    float X = (2.0*Width)/1000;
    float Y = (2.0*Height)/1000;

    float Axes_Xi = 2.0*Xi + 70*X;
    float Axes_Yi = 2.0*Yi;
    float Axes_Width = 860*X;
    float Axes_Height = 970*Y;

    float Axes_Yf = Axes_Yi + Axes_Height;

    float Rec_Height = (Axes_Height - (SP_NMcn - 1)*2*Y - 4*Y)/SP_NMcn;

    float BaseUnit = Axes_Width/(SP_Makespan);

    for (UINT i=0; i<SP_CriticalPath[SP_CriticalPathIndex].size(); i++)
    {
        task = SP_CriticalPath[SP_CriticalPathIndex][i];
        job = SP_JobOfTask[task];

        LeftRect = (INT)(Axes_Xi + (SP_StartTimeOfTask[task])*BaseUnit);
        TopRect = (INT)(Axes_Yf - (Rec_Height+2*Y)*SP_McnOfTask[task]);
        RightRect = (INT)(Axes_Xi + (SP_FinalTimeOfTask[task])*BaseUnit);
        BottomRect = (INT)(TopRect - Rec_Height);

        MoveToEx(hDC, LeftRect, TopRect, NULL);
        LineTo(hDC, LeftRect, BottomRect);
        LineTo(hDC, RightRect, BottomRect);
        LineTo(hDC, RightRect, TopRect);
        LineTo(hDC, LeftRect, TopRect);
    }

    ReleaseDC(hWnd, hDC);

    return TRUE;
}

// *****************************************************************************
// The foloowing functions prints a defined critical path in the Gantt graph.
// *****************************************************************************

bool JS_ScdlProblem :: PrintContourTask (HWND hWnd, const int &Xi, const int &Yi, const int &Width, const int &Height, const int &Task)
{
    HDC hDC = GetDC(hWnd);;

    int job;

    int LeftRect,
        TopRect,
        RightRect,
        BottomRect;

    float X = (2.0*Width)/1000;
    float Y = (2.0*Height)/1000;

    float Axes_Xi = 2.0*Xi + 70*X;
    float Axes_Yi = 2.0*Yi;
    float Axes_Width = 860*X;
    float Axes_Height = 970*Y;

    float Axes_Yf = Axes_Yi + Axes_Height;

    float Rec_Height = (Axes_Height - (SP_NMcn - 1)*2*Y - 4*Y)/SP_NMcn;

    float BaseUnit = Axes_Width/(SP_Makespan);

    job = SP_JobOfTask[Task];

    LeftRect = (INT)(Axes_Xi + (SP_StartTimeOfTask[Task])*BaseUnit);
    TopRect = (INT)(Axes_Yf - (Rec_Height+2*Y)*SP_McnOfTask[Task]);
    RightRect = (INT)(Axes_Xi + (SP_FinalTimeOfTask[Task])*BaseUnit);
    BottomRect = (INT)(TopRect - Rec_Height);

    MoveToEx(hDC, LeftRect, TopRect, NULL);
    LineTo(hDC, LeftRect, BottomRect);
    LineTo(hDC, RightRect, BottomRect);
    LineTo(hDC, RightRect, TopRect);
    LineTo(hDC, LeftRect, TopRect);

    ReleaseDC(hWnd, hDC);

    return TRUE;
}

// *****************************************************************************
// The foloowing functions prints a the block of a defined critical path in the
// Gantt graph.
// *****************************************************************************

bool JS_ScdlProblem :: PrintBlocksOnCriticalPath (HWND hWnd, const int &Xi, const int &Yi, const int &Width, const int &Height)
{
    HDC hDC = GetDC(hWnd);
    HPEN hPen;

    VecCOLOR Pallet;
    Pallet.resize (100);

    Pallet[0] = (RGB(234, 0, 61));
    Pallet[1] = (RGB(25, 0, 125));
    Pallet[2] = (RGB(80, 0, 0));
    Pallet[3] = (RGB(125, 0, 25));
    Pallet[4] = (RGB(0, 214, 92));
    Pallet[5] = (RGB(0, 80, 0));
    Pallet[6] = (RGB(201, 0, 53));
    Pallet[7] = (RGB(141, 42, 0));
    Pallet[8] = (RGB(95, 125, 0));
    Pallet[9] = (RGB(0, 167, 147));
    Pallet[10] = (RGB(100, 100, 100));
    Pallet[11] = (RGB(0, 50, 250));

    int task, job;

    int LeftRect,
        TopRect,
        RightRect,
        BottomRect;

    float X = (2.0*Width)/1000;
    float Y = (2.0*Height)/1000;

    float Axes_Xi = 2.0*Xi + 70*X;
    float Axes_Yi = 2.0*Yi;
    float Axes_Width = 860*X;
    float Axes_Height = 970*Y;

    float Axes_Yf = Axes_Yi + Axes_Height;

    float Rec_Height = (Axes_Height - (SP_NMcn - 1)*2*Y - 4*Y)/SP_NMcn;

    float BaseUnit = Axes_Width/(SP_Makespan);

    for (UINT i=0; i<SP_BlocksOnCriticalPath.size(); i++)
    {
        hPen = CreatePen(PS_SOLID,1,Pallet[i]);
        SelectObject(hDC, hPen);

        for (UINT j=0; j<SP_BlocksOnCriticalPath[i].size(); j++)
        {
            task = SP_BlocksOnCriticalPath[i][j];
            job = SP_JobOfTask[task];

            LeftRect = (INT)(Axes_Xi + (SP_StartTimeOfTask[task])*BaseUnit);
            TopRect = (INT)(Axes_Yf - (Rec_Height+2*Y)*SP_McnOfTask[task]);
            RightRect = (INT)(Axes_Xi + (SP_FinalTimeOfTask[task])*BaseUnit);
            BottomRect = (INT)(TopRect - Rec_Height);

            MoveToEx(hDC, LeftRect, TopRect, NULL);
            LineTo(hDC, LeftRect, BottomRect);
            LineTo(hDC, RightRect, BottomRect);
            LineTo(hDC, RightRect, TopRect);
            LineTo(hDC, LeftRect, TopRect);
        }

        DeleteObject(hPen);
    }

    ReleaseDC(hWnd, hDC);

    return TRUE;
}

bool JS_ScdlProblem :: PrintGanttNeighborhood (HWND hWnd, const int &Xi, const int &Yi, const int &Width, const int &Height)
{
    HDC hDC = GetDC(hWnd);

    UINT count = 0,
         NX,
         NY;

    float X,
          Y,
          SWidth,
          SHeight;

    NY = (UINT)(sqrt(SP_PopulationSize));

    if (NY*NY < SP_PopulationSize)
    {
        NX = NY+1;
    }
    else
    {
        NX = NY;
    }

    SWidth = Width / NX;
    SHeight = Height / NY;

    Y = 0;
    for (UINT y=0; y<NY; y++)
    {
        X = 0;

        for (UINT x=0; x<NX; x++)
        {
            SP_SRScdl = SP_VecScdl[count];
            TimingScdlSR ();
            PrintGanttSolution (hWnd, (int)(X+5), (int)(Y+5), (int)(SWidth-10), (int)(SHeight-10));

            FindCriticalPath ();
            PrintCriticalPath (hWnd, (int)(X+5), (int)(Y+5), (int)(SWidth-10), (int)(SHeight-10));

            X = X + SWidth;
            count++;
            if (count >= SP_PopulationSize) break;
        }

        Y = Y + SHeight;
    }

    SP_SRScdl = SP_VecScdl[SP_SolutionIndex];
    TimingScdlSR ();
    FindCriticalPath ();
    BlocksOnCriticalPath ();

    ReleaseDC(hWnd, hDC);

    return TRUE;
}


bool JS_ScdlProblem :: PrintGanttN5 (HWND hWnd, const int &Xi, const int &Yi, const int &Width, const int &Height)
{
    VecInt A, B;

    HDC hDC = GetDC(hWnd);
    HFONT font;

    font = CreateFont(15, 15, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
    "Times New Roman");

    UINT count = 0,
         NX,
         NY;

    float X,
          Y,
          SWidth,
          SHeight;

    N5_Ngh (A, B);

    UINT NSolutions = SP_Neighborhood.size() + 1;

    NY = (UINT)(sqrt(NSolutions));

    if (NY*NY < NSolutions)
    {
        NX = NY+1;
    }
    else
    {
        NX = NY;
    }

    SWidth = Width / NX;
    SHeight = Height / NY;

    X = 0;
    Y = 0;

    SelectObject(hDC, font);

    TextOut(hDC, (int)(X+5), (int)(Y+5), "Current Solution", 16);

    TimingScdlSR ();
    PrintGanttSolution (hWnd, (int)(X+5), (int)(Y+15), (int)(SWidth-10), (int)(SHeight-25));

    FindCriticalPath ();
    PrintCriticalPath (hWnd, (int)(X+5), (int)(Y+15), (int)(SWidth-10), (int)(SHeight-25));

    X = X + SWidth;

    for (UINT y=0; y<NY; y++)
    {
        for (UINT x=0; x<NX; x++)
        {
            if (x == 0 && y == 0) x=1;

            TextOut(hDC, (int)(2*(X+5)), (int)(2*(Y+5)), "Neighbor", 8);

            SP_SRScdl = SP_Neighborhood[count];
            TimingScdlSR ();
            PrintGanttSolution (hWnd, (int)(X+5), (int)(Y+15), (int)(SWidth-10), (int)(SHeight-25));

            PrintContourTask (hWnd, (int)(X+5), (int)(Y+15), (int)(SWidth-10), (int)(SHeight-25), A[count]);
            PrintContourTask (hWnd, (int)(X+5), (int)(Y+15), (int)(SWidth-10), (int)(SHeight-25), B[count]);

            X = X + SWidth;

            count++;
            if (count >= SP_Neighborhood.size()) break;
        }

        Y = Y + SHeight;
        X = 0;
    }

    DeleteObject(font);

    SP_SRScdl = SP_VecScdl[SP_SolutionIndex];
    TimingScdlSR ();
    FindCriticalPath ();
    BlocksOnCriticalPath ();

    ReleaseDC(hWnd, hDC);

    A.clear();
    B.clear();

    return TRUE;
}
