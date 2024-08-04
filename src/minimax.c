/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimax.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:51:43 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/04 15:35:40 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "connect.h"
#include "minimax.h"
#include "utils.h"
#include "checks.h"
#include "libft.h"

#define MAX_DEPTH 4

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
	return (a < b) ? a : b;
}

/**
 * @brief check if there are potential wins for the player
 * 
 * @param stacks
 * @param rows
 * @param cols
 * @param piece
 * @return int
 * 
 * Returns zero or a strong bias for the move if it is a potential win
 * I added this because I noticed the AI was notrecognizing potential 
 * winning moves. This function is both used for the AI and the player
 */
int check_potential_wins(t_stack *stacks, int rows, int cols, char piece) {
    int potential_wins = 0;
    // Check rows
    for (int i = 0; i < rows; i++) {
        int count = 0;
        for (int j = 0; j < cols; j++) {
        	if (stacks[j].data[i] == piece &&
                stacks[j + 1].data[i] == piece &&
                stacks[j + 2].data[i] == piece &&
                stacks[j + 3].data[i] == EMPTY) {
                potential_wins += 1000; 
            } else if (stacks[j].data[i] == piece &&
				stacks[j + 1].data[i] == piece &&
				stacks[j + 2].data[i] == EMPTY &&
				stacks[j + 3].data[i] == piece) {
				potential_wins += 1000; 
			} else if (stacks[j].data[i] == piece &&
				stacks[j + 1].data[i] == EMPTY &&
				stacks[j + 2].data[i] == piece &&
				stacks[j + 3].data[i] == piece) {
				potential_wins += 1000; 
			} else if (stacks[j].data[i] == EMPTY &&
				stacks[j + 1].data[i] == piece &&
				stacks[j + 2].data[i] == piece &&
				stacks[j + 3].data[i] == piece) {
				potential_wins += 1000; 
			}
        }
    }
    // Check columns and diagonals similarly
    return potential_wins;
}

/**
 * @brief evaluate the board
 * 
 * @param stacks
 * @param rows
 * @param cols
 * @param ai_piece
 * @param player_piece
 * @return int
 * 
 * Returns the score of the board. It is used by the minimax function
 * to evaluate the board and make the best move.
 * I check for potential win or lose situations first of all, then I check
 * the number of pieces in a row for each player and return a score
 * based on that. Also, same for vertical and diagonals.
 */
int evaluate_board(t_stack *stacks, int rows, int cols, char ai_piece, char player_piece) {
    int score = 1;
	int highestrow = 0;

	score += check_potential_wins(stacks, rows, cols, ai_piece);
    score -= check_potential_wins(stacks, rows, cols, player_piece);

	// checking first what the highest stack is
	for (int i = 0; i < cols; i++) {
		if (stacks[i].top > highestrow) {
			highestrow = stacks[i].top;
		}
	}
 	// Simple heuristic: more points for the number of pieces in a row for each player
	for (int i = 0; i <= highestrow; i++) {
		int ai_count = 0, player_count = 0;
		for (int j = 0; j < cols; j++) {
			if (stacks[j].data[i] == ai_piece) {
				ai_count++;
				player_count = 0;
			} else if (stacks[j].data[i] == player_piece) {
				player_count++;
				ai_count = 0;
			} else {
				ai_count = 0;
				player_count = 0;
			}
			if (ai_count == 4) return 1000000; // AI wins
            if (player_count == 4) return -1000000; // Player wins
			score += ai_count * ai_count - player_count * player_count;
		}
    }
	for (int i = 0; i < cols; i++) {
        int ai_count = 0, player_count = 0;
        for (int j = 0; j <= stacks[i].top; j++) {
            if (stacks[i].data[j] == ai_piece) {
                ai_count++;
                player_count = 0;
            } else if (stacks[i].data[j] == player_piece) {
                player_count++;
                ai_count = 0;
            } else {
                ai_count = 0;
                player_count = 0;
            }
			if (ai_count == 4) return 1000000; // AI wins
            if (player_count == 4) return -1000000; // Player wins
            score += ai_count * ai_count - player_count * player_count;
        }
    }
	for (int i = 0; i <= highestrow - 3; i++) {
        for (int j = 0; j < cols - 3; j++) {
            int ai_count = 0, player_count = 0;
            // Check forward diagonal
             for (int k = 0; k < 4; k++) {
                if (stacks[j + k].data[i + k] == ai_piece) {
                    ai_count++;
                    player_count = 0;
                } else if (stacks[j + k].data[i + k] == player_piece) {
                    player_count++;
                    ai_count = 0;
                } else {
                    ai_count = 0;
                    player_count = 0;
                }
                if (ai_count == 4) return 1000000; // AI wins
                if (player_count == 4) return -1000000; // Player wins
                score += ai_count * ai_count - player_count * player_count;
			}
        }
    }

	return score;
}

