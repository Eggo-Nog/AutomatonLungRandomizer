// C++ includes
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
#include <random>
#include <numeric>
#include <array>

// Header includes
#include "alrando.h"

// Maps level names to file names (I.e. "TownD" resolves to "level10")
std::map<std::string, std::string> levelMap = {
	{"BeetleFlightTest", "level2"},
	{"AutomatonBoss", "level4"},
	{"AutomatonDefeatCutscene", "level6"},
	{"TownA", "level7"},
	{"TownB", "level8"},
	{"TownC", "level9"},
	{"TownD", "level10"},
	{"TownDInterior1", "level11"},
	{"TownBPyramidInterior", "level12"},
	{"TownBWeaponRoom", "level13"},
	{"CollectibleTrackerEntrance", "level14"},
	{"CollectibleTrackerInterior", "level15"},
	{"Floor 0", "level16"},
	{"Floor 1", "level17"},
	{"Floor 2", "level18"},
	{"Floor 3", "level19"},
	{"Floor 4", "level20"},
	{"Floor 5", "level21"},
	{"Floor 6", "level22"},
	{"Floor 7", "level23"},
	{"Floor 8", "level24"},
	{"Floor 9", "level25"},
	{"Floor 10", "level26"},
	{"Floor 11", "level27"},
	{"Floor 12", "level28"},
	{"Floor 13", "level29"},
	{"Floor 14", "level30"},
	{"Floor 15", "level31"},
	{"Floor 16", "level32"},
	{"Floor 17", "level33"},
	{"Floor 18", "level34"},
	{"Floor 19", "level35"},
	{"Floor 20", "level36"},
	{"Floor 21", "level37"},
	{"TownE", "level38"},
	{"TownEInterior 1", "level39"},
	{"TownABuildingInterior", "level40"},
	{"TownABuildingInterior 1", "level41"},
	{"TownC 1", "level42"},
	{"TownC 2", "level43"},
	{"TownC 3", "level44"},
	{"TownD 1", "level45"},
	{"AutomatonBossSecondPhase", "level46"},
	{"AutomatonBossMaze", "level48"},
	{"FinalCutscene", "level49"},
	{"CollapsingEscapeRoom", "level50"},
	{"FinalCutscene 1", "level51"},
	{"HorseshoeCrabBeach", "level52"},
	{"EndlessGrassyPlane", "level53"},
	{"RapidFireWeaponArea", "level54"},
	{"RapidFireWeaponArea 1", "level55"},
	{"Harold", "level56"},
	{"Harold 2", "level64"},
	{"AtlantisMainRoom", "level70"}
}; 



// This should be filled dynamically according to flags, but I'm putting it here since this version doesn't do that yet
// Comments indicate string length changes (for easily placing new warps in the correct location)
// It is important for logic reasons that this is sorted by string length in descending order
Warp warpPool[WARP_POOL_SIZE] = {
	{"TownABuildingInterior 1", 0}, //23
	{"TownABuildingInterior 1", 1},
	{"TownABuildingInterior", 0}, //21
	{"TownABuildingInterior", 1},
	{"TownABuildingInterior", 2},
	{"RapidFireWeaponArea 1", 0},
	{"TownBPyramidInterior", 0}, //20
	{"TownBPyramidInterior", 1},
	{"RapidFireWeaponArea", 1}, //19
	{"RapidFireWeaponArea", -1},	
	{"EndlessGrassyPlane", -1}, //18
	{"HorseshoeCrabBeach", -1},
	{"BeetleFlightTest", 0}, //16
	{"BeetleFlightTest", 1},
	{"BeetleFlightTest", 2},
	{"BeetleFlightTest", 3},
	{"BeetleFlightTest", 4},
	{"BeetleFlightTest", 5},
	{"BeetleFlightTest", 6},
	{"BeetleFlightTest", 7},
	{"BeetleFlightTest", 8},
	{"BeetleFlightTest", 9},
	{"AtlantisMainRoom", 0},
	{"TownBWeaponRoom", 0}, //15
	{"TownEInterior 1", 0},
	{"TownEInterior 1", 1},
	{"TownDInterior1", 0}, //14
	{"TownDInterior1", 1},	
	{"Floor 10", 0}, //8
	{"Floor 11", 0},
	{"Floor 12", 0},
	{"Floor 13", 0},
	{"Floor 14", 0},
	{"Floor 15", 0},
	{"Floor 16", 0},
	{"Floor 17", 0},
	{"Floor 18", 0},
	{"Floor 19", 0},
	{"Floor 20", 0},
	{"Floor 21", 1},
	{"Floor 21", 2},
	{"Harold 2", 0},
	{"Floor 0", 0}, //7
	{"Floor 0", 1},
	{"Floor 1", 0},
	{"Floor 2", 0},
	{"Floor 3", 0},
	{"Floor 4", 0},
	{"Floor 5", 0},
	{"Floor 6", 0},
	{"Floor 7", 0},
	{"Floor 8", 0},
	{"Floor 9", 0},
	{"TownC 1", 0},
	{"TownC 1", 1},
	{"TownC 1", 2},
	{"TownC 2", 0},
	{"TownC 3", 0},
	{"TownD 1", 0},
	{"Harold", 0}, //6
	{"TownA", -1}, //5
	{"TownA", 1},
	{"TownA", 2},
	{"TownA", 3},
	{"TownA", 4},
	{"TownA", 5},
	{"TownB", -1},
	{"TownB", 1},
	{"TownB", 2},
	{"TownB", 3},
	{"TownC", -1},
	{"TownC", 1},
	{"TownD", -1},
	{"TownD", 0},
	{"TownD", 1},
	{"TownE", -1},
	{"TownE", 1},
	{"TownE", 2}
};

