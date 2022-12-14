#ifndef BATTLESHIP
#define BATTLESHIP
const int BS_SHIP_HIT = 0x010;  // Ship is hit, or
const int BS_SHIP_SANK = 0x020; // sank (must also | BS_SHIP_HIT)
const int BS_CARRIER = 0x001;
const int BS_BATTLESHIP = 0x002;
const int BS_CRUISER = 0x003;
const int BS_DESTROYER = 0x004;
const int BS_SUBMARINE = 0x005;
const int BS_SHIP_COUNT = 0x005;
const int BS_SHIP_MASK = 0x0F;
const int BS_CARRIER_SIZE = 5;
const int BS_BATTLESHIP_SIZE = 4;
const int BS_CRUISER_SIZE = 3;
const int BS_DESTROYER_SIZE = 2;
const int BS_SUBMARINE_SIZE = 3;
const int BS_MODE_NEW_GAME = 1;
const int BS_MODE_CONTINUE_GAME = 2;
const int BS_GRID_ROWS = 10; // letters A to J
const int BS_GRID_COLS = 10; // numbers 1 to 10
const int MaxPlayerCount = 65; // Maximum size for following arrays

// Pre-defined interactive functions
extern int userIncoming(char, int); //Student may reference these for testing
extern int userBattle(int, int);

// Student must define and initialize these three using MaxPlayerCount
extern int (*fire[])(char, int);
extern int (*battleship[])(int, int);
extern char const *playerName[];
#endif
