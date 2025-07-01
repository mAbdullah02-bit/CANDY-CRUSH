////                            COMMENTS EXPLAINING FUNCTIONALITY!
//
 //                 /*
  /*This C++ program implements a simplified version of the Candy Crush game.
 The game revolves around a grid of candies, and the objective is to swap adjacent
 candies to create matches of three or more candies in a row or column.When a match is
  formed, those candies are removed, and new candies fall from the top to popuE the gaps
 .The game continues until no more matches are possible.The implementation employs a 2D array
 to represent the candy grid, and functions are defined to handle swapping, checking for matches,
  and updating the grid state.The game loop manages user input, grid updates, and score tracking.This well
  - organized and modular design enables easy expansion or modification of game features, making it an ideal
  foundation for building upon or customizing the Candy Crush game.*/






  //              -------------------------------CODE------------------------------------

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <Windows.h>
#include <fstream>
#include<stdlib.h>
#include<conio.h>
#include <chrono>
#include <thread>
using namespace std;

//   -------------------------- DEFINING KEYS-----------------------------

#define KEY_ENTER 13
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// -------------------------SETTING COLOURS-----------------------------

const string ch1 = "\033[31m#\033[0m";
const string ch2 = "\033[34m@\033[0m";
const string ch3 = "\033[32m&\033[0m";
const string ch4 = "\033[35m%\033[0m";
const string ch5 = "\033[33m*\033[0m";
const string ch6 = "\033[36m+\033[0m";
const string ch7 = "\033[37m?\033[0m";


// -------------------------Global variables-----------------------------
int moves = 15;
int score = 0;
string name;
const int easyTimeLimit = 60; // 60 seconds for easy mode
const int hardTimeLimit = 45; // 45 seconds for hard mode

//string array for 5 characters easy mode
const string ch_array[] = { ch1, ch2, ch3, ch4, ch5 };

//string array for 7 character hard mode
const string ch_array_h[] = { ch1, ch2, ch3, ch4, ch5, ch6, ch7 };

//consecutiveLimit is a variable to use in isvalid funstion as a limit 
const int consecutiveLimit = 2;



//-------------------------PROTOTYPES---------------------------


void easy_board();
void hard_board();

void aftergame(int score);

void printBoard();
string rand_candy_e(string candy);
string rand_candy(string candy);
void swaphtop(string arr[][10]);
void popuE(string arr[8][8]);






void aftergame(int score) {  //   After game screen for win or lose conditions.

    if (score > 200)
    {
        cout << "YOU WIN!" << endl;
        cout << "  *           **            *\n";
        cout << "  *           **            *\n";
        cout << "  *           **            *\n";
        cout << "  *           **            *\n";
        cout << "  *           **            *\n";
        cout << "  *           **            *\n";
        cout << "  *           **            *\n";
        cout << "   *         * *            *\n";
        cout << "    *       *    *         *\n";
        cout << "     *     *       *      *\n";
        cout << "      *  *           *   *  \n";
        cout << "       *               *  \n \n\n";
    }

    else
    {
        cout << "YOU LOSE" << endl;

        cout << "  ***\n";
        cout << "  ***\n";
        cout << "  ***\n";
        cout << "  ***\n";
        cout << "  ***\n";
        cout << "  ***\n";
        cout << "  ***\n";
        cout << "  ***\n";
        cout << "  ***\n";
        cout << "  *** * * * * * * * *\n";
        cout << "  ** * * * * * * * * *\n\n\n";
    }

}

string  rand_candy_e(string candy) {  // Generate ran cadies
    int c;
    c = rand() % 5 + 1;
    if (c == 1)
        candy = ch1;
    else if (c == 2)
        candy = ch2;
    else if (c == 3)
        candy = ch3;
    else if (c == 4)
        candy = ch4;
    else if (c == 5)
        candy = ch5;
    return candy;
}




string rand_candy(string candy) { // Generates rand candy
    int c;
    c = (rand() % 7) + 1;
    if (c == 1)
        candy = ch1;
    else if (c == 2)
        candy = ch2;
    else if (c == 3)
        candy = ch3;
    else if (c == 4)
        candy = ch4;
    else if (c == 5)
        candy = ch5;
    else if (c == 6)
        candy = ch6;
    else if (c == 7)
        candy = ch7;
    return candy;
}