/**
 * @brief minimax algorithm
 * 
 * @param stacks
 * @param rows
 * @param cols
 * @param depth
 * @param alpha
 * @param beta
 * @param maximizingPlayer
 * @param ai_piece
 * @param player_piece
 * @return int
 * 
 * The minimax algorithm is a recursive algorithm that is used to find the best move
 * for the AI. The algorithm is based on the concept of a game tree, where each
 * node represents a possible move, and the edges represent the possible outcomes of
 * that move. The algorithm works by recursively exploring the game tree, evaluating
 * the board at each node, and choosing the move that maximizes the AI's chances of
 * winning. The algorithm uses a depth parameter to limit the number of moves it explores,
 * and it uses alpha-beta pruning to improve efficiency by eliminating branches of the
 * game tree that are guaranteed to be suboptimal.
 */
int minimax(t_stack *stacks, int rows, int cols, int depth, int alpha, int beta, int maximizingPlayer, char ai_piece, char player_piece) {
    if (depth == 0 || check_win(stacks, rows, cols, ai_piece) || check_win(stacks, rows, cols, player_piece)) {
        if (check_win(stacks, rows, cols, ai_piece)) {
            return 10000 + (MAX_DEPTH - depth) * 10000; // AI wins
        } else if (check_win(stacks, rows, cols, player_piece)) {
            return -10000 - (MAX_DEPTH - depth) * 10000; // Player wins
        } else {
            return evaluate_board(stacks, rows, cols, ai_piece, player_piece);
        }
    }
	// Maximizing player is the AI. I want the AI to win :)
    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int col = 0; col < cols; col++) {
            if (stacks[col].top < rows - 1) {
                make_move(&stacks[col], ai_piece);
                int eval = minimax(stacks, rows, cols, depth - 1, alpha, beta, 0, ai_piece, player_piece);
                undo_move(&stacks[col]);
                maxEval = max(maxEval, eval);
                alpha = max(alpha, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int col = 0; col < cols; col++) {
            if (stacks[col].top < rows - 1) {
                make_move(&stacks[col], player_piece);
                int eval = minimax(stacks, rows, cols, depth - 1, alpha, beta, 1, ai_piece, player_piece);
                undo_move(&stacks[col]);
                minEval = min(minEval, eval);
                beta = min(beta, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return minEval;
    }
}

/**
 * @brief get the best move for the AI
 * 
 * @param board
 * @param ai_piece
 * @param player_piece
 * @return int
 * 
 * This function is used to get the best move for the AI. It uses the minimax
 * algorithm to evaluate the board and find the best move. The function returns
 * the column number of the best move which starts at zero!
 */
int get_best_move(t_board *board, char ai_piece, char player_piece) {
    int bestMove = -1;
    int bestValue = INT_MIN;
    for (int col = 0; col < board->cols; col++) {
        if (board->stacks[col].top < board->rows - 1) {
            make_move(&board->stacks[col], ai_piece);
            int moveValue = minimax(board->stacks, board->rows, board->cols, MAX_DEPTH, INT_MIN, INT_MAX, 0, ai_piece, player_piece);
            // ft_printf("moveValue: %d for col %d\n", moveValue, col + 1);
			undo_move(&board->stacks[col]);
            if (moveValue > bestValue) {
                bestMove = col;
                bestValue = moveValue;
            }
        }
    }
	// ft_printf("Best move: %d\n", bestMove);
    return bestMove;
}