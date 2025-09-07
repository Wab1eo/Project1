#include <curses.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define PADDLE_SIZE 3
#define p1_x 4
#define p2_x 75

void render(int p1_y, int p2_y, int ball_x, int ball_y, int p1score, int p2score);
void render_winnerp1(int p1_y, int p2_y, int ball_x, int ball_y, int p1score, int p2score);
void render_winnerp2(int p1_y, int p2_y, int ball_x, int ball_y, int p1score, int p2score);
int scoreboard_players(int *ball_x, int *ball_y, int *p1score, int *p2score, int vector);
int vector_ball(int vector, int *ball_x, int *ball_y);
int change_vector(int vector, int ball_x, int ball_y);
int change_vector_paddle(int vector, int ball_x, int ball_y, int p1_y, int p2_y);

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void game() {
    int p1_y = 11, p2_y = 11;
    int ball_x = 40, ball_y = 12;
    int vector = 4;
    int p1score = 0, p2score = 0;
    int ch;
    while (1) {
        if (p1score != 21 && p2score != 21){
            refresh();
            ch = getch();
            timeout(200);
            if (ch == 'a' || ch == 'A') {
                p1_y--;
            } else if (ch == 'z' || ch == 'Z') {
                p1_y++;
            } else if (ch == 'k' || ch == 'K') {
                p2_y--;
            } else if (ch == 'm' || ch == 'M') {
                p2_y++;
            }
            scoreboard_players(&ball_x, &ball_y, &p1score, &p2score, vector);
            vector_ball(vector, &ball_x, &ball_y);
            vector = change_vector(vector, ball_x, ball_y);
            vector = change_vector_paddle(vector, ball_x, ball_y, p1_y, p2_y);
            ball_y = clamp(ball_y, 0, 24);
            p1_y = clamp(p1_y, 0, HEIGHT - PADDLE_SIZE);
            p2_y = clamp(p2_y, 0, HEIGHT - PADDLE_SIZE);
            render(p1_y, p2_y, ball_x, ball_y, p1score, p2score);
        }
        else if (p1score == 21){
            refresh();
            ch = getch();
            timeout(118);
            if (ch == 'a' || ch == 'A') {
                p1_y--;
            } else if (ch == 'z' || ch == 'Z') {
                p1_y++;
            } else if (ch == 'k' || ch == 'K') {
                p2_y--;
            } else if (ch == 'm' || ch == 'M') {
                p2_y++;
            }
            scoreboard_players(&ball_x, &ball_y, &p1score, &p2score, vector);
            vector = 0;
            ball_y = clamp(ball_y, 0, 24);
            p1_y = clamp(p1_y, 0, HEIGHT - PADDLE_SIZE);
            p2_y = clamp(p2_y, 0, HEIGHT - PADDLE_SIZE);
            render_winnerp1(p1_y, p2_y, ball_x, ball_y, p1score, p2score);
        }
        else if (p2score == 21){
            refresh();
            ch = getch();
            timeout(118);
            if (ch == 'a' || ch == 'A') {
                p1_y--;
            } else if (ch == 'z' || ch == 'Z') {
                p1_y++;
            } else if (ch == 'k' || ch == 'K') {
                p2_y--;
            } else if (ch == 'm' || ch == 'M') {
                p2_y++;
            }
            scoreboard_players(&ball_x, &ball_y, &p1score, &p2score, vector);
            vector = 0;
            ball_y = clamp(ball_y, 0, 24);
            p1_y = clamp(p1_y, 0, HEIGHT - PADDLE_SIZE);
            p2_y = clamp(p2_y, 0, HEIGHT - PADDLE_SIZE);
            render_winnerp2(p1_y, p2_y, ball_x, ball_y, p1score, p2score);
        }
    }
}

int scoreboard_players(int *ball_x, int *ball_y, int *p1score, int *p2score, int vector){
    if(*ball_x == 1){
        (*p2score)++;
        (*ball_x) = 40;
        (*ball_y) = 12;
        return *ball_x, *ball_y;
    }
    else if (*ball_x == 79){
        (*p1score)++;
        (*ball_x) = 40;
        (*ball_y) = 12;
        return *ball_x, *ball_y;
    }
}

int change_vector(int vector, int ball_x, int ball_y){
    if (vector == 1 && ball_y == 0){
        vector = 5;
        return vector;
    }
    else if (vector == 5 && ball_y == 24){
        vector = 1;
        return vector;
    }
    else if (vector == 2 && ball_y == 0){
        vector = 4;
        return vector;
    }
    else if (vector == 4 && ball_y == 24){
        vector = 2;
        return vector;
    }
    else if (vector == 6 && ball_y == 24){
        vector = 8;
        return vector;
    }
    else if (vector == 8 && ball_y == 0){
        vector = 6;
        return vector;
    }
}