void popuE(string arr[8][8]) // check if array element has X To replace with random candies.
{
    string candy = "X";
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if (arr[x][y] == "X")
            {
                arr[x][y] = rand_candy_e(candy);
                if (arr[x][y] == arr[x][y + 1] && arr[x][y] == arr[x][y + 2] ||//column wise horizontal
                    arr[x][y] == arr[x + 1][y] && arr[x][y] == arr[x + 2][y] || // row wise vertical
                    arr[x][y] == arr[x - 1][y + 1] && arr[x][y] == arr[x + 1][y - 1] || //forward diagonal
                    arr[x][y] == arr[x - 1][y - 1] && arr[x][y] == arr[x + 1][y + 1])  //backward diagonal
                {
                    char c = 'X';
                    arr[x][y] = rand_candy_e(candy);
                }
            }
        }
    }
}


void swaphtop(string arr[][10])// Clearing the top Array indexec
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (arr[i][j] == "X")
            {
                int l = i, m = j;
                while (l > 0)
                {
                    arr[l][m] = arr[l - 1][m];
                    l--;
                }
            }
        }
    }
}

void popuH(string arr[10][10]) // check if array element has X to replace with random candy.
{
    string candy = "X";
    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            if (arr[x][y] == "X")
            {
                arr[x][y] = rand_candy(candy);
                if (arr[x][y] == arr[x][y + 1] && arr[x][y] == arr[x][y + 2] ||//  horizontal
                    arr[x][y] == arr[x + 1][y] && arr[x][y] == arr[x + 2][y] || //  vertical
                    arr[x][y] == arr[x - 1][y + 1] && arr[x][y] == arr[x + 1][y - 1] || // diagonal
                    arr[x][y] == arr[x - 1][y - 1] && arr[x][y] == arr[x + 1][y + 1])  //  Inverse  diagonal
                {
                    arr[x][y] = rand_candy(candy);
                }
            }
        }
    }
}

void swapstop(string arr[8][8]) //  Clearing top Array indexes
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (arr[i][j] == "X")
            {
                int l = i, m = j;
                while (l > 0)
                {
                    arr[l][m] = arr[l - 1][m];
                    l--;
                }
            }
        }
    }
}

bool isNeighbor(int selectedRow, int selectedCol, int currentRow, int currentCol) {
    // Check if the candies are with each other
    int rowDiff = abs(selectedRow - currentRow);
    int colDiff = abs(selectedCol - currentCol);
    return (rowDiff == 1 && colDiff == 0) || (rowDiff == 0 && colDiff == 1);
}

