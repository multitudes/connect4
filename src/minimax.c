/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimax.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:51:43 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/04 12:33:55 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "connect.h"

#define MAX_DEPTH 5

int evaluate_board(t_stack *stacks, int rows, int cols, char ai_piece, char player_piece) {
 	// Simple heuristic: count the number of pieces in a row for each player
    // Replace with a more sophisticated evaluation function
    int score = 0;
    // ... implementation of evaluation function
    return score;
}

int minimax(t_stack *stacks, int rows, int cols, int depth, int alpha, int beta, int maximizingPlayer, char ai_piece, char player_piece) {
    if (depth == 0 || check_win(stacks, rows, cols, ai_piece) || check_win(stacks, rows, cols, player_piece)) {
        return evaluate_board(stacks, rows, cols, ai_piece, player_piece);
    }

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

int get_best_move(t_board *board, char ai_piece, char player_piece) {
    int bestMove = -1;
    int bestValue = INT_MIN;
    for (int col = 0; col < board->cols; col++) {
        if (board->stacks[col].top < board->rows - 1) {
            make_move(&board->stacks[col], ai_piece);
            int moveValue = minimax(board->stacks, board->rows, board->cols, MAX_DEPTH, INT_MIN, INT_MAX, 0, ai_piece, player_piece);
            undo_move(&board->stacks[col]);
            if (moveValue > bestValue) {
                bestMove = col;
                bestValue = moveValue;
            }
        }
    }
    return bestMove;
}