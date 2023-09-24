#include "gamerule.h"

// Constructor of the class.
// Input: the maximum numbers of rows and cards (in each row), a base time.
// Call: row::init();
GameRule::GameRule(int maxR,int maxC,int maxK,int maxSp, bool* ownedKArr, bool* ownedSpArr)
{
    // initial random seed
    srand((unsigned)time(NULL));

    this->maxR = maxR;
    this->maxC = maxC;
    this->maxK = maxK;
    this->maxSp = maxSp;

    this->ownedKArr = ownedKArr;

    // initial rows
    this->rowArr = new Row[this->maxR];
    for (int r = 0; r < maxR; r++) {
        this->rowArr[r].init(maxC, ownedKArr, ownedSpArr);
    }

    // initial AI
    this->aiMemoryArr = new bool[maxR * maxC];
    for (int p = 0; p<(maxR * maxC); p++) {
        this->aiMemoryArr[p] = false;
    }
}

// Destructor of the class. Release heap.
GameRule::~GameRule()
{
    delete [] this->rowArr;
    delete [] this->aiMemoryArr;
}

// Generate a new level.
// Output: the kind of the generated level.
int GameRule::newLevel()
{
    // not AI mode
    this->isAIMode = false;

    (this->level)++;

    // TODO: ownedK may change after purchase, so we have code here to update every time?
    int ownedKN = 0;
    for (int k = 0; k < this->maxK; k++)
    {
        if (this->ownedKArr[k]) {
            ownedKN++;
        }
    }

    int floor;
    if (this->level % 10 == 0) // It is a Evil Level.
    {
        floor = EVIL;

        this->eraseN = 3;

        // Generate the kind of card.
        this->levelKN = ownedKN;
        this->levelSpN = 2;
        this->currentR = 4;
        this->popN = 2;

        // Calculate the time.
        int minTime = 100; // Here sets the lowest time.
        this->baseTime = minTime + 50 * (this->eraseN - 2) + 10 * (this->levelKN - 2) + 50 * (this->popN - 1) - 2 * (this->level - 1);

        if (this->baseTime < minTime) {
            this->baseTime = minTime;
        }

        this->timeRemain = this->baseTime;

        // Calculte the target points.
        this->objective = 20 + 3 * (this->level - 1);
    }
    else if (this->level % 5 == 0) // It is a Clown Level.
    {
        floor = CLOWN;

        this->eraseN = 2;

        // Generate the kind of card.
        this->levelKN = ownedKN;
        this->levelSpN = 3;
        this->currentR = 3;
        this->popN = 1;

        // Calculate the time.
        int minTime = 100; // Here sets the lowest time.
        this->baseTime = minTime + 50 * (this->eraseN - 2) + 15 * (this->levelKN - 2) + 50 * (this->popN - 1) - 2 * (this->level - 1);

        if (this->baseTime < minTime) {
            this->baseTime = minTime;
        }

        this->timeRemain = this->baseTime;

        // Calculte the target points.
        this->objective = 20 + 3 * (this->level - 1);
    }
    else // It is a normal Level.
    {
        floor = NORMAL;

        // Generate the game rule.
        this->eraseN = 2 + rand() % 7 * 0.2; // About 83% is 2.

        // Generate the kind of card.
        this->levelKN = 2 + rand() % (ownedKN - 1);

        // Generate beginning number of rows.
        this->currentR = 2 + rand() % (this->maxR - 3);

        // Generate how many rows will be popped in one time.
        this->popN = 1 + rand() % 7 * 0.2; // About 83% is 1.

        this->normalLevelDefaultSettings();
    }

    // For MASTER
    if (this->hero == MASTER)
        (this->timeRemain) += 30;

    this->score = 0;
    this->isCombo = false;

    this->start();

    return floor;
}

// Generate a new level by pre-set conditions.
// Input: all kinds of conditions.
void GameRule::newLevelByConfig(int eraseN,int levelKN,int startR, int popN)
{
    this->isAIMode=false;

    (this->level)++;

    // Four variables that can be changed by user.
    this->eraseN = eraseN;
    this->levelKN = levelKN;
    this->currentR = startR;
    this->popN = popN;

    // Other variables generated directly by system.
    this->normalLevelDefaultSettings();

    // For MASTER
    if (this->hero == MASTER)
        (this->timeRemain) += 30;

    this->score = 0;
    this->isCombo = false;

    this->start();
}

