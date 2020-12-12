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

	char x;
	int value;

	while (input >> x >> value){

		if (x == 'F') {
			ship_pos[0] += value * way_pos[0];
			ship_pos[1] += value * way_pos[1];
		}
		else if (x == 'N') way_pos[1] += value;
		else if (x == 'E') way_pos[0] += value;
		else if (x == 'S') way_pos[1] -= value;
		else if (x == 'W') way_pos[0] -= value;
		else if (x == 'L') rotate(value);
		else if (x == 'R') rotate(-1 * value);
	
	}

	cout << abs(ship_pos[0]) + abs(ship_pos[1]) << endl;
}

