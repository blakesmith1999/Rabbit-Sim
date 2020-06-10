#include "Bunny.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>


void new_rabbit(int, Bunny[], std::vector<std::string>, std::vector<std::string>);
void game(std::vector<std::string>, std::vector<std::string>, Bunny[]);
void name_generator(std::vector<std::string>&, std::vector<std::string>&);
std::string new_name(char, std::vector<std::string>, std::vector<std::string>);
void cull(Bunny[], int&, int&);
void write_to_file(Bunny[], std::ofstream);


int main() {
	srand(time(NULL));

	std::vector<std::string> male_names;
	std::vector<std::string> female_names;
	Bunny rabbits[1000];


	game(male_names, female_names, rabbits);
	system("pause");
}

void game(std::vector<std::string> male_names, std::vector<std::string>female_names, Bunny rabbits[]) {
	name_generator(male_names, female_names);
	new_rabbit(10, rabbits, male_names, female_names);
	int counter = 0, deaths = 0;
	//char input;
	std::ofstream stats;
	stats.open("stats.txt");
	do {
		int male_count = 0, female_count = 0, age = 0, total = 0, dead = 0, mutant = 0;
		//std::cout << "\n\n\t\tRound " << counter << std::endl;
		stats << std::endl << "Round " << counter << std::endl;
		for (int i = 0; i < 1000; i++) {
			if (rabbits[i].get_age() != 0) {
				/*
				Bypassing speeds processing
				std::cout << rabbits[i].get_name() << "\t" << std::endl;
				std::cout << "Sex: " << rabbits[i].get_sex() << " | ";
				std::cout << "Age: " << rabbits[i].get_age() << " | ";
				std::cout << "Color: " << rabbits[i].get_color() << " | ";
				std::cout << "Mutant: " << rabbits[i].get_mutant() << std::endl;
				std::cout << std::endl << std::endl;
				*/
				stats << rabbits[i].get_name() << std::endl;
				stats << rabbits[i].get_sex() << std::endl;
				stats << rabbits[i].get_age() << std::endl;
				stats << rabbits[i].get_color() << std::endl;
				stats << rabbits[i].get_mutant() << std::endl;
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
			std::cout << "GAME OVER" << std::endl;
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

		std::cout << "Total: " << total << std::endl;
		std::cout << "Deaths: " << deaths << std::endl;
		std::cout << "Mutants: " << mutant << std::endl;
		std::cout << "Male: " << male_count << std::endl;
		std::cout << "Female: " << female_count << std::endl;
		*/
		counter++;


		//system("pause");
	} while (counter < 20);
	stats.close();
	std::cout << "Simulation Finished" << std::endl;
}

std::string new_name(char s, std::vector<std::string> male_names, std::vector<std::string> female_names) {
	if (s == 'm') {
		return male_names.at(rand() % 50);
	}
	else {
		return female_names.at(rand() % 50);
	}
}

void name_generator(std::vector<std::string>& male_names, std::vector<std::string>& female_names) {
	std::ifstream male, female;

	male.open("male.txt");
	for (std::string name; getline(male, name);) {
		male_names.push_back(move(name));
	}
	female.open("female.txt");
	for (std::string name; getline(female, name);) {
		female_names.push_back(move(name));
	}
	male.close();
	female.close();
}

void new_rabbit(int n, Bunny rabbits[], std::vector<std::string> male_names, std::vector<std::string> female_names) {

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
