// Jared Petersen

#include <cstdlib>
#include <cmath>
#include "battleship.h"

using namespace std;


const int LOOP_LIMIT = 10000;
const int MAX_SHOTS = 6;
const int MAX_OPS = 32;

static int PlayerGrid[BS_GRID_ROWS][BS_GRID_COLS] = {{0}};
static int CarrierHits = 0;
static int BattleshipHits = 0;
static int CruiserHits = 0;
static int SubmarineHits = 0;
static int DestroyerHits = 0;

static int GameNum = -1;

static int CarrierProb[BS_GRID_ROWS][BS_GRID_COLS] = {{0}};
static int BattleshipProb[BS_GRID_ROWS][BS_GRID_COLS] = {{0}};
static int CruiserProb[BS_GRID_ROWS][BS_GRID_COLS] = {{0}};
static int SubmarineProb[BS_GRID_ROWS][BS_GRID_COLS] = {{0}};
static int DestroyerProb[BS_GRID_ROWS][BS_GRID_COLS] = {{0}};
static int ResultTable[BS_GRID_ROWS][BS_GRID_COLS] = {{0}};
static int TrackedShots[MAX_OPS][BS_GRID_ROWS][BS_GRID_COLS] = {{{0}}};
static int RandProbGrid[MAX_OPS][BS_GRID_ROWS][BS_GRID_COLS] = {{{0}}};

static int CurrentTarget = -1;
static int CarrierState = 0;
static int BattleshipState = 0;
static int CruiserState = 0;
static int DestroyerState = 0;
static int SubmarineState = 0;

static int Touches = 0;
static int CurTouches = 0;
static bool bTouches = false;

static int LikelyRows[MAX_SHOTS] = {-1,-1,-1,-1,-1,-1};
static int LikelyCols[MAX_SHOTS] = {-1,-1,-1,-1,-1,-1};
static int NumValid = 0;
int BestRow = -1;
int BestCol = -1;
int TargRow = -1;
int TargCol = -1;


char ConvertToArrayRow(char GridRow)
{
    return (int(GridRow - 'A'));
}


int ConvertToArrayCol(int GridCol)
{
    return (GridCol - 1);
}


char ConvertToGridRow(int ArrayRow)
{
    return(char('A' + ArrayRow));
}


int ConvertToGridCol(int ArrayCol)
{
    return(ArrayCol + 1);
}


int ClearStatics()
{
    int RowCount;
    int ColCount;
    int OpCount;

    for(RowCount = 0; RowCount < BS_GRID_ROWS; RowCount++)
    {
        for(ColCount = 0; ColCount < BS_GRID_COLS; ColCount++)
        {
            PlayerGrid[RowCount][ColCount] = 0;

            CarrierProb[RowCount][ColCount] = 0;
            BattleshipProb[RowCount][ColCount] = 0;
            CruiserProb[RowCount][ColCount] = 0;
            SubmarineProb[RowCount][ColCount] = 0;
            DestroyerProb[RowCount][ColCount] = 0;
            ResultTable[RowCount][ColCount] = 0;

            for(OpCount = 0; OpCount < MAX_OPS; OpCount++)
            {
                RandProbGrid[OpCount][RowCount][ColCount] = TrackedShots[OpCount][RowCount][ColCount];
            }
        }
    }

    CarrierHits = 0;
    BattleshipHits = 0;
    CruiserHits = 0;
    DestroyerHits = 0;
    SubmarineHits = 0;

    CurrentTarget = -1;

    BestRow = -1;
    BestCol = -1;
    TargRow = -1;
    TargCol = -1;

    CarrierState = 0;
    BattleshipState = 0;
    CruiserState = 0;
    DestroyerState = 0;
    SubmarineState = 0;

    Touches += CurTouches;

    GameNum++;

    return 0;
}


int PlaceShips()
{
    bool bPlaceValid = false;
    int RandDir = -1;
    int CurrentShipLength = 0;
    int CurrentShipID = 0;
    int NumShips;
    int RandIntRow = 0;
    int RandIntCol = 0;
    int FitValidation = 0;
    int StrictValidation = 0;
    int DirAttempts = 0;

    for(NumShips = 0; NumShips < BS_SHIP_COUNT; NumShips++)
    {
        bPlaceValid = false;
        RandDir = -1;

        switch(NumShips)
        {
            case 0:
                CurrentShipLength = BS_CARRIER_SIZE;
                CurrentShipID = BS_CARRIER;
            break;

            case 1:
                CurrentShipLength = BS_BATTLESHIP_SIZE;
                CurrentShipID = BS_BATTLESHIP;
            break;

            case 2:
                CurrentShipLength = BS_CRUISER_SIZE;
                CurrentShipID = BS_CRUISER;
            break;

            case 3:
                CurrentShipLength = BS_DESTROYER_SIZE;
                CurrentShipID = BS_DESTROYER;
            break;

            case 4:
                CurrentShipLength = BS_SUBMARINE_SIZE;
                CurrentShipID = BS_SUBMARINE;
            break;
        }

        while(!bPlaceValid)
        {
            RandIntRow = rand() % (BS_GRID_ROWS);
            RandIntCol = rand() % (BS_GRID_COLS);
            RandDir = -1;

            for(DirAttempts = 0; DirAttempts < 4; DirAttempts++)
            {
                if(RandDir == -1)
                    RandDir = rand() % 4;
                else if(!bPlaceValid)
                {
                    if(RandDir < 3)
                        RandDir++;
                    else
                        RandDir = 0;
                }

                switch(RandDir)
                {
                    case 0:
                        if(RandIntRow - (CurrentShipLength - 1) >= 0)
                        {
                            for(FitValidation = 0; FitValidation <= CurrentShipLength + 1; FitValidation++)
                            {
                                if((((RandIntRow + 1) - FitValidation) < BS_GRID_ROWS) && (((RandIntRow + 1) - FitValidation) >= 0))
                                {
                                    if(PlayerGrid[(RandIntRow + 1) - FitValidation][RandIntCol] != 0)
                                    {
                                        bPlaceValid = false;
                                        FitValidation = CurrentShipLength + 1;
                                    }
                                    else
                                    {
                                        bPlaceValid = true;
                                    }
                                }
                            }
                            if(bPlaceValid)
                            {
                                for(StrictValidation = 0; StrictValidation < CurrentShipLength; StrictValidation++)
                                {
                                    if(((RandIntRow - StrictValidation) >= 0) && ((RandIntCol + 1) < BS_GRID_COLS) && ((RandIntRow - StrictValidation) >= 0) && ((RandIntCol - 1) >= 0))
                                    {
                                        if((PlayerGrid[RandIntRow - StrictValidation][RandIntCol + 1] != 0) || (PlayerGrid[RandIntRow - StrictValidation][RandIntCol - 1] != 0))
                                        {
                                            bPlaceValid = false;
                                            StrictValidation = CurrentShipLength + 1;
                                        }
                                        else
                                        {
                                            bPlaceValid = true;
                                        }
                                    }
                                }
                            }
                        }
                    break;
                    case 1:
                        if(RandIntCol + (CurrentShipLength - 1) < BS_GRID_COLS)
                        {
                            for(FitValidation = 0; FitValidation <= CurrentShipLength + 1; FitValidation++)
                            {
                                if((((RandIntCol - 1) + FitValidation) < BS_GRID_COLS) && (((RandIntCol - 1) + FitValidation) >= 0))
                                {
                                    if(PlayerGrid[RandIntRow][(RandIntCol - 1) + FitValidation] != 0)
                                    {
                                        bPlaceValid = false;
                                        FitValidation = CurrentShipLength + 1;
                                    }
                                    else
                                    {
                                        bPlaceValid = true;
                                    }
                                }
                            }
                            if(bPlaceValid)
                            {
                                for(StrictValidation = 0; StrictValidation < CurrentShipLength; StrictValidation++)
                                {
                                    if(((RandIntRow + 1) < BS_GRID_ROWS) && ((RandIntCol + StrictValidation) < BS_GRID_COLS) && ((RandIntRow - 1) >= 0) && ((RandIntCol + StrictValidation) < BS_GRID_COLS))
                                    {
                                        if((PlayerGrid[RandIntRow + 1][RandIntCol + StrictValidation] != 0) || (PlayerGrid[RandIntRow - 1][RandIntCol + StrictValidation] != 0))
                                        {
                                            bPlaceValid = false;
                                            StrictValidation = CurrentShipLength + 1;
                                        }
                                        else
                                        {
                                            bPlaceValid = true;
                                        }
                                    }
                                }
                            }
                        }
                    break;
                    case 2:
                        if(RandIntRow + (CurrentShipLength - 1) < BS_GRID_ROWS)
                        {
                            for(FitValidation = 0; FitValidation <= CurrentShipLength + 1; FitValidation++)
                            {
                                if(((((RandIntRow - 1) + FitValidation)) < BS_GRID_COLS) && ((((RandIntRow - 1) + FitValidation)) >= 0))
                                {
                                    if(PlayerGrid[(RandIntRow - 1) + FitValidation][RandIntCol] != 0)
                                    {
                                        bPlaceValid = false;
                                        FitValidation = CurrentShipLength + 1;
                                    }
                                    else
                                    {
                                        bPlaceValid = true;
                                    }
                                }
                            }
                            if(bPlaceValid)
                            {
                                for(StrictValidation = 0; StrictValidation < CurrentShipLength; StrictValidation++)
                                {
                                    if(((RandIntRow + StrictValidation) < BS_GRID_ROWS) && ((RandIntCol + 1) < BS_GRID_COLS) && ((RandIntCol - 1) >= 0))
                                    {
                                        if((PlayerGrid[RandIntRow + StrictValidation][RandIntCol + 1] != 0) || (PlayerGrid[RandIntRow + StrictValidation][RandIntCol - 1] != 0))
                                        {
                                            bPlaceValid = false;
                                            StrictValidation = CurrentShipLength + 1;
                                        }
                                        else
                                        {
                                            bPlaceValid = true;
                                        }
                                    }
                                }
                            }
                        }
                    break;
                    case 3:
                        if(RandIntCol - (CurrentShipLength - 1) >= 0)
                        {
                            for(FitValidation = 0; FitValidation <= CurrentShipLength + 1; FitValidation++)
                            {
                                if(((((RandIntCol + 1) - FitValidation)) < BS_GRID_COLS) && ((((RandIntCol + 1) - FitValidation)) >= 0))
                                {
                                    if(PlayerGrid[RandIntRow][(RandIntCol + 1) - FitValidation] != 0)
                                    {
                                        bPlaceValid = false;
                                        FitValidation = CurrentShipLength + 1;
                                    }
                                    else
                                    {
                                        bPlaceValid = true;
                                    }
                                }
                            }
                            if(bPlaceValid)
                            {
                                for(StrictValidation = 0; StrictValidation < CurrentShipLength; StrictValidation++)
                                {
                                    if(((RandIntRow + 1) < BS_GRID_ROWS) && ((RandIntRow - 1) >= 0) && ((RandIntCol - StrictValidation) >= 0))
                                    {
                                        if((PlayerGrid[RandIntRow + 1][RandIntCol - StrictValidation] != 0) || (PlayerGrid[RandIntRow - 1][RandIntCol - StrictValidation] != 0))
                                        {
                                            bPlaceValid = false;
                                            StrictValidation = CurrentShipLength + 1;
                                        }
                                        else
                                        {
                                            bPlaceValid = true;
                                        }
                                    }
                                }
                            }
                        }
                    break;
                }

                if(bPlaceValid)
                {
                    DirAttempts = 4;

                    switch(RandDir)
                    {
                        case 0:
                            for(FitValidation = 0; FitValidation < CurrentShipLength; FitValidation++)
                            {
                                PlayerGrid[RandIntRow - FitValidation][RandIntCol] = CurrentShipID;
                            }
                        break;
                        case 1:
                            for(FitValidation = 0; FitValidation < CurrentShipLength; FitValidation++)
                            {
                                PlayerGrid[RandIntRow][RandIntCol + FitValidation] = CurrentShipID;
                            }
                        break;
                        case 2:
                            for(FitValidation = 0; FitValidation < CurrentShipLength; FitValidation++)
                            {
                                PlayerGrid[RandIntRow + FitValidation][RandIntCol] = CurrentShipID;
                            }
                        break;
                        case 3:
                            for(FitValidation = 0; FitValidation < CurrentShipLength; FitValidation++)
                            {
                                PlayerGrid[RandIntRow][RandIntCol - FitValidation] = CurrentShipID;
                            }
                        break;
                    }
                }
            }
        }
    }

    return 0;
}