int writeFileWarp(FileWarp f) {
	// Open file
	std::fstream levelFile;
	levelFile.open(levelMap[f.parentLevel]);
	if (!levelFile.good() || !levelFile.is_open()) return -1; // error checking
	
	// Overwrite string length byte
	levelFile.seekp(f.offset);
	levelFile.put((unsigned char) f.destination.level.size());
	
	// Overwrite destination name
	levelFile.seekp(f.offset+4);
	levelFile.write(f.destination.level.c_str(), f.destination.level.size());
	
	// Overwrite entrance ID
	levelFile.seekp((f.destination.level.size()-1) - ((f.destination.level.size()-1)%4) + 8 + f.offset);
	int i;
	if (f.destination.entranceID == -1){
		for (i = 0; i<4; i++){
			levelFile.put((unsigned char) 255);
		}
	} else {
		levelFile.put((unsigned char) f.destination.entranceID);
		//  Overwrite empty space with null bytes incase this was previously a -1 entrance
		for (i = 0; i<3; i++){
			levelFile.put((unsigned char) 0);
		}
	}
	
	// If fstream still reports good, then close and return
	if (!levelFile.good()) {
		levelFile.close();
		return -1;
	}
	levelFile.close();
	return 0;
}

int writeAllFileWarps(std::array<FileWarp, WARP_COUNT> f){
	// Call writeFileWarp() for every FileWarp object in list, return -1 if any calls return -1, return 0 otherwise
	for (int i = 0; i < WARP_COUNT; i++){
		if (writeFileWarp(f[i]) == -1) return -1;
	}
	return 0;
}

int randomizeWeapons(int mode, int seed){
	// The weapons are all off by one on their pickups (so a weapon pickup for "1" gives you weapon 2, etc.)
	std::vector<int> wepList{1, 2, 3, 4}; 
	
	if (mode == 1) {
		std::random_device rd;
		std::mt19937 g(seed);//rd()
		std::shuffle(wepList.begin(), wepList.end(), g);
	}

	if (mode == 1 || mode == 2) {
		std::fstream w2File, w3File, w4File, w5File;
		
		// Overwrite Weapon 2
		w2File.open(levelMap["HorseshoeCrabBeach"]);
		w2File.seekp(228700);
		w2File.put((unsigned char) wepList[0]);
		
		
		// Overwrite Weapon 3
		w3File.open(levelMap["RapidFireWeaponArea 1"]);
		w3File.seekp(114612);
		w3File.put((unsigned char) wepList[1]);
		
		
		// Overwrite Weapon 4
		w4File.open(levelMap["EndlessGrassyPlane"]);
		w4File.seekp(483812);
		w4File.put((unsigned char) wepList[2]);
		
		
		// Overwrite Weapon 5
		w5File.open(levelMap["CollectibleTrackerInterior"]);
		w5File.seekp(81732);
		w5File.put((unsigned char) wepList[3]);
		
		// Return -1 if any fstream's aren't good
		if ( !w2File.good() || !w3File.good() || !w4File.good() || !w5File.good() ) return -1;
		w2File.close();
		w3File.close();
		w4File.close();
		w5File.close();
		
	}
	
	return 0;
}

