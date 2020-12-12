#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <chrono>

using namespace std;

const int height = 323; //323
const int width = 31; //31

int find_trees(bool map[width][height], int angle_x, int angle_y) {
	int pos[2] = { 0, 0 };

	int trees = 0;
	while (pos[1] < height - 1) {
		pos[0] += angle_x;
		pos[1] += angle_y;

		trees += map[pos[0] % width][pos[1]];
	}
	return trees;
}

int main() {

	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_3.txt");

	bool map[width][height];

	string x;
	int row = 0;
	int col = 0;


	if (input.is_open()) {
		while (getline(input, x)) {
			row = 0;
			for (const char& c : x) {
				if (c == '#') map[row][col] = 1;
				else map[row][col] = 0;

				row++;
			}
			col++;
		}
	}

	auto start = chrono::high_resolution_clock::now();

	unsigned long long result1 = find_trees(map, 1, 1);
	unsigned long long result2 = find_trees(map, 3, 1);
	unsigned long long result3 = find_trees(map, 5, 1);
	unsigned long long result4 = find_trees(map, 7, 1);
	unsigned long long result5 = find_trees(map, 1, 2);

	auto stop = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << duration.count() << endl;

	
	cout << result1 << endl;
	cout << result2 << endl;
	cout << result3 << endl;
	cout << result4 << endl;
	cout << result5 << endl;
	

	unsigned long long result = result1 * result2 * result3 * result4 * result5;


	cout << result << endl;
}