int RoninIncomingFire(char Row, int Col)
{
    int ReturnCode = 0;
    int IntRow;
    int IntCol;

    if (Row == '\0' && Col == 0)
    {
        ClearStatics();
        PlaceShips();
    }
    else
    {
        if(((Row >= 'A') && (Row < 'A' + BS_GRID_ROWS)) && ((Col > 0) && (Col <= BS_GRID_COLS)))
        {
            IntRow = ConvertToArrayRow(Row);
            IntCol = ConvertToArrayCol(Col);

            switch(PlayerGrid[IntRow][IntCol])
            {
                case BS_CARRIER:
                    PlayerGrid[IntRow][IntCol] += 10;
                    CarrierHits++;

                    if(CarrierHits == BS_CARRIER_SIZE)
                        ReturnCode = (BS_SHIP_HIT | BS_SHIP_SANK | BS_CARRIER);

                    else
                        ReturnCode = (BS_SHIP_HIT | BS_CARRIER);
                break;

                case BS_BATTLESHIP:
                    PlayerGrid[IntRow][IntCol] += 10;
                    BattleshipHits++;

                    if(BattleshipHits == BS_BATTLESHIP_SIZE)
                        ReturnCode = (BS_SHIP_HIT | BS_SHIP_SANK | BS_BATTLESHIP);
                    else
                        ReturnCode = (BS_SHIP_HIT | BS_BATTLESHIP);
                break;

                case BS_CRUISER:
                    PlayerGrid[IntRow][IntCol] += 10;
                    CruiserHits++;

                    if(CruiserHits == BS_CRUISER_SIZE)
                        ReturnCode = (BS_SHIP_HIT | BS_SHIP_SANK | BS_CRUISER);
                    else
                        ReturnCode = (BS_SHIP_HIT | BS_CRUISER);
                break;

                case BS_DESTROYER:
                    PlayerGrid[IntRow][IntCol] += 10;
                    DestroyerHits++;

                    if(DestroyerHits == BS_DESTROYER_SIZE)
                        ReturnCode = (BS_SHIP_HIT | BS_SHIP_SANK | BS_DESTROYER);
                    else
                        ReturnCode = (BS_SHIP_HIT | BS_DESTROYER);
                break;

                case BS_SUBMARINE:
                    PlayerGrid[IntRow][IntCol] += 10;
                    SubmarineHits++;

                    if(SubmarineHits == BS_SUBMARINE_SIZE)
                        ReturnCode = (BS_SHIP_HIT | BS_SHIP_SANK | BS_SUBMARINE);
                    else
                        ReturnCode = (BS_SHIP_HIT | BS_SUBMARINE);
                break;

                case BS_CARRIER + 10:
                    if(CarrierHits == BS_CARRIER_SIZE)
                        ReturnCode = (BS_SHIP_HIT | BS_SHIP_SANK | BS_CARRIER);
                    else
                        ReturnCode = (BS_SHIP_HIT | BS_CARRIER);
                break;

                case BS_BATTLESHIP + 10:
                    if(BattleshipHits == BS_BATTLESHIP_SIZE)
                        ReturnCode = (BS_SHIP_HIT | BS_SHIP_SANK | BS_BATTLESHIP);
                    else
                        ReturnCode = (BS_SHIP_HIT | BS_BATTLESHIP);
                break;

                case BS_CRUISER + 10:
                    if(CruiserHits == BS_CRUISER_SIZE)
                        ReturnCode = (BS_SHIP_HIT | BS_SHIP_SANK | BS_CRUISER);
                    else
                        ReturnCode = (BS_SHIP_HIT | BS_CRUISER);
                break;

                case BS_DESTROYER + 10:
                    if(DestroyerHits == BS_DESTROYER_SIZE)
                        ReturnCode = (BS_SHIP_HIT | BS_SHIP_SANK | BS_DESTROYER);
                    else
                        ReturnCode = (BS_SHIP_HIT | BS_DESTROYER);
                break;

                case BS_SUBMARINE + 10:
                    if(SubmarineHits == BS_SUBMARINE_SIZE)
                        ReturnCode = (BS_SHIP_HIT | BS_SHIP_SANK | BS_SUBMARINE);
                    else
                        ReturnCode = (BS_SHIP_HIT | BS_SUBMARINE);
                break;
            }
        }
    }

    return ReturnCode;
}


