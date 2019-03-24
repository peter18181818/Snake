#include <iostream>
#include <conio.h> // getch();
#include <cstdlib> // system("CLS"); rand(); srand(time(NULL));
#include <ctime> // time(NULL);
#include <windows.h> // Sleep(500); // void cursor_return(int x, int y)
#include "functions.h"
using namespace std;

int main()
{
    srand(time(NULL));

    int board_width = 20;//10;//34;
    int board_height = 20;//14;//41;
    int snake_x_coordinate, snake_y_coordinate;
    int food_x_coordinate, food_y_coordinate;
    int counter = 0; // to count how many times game board was generated
    int snake_lenght = 3;
    int x1[20000], y1[20000]; // stores all snake coordinates X and Y
    int button; // stores key pressed to change snake direction
    int direction = 4; // stores snake direction, value 4 is default right direction
    char snake = 219; // char for snake drawing
    char food = 176; // char for food drawing
    char frame_horizontal = 205, frame_vertical = 186; // char for game board frame drawing
    char corner_up_right = 187, corner_up_left = 201, corner_down_right = 188, corner_down_left = 200; // char for game board corners drawing
    int speed = 125; // stores game speed (how fast snake is moving)

    char ** board = new char * [board_width]; // dynamic allocation of game board

    for (int i=0; i<board_width; i++)
        board[i] = new char [board_height];

    /*
        {{board[0][0], board[1][0], board[2][0], ......, board[board_width][0]},
         {board[0][1], board[1][1], board[2][1], ......, board[board_width][1]},
         {board[0][2], board[1][2], board[2][2], ......, board[board_width][2]}.
         .
         .
         .
         {board[0][board_height], board[1][board_height], board[2][board_height], ......, board[board_width][board_height]}};

         Legend:
         e - empty space
         s - snake
         f - food
    */

    // filling up game board
    board_filling(board_width, board_height, board, snake_x_coordinate, snake_y_coordinate, food_x_coordinate, food_y_coordinate);

    // messages on start screen
    start_screen();

    system("CLS"); // clearing screen before game starts

    //game start *******************************************************************************************************************

    for(;;) // game board is generating in each iteration
    {
        // clearing snake tail
        tail_deleting(x1,y1,counter, snake_x_coordinate, snake_y_coordinate);

        // board drawing
        cursor_return(0,0); // screen clearing without flickering // cursor is coming back to board beginning
        board_drawing(board_width, board_height, board, corner_up_left, corner_up_right, corner_down_left, corner_down_right, frame_horizontal, frame_vertical, snake, food);

        // snake speed changes accordingly to snake length
        snake_speed(snake_lenght, speed);

        // delay (in milliseconds) to change game speed (snake speed)
        Sleep(speed);

        // snake moving
        snake_move(button, direction, snake_x_coordinate, snake_y_coordinate);

        // snake collision with food
        food_collision(board_width, board_height, board, snake_x_coordinate, snake_y_coordinate, food_x_coordinate, food_y_coordinate, snake_lenght, x1, y1, counter);

        // snake collision with wall
        if (wall_collision(snake_x_coordinate, snake_y_coordinate, board_width, board_height) == 1)
            break;

        // snake collision with tail
        if (tail_collision(board, snake_x_coordinate, snake_y_coordinate) == 1)
            break;
    }

    //messages on end screen ****************************************************************************************************

    cout << "\t\t\t GAME OVER" << endl << endl;

    for (int i=0; i<board_width; i++)
        delete [] board[i];

    delete [] board; // deleting dynamic allocated board

    getch();
    return 0;
}

