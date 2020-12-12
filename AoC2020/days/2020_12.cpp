#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>

using namespace std;

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_12.txt");

	stringstream buffer;
	buffer << input.rdbuf();
	istringstream is(buffer.str());

	string x;

	vector<pair<char, int>> instructions;

	while (is >> x) 
		instructions.push_back(pair<char, int>(x[0], stoi(x.substr(1, x.length()))));
	

	int pos[] = { 0, 0 }; //x, y
	int direction = 0; //0 E, 1 S, 2 W, 3, N

	for (pair<char, int> p : instructions) {

		if (p.first == 'F') {
			switch (direction) {
				case 0:
					pos[0] += p.second;
					break;
				case 1:
					pos[1] -= p.second;
					break;
				case 2:
					pos[0] -= p.second;
					break;
				case 3:
					pos[1] += p.second;
					break;
			}
		}
		else if (p.first == 'N') pos[1] += p.second;
		else if (p.first == 'E') pos[0] += p.second;
		else if (p.first == 'S') pos[1] -= p.second;
		else if (p.first == 'W') pos[0] -= p.second;
		else if (p.first == 'L') direction = (((size_t) direction - (p.second/90) ) % 4);
		else if (p.first == 'R') direction = (((size_t)direction + (p.second / 90)) % 4);;
				
	}

	cout << abs(pos[0]) + abs(pos[1]) << endl;
}

