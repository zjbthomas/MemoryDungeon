#include "gamerules.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>


// Constructor of the class.
// Input: the maximum numbers of rows and cards (in each row), a base time.
// Call: row::init();
gamerules::gamerules(int mr,int mc,int mk,int msp,bool *k, bool *sp)
{
	srand((unsigned)time(NULL));
	maxr=new int(mr);
	r=new row[*maxr];
	maxc=new int(mc);
	for (int i=0;i<*maxr;i++)
		r[i].init(*maxc,k,sp);
	maxk=new int(mk);
	maxsp=new int(msp);
	pk=k;

	nowr=new int(0);
	score=new int(0);
	half=new int(1);
	n1=new int(-1);
	n2=new int(-1);
	n3=new int(-1);
	basetime=new int(0);
	timeleft=new int(0);
	left=new int(0);
	level=new int(0);
	kn=new int(0);
	spn=new int(0);
	rulen=new int(2);
	popn=new int(0);
	target=new int(0);
	combo=new bool(false);
	// Variables for AI parts.
	AImode=new bool(false);
	AI=new bool(false); // At the beginning is player's turn.
	AIfp=new int(100); // The maximum value is 100%.
	AIr=new bool[(*maxr)*(*maxc)];
	for (int i=0;i<(*maxr)*(*maxc);i++)
		AIr[i]=false;
	AIhalf=new int(1);
	AIscore=new int(0);
	match=new int(-1);
	// For hero system.
	hero=new int(WIZARD); // WIZARD is the default hero.
}

// Destructor of the class. Release heap.
gamerules::~gamerules()
{
	delete maxr;
	delete maxc;
	delete maxk;
	delete maxsp;
	delete [] r;
	delete nowr;
	delete score;
	delete half;
	delete n1;
	delete n2;
	delete n3;
	delete basetime;
	delete timeleft;
	delete left;
	delete level;
	delete kn;
	delete spn;
	delete rulen;
	delete popn;
	delete target;
	delete combo;
	// Variables for AI parts.
	delete AImode;
	delete AI;
	delete AIfp;
	delete [] AIr;
	delete AIhalf;
	delete AIscore;
	delete match;
	delete hero;
}

// Generate a new level.
// Output: the kind of the generated level.
int gamerules::newlevel()
{
	int rt=NORMAL;
	*AImode=false;
	(*level)++;
	int pknum=0;
	int ltime=0;
	if (*level%10==0) // It is a Evil Level.
	{
		*rulen=3;
		// Generate the kind of card.
		for (int i=0;i<*maxk;i++)
		{
			if (pk[i]==true)
				pknum++;
		}
		*kn=pknum;
		*spn=2;
		*nowr=4;
		*popn=2;
		// Calculate the time.
		ltime=100; // Here sets the lowest time.
		*basetime=ltime+50*(*rulen-2)+10*(*kn-2)+50*(*popn-1)-2*(*level-1);
		if (*basetime<ltime)
			*basetime=ltime;
		*timeleft=*basetime;
		// Calculte the target points.
		*target=20+3*(*level-1);
		rt=EVIL;
	}
	else if (*level%5==0) // It is a Clown Level.
	{
		*rulen=2;
		// Generate the kind of card.
		for (int i=0;i<*maxk;i++)
		{
			if (pk[i]==true)
				pknum++;
		}
		*kn=pknum;
		*spn=3;
		*nowr=3;
		*popn=1;
		// Calculate the time.
		ltime=100; // Here sets the lowest time.
		*basetime=ltime+50*(*rulen-2)+15*(*kn-2)+50*(*popn-1)-2*(*level-1);
		if (*basetime<ltime)
			*basetime=ltime;
		*timeleft=*basetime;
		// Calculte the target points.
		*target=20+3*(*level-1);
		rt=CLOWN;
	}
	else // It is a normal Level.
	{
		// Generate the game rule.
		*rulen=2+rand()%7*0.2; // About 83% is 2.
		// Generate the kind of card.
		pknum=0;
		for (int i=0;i<*maxk;i++)
		{
			if (pk[i]==true)
				pknum++;
		}
		*kn=2+rand()%(pknum-1);
		// Generate the kind of spcial card.
		*spn=*maxsp;
		// Generate beginning number of rows.
		*nowr=2+rand()%(*maxr-3);
		// Generate how many rows will be popped in one time.
		*popn=1+rand()%7*0.2; // About 83% is 1.
		// Calculate the time.
		ltime=120; // Here sets the lowest time.
		*basetime=ltime+50*(*rulen-2)+20*(*kn-2)+50*(*popn-1)-2*(*level-1);
		if (*basetime<ltime)
			*basetime=ltime;
		*timeleft=*basetime;
		// Calculte the target points.
		*target=20-5*(*rulen-2)+3*(*level-1)-2*(*nowr-2);
		rt=NORMAL;
	}

	// For MASTER
	if (*hero==MASTER)
		*timeleft+=30;

	*score=0;
	*combo=false;
	start();
	return rt;
}