void checks(string arr[][8], int i, int j) {

    int  move = 15;

    while (move > 0)
    {

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                
                if (arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j])// vertical match
                {
                    arr[i][j] = 'X';
                    arr[i + 1][j] = 'X';
                    arr[i + 2][j] = 'X';
                    score += 1;
                    system("CLS");

                    cout << "\033[33m\t\t\t\t\t\t\t\t\tSweet\033[0m" << endl;
                    cout << "\033[33m\t\t\t\t\t\t\t\t\tLOADING\033[0m" << endl;

                    Sleep(5);
                    system("CLS");

                }
                else if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2])  // horizontal match
                {
                    arr[i][j] = 'X';
                    arr[i][j + 1] = 'X';
                    arr[i][j + 2] = 'X';
                    score += 1;

                    system("CLS");

                    cout << "\033[33m\t\t\t\t\t\t\t\t\tSweet\033[0m" << endl;
                    cout << "\033[33m\t\t\t\t\t\t\t\t\tLOADING\033[0m" << endl;

                    Sleep(5);
                    system("CLS");

                }
                else if (arr[i][j] == arr[i - 1][j + 1] && arr[i][j] == arr[i + 1][j - 1]) //  diaginal match
                {
                    arr[i][j] = 'X';
                    arr[i - 1][j + 1] = 'X';
                    arr[i + 1][j - 1] = 'X';
                    score += 2;
                    system("CLS");

                    cout << "\033[33m\t\t\t\t\t\t\t\t\tSweet\033[0m" << endl;
                    cout << "\033[33m\t\t\t\t\t\t\t\t\tLOADING\033[0m" << endl;

                    Sleep(5);
                    system("CLS");

                }
                else if (arr[i][j] == arr[i - 1][j - 1] && arr[i][j] == arr[i + 1][j + 1])// inverse diagonal match
                {
                    arr[i][j] = 'X';
                    arr[i - 1][j - 1] = 'X';
                    arr[i + 1][j + 1] = 'X';
                    score += 2;

                    system("CLS");

                    cout << "\033[33m\t\t\t\t\t\t\t\t\tSweet\033[0m" << endl;
                    cout << "\033[33m\t\t\t\t\t\t\t\t\tLOADING\033[0m" << endl;

                    Sleep(5);
                    system("CLS");

                }
                else if (arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j] &&
                    arr[i][j] == arr[i + 2][j + 1] && arr[i][j] == arr[i + 2][j + 2])//L shape match
                {
                    arr[i][j] = 'X';
                    arr[i + 1][j] = 'X';
                    arr[i + 2][j] = 'X';
                    arr[i][j + 1] = 'X';
                    arr[i][j + 2] = 'X';
                    score += 3;
                    system("CLS");

                    cout << "\033[33m\t\t\t\t\t\t\t\t\tSweet\033[0m" << endl;
                    cout << "\033[33m\t\t\t\t\t\t\t\t\tLOADING\033[0m" << endl;

                    Sleep(5);
                    system("CLS");

                }
            }
        }
        move--;

        swapstop(arr);
        popuE(arr);


    }

}

