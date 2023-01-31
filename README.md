# 2048-in-C
Programming Practice Final Project
<br>
<br>
In the Fall Semester of 2022, I took a *Programming Practice* course in Seoul National University, where I learned C programming for the first time. For our final project, we were assigned to code the popular game, 2048. Below is the final report which details:
<ol>
  <li>how to play the game</li>
  <li>building and running the project</li>
  <li>troubleshooting points</li>
  <li>how to implement features</li>
</ol>
<h3>Playing the Game</h3>
Firstly, you will be met by a menu screen. Type in the character as it states. In Classic Mode, players will use ‘w’ ‘a’ ‘s’ ‘d’ to move the tiles. Two tiles will appear when the game starts, and continue to appear in a blank space after every move. When a tile slides to a tile with the same number, they will add up. The score will increase every time they add up together. The game will reach the end when a tile reaches 2048 or when no more moves are available. In Time Attack Mode, the same gameplay rules are applied. However, the player will have a 120 second time limit which will show up above the board.

<h3>Building and Running the Project</h3>
In order to build this project, one must start with a four by four integer array. This array will
represent the board in 2048. When the value of an element is 0, it means that it is a blank
box. Thus, it is necessary to make all the elements in the array to be equal to 0 at the start of
the game. This is done by the ‘reset_board’ function, made with a for loop, and is used in the
beginning of all games. Then, build a function that prints the board. To make the board
appear cleaner, make sure to add additional spaces for 1 digit numbers to line up clearly.
Also, replace the 0s with a space, as they are just blank spaces.
<br><br>When the set up for the board is complete, create a function that would randomly generate
2s in a blank board. This function uses the rand function to generate a random coordinate.
However, it is important to make sure that the randomly generated coordinate, in the array,
has a value of 0. Initially, I did not do this, so the function would replace real values like 4
and 8 to a 2, which is not what we intended. This is done so by the if statement.
<br><br>With the setup and generate2 function complete, move on to coding the basic gameplay.
This game uses ‘a’ for left, ‘s’ for down, ‘d’ for right, and ‘w’ for up. For example, when
moving down, the function must complete two tasks: moving the blocks down and adding
them together. For moving the blocks down, use an if statement to find the lowest blank
block. Then, replace a numbered block with that lowest blank block. To add the same blocks,
use an if statement to check whether the two blocks below each other are the same. Then,
multiply the block below by two and change the upper block into a blank block. Lastly, make
sure to add the multiplied block value into the score.
<br><br>To end the game, use two functions: ‘game_end’ and ‘game_over’. If one of them is equal to
0, the game will end. ‘game_end’ checks whether a block is equal to 2048, which means the
player won. ‘game_over’ checks if there are no available moves. It checks if there are no
blocks equal to zero, blocks next to each other are not the same, or blocks below each other
are not the same.
<br><br>To run the project, use the git bash terminal to compile the code. If there are no errors, you
can execute it using “./”.
<h3>Troubleshooting Points</h3>
Previously, I saved the score files without the structure. This made it simple to print all the
information. However, this made it difficult to sort the scores from highest to lowest.
Therefore, I had to create an array of structures. However, I kept getting an error and the
information didn’t get saved properly. I then realized that I had to write a for loop to make
sure the information was written in a blank array, checking if a score was null, and then ask
the user for their game id information. Now that I created an array of structures, it was easier
to sort the score from highest to lowest because I could just write a sorting algorithm with
two for loops comparing the size of the user’s score
<h3>How to Implement Features</h3>
To implement the feature of playing the game, incorporate all the functions mentioned above
in Building and Running the Project. In classic mode, use the score_time integer to measure
how long the game lasts. This is done with time. Measure the start time before the game
starts and the current time as the game progresses. score_time will be the time difference
between these two. score_time will be constantly updated until the game ends. Use a while
loop for the game to progress.
<br><br>
As mentioned above, the game ends when the game is over or the game has ended. Thus,
use the condition that game_over = 1 &&(AND) game_end = 1. Use a clear screen function
every time the player has made a move to make the game more aesthetically pleasing to
play. Remember to generate a 2 every time the player makes a move. In time attack mode,
the score_time will be set to 120 seconds. And instead of increasing, it will decrease until it
reaches zero. Therefore, there’s another condition for the game to end: whether score_time
is less than or equal to zero.
<br><br>
To save the scores and information of the game play, use a structure called score_board.
This saves the player’s user id, score, time, game type, and whether they were successful or
not (reach 2048). When the game ends, use the scoreboard function to save this
information. It will ask the player to enter their game id and store the other information in a
separate text file. Also, for players to view the ranking, use a high_score function. It will open
and sort the structure saved in a file by the user’s score and print them.