// Generate a new level by pre-set conditions.
// Input: all kinds of conditions.
void gamerules::newlevel(int rule,int kind,int startr, int pop)
{
	*AImode=false;
	(*level)++;
	// Four variables that can be changed by user.
	*rulen=rule;
	*kn=kind;
	*nowr=startr;
	*popn=pop;
	// Other variables generated directly by system.
	*spn=*maxsp;
	// Calculate the time.
	int ltime=120; // Here sets the lowest time.
	*basetime=ltime+50*(*rulen-2)+20*(*kn-2)+50*(*popn-1)-2*(*level-1);
	if (*basetime<ltime)
		*basetime=ltime;
	*timeleft=*basetime;

	// For MASTER
	if (*hero==MASTER)
		*timeleft+=30;

	// Calculte the target points.
	*target=20-5*(*rulen-2)+3*(*level-1)-2*(*nowr-2);
	*score=0;
	*combo=false;
	start();
}

// Start a new game.
// Input: number of rows at the beginning, how many kinds should be generated and what's the rule.
// Call: row::setstate(), row::random(), row::start(), row::newrow().
void gamerules::start()
{
	for (int i=0;i<*maxr;i++)
	{
		for (int j=0;j<*maxc;j++)
			r[i].setstate(j,row::NE);
	}
	*left=0;
	int temp=*nowr;
	*nowr=0;
	poprow(temp);
	*nowr=temp;
	gamechaos();
	(*half)=1;
	(*AIhalf)=1;
	
}

// Response whether a card is clickable or not.
// Input: the index of a card (need to be decoded).
// Output: Whether it is clickable or not.
bool gamerules::clickable(int n)
{
	int sr,sc;
	cotransf(n,&sr,&sc);
	if ((r[sr].getkind(sc)==0)||(r[sr].getstate(sc)==row::COVER))
		return true;
	else if ((*half==2)&&(n==*n1))
		return true;
	else
		return false;
}

// Get the state of kind of one card.
// Input: the index of a card (need to be decoded).
// Output: If it's a EXISTED special card, return the kind of special card, if it's not uncovered, return state, Otherwise, return kind.
// Call: cotransf(), row::getkind(), row::getstate().
int gamerules::getp(int n)
{
	int sr,sc;
	cotransf(n,&sr,&sc);
	if (r[sr].getkind(sc)==0)
	{
		// Make TIME of MASTER become visible.
		if ((*hero==MASTER)&&(r[sr].getsp(sc)==row::TIME)&&(r[sr].getstate(sc)!=row::NE))
		{
			r[sr].setstate(sc,row::UNCOVER);
			return r[sr].getsp(sc);
		}
		if (r[sr].getstate(sc)==row::UNCOVER)
			return r[sr].getsp(sc);
		else
			return r[sr].getstate(sc);
	}
	if (r[sr].getstate(sc)!=row::UNCOVER)
		return r[sr].getstate(sc);
	else
		return r[sr].getkind(sc);
}