std::array<FileWarp, WARP_COUNT> generateGameLayout(std::array<FileWarp, WARP_COUNT> f, int flags, int seed) {
	
	// 1. Create vectors for queueing warps to be randomized
	
	// Initialise a vector queuedWarps containing numbers 1 to WARP_COUNT
	std::vector<int> queuedWarps(WARP_COUNT);
	std::iota(queuedWarps.begin(), queuedWarps.end(), 0);
	
	// Create a separate vector for BeetleFlightTest warps
	std::vector<int> bftWarps{};
	
	
	// 2. Check every warp to see if it's blacklisted or relevant to a flag
	
	// This should be changed to a set
	// The following levels are always blacklisted regardless of flags since their warps are necessary for the game to be beatable
	// Any warps directed towards these levels will not be randomized
	std::vector<std::string> blacklist{
		"CollectibleTrackerEntrance", 
		"CollectibleTrackerInterior", 
		"AutomatonBoss",
		"AutomatonDefeatCutscene",
		"CollapsingEscapeRoom",
		"AutomatonBossMaze",
		"AutomatonBossSecondPhase",
		"FinalCutscene 1", 
		"FinalCutscene", 
		"TitleMenu",
		"Harold", // Included because their warps aren't reasonable for a player to reach
		"AutomatonBossEscape"
	};
	
	
	// Now we adjust every remaining warp according to flags
	bool removeWarp;
	for (int i = 0; i < queuedWarps.size(); i++) {
		// Reset removeWarp bool
		removeWarp = false;
		
		// FLAGS APPLIED HERE
		
		// "BeetleFlightTest warps should be bundled together" flag
		if (flags & 1) { 
			if (f[queuedWarps[i]].destination.level == "BeetleFlightTest") {
				bftWarps.push_back(queuedWarps[i]);
				removeWarp = true;
			}
		}
		
		// "Allow Easter Egg Levels" Flag
		if (flags & 2) {
			std::cout << "Trying to apply \"Allow Easter Egg Levels\" Flag without implementation...\n";
		}

		// This is slower than removing them by their indexes (which are known) but this is more readable, and is resillient to blacklist changes
		// The use of std::find itself could also be improved since it uses linear search, which is slow
		if (std::find(blacklist.begin(), blacklist.end(), f[queuedWarps[i]].destination.level) != blacklist.end()) removeWarp = true;
		
		// Remove warp at i and decrement i (since the index doesn't need to move up)
		if (removeWarp) {
			queuedWarps.erase(queuedWarps.begin()+i);
			i--;
		}

	}
	
	// 3. Shuffle queuedWarps and assign warps in turn from the Warp Pool
	
	// Randomly shuffle queuedWarps
	std::random_device rd;
	std::mt19937 g(seed);
	std::shuffle(queuedWarps.begin(), queuedWarps.end(), g);
	
	// Guarantees every warp in the pool shows up at least once
	for (int i = 0; i < WARP_POOL_SIZE; i++){ // For every warp pool warp
		int j = 0;
		bool goodDest = false;
		while (!goodDest){ // Find the first warp in queuedWarps that fits and ISN'T the original warp destination
			int n = f[queuedWarps[j]].destination.level.size();
			if (((n-1) + (4 - ((n-1)%4))) >= warpPool[i].level.size() && warpPool[i].level != f[queuedWarps[j]].parentLevel) {
				goodDest = true;
				f[queuedWarps[j]].destination = warpPool[i];
				queuedWarps.erase(queuedWarps.begin()+j); 
			}
			j++;
			
			// If j somehow gets too high, immediately exit to avoid any issues
			if (j > queuedWarps.size()) {
				goodDest = true;
			}
		}
	}
	
	// 4. Fill remaining queuedWarps with random selections from the pool
	for (int i = 0; i < queuedWarps.size(); i++) {
		bool goodSize = false;
		while (!goodSize) {
			int n = f[queuedWarps[i]].destination.level.size();
			int m = std::rand() % WARP_POOL_SIZE;
			if (((n-1) + (4 - ((n-1)%4))) >= warpPool[m].level.size()) {
				goodSize = true;
				f[queuedWarps[i]].destination = warpPool[m];
			}
		}
	}
	
	return f;
}	

