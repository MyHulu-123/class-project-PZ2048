#include "game_logic.h"

#include <algorithm>
#include <iostream>

namespace PZ2048 {

// You can add global variables here.
// If your IDE suggested some identifiers like "static", "inline" or "extern", you'd better learn about them
// and decide whether, how and where to use them.
// Or if you want to use type aliases, structures, classes or something else,
// just go ahead! You are free (and encouraged) to use them to make your code clearer and more integrated.
// Or... can you?
// Just don't modify the signatures of existing functions.

// Don't try to use extern variables from user_logic.cpp. You're not supposed to communicate through this way.
// After all, the game logic on the online judger won't contain extern variables same as yours.
// You are free to add helper functions.
static int row_num,col_num,target;
static std::vector<std::vector<int>> board,previous_board;
static int score,previous_score,steps;

void Start(int row_num, int col_num, int target, uint game_seed) {
    PZ2048::row_num = row_num;
    PZ2048::col_num = col_num;
    PZ2048::target = target;
    score = previous_score = steps = 0;
    srand(game_seed);
}

std::pair<int, int> EndGame() {
    /** implementation here **/
    return {steps, score};
}

int GetRows() {
    return row_num;
}

int GetCols() { 
    return col_num;
}

bool TryRun(char dir) {
    /** implementation here **/
    return false;
}

bool Undo() {
    /** implement here. **/
    /**in the process you need to undo the operation and both the score**/
    /**for example we have 0 0 0 4 4pts from 2 0 0 2 0pts, after we undo, we get 2 0 0 2 0pts**/
    return false;
}

void SetTile(int row_index, int col_index, int value) {
    board[row_index][col_index] = value;
}

int GetTile(int row_index, int col_index) {
    return board[row_index][col_index];
}

int Score() { 
    return score;
}

int Steps() { 
    return steps;
}

int GetTarget() { 
    return target;
}

bool HasReachedTarget() {
    int max_number = 0;
    for(int i = 0; i < row_num; i++){
        for(int j = 0; j < col_num; j++){
            max_number = std::max(max_number, board[i][j]);
        }
    }
    return max_number >= target;
}

bool Stuck() {
    /** implement here. **/
    return false;
}

void PrintBoard() {
    /** implement here. **/
    /** Hint: You MUST USE std:cout **/
    /** Hint: When you print the board, you have to use 1 space to split the number**/
    /** Hint: More Specifically, you have to open *.ans to check whether your output format is correct**/
}

}
