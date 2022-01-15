#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include <algorithm>

using namespace std;

class Person
{
private:
    string Name;
    string Surname;
    string City;
    int Money;
    int Weight;

public:
    void setName(string name)
    {
        this->Name = name;
    }
    void setSurname(string surname)
    {
        this->Surname = surname;
    }
    void setCity(string city)
    {
        this->City = city;
    }
    void setMoney()
    {
        this -> Money = 10000 + (rand() % 91) * 1000;
    }
    void setWeight()
    {
        this -> Weight = 50 + rand() % 51;
    }

    string getName()
    {
        return this -> Name;
    }
     string getSurname()
    {
        return this -> Surname;
    }
     string getCity()
    {
        return this -> City;
    }
    int getMoney()
    {
        return this -> Money;
    }
    int getWeight()
    {
        return this -> Weight;
    }
};

class Player : public Person
{
private:

    int Number;
    bool isEliminated;

public:

    void setNumber(int number)
    {
       this -> Number = number;
       this -> isEliminated = false;
    }

    int getNumber()
    {
        return this -> Number;
    }

    void showPlayerDetails()
    {
        cout << getName() << " " << getSurname() << " " << getCity() << " " << getMoney() << " " << getWeight() << endl;
    }

    void getsEliminated()
    {
        this -> isEliminated = true;
    }

    string getFullName()
    {
        return this -> getName() + " " + this -> getSurname();
    }

    bool hasBeenEliminated()
    {
        return this -> isEliminated;
    }
};

class Supervisor : public Person
{
private:
    string Mask;
    int Allocated_players[12];
    int NrofAllocatedPlayers;

public:
    Supervisor() { NrofAllocatedPlayers = 0; }
    void AddPlayer(int NAP)
    {
        Allocated_players[NrofAllocatedPlayers] = NAP;
        NrofAllocatedPlayers++;
    }
    void setMask(string mask)
    {
        this -> Mask = mask;
    }
    string getMask()
    {
        return this -> Mask;
    }

    void showSupervisorDetails()
    {
        cout << getMask() << " " << getSurname() << " " << getCity() << " " << getMoney() << " " << getWeight() << endl;
    }
};

class Supervisors
{
private:
    Supervisor Superv[10];
    int NrofSup;

public:
    Supervisors() { NrofSup = 0;}

    void addSupervisor(string name, string surname, string city, string mask)
    {
        Superv[NrofSup].setName(name);
        Superv[NrofSup].setSurname(surname);
        Superv[NrofSup].setCity(city);
        Superv[NrofSup].setWeight();
        Superv[NrofSup].setMoney();
        Superv[NrofSup].setMask(mask);

        NrofSup++;
    }

     void showSupervDetails()
    {
        for(int i = 0; i < NrofSup; i++)
            Superv[i].showSupervisorDetails();
    }

};

class Players
{
private:
    Player Competitors[102];
    int NrofComp;

public:
    Players() { NrofComp = 1; }

    void addPlayer(string name, string surname, string city, int nr)
    {
        Competitors[NrofComp].setName(name);
        Competitors[NrofComp].setSurname(surname);
        Competitors[NrofComp].setCity(city);
        Competitors[NrofComp].setWeight();
        Competitors[NrofComp].setMoney();
        Competitors[NrofComp].setNumber(nr);

        NrofComp++;
    }

    void showPeopleDetails()
    {
        for(int i = 1; i < NrofComp; i++)
            if (!Competitors[i].hasBeenEliminated())
                Competitors[i].showPlayerDetails();
    }

    int getWeightByIndex (int index)
    {
        return Competitors[index].getWeight();
    }

    string getCompetitorName (int number)
    {
        return Competitors[number].getFullName();
    }

    void eliminatePlayer(int number)
    {
        Competitors[number].getsEliminated();
    }

    int getMoneyOwedByIndex(int number)
    {
        return Competitors[number].getMoney();
    }

    int getBigPrize()
    {
        unsigned long int BigPrize = 0;
        for (int i = 1; i < NrofComp; i++ )
            BigPrize = BigPrize + getMoneyOwedByIndex(i);

        return BigPrize;
    }

};

