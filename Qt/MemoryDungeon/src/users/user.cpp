#include "user.h"


// The constructor of the class.
User::User(int maxK,int maxSp)
{
    // initial random seed
    srand((unsigned)time(NULL));

    // For purchase.
    this->maxK = maxK;
    this->maxSp = maxSp;

    this->ownedK = new bool[maxK];
    for (int k = 0; k < maxK; k++) {
        this->ownedK[k] = false;
    }


    this->ownedSp = new bool[maxSp];
    for (int sp = 0; sp < maxSp; sp++) {
        this->ownedSp[sp] = false;
    }
}

// The destructor of the class. Release heap.
User::~User()
{
    delete [] this->ownedK;
    delete [] this->ownedSp;
}

// Read file if it is existed.
// Input: input a name and a password.
// Output: if there isn't the file, output -1; If the password is wrong, output -2; otherwise, output 0.
// Call: ifstream::close, strcpy(), strcmp(), ifstream::getline(), atoi().
int User::readFile(string username, string passwordAttmpt)
{
    this->username = username;

    // First check whether the file is exist or not.
    ifstream fin(username);
    if (!fin)
    {
        this->password = passwordAttmpt;
        fin.close();
        return -1;
    }

    // Check the version of the profile
    string versionStr;
    getline(fin, versionStr);
    if (stoi(versionStr) != this->VERSION)
    {
        // If the version is not the same, works as if no profile exist.
        this->password = passwordAttmpt;
        fin.close();
        return -1;
    }

    // check password
    getline(fin, this->password);
    if (this->password != passwordAttmpt)
    {
        fin.close();
        return -2;
    }

    string bestLevelStr;
    getline(fin, bestLevelStr);
    this->bestLevel = stoi(bestLevelStr);

    string savedLevelStr;
    getline(fin, savedLevelStr);
    this->savedLevel = stoi(savedLevelStr);

    string goldStr;
    getline(fin, goldStr);
    this->gold = stoi(goldStr);

    string aiForgetRateStr;
    getline(fin, aiForgetRateStr);
    this->aiForgetRate = stoi(aiForgetRateStr);

    string heroStr;
    getline(fin, heroStr);
    this->hero = stoi(heroStr);

    string ownedKStr;
    getline(fin, ownedKStr);
    for (int k = 0; k < this->maxK; k++)
    {
        this->ownedK[k] = (ownedKStr[k] - '0');
    }

    string ownedSpStr;
    getline(fin, ownedSpStr);
    for (int sp = 0; sp < this->maxSp; sp++)
    {
            this->ownedSp[sp] = (ownedSpStr[sp] - '0');
    }

    fin.close();
    return 0;
}

// Write the record to a file.
// Input: the new score.
// Call: ifstream::close.
void User::writeFile()
{
    ofstream fout(this->username);
    fout << this->VERSION << endl;
    fout << this->password << endl;
    fout << this->bestLevel <<endl;
    fout << this->savedLevel <<endl;
    fout << this->gold <<endl;
    fout << this->aiForgetRate <<endl;
    fout << this->hero <<endl;

    for (int k = 0; k < this->maxK; k++)
    {
        fout << this->ownedK[k];
    }
    fout << endl;

    for (int sp = 0; sp < this->maxSp; sp++)
    {
        fout << this->ownedSp[sp];
    }
    fout << endl;

    fout.close();
}

// Get the username.
// Output: the pointer pointed to the username.
string User::getUsername()
{
    return this->username;
}

// Get the level.
// Output: the level.
int User::getBestLevel()
{
    return this->bestLevel;
}

// Set the level.
// Input: the expected level.
void User::setBsetLevel(int l)
{
    this->bestLevel = l;
}

// Get saved level.
// Output: the saved level number.
int User::getSavedLevel()
{
    return this->savedLevel;
}

// Set saved level.
// Input: the expected level to be saved.
void User::setSavedLevel(int s)
{
    this->savedLevel = s;
}
// Get the credit.
// Output: the current credit.
int User::getGold()
{
    return this->gold;
}

// Set the credit.
// Input: the expected credit.
void User::setGold(int c)
{
    this->gold = c;
}

// Get the remember percentage of AI.
// Output: the current remember percentage of AI.
int User::getAIForgetRate()
{
    return this->aiForgetRate;
}

// Set the remember percentage of AI.
// Input: the remember percentage of AI..
void User::setAIForgetRate(int r)
{
    this->aiForgetRate = r;
}

// Get purchased kind of the user.
// Output: the pointer pointed to the array that store what user purchased.
bool* User::getOwnedK()
{
    return this->ownedK;
}

// Set what kind user purchased.
// Input: The index represents the expected kind and the expected boolean value.
void User::setAnOwnedK(int k,bool p)
{
    this->ownedK[k] = p;
}

// Get purchased special kind of the user.
// Output: the pointer pointed to the array that store what user purchased.
bool * User::getOwnedSp()
{
    return this->ownedSp;
}

// Set what special kind user purchased.
// Input: The index represents the expected kind and the expected boolean value.
void User::setAnOwnedSp(int sp, bool p)
{
    this->ownedSp[sp] = p;
}

// Use to generate what user purchased and update its information.
// Input: a pointer used to communicate with GUI.
// Output: whether the user gets a new kind or an old one.
bool User::gachaK(int fee, int* retK)
{
    // First substract the credit.
    this->gold -= fee;

    // Then generate a random card.
    *retK = rand() % (this->maxK) + 1;

    // a new random card or an old one
    if (this->ownedK[*retK - 1])
    {
        (this->gold)++; // pay back

        this->writeFile();

        return false;
    }
    else
    {
        this->ownedK[*retK - 1] = true;

        this->writeFile();

        return true;
    }
}

// Calculate the rate that user collected.
// Output: the rate times 100.
int User::getCollectionRate()
{
    int owned=0;
    for (int k = 0; k < this->maxK; k++)
    {
        if (this->ownedK[k]) {
            owned++;
        }
    }
    for (int sp = 0; sp < this->maxSp; sp++)
    {
        if (this->ownedSp[sp]) {
            owned++;
        }
    }
    return (int)((float)owned/(this->maxK+this->maxSp)*100.0);
}

// Get the current hero.
// Output: the current hero,
int User::getHero()
{
    return this->hero;
}

// Set the current hero.
// Input: the expected hero.
void User::setHero(int h)
{
    this->hero = h;
}
