// keyboard.c
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "keyboard.h"

void keyboardInit() {
    struct termios settings;
    tcgetattr(0, &settings);
    settings.c_lflag &= ~ICANON;
    settings.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &settings);
}

void keyboardDestroy() {
    struct termios settings;
    tcgetattr(0, &settings);
    settings.c_lflag |= ICANON;
    settings.c_lflag |= ECHO;
    tcsetattr(0, TCSANOW, &settings);
}

int keyhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

char readch() {
    return getchar();
}