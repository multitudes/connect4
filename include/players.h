/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:37:39 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/03 18:44:46 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYERS_H
# define PLAYERS_H

#include "connect.h"

void choose_player(t_board *board);
bool player_plays_and_win(t_board *board);
bool ai_plays_and_win(t_board *board);

#endif