// Response to a click.
// Input: the index of a card (need to be decoded).
// Output: If a special card is clicked, return the kind of that card; Otherwise, return whether a single card or a pair of cards is clicked.
// Call: cotransf(), row::getkind(), row::getstate(), row::setstate().
int gamerules::response(int n)
{
	int sr,sc;
	cotransf(n,&sr,&sc);
	 // If it is a special card.
	if (r[sr].getkind(sc)==0)
	{
		// If a single/double card had been clicked, cover it/them.
		int tr,tc;
		switch (*half)
		{
		case 2:
			cotransf(*n1,&tr,&tc);
			r[tr].setstate(tc,row::COVER);
			break;
		case 3:
			cotransf(*n1,&tr,&tc);
			r[tr].setstate(tc,row::COVER);
			cotransf(*n2,&tr,&tc);
			r[tr].setstate(tc,row::COVER);
			break;
		}
		
		switch (r[sr].getsp(sc))
		{
		case row::FORCE:
			// Minus the score by the number of rows left.
			if (*score>=(*maxr-*nowr))
				(*score)-=(*maxr-*nowr);
			// Pop a new row and show it.
			if (*nowr<*maxr)
			{
				poprow(1);
				// Update the value of n.
				n+=*maxc;
				cotransf(n,&sr,&sc);
				for (int i=0;i<*maxc;i++)
					r[*nowr-1].setstate(i,row::UNCOVER);
			}
			break;
		case row::CHAOS:
			gamechaos();
			for (int i=0;i<*nowr;i++)
			{
				for (int j=0;j<*maxc;j++)
				{
					if (r[i].getstate(j)!=row::NE)
						r[i].setstate(j,row::UNCOVER); 
				}
			}
			break;
		case row::CREDIT:
			// The operations are done in the GUI.
			break;
		case row::MATCH:
			*match=-1;
			int mtemp;
			int ttemp;
			int htemp; htemp=-1;
			if (*hero==HUNTER)
				ttemp=2;
			else
				ttemp=1;
			for (int j=0;j<ttemp;j++)
			{
				for (int i=0;i<(*maxr)*(*maxc);i++)
				{
					cotransf(i,&tr,&tc);
					if ((r[tr].getstate(tc)!=row::NE)&&(r[tr].getkind(tc)!=0)&&(r[tr].getkind(tc)!=htemp))
					{
						r[tr].setstate(tc,row::UNCOVER);
						*match=r[tr].getkind(tc);
						mtemp=i;
						htemp=r[tr].getkind(tc);
						break;
					}
				}
				switch (*rulen)
				{
				case 3:
					for (int i=(mtemp+1);i<(*maxr)*(*maxc);i++)
					{
						cotransf(i,&tr,&tc);
						if ((r[tr].getstate(tc)!=row::NE)&&(r[tr].getkind(tc)==*match))
						{
							r[tr].setstate(tc,row::UNCOVER);
							mtemp=i;
							break;
						}
					}
				   // No break;
				case 2:
					for (int i=(mtemp+1);i<(*maxr)*(*maxc);i++)
					{
						cotransf(i,&tr,&tc);
						if ((r[tr].getstate(tc)!=row::NE)&&(r[tr].getkind(tc)==*match))
						{
							r[tr].setstate(tc,row::UNCOVER);
							break;
						}
					}
					break;
				}
			}
			break;
		case row::TIME:
			if (*hero==MASTER)
			{
				*timeleft+=*basetime/2;
				if (*timeleft>*basetime)
					*timeleft=*basetime;
			}
			else
				*timeleft=*basetime;
			break;
		case row::GIFT:
			// The operations are done in the GUI.
			break;
		}
		r[sr].setstate(sc,row::UNCOVER);
		
		*n1=n;
		*half=1;
		return r[sr].getsp(sc); // return the kind of special card.
	}
	// If it is a normal card.
	switch (*half)
	{
	case 1:
		*n1=n;
		(*half)++;
		break;
	case 2:
		*n2=n;
		if (*rulen==2)
		{
			(*half)=1;
			if (*n1==*n2)
			{
				r[sr].setstate(sc,row::COVER);
				return 0;
			}
		}
		else
		{
			int sr1,sc1,sr2,sc2;
			cotransf(*n1,&sr1,&sc1);
			cotransf(*n2,&sr2,&sc2);
			if (*n1==*n2)
			{
				r[sr].setstate(sc,row::COVER);
				(*half)=1;
				return 0;
			}
			if (r[sr1].getkind(sc1)!=r[sr2].getkind(sc2))
			{
				*n3=n;
				(*half)=1;
			}
			else
				(*half)++;
		}
		break;
	case 3:
		*n3=n;
		(*half)=1;
		break;
	}
	r[sr].setstate(sc,row::UNCOVER);
	return ((*half)==1);
}

