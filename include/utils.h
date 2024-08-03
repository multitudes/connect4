/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:00:42 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/03 18:18:51 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdbool.h>
#include "connect.h"

bool player_wins(t_board board, char *move);
bool not_a_valid_input(t_board board, char *move);
bool time_is_up(t_board board, char *move);
bool asked_to_quit(char *move);
void make_move(t_stack *stack, char piece);
bool init_board(t_board *board, int argc, char **argv);
void printplayers(t_player ai, t_player player);
void printstacks(t_stack *stacks, int rows, int cols);
void init_stacks(t_stack *stacks, int cols);

#endif