MOUSE AND CAT GAME 

Herut Partner 205741333
Nicole Kazantsev 208258085

The exercise implements the MOUSE&CAT game.
For the implementation of the game there is the use of inheritance, polymorphism, and the graphic library SFML.
The goal of the game: the player must collect all the cheeses in the stages. 
In the stages of the game there is a time limit - if you do not finish the stage in time the game ends.
The mouse can move down, up, left and right.
The cats in the game are chasing the mouse and the mouse has to avoid them. 
In every collision between a mouse and a cat, the mouse lost a life.
In order to open the doors you need to collect keys.
The mouse can take gifts where each gift gives it a different reward:
- More lives.
- 10 seconds extra time.
- Deleting a random cat from the game board.
- Freezing the cats on the game board for a certain period of time.

Details of the classes in the exercise:
- GameObject class: represents all the objects of the game.
  The StaticObjects and MovingObjects classes inherit from this class.
- StaticObjects class: represents all static objects, those that do not move on the game board.
  The wall, door, key, present, cheese classes inherit from this class.
- MovingObjects class: represents the objects that can be moved or move regularly on the game board.
  From this class inherit the classes Mouse, Cat.
- Class Present – ​​represents the gifts in the game.
  The Addtime, Addlife, Freeze classes inherit from this classes.
- Mouse class: represents the mouse in the game.
- Cat class: represents the cats in the game.

Additional classes:
- GameController: This class is responsible for managing the game.
- Board: this class is responsible for the game board and what is contained in it, reading the stage, saving into vectors, identifying objects, etc.
- Menu: the opening screen menu.
- Toolbar: responsible for the right side of the panel - notification of the stage number, timer, amount of life and time remaining for the stage.
- Resources: this department is responsible for all dealing with the files required in the program, loading them into textures, etc.


The input file:
Since in the project we keep all the levels in one continuous file, in order to add a level you can add it at the end of the steps file board.txt which is in the resources folder.
The text file should be structured like this:
In the first row the number of rows in a space table and then the number of columns in the table. 
Then go down a step and register the requested board.
All stages in the game have a time limit of 40 seconds.
In the following lines, the level will appear built by characters so that each character represents an object on the board as follows:
%- mouse, ^- cat, T- gift of time, Z- gift of stagnation, L - gift of life, $ - gift of erasing cat, # - wall, *- cheese, D- door, F- key.
**important!! The stages must be framed by a wall so that the players of the game do not leave the board!

Key data structures:
Vectors - separate vectors to keep the moving objects on the board. 
Enums - for the textures of the objects, music, sounds.  

Algorithms worth noting:
Calculation of the board size according to the number of rows and columns 
Cat movement algorithm: When the cat is in a normal state, the cats attempt to
approach it in a random manner for almost the entire duration of the game
(but not entirely), with the thought that after several games, the player will
already learn the algorithm (no matter how complex it may be) and will know how
to easily defeat the cats. 
Additionally, to demonstrate control over the game
and coding complexity, we added the option that when the cat is one step away 
from the mouse, it will definitely choose to eat it, meaning they locate where
it is and approach it accordingly. For example, if it's above them, they will 
go up. Another feature we implemented is to give the mouse a thought about 
where to go (despite the randomness), to enter places at its own stage where it
will be very difficult for the cat to reach, so choosing a good strategy for
the mouse will lead to winning the game.
