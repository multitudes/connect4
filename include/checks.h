/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:28:29 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/07 13:44:53 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKS_H
# define CHECKS_H

#include "connect.h"

int check_win(t_stack*, int, int cols, char player);
int check_horizontal_win(t_stack *stacks, int rows, int cols, char player);
int check_vertical_win(t_stack *stacks, int rows, int cols, char player);
int check_diagonal_win(t_stack *stacks, int rows, int cols, char player);

#endif