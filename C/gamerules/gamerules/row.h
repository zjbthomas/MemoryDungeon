class row
{
public:
	enum state {NE=-1,COVER=0,UNCOVER=1}; // NE and COVER should be different from sp.
	enum sp {FORCE=-2,CHAOS=-3,CREDIT=-4,MATCH=-5,TIME=-6,GIFT=-7}; // Order from worst to best.
	~row();
	// All the functions of this class should be only used in class gamerules.
	// Initialization.
	void init(int,bool*,bool*);
	// Generate new row.
	void newrow(int,int,int,int); // Used in a row with special card.
	void random(int,int*); // Used in a row without special card.
	// Change the private variables.
	int getstate(int);
	void setstate(int,int);
	int getkind(int);
	void setkind(int,int);
	int getsp(int);
	void setsp(int,int);
	// Other functions.
	void chaosrand(int,int*);
private:
	int * maxc;
	int * cs;
	int * ck; // -1 for not designed kind, 0 for special, 1 or more for normal kinds.
	int * csp;
	bool * pk;
	bool * psp;
};