void GameRule::normalLevelDefaultSettings() {
    // Generate the kind of spcial card.
    this->levelSpN = this->maxSp; // TODO: why?

    // Calculate the time.
    int minTime = 120;
    this->baseTime = minTime + 50 * (this->eraseN - 2) + 20 * (this->levelKN - 2) + 50 * (this->popN - 1) - 2 * (this->level - 1);

    if (this->baseTime < minTime) {
        this->baseTime = minTime;
    }

    this->timeRemain = this->baseTime;

    // Calculte the target points.
    this->objective = 20 - 5 * (this->eraseN - 2) + 3 * (this->level - 1) - 2 * (this->currentR - 2);
}

// Start a new game.
// Input: number of rows at the beginning, how many kinds should be generated and what's the rule.
// Call: row::setstate(), row::random(), row::start(), row::newrow().
void GameRule::start()
{
    for (int r = 0; r < this->maxR; r++) {
        for (int c = 0; c < this->maxC; c++) {
            this->rowArr[r].setCardState(c, Row::NE);
        }
    }

    this->cardRemain = 0;

    int tempR = this->currentR;
    this->currentR = 0; // popRow() will use and modify this value, so we reset it to 0 here
    this->popRow(tempR);
    this->currentR = tempR;

    this->shuffleCards();

    this->flipState = 1;
    this->aiFlipState = 1;
}

// Response whether a card is clickable or not.
// Input: the index of a card (need to be decoded).
// Output: Whether it is clickable or not.
bool GameRule::isCardClickable(int n)
{
    int sr,sc;
    this->n2RC(n,&sr,&sc);

    if ((this->rowArr[sr].getCardKind(sc)==0)||(this->rowArr[sr].getCardState(sc) == Row::COVER)) {
        return true;
    }
    else if ((this->flipState == 2) && (n == this->flip1)) {
        return true;
    }
    else {
        return false;
    }
}

// Get the state of kind of one card.
// Input: the index of a card (need to be decoded).
// Output: If it's a EXISTED special card, return the kind of special card, if it's not uncovered, return state, Otherwise, return kind.
// Call: n2RC(), row::getkind(), row::getstate().
int GameRule::getCardDisplay(int n)
{
    int sr,sc;
    n2RC(n,&sr,&sc);

    if (this->rowArr[sr].getCardKind(sc) == 0) // 0 means special kind
    {
        // Make TIME of MASTER become visible.
        if ((this->hero == MASTER)&&(this->rowArr[sr].getSp(sc) == Row::HEAL) && (this->rowArr[sr].getCardState(sc) != Row::NE))
        {
            this->rowArr[sr].setCardState(sc, Row::UNCOVER);
            return this->rowArr[sr].getSp(sc);
        }
        if (this->rowArr[sr].getCardState(sc) == Row::UNCOVER)
            return this->rowArr[sr].getSp(sc);
        else
            return this->rowArr[sr].getCardState(sc);
    }

    if (this->rowArr[sr].getCardState(sc) != Row::UNCOVER)
        return this->rowArr[sr].getCardState(sc);
    else
        return this->rowArr[sr].getCardKind(sc);
}

