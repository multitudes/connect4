/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:23:55 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/04 11:37:20 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT_H
# define CONNECT_H

#define MAX_TIME 240
#define MAX_MOVE_TIME 40
#define MAX_ROWS 9
#define MAX_COLS 9

#include <time.h>
#include <stdbool.h>
#include "players.h"

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

#endif