// When a hint or a pair of cards are shown for a given time, decide what to do next. Used in the closing timer.
// Input: A pointer pointed to a boolean whether game wins or not.
// Output: The number of row is available in the game and a boolean pointer.
// Call: cotransf(), row::getkind(), row::row::getstate(), row::setstate().
int gamerules::closing(bool * f,int * cond)
{
	*cond=NULL;
	int sr1,sc1,sr2,sc2,sr3,sc3;
	cotransf(*n1,&sr1,&sc1);
	// If it is a special card.
	if (r[sr1].getkind(sc1)==0)
	{
		*cond=BONUS;
		switch (r[sr1].getsp(sc1))
		{
		case row::FORCE:
			for (int i=0;i<*maxc;i++)
				r[*nowr-1].setstate(i,row::COVER);
			(*score)--;
			*cond=BREAK;
			break;
		case row::CHAOS:
			for (int i=0;i<*nowr;i++)
			{
				for (int j=0;j<*maxc;j++)
				{
					if (r[i].getstate(j)!=row::NE)
						r[i].setstate(j,row::COVER); 
				}
			}
			break;
		case row::CREDIT:
			*cond=CREDIT;
			break;
		case row::MATCH:
			if (*match!=-1)
			{
				for (int i=0;i<(*maxr)*(*maxc);i++)
				{
					int tr,tc;
					cotransf(i,&tr,&tc);
					if ((r[tr].getstate(tc)==row::UNCOVER)&&(r[tr].getkind(tc)!=0))
					{
						r[tr].setstate(tc,row::NE);
						(*left)--;
					}
				}
			}
			break;
		case row::TIME:
			break;
		case row::GIFT:
			break;
		}
		r[sr1].setstate(sc1,row::NE);
		(*score)++;
		(*left)--;
	}
	else
	{
		cotransf(*n2,&sr2,&sc2);
		cotransf(*n3,&sr3,&sc3);
		switch (*rulen)
		{
		case 2:
			if (r[sr1].getkind(sc1)==r[sr2].getkind(sc2))
			{
				r[sr1].setstate(sc1,row::NE);
				r[sr2].setstate(sc2,row::NE);
				(*score)++;
				*cond=SCORE;
				if (*hero!=BERSERKER)
				{
					// COMBO system except BERSERKER.
					if (*combo==true)
					{
						(*score)++;
						*cond=COMBO;
					}
					else
						*combo=true;
				}
				else
				{
					// CRITICAL system for BERSERKER.
					int temp=rand()%100+1;
					if (temp<=30) // Here set the critical rate.
					{
						(*score)+=2;
						*cond=CRITICAL;
					}
				}
				(*left)-=(*rulen);
			}
			else
			{
				r[sr1].setstate(sc1,row::COVER);
				r[sr2].setstate(sc2,row::COVER);
				*combo=false;
			}
			break;
		case 3:
			if ((r[sr1].getkind(sc1)==r[sr2].getkind(sc2))&&(r[sr1].getkind(sc1)==r[sr3].getkind(sc3)))
			{
				r[sr1].setstate(sc1,row::NE);
				r[sr2].setstate(sc2,row::NE);
				r[sr3].setstate(sc3,row::NE);
				(*score)++;
				*cond=SCORE;
				if (*hero!=BERSERKER)
				{
					// COMBO system except BERSERKER.
					if (*combo==true)
					{
						(*score)++;
						*cond=COMBO;
					}
					else
						*combo=true;
				}
				else
				{
					// CRITICAL system for BERSERKER.
					int temp=rand()%100+1;
					if (temp<=30) // Here set the critical rate.
					{
						(*score)+=2;
						*cond=CRITICAL;
					}
				}
				(*left)-=(*rulen);
			}
			else
			{
				r[sr1].setstate(sc1,row::COVER);
				r[sr2].setstate(sc2,row::COVER);
				r[sr3].setstate(sc3,row::COVER);
				*combo=false;
			}
			break;
		}
	}
	downwards();
	if (*left==0)
	{
		// Pop half of maximum rows right now, and the left time will change into score.
		(*score)+=(*timeleft)/10;
		*cond=BONUS;
		poprow(*maxr/2);
		gamechaos();
	}
	if ((*score)>=(*target))
	{
		*f=true;
		for (int i=0;i<(*maxr)*(*maxc);i++)
		{
			cotransf(i,&sr1,&sc1);
			r[sr1].setstate(sc1,row::NE);
		}
	}
	else
		*f=false;
	return updatenowr();
}