// Response to a click.
// Input: the index of a card (need to be decoded).
// Output: If a special card is clicked, return the kind of that card; Otherwise, return whether a single card or a pair of cards is clicked.
// Call: n2RC(), row::getkind(), row::getstate(), row::setstate().
int GameRule::performClick(int n)
{
    int sr,sc;
    n2RC(n,&sr,&sc);

    // If it is a special card.
    if (this->rowArr[sr].getCardKind(sc) == 0)
    {
        // If a single/double card had been clicked, cover it/them.
        int tr,tc;
        switch (this->flipState)
        {
        case 2:
            n2RC(this->flip1, &tr, &tc);
            this->rowArr[tr].setCardState(tc, Row::COVER);
            break;
        case 3:
            n2RC(this->flip1,&tr,&tc);
            this->rowArr[tr].setCardState(tc,Row::COVER);
            n2RC(this->flip2,&tr,&tc);
            this->rowArr[tr].setCardState(tc,Row::COVER);
            break;
        }

        // special card effect
        // TODO: move this to a single function
        switch (this->rowArr[sr].getSp(sc))
        {
        case Row::REINFORCE:
            // Minus the score by the number of rows left.
            if (this->score >= (this->maxR - this->currentR)) {
                this->score -= (this->maxR - this->currentR);
            }
            // Pop a new row and show it.
            if (this->currentR < this->maxR)
            {
                this->popRow(1);

                // Update the value of n as rows are added.
                n += (this->maxC);
                n2RC(n,&sr,&sc); // used later which uncover the card

                // uncover newly added row (for user to remember them)
                for (int c = 0; c < this->maxC; c++) {
                    this->rowArr[this->currentR - 1].setCardState(c, Row::UNCOVER);
                }
            }
            break;{}
        case Row::CHAOS:
            this->shuffleCards();

            // show all the cards
            for (int r = 0; r < this->currentR; r++)
            {
                for (int c = 0; c < this->maxC; c++) {
                    if (this->rowArr[r].getCardState(c) != Row::NE) {
                        this->rowArr[r].setCardState(c, Row::UNCOVER);
                    }
                }
            }
            break;
        case Row::GOLD:
            // The operations are done in the GUI.
            break;
        case Row::MAP:
            this->match = -1; // we need a class member as it is used in other function

            int nPairs2Match;
            int tempPos;

            int tempMatch; // we need this as HUNTER will find two pairs
            tempMatch = -1;

            // decide how many pairs to match
            if (this->hero == HUNTER) {
                nPairs2Match = 2;
            }
            else {
                nPairs2Match = 1;
            }

            // handle each pair
            for (int p = 0; p < nPairs2Match; p++)
            {
                // find one as reference
                for (int cn = 0; cn < (this->maxR)*(this->maxC); cn++)
                {
                    n2RC(cn,&tr,&tc);

                    if ((this->rowArr[tr].getCardState(tc) != Row::NE) &&
                        (this->rowArr[tr].getCardKind(tc) != 0) &&
                        (this->rowArr[tr].getCardKind(tc) != tempMatch))
                    {
                        this->rowArr[tr].setCardState(tc, Row::UNCOVER);
                        this->match = this->rowArr[tr].getCardKind(tc);
                        tempPos = cn;
                        tempMatch = this->rowArr[tr].getCardKind(tc);
                        break;
                    }
                }

                // find other cards that match the reference
                for (int en = this->eraseN; en >= 2; en--) {
                    for (int cn = (tempPos + 1) ; cn < (this->maxR)*(this->maxC); cn++)
                    {
                        n2RC(cn,&tr,&tc);

                        if ((this->rowArr[tr].getCardState(tc) != Row::NE) && (this->rowArr[tr].getCardKind(tc) == this->match))
                        {
                            this->rowArr[tr].setCardState(tc, Row::UNCOVER);
                            tempPos = cn;
                            break;
                        }
                    }
                }
            }
            break;
        case Row::HEAL:
            if (this->hero == MASTER)
            {
                this->timeRemain += (this->baseTime / 2.0);

                if (this->timeRemain > this->baseTime) {
                    this->timeRemain = this->baseTime;
                }
            }
            else {
                this->timeRemain = this->baseTime;
            }
            break;
        case Row::TREASURE:
            // The operations are done in the GUI.
            break;
        }

        // uncover the special card
        this->rowArr[sr].setCardState(sc, Row::UNCOVER);

        this->flip1 = n;
        this->flipState = 1;

        return this->rowArr[sr].getSp(sc); // return the kind of special card.
    }

    // If it is a normal card.
    switch (this->flipState)
    {
    case 1:
        this->flip1 = n;
        (this->flipState)++;
        break;
    case 2:
        this->flip2 = n;
        if (this->eraseN == 2)
        {
            this->flipState = 1;

            // if user click the same card, cover it
            if (this->flip1 == this->flip2)
            {
                this->rowArr[sr].setCardState(sc,Row::COVER);

                return 0;
            }
        }
        else
        {
            int sr1,sc1,sr2,sc2;
            n2RC(this->flip1,&sr1,&sc1);
            n2RC(this->flip2,&sr2,&sc2);

            if (this->flip1 == this->flip2)
            {
                this->rowArr[sr].setCardState(sc,Row::COVER);

                this->flipState = 1;

                return 0;
            }

            if (this->rowArr[sr1].getCardKind(sc1) != this->rowArr[sr2].getCardKind(sc2))
            {
                this->flip3 = n;

                this->flipState = 1;
            }
            else
                (this->flipState)++;
        }
        break;
    case 3:
        this->flip3 = n;

        (this->flipState)=1;

        break;
    }

    this->rowArr[sr].setCardState(sc, Row::UNCOVER);

    return ((this->flipState) == 1);
}

