/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:37:10 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/04 14:49:12 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "connect.h"
#include <time.h>
#include "utils.h"
#include "checks.h"
#include "players.h"
#include "minimax.h"

/**
 * @brief choose the first player randomly
 * 
 * @param board 
 * Using only rand() without seeding first was definitely 
 * not something i could use since predictably the same player
 * would start the game every time.
 * srand() is used to seed the random number generator.
 */
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
	ft_printf(GREEN "Player %s starts\n", board->players[board->current_player].name);
}

/**
 * @brief AI plays randomly and wins
 * 
 * @param board 
 * @return true 
 * 
 * The AI plays randomly. Returns true if AI wins the game.
 */
bool ai_plays_randomly_and_wins(t_board *board)
{
	time_t currentTime = time(NULL);
	board->players[board->current_player].start_move_time = currentTime;
	int pos = rand() % board->cols + 1;
	make_move(&(board->stacks[pos - 1]), board->players[board->current_player].piece);
	board->players[board->current_player].number_of_moves++;
	if (board->players[board->current_player].number_of_moves > 3)
	{
		if (check_win(board->stacks, board->rows, board->cols, board->players[board->current_player].piece))
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

bool ai_plays_minimax_and_wins(t_board *board)
{
	time_t currentTime = time(NULL);
	board->players[board->current_player].start_move_time = currentTime;
	// int pos = rand() % board->cols + 1;
	int pos = get_best_move(board, board->players[board->current_player].piece, board->players[board->current_player == 0 ? 1 : 0].piece);
	if (pos < 0 || pos >= board->cols)
	{
		ft_printf("Invalid move. Please enter a number between 1 and %d\n", board->cols);
		return false;
	}
	make_move(&(board->stacks[pos]), board->players[board->current_player].piece);
	board->players[board->current_player].number_of_moves++;
	if (board->players[board->current_player].number_of_moves > 3)
	{
		if (check_win(board->stacks, board->rows, board->cols, board->players[board->current_player].piece))
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

bool player_plays_and_wins(t_board *board)
{
	time_t currentTime = time(NULL);

	board->players[board->current_player].start_move_time = currentTime;
		
	printstacks(board->stacks, board->rows ,board->cols);
	ft_printf(GREEN "Remaining time %d min and %d sec\n", (MAX_TIME - (currentTime - board->players[board->current_player].start_time)) / 60, (MAX_TIME - (currentTime - board->players[board->current_player].start_time)) % 60);	
	ft_printf(GREEN "\nYour move?\n");
	char *move;
	while ((move = get_next_line(0)) != NULL)
	{
		if (move)
		{
			// ft_printf(GREEN "You entered: %s\n", move);
			if (asked_to_quit(move) || time_is_up(*board, move))
				return (true);
			if (not_a_valid_input(*board, move))
				continue;
			int pos = ft_atoi(move);
			make_move(&(board->stacks[pos - 1]), board->players[board->current_player].piece);
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