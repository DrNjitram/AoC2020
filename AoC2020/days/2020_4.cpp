#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <iterator>


using namespace std;

regex height_rule("(\\d+)(in|cm)"); 
regex hair_rule("#[0-9a-f]{6}");
regex eye_rule("(amb|blu|brn|gry|grn|hzl|oth)");
regex id_rule("([0-9]{9})");
smatch sm;


struct passport {
	string byr;
	string iyr;
	string eyr;
	string hgt;
	string hcl;
	string ecl;
	string pid;
	string cid;
};

template <class Container>
void split(const string& str, Container& cont, char delim = ' ')
{
	stringstream ss(str);
	string token;
	while (getline(ss, token, delim)) {
		cont.push_back(token);
	}
}

void parse_input(passport& pass, string input) {
	vector<string> values;
	split(input, values, ':');
	//cout << values[0] << "-" << values[1] << endl;
	if(values[0] == "byr") pass.byr = values[1];
	else if (values[0] == "iyr") pass.iyr = values[1];
	else if (values[0] == "eyr") pass.eyr = values[1];
	else if (values[0] == "hgt") pass.hgt = values[1];
	else if (values[0] == "hcl") pass.hcl = values[1];
	else if (values[0] == "ecl") pass.ecl = values[1];
	else if (values[0] == "pid") pass.pid = values[1];
	else if (values[0] == "cid") pass.cid = values[1];
}

void print_pass(passport pass, bool valid) {
	cout << pass.byr << ", "
		<< pass.iyr << ", "
		<< pass.eyr << ", "
		<< pass.hgt << ", "
		<< pass.hcl << ", "
		<< pass.ecl << ", "
		<< pass.pid << ", "
		<< pass.cid << ", " 
		<< valid << endl;
}

bool validity(passport pass) {
	if (pass.byr.length() * pass.iyr.length() * pass.eyr.length() * pass.hgt.length() * pass.hcl.length() * pass.ecl.length() * pass.pid.length() == 0) return 0;

	if (stoi(pass.byr) > 2002 || stoi(pass.byr) < 1920) return 0;
	if (stoi(pass.iyr) > 2020 || stoi(pass.iyr) < 2010) return 0;
	if (stoi(pass.eyr) > 2030 || stoi(pass.eyr) < 2020) return 0;

	regex_match(pass.hgt, sm, height_rule);
	if (sm.size() > 0) {
		if (sm[2] == "cm" && (stoi(sm[1]) > 193 || stoi(sm[1]) < 150)) return 0;
		else if (sm[2] == "in" && (stoi(sm[1]) > 76 || stoi(sm[1]) < 59)) return 0;
	}
	else {
		return 0;
	}

	regex_match(pass.hcl, sm, hair_rule);
	if (sm.size() == 0) return 0;

	regex_match(pass.ecl, sm, eye_rule);
	if (sm.size() == 0) return 0;

	regex_match(pass.pid, sm, id_rule);
	if (sm.size() == 0 || pass.pid.length() != 9) return 0;

	return 1;
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_4.txt");


	vector<passport> passports;
	string x;
	string substring;
	

	passport curr_pass;
	int valid = 0;

	if (input.is_open()) {
		while (getline(input, x)) {
			istringstream is(x);
			while (is >> substring) {
				parse_input(curr_pass, substring);
			}
			if (x == "") {
				passports.push_back(curr_pass);
				valid += validity(curr_pass);
				curr_pass = passport();
			}
		}
	}
	cout << valid << endl;
	cout << passports.size() << endl;

	//209 too low
}