// When a hint or a pair of cards are shown for a given time, decide what to do next. Used in the closing timer.
// Input: A pointer pointed to a boolean whether game wins or not.
// Output: The number of row is available in the game and a boolean pointer.
// Call: n2RC(), row::getkind(), row::row::getstate(), row::setstate().
int GameRule::settle(bool* winGame,int* status)
{
    *status = EMPTY;

    int sr1,sc1,sr2,sc2,sr3,sc3;
    n2RC(this->flip1,&sr1,&sc1);

    // If it is a special card.
    if (this->rowArr[sr1].getCardKind(sc1) == 0)
    {
        *status = BONUS;
        switch (this->rowArr[sr1].getSp(sc1))
        {
        case Row::REINFORCE:
            // cover the newly added row
            for (int c = 0; c < this->maxC; c++) {
                this->rowArr[this->currentR - 1].setCardState(c, Row::COVER);
            }

            if (this->score > 0) {
                (this->score)--;
            }

            *status=BREAK;

            break;

        case Row::CHAOS:
            // cover all the cards
            for (int r=0; r < this->maxR; r++)
            {
                for (int c = 0; c < this->maxC; c++)
                {
                    if (this->rowArr[r].getCardState(c) != Row::NE) {
                        this->rowArr[r].setCardState(c, Row::COVER);
                    }
                }
            }
            break;

        case Row::GOLD:
            *status = CREDIT;
            break;

        case Row::MAP:
            // when a match is found, remove the matched cards
            if (this->match != -1)
            {
                for (int cn = 0; cn < (this->maxR)*(this->maxC); cn++)
                {
                    int tr,tc;
                    n2RC(cn,&tr,&tc);
                    if ((this->rowArr[tr].getCardState(tc) == Row::UNCOVER) && (this->rowArr[tr].getCardKind(tc) != 0))
                    {
                        this->rowArr[tr].setCardState(tc, Row::NE);

                        (this->cardRemain)--;
                    }
                }
            }

            (this->score)++;

            break;
        case Row::HEAL:
            break;
        case Row::TREASURE:
            break;
        }

        this->rowArr[sr1].setCardState(sc1,Row::NE);

        //(this->score)++;
        (this->cardRemain)--;
    }
    else
    {
        // it is a normal card
        n2RC(this->flip2,&sr2,&sc2);
        n2RC(this->flip3,&sr3,&sc3);

        switch (this->eraseN)
        {
        case 2:
            if (this->rowArr[sr1].getCardKind(sc1) == this->rowArr[sr2].getCardKind(sc2))
            {
                // remove two cards
                this->rowArr[sr1].setCardState(sc1, Row::NE);
                this->rowArr[sr2].setCardState(sc2, Row::NE);

                // add score
                (this->score)++;

                *status=SCORE;

                // handle combo except BERSERKER
                if (this->hero != BERSERKER)
                {
                    if (this->isCombo)
                    {
                        // add one more score
                        (this->score)++;

                        *status=COMBO;
                    }
                    else
                        this->isCombo = true;
                }
                else
                {
                    // CRITICAL system for BERSERKER.
                    int criticalRoll = rand() % 100 + 1;
                    if (criticalRoll <= this->CRITICALRATE) // Here set the critical rate.
                    {
                        // add 2 points
                        (this->score)+=2;

                        *status=CRITICAL;
                    }
                }

                // update remaining card number
                (this->cardRemain) -= (this->eraseN);

            }
            else
            {
                // cover cards if not matched
                this->rowArr[sr1].setCardState(sc1, Row::COVER);
                this->rowArr[sr2].setCardState(sc2, Row::COVER);

                // reset combo flag
                this->isCombo=false;
            }
            break;
        case 3:
            if ((this->rowArr[sr1].getCardKind(sc1) == this->rowArr[sr2].getCardKind(sc2)) &&
                (this->rowArr[sr1].getCardKind(sc1)==this->rowArr[sr3].getCardKind(sc3)))
            {
                this->rowArr[sr1].setCardState(sc1,Row::NE);
                this->rowArr[sr2].setCardState(sc2,Row::NE);
                this->rowArr[sr3].setCardState(sc3,Row::NE);

                // add score
                (this->score)++;

                *status=SCORE;

                // handle combo except BERSERKER
                if (this->hero != BERSERKER)
                {
                    if (this->isCombo)
                    {
                        // add one more score
                        (this->score)++;

                        *status=COMBO;
                    }
                    else
                        this->isCombo = true;
                }
                else
                {
                    // CRITICAL system for BERSERKER.
                    int criticalRoll = rand() % 100 + 1;
                    if (criticalRoll <= this->CRITICALRATE) // Here set the critical rate.
                    {
                        // add 2 points
                        (this->score)+=2;

                        *status=CRITICAL;
                    }
                }

                // update remaining card number
                (this->cardRemain) -= (this->eraseN);
            }
            else
            {
                this->rowArr[sr1].setCardState(sc1,Row::COVER);
                this->rowArr[sr2].setCardState(sc2,Row::COVER);
                this->rowArr[sr3].setCardState(sc3,Row::COVER);

                // reset combo flag
                this->isCombo=false;
            }
            break;
        }
    }

    // after removing cards, move remaining cards downwards
    this->moveCardsDownwards();

    // when the game is not end but no card left, pop new rows
    if (this->cardRemain == 0)
    {
        // Pop half of maximum rows right now, and the left time will change into score.
        (this->score) += (this->timeRemain) / 10; // TODO: a magic number here

        *status = BONUS;

        this->popRow(this->maxR / 2);

        this->shuffleCards();
    }

    // win game
    if ((this->score) >= (this->objective))
    {
        *winGame = true;

        // remove all cards
        for (int n = 0; n < (this->maxR) * (this->maxC); n++)
        {
            n2RC(n,&sr1,&sc1);
            this->rowArr[sr1].setCardState(sc1,Row::NE);
        }
    }
    else {
        *winGame=false;
    }

    return this->updateCurrentR();
}