Players PlayerList;
Supervisors SupervisorList;
vector <int> PlayerNumbers;
vector <vector<int>> Teams (4, vector<int>(12));

void RedLightGreenLight()
{
    for ( int i = 2; i < 100; i = i+2 )
        PlayerList.eliminatePlayer(i);

    for ( int i = 97; i >= 0; i = i-2 )
        PlayerNumbers.erase(PlayerNumbers.begin() + i);

    cout << endl << endl << "Players after the first game were eliminated!" << endl << endl << "Players which continues the game:"<< endl << endl;

        PlayerList.showPeopleDetails();
}

void TugOfWar ()
{
     int NumberAvailable = PlayerNumbers.size();

     for ( int i = 0; i < 4; i++)
        for ( int j = 0; j < 12; j++)
            {
             int PlayerNumber = rand() % NumberAvailable;
             Teams[i][j] =  PlayerNumbers[PlayerNumber];
             PlayerNumbers.erase(PlayerNumbers.begin() + PlayerNumber);
             NumberAvailable-- ;
            }

     int WeightTeam1 = 0;
     int WeightTeam2 = 0;
     int WeightTeam3 = 0;
     int WeightTeam4 = 0;

     for ( int i = 0; i < 12; i++)
        {
         int PersonWeightTeam1 = PlayerList.getWeightByIndex(Teams[0][i]);
         int PersonWeightTeam3 = PlayerList.getWeightByIndex(Teams[2][i]);

         WeightTeam1 +=  PersonWeightTeam1;
         WeightTeam3 +=  PersonWeightTeam3;
        }

     if (WeightTeam1 > WeightTeam3)
         for ( int i = 0; i < 12; i++)
            {
            PlayerList.eliminatePlayer(Teams[2][i]);
            PlayerNumbers.push_back(Teams[0][i]);
            }

     else
         for ( int i = 0; i < 12; i++)
            {
            PlayerList.eliminatePlayer(Teams[0][i]);
            PlayerNumbers.push_back(Teams[2][i]);
            }

     for ( int i = 0; i < 12; i++)
        {
         int PersonWeightTeam2 = PlayerList.getWeightByIndex(Teams[1][i]);
         int PersonWeightTeam4 = PlayerList.getWeightByIndex(Teams[3][i]);

         WeightTeam2 +=  PersonWeightTeam2;
         WeightTeam4 +=  PersonWeightTeam4;
        }

     if (WeightTeam2 > WeightTeam4)
         for ( int i = 0; i < 12; i++)
            {
            PlayerList.eliminatePlayer(Teams[3][i]);
            PlayerNumbers.push_back(Teams[1][i]);
            }

     else
         for ( int i = 0; i < 12; i++)
            {
            PlayerList.eliminatePlayer(Teams[1][i]);
            PlayerNumbers.push_back(Teams[3][i]);
            }


     cout << endl << endl << "Players after the second game were eliminated!" << endl << endl << "Players which continue the game:"<< endl << endl;

     PlayerList.showPeopleDetails();
}

void Marbles ()
{

    int NumberAvailable = PlayerNumbers.size();

    srand(time(NULL));

    for (int i = 0; i < NumberAvailable/2; i++)
        {
         int Player1Roll = rand () % 15 + 1;
         int Player2Roll = rand () % 15 + 1;

         while (Player1Roll == Player2Roll)
            {
             int Player1Roll = rand () % 15 + 1;
             int Player2Roll = rand () % 15 + 1;
            }

         if (Player1Roll < Player2Roll)
            {
            PlayerList.eliminatePlayer(PlayerNumbers[NumberAvailable/2 + i]);
            PlayerNumbers[NumberAvailable/2 + i] = 0;
            }

         else
            {
            PlayerList.eliminatePlayer(PlayerNumbers[i]);
            PlayerNumbers[i] = 0;
            }

        }

     for(int i = PlayerNumbers.size(); i >= 0; i--)
        if(PlayerNumbers[i] == 0)
            PlayerNumbers.erase(PlayerNumbers.begin() + i);


    cout << endl << endl << "Players after the third game were eliminated!" << endl << endl << "Players which continue the game:"<< endl << endl;

    PlayerList.showPeopleDetails();
}

