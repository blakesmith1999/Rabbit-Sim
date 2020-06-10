#ifndef Bunny_h
#define Bunny_h

#include <iostream>
#include <string>

class Bunny {
private:
	char sex;
	int age;
	std::string color;
	std::string name;
	bool radioactive_mutant_vampire_bunny;

public:
	Bunny();
	void set_sex(int);
	void set_age(int);
	void set_color(int);
	void set_name(std::string);
	void set_mutant(int);
	char get_sex();
	int get_age();
	std::string get_color();
	std::string get_name();
	std::string get_mutant();

};

Bunny::Bunny() {
	sex = 'n';
	age = 0;
	color = "uninitialized";
	name = "uninitialized";
	radioactive_mutant_vampire_bunny = 0;
}
void Bunny::set_sex(int s) {
	switch (s) {
	case 0: sex = 'm';
		break;
	case 1: sex = 'f';
		break;
	case 3: sex = 'n';
		break;
	}
}

void Bunny::set_age(int a) {
	age = a;
}

void Bunny::set_color(int c) {
	switch (c) {
	case 0: color = "white";
		break;
	case 1: color = "brown";
		break;
	case 2: color = "black";
		break;
	case 3: color = "spotted";
		break;
	}
}

void Bunny::set_name(std::string n) {
	name = n;
}

void Bunny::set_mutant(int m) {
	if (m >= 2) {
		radioactive_mutant_vampire_bunny = false;
	}
	else {
		radioactive_mutant_vampire_bunny = true;
	}
}

char Bunny::get_sex() {
	return sex;
}

int Bunny::get_age() {
	return age;
}

std::string Bunny::get_color() {
	return color;
}

std::string Bunny::get_name() {
	return name;
}

std::string Bunny::get_mutant() {
	if (radioactive_mutant_vampire_bunny)
		return "true";
	else
		return "false";
}

#endif
