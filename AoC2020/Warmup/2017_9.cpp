// AoC2020.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

int calculate_score(string input) {
	// { new group, push to stack, level up one
	 // } close last opened group, level down one
	 // , seperates groups on same level
	 // < opens garbage, then ignore any character that is not >
	 // > closes garbage
	 // ! ignore next character

	//cout << "Start: " << input << endl;

	int level = 0;
	int score = 0;
	int garbage = 0;


	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '!') {
			i++;
		}
		else if (input[i] == '<') {
			while (input[i] != '>') {
				if (input[i] == '!') 
					i += 2;
				else {
					i++;
					garbage++;
				}		
			}
			garbage--;
		}
		else if (input[i] == '{') {
			level++;
		}
		else if (input[i] == '}') {
			score += level;
			level--;
		}
	}

	cout << score << endl;
	return garbage;
}

int main() {
	cout << "2017 9" << endl;

	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\Warmup\\input\\day9_2017.txt");

	stringstream buffer;
	buffer << input.rdbuf();

	cout << "Removed garbage:" << calculate_score(buffer.str()) << endl;;

	/*
	calculate_score("{}");
	calculate_score("{{{}}}");
	calculate_score("{{},{}}");
	calculate_score("{{{},{},{{}}}}");
	calculate_score("{<a>,<a>,<a>,<a>}");
	calculate_score("{{<ab>},{<ab>},{<ab>},{<ab>}}");
	calculate_score("{{<!!>},{<!!>},{<!!>},{<!!>}}");
	calculate_score("{{<a!>},{<a!>},{<a!>},{<ab>}}");
	*/

}

