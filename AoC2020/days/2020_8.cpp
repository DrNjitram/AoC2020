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

pair<int, int> run_program(int n) {
	zero_visits();
	int acc = 0;
	int instrpnt = 0;
	int nop_jmp_cnt = 0;

	while (check_postion(instrpnt)) {
		visits[instrpnt]++;

		int instr = instruction[instrpnt];
		if (instr != 0) {
			if (nop_jmp_cnt == n) {
				instr = instr == 1 ? 2 : 1;
			}
			nop_jmp_cnt++;
		}

		switch (instr) {
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

	cout << "Part 1: " << run_program(-1).second << endl;;

	pair<int, int> result;
	int change = 0;
	do {

		result = run_program(change++);

	} while (result.first < instruction.size());
	

	cout << "Part 2: " << result.second << endl;

}