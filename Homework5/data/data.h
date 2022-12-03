#ifndef _DATA_
#define _DATA_
struct systemData{
    short int difficulty = 0;
    short int lcdContrast = 0;
    short int lcdBrightness = 0;
    short int matrixBrightness = 0;
};
struct dataPlayer{
    char name[3] = "AAA";
    short int score = 0;
};

static systemData systemData; // 8 bytes (evaluated with sizeof)

static dataPlayer Player;

static dataPlayer dataHighscores[3]; // highscores of players
                                        // 12 bytes (evaluated with sizeof)

#endif