void checkh(string arr[][10], int i, int j) {

    int move = 15;

    while (move != 0)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                int c = 0;
               
                if (arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j])// vertical match
                {
                    arr[i][j] = 'X';
                    arr[i + 1][j] = 'X';
                    arr[i + 2][j] = 'X';
                    score += 1;
                    system("CLS");

                    cout << "\033[33m\t\t\t\t\t\t\t\t\tSweet\033[0m" << endl;
                    cout << "\033[33m\t\t\t\t\t\t\t\t\tLOADING\033[0m" << endl;

                    Sleep(5);
                    system("CLS");

                }
                else if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2])  // horizontal match
                {
                    arr[i][j] = 'X';
                    arr[i][j + 1] = 'X';
                    arr[i][j + 2] = 'X';
                    score += 1;
                    system("CLS");

                    cout << "\033[33m\t\t\t\t\t\t\t\t\tSweet\033[0m" << endl;
                    cout << "\033[33m\t\t\t\t\t\t\t\t\tLOADING\033[0m" << endl;

                    Sleep(5);
                    system("CLS");


                }
                else if (arr[i][j] == arr[i - 1][j + 1] && arr[i][j] == arr[i + 1][j - 1]) //  Diaginal match
                {
                    arr[i][j] = 'X';
                    arr[i - 1][j + 1] = 'X';
                    arr[i + 1][j - 1] = 'X';
                    score += 20;
                    score += 1;
                    system("CLS");

                    cout << "\033[33m\t\t\t\t\t\t\t\t\tSweet\033[0m" << endl;
                    cout << "\033[33m\t\t\t\t\t\t\t\t\tLOADING\033[0m" << endl;

                    Sleep(5);
                    system("CLS");


                }
                else if (arr[i][j] == arr[i - 1][j - 1] && arr[i][j] == arr[i + 1][j + 1])// inverse diagonal match
                {
                    arr[i][j] = 'X';
                    arr[i - 1][j - 1] = 'X';
                    arr[i + 1][j + 1] = 'X';
                    score += 1;
                    system("CLS");

                    cout << "\033[33m\t\t\t\t\t\t\t\t\tSweet\033[0m" << endl;
                    cout << "\033[33m\t\t\t\t\t\t\t\t\tLOADING\033[0m" << endl;

                    Sleep(5);
                    system("CLS");
                }
                else if (arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j] &&
                    arr[i][j] == arr[i + 2][j + 1] && arr[i][j] == arr[i + 2][j + 2])//L shape match
                {
                    arr[i][j] = 'X';
                    arr[i + 1][j] = 'X';
                    arr[i + 2][j] = 'X';
                    arr[i][j + 1] = 'X';
                    arr[i][j + 2] = 'X';
                    score += 3;
                    system("CLS");

                    cout << "\033[33m\t\t\t\t\t\t\t\t\tSweet\033[0m" << endl;
                    cout << "\033[33m\t\t\t\t\t\t\t\t\tLOADING\033[0m" << endl;

                    Sleep(5);
                    system("CLS");
                }
            }
        }
        move--;
        swaphtop(arr);
        popuH(arr);

    }

}
void displayArray(string array[][8], int selectedRow, int selectedCol) {
    system("cls");  // Clear the console screen
    cout << endl;
    //to display a message of player and mode choosed by him/her.
    cout << "\033[31m\t\t\t\t\t\t " << name << " Choose EASY MODE\033[0m\n";
    cout << "\033[31m\t\t\t\t\t\t ====================\033[0m\n";

    cout << "\n\n\n";
    for (int i = 0; i < 8; ++i) {
        cout << "\t\t\t\t";
        for (int j = 0; j < 8; ++j) {
            if (i == selectedRow && j == selectedCol) {
                cout << "(x) | ";

            }
            else {
                cout << " " << array[i][j] << "  | ";
            }
        }
        cout << endl;
        cout << "\t\t\t\t------------------------------------------------";
        cout << endl;
        cout << '\n';
    }

    cout << "\n\n\t\tScore: " << score << "\t\tMoves: " << moves;
    cout << "\n\n\033[31m Press Zero for shuffling the board if there is no match left!\033[0m" << endl;



}
void swape(string board[][8]) {
    int currentRow = 0;
    int currentCol = 0;


    char key;
    int selectedRow = 0;
    int selectedCol = 0;
    bool candySelected = false;



    string temp1;
    std::chrono::seconds duration(60); // TIME LIMIT
    auto startTime = std::chrono::high_resolution_clock::now();
    do {
        for (int i = 0; i < 5; ++i) {
            displayArray(board, currentRow, currentCol);

            key = _getch(); // Get the key without waiting for Enter

            switch (key) {
            case KEY_UP: // Up arrow key
                if (currentRow > 0) {
                    --currentRow;
                }
                break;
            case KEY_DOWN: // Down arrow key
                if (currentRow < 8 - 1) {
                    ++currentRow;
                }
                break;
            case KEY_LEFT: // Left arrow key
                if (currentCol > 0) {
                    --currentCol;
                }
                break;
            case KEY_RIGHT: // Right arrow key
                if (currentCol < 8 - 1) {
                    ++currentCol;
                }
                break;
            case KEY_ENTER: // Select or swap candy
                if (!candySelected) {
                    // First press of ENTER - select candy
                    selectedRow = currentRow;
                    selectedCol = currentCol;
                    candySelected = true;
                }
                else {

                }
                break;
            case 's': // Swap candy when 's' key is pressed
                if (candySelected && isNeighbor(selectedRow, selectedCol, currentRow, currentCol)) {
                    // Swap only if the selected candy and the current candy are neighbors
                    swap(board[selectedRow][selectedCol], board[currentRow][currentCol]);

                    checks(board, currentRow, currentCol);

                  
                    moves--;

                }
                candySelected = false;
                break;
            case '0':
                easy_board();

                break;
            }
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

            // Check if the time limit is reached
            if (elapsedTime >= duration) {
                system("cls");
                cout << "\033[31m\t\t\t\t\t\t\t\tTimes Up!!\033[0m" << endl;
                cout << "\033[31m\t\t\t\t\t\t\t\tYour score: \033[0m" << score << endl;
                cout << "\033[31m\t\t\t\t\t\t\t\tPlayer Name\033[0m" << name << endl;
                Sleep(5000);
                system("cls");
                cout << "Program is exiting." << endl;
                exit(5);
            }
        }
    } while (moves != 0); // Exit when loop = zero

}

