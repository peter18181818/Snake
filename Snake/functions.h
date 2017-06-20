#ifndef functions_h
#define functions_h
using namespace std;


void board_filling(int & board_width, int & board_height, char ** board, int & snake_x_coordinate, int & snake_y_coordinate, int & food_x_coordinate, int & food_y_coordinate);

void start_screen();

void tail_deleting(int x1[], int y1[], int & counter, int & snake_x_coordinate, int & snake_y_coordinate);

void cursor_return(int x, int y);

void board_drawing(int & board_width, int & board_height, char ** board, char & corner_up_left, char & corner_up_right,
                   char & corner_down_left, char & corner_down_right, char & frame_horizontal, char & frame_vertical, char & snake, char & food);

void snake_speed(int & snake_lenght, int & speed);

void snake_move(int & button, int & direction, int & snake_x_coordinate, int & snake_y_coordinate);

void food_collision(int & board_width, int & board_height, char ** board, int & snake_x_coordinate, int & snake_y_coordinate,
                    int & food_x_coordinate, int & food_y_coordinate, int & snake_lenght, int x1[], int y1[], int & counter);

bool wall_collision(int & snake_x_coordinate, int & snake_y_coordinate, int & board_width, int & board_height);

bool tail_collision(char ** board, int & snake_x_coordinate, int & snake_y_coordinate);


#endif // functions_h
