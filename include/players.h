/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:37:39 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/04 13:03:39 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYERS_H
# define PLAYERS_H

#include "connect.h"

typedef struct	s_board t_board;

/**
 * @brief a player has 40 sec for move and ttl 4 min
 * 
 * 
*/
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

void choose_player(t_board *board);
bool player_plays_and_wins(t_board *board);
bool ai_plays_randomly_and_wins(t_board *board);
bool ai_plays_minimax_and_wins(t_board *board);

#endif