void Genken()
{
   int Selection[13]={0};

   for(int i = 12; i > 0; i--)
     {

     do
     {
     Selection[i] = rand () % 3 + 1;
     Selection[i-1] = rand () % 3 + 1;
     }while (Selection[i] == Selection[i-1]);

     if(Selection[i] == 1 && Selection[i-1] == 2)
       {
            PlayerList.eliminatePlayer(PlayerNumbers[i]);
            PlayerNumbers.erase(PlayerNumbers.begin() + i);
       }

     if(Selection[i] == 1 && Selection[i-1] == 3)
        {
            PlayerList.eliminatePlayer(PlayerNumbers[i-1]);
            PlayerNumbers.erase(PlayerNumbers.begin() + (i-1));
        }

     if(Selection[i] == 2 && Selection[i-1] == 1)
        {
            PlayerList.eliminatePlayer(PlayerNumbers[i-1]);
            PlayerNumbers.erase(PlayerNumbers.begin() + (i-1));
        }

     if(Selection[i] == 2 && Selection[i-1] == 3)
        {
            PlayerList.eliminatePlayer(PlayerNumbers[i]);
            PlayerNumbers.erase(PlayerNumbers.begin() + i);
        }

     if(Selection[i] == 3 && Selection[i-1] == 1)
        {
            PlayerList.eliminatePlayer(PlayerNumbers[i]);
            PlayerNumbers.erase(PlayerNumbers.begin() + i);
        }

     if(Selection[i] == 3 && Selection[i-1] == 2)
        {
            PlayerList.eliminatePlayer(PlayerNumbers[i-1]);
            PlayerNumbers.erase(PlayerNumbers.begin() + (i-1));
        }

     }


   cout << endl << endl << "Players after the fourth game were eliminated!" << endl << endl << "The winner is:"<< endl << endl;

   PlayerList.showPeopleDetails();
}

struct Winner
{
  string Name;
  long int Prize;
};

bool comparator (Winner n1, Winner n2)
    {
    return (n1.Prize > n2.Prize);
    }

void Earnings()
{
   vector <Winner> Winners;

   Winner w;

   w.Name = PlayerList.getCompetitorName(PlayerNumbers[0]);
   w.Prize = PlayerList.getBigPrize();

   Winners.push_back(w);

        cout << endl;
        cout << w.Name << " won " << w.Prize << "\n";

}

int main()
{
    vector<string>name;
    vector<string>surname;
    vector<string>city;
    vector<string>number;
    string line, word;


    for (int i = 1; i < 100; i++)
        PlayerNumbers.push_back(i);

    fstream file("informatie.csv", ios::in);

    getline(file, line);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream str(line);

            getline(str,word,',');
            number.push_back(word);

            getline(str,word,',');
            name.push_back(word);

            getline(str,word,',');
            surname.push_back(word);

            getline(str,word,',');
            city.push_back(word);

        }
    }
    else
        cout << "Could not open the file\n";

    srand(time(NULL));
    int PlayersRemaining = 108;

    for(int i=0; i < 99; i++)
    {
        int random_nr = rand() % PlayersRemaining;

        PlayerList.addPlayer(name[random_nr], surname[random_nr], city[random_nr], i+1);
        name.erase(name.begin() + random_nr);
        surname.erase(surname.begin() + random_nr);
        city.erase(city.begin() + random_nr);
        PlayersRemaining--;

    }
    cout << endl;
    cout << "The participants are:" << endl << endl;
        PlayerList.showPeopleDetails();

    string Mask_types[] = { "square", "triangle", "circle" };

    for( int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            int random_nr = rand() % PlayersRemaining;

            SupervisorList.addSupervisor(name[random_nr], surname[random_nr], city[random_nr], Mask_types[j]);
            name.erase(name.begin() + random_nr);
            surname.erase(surname.begin() + random_nr);
            city.erase(city.begin() + random_nr);
            PlayersRemaining --;
        }
    }
    cout << endl;
    cout << "The supervisors are: " << endl << endl;
    SupervisorList.showSupervDetails();

    RedLightGreenLight();

    TugOfWar();

    Marbles();

    Genken();

    Earnings();

    return 0;
}