bool DetermineTouch()
{
    int ArrayCount;
    int ArrayCount2;
    int CurrentShip = -6;

    CurTouches = 0;

    for(ArrayCount = 0; ArrayCount < BS_GRID_ROWS; ArrayCount++)
        {
            for(ArrayCount2 = 0; ArrayCount2 < BS_GRID_COLS; ArrayCount2++)
            {
                if(ResultTable[ArrayCount][ArrayCount2] > 0)
                {
                    CurrentShip = ResultTable[ArrayCount][ArrayCount2];

                    if(CurrentShip > 0)
                    {
                        if((ArrayCount + 1 < BS_GRID_ROWS) && (ResultTable[ArrayCount + 1][ArrayCount2] > 0) && (ResultTable[ArrayCount + 1][ArrayCount2] != CurrentShip))
                        {
                            CurTouches++;
                        }
                        if((ArrayCount2 + 1 < BS_GRID_COLS) && (ResultTable[ArrayCount][ArrayCount2 + 1] > 0) && (ResultTable[ArrayCount][ArrayCount2 + 1] != CurrentShip))
                        {
                            CurTouches++;
                        }
                        if((ArrayCount - 1 >= 0) && (ResultTable[ArrayCount - 1][ArrayCount2] > 0) && (ResultTable[ArrayCount - 1][ArrayCount2] != CurrentShip))
                        {
                            CurTouches++;
                        }
                        if((ArrayCount2 - 1 >= 0) && (ResultTable[ArrayCount][ArrayCount2 - 1] > 0) && (ResultTable[ArrayCount][ArrayCount2 - 1] != CurrentShip))
                        {
                            CurTouches++;
                        }
                    }
                }
            }
        }

        CurTouches /= 2;

        if((CurTouches > 0) || ((((Touches + CurTouches) * 1.0)/(GameNum * 1.0)) > 0.2))
            return true;
        else
            return false;
}


int DetermineTarget()
{
    int TargetArray[BS_SHIP_COUNT] = {0};
    int NumTargets = 0;
    int RandTarget;

    if(CarrierState == 1)
    {
        TargetArray[NumTargets] = BS_CARRIER;
        NumTargets++;
    }
    if(BattleshipState == 1)
    {
        TargetArray[NumTargets] = BS_BATTLESHIP;
        NumTargets++;
    }
    if(CruiserState == 1)
    {
        TargetArray[NumTargets] = BS_CRUISER;
        NumTargets++;
    }
    if(DestroyerState == 1)
    {
        TargetArray[NumTargets] = BS_DESTROYER;
        NumTargets++;
    }
    if(SubmarineState == 1)
    {
        TargetArray[NumTargets] = BS_SUBMARINE;
        NumTargets++;
    }

    if(NumTargets > 0)
    {
        RandTarget = rand() % NumTargets;

        if(TargetArray[RandTarget] != 0)
            return TargetArray[RandTarget];
    }

    return -1;
}


int SmallestFitLogic()
{
    int Counter;
    int Smallest = -1;
    int ArrayCount;
    int ArrayCount2;
    int FitHorz = 0;
    int FitVert = 0;
    int FitCount;

    for(Counter = 0; Counter < BS_SHIP_COUNT; Counter++)
    {
        switch (Counter)
        {
            case 0:
                if(((Smallest == -1) || (BS_CARRIER_SIZE <= Smallest)) && (CarrierState < 3))
                {
                    Smallest = BS_CARRIER_SIZE;
                }
            break;
            case 1:
                if(((Smallest == -1) || (BS_BATTLESHIP_SIZE <= Smallest)) && (BattleshipState < 3))
                {
                    Smallest = BS_BATTLESHIP_SIZE;
                }
            break;
            case 2:
                if(((Smallest == -1) || (BS_CRUISER_SIZE <= Smallest)) && (CruiserState < 3))
                {
                    Smallest = BS_CRUISER_SIZE;
                }
            break;
            case 3:
                if(((Smallest == -1) || (BS_DESTROYER_SIZE <= Smallest)) && (DestroyerState < 3))
                {
                    Smallest = BS_DESTROYER_SIZE;
                }
            break;
            case 4:
                if(((Smallest == -1) || (BS_SUBMARINE_SIZE <= Smallest)) && (SubmarineState < 3))
                {
                    Smallest = BS_SUBMARINE_SIZE;
                }
            break;
        }
    }

    if(Smallest > 0)
    {
        for(ArrayCount = 0; ArrayCount < BS_GRID_ROWS; ArrayCount++)
        {
            for(ArrayCount2 = 0; ArrayCount2 < BS_GRID_COLS; ArrayCount2++)
            {
                FitHorz = 0;
                FitVert = 0;

                if(ArrayCount + 1 < BS_GRID_ROWS)
                {
                    for(FitCount = ArrayCount + 1; FitCount < BS_GRID_ROWS; FitCount++)
                    {
                        if((ResultTable[FitCount][ArrayCount2] == 0) || ((ResultTable[FitCount][ArrayCount2] == BS_CARRIER) && (CarrierState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_BATTLESHIP) && (BattleshipState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_CRUISER) && (CruiserState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_DESTROYER) && (DestroyerState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_SUBMARINE) && (SubmarineState != 3)))
                            FitVert++;

                        else
                            FitCount = BS_GRID_ROWS;
                    }
                }
                if(ArrayCount - 1 >= 0)
                {
                    for(FitCount = ArrayCount - 1; FitCount >= 0; FitCount--)
                    {
                        if((ResultTable[FitCount][ArrayCount2] == 0) || ((ResultTable[FitCount][ArrayCount2] == BS_CARRIER) && (CarrierState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_BATTLESHIP) && (BattleshipState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_CRUISER) && (CruiserState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_DESTROYER) && (DestroyerState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_SUBMARINE) && (SubmarineState != 3)))
                            FitVert++;

                        else
                            FitCount = -1;
                    }
                }

                if(ArrayCount2 + 1 < BS_GRID_COLS)
                {
                    for(FitCount = ArrayCount2 + 1; FitCount < BS_GRID_COLS; FitCount++)
                    {
                        if((ResultTable[ArrayCount][FitCount] == 0) || ((ResultTable[ArrayCount][FitCount] == BS_CARRIER) && (CarrierState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_BATTLESHIP) && (BattleshipState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_CRUISER) && (CruiserState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_DESTROYER) && (DestroyerState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_SUBMARINE) && (SubmarineState != 3)))
                            FitHorz++;

                        else
                            FitCount = BS_GRID_COLS;
                    }
                }

                if(ArrayCount2 - 1 >= 0)
                {
                    for(FitCount = ArrayCount2 - 1; FitCount >= 0; FitCount--)
                    {
                        if((ResultTable[ArrayCount][FitCount] == 0) || ((ResultTable[ArrayCount][FitCount] == BS_CARRIER) && (CarrierState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_BATTLESHIP) && (BattleshipState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_CRUISER) && (CruiserState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_DESTROYER) && (DestroyerState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_SUBMARINE) && (SubmarineState != 3)))
                            FitHorz++;

                        else
                            FitCount = -1;
                    }
                }

                if(((FitHorz < (Smallest - 1)) && (FitVert < (Smallest - 1))) && (ResultTable[ArrayCount][ArrayCount2] == 0))
                {
                    CarrierProb[ArrayCount][ArrayCount2] = -101;
                    BattleshipProb[ArrayCount][ArrayCount2] = -101;
                    CruiserProb[ArrayCount][ArrayCount2] = -101;
                    DestroyerProb[ArrayCount][ArrayCount2] = -101;
                    SubmarineProb[ArrayCount][ArrayCount2] = -101;
                    ResultTable[ArrayCount][ArrayCount2] = -101;
                }
            }
        }
    }

    return 0;
}


