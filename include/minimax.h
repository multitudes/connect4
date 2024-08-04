/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimax.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:34:34 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/04 12:34:55 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAX_H
# define MINIMAX_H

#include "connect.h"

int evaluate_board(t_stack *stacks, int rows, int cols, char ai_piece, char player_piece);
int minimax(t_stack *stacks, int rows, int cols, int depth, int alpha, int beta, int maximizingPlayer, char ai_piece, char player_piece);
int get_best_move(t_board *board, char ai_piece, char player_piece);

#endif