// The card will move downwards if there is no card below.
int gamerules::downwards()
{
	// Notice that the row indeces in game are mirrored.
	for (int i=0;i<*nowr;i++)
	{
		for (int j=0;j<(*maxc);j++)
		{
			if (r[i].getstate(j)!=row::NE)
			{
				for (int k=i+1;k<*nowr;k++)
				{
					if (r[k].getstate(j)==row::NE)
					{
						r[k].setstate(j,r[i].getstate(j));
						r[k].setkind(j,r[i].getkind(j));
						r[k].setsp(j,r[i].getsp(j));
						r[i].setstate(j,row::NE);
						break;
					}
				}
			}
		}
	}
	return updatenowr(); // This is a MUST.
}

// Get the number of rows avaliable in the game. It will also update nowr.
// Output: the number of rows avaliable in the game. 
int gamerules::updatenowr()
{
	// Notice that the row indeces in game are mirrored.
	int emptyrow=0;
	for (int i=0;i<*nowr;i++)
	{
		for (int j=0;j<*maxc;j++)
		{
			if (r[i].getstate(j)!=row::NE)
			{
				emptyrow=i;
				i=*nowr;
				break;
			}
		}
	}
	// Move the rows to fill the empty row.
	if (emptyrow!=0)
	{
		for (int i=emptyrow;i<*nowr;i++)
		{
			for (int j=0;j<*maxc;j++)
			{
				r[i-emptyrow].setstate(j,r[i].getstate(j));
				r[i-emptyrow].setkind(j,r[i].getkind(j));
				r[i-emptyrow].setsp(j,r[i].getsp(j));
				r[i].setstate(j,row::NE);
			}
		}
	}
	(*nowr)-=emptyrow;
	return *nowr;
}

// To make a new row available in the game, and decide whether game over.
// Input: how many rows will be popped in one time.
// Output: whether game IS NOT over (or rather say, whether a new line is poped).
// Call: row::setstate().
bool gamerules::poprow(int n)
{
	if ((*nowr+n)>*maxr) // Game over.
	{
		for (int i=0;i<*maxr;i++)
		{
			for (int j=0;j<*maxc;j++)
				r[i].setstate(j,row::NE);
		}
		return false;
	}
	else
	{
		int lastr=*nowr;
		int cardnum=n*(*maxc);
		// If the number of cards is not devidable by the rule number, add special card.
		int rownum=cardnum%(*rulen);
		int random1=-1,random2=-1;
		int temp;
		switch (rownum)
		{
		case 2:
			temp=lastr+rand()%n;
			random2=temp;
			r[temp].newrow(*maxk,*kn,*rulen,*spn);
			for (int i=0;i<*maxc;i++)
				r[temp].setstate(i,row::COVER);
			(*nowr)++;
			(*n1)+=*maxc;
			(*n2)+=*maxc;
			(*n3)+=*maxc;
			(*left)+=*maxc;
		case 1:
			temp=lastr+rand()%n;
			while (temp==random2)
				temp=lastr+rand()%n;
			random1=temp;
			r[temp].newrow(*maxk,*kn,*rulen,*spn);
			for (int i=0;i<*maxc;i++)
				r[temp].setstate(i,row::COVER);
			(*nowr)++;
			(*n1)+=*maxc;
			(*n2)+=*maxc;
			(*n3)+=*maxc;
			(*left)+=*maxc;
			break;
		}
		// Generate other rows.
		rownum=n-rownum;
		cardnum=(*maxc)*(rownum);
		// Calculate purchased card kinds.
		int pknum=0,pklast=0;
		for (int i=0;i<*maxk;i++)
		{
			if (pk[i]==true)
			{
				pknum++;
			}
			if (pknum==*kn)
			{
				pklast=i;
				break;
			}
		}
		int * record=new int[pklast+1];
		for (int i=0;i<pklast;i++)
		{
			if ((pk[i]==true)&&(cardnum>=(*maxc)*(rownum)/(*kn)))
			{
				int temp=(*maxc)*(rownum)/(*rulen)/(*kn)+rand()%2;  // This gives the number of pairs of one kind of cards.
				while ((temp*(*rulen))>cardnum)
					temp=(*maxc)*(rownum)/(*rulen)/(*kn)+rand()%2;
				record[i]=temp*(*rulen);
				cardnum-=record[i];
			}
			else
			{
				record[i]=0;
			}
		}
		record[pklast]=cardnum;
		if (rownum!=0)
		{
			for (int i=0;i<n;i++)
			{
				if (((lastr+i)!=random1)&&((lastr+i)!=random2))
				{
					r[(lastr+i)].random(pklast,record);
					for (int j=0;j<*maxc;j++)
						r[(lastr+i)].setstate(j,row::COVER);
					(*nowr)++;
					(*n1)+=*maxc;
					(*n2)+=*maxc;
					(*n3)+=*maxc;
					(*left)+=*maxc;
				}
			}
		}

		(*timeleft)=(*basetime);
		return true;
	}
}