int FitShipLogic(int ShipID, int ShipSize)
{
    int ArrayCount;
    int ArrayCount2;
    int ArrayCount3;
    int ArrayCount4;
    int FitHorz = 0;
    int FitVert = 0;
    int FitCount;
    int DetectedRow[5] = {-1,-1,-1,-1,-1};
    int DetectedCol[5] = {-1,-1,-1,-1,-1};
    int NumDetectedShots = 0;

    if(ShipSize > 0)
    {
        for(ArrayCount = 0; ArrayCount < BS_GRID_ROWS; ArrayCount++)
        {
            for(ArrayCount2 = 0; ArrayCount2 < BS_GRID_COLS; ArrayCount2++)
            {
                if(ResultTable[ArrayCount][ArrayCount2] == ShipID)
                {
                    if(NumDetectedShots < 5)
                    {
                        DetectedRow[NumDetectedShots] = ArrayCount;
                        DetectedCol[NumDetectedShots] = ArrayCount2;
                    }

                    NumDetectedShots++;
                }
            }
        }

        for(ArrayCount = 0; ArrayCount < BS_GRID_ROWS; ArrayCount++)
        {
            for(ArrayCount2 = 0; ArrayCount2 < BS_GRID_COLS; ArrayCount2++)
            {
                FitHorz = 0;
                FitVert = 0;

                if(ArrayCount + 1 < BS_GRID_ROWS)
                {
                    for(FitCount = ArrayCount + 1; FitCount < BS_GRID_ROWS; FitCount++)
                    {
                        if((ResultTable[FitCount][ArrayCount2] == 0) || ((ResultTable[FitCount][ArrayCount2] == BS_CARRIER) && (CarrierState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_BATTLESHIP) && (BattleshipState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_CRUISER) && (CruiserState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_DESTROYER) && (DestroyerState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_SUBMARINE) && (SubmarineState != 3)))
                            FitVert++;

                        else
                            FitCount = BS_GRID_ROWS;
                    }
                }
                if(ArrayCount - 1 >= 0)
                {
                    for(FitCount = ArrayCount - 1; FitCount >= 0; FitCount--)
                    {
                        if((ResultTable[FitCount][ArrayCount2] == 0) || ((ResultTable[FitCount][ArrayCount2] == BS_CARRIER) && (CarrierState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_BATTLESHIP) && (BattleshipState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_CRUISER) && (CruiserState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_DESTROYER) && (DestroyerState != 3)) || ((ResultTable[FitCount][ArrayCount2] == BS_SUBMARINE) && (SubmarineState != 3)))
                            FitVert++;

                        else
                            FitCount = -1;
                    }
                }

                if(ArrayCount2 + 1 < BS_GRID_COLS)
                {
                    for(FitCount = ArrayCount2 + 1; FitCount < BS_GRID_COLS; FitCount++)
                    {
                        if((ResultTable[ArrayCount][FitCount] == 0) || ((ResultTable[ArrayCount][FitCount] == BS_CARRIER) && (CarrierState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_BATTLESHIP) && (BattleshipState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_CRUISER) && (CruiserState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_DESTROYER) && (DestroyerState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_SUBMARINE) && (SubmarineState != 3)))
                            FitHorz++;

                        else
                            FitCount = BS_GRID_COLS;
                    }
                }

                if(ArrayCount2 - 1 >= 0)
                {
                    for(FitCount = ArrayCount2 - 1; FitCount >= 0; FitCount--)
                    {
                        if((ResultTable[ArrayCount][FitCount] == 0) || ((ResultTable[ArrayCount][FitCount] == BS_CARRIER) && (CarrierState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_BATTLESHIP) && (BattleshipState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_CRUISER) && (CruiserState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_DESTROYER) && (DestroyerState != 3)) || ((ResultTable[ArrayCount][FitCount] == BS_SUBMARINE) && (SubmarineState != 3)))
                            FitHorz++;

                        else
                            FitCount = -1;
                    }
                }

                if((NumDetectedShots > 0) && (((ArrayCount == DetectedRow[0]) && (ArrayCount2 == DetectedCol[0])) || ((ArrayCount == DetectedRow[1]) && (ArrayCount2 == DetectedCol[1])) || ((ArrayCount == DetectedRow[2]) && (ArrayCount2 == DetectedCol[2])) || ((ArrayCount == DetectedRow[3]) && (ArrayCount2 == DetectedCol[3])) || ((ArrayCount == DetectedRow[4]) && (ArrayCount2 == DetectedCol[4]))))
                {
                    if(FitHorz < (ShipSize - 1))
                    {
                        for(ArrayCount3 = 0; ArrayCount3 < BS_GRID_ROWS; ArrayCount3++)
                        {
                            for(ArrayCount4 = 0; ArrayCount4 < BS_GRID_COLS; ArrayCount4++)
                            {
                                if((ArrayCount4 != DetectedCol[0]) && (ResultTable[ArrayCount3][ArrayCount4] == 0))
                                {
                                    switch(ShipID)
                                    {
                                        case BS_CARRIER:
                                            CarrierProb[ArrayCount3][ArrayCount4] = -300;
                                        break;

                                        case BS_BATTLESHIP:
                                            BattleshipProb[ArrayCount3][ArrayCount4] = -300;
                                        break;

                                        case BS_CRUISER:
                                            CruiserProb[ArrayCount3][ArrayCount4] = -300;
                                        break;

                                        case BS_DESTROYER:
                                            DestroyerProb[ArrayCount3][ArrayCount4] = -300;
                                        break;

                                        case BS_SUBMARINE:
                                            SubmarineProb[ArrayCount3][ArrayCount4] = -300;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if(FitVert < (ShipSize - 1))
                    {
                        for(ArrayCount3 = 0; ArrayCount3 < BS_GRID_ROWS; ArrayCount3++)
                        {
                            for(ArrayCount4 = 0; ArrayCount4 < BS_GRID_COLS; ArrayCount4++)
                            {
                                if((ArrayCount3 != DetectedRow[0]) && (ResultTable[ArrayCount3][ArrayCount4] == 0))
                                {
                                    switch(ShipID)
                                    {
                                        case BS_CARRIER:
                                            CarrierProb[ArrayCount3][ArrayCount4] = -300;
                                        break;

                                        case BS_BATTLESHIP:
                                            BattleshipProb[ArrayCount3][ArrayCount4] = -300;
                                        break;

                                        case BS_CRUISER:
                                            CruiserProb[ArrayCount3][ArrayCount4] = -300;
                                        break;

                                        case BS_DESTROYER:
                                            DestroyerProb[ArrayCount3][ArrayCount4] = -300;
                                        break;

                                        case BS_SUBMARINE:
                                            SubmarineProb[ArrayCount3][ArrayCount4] = -300;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }

                if(((FitHorz < (ShipSize - 1)) && (FitVert < (ShipSize - 1))) && (ResultTable[ArrayCount][ArrayCount2] == 0))
                {
                    switch (ShipID)
                    {
                        case BS_CARRIER:
                            CarrierProb[ArrayCount][ArrayCount2] = -201;
                        break;

                        case BS_BATTLESHIP:
                            BattleshipProb[ArrayCount][ArrayCount2] = -201;
                        break;

                        case BS_CRUISER:
                            CruiserProb[ArrayCount][ArrayCount2] = -201;
                        break;

                        case BS_DESTROYER:
                            DestroyerProb[ArrayCount][ArrayCount2] = -201;
                        break;

                        case BS_SUBMARINE:
                            SubmarineProb[ArrayCount][ArrayCount2] = -201;
                        break;
                    }
                }
            }
        }
    }

    return 0;
}


int Bushido(int SankShip, int opponent)
{
    int ArrayCount;
    int ArrayCount2;

    for(ArrayCount = 0; ArrayCount < BS_GRID_ROWS; ArrayCount++)
    {
        for(ArrayCount2 = 0; ArrayCount2 < BS_GRID_COLS; ArrayCount2++)
        {
            if((SankShip > 0) && (ResultTable[ArrayCount][ArrayCount2] == SankShip))
            {
                if((ArrayCount - 1 >= 0) && (ResultTable[ArrayCount - 1][ArrayCount2] <= 0))
                {
                    if((opponent >= 0) && (opponent < MAX_OPS))
                        if(RandProbGrid[opponent][ArrayCount - 1][ArrayCount2] >= 0)
                            RandProbGrid[opponent][ArrayCount - 1][ArrayCount2] = -1;
                    if(CarrierProb[ArrayCount - 1][ArrayCount2] >= 0)
                        CarrierProb[ArrayCount - 1][ArrayCount2] = -1;
                    if(BattleshipProb[ArrayCount - 1][ArrayCount2] >= 0)
                        BattleshipProb[ArrayCount - 1][ArrayCount2] = -1;
                    if(CruiserProb[ArrayCount - 1][ArrayCount2] >= 0)
                        CruiserProb[ArrayCount - 1][ArrayCount2] = -1;
                    if(DestroyerProb[ArrayCount - 1][ArrayCount2] >= 0)
                        DestroyerProb[ArrayCount - 1][ArrayCount2] = -1;
                    if(SubmarineProb[ArrayCount - 1][ArrayCount2] >= 0)
                        SubmarineProb[ArrayCount - 1][ArrayCount2] = -1;
                }

                if((ArrayCount + 1 < BS_GRID_ROWS) && (ResultTable[ArrayCount + 1][ArrayCount2] <= 0))
                {
                    if((opponent >= 0) && (opponent < MAX_OPS))
                        if(RandProbGrid[opponent][ArrayCount + 1][ArrayCount2] >= 0)
                            RandProbGrid[opponent][ArrayCount + 1][ArrayCount2] = -1;
                    if(CarrierProb[ArrayCount + 1][ArrayCount2] >= 0)
                        CarrierProb[ArrayCount + 1][ArrayCount2] = -1;
                    if(BattleshipProb[ArrayCount + 1][ArrayCount2] >= 0)
                        BattleshipProb[ArrayCount + 1][ArrayCount2] = -1;
                    if(CruiserProb[ArrayCount + 1][ArrayCount2] >= 0)
                        CruiserProb[ArrayCount + 1][ArrayCount2] = -1;
                    if(DestroyerProb[ArrayCount + 1][ArrayCount2] >= 0)
                        DestroyerProb[ArrayCount + 1][ArrayCount2] = -1;
                    if(SubmarineProb[ArrayCount + 1][ArrayCount2] >= 0)
                        SubmarineProb[ArrayCount + 1][ArrayCount2] = -1;
                }

                if((ArrayCount2 - 1 >= 0) && (ResultTable[ArrayCount][ArrayCount2 - 1] <= 0))
                {
                    if((opponent >= 0) && (opponent < MAX_OPS))
                        if(RandProbGrid[opponent][ArrayCount][ArrayCount2 - 1] >= 0)
                            RandProbGrid[opponent][ArrayCount][ArrayCount2 - 1] = -1;
                    if(CarrierProb[ArrayCount][ArrayCount2 - 1] >= 0)
                        CarrierProb[ArrayCount][ArrayCount2 - 1] = -1;
                    if(BattleshipProb[ArrayCount][ArrayCount2 - 1] >= 0)
                        BattleshipProb[ArrayCount][ArrayCount2 - 1] = -1;
                    if(CruiserProb[ArrayCount][ArrayCount2 - 1] >= 0)
                        CruiserProb[ArrayCount][ArrayCount2 - 1] = -1;
                    if(DestroyerProb[ArrayCount][ArrayCount2 - 1] >= 0)
                        DestroyerProb[ArrayCount][ArrayCount2 - 1] = -1;
                    if(SubmarineProb[ArrayCount][ArrayCount2 - 1] >= 0)
                        SubmarineProb[ArrayCount][ArrayCount2 - 1] = -1;
                }

                if((ArrayCount2 + 1 < BS_GRID_COLS) && (ResultTable[ArrayCount][ArrayCount2 + 1] <= 0))
                {
                    if((opponent >= 0) && (opponent < MAX_OPS))
                        if(RandProbGrid[opponent][ArrayCount][ArrayCount2 + 1] >= 0)
                            RandProbGrid[opponent][ArrayCount][ArrayCount2 + 1] = -1;
                    if(CarrierProb[ArrayCount][ArrayCount2 + 1] >= 0)
                        CarrierProb[ArrayCount][ArrayCount2 + 1] = -1;
                    if(BattleshipProb[ArrayCount][ArrayCount2 + 1] >= 0)
                        BattleshipProb[ArrayCount][ArrayCount2 + 1] = -1;
                    if(CruiserProb[ArrayCount][ArrayCount2 + 1] >= 0)
                        CruiserProb[ArrayCount][ArrayCount2 + 1] = -1;
                    if(DestroyerProb[ArrayCount][ArrayCount2 + 1] >= 0)
                        DestroyerProb[ArrayCount][ArrayCount2 + 1] = -1;
                    if(SubmarineProb[ArrayCount][ArrayCount2 + 1] >= 0)
                        SubmarineProb[ArrayCount][ArrayCount2 + 1] = -1;
                }
            }
        }
    }
    return 0;
}


int DetermineOrientation(int HitShip)
{
    int DetectedRow[2] = {-1,-1};
    int DetectedCol[2] = {-1,-1};
    int ArrayCount;
    int ArrayCount2;
    int NumDetectedShots = 0;
    int FitHorz = 0;
    int FitVert = 0;
    int FitCount;
    int FitCount2;
    int ShipLength = 0;

    for(ArrayCount = 0; ArrayCount < BS_GRID_ROWS; ArrayCount++)
    {
        for(ArrayCount2 = 0; ArrayCount2 < BS_GRID_COLS; ArrayCount2++)
        {
            if(ResultTable[ArrayCount][ArrayCount2] == HitShip)
            {
                if(NumDetectedShots < 2)
                {
                    DetectedRow[NumDetectedShots] = ArrayCount;
                    DetectedCol[NumDetectedShots] = ArrayCount2;
                }

                NumDetectedShots++;
            }
        }
    }

    if(NumDetectedShots == 2)
    {
        if(DetectedRow[0] == DetectedRow[1])
        {
            for(ArrayCount = 0; ArrayCount < BS_GRID_ROWS; ArrayCount++)
            {
                for(ArrayCount2 = 0; ArrayCount2 < BS_GRID_COLS; ArrayCount2++)
                {
                    if(ArrayCount != DetectedRow[0])
                    {
                        switch(HitShip)
                        {
                            case BS_CARRIER:
                                CarrierProb[ArrayCount][ArrayCount2] = -100;
                            break;

                            case BS_BATTLESHIP:
                                BattleshipProb[ArrayCount][ArrayCount2] = -100;
                            break;

                            case BS_CRUISER:
                                CruiserProb[ArrayCount][ArrayCount2] = -100;
                            break;

                            case BS_DESTROYER:
                                DestroyerProb[ArrayCount][ArrayCount2] = -100;
                            break;

                            case BS_SUBMARINE:
                                SubmarineProb[ArrayCount][ArrayCount2] = -100;
                            break;
                        }
                    }
                }
            }
        }
        else if(DetectedCol[0] == DetectedCol[1])
        {
            for(ArrayCount = 0; ArrayCount < BS_GRID_ROWS; ArrayCount++)
            {
                for(ArrayCount2 = 0; ArrayCount2 < BS_GRID_COLS; ArrayCount2++)
                {
                    if(ArrayCount2 != DetectedCol[0])
                    {
                        switch(HitShip)
                        {
                            case BS_CARRIER:
                                CarrierProb[ArrayCount][ArrayCount2] = -100;
                            break;

                            case BS_BATTLESHIP:
                                BattleshipProb[ArrayCount][ArrayCount2] = -100;
                            break;

                            case BS_CRUISER:
                                CruiserProb[ArrayCount][ArrayCount2] = -100;
                            break;

                            case BS_DESTROYER:
                                DestroyerProb[ArrayCount][ArrayCount2] = -100;
                            break;

                            case BS_SUBMARINE:
                                SubmarineProb[ArrayCount][ArrayCount2] = -100;
                            break;
                        }
                    }
                }
            }
        }
    }
    else if(NumDetectedShots == 1)
    {
        if(DetectedRow[0] + 1 < BS_GRID_ROWS)
        {
            for(FitCount = DetectedRow[0] + 1; FitCount < BS_GRID_ROWS; FitCount++)
            {
                if(ResultTable[FitCount][DetectedCol[0]] == 0)
                    FitVert++;

                else
                    FitCount = BS_GRID_ROWS;
            }
        }

        if(DetectedRow[0] - 1 >= 0)
        {
            for(FitCount = DetectedRow[0] - 1; FitCount >= 0; FitCount--)
            {
                if(ResultTable[FitCount][DetectedCol[0]] == 0)
                    FitVert++;

                else
                    FitCount = -1;
            }
        }

        if(DetectedCol[0] + 1 < BS_GRID_COLS)
        {
            for(FitCount = DetectedCol[0] + 1; FitCount < BS_GRID_COLS; FitCount++)
            {
                if(ResultTable[DetectedRow[0]][FitCount] == 0)
                    FitHorz++;

                else
                    FitCount = BS_GRID_COLS;
            }
        }

        if(DetectedCol[0] - 1 >= 0)
        {
            for(FitCount = DetectedCol[0] - 1; FitCount >= 0; FitCount--)
            {
                if(ResultTable[DetectedRow[0]][FitCount] == 0)
                    FitHorz++;

                else
                    FitCount = -1;
            }
        }

        switch(CurrentTarget)
        {
            case BS_CARRIER:
                ShipLength = BS_CARRIER_SIZE;
            break;
            case BS_BATTLESHIP:
                ShipLength = BS_BATTLESHIP_SIZE;
            break;
            case BS_CRUISER:
                ShipLength = BS_CRUISER_SIZE;
            break;
            case BS_DESTROYER:
                ShipLength = BS_DESTROYER_SIZE;
            break;
            case BS_SUBMARINE:
                ShipLength = BS_SUBMARINE_SIZE;
            break;
        }

        if(ShipLength > 0)
        {
            if(FitVert < (ShipLength - 1))
            {
                for(FitCount = 0; FitCount < BS_GRID_ROWS; FitCount++)
                {
                    for(FitCount2 = 0; FitCount2 < BS_GRID_COLS; FitCount2++)
                    {
                        if(FitCount != DetectedRow[0])
                        {
                            switch(CurrentTarget)
                            {
                                case BS_CARRIER:
                                    CarrierProb[FitCount][FitCount2] = -1;
                                break;
                                case BS_BATTLESHIP:
                                    BattleshipProb[FitCount][FitCount2] = -1;
                                break;
                                case BS_CRUISER:
                                    CruiserProb[FitCount][FitCount2] = -1;
                                break;
                                case BS_DESTROYER:
                                    DestroyerProb[FitCount][FitCount2] = -1;
                                break;
                                case BS_SUBMARINE:
                                    SubmarineProb[FitCount][FitCount2] = -1;
                                break;
                            }
                        }
                    }
                }
            }

            if(FitHorz < (ShipLength - 1))
            {
                for(ArrayCount = 0; ArrayCount < BS_GRID_ROWS; ArrayCount++)
                {
                    for(ArrayCount2 = 0; ArrayCount2 < BS_GRID_COLS; ArrayCount2++)
                    {
                        if(ArrayCount2 != DetectedCol[0])
                        {
                            switch(CurrentTarget)
                            {
                                case BS_CARRIER:
                                    CarrierProb[ArrayCount][ArrayCount2] = -1;
                                break;
                                case BS_BATTLESHIP:
                                    BattleshipProb[ArrayCount][ArrayCount2] = -1;
                                break;
                                case BS_CRUISER:
                                    CruiserProb[ArrayCount][ArrayCount2] = -1;
                                break;
                                case BS_DESTROYER:
                                    DestroyerProb[ArrayCount][ArrayCount2] = -1;
                                break;
                                case BS_SUBMARINE:
                                    SubmarineProb[ArrayCount][ArrayCount2] = -1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}


int DetermineBestRandom(int opponent)
{
    int RunCounter;
    int ArrayCount;
    int ArrayCount2;
    int ShiftCounter;
    int LikelyCounter;
    bool bCompleted = false;
    bool bShotValid = false;
    int LoopCount = 0;
    int LikelyChoice = -1;

    NumValid = 0;

    for(RunCounter = 0; RunCounter < MAX_SHOTS; RunCounter++)
    {
        for(ArrayCount = 0; ArrayCount < BS_GRID_ROWS; ArrayCount++)
        {
            for(ArrayCount2 = 0; ArrayCount2 < BS_GRID_COLS; ArrayCount2++)
            {
                for(LikelyCounter = 0; LikelyCounter < MAX_SHOTS; LikelyCounter++)
                {
                    if(!bCompleted)
                    {
                        if((opponent >= 0) && (opponent < MAX_OPS))
                        {
                            if(((LikelyRows[LikelyCounter] <= -1) || (LikelyCols[LikelyCounter] <= -1)) || (RandProbGrid[opponent][ArrayCount][ArrayCount2] >= RandProbGrid[opponent][LikelyRows[LikelyCounter]][LikelyCols[LikelyCounter]]))
                            {
                                if((ResultTable[ArrayCount][ArrayCount2] == 0) && ((ArrayCount != LikelyRows[LikelyCounter]) && (ArrayCount2 != LikelyCols[LikelyCounter])) && ((ArrayCount + ArrayCount2) % 2 == 0))
                                {
                                    for(ShiftCounter = (MAX_SHOTS - 2); ShiftCounter >= LikelyCounter; ShiftCounter--)
                                    {
                                        if(ShiftCounter == LikelyCounter)
                                        {
                                            LikelyRows[LikelyCounter + 1] = LikelyRows[LikelyCounter];
                                            LikelyCols[LikelyCounter + 1] = LikelyCols[LikelyCounter];
                                            LikelyRows[LikelyCounter] = ArrayCount;
                                            LikelyCols[LikelyCounter] = ArrayCount2;
                                        }
                                        else
                                        {
                                            LikelyRows[LikelyCounter + 1] = LikelyRows[LikelyCounter];
                                            LikelyCols[LikelyCounter + 1] = LikelyCols[LikelyCounter];
                                        }
                                    }

                                    bCompleted = true;

                                    if(NumValid < MAX_SHOTS)
                                        NumValid++;
                                }
                            }
                        }
                        else
                        {
                            NumValid = 0;
                            bCompleted = true;
                        }
                    }
                }

                bCompleted = false;
            }
        }
    }

    while((!bShotValid) && (LoopCount < LOOP_LIMIT))
    {
        if(NumValid > 0)
            LikelyChoice = rand() % NumValid;

        if((GameNum > 0) && (NumValid > 0) && (LikelyRows[LikelyChoice] > -1) && (LikelyCols[LikelyChoice] > -1) && (ResultTable[LikelyRows[LikelyChoice]][LikelyCols[LikelyChoice]] == 0))
        {
            BestRow = LikelyRows[LikelyChoice];
            BestCol = LikelyCols[LikelyChoice];
        }
        else
        {
            BestRow = (rand() % BS_GRID_ROWS);
            BestCol = ((BestRow  % 2) + 1) + (2 * (rand() % (BS_GRID_COLS / 2)));
        }

        if((((BestRow >= 0) && (BestRow < BS_GRID_ROWS)) && ((BestCol >= 0) && (BestCol < BS_GRID_COLS))) && (ResultTable[BestRow][BestCol] == 0))
            bShotValid = true;
        else
            bShotValid = false;

        LoopCount++;
    }

    LoopCount = 0;

    while((!bShotValid) && (LoopCount < LOOP_LIMIT))
    {
        BestRow = (rand() % BS_GRID_ROWS);
        BestCol = (rand() % BS_GRID_COLS);

        if(ResultTable[BestRow][BestCol] == 0)
            bShotValid = true;
        else
            bShotValid = false;

        LoopCount++;
    }

    if(!bShotValid)
    {
        for(ArrayCount = 0; ArrayCount < BS_GRID_ROWS; ArrayCount++)
        {
            for(ArrayCount2 = 0; ArrayCount2 < BS_GRID_COLS; ArrayCount2++)
            {
                if((ResultTable[ArrayCount][ArrayCount2] >= -1) && (!bShotValid))
                {
                    BestRow = ArrayCount;
                    BestCol = ArrayCount;
                    bShotValid = true;
                }
            }
        }

        if(!bShotValid)
        {
            BestRow = (rand() % BS_GRID_ROWS);
            BestCol = (rand() % BS_GRID_COLS);
            bShotValid = true;
        }
    }

    return 0;
}


int DetermineBestShipShot(int ShipNum)
{
    int ArrayCount;
    int ArrayCount2;
    int HighestProb = -2;
    bool bShotValid = false;
    int LoopCount;

    while((!bShotValid) && (LoopCount < LOOP_LIMIT))
    {
        for(ArrayCount = 0; ArrayCount < BS_GRID_ROWS; ArrayCount++)
        {
            for(ArrayCount2 = 0; ArrayCount2 < BS_GRID_COLS; ArrayCount2++)
            {
                switch (ShipNum)
                {
                    case BS_CARRIER:
                        if(CarrierProb[ArrayCount][ArrayCount2] > HighestProb)
                        {
                            HighestProb = CarrierProb[ArrayCount][ArrayCount2];
                            TargRow = ArrayCount;
                            TargCol = ArrayCount2;
                        }
                    break;

                    case BS_BATTLESHIP:
                        if(BattleshipProb[ArrayCount][ArrayCount2] > HighestProb)
                        {
                            HighestProb = BattleshipProb[ArrayCount][ArrayCount2];
                            TargRow = ArrayCount;
                            TargCol = ArrayCount2;
                        }
                    break;

                    case BS_CRUISER:
                        if(CruiserProb[ArrayCount][ArrayCount2] > HighestProb)
                        {
                            HighestProb = CruiserProb[ArrayCount][ArrayCount2];
                            TargRow = ArrayCount;
                            TargCol = ArrayCount2;
                        }
                    break;

                    case BS_DESTROYER:
                        if(DestroyerProb[ArrayCount][ArrayCount2] > HighestProb)
                        {
                            HighestProb = DestroyerProb[ArrayCount][ArrayCount2];
                            TargRow = ArrayCount;
                            TargCol = ArrayCount2;
                        }
                    break;

                    case BS_SUBMARINE:
                        if(SubmarineProb[ArrayCount][ArrayCount2] > HighestProb)
                        {
                            HighestProb = SubmarineProb[ArrayCount][ArrayCount2];
                            TargRow = ArrayCount;
                            TargCol = ArrayCount2;
                        }
                    break;
                }
            }
        }

        if((ResultTable[TargRow][TargCol] >= -1) && (ResultTable[TargRow][TargCol] < 1))
            bShotValid = true;

        LoopCount++;
    }

    return 0;
}

int RoninAttack(int mode, int opponent)
{
    char Row;
    int Col;
    int IntRow;
    int IntCol;
    int ReturnCode = -868686;

    switch(mode)
    {
        case BS_MODE_NEW_GAME:
        break;

        case BS_MODE_CONTINUE_GAME:

            bTouches = DetermineTouch();

            if(CurrentTarget == -1)
                CurrentTarget = DetermineTarget();

            SmallestFitLogic();

            if(CarrierState < 3)
                FitShipLogic(BS_CARRIER, BS_CARRIER_SIZE);
            if(BattleshipState < 3)
                FitShipLogic(BS_BATTLESHIP, BS_BATTLESHIP_SIZE);
            if(CruiserState < 3)
                FitShipLogic(BS_CRUISER, BS_CRUISER_SIZE);
            if(DestroyerState < 3)
                FitShipLogic(BS_DESTROYER, BS_DESTROYER_SIZE);
            if(SubmarineState < 3)
                FitShipLogic(BS_SUBMARINE, BS_SUBMARINE_SIZE);

            if(CurrentTarget == -1)
            {
                DetermineBestRandom(opponent);

                if(((BestRow >= 0) && (BestRow < BS_GRID_ROWS)) && ((BestCol >= 0) && (BestCol < BS_GRID_COLS)))
                {
                    Row = ConvertToGridRow(BestRow);
                    Col = ConvertToGridCol(BestCol);
                    ReturnCode = fire[opponent](Row, Col);
                }
            }
            else
            {
                DetermineBestShipShot(CurrentTarget);

                if(((TargRow >= 0) && (TargRow < BS_GRID_ROWS)) && ((TargCol >= 0) && (TargCol < BS_GRID_COLS)))
                {
                    Row = ConvertToGridRow(TargRow);
                    Col = ConvertToGridCol(TargCol);
                    ReturnCode = fire[opponent](Row, Col);
                }
            }

            IntRow = ConvertToArrayRow(Row);
            IntCol = ConvertToArrayCol(Col);

            if(ReturnCode == 0)
            {
                CarrierProb[IntRow][IntCol] = -1000;
                BattleshipProb[IntRow][IntCol] = -1000;
                CruiserProb[IntRow][IntCol] = -1000;
                DestroyerProb[IntRow][IntCol] = -1000;
                SubmarineProb[IntRow][IntCol] = -1000;
                ResultTable[IntRow][IntCol] = -1000;
                if((opponent >= 0) && (opponent < MAX_OPS))
                    RandProbGrid[opponent][IntRow][IntCol] = -1000;
            }
            else if((ReturnCode & BS_SHIP_HIT) && (ReturnCode & BS_SHIP_SANK))
            {
                if((opponent >= 0) && (opponent < MAX_OPS))
                {
                    TrackedShots[opponent][IntRow][IntCol] += 1;
                    RandProbGrid[opponent][IntRow][IntCol] = -1000;
                }

                CarrierProb[IntRow][IntCol] = -1000;
                BattleshipProb[IntRow][IntCol] = -1000;
                CruiserProb[IntRow][IntCol] = -1000;
                DestroyerProb[IntRow][IntCol] = -1000;
                SubmarineProb[IntRow][IntCol] = -1000;

                switch(ReturnCode & BS_SHIP_MASK)
                {
                    case BS_CARRIER:
                        ResultTable[IntRow][IntCol] = BS_CARRIER;
                        CarrierState = 3;
                        CurrentTarget = -1;

                        if(!bTouches)
                            Bushido(BS_CARRIER, opponent);
                    break;

                    case BS_BATTLESHIP:

                        ResultTable[IntRow][IntCol] = BS_BATTLESHIP;
                        BattleshipState = 3;
                        CurrentTarget = -1;

                        if(!bTouches)
                            Bushido(BS_BATTLESHIP, opponent);
                    break;

                    case BS_CRUISER:
                        ResultTable[IntRow][IntCol] = BS_CRUISER;
                        CruiserState = 3;
                        CurrentTarget = -1;

                        if(!bTouches)
                            Bushido(BS_CRUISER, opponent);
                    break;

                    case BS_DESTROYER:
                        ResultTable[IntRow][IntCol] = BS_DESTROYER;
                        DestroyerState = 3;
                        CurrentTarget = -1;

                        if(!bTouches)
                            Bushido(BS_DESTROYER, opponent);
                    break;

                    case BS_SUBMARINE:
                        ResultTable[IntRow][IntCol] = BS_SUBMARINE;
                        SubmarineState = 3;
                        CurrentTarget = -1;

                        if(!bTouches)
                            Bushido(BS_SUBMARINE, opponent);
                    break;
                }

                TargRow = -1;
                TargCol = -1;
            }
            else if(ReturnCode & BS_SHIP_HIT)
            {
                if((opponent >= 0) && (opponent < MAX_OPS))
                {
                    TrackedShots[opponent][IntRow][IntCol] += 1;
                    RandProbGrid[opponent][IntRow][IntCol] = -1000;
                }

                CarrierProb[IntRow][IntCol] = -1000;
                BattleshipProb[IntRow][IntCol] = -1000;
                CruiserProb[IntRow][IntCol] = -1000;
                DestroyerProb[IntRow][IntCol] = -1000;
                SubmarineProb[IntRow][IntCol] = -1000;

                switch(ReturnCode & BS_SHIP_MASK)
                {
                     case BS_CARRIER:
                        ResultTable[IntRow][IntCol] = BS_CARRIER;

                        if(CarrierState == 0)
                            CarrierState = 1;

                        if(CurrentTarget == -1)
                        {
                            CurrentTarget = BS_CARRIER;
                            CarrierState = 2;
                        }

                        DetermineOrientation(BS_CARRIER);

                        if((IntRow + 1 < BS_GRID_ROWS) && (ResultTable[IntRow + 1][IntCol] == 0) && ((CarrierProb[IntRow + 1][IntCol] == 0) || (CarrierProb[IntRow + 1][IntCol] > 1)))
                            CarrierProb[IntRow + 1][IntCol] += 4;
                        if((IntRow - 1 >= 0) && (ResultTable[IntRow - 1][IntCol] == 0) && ((CarrierProb[IntRow - 1][IntCol] == 0) || (CarrierProb[IntRow - 1][IntCol] > 1)))
                            CarrierProb[IntRow - 1][IntCol] += 4;
                        if((IntCol + 1 < BS_GRID_COLS) && (ResultTable[IntRow][IntCol + 1] == 0) && ((CarrierProb[IntRow][IntCol + 1] == 0) || (CarrierProb[IntRow][IntCol + 1] > 1)))
                            CarrierProb[IntRow][IntCol + 1] += 4;
                        if((IntCol - 1 >= 0) && (ResultTable[IntRow][IntCol - 1] == 0) && ((CarrierProb[IntRow][IntCol - 1] == 0) || (CarrierProb[IntRow][IntCol - 1] > 1)))
                            CarrierProb[IntRow][IntCol - 1] += 4;
                    break;

                    case BS_BATTLESHIP:
                        ResultTable[IntRow][IntCol] = BS_BATTLESHIP;

                        if(BattleshipState == 0)
                            BattleshipState = 1;

                        if(CurrentTarget == -1)
                        {
                            CurrentTarget = BS_BATTLESHIP;
                            BattleshipState = 2;
                        }

                        DetermineOrientation(BS_BATTLESHIP);

                        if((IntRow + 1 < BS_GRID_ROWS) && (ResultTable[IntRow + 1][IntCol] == 0) && ((BattleshipProb[IntRow + 1][IntCol] == 0) || (BattleshipProb[IntRow + 1][IntCol] > 1)))
                            BattleshipProb[IntRow + 1][IntCol] += 4;
                        if((IntRow - 1 >= 0) && (ResultTable[IntRow - 1][IntCol] == 0) && ((BattleshipProb[IntRow - 1][IntCol] == 0) || (BattleshipProb[IntRow - 1][IntCol] > 1)))
                            BattleshipProb[IntRow - 1][IntCol] += 4;
                        if((IntCol + 1 < BS_GRID_COLS) && (ResultTable[IntRow][IntCol + 1] == 0) && ((BattleshipProb[IntRow][IntCol + 1] == 0) || (BattleshipProb[IntRow][IntCol + 1] > 1)))
                            BattleshipProb[IntRow][IntCol + 1] += 4;
                        if((IntCol - 1 >= 0) && (ResultTable[IntRow][IntCol - 1] == 0) && ((BattleshipProb[IntRow][IntCol - 1] == 0) || (BattleshipProb[IntRow][IntCol - 1] > 1)))
                            BattleshipProb[IntRow][IntCol - 1] += 4;
                    break;

                    case BS_CRUISER:
                        ResultTable[IntRow][IntCol] = BS_CRUISER;

                        if(CruiserState == 0)
                            CruiserState = 1;

                        if(CurrentTarget == -1)
                        {
                            CurrentTarget = BS_CRUISER;
                            CruiserState = 2;
                        }

                        DetermineOrientation(BS_CRUISER);

                        if((IntRow + 1 < BS_GRID_ROWS) && (ResultTable[IntRow + 1][IntCol] == 0) && ((CruiserProb[IntRow + 1][IntCol] == 0) || (CruiserProb[IntRow + 1][IntCol] > 1)))
                            CruiserProb[IntRow + 1][IntCol] += 4;
                        if((IntRow - 1 >= 0) && (ResultTable[IntRow - 1][IntCol] == 0) && ((CruiserProb[IntRow - 1][IntCol] == 0) || (CruiserProb[IntRow - 1][IntCol] > 1)))
                            CruiserProb[IntRow - 1][IntCol] += 4;
                        if((IntCol + 1 < BS_GRID_COLS) && (ResultTable[IntRow][IntCol + 1] == 0) && ((CruiserProb[IntRow][IntCol + 1] == 0) || (CruiserProb[IntRow][IntCol + 1] > 1)))
                            CruiserProb[IntRow][IntCol + 1] += 4;
                        if((IntCol - 1 >= 0) && (ResultTable[IntRow][IntCol - 1] == 0) && ((CruiserProb[IntRow][IntCol - 1] == 0) || (CruiserProb[IntRow][IntCol - 1] > 1)))
                            CruiserProb[IntRow][IntCol - 1] += 4;
                    break;

                    case BS_DESTROYER:
                        ResultTable[IntRow][IntCol] = BS_DESTROYER;

                        if(DestroyerState == 0)
                            DestroyerState = 1;

                        if(CurrentTarget == -1)
                        {
                            CurrentTarget = BS_DESTROYER;
                            DestroyerState = 2;
                        }

                        DetermineOrientation(BS_DESTROYER);

                        if((IntRow + 1 < BS_GRID_ROWS) && (ResultTable[IntRow + 1][IntCol] == 0) && ((DestroyerProb[IntRow + 1][IntCol] == 0) || (DestroyerProb[IntRow + 1][IntCol] > 1)))
                            DestroyerProb[IntRow + 1][IntCol] += 4;
                        if((IntRow - 1 >= 0) && (ResultTable[IntRow - 1][IntCol] == 0) && ((DestroyerProb[IntRow - 1][IntCol] == 0) || (DestroyerProb[IntRow - 1][IntCol] > 1)))
                            DestroyerProb[IntRow - 1][IntCol] += 4;
                        if((IntCol + 1 < BS_GRID_COLS) && (ResultTable[IntRow][IntCol + 1] == 0) && ((DestroyerProb[IntRow][IntCol + 1] == 0) || (DestroyerProb[IntRow][IntCol + 1] > 1)))
                            DestroyerProb[IntRow][IntCol + 1] += 4;
                        if((IntCol - 1 >= 0) && (ResultTable[IntRow][IntCol - 1] == 0) && ((DestroyerProb[IntRow][IntCol - 1] == 0) || (DestroyerProb[IntRow][IntCol - 1] > 1)))
                            DestroyerProb[IntRow][IntCol - 1] += 4;
                    break;

                    case BS_SUBMARINE:
                        ResultTable[IntRow][IntCol] = BS_SUBMARINE;

                        if(SubmarineState == 0)
                            SubmarineState = 1;

                        if(CurrentTarget == -1)
                        {
                            CurrentTarget = BS_SUBMARINE;
                            SubmarineState = 2;
                        }

                        DetermineOrientation(BS_SUBMARINE);

                        if((IntRow + 1 < BS_GRID_ROWS) && (ResultTable[IntRow + 1][IntCol] == 0) && ((SubmarineProb[IntRow + 1][IntCol] == 0) || (SubmarineProb[IntRow + 1][IntCol] > 1)))
                            SubmarineProb[IntRow + 1][IntCol] += 4;
                        if((IntRow - 1 >= 0) && (ResultTable[IntRow - 1][IntCol] == 0) && ((SubmarineProb[IntRow - 1][IntCol] == 0) || (SubmarineProb[IntRow - 1][IntCol] > 1)))
                            SubmarineProb[IntRow - 1][IntCol] += 4;
                        if((IntCol + 1 < BS_GRID_COLS) && (ResultTable[IntRow][IntCol + 1] == 0) && ((SubmarineProb[IntRow][IntCol + 1] == 0) || (SubmarineProb[IntRow][IntCol + 1] > 1)))
                            SubmarineProb[IntRow][IntCol + 1] += 4;
                        if((IntCol - 1 >= 0) && (ResultTable[IntRow][IntCol - 1] == 0) && ((SubmarineProb[IntRow][IntCol - 1] == 0) || (SubmarineProb[IntRow][IntCol - 1] > 1)))
                            SubmarineProb[IntRow][IntCol - 1] += 4;
                    break;
                }
            }

            if(CarrierState < 3)
                FitShipLogic(BS_CARRIER, BS_CARRIER_SIZE);
            if(BattleshipState < 3)
                FitShipLogic(BS_BATTLESHIP, BS_BATTLESHIP_SIZE);
            if(CruiserState < 3)
                FitShipLogic(BS_CRUISER, BS_CRUISER_SIZE);
            if(DestroyerState < 3)
                FitShipLogic(BS_DESTROYER, BS_DESTROYER_SIZE);
            if(SubmarineState < 3)
                FitShipLogic(BS_SUBMARINE, BS_SUBMARINE_SIZE);
        break;
    }

    return 0;
}


//int (*fire[MaxPlayerCount])(char, int)= {NULL, RoninIncomingFire};
//int (*battleship[MaxPlayerCount])(int, int) = {NULL, RoninAttack};
//char const *playerName[MaxPlayerCount] = {"", "Ronin"};
