# Arduino Game ENhancement Device for Airsoft (AGEnDA)

An Arduino-powered contraption that brings game modes from popular video games into real life Nerf/Airsoft/Paintball games. I play airsoft with my friends often, and thought it would be cool to have the _King of the Hill_ Game Mode from Valve's _Team Fortress 2_. As such, this project was born. I later added a _Defuse the Bomb_ game mode inspired by Valve's _Counter Strike: Global Offensive_.

## Code Structure

Despite running on an Arduino, this software is slightly more complex than your typical Arduino sketch as it follows pretty intense Object Oriented Design. Here is a brief description of the code files:

Class/Header file |Description
------------------|-----------
AGEnDA.ino        | The main Arduino sketch file. Initializes all IO and holds the main setup/loop functions
TimeManager.h     | Holds a static method that returns the global time rounded to 50 ms for global timing purposes
HardwareMap.h     | Holds the value of every single IO port for global reference
MenuManager class | Responsible for rendering the main game selection menu as well as submenus for game-specific settings
Game.h            | An abstract class that all _Game Modes_ must extend
KOTHGame class    | Defines behaviour of the KOTH game mode; extends Game
CSGOGame class    | Defines behaviour of the CSGO game mode; extends Game


## Contributing/Adding additional Game Modes

Any suggestions for game modes are welcome. I have tried to make adding a game mode fairly modular, here is how to add a new one:
1) Create a _MyGameMode_ class that extends the Game class. Look at the existing game modes for an idea of how to do that
2) Update the __NUMGAMES__ constant in Game.h
3) Initialise your game mode in AGEnDA.ino by passing into its constructor the address of hardwareMap and a unique numeric ID that will reflect its index in the gameList array
4) Manually add the address of your game mode object to the gameList array in the `setup()` function
5) Implement the inherited methods of Game inside your game mode .cpp file, and implement your own functionality via private methods
6) Add your own settings and initialize them in the constructor of your gamemode. Make sure your "option parameters" array ends with a 0. Make sure to define your own GameOption array in the header file and return it in the source file

## Current TODO/Wish List
- [x] Add settings for each Game Mode that are accessible at boot time
- [ ] Remember settings accross boot (still wondering about this one)
- [ ] Add javadocs-style documentation to everything
- [X] Add descriptions of game modes in game mode files
- [ ] Add pausing
- [ ] Make MenuManager scroll automatically for text that is too long
- [ ] Add flexibility for displays of different sizes
- [ ] Make HardwareMap a static class
- [ ] Upload schematic files
- [ ] Add speaker and sounds
- [ ] Make a youtube video to demonstrate this project
- [ ] Come up with a cooler name for this than AGEnDA

## License and stuff
I'm still deciding how I want to license this project. For now let's just say you can look at the source code, become inspired by it, offer me suggestions, submit pull requests, and use the software for personal purposes. But please don't try to sell my work as your own or steal credit. I shall update this as soon as I have something in mind that sounds reasonable
