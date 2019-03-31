## Conway's Game Of Life.
---
The Game of Life is a cellular automaton design by the British mathematician John Horton Conway in 1970. The 
target of this challenge is to implement the Game of Life in python. The application is executed from a terminal
and it should refresh the grid in each iteration with information about the game and the evolution of the 
patterns. When the application starts the user chooses a pattern to start the game. A configuration file
(json format) stores all configurable options of game.
---

### Configuration file
 
Currently, the configuration file stores:
* The Number of grid cells (horizontally and vertically)
* The fps rate that refreshes the grid
---

### get started 

1. clone the repository & cd in the labyrinth folder

`git clone https://github.com/Mahmoud-Selim/Challenges.git && Game-Of-Life`

3. run the project and give the configuration file as an argument to the program. if you don't you will be asked 
to provide the file name in the program.

`python game_of_life.py [file_namme.json]`

