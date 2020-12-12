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
#include <math.h>

using namespace std;

int ship_pos[] = { 0, 0 }; //x, y
int way_pos[] = { 10, 1 };
int direction = 0; //0 E, 1 S, 2 W, 3, N


void rotate(int degrees) {
	int result[2];

	double angle = degrees * ((atan(1) * 4) / 180);

	int c = cos(angle);
	int s = sin(angle);

	result[0] = (way_pos[0] * c) - (way_pos[1] * s);
	result[1] = (way_pos[1] * c) + (way_pos[0] * s);

	way_pos[0] = result[0];
	way_pos[1] = result[1];
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_12.txt");

	stringstream buffer;
	buffer << input.rdbuf();
	istringstream is(buffer.str());

	string x;

	vector<pair<char, int>> instructions;

	while (is >> x) 
		instructions.push_back(pair<char, int>(x[0], stoi(x.substr(1, x.length()))));
	

	for (pair<char, int> p : instructions) {

		if (p.first == 'F') {
			ship_pos[0] += p.second * way_pos[0];
			ship_pos[1] += p.second * way_pos[1];
		}
		else if (p.first == 'N') way_pos[1] += p.second;
		else if (p.first == 'E') way_pos[0] += p.second;
		else if (p.first == 'S') way_pos[1] -= p.second;
		else if (p.first == 'W') way_pos[0] -= p.second;
		else if (p.first == 'L') rotate(p.second);
		else if (p.first == 'R') rotate(-1 * p.second);
		

	}

	cout << abs(ship_pos[0]) + abs(ship_pos[1]) << endl;
}

