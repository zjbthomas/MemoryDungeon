#ifndef ROW_H
#define ROW_H

#include <stdlib.h>
#include <time.h>

class Row
{
public:
    enum CARDSTATE {NE=-1,COVER=0,UNCOVER=1}; // NE and COVER should be different from sp.
    enum SPTYPE {REINFORCE=-2,CHAOS=-3,GOLD=-4,MAP=-5,HEAL=-6,TREASURE=-7}; // Order from worst to best.
    ~Row();
    // All the functions of this class should be only used in class gamerules.
    // Initialization.
    void init(int,bool*,bool*);
    // Generate new row.
    void newRow(int,int,int,int); // Used in a row with special card.
    void oneRandomRow(int,int*); // Used in a row without special card.
    // Change the private variables.
    int getCardState(int);
    void setCardState(int,int);
    int getCardKind(int);
    void setCardKind(int,int);
    int getSp(int);
    void setSp(int,int);
    // Other functions.
    void shuffle(int,int*);
private:
    const static int OFFSET = -2; // Here changes the first number of specail kind.

    int maxC;
    int* cardStatusArr;
    int* cardKArr; // -1 for not designed kind, 0 for special, 1 or more for normal kinds.
    int* cardSpArr;
    bool* ownedKArr;
    bool* ownedSpArr;
};

#endif // ROW_H