void displayArray1(string array[][10], int selectedRow, int selectedCol) {
    system("cls");
    cout << endl;// Clear the console screen
    //to display a message of player and mode choosed by him/her.
    cout << endl;
    cout << "\033[31m\t\t\t\t\t\t " << name << " Choose HARD MODE\033[0m\n";
    cout << "\033[31m\t\t\t\t\t\t ====================\033[0m\n";

    cout << "\n\n\n";
    for (int i = 0; i < 10; ++i) {
        cout << "\t\t\t\t";
        for (int j = 0; j < 10; ++j) {
            if (i == selectedRow && j == selectedCol) {
                cout << "(+) | ";

            }
            else {
                cout << " " << array[i][j] << "  | ";
            }
        }
        cout << endl;
        cout << "\t\t\t\t------------------------------------------------------------";
        cout << endl;
        cout << '\n';
    }
    cout << "\n\n\t\tScore: " << score << "\t\tMoves: " << moves;
    cout << "\n\n\033[31m Press Zero for shuffling the board if there is no match left!\033[0m" << endl;



}

void swaph(string board[][10]) {

    int currentRow = 0;
    int currentCol = 0;


    char key;
    int selectedRow = 0;
    int selectedCol = 0;
    bool candySelected = false;



    string temp1;
    std::chrono::seconds duration(40); // TIME LIMIT
    auto startTime = std::chrono::high_resolution_clock::now();
    do {

        displayArray1(board, currentRow, currentCol);

        key = _getch(); // Get the key without waiting for Enter

        switch (key) {
        case KEY_UP: // Up arrow key
            if (currentRow > 0) {
                --currentRow;
            }
            break;
        case KEY_DOWN: // Down arrow key
            if (currentRow < 10 - 1) {
                ++currentRow;
            }
            break;
        case KEY_LEFT: // Left arrow key
            if (currentCol > 0) {
                --currentCol;
            }
            break;
        case KEY_RIGHT: // Right arrow key
            if (currentCol < 10 - 1) {
                ++currentCol;
            }
            break;
        case KEY_ENTER: // Select or swap candy
            if (!candySelected) {
                // First press of ENTER - select candy
                selectedRow = currentRow;
                selectedCol = currentCol;
                candySelected = true;
            }
            else {
                // Second press of ENTER - navigate for swapping
                // Do nothing here, just wait for arrow key or 's' key
            }
            break;
        case 's': // Swap candy when 's' key is pressed
            if (candySelected && isNeighbor(selectedRow, selectedCol, currentRow, currentCol)) {
                // Swap only if the selected candy and the current candy are neighbors
                swap(board[selectedRow][selectedCol], board[currentRow][currentCol]);

                checkh(board, currentRow, currentCol);

                moves--;

            }
            candySelected = false;
            break;

        case '0':
            hard_board();

            break;

        }
        //Time counter
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

        // Check if the time limit is reached
        if (elapsedTime >= duration) {
            system("cls");
            cout << "\033[31m\t\t\t\t\t\t\t\tTimes Up!!\033[0m" << endl;
            cout << "\033[31m\t\t\t\t\t\t\t\tYour score: \033[0m" << score << endl;
            cout << "\033[31m\t\t\t\t\t\t\t\tPlayer Name: \033[0m" << name << endl;
            Sleep(5000);
            system("cls");
            cout << "Program is exiting." << endl;
            exit(5);
        }
    } while (moves != 0); // breaks the loop when moves = 0

}



// Function to check if placing a candy at a certain position is valid For Easy Display
bool isValid(string board[8][8], int row, int col, string candy) {
    // Check horizontally
    int countHorizontal = 0;
    for (int i = col - consecutiveLimit; i <= col; ++i) {
        if (i >= 0 && board[row][i] == candy) {
            countHorizontal++;
        }
        else {
            break;
        }
    }
    // Check vertically
    int countVertical = 0;
    for (int i = row - consecutiveLimit; i <= row; ++i) {
        if (i >= 0 && board[i][col] == candy) {
            countVertical++;
        }
        else {
            break;
        }
    }
    // Check if candy appears on three or more consecutive blocks
    return countHorizontal < consecutiveLimit && countVertical < consecutiveLimit;
}

//print board function for easy board
void printBoard(string board[8][8]) {
    for (int i = 0; i < 8; i++) {
        cout << "\t\t\t\t\t\t\t\t";
        for (int j = 0; j < 8; j++) {
            cout << setw(4) << board[i][j] << " | ";
        }
        cout << endl;
        cout << "\t\t\t\t\t\t\t\t";
        for (int k = 0; k < 8; k++) {
            cout << "----";
        }
        cout << endl;
    }

    swape(board);

}