// The card will move downwards if there is no card below.
int GameRule::moveCardsDownwards()
{
    // Notice that the row indeces in game are mirrored.
    for (int r = 0; r < this->currentR ;r++)
    {
        for (int c=0; c < this->maxC; c++)
        {
            if (this->rowArr[r].getCardState(c) != Row::NE)
            {
                for (int tr = r + 1; tr < this->currentR; tr++)
                {
                    if (this->rowArr[tr].getCardState(c) == Row::NE)
                    {
                        this->rowArr[tr].setCardState(c, this->rowArr[r].getCardState(c));
                        this->rowArr[tr].setCardKind(c,this->rowArr[r].getCardKind(c));
                        this->rowArr[tr].setSp(c,this->rowArr[r].getSp(c));
                        this->rowArr[r].setCardState(c, Row::NE);
                        break;
                    }
                }
            }
        }
    }
    return this->updateCurrentR(); // This is a MUST!!
}

// Get the number of rows avaliable in the game. It will also update nowr.
// Output: the number of rows avaliable in the game.
int GameRule::updateCurrentR()
{
    // find the empty row position
    // Notice that the row indeces in game are mirrored, which means we find the minimum r with enabled cards
    int emptyRIndex = 0;
    for (int r = 0; r < this->currentR; r++)
    {
        for (int c = 0; c < this->maxC; c++)
        {
            if (this->rowArr[r].getCardState(c) != Row::NE)
            {
                emptyRIndex = r;
                r = this->currentR; // break loop for r as well
                break;
            }
        }
    }

    // Move the rows to fill the empty row.
    if (emptyRIndex != 0)
    {
        for (int r = emptyRIndex; r < this->currentR; r++)
        {
            for (int c = 0; c < this->maxC; c++)
            {
                this->rowArr[r - emptyRIndex].setCardState(c,this->rowArr[r].getCardState(c));
                this->rowArr[r - emptyRIndex].setCardKind(c,this->rowArr[r].getCardKind(c));
                this->rowArr[r - emptyRIndex].setSp(c,this->rowArr[r].getSp(c));
                this->rowArr[r].setCardState(c,Row::NE);
            }
        }
    }

    // update currentR
    (this->currentR) -= emptyRIndex;

    return this->currentR;
}

