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

const int width = 91;
const int height = 90;

int seats[height][width];
int temp_seats[height][width];

bool change = false;

const int y[] = { -1, -1, -1,  1, 1, 1,  0, 0 };// 8 shifts to neighbors
const int x[] = { -1,  0,  1, -1, 0, 1, -1, 1 };// used in functions 

bool inField(int c, int r) {
	if (r < 0 || r >= width) return false;
	if (c < 0 || c >= height) return false;
	return true;
}

vector<int> get_neighbours(int c, int r) {
	vector<int> result(3);

	for (int i = 0; i < 8; ++i) {
		if (inField(c + y[i], r + x[i])) {
			int add = 1;
			while (true) {		
				int seat = seats[c + (add * y[i])][r + (add * x[i])];
				if (seat != 0) {
					result[seat]++;
					break;
				}
				else add++;	
				
				if(!inField(c + (add * y[i]), r + (add * x[i]))) break;
			}	
		}	
	}
	return result;
}

int get_new_value(int c, int r) {
	vector<int> neigh = get_neighbours(c, r);

	if (seats[c][r] == 1 && neigh[2] == 0) { change = true; return 2; }
	if (seats[c][r] == 2 && neigh[2] >= 5) { change = true; return 1; }
	
	return seats[c][r];
}


void iterate() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (seats[i][j] == 0) temp_seats[i][j] = 0;
			else temp_seats[i][j] = get_new_value(i, j);
		}
	}

	copy(&temp_seats[0][0], &temp_seats[0][0] + width * height, &seats[0][0]);
}

void print_seats() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << seats[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_11.txt");

	string x;
	int h = 0;

	if (input.is_open()) {

		while (getline(input, x)) {
			for (int i = 0; i < x.length(); i++) {
				if (x[i] == 'L') seats[h][i] = 1;
				else seats[h][i] = 0;
			}
			h++;
		}
	}

	auto start = chrono::high_resolution_clock::now();
	//print_seats();

	do {
		change = false;
		iterate();	
	} while (change);

	//print_seats();


	int result = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (seats[i][j] == 2) result++;
		}
	}
	cout << result << endl;

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << "Time(us): " << duration.count() << endl;

}