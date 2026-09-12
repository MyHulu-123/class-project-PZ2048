#include "game_logic.h"
#include "utils.h"
#include <algorithm>
#include <iomanip>

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
static bool has_previous;

static bool CheckMoveUp(){
    for(int j = 0; j < col_num; j++){
        for(int i = 1; i < row_num; i++){
            if(board[i][j] != 0 && board[i-1][j] == 0)return true;
            if(board[i][j] != 0 && board[i-1][j] == board[i][j])return true;
        }
    }
    return false;
}

static bool CheckMoveDown(){
    for(int j = 0; j < col_num; j++){
        for(int i = row_num-2; i >= 0; i--){
            if(board[i][j] != 0 && board[i+1][j] == 0)return true;
            if(board[i][j] != 0 && board[i+1][j] == board[i][j])return true;
        }
    }
    return false;
}

static bool CheckMoveLeft(){
    for(int i = 0; i < row_num; i++){
        for(int j = 1; j < col_num; j++){
            if(board[i][j] != 0 && board[i][j-1] == 0)return true;
            if(board[i][j] != 0 && board[i][j-1] == board[i][j])return true;
        }
    }
    return false;
}

static bool CheckMoveRight(){
    for(int i = 0; i < row_num; i++){
        for(int j = col_num-2; j >= 0; j--){
            if(board[i][j] != 0 && board[i][j+1] == 0)return true;
            if(board[i][j] != 0 && board[i][j+1] == board[i][j])return true;
        }
    }
    return false;
}

static void MoveUp(){
    for(int j = 0; j < col_num; j++){
        int pre_row = 0;
        for(int i = 0; i < row_num;){
            if(board[i][j] == 0)i++;
            else{
                std::swap(board[i][j],board[pre_row][j]);
                i++;
                while (i < row_num && board[i][j]==0)i++;
                if(i < row_num && board[i][j] == board[pre_row][j]){
                    board[i][j] = 0;
                    board[pre_row][j] *= 2;
                    score += board[pre_row][j];
                    i++;
                }
                pre_row++;
            }
        }
    }
}

static void MoveDown(){
    for(int j = 0; j < col_num; j++){
        int pre_row = row_num-1;
        for(int i = row_num-1; i >= 0;){
            if(board[i][j] == 0)i--;
            else{
                std::swap(board[i][j],board[pre_row][j]);
                i--;
                while (i >= 0 && board[i][j]==0)i--;
                if(i >= 0 && board[i][j] == board[pre_row][j]){
                    board[i][j] = 0;
                    board[pre_row][j] *= 2;
                    score += board[pre_row][j];
                    i--;
                }
                pre_row--;
            }
        }
    }
}

static void MoveLeft(){
    for(int i = 0; i < row_num; i++){
        int pre_col = 0;
        for(int j = 0; j < col_num;){
            if(board[i][j] == 0)j++;
            else{
                std::swap(board[i][j],board[i][pre_col]);
                j++;
                while (j < col_num && board[i][j]==0)j++;
                if(j < col_num && board[i][j] == board[i][pre_col]){
                    board[i][j] = 0;
                    board[i][pre_col] *= 2;
                    score += board[i][pre_col];
                    j++;
                }
                pre_col++;
            }
        }
    }
}

static void MoveRight(){
    for(int i = 0; i < row_num; i++){
        int pre_col = col_num-1;
        for(int j = col_num-1; j >= 0;){
            if(board[i][j] == 0)j--;
            else{
                std::swap(board[i][j],board[i][pre_col]);
                j--;
                while (j >= 0 && board[i][j]==0)j--;
                if(j >= 0 && board[i][j] == board[i][pre_col]){
                    board[i][j] = 0;
                    board[i][pre_col] *= 2;
                    score += board[i][pre_col];
                    j--;
                }
                pre_col--;
            }
        }
    }
}

static void UpdatePrevious(){
    previous_board = board;
    previous_score = score;
    has_previous = true;
}

void Start(int row_num, int col_num, int target, uint game_seed) {
    PZ2048::row_num = row_num;
    PZ2048::col_num = col_num;
    PZ2048::target = target;
    score = previous_score = steps = 0;
    has_previous = false;
    srand(game_seed);
    board.assign(row_num,std::vector<int>(col_num,0));
    previous_board.assign(row_num,std::vector<int>(col_num,0));
    TryGenerateTile();
}

std::pair<int, int> EndGame() {
    return {steps, score};
}

int GetRows() {
    return row_num;
}

int GetCols() { 
    return col_num;
}

bool TryRun(char dir) {
    switch (dir)
    {
        case 'w':
            if(CheckMoveUp()){
                UpdatePrevious();
                MoveUp();
                steps++;
                TryGenerateTile();
                return true;
            }
            break;
        case 's':
            if(CheckMoveDown()){
                UpdatePrevious();
                MoveDown();
                steps++;
                TryGenerateTile();
                return true;
            }
            break;
        case 'a':
            if(CheckMoveLeft()){
                UpdatePrevious();
                MoveLeft();
                steps++;
                TryGenerateTile();
                return true;
            }
            break;
        case 'd':
            if(CheckMoveRight()){
                UpdatePrevious();
                MoveRight();
                steps++;
                TryGenerateTile();
                return true;
            }
            break;
    }
    return false;
}

bool Undo() {
    if(!has_previous)return false;
    has_previous = false;
    steps--;
    board = previous_board;
    score = previous_score;
    return true;
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
    if(CheckMoveUp())return false;
    if(CheckMoveDown())return false;
    if(CheckMoveLeft())return false;
    if(CheckMoveRight())return false;
    return true;
}

void PrintBoard() {
    for(int i = 0; i < row_num; i++){
        for (int j = 0; j < col_num; j++)
        {
            std:: cout << std::left << std::setw(4) << board[i][j] << ' ';
        }
        std::cout << '\n';
        
    }
    /** Hint: You MUST USE std:cout **/
    /** Hint: When you print the board, you have to use 1 space to split the number**/
    /** Hint: More Specifically, you have to open *.ans to check whether your output format is correct**/
}

}
