#ifndef GAMERULE_H
#define GAMERULE_H

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "row.h"

class GameRule
{
public:
    // enums
    enum STATUS {EMPTY,SCORE,BONUS,CREDIT,COMBO,BREAK,AISCORE,CRITICAL};
    enum FLOORTYPE {NORMAL,CLOWN,EVIL};
    enum HEROTYPE {WIZARD=0,BERSERKER=1,HUNTER=2,MASTER=3};

    GameRule(int,int,int,int ,bool*,bool*);
    ~GameRule();
    // Start a single game.
    int newLevel();
    void newLevelByConfig(int,int,int, int);
    void normalLevelDefaultSettings();
    void start();
    // Response to GUI.
    bool isCardClickable(int);
    int getCardDisplay(int);
    int performClick(int);
    int settle(bool*,int*);
    // Change the status of cards.
    int moveCardsDownwards(); // updatenowr() will be called in this function.
    int updateCurrentR();
    bool popRow(int);
    void shuffleCards();
    // Change the private variables.
    int getEraseN();
    int getLevelKN();
    int getPopN();
    int getBaseTime();
    int getObjective();
    // Change interact variables.
    int getScore();
    int getTimeRemain();
    void setTimeRemain(int);
    int getLevel();
    void setLevel(int);
    // Functions for AI parts.
    void newAILevel(int);
    int aiAction();
    int settleAI(bool*,int*);
    bool getIsAIMode();
    bool getIsAITurn();
    int getAIScore();
    // For purchased.
    int getOwnedKN();
    // For hero system.
    int getHero();
    void setHero(int);
private:
    // Functions only avaliable in the class.
    void n2RC(int, int*, int*);
    // Constants
    const static int CRITICALRATE = 30;
    // Generate the rows.
    Row* rowArr;
    // Initiallized the game system.
    int maxR;
    int maxC;
    int maxK;
    int maxSp;
    // Initialized a single game. Used in newlevel().
    int eraseN = 2; // It control clicks how many identical cards to erase them. MUST be 2 or 3.
    int levelKN = 0; // It should not be bigger than maxk.
    int levelSpN = 0; // It should not be bigger than maxsp.
    int popN = 0;
    int baseTime = 0; // The unit is ms.
    int objective = 0;
    // Used to record and response in the game progress.
    int currentR = 0;
    int flipState = 1; // MUST be 1, 2 or 3. It represents the state that how many cards is show. 1 to trigger the GUI.
    int flip1 = -1;
    int flip2 = -1;
    int flip3 = -1;
    int cardRemain = 0; // The number of available cards left in the game.
    int match = -1;
    bool isCombo = false;
    // Variables that interact between the class and the GUI.
    int score = 0; // R only. Add score automatically.
    int timeRemain = 0; // R/W only.
    int level = 0; // R/W.
    // Variables for AI parts.
    bool isAIMode = false;
    bool isAITurn = false; // At the beginning is player's turn.
    int aiForgetRate = 100; // The maximum value is 100%.
    bool* aiMemoryArr;
    int aiFlipState = 1;
    int aiScore = 0;
    // For purchased.
    bool* ownedKArr;
    // For hero system.
    int hero = WIZARD; // WIZARD is the default hero.
};

#endif // GAMERULE_H
