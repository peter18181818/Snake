#include <iostream>
#include <cstdlib> // system("CLS"); rand(); srand(time(NULL));
#include <windows.h> // Sleep(500); // void cursor_return(int x, int y)
#include <conio.h> // getch();
#include "functions.h"
using namespace std;

void board_filling(int & board_width, int & board_height, char ** board, int & snake_x_coordinate, int & snake_y_coordinate, int & food_x_coordinate, int & food_y_coordinate)
{
    for (int i=0; i<board_height; i++)
    {
        for (int j=0; j<board_width; j++)
            board[j][i] = 'e'; // empty space on game board
    }

    snake_x_coordinate = rand()%(board_width-4)+1; // X coordinate of snake head drawing
    snake_y_coordinate = rand()%(board_height-4)+1; // Y coordinate of snake head drawing
    board[snake_x_coordinate][snake_y_coordinate] = 's'; // assigning a snake head to the game board

    do
    {
        food_x_coordinate = rand()%board_width; // X coordinate of food drawing
        food_y_coordinate = rand()%board_height; // Y coordinate of food drawing
        if(board[food_x_coordinate][food_y_coordinate] == 'e') // check if there is no snake on space for food
            board[food_x_coordinate][food_y_coordinate] = 'f'; // assigning food to the game board
    }
    while(board[food_x_coordinate][food_y_coordinate] != 'f');
}

void start_screen()
{
    cout << "\n\n\n\n\n\t\t ********** SNAKE *********** \n\n\n\n " << endl;
    cout << "Control: Arrow keys on keyboard" << endl;
    cout << "Pause: P key on keyboard" << endl << endl;
    cout << "Speed of the game increases every 10 points" << endl;
    cout << "You lose if snake will crash his tail or the wall" << endl << endl;

    cout << "Press Enter and start the game " << endl;
    getch();
}

void tail_deleting(int x1[], int y1[], int & counter, int & snake_x_coordinate, int & snake_y_coordinate)
{
    counter++;
    x1[counter] = snake_x_coordinate; // saving snake X coordinate in each iteration
    y1[counter] = snake_y_coordinate; // saving snake X coordinate in each iteration
}

void cursor_return(int x, int y) // this function cancel game board flickering when board is created
{                                // set cursor on the board beginning
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}

void board_drawing(int & board_width, int & board_height, char ** board, char & corner_up_left, char & corner_up_right,
                   char & corner_down_left, char & corner_down_right, char & frame_horizontal, char & frame_vertical, char & snake, char & food)
{
    cout << corner_up_left;
    for (int i=0; i<board_width; i++)
        cout << frame_horizontal << frame_horizontal; // upper frame
    cout << corner_up_right;
    for (int i=0; i<board_height; i++)
    {
        cout << endl << frame_vertical; // left frame
        for (int j=0; j<board_width; j++)
        {
            if(board[j][i] == 'e') cout << "  "; // empty space on board
            if(board[j][i] == 's') cout << snake << snake; // snake on board
            if(board[j][i] == 'f') cout << food << food; // food on board
        }
        cout << frame_vertical; // right frame
    }
    cout << endl;

    cout << corner_down_left;
    for (int i=0; i<board_width; i++)
        cout << frame_horizontal << frame_horizontal; // lower frame
    cout << corner_down_right;

}

void snake_speed(int & snake_length, int & speed) // speed is rising with snake length
{
    if (snake_length >= 10 ) speed = 75;
    if (snake_length >= 20 ) speed = 65;
    if (snake_length >= 30 ) speed = 55;
    if (snake_length >= 40 ) speed = 45;

    cout << "\n\n\n\t\t  Points (snake length): " << snake_length << endl; // showing snake length (points) on the screen
}

void snake_move(int & button, int & direction, int & snake_x_coordinate, int & snake_y_coordinate)
{
    if(kbhit()) // if any keyboard key is hit
    {
        button = getch();
        if ((button == 80) || (button == 112)) // Pause
        {
            cout << "\n\t\t      PAUSE (press P key to continue) " << endl;
            getch();
            system("CLS"); // clear screen after pause
        }
        if (button == 224)
            button += getch();
        switch(button)
        {
        case 296: // up key
            if ((button == 296) && ((direction == 3) || (direction == 4)))
            {
                direction=1;
                break;
            }
        case 304: // down key
            if ((button == 304) && ((direction == 3) || (direction == 4)))
            {
                direction=2;
                break;
            }
        case 299: // left key
            if ((button == 299) && ((direction == 1) || (direction == 2)))
            {
                direction=3;
                break;
            }
        case 301: // right key
            if ((button == 301) && ((direction == 1) || (direction == 2)))
            {
                direction=4;
                break;
            }
        };
    }

    if (direction == 1) snake_y_coordinate--; // up direction
    else if (direction == 2) snake_y_coordinate++; // down direction
    else if (direction == 3) snake_x_coordinate--; // left direction
    else if (direction == 4) snake_x_coordinate++; // right direction
}

void food_collision(int & board_width, int & board_height, char ** board, int & snake_x_coordinate, int & snake_y_coordinate,
                    int & food_x_coordinate, int & food_y_coordinate, int & snake_length, int x1[], int y1[], int & counter)
{
    if ((snake_x_coordinate == food_x_coordinate) && (snake_y_coordinate == food_y_coordinate))
    {
        snake_length++;
        do
        {
            food_x_coordinate = rand()%board_width; // X coordinate of food drawing
            food_y_coordinate = rand()%board_height; // Y coordinate of food drawing
            if(board[food_x_coordinate][food_y_coordinate] == 'e') // check if there is no snake on space for food
                board[food_x_coordinate][food_y_coordinate] = 'f'; // assigning food to the game board
        }
        while(board[food_x_coordinate][food_y_coordinate] != 'f');
    }
    else
        board[x1[counter-snake_length+1]][y1[counter-snake_length+1]] = 'e'; // snake tail clearing if there is no collision with food
}

bool wall_collision(int & snake_x_coordinate, int & snake_y_coordinate, int & board_width, int & board_height)
{
    if ((snake_x_coordinate == -1) || (snake_x_coordinate == board_width) ||
            (snake_y_coordinate == -1) || (snake_y_coordinate == board_height))
    {
        cout << "\n\t\t    Snake hit the wall" << endl << endl;
        return 1;
    }
    else
        return 0;
}

bool tail_collision(char ** board, int & snake_x_coordinate, int & snake_y_coordinate)
{
    if (board[snake_x_coordinate][snake_y_coordinate]=='s')
    {
        cout << "\n\t\t    Snake hit his tail " << endl << endl;
        return 1;
    }
    else
    {
        board[snake_x_coordinate][snake_y_coordinate] = 's'; // changing head position according to moving direction
        return 0;
    }

}
