#ifndef GAME_H
#define GAME_H

class Game
{
    public:
        static enum gameType {KOTH, CSGO};
        Game();
        void playGame(int type);
        void playKOTH();
        void playCSGO();
};

#endif
