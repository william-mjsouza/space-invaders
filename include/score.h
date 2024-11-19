// score.h
#ifndef SCORE_H
#define SCORE_H

void saveScoreToFile(const char *name, double elapsedTime);
void sortScores();
void getTopScores(char names[][30], double times[], int count);

#endif