// To make a new row available in the game, and decide whether game over.
// Input: how many rows will be popped in one time.
// Output: whether game IS NOT over (or rather say, whether a new line is poped).
// Call: row::setstate().
bool GameRule::popRow(int n)
{
    if ((this->currentR + n) > this->maxR) // Game over.
    {
        for (int r = 0; r < this->maxR; r++)
        {
            for (int c = 0; c < this->maxC; c++)
                this->rowArr[r].setCardState(c, Row::NE);
        }
        return false;
    }
    else
    {
        int lastR = this->currentR;
        int genN = n * this->maxC;
        // If the number of cards is not devidable by the rule number, add special card.
        int nRow2AddSp = genN % this->eraseN;

        // add random special card
        int randomR1 = -1, randomR2 = -1;
        switch (nRow2AddSp)
        {
        case 2:
            randomR2 = lastR + rand() % n;

            this->rowArr[randomR2].newRow(this->maxK, this->levelKN, this->eraseN, this->levelSpN);
            for (int c = 0; c < this->maxC; c++) {
                this->rowArr[randomR2].setCardState(c, Row::COVER);
            }

            (this->currentR)++;
            (this->flip1) += this->maxC;
            (this->flip2) += this->maxC;
            (this->flip3) += this->maxC;
            (this->cardRemain) += this->maxC;

            // no break - do case 1 as well
        case 1:
            randomR1 = lastR + rand() % n;
            while (randomR1 == randomR2) {
                randomR1 = lastR + rand() % n;
            }

            this->rowArr[randomR1].newRow(this->maxK, this->levelKN, this->eraseN, this->levelSpN);
            for (int c = 0; c < this->maxC; c++) {
                this->rowArr[randomR1].setCardState(c, Row::COVER);
            }

            (this->currentR)++;
            (this->flip1) += this->maxC;
            (this->flip2) += this->maxC;
            (this->flip3) += this->maxC;
            (this->cardRemain) += this->maxC;

            break;
        }

        // Generate other rows that without special card.
        int rowN = n - nRow2AddSp;
        genN = this->maxC * rowN;

        // Calculate purchased card kinds.
        // TODO: better to move these into row.cpp
        int ownedKN = 0;
        int kLast = 0; // this is used in generating random kind
        for (int k=0; k < maxK; k++)
        {
            if (this->ownedKArr[k])
            {
                ownedKN++;
            }

            // TODO: a trick: first few kinds appear more than later kinds, as we stop when ownedKN == levelK
            if (ownedKN == this->levelKN)
            {
                kLast = k;
                break;
            }
        }

        int* perKNArr = new int[kLast + 1];
        for (int k = 0; k < kLast; k++)
        {
            if ((this->ownedKArr[k]) && (genN >= (this->maxC) * (rowN) / (this->levelKN)))
            {
                int nPairs = (this->maxC) * (rowN) / (this->eraseN) / (this->levelKN) + rand() % 2;  // This gives the number of pairs of one kind of cards.
                while ((nPairs * (this->eraseN)) > genN) {
                    nPairs = (this->maxC) * (rowN) / (this->eraseN) / (this->levelKN) + rand() % 2;
                }
                perKNArr[k] = nPairs * this->eraseN;
                genN -= perKNArr[k];
            }
            else
            {
                perKNArr[k] = 0;
            }
        }

        perKNArr[kLast] = genN;
        if (rowN != 0)
        {
            for (int r = 0; r < n; r++)
            {
                if (((lastR + r) != randomR1) && ((lastR + r) != randomR2))
                {
                    this->rowArr[(lastR + r)].oneRandomRow(kLast, perKNArr);
                    for (int c = 0; c < this->maxC; c++) {
                        this->rowArr[(lastR + r)].setCardState(c, Row::COVER);
                    }

                    (this->currentR)++;
                    (this->flip1) += this->maxC;
                    (this->flip2) += this->maxC;
                    (this->flip3) += this->maxC;
                    (this->cardRemain) += this->maxC;
                }
            }
        }

        // reset timer
        this->timeRemain = this->baseTime;

        return true;
    }
}

// Disorganise all existing and avaliable (NOT SPECIAL) cards in the game.
void GameRule::shuffleCards()
{
    int* perKNArr=new int[this->maxK];
    for (int k = 0; k < this->maxK; k++) {
        perKNArr[k] = 0;
    }

    // check and store how many cards per kind
    for (int r = 0; r < this->currentR; r++)
    {
        for (int c = 0; c < this->maxC; c++)
        {
            if ((this->rowArr[r].getCardState(c) != Row::NE) && (this->rowArr[r].getCardKind(c) != 0)) {
                perKNArr[this->rowArr[r].getCardKind(c) - 1]++;
            }
        }
    }

    // shuffle
    for (int r = 0; r < this->currentR; r++)
    {
        this->rowArr[r].shuffle(this->maxK, perKNArr);
    }
    delete [] perKNArr;
}

// Get the rule.
// Output: the number represent the rule.
int GameRule::getEraseN()
{
    return this->eraseN;
}

// Get how many kinds is at the game.
// Output: the current number of kinds.
int GameRule::getLevelKN()
{
    return this->levelKN;
}

// Get how many rows will pop when time out.
// Output: the current popn.
int GameRule::getPopN()
{
    return this->popN;
}

// Get the base time.
// Output: the current basetime.
int GameRule::getBaseTime()
{
    return this->baseTime;
}

// Get the score.
// Output: the score.
int GameRule::getObjective()
{
    return this->objective;
}

