# AutomatonLungRandomizer

This repository will host a randomizer for the PC game 'Automaton Lung'. Version 1 will be able to randomize the layout of the game's world by swapping where in-game warps take the player. This will be done by modifying the game's level files directly. 
___
I will release version 1 on GitHub once I've implemented everything from the below list:
* Change a warp to go to a chosen destination
* Load every warp from the game into a format I can work with programatically
* Select a warp at random
* Swap out every warp in a given level for random warps 
* Do the same, but for every level in the game <--- I AM HERE
* Add logic to check if generated layouts are impossible to complete (such as locking the player into dead ends, making the final boss impossible to reach, etc.)
* Add appropriate code to try and fix these layouts when they crop up, or prevent them from appearing in the first place
* Add options for the player to toggle, like setting the seed or controlling how the randomization works (using command line arguments)
* Add a "repair" feature which will revert all level files back to their original state
* Write a small terminal script to go with it which can manage the command line arguments in a user friendlier way
