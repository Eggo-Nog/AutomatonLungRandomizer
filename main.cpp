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

int main(int argc, char *argv[]) {
	
	// List of stock warps in the game (excluding inaccessible warps) - either to be copied from when generating a layout or used for repairing
	std::array<FileWarp, WARP_COUNT> stockWarps{{
		{"BeetleFlightTest", 134344, {"TownA", -1}},
		{"BeetleFlightTest", 134392, {"TownD", -1}},
		{"BeetleFlightTest", 134440, {"TownB", -1}},
		{"BeetleFlightTest", 134488, {"CollectibleTrackerEntrance", -1}},
		{"BeetleFlightTest", 134560, {"TownE", -1}},
		{"BeetleFlightTest", 134608, {"Floor 0", -1}},
		{"BeetleFlightTest", 134656, {"RapidFireWeaponArea", -1}},
		{"BeetleFlightTest", 134720, {"HorseshoeCrabBeach", -1}},
		{"BeetleFlightTest", 134784, {"EndlessGrassyPlane", -1}},
		{"BeetleFlightTest", 134848, {"TownC", -1}},
		{"AutomatonBoss", 85204, {"AutomatonDefeatCutscene", 0}},
		{"AutomatonDefeatCutscene", 48144, {"CollapsingEscapeRoom", 0}},
		{"TownA", 114032, {"TownABuildingInterior 1", 0}},
		{"TownA", 114096, {"TownABuildingInterior", 0}},
		{"TownA", 114160, {"TownABuildingInterior", 2}},
		{"TownA", 114224, {"TownABuildingInterior", 1}},
		{"TownA", 114288, {"TownABuildingInterior 1", 1}},
		{"TownA", 117072, {"BeetleFlightTest", 5}},
		{"TownA", 117808, {"BeetleFlightTest", 5}},
		{"TownB", 111080, {"TownBWeaponRoom", 0}},
		{"TownB", 111136, {"TownBPyramidInterior", 1}},
		{"TownB", 111200, {"TownBPyramidInterior", 0}},
		{"TownB", 113480, {"BeetleFlightTest", 0}},
		{"TownB", 114096, {"BeetleFlightTest", 0}},
		{"TownC", 135216, {"TownC 1", 0}},
		{"TownC", 137328, {"BeetleFlightTest", 3}},
		{"TownC", 137872, {"BeetleFlightTest", 3}},
		{"TownD", 230392, {"TownDInterior1", 1}},
		{"TownD", 230448, {"TownD 1", 0}},
		{"TownD", 230496, {"Floor 0", 1}},
		{"TownD", 233048, {"Harold", 0}},
		{"TownD", 234352, {"BeetleFlightTest", 6}},
		{"TownD", 235040, {"BeetleFlightTest", 6}},
		{"TownDInterior1", 52152, {"Floor 21", 1}},
		{"TownDInterior1", 52200, {"TownD", 0}},
		{"TownBPyramidInterior", 67152, {"TownB", 2}},
		{"TownBPyramidInterior", 67200, {"TownB", 1}},
		{"TownBWeaponRoom", 61184, {"TownB", 3}},
		{"CollectibleTrackerEntrance", 51976, {"CollectibleTrackerInterior", 0}},
		{"CollectibleTrackerEntrance", 53240, {"BeetleFlightTest", 1}},
		{"CollectibleTrackerEntrance", 53592, {"BeetleFlightTest", 1}},
		{"CollectibleTrackerInterior", 79960, {"AutomatonBoss", 0}},
		{"CollectibleTrackerInterior", 80016, {"CollectibleTrackerEntrance", 1}},
		{"Floor 0", 132992, {"Elevator", 0}},
		{"Floor 0", 135400, {"BeetleFlightTest", 4}},
		{"Floor 0", 135992, {"BeetleFlightTest", 4}},
		{"Floor 1", 65080, {"Elevator", 0}},
		{"Floor 2", 124960, {"Elevator", 0}},
		{"Floor 3", 143944, {"Elevator", 0}},
		{"Floor 4", 60824, {"Elevator", 0}},
		{"Floor 5", 70736, {"Elevator", 0}},
		{"Floor 6", 67072, {"Elevator", 0}},
		{"Floor 7", 86752, {"Elevator", 0}},
		{"Floor 8", 69168, {"Elevator", 0}},
		{"Floor 9", 61664, {"Elevator", 0}},
		{"Floor 10", 110304, {"Elevator", 0}},
		{"Floor 11", 59008, {"Elevator", 0}},
		{"Floor 12", 90016, {"Elevator", 0}},
		{"Floor 13", 61240, {"Elevator", 0}},
		{"Floor 14", 66224, {"Elevator", 0}},
		{"Floor 15", 69224, {"Elevator", 0}},
		{"Floor 16", 90272, {"Elevator", 0}},
		{"Floor 17", 96832, {"Elevator", 0}},
		{"Floor 18", 65288, {"Elevator", 0}},
		{"Floor 19", 61152, {"Elevator", 0}},
		{"Floor 19", 61200, {"AutomatonBossEscape", 0}},
		{"Floor 20", 103600, {"Elevator", 0}},
		{"Floor 21", 184728, {"TownDInterior1", 0}},
		{"Floor 21", 184784, {"Elevator", 0}},
		{"TownE", 274160, {"TownEInterior 1", 0}},
		{"TownE", 274216, {"TownEInterior 1", 1}},
		{"TownE", 278064, {"BeetleFlightTest", 2}},
		{"TownE", 278656, {"BeetleFlightTest", 2}},
		{"TownEInterior 1", 220024, {"TownE", 2}},
		{"TownEInterior 1", 220072, {"TownE", 1}},
		{"TownABuildingInterior", 73032, {"TownA", 3}},
		{"TownABuildingInterior", 73080, {"TownA", 1}},
		{"TownABuildingInterior", 73128, {"TownA", 2}},
		{"TownABuildingInterior 1", 67696, {"TownA", 5}},
		{"TownABuildingInterior 1", 67744, {"TownA", 4}},
		{"TownC 1", 101072, {"TownC", 1}},
		{"TownC 1", 101120, {"TownC 3", 0}},
		{"TownC 1", 101168, {"TownC 2", 0}},
		{"TownC 2", 131360, {"TownC 1", 1}},
		{"TownC 3", 175672, {"TownC 1", 2}},
		{"TownD 1", 114624, {"TownD", 1}},
		{"AutomatonBossSecondPhase", 54076, {"FinalCutscene 1", 0}},
		{"AutomatonBossMaze", 98400, {"AutomatonBossSecondPhase", 0}},
		{"CollapsingEscapeRoom", 266328, {"AutomatonBossMaze", 0}},
		{"FinalCutscene 1", 38272, {"FinalCutscene", 0}},
		{"HorseshoeCrabBeach", 228752, {"BeetleFlightTest", 7}},
		{"HorseshoeCrabBeach", 229248, {"BeetleFlightTest", 7}},
		{"EndlessGrassyPlane", 483864, {"BeetleFlightTest", 9}},
		{"EndlessGrassyPlane", 484216, {"BeetleFlightTest", 9}},
		{"RapidFireWeaponArea", 108816, {"RapidFireWeaponArea 1", 0}},
		{"RapidFireWeaponArea", 110376, {"BeetleFlightTest", 8}},
		{"RapidFireWeaponArea", 110928, {"BeetleFlightTest", 8}},
		{"RapidFireWeaponArea 1", 113312, {"RapidFireWeaponArea", 1}},
		{"Harold", 91440, {"Harold 1", 0}},
		{"Harold 2", 137344, {"Harold 3", 0}},
		{"Harold 2", 137392, {"Harold 3", 0}},
		{"Harold 2", 137440, {"Harold 3", 0}},
		{"Harold 2", 137488, {"Harold 3", 0}},
		{"Harold 2", 137536, {"Harold 3", 0}},
		{"Harold 2", 137584, {"Harold 3", 0}},
		{"Harold 2", 137632, {"Harold 3", 0}},
		{"Harold 2", 138128, {"Harold 3", 0}},
		{"AtlantisMainRoom", 49888, {"Elevator", 0}}
	}};
	
	
	// Only run if we're given a mode and a seed as cmd args
	if (argc == 3) {
		unsigned int mode = 0;
		unsigned int uSeed = 0;
		
		try {
			mode = std::stoi(argv[1]);
			uSeed = std::stoi(argv[2]);
			
		} catch (std::invalid_argument const& ex) {
			std::cout << "Seed isn't a number, please try again without using any letters or symbols.\n";
			return 0;
			
		} catch (std::out_of_range const& ex) {
			std::cout << "Seed number is too large, try using a smaller number (something between 0-64000 should work for most machines).\n";
			return 0;
		}
		
		// Initialize rLayout
		std::array<FileWarp,WARP_COUNT> rLayout;
		
		// Randomizing game layout
		if (mode == 1) {
			std::cout << "Generating game layout.";
			
			// Seed given by the user is used to give random seeds to generateGameLayout() to ensure it gets seeded differently if it's run more than once
			std::mt19937 seedGen;
			seedGen.seed(uSeed);
			
			std::cout << ".";
			
			// Generate a game layout, and if it can't be fixed, just generate another one :^)
			
			do {
				rLayout = generateGameLayout(stockWarps, 0, seedGen());
			} while (rLayout[0].parentLevel == "Candidate_Not_Found");
			
			std::cout << ".\nWriting new game layout to game files.";
			

		}
		
		// "Repairing" game files (this can also be done through Steam but I figured it's still good to give people the option)
		else if (mode == 0) {
			std::cout << "Repairing game files.";
			rLayout = stockWarps;
		}
		
		// All of these functions return -1 when they encounter a file I/O error, so track if any do and relay this to the user
		int bad = 0;
		bad += randomizeWeapons(mode, uSeed);
		std::cout << ".";
		bad += makeBeetleFast(mode);
		std::cout << ".\n";
		bad += writeAllFileWarps(rLayout);
		
		if (bad < 0) {
			std::cout << "Some kind of error was encountered when trying to modify your game's files.\nYou can try to run the program again as administrator, or contact the randomizer developer for help.\nYou should also double check the README to make sure you're using the program correctly.\nIn the meantime, you can use Steam's \"Verify Integrity of Game File\'s\" option to repair your game install.\n";
		}
		else {
			std::cout << "Done!\n";
		}
	}
	
	
	return 0;
}
