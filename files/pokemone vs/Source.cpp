
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
#include "Mc.h"
#include "screenclear.h"
#include "savefile.h"
using namespace std;

// game over exception
class game_over_exception : public runtime_error
{
public:
    game_over_exception() : runtime_error("Een pokemon heeft je brutaal vermoord") {}
    game_over_exception(const string &what) : runtime_error(what) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void adventure_ui(Mc &test)
{
    screenClearSingleton& singleton = screenClearSingleton::instance();
    singleton.clearScreen();

    string woord;
    int stage;

    int optie; // weglopen (1) of switch pokemon (2)
    cout << "Het doel van dit spel is om alle checkpoints te unlucken. Je hebt er " << test.getStage_unlocked() << " unlocked." << endl;
    cout << "kies een checkpoint (er zijn 1-5 checkpoints): ";
    cin >> stage;

    while (stage > test.getStage_unlocked() || stage == 0)
    {
        cout << "Dit checkpoint is nog niet unlocked voor jou. Voer een nieuwe in: ";
        cin >> stage;
    }

    test.setStage(stage);

    cout << "you start exploring. " << endl;
    while (woord != "N")
    {
        //  type is tegenstander en winaar uitkomst eerste gevecht

        unique_ptr<Pokemon> wilde_pokemon = test.encounter(stage); // automatisch geen type
        if (wilde_pokemon->get_naam() == "dummy")                  // niks gebeurt
        {
            cout << "Je hebt niks gevonden" << endl;
            cout << "continue? Y/N: ";
            cin >> woord;
            cout << endl;
            cin.ignore();
        }
        else
        {
            char winaar = test.getInventory().at(0)->battle(*wilde_pokemon);
            // winaar a als this heeft gewonnen, b als b heeft gewonnen, c als niemand heeft gewonnen
            if (winaar == 'a')
            {
                test.catch_pokemon(move(wilde_pokemon));
                cout << "continue? Y/N: ";
                cin >> woord;
                cin.ignore();
                cout << endl;
            }
            else if (winaar == 'c')
            {
                unique_ptr<Pokemon> temp = move(test.getInventory().at(0));
                test.getInventory().push_back(move(temp));

                test.getInventory().erase(test.getInventory().begin());
                if (test.getAmount_alive() == 0)
                {
                    cout << endl
                         << "je hebt geen pokemons meer! Gelukkig kan je nog terugkeren zonder probleem." << endl;
                    woord = "N";
                }
                else
                {
                    cout << "continue? Y/N: ";
                    cin >> woord;
                    cin.ignore();
                    cout << endl;
                }
            }
            else if (winaar == 'b')
            {

                cout << "Wil je proberen weglopen(1) of een andere pokemon(2) kiezen?" << endl;
                cin >> optie;
                while (optie != 1 && optie != 2) // userinput
                {
                    cin >> optie;
                }
                cin.ignore();
                if (optie == 1)
                {
                    int kans_run = 0;
                    while (kans_run != 1)
                    {
                        kans_run = rand() % 3;
                        cout << "Lopen is niet gelukt" << endl
                             << "--Het volgende gevecht start!--" << endl;
                        int teller = 404;

                        for (int i = test.getInventory().size() - 1; i > -1; i--)
                        {
                            if (test.getInventory().at(i)->get_hp() != 0)
                            {
                                teller = i;
                            }
                        }
                        try
                        {
                            winaar = test.getInventory().at(teller)->battle(*wilde_pokemon);
                        }
                        catch (const out_of_range &e)
                        {
                            cout << "Je hebt geen pokemons meer!" << endl;
                            cout << "GAME OVER";
                            throw game_over_exception();
                        }
                    }
                    cout << "je bent succesvol ontsnapt!" << endl
                         << "je keert nu terug."
                         << endl;
                    woord = "N";  // break
                    winaar = 'o'; // break
                }
                else if (optie == 2)
                {
                    while (winaar == 'b')
                    {
                        if (test.getAmount_alive() == 0)
                        {
                            cout << "Je hebt geen pokemons meer!" << endl;
                            cout << "GAME OVER";
                            throw game_over_exception();
                        }
                        int gekozen_pokemon;
                        test.showInventory();
                        cout << "Welke pokemon wil je kiezen? (nummer)" << endl;
                        cin >> gekozen_pokemon;
                        while ((test.getInventory().at(gekozen_pokemon - 1)->get_hp() == 0) || !(gekozen_pokemon > 0 || gekozen_pokemon < test.getInventory().size())) // error geeft geen optie voor Y/N na beide flauw kan encounter starten zonder pokemn met hp
                        {
                            cout << "Dit is geen mogelijke pokemon, kies opnieuw" << endl;
                            cin >> gekozen_pokemon;
                            cin.ignore();
                        }

                        winaar = test.getInventory().at(gekozen_pokemon - 1)->battle(*wilde_pokemon);
                    }
                    if (winaar == 'a')
                    {
                        test.catch_pokemon(move(wilde_pokemon));
                        cout << "continue? Y/N: ";
                        cin >> woord;
                        cin.ignore();
                        cout << endl;
                    }
                    else if (winaar == 'c')
                    {
                        unique_ptr<Pokemon> temp = move(test.getInventory().at(0));
                        test.getInventory().push_back(move(temp));
                        test.getInventory().erase(test.getInventory().begin());
                        if (test.getAmount_alive() == 0)
                        {
                            cout << endl
                                 << "je hebt geen pokemons meer! Gelukkig kan je nog terugkeren zonder probleem." << endl;
                            woord = "N";
                        }
                        else
                        {
                            cout << "continue? Y/N: ";
                            cin >> woord;
                            cin.ignore();
                            cout << endl;
                        }
                    }
                }
            }
        }
    }
    cout << "press enter to continue: " << endl;
    cin.ignore();
    singleton.clearScreen(); 
}

void inventory_ui(Mc &test)
{

    string woord;
    while (woord != "ESCAPE")
    {
        test.showInventory();
        cout << "je opties zijn NAME CHANGE, CHANGE ORDER en ESCAPE:  ";
        getline(cin, woord);
        if (woord == "NAME CHANGE")
        {
            try
            {
                int gekozen_pokemon;
                cout << "welke pokemon wil je veranderen (nummer):  ";
                cin >> gekozen_pokemon;
                Pokemon &chosen = *(test.getInventory().at(gekozen_pokemon - 1));
                chosen.geef_naam();
            }
            catch (const out_of_range &e) // checken of inventory niet out of range
            {
                cout << "je hebt maar " << test.getInventory().size() << " pokemon(s)." << endl;
                cin.ignore();
            }
        }
        else if (woord == "CHANGE ORDER")
        {
            try
            {
                int getal;
                cout << "Geef de pokemon die je wilt verzetten naar plek 1: ";
                cin >> getal;
                cin.ignore();
                test.getInventory()[0].swap(test.getInventory()[getal - 1]);
            }
            catch (const out_of_range &e) // checken of inventory niet out of range
            {
                cout << "je hebt maar " << test.getInventory().size() << " pokemon(s)." << endl;
            }
        }
        // cout << "naam: " << chosen.get_naam() << "soort: " << chosen.get_soort(); // test voor
    }
    screenClearSingleton& singleton = screenClearSingleton::instance();
    singleton.clearScreen();
}
void heal_pokemons(Mc &test)
{
    cout << endl;
    for (auto &i : test.getInventory())
    {
        cout << "ta ta ta... " << i->get_naam() << " been healed!" << endl;
        i->setHp(i->get_hp_max());
    }
    cout << endl;
    cout << "press enter to continue: " << endl;
    cin.ignore();

    screenClearSingleton& singleton = screenClearSingleton::instance();
    singleton.clearScreen();
}
void merge_pokemons() {
    string woord; 
    while (woord != "ESCAPE") {
        string woord2;
        cout << "je opties zijn MERGE, ESCAPE"<<endl;
        cin >> woord;
    
    }

}

void start() // main programma
{
    screenClearSingleton& singleton = screenClearSingleton::instance();
    singleton.setUp();
    
    cout << endl;
    singleton.clearScreen();
    for (int i = 0; i < 5; i++)
    {
        cout << "//////////////////////////////////////////////";
    }
    cout << endl;
    Mc test;
    string woord;

    while (woord != "END GAME")
    {
        cout << "je opties zijn ADVENTURE, INVENTORY, HEAL POKEMONS, en END GAME: ";

        getline(cin, woord);

        if (woord == "ADVENTURE")
        {
            adventure_ui(test);
        }
        else if (woord == "INVENTORY")
        {
            inventory_ui(test);
        }
        else if (woord == "HEAL POKEMONS")
        {
            heal_pokemons(test);
        }
    }
}

int main()
{
    //Mc test;
    //saveFile saver;

    
    try
    {
        start();
    }
    catch (const game_over_exception &e)
    {
        return 0;
    }
    
    
    //Legendary defa;
    //cout<<defa.getNextEvolution();
    

}
// errors:
//  geen
// TO DO:
// bossfight/ events, evolutions (pokemons combinen) , level up: override methode ++( pokemon object), story (mss inlezen uit txt)
// save file, opties tussen save files, game minder moeilijk maken, mss hardcore versie en niet hardcore
//gui met ai generated images