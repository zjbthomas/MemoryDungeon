#ifndef USER_H
#define USER_H

#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

class User
{
public:
    User(int mpk,int mpsp);
    ~User();
    // R/W files.
    int readFile(string, string);
    void writeFile();
    // Change the private variables.
    string getUsername();
    int getBestLevel();
    void setBsetLevel(int);
    int getSavedLevel();
    void setSavedLevel(int);
    int getGold();
    void setGold(int);
    int getAIForgetRate();
    void setAIForgetRate(int);
    // For purchased.
    bool* getOwnedK();
    void setAnOwnedK(int,bool);
    bool* getOwnedSp();
    void setAnOwnedSp(int,bool);
    bool gachaK(int, int*);
    int getCollectionRate();
    // For hero system.
    int getHero();
    void setHero(int);
private:
    // constants
    int VERSION = 1;
    // The order here is very important. It decides the order of the file R/W.
    string username = "";
    string password = "";

    int bestLevel = 0; // This is the highest level recorded.
    int savedLevel = 0;
    int gold = 0;
    int aiForgetRate = 0;
    // For purchase.
    int maxK;
    int maxSp;
    bool* ownedK;
    bool* ownedSp;
    // For hero system.
    int hero = 0;
};

#endif // USER_H
