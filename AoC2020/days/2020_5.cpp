#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;

int get_pos(string movements, char front, char front2) {
	int result = 0;

	for (char& c : movements) {
		result <<= 1;
		if (c == front || c == front2) result += 1;
	}

	return result;
}

int find_seat(set<int> seats) {
	for (int val : seats)
		if (seats.find(val + 1) == seats.end() &&
			seats.find(val + 2) != seats.end())
			return val + 1;

	return 0;
}


int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_5.txt");

	stringstream buffer;
	buffer << input.rdbuf();

	string x;
	int max = 0;
	set<int> seats;

	while (buffer >> x) {
		int result = get_pos(x, 'B', 'R');
		seats.insert(result);
		if (result > max) max = result;
	}

	cout << max << endl;
	cout << find_seat(seats) << endl;
}