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
            board[j][i] = 'p'; // puste pola
    }

    snake_x_coordinate = rand()%(board_width-4)+1; // losowanie wspolrzedniej X glowy weza // lub rand()%((board_width-5)-0+1)+0
    snake_y_coordinate = rand()%(board_height-4)+1; // losowanie wspolrzedniej Y glowy weza
    board[snake_x_coordinate][snake_y_coordinate] = 'w'; // przypisanie glowy weza do pola planszy

    do
    {
        food_x_coordinate = rand()%board_width; // losowanie wspolrzedniej X jedzenia // lub rand()%((board_width-1)-0+1)+0
        food_y_coordinate = rand()%board_height; // losowanie wspolrzedniej Y jedzenia
        if(board[food_x_coordinate][food_y_coordinate] == 'p') // sprawdzenie czy wylosowane dla jedzenia pole jest puste/nie zajete przez weza
            board[food_x_coordinate][food_y_coordinate] = 'j'; // przypisanie jedzenia do pola planszy
    }
    while(board[food_x_coordinate][food_y_coordinate] != 'j');
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
    x1[counter] = snake_x_coordinate; // zapisanie informacji w jakim polu znajdowala sie glowa weza w kazdej iteracji
    y1[counter] = snake_y_coordinate; // zapisanie informacji w jakim polu znajdowala sie glowa weza w kazdej iteracji
}

void cursor_return(int x, int y) // ta funkcja niweluje miganie ekranu przy rysowaniu planszy
{                                // kursor wraca do poczatku planszy
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
    cout << corner_up_left; // lewy gorny rog
    for (int i=0; i<board_width; i++)
        cout << frame_horizontal << frame_horizontal; // gorna ramka
    cout << corner_up_right; // prawy gorny rog

    for (int i=0; i<board_height; i++)
    {
        cout << endl << frame_vertical; // lewa ramka
        for (int j=0; j<board_width; j++)
        {
            if(board[j][i] == 'p') cout << "  "; // puste pola
            if(board[j][i] == 'w') cout << snake << snake; // waz
            if(board[j][i] == 'j') cout << food << food; // jedzenie
        }
        cout << frame_vertical; // prawa ramka
    }
    cout << endl;

    cout << corner_down_left; // lewy dolny rog
    for (int i=0; i<board_width; i++)
        cout << frame_horizontal << frame_horizontal; // dolna ramka
    cout << corner_down_right; // prawy dolny rog

}

void snake_speed(int & snake_lenght, int & speed)
{
    if (snake_lenght >= 10 ) speed = 75;
    if (snake_lenght >= 20 ) speed = 65;
    if (snake_lenght >= 30 ) speed = 55;
    if (snake_lenght >= 40 ) speed = 45;

    cout << "\n\n\n\t\t  Points (snake length): " << snake_lenght << endl; // wypisuje dlugosc weza(punkty) na ekran
}

void snake_move(int & button, int & direction, int & snake_x_coordinate, int & snake_y_coordinate)
{
    if(kbhit()) // jesli zostanie wcisniety klawisz na klawiaturze
    {
        button = getch();
        if ((button == 80) || (button == 112)) // Pauza
        {
            cout << "\n\t\t      PAUSE (press P key to continue) " << endl;
            getch();
            system("CLS"); // czyszczenie ekranu po zakonczeniu pauzy
        }
        if (button == 224)
            button += getch();
        switch(button)
        {
        case 296: // klawisz strzalka w gore
            if ((button == 296) && ((direction == 3) || (direction == 4)))
            {
                direction=1;
                break;
            }
        case 304: // kalwisz strzalka w dol
            if ((button == 304) && ((direction == 3) || (direction == 4)))
            {
                direction=2;
                break;
            }
        case 299: // klawisz strzalka w lewo
            if ((button == 299) && ((direction == 1) || (direction == 2)))
            {
                direction=3;
                break;
            }
        case 301: // klawisz strzalka w prawo
            if ((button == 301) && ((direction == 1) || (direction == 2)))
            {
                direction=4;
                break;
            }
        };
    }

    if (direction == 1) snake_y_coordinate--; // ruch w gore
    else if (direction == 2) snake_y_coordinate++; // ruch w dol
    else if (direction == 3) snake_x_coordinate--; // ruch w lewo
    else if (direction == 4) snake_x_coordinate++; // ruch w prawo
}

void food_collision(int & board_width, int & board_height, char ** board, int & snake_x_coordinate, int & snake_y_coordinate,
                    int & food_x_coordinate, int & food_y_coordinate, int & snake_lenght, int x1[], int y1[], int & counter)
{
    if ((snake_x_coordinate == food_x_coordinate) && (snake_y_coordinate == food_y_coordinate))
    {
        snake_lenght++;
        do
        {
            food_x_coordinate = rand()%board_width; // losowanie wspolrzedniej X jedzenia // lub rand()%((board_width-1)-0+1)+0
            food_y_coordinate = rand()%board_height; // losowanie wspolrzedniej Y jedzenia
            if(board[food_x_coordinate][food_y_coordinate] == 'p') // sprawdzenie czy wylosowane dla jedzenia pole jest puste/nie zajete przez weza
                board[food_x_coordinate][food_y_coordinate] = 'j'; // przypisanie jedzenia do pola planszy
        }
        while(board[food_x_coordinate][food_y_coordinate] != 'j');
    }
    else
        board[x1[counter-snake_lenght+1]][y1[counter-snake_lenght+1]] = 'p'; //kasowanie ogona jesli nie ma kolizji z jedzeniem
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
    if (board[snake_x_coordinate][snake_y_coordinate]=='w')
    {
        cout << "\n\t\t    Snake hit his tail " << endl << endl;
        return 1;
    }
    else
    {
        board[snake_x_coordinate][snake_y_coordinate] = 'w'; // zmiana polozenia glowy weza w zaleznosci od kierunku ruchu
        return 0;
    }

}
