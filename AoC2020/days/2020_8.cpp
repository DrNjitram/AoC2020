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

vector<int> visits;
vector<int> instruction;
vector<int> arguments;

bool check_postion(int pos) {
	return visits[pos] == 0;
}

void zero_visits() {
	for (int i = 0; i < visits.size(); i++) {
		visits[i] = 0;
	}
}

pair<int, int> run_program() {
	zero_visits();
	int acc = 0;
	int instrpnt = 0;


	while (check_postion(instrpnt)) {
		visits[instrpnt]++;


		switch (instruction[instrpnt]) {
			case 0:
				acc += arguments[instrpnt];
				instrpnt++;
				break;
			case 1:
				instrpnt += arguments[instrpnt];
				break;
			case 2:
				instrpnt++;
			default:
				break;
		}

		if (instrpnt == instruction.size()) break;
	}

	return pair<int, int>(instrpnt, acc);
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_8.txt");

	stringstream buffer;
	buffer << input.rdbuf();
	istringstream is(buffer.str());

	string x;
	int n;

	while (is >> x) {
		if (x.compare("acc") == 0) {
			instruction.push_back(0);
		}
		else if (x.compare("jmp") == 0) {
			instruction.push_back(1);
		}
		else {
			instruction.push_back(2);
		} 
		is >> n;
		arguments.push_back(n);
		visits.push_back(0);
	}

	
	auto start = chrono::high_resolution_clock::now();

	cout << "Part 1: " << run_program().second << endl;;

	pair<int, int> result;

	int last_change = 0;
	do {
		while (instruction[last_change] == 0) last_change++;
		instruction[last_change] = instruction[last_change] == 1 ? 2 : 1;

		result = run_program();

		instruction[last_change] = instruction[last_change] == 1 ? 2 : 1;
		last_change++;

	} while (result.first < instruction.size());
	

	cout << "Part 2: " << result.second << endl;

	auto stop = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << "Time(us): " << duration.count() << endl;

}