// Get the score.
// Output: the current score.
int GameRule::getScore()
{
    return this->score;
}

// Get the left time.
// Output: the left time.
int GameRule::getTimeRemain()
{
    return this->timeRemain;
}

// Set the left time.
// Input: which time to set.
void GameRule::setTimeRemain(int t)
{
    this->timeRemain = t;
}

// Get the level.
// Output: the current level.
int GameRule::getLevel()
{
    return this->level;
}

// Set the level.
// Input: which level.
void GameRule::setLevel(int l)
{
    this->level = l;
}

// Decode an index to row and column.
// Input: index and two return pointers.
void GameRule::n2RC(int n, int* sr, int* sc)
{
    *sr = n / (this->maxC);
    *sc = n % (this->maxC);

    // Mirrored the rows which is avaliable in the game.
    if (*sr < this->currentR) {
        *sr = this->currentR - (*sr + 1);
    }
}

// Start a new AI game.
// Input: the expected forget percentage of the AI.
void GameRule::newAILevel(int forgetRate)
{
    this->isAIMode = true;

    // Initialize the AI system.
    this->aiForgetRate = forgetRate;

    for (int n = 0; n < (this->maxR) * (this->maxC); n++) {
        this->aiMemoryArr[n] = false;
    }

    this->aiScore = 0;

    // Start a new game.
    this->isAITurn = false;

    this->eraseN = 2; // force to only match 2 cards

    int ownedKN = 0;
    for (int k = 0; k < this->maxK; k++)
    {
        if (this->ownedKArr[k]) {
            ownedKN++;
        }
    }
    this->levelKN = ownedKN;

    this->levelSpN = 0; // no special card

    this->currentR = this->maxR; // all rows used

    this->score = 0;

    this->start();
}

// Do an AI click action.
// Output: the index number of the progress.
int GameRule::aiAction()
{
    int sr,sc;

    // First the AI will forget some EXISTED cards if it is its first click.
    // Change the forget percentage into an effective one.
    int rememberN=0;
    for (int n = 0; n < (this->maxR) * (this->maxC); n++)
    {
        n2RC(n,&sr,&sc);
        if ((this->aiMemoryArr[n]) && (this->rowArr[sr].getCardState(sc) != Row::NE)) {
            rememberN++;
        }
    }

    int effectiveForgetRate;
    if (rememberN == 0) {
        effectiveForgetRate = this->aiForgetRate;
    }
    else {
        effectiveForgetRate = 100 - pow((float)(100 - (this->aiForgetRate)) /100.0 , 1.0 / (float)rememberN) * 100;
    }

    // a histogram of card kinds that AI remember
    int* aiPerKNArr = new int[this->maxK];
    for (int k = 0; k < this->maxK; k++) {
        aiPerKNArr[k]=0;
    }

    for (int n = 0; n < (this->maxR) * (this->maxC); n++)
    {
        n2RC(n,&sr,&sc);
        if ((this->aiMemoryArr[n]) && (this->rowArr[sr].getCardState(sc) != Row::NE))
        {
            // AI will first forget some cards
            int forgetRoll = rand() % 100 + 1;
            if ((forgetRoll <= effectiveForgetRate) &&
                (this->aiFlipState == 1)) { // will not forget when AI is in action
                this->aiMemoryArr[n] = false;
            }
            else
            {
                aiPerKNArr[this->rowArr[sr].getCardKind(sc) - 1]++;
            }
        }
    }

    // Then the AI will click a card.
    // first check whether the AI remember two identical cards.
    int possibleK=0;
    for (int k = 0; k < this->maxK; k++)
    {
        if (aiPerKNArr[k] >= 2) // TODO: safe to change this to eraseN?
        {
            possibleK = k + 1; // an offset 1 is added as 0 is special kind
            break;
        }
    }

    switch (this->aiFlipState)
    {
    case 1:
        if (possibleK != 0)
        {
            for (int n = 0; n < (this->maxR) * (this->maxC); n++)
            {
                n2RC(n,&sr,&sc);
                if ((this->aiMemoryArr[n]) &&
                    (this->rowArr[sr].getCardState(sc) != Row::NE) &&
                    (this->rowArr[sr].getCardKind(sc) == possibleK))
                {
                    this->performClick(n);
                    break;
                }
            }
        }
        else
        {
            // Randomly click a card that it does not remember.
            int clickPos = rand() % ((this->maxR) * (this->maxC));
            n2RC(clickPos,&sr,&sc);
            while ((this->aiMemoryArr[clickPos]) || (this->rowArr[sr].getCardState(sc) == Row::NE))
            {
                clickPos = rand() % ((this->maxR) * (this->maxC));
                n2RC(clickPos,&sr,&sc);
            }

            this->performClick(clickPos);

            // update memory
            this->aiMemoryArr[clickPos] = true;

            // if AI now remembers a pair
            aiPerKNArr[this->rowArr[sr].getCardKind(sc) - 1]++;

            // TODO: do we really need the following two lines?
            if (aiPerKNArr[this->rowArr[sr].getCardKind(sc) - 1] >= 2) // TODO: safe to change this to eraseN?
                possibleK = this->rowArr[sr].getCardKind(sc);
        }

        (this->aiFlipState)++;
        break;
    case 2:
        if (possibleK != 0)
        {
            for (int n = 0; n < (this->maxR) * (this->maxC); n++)
            {
                n2RC(n,&sr,&sc);
                if ((this->aiMemoryArr[n]) &&
                    (this->rowArr[sr].getCardState(sc) != Row::NE) &&
                    (this->rowArr[sr].getCardKind(sc) == possibleK) &&
                    (n != this->flip1)) // will not click the same card that is already uncovered
                {
                    this->performClick(n);
                    break;
                }
            }
        }
        else
        {
            // Randomly click a card that it does not remember.
            int clickPos = rand() % ((this->maxR) * (this->maxC));
            n2RC(clickPos,&sr,&sc);
            while ((this->aiMemoryArr[clickPos]) ||
                   (this->rowArr[sr].getCardState(sc) == Row::NE) ||
                   (clickPos == this->flip1))
            {
                clickPos = rand() % ((this->maxR) * (this->maxC));
                n2RC(clickPos,&sr,&sc);
            }

            this->performClick(clickPos);

            this->aiMemoryArr[clickPos] = true;
        }

        (this->aiFlipState)++;
        break;

    case 3:
        this->aiFlipState = 1;
        break;
    }

    delete [] aiPerKNArr;
    return this->aiFlipState;

}