//print board function for hard board
void printBoard1(string board[][10]) {
    for (int i = 0; i < 10; i++) {
        cout << "\t\t\t\t\t\t\t\t";            //to bring Board in center 
        for (int j = 0; j < 10; j++) {
            cout << setw(4) << board[i][j] << " | ";
        }
        cout << endl;
        cout << "\t\t\t\t\t\t\t\t";
        for (int k = 0; k < 10; k++) {
            cout << "----";
        }
        cout << endl;
    }
    swaph(board);
}
//Easy Board Display
void easy_board() {
    system("cls");
    srand(time(0));
    string board[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int randomIndex;
            do {
                randomIndex = rand() % (sizeof(ch_array) / sizeof(ch_array[0]));
            } while (!isValid(board, i, j, ch_array[randomIndex]));
            board[i][j] = ch_array[randomIndex];
        }
    }

    printBoard(board);


}



// Function to check if placing a candy at a certain position is valid For hard Board
bool isValid(string board[10][10], int row, int col, string candy) {
    // Check horizontally
    int countHorizontal = 0;
    for (int i = col - consecutiveLimit; i <= col; ++i) {
        if (i >= 0 && board[row][i] == candy) {
            countHorizontal++;
        }
        else {
            break;
        }
    }
    // Check vertically
    int countVertical = 0;
    for (int i = row - consecutiveLimit; i <= row; ++i) {
        if (i >= 0 && board[i][col] == candy) {
            countVertical++;
        }
        else {
            break;
        }
    }
    // Check if candy appears on three or more consecutive blocks
    return countHorizontal < consecutiveLimit && countVertical < consecutiveLimit;
}
//Hard board
void hard_board() {
    srand(time(0));
    string board[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int randomIndex;
            do {
                randomIndex = rand() % (sizeof(ch_array_h) / sizeof(ch_array_h[0]));
            } while (!isValid(board, i, j, ch_array_h[randomIndex]));
            board[i][j] = ch_array_h[randomIndex];
        }
    }
    printBoard1(board);
}



//Display credits of Game
void credits() {
    ifstream my_input_file("Credits.txt");

    if (!my_input_file.is_open()) {
        cout << "File cannot be opened." << endl;
        return;
    }
    cout << "\n\n\n\n";
    char ch;
    while (my_input_file.get(ch)) {
        cout << "\033[33m" << ch << "\033[0m";
    }

    cout << endl;
    my_input_file.close();
}


void file_write() {
    {

        cout << name << " scored :" << score << endl;
        fstream file;/// ifstream  fin..../// ofstream out  ... fout ... fin.>> 
        file.open("Score.txt", ios::app); // fin.open//ios::in.
        file << endl;
        file << name;
        file << " ";
        file << score;
        file << endl;
        file.close();
    }
}

