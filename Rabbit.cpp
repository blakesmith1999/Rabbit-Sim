#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Bunny.h"

using namespace std;

void new_rabbit(int, Bunny[], vector<string>, vector<string>);
void game(vector<string>, vector<string>, Bunny[]);
void name_generator(vector<string>&, vector<string>&);
string new_name(char, vector<string>, vector<string>);
void cull(Bunny[], int&, int&);
void write_to_file(Bunny[], ofstream);


int main() {
	srand(time(NULL));

	vector<string> male_names;
	vector<string> female_names;
	Bunny rabbits[1000];


	game(male_names, female_names, rabbits);
	system("pause");
}

void game(vector<string> male_names, vector<string>female_names, Bunny rabbits[]) {
	name_generator(male_names, female_names);
	new_rabbit(10, rabbits, male_names, female_names);
	int counter = 0, deaths = 0;
	//char input;
	ofstream stats;
	stats.open("stats.txt");
	do {
		int male_count = 0, female_count = 0, age = 0, total = 0, dead = 0, mutant = 0;
		//cout << "\n\n\t\tRound " << counter << endl;
		stats << endl << "Round " << counter << endl;
		for (int i = 0; i < 1000; i++) {
			if (rabbits[i].get_age() != 0) {
				/*
				cout << rabbits[i].get_name() << "\t" << endl;
				cout << "Sex: " << rabbits[i].get_sex() << " | ";
				cout << "Age: " << rabbits[i].get_age() << " | ";
				cout << "Color: " << rabbits[i].get_color() << " | ";
				cout << "Mutant: " << rabbits[i].get_mutant() << endl;
				cout << endl << endl;
				*/
				stats << rabbits[i].get_name() << endl;
				stats << rabbits[i].get_sex() << endl;
				stats << rabbits[i].get_age() << endl;
				stats << rabbits[i].get_color() << endl;
				stats << rabbits[i].get_mutant() << endl;
				total++;

				if (rabbits[i].get_sex() == 'm') {
					male_count++;
				}
				else if (rabbits[i].get_sex() == 'f') {
					female_count++;
				}
				else {
					mutant++;
				}
				age = rabbits[i].get_age();
				rabbits[i].set_age(++age);
				if ((rabbits[i].get_mutant() == "false") && (rabbits[i].get_age() > 9)) {
					rabbits[i].set_age(0);
					deaths++;
				}
				else if ((rabbits[i].get_mutant() == "true") && (rabbits[i].get_age() > 49)) {
					rabbits[i].set_age(0);
					deaths++;
				}
			}
			else {
				dead++;
			}
		}
		if ((male_count != 0)&&(dead>female_count)) {
			new_rabbit(female_count, rabbits, male_names, female_names);
		}
		else if ((male_count !=0)&&(dead<=female_count)) {
			new_rabbit(dead, rabbits, male_names, female_names);
			total += dead;
			cull(rabbits, total, deaths);
		}
		else if (male_count == 0) {
			cout << "GAME OVER" << endl;
			return;
		}
		/*
		//Doesn't work yet
		cin >> input;
		if (input == 'k') {
			cull(rabbits, total);
		}
		*/

		/*/  Speeds up the program writing directly to file

		cout << "Total: " << total << endl;
		cout << "Deaths: " << deaths << endl;
		cout << "Mutants: " << mutant << endl;
		cout << "Male: " << male_count << endl;
		cout << "Female: " << female_count << endl;
		*/
		counter++;


		//system("pause");
	} while (counter < 20);
	stats.close();
	cout << "Simulation Finished" << endl;
}

string new_name(char s, vector<string> male_names, vector<string> female_names) {
	if (s == 'm') {
		return male_names.at(rand() % 50);
	}
	else {
		return female_names.at(rand() % 50);
	}
}

void name_generator(vector<string>& male_names, vector<string>& female_names) {
	ifstream male, female;

	male.open("male.txt");
	for (string name; getline(male, name);) {
		male_names.push_back(move(name));
	}
	female.open("female.txt");
	for (string name; getline(female, name);) {
		female_names.push_back(move(name));
	}
	male.close();
	female.close();
}

void new_rabbit(int n, Bunny rabbits[], vector<string> male_names, vector<string> female_names) {

	for (int i = 0; i < n; i++) {
		int c, s, m;
		Bunny rabbit;
		for (int i = 0; i < 1000; i++) {

			if (rabbits[i].get_age() == 0) {

				c = rand() % 4;
				rabbits[i].set_color(c);

				s = rand() % 2;
				rabbits[i].set_sex(s);

				rabbits[i].set_name(new_name(rabbits[i].get_sex(), male_names, female_names));

				m = rand() % 100;
				rabbits[i].set_mutant(m);
				if (rabbits[i].get_mutant() == "true") {
					rabbits[i].set_sex(3);
				}

				rabbits[i].set_age(1);
				break;
			}

		}
	}
}

void cull(Bunny rabbits[], int &total, int &deaths) {
	int new_total = total;
	for (int i = 0; i < new_total/2;) {
		int random = rand() % 1000;
		if ((rabbits[random].get_age() != 0)&&(rabbits[random].get_mutant()=="false")) {
			rabbits[random].set_age(0);
			i++;
			deaths++;
			total--;
		}
		if (rabbits[random].get_mutant() == "true") {
			total--;
		}
	}

}
