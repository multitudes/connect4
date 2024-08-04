# Connect4

Here at 42 we do a weekend rush project. This weekend it is about Connect4.

> The goal of this rush is to write a Connect Four. That’s not all, you will need to write
an AI to play against you. Wonderful, isn’t it?


## General rules
• The assignment has to be written in C.
• No norm.
• cc is used as compiler.
• You have to compile with the following flags -Wall -Wextra -Werror.
• You have to turn in a Makefile which will compile your source files.
• Your program should not quite unexpectedly (segmentation fault, bus error, double
free, and so forth) except for undefined behaviors.
• Within the mandatory part, you’re allowed to use the following:
◦ Our Libft library. And the following C functions:  malloc(3), free(3), rand(3), srand(3), time(3)

## Mandatory part
It is played in the terminal.

## Bonus part
We can choose any lib you want (like sdl or ncurses).

## How to play
The program will be launched taking as arguments the width and height of the board. The minimum size is 6x7.

I hardcoded a maximum size of 20x20. But this can be extended by changing the defines MAX_ROWS and MAX_COLS in the header file.

The first to play is to be decided at random. The first to connect 4 pieces diabgonally, horizontaally or vertically wins.

I first implemented a working game with the AI playing random moves.  
My data structure is an array of stacks. Each stack represents a column.
```c
typedef struct	s_stack
{
	char data[MAX_ROWS + 1];
	int top;
} 				t_stack;
```
They keep track of the top of the stack and the data in the stack which is an array of characters.

This is how I implemented the game board:
```c
typedef struct	s_board
{
	t_stack		*stacks;
	int			rows;
	int			cols;
	t_player	players[2];
	int			current_player;	
	bool		has_GUI;
} 				t_board;
```
The board has an array of stacks, the number of rows and columns, the players, the current player and a boolean to check if the game has a GUI.
The Players are defined as follows:
```c
typedef struct 	s_player
{
	char 	*name;
	char 	piece;
	time_t 	start_time;
	time_t 	start_move_time;
	int 	allowed_time;
	int 	allowed_move_time;
	int 	number_of_moves;
}				t_player;
```

## MINIMAX

The most interesting part of this project was implementing the minimax algorithm. Since it is a small board and the player have a limited number of moves, I could implement a simple minimax algorithm with alpha-beta pruning.

The minimax is an algorithm that starts with the current board state and recursively explores all possible moves until a certain depth. It then evaluates the board state and returns a score. The score is then used to decide which move is the best.

The alpha-beta pruning is a way to optimize the minimax algorithm. It is a way to reduce the number of nodes that need to be evaluated in the search tree.  

It keeps track of two values, alpha and beta, which represent the minimum score that the maximizing player is assured of and the maximum score that the minimizing player is assured of respectively.

Imagine at the beginning I play 1. The AI now will play a move on 1 and then evaluate. Then will play 2 and then evaluate...
In the end the move that has the highest score is the best move.
So if my board has 10 cols I will have a recursion over 10 possible move. Each of the move will go to explore a game until 4 recursion depth. So in the end I will have 10^4 = 10000 possible game states to evaluate. This is why the alpha-beta pruning is so important. Because for each branch from my parent node I will keep track of the best and worse score. If I find a move that is worse than the best move I already have I can stop exploring that branch.

## Evaluation function
I need:
- Game state: Represented by my t_board struct.
- Move generation: A function to generate all possible legal moves for a given board state.
- Evaluation function: A function to evaluate the quality of a board position.
- Minimax algorithm: The core recursive function to explore the game tree.

### The move generation
This is easy... I go through all columns in a for loops and check if the column is not full. If it is not full I can play a move there.

### The evaluation function 
It is the most important part. I need to evaluate the board state and return a score. The score will be used by the minimax algorithm to decide which move is the best.  
I first check for possible wins. I had to hardcode this but it is easy. If I have a blank space and I have 3 pieces in a row I can win. Or same if 2 pieces, a space and another same piece.
Also I give a higher score for a player if I find 1, 2 , 3 pieces in a row or in a column or diagonal, but for the diagonal I should ideally check if the connection is possible... I didn't do that yet. It could be a nice improvement.

### The minimax algorithm
It is a recursive function alternating moves of the players alternating between them. I will keep checking for a win or a lose and return a bias score. If I reach the maximum depth I will return the evaluation function's score.
EX:
if at a certain point in my simulation i get to the AI winning at a depth of 4 I will return a score of 1000. If I get to the player winning I will return -1000. But If I have my AI winning at depth 1 then this move is actually better so it will be 4000!

After going through all the possible moves I will return the best score and the player will move again.

## Optimizations
I could adjust the depth parameter to make it stronger or weaker for different levels of play. 