int main() {
    char ch = 'X';
    char exi_;
    do {
        int mode = 0, play_game = 0;
        cout << "\033[1m";
        cout << endl;
        //Display menu \033[35m" "\033[om for different colors onconsole
        //WELCOME MESSAGE
        cout << "\033[35m\t\t\t\t\t\t=======================\033[0m\n";
        cout << "\033[33m\t\t\t\t\t\tWELCOME TO CANDY CRUSH\033[0m\n";
        cout << "\033[35m\t\t\t\t\t\t=======================\033[0m\n";
        //MENU BAR
        cout << endl;
        cout << "\t\t\t\t\t\t,-----------------------,\n";
        cout << "\t\t\t\t\t\t|    1. Play Game       |\n";
        cout << "\t\t\t\t\t\t|    2. Credits         |\n";
        cout << "\t\t\t\t\t\t|    3. Instructions    |\n";
        cout << "\t\t\t\t\t\t|    4. Score section   |\n";
        cout << "\t\t\t\t\t\t|    5. Exit            |\n";
        cout << "\t\t\t\t\t\t|                       |\n";
        cout << "\t\t\t\t\t\t|    Your Choice        |\n";
        cout << "\t\t\t\t\t\t'-----------------------'\n";
        cout << "\t\t\t\t\t\t\tYour Choice: ";

        cin >> play_game;
        if (play_game == 1) {

            system("CLS");
            cout << endl << endl << endl;
            cout << "\t\t\t\t\t\t\033[36m|         PLEASE ENTER YOUR NAME:          |\033[0m" << endl;
            cout << "\033[36m\t\t\t\t\t\t          ----------------------\033[0m" << endl;
            cout << "\t\t\t\t\t\t          ";
            cout << "NAME: ";
            cin.ignore();// without this control ignores user to input his name..
            getline(cin, name); // gets input in string with spaces..

            system("cls");
            cout << endl;

            cout << "\033[1m";   //to bold output on console 
            cout << "\033[32m\t\t\t\t\t 1. Easy Mode\033[0m\n";
            cout << "\033[32m\t\t\t\t\t 2. Hard Mode\033[0m\n";
            cout << "\t\t\t\t\t ==============\n";
            cout << "\t\t\t\t\tYour Choice: ";
            cin >> mode;
            system("cls");
            if (mode == 1) {
                cout << endl;
                cout << "\033[33m\t\t\t\t\t\t\t\t\t\t EASY MODE\033[0m\n";
                cout << "\033[33m\t\t\t\t\t\t\t\t\t\t =========\033[0m\n";
                cout << "\t\t\t\t\t\t\tTime: \t\t\t\t\t\t\t Score: \n";
                cout << endl;
                cout << endl;

                easy_board();

                Sleep(6000);
                cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t " << score;
                system("cls");
                cout << endl; cout << "\033[31m\t\t\t\t\t\t\t\tTIME IS OVER...\033[0m\n\n";
                aftergame(score);
                file_write();
                cin >> ch;

            }
            else if (mode == 2) {
                cout << endl;
                cout << "\033[31m\t\t\t\t\t\t\t\t\t\t HARD MODE\033[0m\n";
                cout << "\033[31m\t\t\t\t\t\t\t\t\t\t =========\033[0m\n";
                cout << "\t\t\t\t\t\t\tTime: \t\t\t\t\t\t\t Score: \n";
                cout << endl;
                cout << endl;
                hard_board();
                Sleep(6000);
                system("cls");
                cout << endl; cout << "\033[31m\t\t\t\t\t\t\t\tTIME IS OVER...\033[0m\n\n";
                aftergame(score);
                file_write();
                cin >> ch;

            }
            cin >> ch;
        }
        // 2 will show credit of game
        else if (play_game == 2)
        {
            system("cls");
            credits();
            cin >> ch;
        }
        // 3 will show instruction by file reading
        else if (play_game == 3) {
            system("cls");
            ifstream my_input_file;
            my_input_file.open("instructions.txt");
            if (!(my_input_file.is_open()))
            {
                cout << "File cannot be opened.";
                return 0;
            }
            char ch;
            while (!my_input_file.eof())
            {
                my_input_file.get(ch); // using get() function
                if (!my_input_file.eof())
                    cout << "\033[33m" << ch << "\033[0m";
            }
            cout << endl;
            my_input_file.close();
            cin >> ch;
        }
        else if (play_game == 4) {
            system("cls");
            int score;
            string record;
            string nam;
            fstream disp;
            disp.open("Score.txt", ios::in);
            while (!disp.eof())
            {
                getline(disp, record);
                cout << endl << record;
            }
            cout << endl;
            cin >> ch;
        }
        // 5 will exit the game simply by using exit keyword
        else if (play_game == 5)
        {
            system("cls");
            cout << "\033[31m\t\t\t\t\t\t\tYou Want to Exit Game?\n\t\t\t\t\t\t\tY or y for yes\n\t\t\t\t\t\t\tb or B for NO\033[0m" << endl;
            cin >> exi_;
            if (exi_ == 'Y' || exi_ == 'y') {
                cout << "\033[33m\t\t\t\t\t\t\t You Exit Game!!\033[0m" << endl;
                Sleep(2000);
                exit(5);
            }
            else
                cin >> ch;
        }

        cout << "\033[0m";   //to bold output on console 
        cin >> ch;
        system("cls");
    } while (ch == 'B' || ch == 'b');

    system("pause");
    return 0;


}