int change_vector_paddle(int vector, int ball_x, int ball_y, int p1_y, int p2_y){
    if (ball_x == p1_x + 1) {
        if (ball_y >= p1_y && ball_y < p1_y + PADDLE_SIZE) {
            if (vector == 2) vector = 8;
            if (vector == 4) vector = 6;
        }
    }
    if (ball_x == p2_x - 1) {
        if (ball_y >= p2_y && ball_y < p2_y + PADDLE_SIZE) { 
            if (vector == 8) vector = 2;
            if (vector == 6) vector = 4;
        }
    }
    if (ball_x == p1_x + 1) {
        if (ball_y >= p1_y && ball_y < p1_y + 1) {
            if (vector == 3) vector = 8;
        }
        else if (ball_y >= p1_y && ball_y < p1_y + 2){
            if (vector == 3) vector = 7;
        }
        else if (ball_y >= p1_y && ball_y < p1_y + 3){
            if (vector == 3) vector = 6;
        }
    }
    if (ball_x == p2_x - 1) {
        if (ball_y >= p2_y && ball_y < p2_y + 1) {
            if (vector == 7) vector = 2;
        }
        else if (ball_y >= p2_y && ball_y < p2_y + 2){
            if (vector == 7) vector = 3;
        }
        else if (ball_y >= p2_y && ball_y < p2_y + 3){
            if (vector == 7) vector = 4;
        }
    }
    return vector;
}

int vector_ball(int vector, int *ball_x, int *ball_y){
    if (vector == 1){
        (*ball_y)--; //Вверх
    }
    else if (vector == 2){
        (*ball_x)--; //Влево вверх
        (*ball_y)--;
    }
    else if (vector == 3){
        (*ball_x)--; //Влево
    }
    else if (vector == 4){
        (*ball_x)--; //Влево вниз
        (*ball_y)++;
    }
    else if (vector == 5){
        (*ball_y)++; //Вниз
    }
    else if (vector == 6){
        (*ball_x)++; //Вправо вниз
        (*ball_y)++;
    }
    else if (vector == 7){
        (*ball_x)++; //Вправо
    }
    else if (vector == 8){
        (*ball_x)++; //Вправо вверх
        (*ball_y)--;
    }
    else if (vector == 0){
        (*ball_x) = 40;
        (*ball_y) = 12;
    }
}

void render(int p1_y, int p2_y, int ball_x, int ball_y, int p1score, int p2score) {
    clear();
    printw("\n");
    printw("\n");
    printw("\n");
    for (int i = 0; i < WIDTH; i++) printw("_");
    printw("\n");
    printw("   Player 1: %d                                                    Player 2: %d", p1score, p2score);
    printw("\n");
    for (int i = 0; i < WIDTH; i++) printw("_");
    printw("\n");

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == p1_x && y >= p1_y && y < p1_y + PADDLE_SIZE)
                printw("|");
            else if (x == p2_x && y >= p2_y && y < p2_y + PADDLE_SIZE)
                printw("|");
            else if (x == ball_x && y == ball_y)
                printw("O");
            else
                printw(" ");
        }
        printw("\n");
    }

    for (int i = 0; i < WIDTH; i++) printw("-");
    printw("\n");
}

void render_winnerp1(int p1_y, int p2_y, int ball_x, int ball_y, int p1score, int p2score){
    clear();
    printw("\n");
    printw("\n");
    printw("\n");
    for (int i = 0; i < WIDTH; i++) printw("_");
    printw("\n");
    printw("                                 PLAYER 1 WON!                          ");
    printw("\n");
    for (int i = 0; i < WIDTH; i++) printw("_");
    printw("\n");

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == p1_x && y >= p1_y && y < p1_y + PADDLE_SIZE)
                printw("|");
            else if (x == p2_x && y >= p2_y && y < p2_y + PADDLE_SIZE)
                printw("|");
            else if (x == ball_x && y == ball_y)
                printw(" ");
            else
                printw(" ");
        }
        printw("\n");
    }

    for (int i = 0; i < WIDTH; i++) printw("-");
    printw("\n");
}

void render_winnerp2(int p1_y, int p2_y, int ball_x, int ball_y, int p1score, int p2score){
    clear();
    printw("\n");
    printw("\n");
    printw("\n");
    for (int i = 0; i < WIDTH; i++) printw("_");
    printw("\n");
    printw("                                 PLAYER 2 WON!                          ");
    printw("\n");
    for (int i = 0; i < WIDTH; i++) printw("_");
    printw("\n");

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == p1_x && y >= p1_y && y < p1_y + PADDLE_SIZE)
                printw("|");
            else if (x == p2_x && y >= p2_y && y < p2_y + PADDLE_SIZE)
                printw("|");
            else if (x == ball_x && y == ball_y)
                printw(" ");
            else
                printw(" ");
        }
        printw("\n");
    }

    for (int i = 0; i < WIDTH; i++) printw("-");
    printw("\n");
}

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    game();

    endwin();
    return 0;
}