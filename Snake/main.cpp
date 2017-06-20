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
    int counter = 0; // liczy ile razy wykonalo sie rysowanie planszy
    int snake_lenght = 3; // przechowuje dlugosc weza
    int x1[20000], y1[20000]; // przechowuje wszystkie dotychczasowe wspolrzedne X i Y weza
    int button; // przechowuje klawisz wcisniety w celu zmiany kierunku weza
    int direction = 4; // przechowuje kierunek ruchu weza, wartosc 4 oznacza domyslny ruch w prawo
    char snake = 219; // znak do rysowania weza
    char food = 176; // znak do rysowania jedzenia
    char frame_horizontal = 205, frame_vertical = 186; // znaki do rysowania ramki
    char corner_up_right = 187, corner_up_left = 201, corner_down_right = 188, corner_down_left = 200; // znaki do rysowania rogow planszy
    int speed = 125; // przechowuje predkosc gry (zmienna do funkcji sleep())

    char ** board = new char * [board_width]; // alokacja dynamiczna tablicy (planszy)

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

         Legenda dla tablicy/planszy:
         p - puste pole;
         w - na tym polu jest snake;
         j - na tym polu jest jedzenie;
    */

    // wypelnianie planszy/tablicy - wywolanie funkcji
    board_filling(board_width, board_height, board, snake_x_coordinate, snake_y_coordinate, food_x_coordinate, food_y_coordinate);

    // komunikaty przed rozpoczeciem gry - wywolanie funkcji
    start_screen();

    system("CLS"); // czyszczenie ekranu przed rozpoczeciem gry

    //poczatek gry *******************************************************************************************************************

    for(;;) // rysowanie planszy na nowo w kazdej iteracji
    {
        // kasowanie ogona weza - wywolanie funkcji
        tail_deleting(x1,y1,counter, snake_x_coordinate, snake_y_coordinate);

        // rysowanie planszy/tablicy - wywolanie dwoch funkcji
        cursor_return(0,0); // czyszczenie ekranu bez "migania" // kursor wraca na poczatek planszy
        board_drawing(board_width, board_height, board, corner_up_left, corner_up_right, corner_down_left, corner_down_right, frame_horizontal, frame_vertical, snake, food);

        // zmiana prędkosci gry w zaleznosci od dlugosci weza - wywolanie funkcji
        snake_speed(snake_lenght, speed);

        // opoznienie (w milisekundach) sluzy do sterowania predokoscia gry
        Sleep(speed);

        // poruszanie sie weza - wywolanie funkcji
        snake_move(button, direction, snake_x_coordinate, snake_y_coordinate);

        // kolizja weza z jedzeniem
        food_collision(board_width, board_height, board, snake_x_coordinate, snake_y_coordinate, food_x_coordinate, food_y_coordinate, snake_lenght, x1, y1, counter);

        // kolizja weza ze sciana
        if (wall_collision(snake_x_coordinate, snake_y_coordinate, board_width, board_height) == 1)
            break;

        // kolizja weza z ogonem
        if (tail_collision(board, snake_x_coordinate, snake_y_coordinate) == 1)
            break;
    }

    //komunikat po zakonczeniu gry ****************************************************************************************************

    cout << "\t\t\t GAME OVER" << endl << endl;

    for (int i=0; i<board_width; i++)
        delete [] board[i];

    delete [] board; // kasowanie zaalokowanej dynamicznie tablicy (planszy)

    getch();
    return 0;
}