// Disorganise all existing and avaliable (NOT SPECIAL) cards in the game.
void gamerules::gamechaos()
{
	int * record=new int[*maxk];
	for (int i=0;i<*maxk;i++)
		record[i]=0;
	for (int i=0;i<*nowr;i++)
	{
		for (int j=0;j<*maxc;j++)
		{
			if ((r[i].getstate(j)!=row::NE)&&(r[i].getkind(j)!=0))
				record[r[i].getkind(j)-1]++;
		}
	}
	for (int i=0;i<*nowr;i++)
	{
		r[i].chaosrand(*maxk,record);
	}
	delete [] record;
}

// Get the rule.
// Output: the number represent the rule.
int gamerules::getrulen()
{
	return *rulen;
}

// Get how many kinds is at the game.
// Output: the current number of kinds.
int gamerules::getkn()
{
	return *kn;
}

// Get how many rows will pop when time out.
// Output: the current popn.
int gamerules::getpopn()
{
	return *popn;
}

// Get the base time.
// Output: the current basetime.
int gamerules::getbasetime()
{
	return *basetime;
}

// Get the score.
// Output: the score.
int gamerules::gettarget()
{
	return *target;
}

// Get the score.
// Output: the current score.
int gamerules::getscore()
{
	return *score;
}

// Get the left time.
// Output: the left time.
int gamerules::gettimeleft()
{
	return *timeleft;
}

// Set the left time.
// Input: which time to set.
void gamerules::settimeleft(int t)
{
	*timeleft=t;
}

// Get the level.
// Output: the current level.
int gamerules::getlevel()
{
	return *level;
}

// Set the level.
// Input: which level.
void gamerules::setlevel(int l)
{
	*level=l;
}

// Decode an index to row and column.
// Input: index and two return pointers.
void gamerules::cotransf(int n,int *sr,int *sc)
{
	*sr=n/(*maxc);
	*sc=n%(*maxc);
	if (*sr<*nowr) // Mirrored the rows which is avaliable in the game.
		*sr=*nowr-(*sr+1);
}

// Start a new AI game.
// Input: the expected forget percentage of the AI.
void gamerules::AIlevel(int fp)
{
	*AImode=true;
	// Initialize the AI system.
	*AI=false;
	*AIfp=fp;
	for (int i=0;i<(*maxr)*(*maxc);i++)
		AIr[i]=false;
	*AIscore=0;
	// Start a new game.
	*rulen=2;
	int pknum=0;
	for (int i=0;i<*maxk;i++)
	{
		if (pk[i]==true)
			pknum++;
	}
	*kn=pknum;
	*spn=0;
	*nowr=*maxr;
	*score=0;
	start();
}

