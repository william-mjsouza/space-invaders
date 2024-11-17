// score.h
#ifndef SCORE_H
#define SCORE_H

void initScore();
void updateScore(int points);
void drawScore();
// Removed showFinalScore() declaration
void saveScoreToFile(const char *name, double elapsedTime);
void sortScores();

#endif
