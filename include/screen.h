// screen.h
#ifndef SCREEN_H
#define SCREEN_H

void screenInit(int borders);
void screenDestroy();
void screenClear();
void screenDrawBorders();
void screenGotoxy(int x, int y);
void screenHomeCursor();

#define MAXX 80
#define MAXY 24

#endif

