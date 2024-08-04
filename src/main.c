/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:21:34 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/04 12:31:06 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <time.h>
#include <stdbool.h>
#include "connect.h"
#include "checks.h"
#include "utils.h"
#include "players.h"


/**
 * @brief main function
 * 
 * The grid size must be taken as parameters to the program.
 * Cannot be smaller than 6x7. There is a time limit for the game. 
 */
int main(int argc, char **argv)
{
	t_board board;
	if (!init_board(&board, argc, argv))
		return (1);
	
	// init stacks
	t_stack stacks[board.cols];
	init_stacks(stacks, board.cols);
	board.stacks = stacks;

	// initialize players - name , piece, start_time, start_move_time, allowed_time, allowed_move_time, curr number_of_moves
	t_player ai = {"AI", 'X', time(NULL), time(NULL), MAX_TIME, 4, 0};
	t_player player = {"Mario", 'O', time(NULL), time(NULL), MAX_TIME, 4, 0};
	board.players[0] = player;
	board.players[1] = ai;

	print_header();
	printplayers(ai, player);

	choose_player(&board);
	

	ft_printf(GREEN "Player %s starts\n", board.players[board.current_player].name);
	
	while (1) {	
		if (board.current_player == 0){
			if (player_plays_and_win(&board))
				return (0);
		}
		else
		{
			if (ai_plays_and_win(&board))
				return (0);
		}
	}
    // int elapsedMinutes = moveelapsedSeconds / 60;

	// ask for player move an check time

	// check for winner

	// switch player
	
}