int makeBeetleFast(int mode){
	// 1 for speed, 0 for repair
	std::fstream bftFile;
	if (mode == 1) {
		
		bftFile.open(levelMap["BeetleFlightTest"]);
		bftFile.seekp(133906);
		bftFile.put((unsigned char) 250);
		bftFile.seekp(133910);
		bftFile.put((unsigned char) 200);
		
	} else if (mode == 0) {
		
		bftFile.open(levelMap["BeetleFlightTest"]);
		bftFile.seekp(133906);
		bftFile.put((unsigned char) 52);
		bftFile.seekp(133910);
		bftFile.put((unsigned char) 112);
		
	}
	if (mode == 1 || mode == 2) {
		if (!bftFile.good()) return -1;
		bftFile.close();
	}
	return 0;
}

std::array<FileWarp, WARP_COUNT> checkForIslands(std::array<FileWarp, WARP_COUNT> f){
	
	bool islands = true;
	bool elevatorInLayout = false;
	int i = 0, timeout = 0, islandSize = 0, smallestIslandSize = 99;
	std::string islandLevel;
	
	std::map<std::string, std::vector<std::string>> adjacencyList;
	
	std::vector<std::string> endgameLevels = {
		"AutomatonBoss",
		"AutomatonDefeatCutscene",
		"CollapsingEscapeRoom",
		"AutomatonBossMaze",
		"AutomatonBossSecondPhase",
		"FinalCutscene 1"
	};
	
	while (islands && timeout < 10){
		// Reset island info
		islandLevel = "defaultTest";
		smallestIslandSize = 99;
		
		// 1. Create an adjacency list from f
		// Clear adjacency list following removeIslands() calls
		adjacencyList.clear(); 
		// Write in all warps from the game
		for (i = 0; i < WARP_COUNT; i++) {
			adjacencyList[f[i].parentLevel].push_back(f[i].destination.level);
		}
		// Add in special entry for elevator since it doesn't contain traditional warps
		for (i = 0; i < 22; i++) {
			adjacencyList["Elevator"].push_back("Floor " + std::to_string(i));
		}
		
		
		// 2. Check the findIslandSize() result for every level in the adjacency list, while keeping track of the smallest result
		// TODO: CAN BE OPTIMIZED BY NOT CALLING findIslandSize() ON ENDGAME LEVELS
		for (auto levelName = adjacencyList.begin(); levelName != adjacencyList.end(); ++levelName) {
			islandSize = findIslandSize(levelName->first, adjacencyList);
			
			// Don't count endgame levels for island size calculation
			if (std::count(endgameLevels.begin(), endgameLevels.end(), levelName->first) > 0) islandSize = 99;
			
			if (islandSize < smallestIslandSize) {
				smallestIslandSize = islandSize;
				islandLevel = levelName->first;
			}
		}
		
		
		// 3. If the smallest result is smaller than expected (indicating an island), call removeIslands() on that level
		// The ternary operator here is to account for the elevator potentially being added to the layout in an edge case where a single level is unreachable
		if (smallestIslandSize < (elevatorInLayout ? LEVEL_COUNT+1 : LEVEL_COUNT)) {
			f = removeIslands(f, adjacencyList, islandLevel);
			if (f[0].parentLevel == "Candidate_Not_Found") return f;
			elevatorInLayout = true;
		} 
		// 4. If we didn't have to remove any islands, set islands to false and exit loop
		else {
			islands = false;
		}
		
		
		// 5. Just in case this code softlocks, it'll force exit after 10 loops and return -1
		timeout++; 
	}
	
	// More godawful alternatives because I'm too lazy to write in an exception atm
	if (timeout >= 10) f[0].parentLevel == "Candidate_Not_Found";
	return f;
}

