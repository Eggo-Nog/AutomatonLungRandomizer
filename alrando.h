#ifndef alrando_h
#define alrando_h

// MACROS

#define LEVEL_COUNT 54
#define WARP_COUNT 108
#define WARP_POOL_SIZE 78


// ========== STRUCT DEFINITIONS ==========

// Basic warp struct
struct Warp {
	std::string level; // The named level this warp originally leads to
	int entranceID; // The numbered entrance this warp originally lead to
};

// Struct which associates a warp with its placement in the game files
struct FileWarp {
	std::string parentLevel; // The named (I.e. "TownD") level the warp is in
	int offset; // File offset of the warp
	Warp destination; // The warp itself (as in, the level and entrance it points to)
};



// ========== FUNCTION CONSTRUCTORS ==========

// WARP RANDOMIZATION FUNCTIONS

// Writes the warp indicated by the FileWarp struct passed
// Returns 0 if successful, -1 if fstream.good() returns false at any point (indicating a file I/O error)
int writeFileWarp(FileWarp f);

// Given a list of all FileWarps, write them into their corresponding files
// Returns 0 if successful, returns -1 if any writeFileWarp() calls return -1 indicating a file I/O error
int writeAllFileWarps(std::array<FileWarp, WARP_COUNT> f);

// Checks if islands (areas in the layout where the player can become trapped) are present in f, and calls removeIslands() to try and fix any found
// Returns 0 if successful, and -1 if islands are detected but they can't be removed for any reason
std::array<FileWarp, WARP_COUNT> checkForIslands(std::array<FileWarp, WARP_COUNT> f);

// Finds the number of levels that can be visited from startingLevel using breadth first search
// Returns the number of vertices marked as visited
int findIslandSize(std::string startingLevel, std::map<std::string, std::vector<std::string>> adjacencyList);

// Attempts to remove an island in a layout by redirecting a warp in it to the elevator
// Candidate warps are chosen by first looking for duplicates, then tower floor warps, then warps that are not inside of a protected blacklist
// Returns 0 if successful, -1 if it couldn't find any suitable warps to replace
std::array<FileWarp, WARP_COUNT> removeIslands(std::array<FileWarp, WARP_COUNT> f, std::map<std::string, std::vector<std::string>> adjacencyList, std::string islandLevel);

// Randomizes the game layout described in the FileWarp array pointed to by f and returns the new layout
std::array<FileWarp, WARP_COUNT> generateGameLayout(std::array<FileWarp, WARP_COUNT> f, int flags, int seed);


// OTHER GAMEPLAY CHANGING FUNCTIONS

// Overwrite the flight speed and rotate speed of the beetle
// Pass 1 for faster beetle, 0 for default beetle, all other values exit immediately without changes
// Returns 0 if successful, returns -1 if any file I/O errors are encountered
int makeBeetleFast(int mode);

// Shuffles around which weapons are found in which weapon areas, or restores them to original values
// Pass 1 to randomize, 2 to repair, all other values will exit immediately without changes
// Returns 0 if successful, returns -1 if any file I/O errors are encountered
int randomizeWeapons(int mode, int seed);

// If 1 is passed, moves the HaroldStrange in Collectible Tracker Interior behind the 210 chip gate, and brings the weapon pickup ahead of both chip gates
// If 2 is passed, it returns both objects to their original locations
// All other values exit immediately without changes
// Returns 0 if successful, returns -1 if any file I/O errors are encountered
// int adjustCollectibleTrackerInterior(int mode); <-- Commented out because I don't know how to modify object coordinates yet


#endif