// A closing function that designed dedicately for AI.
// Input: A pointer pointed to a boolean whether game wins or not.
// Output: The number of row is available in the game and a boolean pointer.
int GameRule::settleAI(bool* winGame,int* status)
{
    *status = EMPTY;

    int sr1,sc1,sr2,sc2;
    n2RC(this->flip1,&sr1,&sc1);
    n2RC(this->flip2,&sr2,&sc2);

    if (this->rowArr[sr1].getCardKind(sc1) == this->rowArr[sr2].getCardKind(sc2))
    {
        this->rowArr[sr1].setCardState(sc1,Row::NE);
        this->rowArr[sr2].setCardState(sc2,Row::NE);

        if (this->isAITurn == false)
        {
            (this->score)++;
            *status=SCORE;
        }
        else
        {
            (this->aiScore)++;
            *status=AISCORE;
        }

        (this->cardRemain) -= (this->eraseN);
    }
    else
    {
        this->rowArr[sr1].setCardState(sc1,Row::COVER);
        this->rowArr[sr2].setCardState(sc2,Row::COVER);

        // AI remembers all opened cards
        this->aiMemoryArr[this->flip1]=true;
        this->aiMemoryArr[this->flip2]=true;

        // if one fails to match cards, swap turn
        this->isAITurn = !(this->isAITurn);
    }

    // win game
    // TODO: why this logic?
    if (this->cardRemain == 0)
        *winGame=true;
    else
        *winGame = false;

    return this->updateCurrentR();
}

// Get whether AI system is on or off.
// Output: the state of the AI system.
bool GameRule::getIsAIMode()
{
    return this->isAIMode;
}

// Get who is controlling the game.
// Output: a Boolean to show who is controlling the game.
bool GameRule::getIsAITurn()
{
    return this->isAITurn;
}

// Get the score of the AI.
// Output: the score of the AI.
int GameRule::getAIScore()
{
    return this->aiScore;
}

// Get how many kinds are purchased.
// Output: the number of cards purchased by user.
int GameRule::getOwnedKN()
{
    int ownedKN=0;
    for (int k = 0; k < this->maxK; k++)
    {
        if (this->ownedKArr[k])
            ownedKN++;
    }
    return ownedKN;
}

// Get the current hero.
// Output: the current hero,
int GameRule::getHero()
{
    return this->hero;
}

// Set the current hero.
// Input: the expected hero.
void GameRule::setHero(int h)
{
    this->hero = h;
}