// Do an AI click action.
// Output: the index number of the progress.
int gamerules::AIclick()
{
	int sr,sc;
	// First the AI will forget some EXISTED cards if it is its first click.
	// Change the forget percentage into an effective one.
	int efp;
	int rcard=0;
	for (int i=0;i<(*maxr)*(*maxc);i++)
	{
		cotransf(i,&sr,&sc);
		if ((AIr[i]==true)&&(r[sr].getstate(sc)!=row::NE))
			rcard++;
	}
	if (rcard==0)
		efp=*AIfp;
	else
		efp=100-pow((float)(100-(*AIfp))/100.0,1.0/(float)rcard)*100;

	int * record=new int[*maxk]; // It is used to record the kind that the AI remember.
	for (int i=0;i<*maxk;i++)
		record[i]=0;
	for (int i=0;i<(*maxr)*(*maxc);i++)
	{
		cotransf(i,&sr,&sc);
		if ((AIr[i]==true)&&(r[sr].getstate(sc)!=row::NE))
		{
			int temp=rand()%100+1;
			if ((temp<=efp)&&(*AIhalf==1))
				AIr[i]=false;
			else
			{
				record[r[sr].getkind(sc)-1]++;
			}
		}
	}
	// Then the AI will click a card.
	// Cheak whether the AI remember identical card.
	int same=0;
	for (int i=0;i<*maxk;i++)
	{
		if (record[i]>=2)
		{
			same=i+1;
			break;
		}
	}
	switch (*AIhalf)
	{
	case 1:
		if (same!=0)
		{
			for (int i=0;i<(*maxr)*(*maxc);i++)
			{
				cotransf(i,&sr,&sc);
				if ((AIr[i]==true)&&(r[sr].getstate(sc)!=row::NE)&&(r[sr].getkind(sc)==same))
				{
					response(i);
					break;
				}
			}
		}
		else
		{
			// Randomly click a card that it does not remember.
			int temp=rand()%((*maxr)*(*maxc));
			cotransf(temp,&sr,&sc);
			while ((AIr[temp]==true)||(r[sr].getstate(sc)==row::NE))
			{
				temp=rand()%((*maxr)*(*maxc));
				cotransf(temp,&sr,&sc);
			}
			response(temp);
			AIr[temp]=true;
			record[r[sr].getkind(sc)-1]++;
			if (record[r[sr].getkind(sc)-1]>=2)
				same=r[sr].getkind(sc);
		}
		(*AIhalf)++;
		break;
	case 2:
		if (same!=0)
		{
			for (int i=0;i<(*maxr)*(*maxc);i++)
			{
				cotransf(i,&sr,&sc);
				if ((AIr[i]==true)&&(r[sr].getstate(sc)!=row::NE)&&(r[sr].getkind(sc)==same)&&(i!=*n1))
				{
					response(i);
					break;
				}
			}
		}
		else
		{
			// Randomly click a card that it does not remember.
			int temp=rand()%((*maxr)*(*maxc));
			cotransf(temp,&sr,&sc);
			while ((AIr[temp]==true)||(r[sr].getstate(sc)==row::NE)||(temp==*n1))
			{
				temp=rand()%((*maxr)*(*maxc));
				cotransf(temp,&sr,&sc);
			}
			response(temp);
			AIr[temp]=true;
		}
		(*AIhalf)++;
		break;
	case 3:
		(*AIhalf)=1;
		break;
	}
	delete [] record;
	return (*AIhalf);
}

// A closing function that designed dedicately for AI.
// Input: A pointer pointed to a boolean whether game wins or not.
// Output: The number of row is available in the game and a boolean pointer.
int gamerules::AIclosing(bool *f,int *cond)
{
	*cond=NULL;
	int sr1,sc1,sr2,sc2;
	cotransf(*n1,&sr1,&sc1);
	cotransf(*n2,&sr2,&sc2);
	if (r[sr1].getkind(sc1)==r[sr2].getkind(sc2))
	{
		r[sr1].setstate(sc1,row::NE);
		r[sr2].setstate(sc2,row::NE);
		if (*AI==false)
		{
			(*score)++;
			*cond=SCORE;
		}
		else
		{
			(*AIscore)++;
			*cond=AISCORE;
		}
		(*left)-=(*rulen);
	}
	else
	{
		r[sr1].setstate(sc1,row::COVER);
		r[sr2].setstate(sc2,row::COVER);
		AIr[*n1]=true;
		AIr[*n2]=true;
		*AI=!(*AI);
	}
	if (*left==0)
		*f=true;
	else
		*f=false;
	return updatenowr();
}

// Get whether AI system is on or off.
// Output: the state of the AI system.
bool gamerules::getAImode()
{
	return *AImode;
}

// Get who is controlling the game.
// Output: a Boolean to show who is controlling the game.
bool gamerules::getAI()
{
	return *AI;
}

// Get the score of the AI.
// Output: the score of the AI.
int gamerules::getAIscore()
{
	return *AIscore;
}

// Get how many kinds are purchased.
// Output: the number of cards purchased by user.
int gamerules::getpk()
{
	int pknum=0;
	for (int i=0;i<*maxk;i++)
	{
		if (pk[i]==true)
			pknum++;
	}
	return pknum;
}

// Get the current hero.
// Output: the current hero,
int gamerules::gethero()
{
	return *hero;
}

// Set the current hero.
// Input: the expected hero.
void gamerules::sethero(int h)
{
	*hero=h;
}