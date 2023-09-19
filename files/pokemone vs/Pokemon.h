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

using namespace std;
class Pokemon
{
private:
    string naam;
    string soort;
    int hp;
    int hp_max;
    int dmg;
    int evolution; // 0= geen, 1 , 2, 3 als 3 reset naar 1 en evolution
    int xp;        // pokemon++ overriden
    static vector<vector<string>> evo_namen;

public:
    Pokemon() : naam("dummy"), hp_max(5), hp(5), dmg(5), soort("obekend") {}
    Pokemon(string soort, int hpmax, int hp, int dmg) : soort(soort), naam(soort), hp_max(hpmax), hp(hp), dmg(dmg) {}
    Pokemon(string soort, int hpmax, int hp, int dmg, string naam) : soort(soort), naam(naam), hp_max(hpmax), hp(hp), dmg(dmg) {}
    //~Pokemon() { cout << naam << " has fainted!" << endl; }
    void geef_naam();        // met UI
    char battle(Pokemon &b); // return a als this heeft gewonnen, b als b heeft gewonnen, c als niemand heeft gewonnen
    string getNextEvolution();
    // friend functies
    friend void showInventory(int page); // nog niet gemaakt
    friend void showInventory();
    friend ostream &operator<<(ostream &uit, const Pokemon &a);
    // getters
    string get_naam() const { return naam; } // const en & toevoegen
    int get_hp_max() const { return hp_max; }
    int get_hp() const { return hp; }
    int get_dmg() const { return dmg; }
    string get_soort() const { return soort; }
    virtual string getZeldzaam() const { return "no type"; }

    // setters
    void setNaam(string naam_) { naam = naam_; }
    void setHp(int hp_) { hp = hp_; }
};
vector<vector<string>> Pokemon::evo_namen = {{"charmander", "charmeleon", "charizard"}, {"eevee", "vaporion", "null"}, {"dratini", "dragonair", "dragonite"}, {"magicarp", "temp", "gyarados"}};
void Pokemon::geef_naam() // naam veranderen met UI
{
    string set_naam;
    cout << "Geef hier de naam:  ";
    cin.ignore(); // cin callen voor getline geeft de \n door en dus skipt ie getline
    getline(cin, set_naam);
    setNaam(set_naam);
}
char Pokemon::battle(Pokemon &b)
{ // destructor pokemon maken
    cout << naam << " vs " << b.get_naam() << endl;
    int a_hp = hp;
    int b_hp = b.get_hp();
    int a_dmg = dmg;
    int b_dmg = b.get_dmg();
    string woord;

    while (a_hp > 0 && b_hp > 0)
    {
        a_hp -= b_dmg;

        b_hp -= a_dmg;
        cout << "hp: " << a_hp << "\t hp:" << b_hp << endl;
    }
    if (a_hp <= 0 && b_hp > 0)
    {
        b.setHp(b_hp);
        hp = 0;
        cout << "De wilde pokemon won het gevecht met " << b_hp << " hp!" << endl;
        return 'b';
        // cout << "wil je een andere pokemon kiezen? Y/N";
    }
    else if (b_hp <= 0 && a_hp > 0)
    {
        hp = a_hp;
        b.setHp(0);
        cout << "Jouw pokemon won het gevecht met " << a_hp << " hp!" << endl;
        return 'a';
    }
    else
    {

        cout << "Beide pokemon zijn flauw gevallen!" << endl;
        hp = 0;
        b.hp = 0;
        return 'c';
    }
    cout << endl;
}
string Pokemon::getNextEvolution()
{
    cout << "pokemon soort: " << soort << endl;
    int vecto = 0;
    int pokemons;
    for (auto &vectors : evo_namen)
    {
        pokemons = 0;
        for (auto &pokes : vectors)
        {
            if (pokes == soort)
            {
                if (pokemons == 2)//was 3
                {
                    cout << "deze pokemons kan niet meer evolueren " << endl;
                    return "null";
                }
                else
                {
                    cout << "nieuwe pokemon wordt " << evo_namen[vecto][pokemons + 1] << endl;
                    return evo_namen[vecto][pokemons + 1];
                }
            }
            pokemons++;
        }
        vecto++;
    }
    return "null"; 
}

ostream &operator<<(ostream &uit, const Pokemon &a)
{
    if (a.naam == a.soort)
    {
        uit << "Soort: " << a.soort << ", hp: " << a.hp << ", dmg: " << a.dmg << ", zeldzaamheid: " << a.getZeldzaam() << "." << endl;
    }
    else
    {
        uit << "Naam: " << a.naam << ", soort: " << a.soort << ", hp: " << a.hp << ", dmg: " << a.dmg << ", zeldzaamheid: " << a.getZeldzaam() << "." << endl;
    }
    return uit;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Common : public Pokemon
{
private:
    static vector<string> poke_namen_common;

public:
    Common() : Pokemon(poke_namen_common[rand() % poke_namen_common.size()], (rand() % 5) + 6, (rand() % 5) + 1, (rand() % 5) + 1) {}
    Common(int hp, int dmg) : Pokemon("charmander", hp, hp, dmg) {}
    string getZeldzaam() const override { return "Common"; }
};
vector<string> Common::poke_namen_common = {"meowth", "rattata", "charmander", "eevee", "zubat", "nidoran", "pidgey", "geodude", "ponyta", "dratini", "magicarp"}; // verschillende soorten types voor common
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Rare : public Pokemon
{
private:
    static vector<string> poke_namen_rare;

public:
    Rare() : Pokemon(poke_namen_rare[rand() % poke_namen_rare.size()], (rand() % 5) + 13, (rand() % 10) + 7, (rand() % 5) + 7) {}
    string getZeldzaam() const override { return "Rare"; }
};
vector<string> Rare::poke_namen_rare = {"snorlax", "vaporian", "charmeleon", "dragonair", "pikachu"};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Epic : public Pokemon
{
private:
    static vector<string> poke_namen_epic;

public:
    Epic() : Pokemon(poke_namen_epic[rand() % poke_namen_epic.size()], (rand() % 5) + 19, (rand() % 5) + 20, (rand() % 5) + 14) {}
    string getZeldzaam() const override { return "Epic"; }
};
vector<string> Epic::poke_namen_epic = {"gyarados", "dragonite", "charizard"};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Legendary : public Pokemon
{
private:
    static vector<string> poke_namen_legendary;

public:
    Legendary() : Pokemon(poke_namen_legendary[rand() % poke_namen_legendary.size()], (rand() % 5) + 36, (rand() % 10) + 30, (rand() % 5) + 30) {}
    string getZeldzaam() const override { return "Legendary"; }
};
vector<string> Legendary::poke_namen_legendary = {"mew"};