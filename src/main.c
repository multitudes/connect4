/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:21:34 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/03 17:59:37 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <time.h>
#include <stdbool.h>
#include "connect.h"
#include "checks.h"

/**
 * @brief the board is an array of stacks
 * 
 * @param stacks the columns of the board
 * @param rows the number of rows in the board
 * @param cols the number of columns in the board
 * @param players the players in the game
 * @param current_player the player that is playing
 * @param has_GUI if the game has a GUI
 * 
*/
typedef struct	s_board
{
	t_stack		*stacks;
	int			rows;
	int			cols;
	t_player	players[2];
	int			current_player;	
	bool		has_GUI;
} 				t_board;


void init_stacks(t_stack *stacks, int cols)
{
	for (int i = 0; i < cols; i++)
	{
		ft_memset(stacks[i].data, '-', MAX_ROWS);
		stacks[i].data[MAX_ROWS] = '\0';
		stacks[i].top = -1;
	}
}


void printstacks(t_stack *stacks, int rows, int cols)
{	
	for (int i = rows - 1; i >= 0; i--)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%c", stacks[j].data[i]);
		}
		printf("\n");
	}
}

void printplayers(t_player ai, t_player player)
{
	printf("Player 1: %s --- ", player.name);
	printf("Player 2: %s\n", ai.name);
}

bool init_board(t_board *board, int argc, char **argv)
{
	board->rows = 0;
	board->cols = 0;
	board->current_player = 0;

	board->has_GUI = false;
	if (argc == 4 && (ft_strcmp(argv[3], "--gui") == 0 || ft_strcmp(argv[3], "-g") == 0))
		board->has_GUI = true;
	else
	if (argc != 3 )
	{
		ft_printf("Usage: ./connect4 <rows> <cols> (<--gui | -g>)\n");
		return (false);
	}

	board->rows = ft_atoi(argv[1]);
	if (board->rows < 6 || board->rows > 9)
	{
		ft_printf("The number of rows must be between 6 and 9\n");
		return (false);
	}
	board->cols = ft_atoi(argv[2]);
	if (board->cols < 7 || board->cols > 9)
	{
		ft_printf("The number of columns must be between 7 and 9\n");
		return (false);
	}
	return (true);
}

void make_move(t_stack *stack, char piece)
{

	stack->top++;
	stack->data[stack->top] = piece;
}


int main(int argc, char **argv)
{
	//The grid size must be taken as parameters to the program.
	// Ex: ./connect4 8 10
	t_board board;
	if (!init_board(&board, argc, argv))
		return (1);
	
	// init stacks
	t_stack stacks[board.cols];
	init_stacks(stacks, board.cols);
	board.stacks = stacks;

	// initialize players - name , piece, start_time, start_move_time, allowed_time, allowed_move_time, curr number_of_moves
	t_player ai = {"AI", "X", time(NULL), time(NULL), MAX_TIME, 4, 0};
	t_player player = {"Mario", "O", time(NULL), time(NULL), MAX_TIME, 4, 0};
	board.players[0] = player;
	board.players[1] = ai;

	printf("Hello World!\n");
	printplayers(ai, player);


	// seed random number generator
	srand(time(NULL));

	// chose the first player
	if (rand() % 2 == 0) {
		board.current_player = 0;
	}
    else 	
		board.current_player = 1;
	

	printf("Player %s starts\n", board.players[board.current_player].name);
	
	while (1) {	
		if (board.current_player == 0)
		{
			time_t currentTime = time(NULL);

			board.players[board.current_player].start_move_time = currentTime;
			
			printstacks(board.stacks, board.rows ,board.cols);
			ft_printf("Remaining time %d min and %d sec\n", (MAX_TIME - (currentTime - board.players[board.current_player].start_time)) / 60, (MAX_TIME - (currentTime - board.players[board.current_player].start_time)) % 60);	
			ft_printf("\nYour move?\n");
			char *move;
			while ((move = get_next_line(0)) != NULL)
			{
				if (move)
				{
					printf("You entered: %s\n", move);
					if (ft_strcmp(move, "q\n") == 0)
					{
						printf("quitting\n");
						free(move);
						return (1);
					}
					currentTime = time(NULL);
					if ((currentTime - board.players[board.current_player].start_move_time > board.players[board.current_player].allowed_move_time) || \
						(currentTime - board.players[board.current_player].start_time > board.players[board.current_player].allowed_time))
					{
						ft_printf("But your time is up...\n");
						ft_printf("You lose!\n");
						free(move);
						return (1);
					}
					// check move is a number and between 1 and board.cols
					int pos = ft_atoi(move);
					if (pos < 1 || pos > board.cols)
					{
						ft_printf("Invalid move. Please enter a number between 1 and %d\n", board.cols);
						free(move);
						continue;
					}
					// check if the stack is full
					if (board.stacks[pos - 1].top == board.rows - 1)
					{
						ft_printf("The stack is full. Please enter another move\n");
						free(move);
						continue;
					}
					make_move(&board.stacks[pos - 1], board.players[board.current_player].piece[0]);
					board.players[board.current_player].number_of_moves++;
					// printf("data in stack %s\n", board.stacks[pos - 1].data);
					if (board.players[board.current_player].number_of_moves++ > 3)
					{
						// check for winner
						if (check_win(board.stacks, board.rows, board.cols, board.players[board.current_player].piece[0]))
						{
							ft_printf("Player %s wins!\n", board.players[board.current_player].name);
							printstacks(board.stacks, board.rows ,board.cols);
							ft_printf("\nGame over\n");
							free(move);
							return (0);
						}
					}
					free(move);
					break;
				}
				free(move);
			}
			printstacks(board.stacks, board.rows ,board.cols);
			board.current_player = board.current_player == 0 ? 1 : 0;
		}
		else
		{
			time_t currentTime = time(NULL);
			board.players[board.current_player].start_move_time = currentTime;
			int pos = rand() % board.cols + 1;
			make_move(&board.stacks[pos - 1], board.players[board.current_player].piece[0]);
			board.players[board.current_player].number_of_moves++;
			if (board.players[board.current_player].number_of_moves++ > 3)
			{
				if (check_win(board.stacks, board.rows, board.cols, board.players[board.current_player].piece[0]))
				{
					ft_printf("\nPlayer %s wins!\n\n", board.players[board.current_player].name);
					printstacks(board.stacks, board.rows ,board.cols);
					ft_printf("\nGame over\n\n");
					return (0);
				}
			}
			ft_printf("\nAI move\n");
			board.current_player = board.current_player == 0 ? 1 : 0;
		}
	}
    // int elapsedMinutes = moveelapsedSeconds / 60;

	// ask for player move an check time

	// check for winner

	// switch player
	
}