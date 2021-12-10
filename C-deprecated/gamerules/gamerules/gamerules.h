#ifndef GAMERULES_H
#define GAMERULES_H

#include "row.h"

class gamerules
{
public:
	enum condition {NULL,SCORE,BONUS,CREDIT,COMBO,BREAK,AISCORE,CRITICAL};
	enum floor {NORMAL,CLOWN,EVIL};
	enum herotype {WIZARD=0,BERSERKER=1,HUNTER=2,MASTER=3};
	gamerules(int mr,int mc,int mk,int msp,bool * pk,bool * psp);
	~gamerules();
	// Start a single game.
	int newlevel();
	void newlevel(int rule,int kind,int startr, int pop);
	void start();
	// Response to GUI.
	bool clickable(int);
	int getp(int);
	int response(int);
	int closing(bool *f,int *cond);
	// Change the status of cards.
	int downwards(); // updatenowr() will be called in this function.
	int updatenowr();
	bool poprow(int);
	void gamechaos();
	// Change the private variables.
	int getrulen();
	int getkn();
	int getpopn();
	int getbasetime();
	int gettarget();
	// Change interact variables.
	int getscore();
	int gettimeleft();
	void settimeleft(int);
	int getlevel();
	void setlevel(int);
	// Functions for AI parts.
	void AIlevel(int);
	int AIclick();
	int AIclosing(bool *f,int *cond);
	bool getAImode();
	bool getAI();
	int getAIscore();
	// For purchased.
	int getpk();
	// For hero system.
	int gethero();
	void sethero(int);
private:
	// Functions only avaliable in the class.
	void cotransf(int,int*,int*);
	// Generate the rows.
	row * r;
	// Initiallized the game system.
	int * maxr;
	int * maxc;
	int * maxk;
	int * maxsp;
	// Initialized a single game. Used in newlevel().
	int * rulen; // It control clicks how many identical cards to erase them. MUST be 2 or 3.
	int * kn; // It should not be bigger than maxk.
	int * spn; // It should not be bigger than maxsp.
	int * popn;
	int * basetime; // The unit is ms.
	int * target;
	// Used to record and response in the game progress.
	int * nowr;
	int * half; // MUST be 1, 2 or 3. It represents the state that how many cards is show. 1 to trigger the GUI.
	int * n1;
	int * n2;
	int * n3;
	int * left; // The number of available cards left in the game.
	int * match;
	bool * combo;
	// Variables that interact between the class and the GUI.
	int * score; // R only. Add score automatically.
	int * timeleft; // R/W only.
	int * level; // R/W.
	// Variables for AI parts.
	bool * AImode;
	bool * AI;
	int * AIfp;
	bool * AIr;
	int * AIhalf;
	int * AIscore;
	// For purchased.
	bool * pk;
	// For hero system.
	int * hero;
};

#endif