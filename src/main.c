/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:21:34 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/03 13:33:06 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <time.h>

/**
 * @brief a player has 40 sec for move and ttl 4 min
 * 
 * 
*/
typedef struct 	s_player
{
	char *name;
	char *piece;
	time_t start_time;
	time_t move_time;
}				t_player;

/**
 * @brief a stack is a column in the board
 * 
 * It is initialized at -1 and it increases as the player puts pieces in it
 * @param data the piece that is in the stack as a char X or O
*/
typedef struct	s_stack
{
	char data;
	int top;
} 				t_stack;

/**
 * @brief the board is an array of stacks
 * 
 * @param stacks the columns of the board
 * @param rows the number of rows in the board
 * @param cols the number of columns in the board
 * @param players the players in the game
 * @param current_player the player that is playing
 * 
*/
typedef struct	s_board
{
	t_stack		*stacks;
	int			rows;
	int			cols;
	t_player	players[2];
	int			current_player;	
} 				t_board;

void init_stacks(t_stack *stacks, int cols)
{
	for (int i = 0; i < cols; i++)
	{
		stacks[i].data = '-';
		stacks[i].top = -1;
	}
}


void printstacks(t_stack *stacks, int rows, int cols)
{	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%c", stacks[j].data);
		}
		printf("\n");
	}
	
}

void printplayers(t_player ai, t_player player)
{
	printf("Player 1: %s --- ", player.name);
	printf("Player 2: %s\n", ai.name);
}

int main(int argc, char **argv)
{
	//The grid size must be taken as parameters to the program.
	// Ex: ./connect4 8 10
	if (argc != 3)
	{
		printf("Usage: ./connect4 <rows> <cols>\n");
		return (1);
	}
	t_board board;
	board.rows = ft_atoi(argv[1]);
	if (board.rows < 6 || board.rows > 9)
	{
		printf("The number of rows must be between 6 and 9\n");
		return (1);
	}
	board.cols = ft_atoi(argv[2]);
	if (board.cols < 7 || board.cols > 9)
	{
		printf("The number of columns must be between 7 and 9\n");
		return (1);
	}
	t_stack stacks[board.cols];
	init_stacks(stacks, board.cols);
	board.stacks = stacks;

	// initialize players
	t_player ai = {"AI", "X", time(NULL), time(NULL)};
	t_player player = {"Mario", "O", time(NULL), time(NULL)};
	board.players[0] = ai;
	board.players[1] = player;
	printf("Hello World!\n");
	printplayers(ai, player);
	printstacks(board.stacks, board.rows ,board.cols);
}