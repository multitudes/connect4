/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:37:10 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/03 18:47:05 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "connect.h"
#include <time.h>
#include "utils.h"
#include "checks.h"

void choose_player(t_board *board)
{
	// seed random number generator
	srand(time(NULL));
	// chose the first player
	if (rand() % 2 == 0) {
		board->current_player = 0;
	}
    else 	
		board->current_player = 1;
}
bool ai_plays_and_win(t_board *board)
{
	time_t currentTime = time(NULL);
	board->players[board->current_player].start_move_time = currentTime;
	int pos = rand() % board->cols + 1;
	make_move(&(board->stacks[pos - 1]), board->players[board->current_player].piece[0]);
	board->players[board->current_player].number_of_moves++;
	if (board->players[board->current_player].number_of_moves > 3)
	{
		if (check_win(board->stacks, board->rows, board->cols, board->players[board->current_player].piece[0]))
		{
			ft_printf("\nPlayer %s wins!\n\n", board->players[board->current_player].name);
			printstacks(board->stacks, board->rows, board->cols);
			ft_printf("\nGame over in %d min and %d sec\n\n",  (MAX_TIME - (currentTime - board->players[board->current_player].start_time)) / 60, (MAX_TIME - (currentTime - board->players[board->current_player].start_time)) % 60);	
			return true;
		}
	}
	ft_printf("\nAI move\n");
	board->current_player = board->current_player == 0 ? 1 : 0;
	return false;
}

bool player_plays_and_win(t_board *board)
{
	time_t currentTime = time(NULL);

	board->players[board->current_player].start_move_time = currentTime;
		
	printstacks(board->stacks, board->rows ,board->cols);
	ft_printf("Remaining time %d min and %d sec\n", (MAX_TIME - (currentTime - board->players[board->current_player].start_time)) / 60, (MAX_TIME - (currentTime - board->players[board->current_player].start_time)) % 60);	
	ft_printf("\nYour move?\n");
	char *move;
	while ((move = get_next_line(0)) != NULL)
	{
		if (move)
		{
			printf("You entered: %s\n", move);
			if (asked_to_quit(move) || time_is_up(*board, move))
				return (false);
			if (not_a_valid_input(*board, move))
				continue;
			int pos = ft_atoi(move);
			make_move(&(board->stacks[pos - 1]), board->players[board->current_player].piece[0]);
			board->players[board->current_player].number_of_moves++;
			if (player_wins(*board, move))
				return (true);
			free(move);
			break;
		}
		free(move);
	}
	printstacks(board->stacks, board->rows ,board->cols);
	board->current_player = board->current_player == 0 ? 1 : 0;
	return (false);
}