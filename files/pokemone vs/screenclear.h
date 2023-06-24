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


class screenClearSingleton {

private:
	bool aan;
	screenClearSingleton() {};
	//string test;
public:
	static screenClearSingleton& instance()
	{
		static screenClearSingleton INSTANCE;
		return INSTANCE;
	}
	
	void zetAan() { aan = true; }
	void zetAf() { aan = false; }

	//string tester() { return test; }

	void clearScreen() {
		if (aan) {
			system("cls");
		}
	}

	void setUp() {
		string input;
		cout << "Wil je clearScrean aanzetten? Als je niet op een linux terminal zit dan kan dit een error geven. De visual studio terminal is een linux terminal" << endl<<"y/n"<<endl;
		cin >> input;
		//cout << "input gegeven was " << input << endl;
		cin.ignore();
		while (input != "y" && input != "n") {
			cout << "Je gaf niet de verwachte input in, probeer het opnieuw"<<endl;
			cin >> input;
			cin.ignore();
		}
		if (input == "y") {
			zetAan();
		}
		else if(input=="n") {
			zetAf();
		}
		else {
			cout << "logische error waardoor onverwachte input";
		}
		//test = input;
	}
};
