/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:21:34 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/03 18:19:05 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <time.h>
#include <stdbool.h>
#include "connect.h"
#include "checks.h"
#include "utils.h"

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
					if (asked_to_quit(move) || time_is_up(board, move))
						return (1);
					if (not_a_valid_input(board, move))
						continue;
					int pos = ft_atoi(move);
					make_move(&board.stacks[pos - 1], board.players[board.current_player].piece[0]);
					board.players[board.current_player].number_of_moves++;
					if (player_wins(board, move))
						return (0);
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