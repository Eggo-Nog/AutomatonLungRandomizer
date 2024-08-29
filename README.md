# AutomatonLungRandomizer

This is a randomizer for the game 'Automaton Lung', which randomizes the layout of the game's world by swapping where in-game warps take the player. It also modifies which weapons are obtained from weapon pickups.

## Where can I download this?
Go to this repository's [releases](https://github.com/Eggo-Nog/AutomatonLungRandomizer/releases) and download the latest version. 

Currently releases only exist for Windows 64-bit, but the source code should work for Linux as well if you're fine with compiling yourself and running the randomizer through the terminal.

## What am I downloading?
The zip you download should contain a readme, an executable (.exe) file, 3 .dll files, and a windows batch (.bat) file. The readme gives you instructions on how to install the randomizer, but simply:
* The .exe file is the randomizer itself
* The .dll files are files the randomizer needs to work, and they should always be in the same directory as it
* The .bat file is intended as an interface for you to use the randomizer. When you run it, it'll give you instructions on what to enter and do the rest for you.

## Using the randomizer without the .bat file (read this if you're compiling it yourself)
The randomizer takes 2 arguments from the command line, which both need to be numbers.
* The first number determines the "mode" of the randomizer, if this is set to 1, it'll randomize the game, for any other value it defaults to "repairing" your game install by rewriting all game files to their vanilla states.
* The second number is the seed used for the randomizer's rng.

So for example, "AutomatonLungRandomizer.exe 1 12" would randomize the game layout using 12 as a seed.

## What should I do if it doesn't work?
If you've worked through the steps in the readme, as well as the potential fixes the program suggests, then please reach out to me and I'll try to figure out what's wrong.
