#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <map>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <stdexcept>
#include <memory>
#include "Pokemon.h"
using namespace std;
class Mc
{
private:
    vector<unique_ptr<Pokemon>> inventory;
    int stage; // stage
    int stage_unlocked;
    string name; 

public:
    Mc(string name_="ash")
    {
        name = name_;
        srand(time(NULL));
        // default pokemon
        Common defa(8, 4);
        Common BRUH(20, 4);

        inventory.push_back(make_unique<Common>(defa));
        inventory.push_back(make_unique<Common>(BRUH));

        stage_unlocked = 1;
        stage = 1;

    }
    void showInventory(int page);
    void showInventory();
    void ga_dieper();
    unique_ptr<Pokemon> encounter(int stage); // c voor common, r voor rare, e voor epic, l voor legendary, n voor niks
    void boss_encounter(int stage);
    void catch_pokemon( unique_ptr<Pokemon> b);
    void intro(); // alle uitleg

    // getters
    vector<unique_ptr<Pokemon>>& getInventory() { return inventory; }
    int getStage_unlocked() { return stage_unlocked; }
    int getAmount_alive();
    // setters
    void setStage_unlocked(int stage) { stage_unlocked = stage; }
    void setStage(int stage_){stage=stage_;}
};

unique_ptr<Pokemon> Mc::encounter(int stage)
{
    static int count = 0;

    count++;
    if (count % 10 == 0)
    {
        stage_unlocked = (count / 10) + 1;
        cout << "Je hebt route " << stage_unlocked << " unlocked!" << endl;
    }

    int kans = rand() % (1000 /stage); // (1-5) gebieden, per gebied 10 encounters
    cout << endl;
    if ((kans <= 2) && stage > 3)
    {
        cout << "        --encounter " << count << "--" << endl;
        cout << "--A Legendary pokemon has apeared!--" << endl;
        return make_unique<Legendary>();
    }
    else if ((kans > 2 && kans <= 40) && stage > 2)
    {
        cout << "      --encounter " << count << "--" << endl;
        cout << "--A epic pokemon has apeared!--" << endl;
        return make_unique<Epic>();
    }
    else if ((kans > 40 && kans <= 100)&&stage>1)
    {
        cout << "     --encounter " << count << "--" << endl;
        cout << "--A rare pokemon has apeared--" << endl;
        return make_unique<Rare>();
    }
    else if (kans > 100 && kans <= 800)
    {
        cout << "      --encounter " << count << "--" << endl;
        cout << "--A common pokemon has apeared--" << endl;
        return make_unique<Common>();
    }
    return make_unique<Pokemon>();
    

}
void Mc::showInventory()
{
    cout << endl;
    for (int i = 0; i < inventory.size(); i++)
    {
        cout << "Pokemon " << i + 1 << ": " << endl;
        cout << *(inventory[i]);
    }
    cout << endl;

}

void Mc::showInventory(int page) {}
void Mc::ga_dieper() {}
void Mc::catch_pokemon( unique_ptr<Pokemon> b)
{
    string woord;
    int kans;
    cout << "The wild pokemon has fainted! Wil je " << b->get_naam() << " vangen? Y/N" << endl;
    cin >> woord;
    while (woord != "Y" && woord != "N")
    {
        cin >> woord;
    }

    if (woord == "Y")
    {
        cout << "You throw a pokeball. " << endl;
        for (int i = 3; i > 0; i--)
        {
            kans = rand() % 3;
            if (kans == 1)
            {
                cout << "wiggle.. wiggle.. wiggle.. CATCH! " << b->get_naam() << " has been caught!" << endl;
                inventory.push_back(move(b));
                break;
            }
            else
            {
                cout << "wiggle.. wiggle.. wiggle.. BOOM " << b->get_naam() << " escaped the pokeball!" << endl;
                cout << "You try again." << endl;
                if (i == 1)
                {
                    cout << b->get_naam() << " ran away." << endl;
                }
            }
        }
    }
    cin.ignore();
}
int Mc::getAmount_alive()
{
    int teller = 0;
    for (auto& i : inventory)
    {
        if ((*i).get_hp() > 0)
        {
            teller++;
        }
    }
    return teller;
}