int findIslandSize(std::string startingLevel, std::map<std::string, std::vector<std::string>> adjacencyList){
	int islandSize = 0;
	std::map<std::string, bool> visited;
	
	// 1. Create a visited map for the BFS
	for (auto levelName = adjacencyList.begin(); levelName != adjacencyList.end(); ++levelName) {
		visited[levelName->first] = false;
	}
	visited["Elevator"] = false;
	
	// 2. Initialise a queue for vertices to visit, as well as a string to mark the current vertex
	std::queue<std::string> q;
	std::string curr;
	
	// 3. Add starting location to queue and mark as visited
	visited[startingLevel] = true;
	q.push(startingLevel);
	
	// 4. Perform a BFS
	while (!q.empty()) {
		curr = q.front();
		q.pop();
		
		for (std::string x : adjacencyList[curr]) {
			if (!visited[x]) {
				visited[x] = true;
				q.push(x);
			}
		}

	}
	
	// 5. Count number of visited vertices in visited map and return
	for (auto levelName = visited.begin(); levelName != visited.end(); ++levelName) {
		if (visited[levelName->first]) islandSize++;
	}
	return islandSize;
}

std::array<FileWarp, WARP_COUNT> removeIslands(std::array<FileWarp, WARP_COUNT> f, std::map<std::string, std::vector<std::string>> adjacencyList, std::string islandLevel) {
	// IMPLEMENT?
	// 2c. BeetleFlightTest warps
	// 2d. Town warps
	
	bool candidateFound = false;
	std::vector<FileWarp> islandWarps;
	std::map<std::string, bool> visited;
	FileWarp candidate;
	int i = 0, j = 0;
	
	// 1. Get a vector of every warp in the island via BFS 
	// This just copies the BFS implementation from findIslandSize(), see that for comments
	for (auto levelName = adjacencyList.begin(); levelName != adjacencyList.end(); ++levelName) {
		visited[levelName->first] = false;
	}
	visited["Elevator"] = false;
	std::queue<std::string> q;
	std::string curr;
	visited[islandLevel] = true;
	q.push(islandLevel);
	while (!q.empty() && !candidateFound) {
		curr = q.front();
		q.pop();
		
		for (std::string x : adjacencyList[curr]) {
			// Special immediate check if a level is pointing to itself
			if (curr == x) {
				candidateFound = true;
				candidate = {curr, 0, {x, 0}};
			}
			
			// Push back a FileWarp indicating there's a connection from curr to x (offset and entranceID do not matter for this)
			islandWarps.push_back({curr, 0, {x, 0}});
			// Mark as visited as usual
			if (!visited[x]) {
				visited[x] = true;
				q.push(x);
			}
		}
	}
	
	// 2. Check the vector against every rule, these being:
	// 2a. Duplicate warps
	for (i = 0; i < islandWarps.size() && !candidateFound; i++) {
		for (j = i+1; j < islandWarps.size() && !candidateFound; j++) {
			if (islandWarps[i].parentLevel == islandWarps[j].parentLevel && islandWarps[i].destination.level == islandWarps[j].destination.level) {
				candidateFound = true;
				candidate = islandWarps[i];
			}
		}
	}
	
	// 2b. Tower Floor warps
	for (i = 0; i < islandWarps.size() && !candidateFound; i++) {
		if (islandWarps[i].destination.level.substr(0, 5) == "Floor") {
			candidateFound = true;
			candidate = islandWarps[i];
		}
	}
	
	// TODO: Hacky workaround to throwing an exception that should really be changed
	if (!candidateFound) {
		f[0].parentLevel = "Candidate_Not_Found";
	} 
	else {
		// Find candidate's corresponding FileWarp in f and overwrite with an elevator warp
		for (i = 0; i < WARP_COUNT; i++) {
			if (f[i].parentLevel == candidate.parentLevel && f[i].destination.level == candidate.destination.level) {
				f[i].destination.level = "Elevator";
				f[i].destination.entranceID = 0;
				i = WARP_COUNT+10;
			}
		}
	}
	
	return f;
}
