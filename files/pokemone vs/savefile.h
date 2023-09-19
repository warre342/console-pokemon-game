#pragma once
#include <string>
#include <fstream>
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
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
//https://www.codeguru.com/cplusplus/an-introduction-to-object-serialization-in-c/
//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
using namespace std;
class saveFile {

private:
	string bestandsnaam1= "saveFile.txt";
	string bestandsnaam2= "saveFile2.txt";
	bool isSaved;
	Mc mc1;
	Mc mc2;
public:
	
	saveFile() {
		string data;
		ifstream infile;
		infile.open(bestandsnaam1);
		cout << "Reading from the file" << endl;
		string woord1, woord2, woord3, woord4;
		while (infile >> woord1 >> woord2 >> woord3>>woord4) {
			cout << woord1<<endl<<woord2<<endl<<woord3<<endl<<woord4;
		}
		infile.close();
	}
	//Mc restoreMc();
	//void saveMc();
};
