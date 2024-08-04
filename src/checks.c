/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:28:00 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/04 11:36:58 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "connect.h"
#include <checks.h>

/**
 * @brief check if a player has won the game
 */
int check_horizontal_win(t_stack *stacks, int rows, int cols, char player) 
{
	int highestrow = 0;
	// checking first what the highest stack is
	for (int i = 0; i < cols; i++) {
		if (stacks[i].top > highestrow) {
			highestrow = stacks[i].top;
		}
	}
    for (int i = 0; i < highestrow; i++) {
        int count = 0;
        for (int j = 0; j < cols; j++) {
            if (stacks[j].data[i] == player) {
                count++;
                if (count == 4) {
                    return 1;
                }
            } else {
                count = 0;
				if (j == cols -3)
					break ;
            }
        }
    }
    return 0;
}

int check_vertical_win(t_stack *stacks, int rows, int cols, char player) 
{
    for (int i = 0; i < cols; i++) {
        int count = 0;
        for (int j = 0; j <= stacks[i].top; j++) {
            if (stacks[i].data[j] == player) {
                count++;
                if (count == 4) {
                    return 1;
                }
            } else {
                count = 0;
            }
        }
    }
    return 0;
}


int check_diagonal_win(t_stack *stacks, int rows, int cols, char player) 
{
	int highestrow = 0;
	for (int i = 0; i < cols; i++) {
		if (stacks[i].top > highestrow) 
			highestrow = stacks[i].top;
	}
    // Check forward diagonals
    for (int i = 0; i < highestrow - 3; i++) {
        for (int j = 0; j < cols - 3; j++) {
            if (stacks[j].data[i] == player &&
                stacks[j + 1].data[i + 1] == player &&
                stacks[j + 2].data[i + 2] == player &&
                stacks[j + 3].data[i + 3] == player) 
			    return 1;
        }
    }

    // Check backward diagonals
    for (int i = 3; i < highestrow; i++) {
        for (int j = 0; j < cols - 3; j++) {
            if (stacks[j].data[i] == player &&
                stacks[j + 1].data[i - 1] == player &&
                stacks[j + 2].data[i - 2] == player &&
                stacks[j + 3].data[i - 3] == player) 
                return 1;
        }
    }
    return 0;
}

// ... check_diagonal_win function (more complex)

int check_win(t_stack *stacks, int rows, int cols, char player) 
{
    return check_horizontal_win(stacks, rows, cols, player) ||
           check_vertical_win(stacks, rows, cols, player) ||
           check_diagonal_win(stacks, rows, cols, player);
}

