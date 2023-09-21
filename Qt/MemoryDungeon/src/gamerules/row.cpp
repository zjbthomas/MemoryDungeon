#include "row.h"

// Destructor of row objects. Release heap.
Row::~Row()
{
    delete [] this->cardStatusArr;
    delete [] this->cardKArr;
    delete [] this->cardSpArr;
}

// Works as constructor of the class.
// Input: the number of cards in this row.
void Row::init(int maxC, bool* ownedKArr, bool* ownedSpArr)
{
    this->maxC = maxC;

    this->cardStatusArr = new int[maxC];
    this->cardKArr = new int[maxC];
    this->cardSpArr = new int[maxC];
    for (int c=0; c < maxC; c++)
    {
        this->cardStatusArr[c] = NE;
        this->cardKArr[c] = -1;
        this->cardSpArr[c] = 0;
    }

    this->ownedKArr = ownedKArr;
    this->ownedSpArr = ownedSpArr;
}

// Generate a row of cards with a hint card.
// Input: how many kinds to generate and what is the rule.
// Call: rand().
void Row::newRow(int maxK, int levelKN,int eraseN,int levelSp)
{
    // First decide what and where is the special card.
    int spPos = rand() % (this->maxC);

    // Check whether it is purchased.
    int selectedSp = rand() % levelSp - levelSp + this->OFFSET + 1;
    while (this->ownedSpArr[- selectedSp + this->OFFSET] == false) {
        selectedSp = rand() % levelSp - levelSp + this->OFFSET + 1;
    }
    this->cardSpArr[spPos] = selectedSp;
    this->cardKArr[spPos] = 0;

    // Generate each kind has how many cards in this row.
    int genN = this->maxC - 1; // Minus the special card.

    // Calculate purchased card kinds.
    int ownedKN = 0;
    int kLast = 0; // this is used in generating random kind
    for (int k=0; k < maxK; k++)
    {
        if (this->ownedKArr[k])
        {
            ownedKN++;
        }

        // TODO: a trick: first few kinds appear more than later kinds, as we stop when ownedKN == levelK
        if (ownedKN == levelKN)
        {
            kLast = k;
            break;
        }
    }

    // Calculate the number of cards for one kind
    // TODO: need to rethink the logic here
    int* perKNArr = new int[kLast + 1];
    for (int k = 0; k < kLast; k++)
    {
        if (this->ownedKArr[k])
        {
            int nPairs = (this->maxC - 1) / eraseN / levelKN + rand() % 2;  // This gives the number of pairs of one kind of cards.
            while ((eraseN * nPairs) > genN) {
                nPairs = (this->maxC - 1) / eraseN / levelKN + rand() % 2;
            }
            perKNArr[k] = eraseN * nPairs;
            genN -= perKNArr[k];
        }
        else
        {
            perKNArr[k] = 0; // if no owned, set to 0
        }
    }

    // Assign card kinds to each position
    perKNArr[kLast] = genN; // the remaining genN
    for (int c = 0; c < this->maxC; c++)
    {
        if (c != spPos)
        {
            int selectedK = rand() % (kLast + 1) + 1;
            while (perKNArr[selectedK - 1] <= 0) {
                selectedK = rand() % (kLast + 1) + 1;
            }
            cardKArr[c] = selectedK;
            perKNArr[selectedK - 1]--;
        }
    }
    delete [] perKNArr;
}

// To randomly generate a row of cards. Used at the start of a game. Should follow row::start().
// Input: number of kinds, a pointer to link the row in order to make sure the numbers of each kind are even.
void Row::oneRandomRow(int kLast,int* perKNArr)
{
    for (int c = 0; c < this->maxC; c++)
    {
        int selectedK = rand() % (kLast + 1) + 1;
        while (perKNArr[selectedK - 1] <= 0) {
            selectedK = rand() % (kLast + 1) + 1;
        }
        cardKArr[c] = selectedK;
        perKNArr[selectedK - 1]--;
    }
}

// Get the state of a single card.
// Input: the index of a card.
// Ouput: the state of that card.
int Row::getCardState(int pos)
{
    return this->cardStatusArr[pos];
}

// Set the state of a single card.
// Input: the index of a card and the expected state.
void Row::setCardState(int pos,int s)
{
    this->cardStatusArr[pos] = s;
}

// Get the kind of a single card.
// Input: the index of a card.
// Ouput: the kind of that card.
int Row::getCardKind(int pos)
{
    return this->cardKArr[pos];
}

// Set the kind of a single card. Usually used in initialization.
// Input: the index of a card and the expected kind.
void Row::setCardKind(int pos, int k)
{
    this->cardKArr[pos] = k;
}

// Return the special kind.
// Output: the special kind.
int Row::getSp(int pos)
{
    return this->cardSpArr[pos];
}

// Set the special kind.
// Input: the index of a card and the expected special kind.
void Row::setSp(int pos,int p)
{
    this->cardSpArr[pos] = p;
}

// When there is a "chaos" operation, use this random function.
// Input: number of kinds, a pointer to link the row in order to make sure the numbers of each kind are even.
void Row::shuffle(int maxK,int* perKNArr)
{
    for (int c = 0; c < this->maxC; c++)
    {
        if ((this->cardStatusArr[c] != NE) && (this->cardKArr[c] != 0)) // 0 means special card
        {
            int selectedK = rand() % maxK + 1;
            while (perKNArr[selectedK - 1] <= 0) {
                selectedK = rand() % maxK + 1;
            }
            this->cardKArr[c] = selectedK;
            perKNArr[selectedK - 1]--;
        }
    }
}
