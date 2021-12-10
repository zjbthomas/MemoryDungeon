class userlogin
{
public:
	userlogin(int mpk,int mpsp);
	~userlogin();
	// R/W files.
	int readfile(char *inname,char *inpw);
	void writefile();
	// Change the private variables.
	char * getusername();
	int getlevel();
	void setlevel(int);
	int getsave();
	void setsave(int);
	int getcredit();
	void setcredit(int);
	int getAIrp();
	void setAIrp(int);
	// For purchased.
	bool * getpk();
	void setpk(int,bool);
	bool * getpsp();
	void setpsp(int,bool);
	bool randompk(int*);
	int getrate();
	// For hero system.
	int gethero();
	void sethero(int);
private:
	// The order here is very important. It decides the order of the file R/W.
	char * username;
	char * password;
	int * level; // This is the highest level recorded.
	int * save;
	int * credit;
	int * AIrp;	
	// For purchase.
	int * maxpk;
	int * maxpsp;
	bool * pk;
	bool * psp;
	// For hero system.
	int * hero;
};