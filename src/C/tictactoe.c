// tic tac toe between a computer or 2 people
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// global variable, need fill
const char* IP_ADDRESS = "need fill";
const int PORT = 1883;
const char* USER_NAME = "";
const int PASSWORD = 123456;

// function to display current board
void display_board(char *board) {
    int i = 0;
    for (int j = 0; j < 3; j++) {
        printf("+-----------+\n");
        for (int k = 0; k < 3; k++) {
            printf("| %c ", board[i]);
            i++;
        }
        printf("|\n");
    }
    printf("+-----------+\n");
};
// check if valid input
int input_check(int input) {
    int i;
    do {
        i = scanf("%d", &input);
        if (i != 1) {
            printf("Invalid input!\n");
            scanf("%*s");
            // clear input buffer
            while (getchar() != '\n')
                ;
        }
    } while (i != 1);
    return input;
};
// function where player enter location
void player_turn(char *board, char symbol) {
    int loc;
    do {
        printf("Enter location 1-9: ");
        loc = input_check(loc);
        if (loc > 9 || loc < 1) {
            printf("Enter limit co-ordinate.\n");
        } else if (board[loc - 1] != ' ') {
            printf("Location taken.\n");
        } else {
            char buffer[128];
            snprintf(buffer, 128, ".\\mosquitto\\mosquitto_pub.exe -h %s -p %d -u %s -P %d -t light -m %d", IP_ADDRESS, PORT, USER_NAME, PASSWORD, loc);
            int status = system(buffer);
            if (status == 1) {
                printf("Fail to send co-ordinate\n");
            }
            board[loc - 1] = symbol;
            break;
        }
    } while (1);
};
// function to check if there is a winner
int check_win(char *board, char symbol) {
    int win = 0;
    if ((board[0] == symbol && board[1] == symbol && board[2] == symbol) || (board[0] == symbol && board[4] == symbol && board[8] == symbol) || (board[0] == symbol && board[3] == symbol && board[6] == symbol) || (board[2] == symbol && board[4] == symbol && board[6] == symbol) || (board[2] == symbol && board[5] == symbol && board[8] == symbol) || (board[1] == symbol && board[4] == symbol && board[7] == symbol) || (board[3] == symbol && board[4] == symbol && board[5] == symbol) || (board[6] == symbol && board[7] == symbol && board[8] == symbol)) {
        win = 1;
    }
    return win;
};
// function let computer choose a location on the board
void computer_turn(char *board, char symbol) {
    time_t t;
    int rand_location;
    srand((unsigned)time(&t));
    do {
        rand_location = rand() % 9;
    } while (board[rand_location] != ' ');

    char buffer[128];
    snprintf(buffer, 128, ".\\mosquitto\\mosquitto_pub.exe -h %s -p %d -u %s -P %d -t light -m %d", IP_ADDRESS, PORT, USER_NAME, PASSWORD, rand_location+1);
    int status = system(buffer);
    if (status == 1) {
        printf("Fail to send co-ordinate\n");
    }
    board[rand_location] = symbol;
};
// check who's the winner based on symbol and game type
int winner(char symbol, int game_type) {
    if (game_type == 1) {
        if (symbol == 'X') {
            printf("Player 1 win!\n");
        } else {
            printf("Player 2 win!\n");
        }
    } else {
        if (symbol == 'X') {
            printf("Player win!\n");
        } else {
            printf("Computer win!\n");
        }
    }
};
// main function
int main(void) {
    int game_type = 0;
    char board[9] = {' ', ' ', ' ',
                     ' ', ' ', ' ',
                     ' ', ' ', ' '};
    printf("1) player vs. player\t2) player vs. computer\n: ");
    do {
        game_type = input_check(game_type);
        // range check
        if (game_type != 1 || game_type != 2) {
            printf("Please enter 1 or 2.\n");
            // clear input buffer
            while (getchar() != '\n')
                ;
        }
    } while (game_type < 1 || game_type > 2);
    // read input to determine which type
    int turn = 9;
    char symbol;
    // display initial board
    display_board(board);
    if (game_type == 1) {
        // loop back until board is full -> draw
        while (turn != 0) {
            if (turn % 2 == 1) {
                // symbol differenciate between 2 player
                symbol = 'X';
                printf("Player 1's turn\n");
            } else {
                symbol = 'O';
                printf("Player 2's turn\n");
            }
            // player 1 or 2 's turn based on turn number
            player_turn(board, symbol);
            // display current board
            display_board(board);
            // check win condition
            if (check_win(board, symbol) == 1) {
                break;
            }
            turn--;
        }
    } else {
        // player vs. computer
        while (turn != 0) {
            if (turn % 2 == 1) {
                symbol = 'X';
                printf("Player's turn\n");
                player_turn(board, symbol);
            } else {
                // computer turn
                symbol = 'O';
                printf("Computer's turn\n");
                computer_turn(board, symbol);
            }
            display_board(board);
            if (check_win(board, symbol) == 1) {
                break;
            }
            turn--;
        }
    }
    if (turn == 0) {
        // draw as board is full
        printf("Draw!\n");
    } else {
        // there's winnerls
        winner(symbol, game_type);
    }
    char buffer[128];
    snprintf(buffer, 128, ".\\mosquitto\\mosquitto_pub.exe -h %s -p %d -u %s -P %d -t light -m 0", IP_ADDRESS, PORT, USER_NAME, PASSWORD);
    int status = system(buffer);
    if (status == 1) {
        printf("Fail to send co-ordinate\n");
    }
    return EXIT_SUCCESS;
}
