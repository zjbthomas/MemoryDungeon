#include "row.h"
#include <stdlib.h> 
#include <time.h>

// Destructor of row objects. Release heap.
row::~row()
{
	delete [] cs;
	delete [] ck;
	delete [] csp;
}

// Works as constructor of the class.
// Input: the number of cards in this row.
void row::init(int mc,bool * k,bool* sp)
{
	maxc=new int(mc);
	cs=new int[*maxc];
	ck=new int[*maxc];
	csp=new int[*maxc];
	for (int i=0;i<*maxc;i++)
	{
		cs[i]=NE;
		ck[i]=-1;
		csp[i]=0;
	}
	pk=k;
	psp=sp;
}

// Generate a row of cards with a hint card.
// Input: how many kinds to generate and what is the rule.
// Call: rand().
void row::newrow(int mk, int kn,int rulen,int spn)
{
	// Here changes the first number of specail kind.
	int offset=-2;
	// First decide what and where is the special card.
	int spp=rand()%(*maxc);
	// Check whether it is purchased.
	int temp=rand()%spn-spn+offset+1;
	while (psp[-temp+offset]==false)
		temp=rand()%spn-spn+offset+1;
	csp[spp]=temp;
	ck[spp]=0;
	// Generate each kind has how many cards in this row.
	int num=*maxc-1; // Minus the special card.
	// Calculate purchased card kinds.
	int pknum=0,pklast=0;
	for (int i=0;i<mk;i++)
	{
		if (pk[i]==true)
		{
			pknum++;
		}
		if (pknum==kn)
		{
			pklast=i;
			break;
		}
	}
	int * record=new int[pklast+1];
	for (int i=0;i<pklast;i++)
	{
		if (pk[i]==true)
		{
			int temp=(*maxc-1)/rulen/kn+rand()%2;  // This gives the number of pairs of one kind of cards.
			while ((rulen*temp)>num)
				temp=(*maxc-1)/rulen/kn+rand()%2;
			record[i]=rulen*temp;
			num-=record[i];
		}
		else
		{
			record[i]=0;
		}
	}
	record[pklast]=num;
	for (int i=0;i<*maxc;i++)
	{
		if (i!=spp)
		{
			int temp=rand()%(pklast+1)+1;
			while (record[temp-1]<=0)
				temp=rand()%(pklast+1)+1;
			ck[i]=temp;
			record[temp-1]--;
		}
	}
	delete [] record;
}

// To randomly generate a row of cards. Used at the start of a game. Should follow row::start().
// Input: number of kinds, a pointer to link the row in order to make sure the numbers of each kind are even.
void row::random(int pklast,int * record)
{
	for (int i=0;i<*maxc;i++)
	{
		int temp=rand()%(pklast+1)+1;
		while (record[temp-1]<=0)
			temp=rand()%(pklast+1)+1;
		ck[i]=temp;
		record[temp-1]--;
	}
}

// Get the state of a single card.
// Input: the index of a card.
// Ouput: the state of that card.
int row::getstate(int cn)
{
	return cs[cn];
}

// Set the state of a single card.
// Input: the index of a card and the expected state.
void row::setstate(int cn,int s)
{
	cs[cn]=s;
}

// Get the kind of a single card.
// Input: the index of a card.
// Ouput: the kind of that card.
int row::getkind(int cn)
{
	return ck[cn];
}

// Set the kind of a single card. Usually used in initialization.
// Input: the index of a card and the expected kind.
void row::setkind(int cn, int k)
{
	ck[cn]=k;
}

// Return the special kind.
// Output: the special kind.
int row::getsp(int cn)
{
	return csp[cn];
}

// Set the special kind.
// Input: the index of a card and the expected special kind.
void row::setsp(int cn,int p)
{
	csp[cn]=p;
}

// When there is a "chaos" operation, use this random function.
// Input: number of kinds, a pointer to link the row in order to make sure the numbers of each kind are even.
void row::chaosrand(int mk,int* record)
{
	for (int i=0;i<*maxc;i++)
	{
		if ((cs[i]!=NE)&&(ck[i]!=0))
		{
			int temp=rand()%mk+1;
			while (record[temp-1]<=0)
				temp=rand()%mk+1;
			ck[i]=temp;
			record[temp-1]--;
		}
	}
}