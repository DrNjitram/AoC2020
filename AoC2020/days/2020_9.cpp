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

const int preamble = 25;
int stack[preamble];
vector<int> data_stream;


bool check(int n) {
	for (int i = 0; i < preamble; i++) {	
		int target = n - stack[i];
		for (int j = 0; j < preamble; j++) {
			if (i != j && target == stack[j]) {
				return true;
			}
		}
	}
	return false;
}

int answer(int start, int end) {
	vector<int> sub_v = vector<int>(data_stream.begin() + start, data_stream.begin() + end);

	sort(sub_v.begin(), sub_v.end());

	return sub_v[0] + sub_v[end-start-1];
}

int part2(int target){
	int start = 0;
	int current_sum = data_stream[0];

	for (int end = 1; end < data_stream.size(); end++) {
		current_sum += data_stream[end];

		while (current_sum > target && start < end) {
			current_sum -= data_stream[start];
			start++;
		}

		if (current_sum == target) return answer(start, end);
	}

	return -1;
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_9.txt");
	stringstream buffer;
	buffer << input.rdbuf();
	istringstream is(buffer.str());

	int cursor = 0;
	int n;
	auto start = chrono::high_resolution_clock::now();

	while (is >> n) {
		if (cursor >= preamble) {
			if (!check(n)) break;
		}
		stack[cursor++ % preamble] = n;
		data_stream.push_back(n);
	}

	cout << "Part 1: " << n << endl;
	cout << "Part 2: " << part2(n) << endl;

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << "Time(us): " << duration.count() << endl;
}