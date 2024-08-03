/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:00:26 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/03 18:17:12 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "connect.h"

void init_stacks(t_stack *stacks, int cols)
{
	for (int i = 0; i < cols; i++)
	{
		ft_memset(stacks[i].data, '-', MAX_ROWS);
		stacks[i].data[MAX_ROWS] = '\0';
		stacks[i].top = -1;
	}
}


void printstacks(t_stack *stacks, int rows, int cols)
{	
	for (int i = rows - 1; i >= 0; i--)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%c", stacks[j].data[i]);
		}
		printf("\n");
	}
}

void printplayers(t_player ai, t_player player)
{
	printf("Player 1: %s --- ", player.name);
	printf("Player 2: %s\n", ai.name);
}

bool init_board(t_board *board, int argc, char **argv)
{
	board->rows = 0;
	board->cols = 0;
	board->current_player = 0;

	board->has_GUI = false;
	if (argc == 4 && (ft_strcmp(argv[3], "--gui") == 0 || ft_strcmp(argv[3], "-g") == 0))
		board->has_GUI = true;
	else
	if (argc != 3 )
	{
		ft_printf("Usage: ./connect4 <rows> <cols> (<--gui | -g>)\n");
		return (false);
	}

	board->rows = ft_atoi(argv[1]);
	if (board->rows < 6 || board->rows > 9)
	{
		ft_printf("The number of rows must be between 6 and 9\n");
		return (false);
	}
	board->cols = ft_atoi(argv[2]);
	if (board->cols < 7 || board->cols > 9)
	{
		ft_printf("The number of columns must be between 7 and 9\n");
		return (false);
	}
	return (true);
}

void make_move(t_stack *stack, char piece)
{

	stack->top++;
	stack->data[stack->top] = piece;
}

bool asked_to_quit(char *move)
{
	if (ft_strcmp(move, "q\n") == 0)
	{
		printf("quitting\n\n");
		free(move);
		return (true);
	}
	return (false);
}

bool time_is_up(t_board board, char *move)
{
	time_t currentTime = time(NULL);
	if ((currentTime - board.players[board.current_player].start_move_time > board.players[board.current_player].allowed_move_time) || \
		(currentTime - board.players[board.current_player].start_time > board.players[board.current_player].allowed_time))
	{
		ft_printf("But your time is up...\n");
		ft_printf("You lose!\n");
		free(move);
		return (true);
	}
	return (false);
}

bool not_a_valid_input(t_board board, char *move)
{
// check move is a number and between 1 and board.cols
	int pos = ft_atoi(move);
	if (pos < 1 || pos > board.cols)
	{
		ft_printf("Invalid move. Please enter a number between 1 and %d\n", board.cols);
		free(move);
		return (true);
	}
	// check if the stack is full
	if (board.stacks[pos - 1].top == board.rows - 1)
	{
		ft_printf("The stack is full. Please enter another move\n");
		free(move);
		return (true);
	}
	return (false);
}

bool player_wins(t_board board, char *move)
{
	if (board.players[board.current_player].number_of_moves++ > 3)
	{
		if (check_win(board.stacks, board.rows, board.cols, board.players[board.current_player].piece[0]))
		{
			ft_printf("Player %s wins!\n", board.players[board.current_player].name);
			printstacks(board.stacks, board.rows ,board.cols);
			ft_printf("\nGame over\n");
			free(move);
			return (true);
		}
	}
	return (false);
}