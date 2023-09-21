#include "userlogin.h"
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int version=1; // Here sets the version of the user profile.

// The constructor of the class.
userlogin::userlogin(int mpk,int mpsp)
{
	srand((unsigned)time(NULL));
	username=new char[20];
	strcpy(username,"");
	password=new char[20];
	strcpy(password,"");
	level=new int(0); // The first level is 0.
	save=new int(0); // The first level is 0.
	credit=new int(0);
	AIrp=new int(0);
	// For purchase.
	maxpk=new int(mpk);
	maxpsp=new int(mpsp);
	pk=new bool[*maxpk];
	for (int i=0;i<*maxpk;i++)
		pk[i]=false;
	psp=new bool[*maxpsp];
	for (int i=0;i<*maxpsp;i++)
		psp[i]=false;
	// For hero system.
	hero=new int(0);
}

// The destructor of the class. Release heap.
userlogin::~userlogin()
{
	delete [] username;
	delete [] password;
	delete level;
	delete save;
	delete credit;
	delete AIrp;
	delete maxpk;
	delete maxpsp;
	delete [] pk;
	delete [] psp;
	delete hero;
}

// Read file if it is existed.
// Input: input a name and a password.
// Output: if there isn't the file, output -1; If the password is wrong, output -2; otherwise, output 0.
// Call: ifstream::close, strcpy(), strcmp(), ifstream::getline(), atoi().
int userlogin::readfile(char * inname,char * inpw)
{
	strcpy(username,inname);
	ifstream fin(username);
	// First check whether the file is exist or not.
	if (!fin)
	{
		strcpy(password,inpw);
		fin.close();
		return -1;
	}
	char getnum[20];
	// Check the version of the profile
	fin.getline(getnum,20);
	int fversion=atoi(getnum);
	if (fversion!=version)
	{
		// If the version is not the same, works as if no profile exist.
		strcpy(password,inpw);
		fin.close();
		return -1;
	}

	fin.getline(password,20);
	if (strcmp(password,inpw)!=0)
	{
		fin.close();
		return -2;
	}
	fin.getline(getnum,20);
	*level=atoi(getnum);
	fin.getline(getnum,20);
	*save=atoi(getnum);
	fin.getline(getnum,20);
	*credit=atoi(getnum);
	fin.getline(getnum,20);
	*AIrp=atoi(getnum);
	fin.getline(getnum,20);
	*hero=atoi(getnum);
	for (int i=0;i<*maxpk;i++)
	{
		char temp;
		fin.get(temp);
		pk[i]=atoi(&temp);
	}
	fin.getline(getnum,20);
	for (int i=0;i<*maxpsp;i++)
	{
		char temp;
		fin.get(temp);
		psp[i]=atoi(&temp);
	}
	fin.getline(getnum,20);
	fin.close();
	return 0;
}

// Write the record to a file.
// Input: the new score.
// Call: ifstream::close.
void userlogin::writefile()
{
	ofstream fout(username);
	fout << version << endl;
	fout << password << endl;
	fout << *level<<endl;
	fout << *save<<endl;
	fout<< *credit<<endl;
	fout << *AIrp<<endl;
	fout << *hero<<endl;
	for (int i=0;i<*maxpk;i++)
	{
		fout << pk[i];
	}
	fout << endl;
	for (int i=0;i<*maxpsp;i++)
	{
		fout << psp[i];
	}
	fout << endl;
	fout.close();
}

// Get the username.
// Output: the pointer pointed to the username.
char * userlogin::getusername()
{
	return username;
}

// Get the level.
// Output: the level.
int userlogin::getlevel()
{
	return *level;
}

// Set the level.
// Input: the expected level.
void userlogin::setlevel(int l)
{
	*level=l;
}

// Get saved level.
// Output: the saved level number.
int userlogin::getsave()
{
	return *save;
}

// Set saved level.
// Input: the expected level to be saved.
void userlogin::setsave(int s)
{
	*save=s;
}
// Get the credit.
// Output: the current credit.
int userlogin::getcredit()
{
	return *credit;
}

// Set the credit.
// Input: the expected credit.
void userlogin::setcredit(int c)
{
	*credit=c;
}

// Get the remember percentage of AI.
// Output: the current remember percentage of AI.
int userlogin::getAIrp()
{
	return *AIrp;
}

// Set the remember percentage of AI.
// Input: the remember percentage of AI..
void userlogin::setAIrp(int r)
{
	*AIrp=r;
}

// Get purchased kind of the user.
// Output: the pointer pointed to the array that store what user purchased.
bool * userlogin::getpk()
{
	return pk;
}

// Set what kind user purchased.
// Input: The index represents the expected kind and the expected boolean value.
void userlogin::setpk(int i,bool p)
{
	pk[i]=p;
}

// Get purchased special kind of the user.
// Output: the pointer pointed to the array that store what user purchased.
bool * userlogin::getpsp()
{
	return psp;
}

// Set what special kind user purchased.
// Input: The index represents the expected kind and the expected boolean value.
void userlogin::setpsp(int i,bool p)
{
	psp[i]=p;
}

// Use to generate what user purchased and update its information.
// Input: a pointer used to communicate with GUI.
// Output: whether the user gets a new kind or an old one.
bool userlogin::randompk(int * pass)
{
	// First substract the credit.
	*credit-=*pass;
	// Then generate a random card.
	int temp=rand()%(*maxpk);
	*pass=temp+1;
	if (pk[temp]==true)
	{
		(*credit)++;
		writefile();
		return false;
	}
	else
	{
		pk[temp]=true;
		writefile();
		return true;
	}
}

// Calculate the rate that user collected.
// Output: the rate times 100.
int userlogin::getrate()
{
	int owned=0;
	for (int i=0;i<*maxpk;i++)
	{
		if (pk[i]==true)
			owned++;
	}
	for (int i=0;i<*maxpsp;i++)
	{
		if (psp[i]==true)
			owned++;
	}
	return (int)((float)owned/(*maxpk+*maxpsp)*100.0);
}

// Get the current hero.
// Output: the current hero,
int userlogin::gethero()
{
	return *hero;
}

// Set the current hero.
// Input: the expected hero.
void userlogin::sethero(int h)
{
	*hero=h;
}