/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:23:55 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/03 17:24:46 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT_H
# define CONNECT_H

#define MAX_TIME 240
#define MAX_MOVE_TIME 40
#define MAX_ROWS 9
#define MAX_COLS 9

#include <time.h>

/**
 * @brief a stack is a column in the board
 * 
 * It is initialized at -1 and it increases as the player puts pieces in it
 * @param data the piece that is in the stack as a char X or O
*/
typedef struct	s_stack
{
	char data[MAX_ROWS + 1];
	int top;
} 				t_stack;

/**
 * @brief a player has 40 sec for move and ttl 4 min
 * 
 * 
*/
typedef struct 	s_player
{
	char 	*name;
	char 	*piece;
	time_t 	start_time;
	time_t 	start_move_time;
	int 	allowed_time;
	int 	allowed_move_time;
	int 	number_of_moves;
}				t_player;

#endif