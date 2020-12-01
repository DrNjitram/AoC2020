#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <chrono> 

using namespace std;

int main() {

	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_1.txt");

	stringstream buffer;
	buffer << input.rdbuf();
	istringstream is(buffer.str());

	vector<int> numbers;

	int n;

	while (is >> n) {
		numbers.push_back(n);
	}

	auto start = chrono::high_resolution_clock::now();

	int answer1_1;
	int answer1_2;

	int answer2_1;
	int answer2_2;
	int answer2_3;

	int min = 9999;
	for (int& val : numbers) {
		if (val < min) min = val;
	}

	min = 2020 - min;

	vector<int> second_numbers;

	for (int& val : numbers) {
		if (val <= min) {
			second_numbers.push_back(val);
		}
	}

	numbers = second_numbers;
	
	int target1;
	int target2;

	for (int& val1 : numbers) {
		if (val1 > min) continue;
		target1 = 2020 - val1;
		for (int& val2 : numbers) {

			if (val2 == target1) {
				answer1_1 = val1;
				answer1_2 = val2;
				continue;
			}
			else if (val1 + val2 > min) {
				continue;
			}

			target2 = 2020 - val1 - val2;
			for (int& val3 : numbers) {
				if (val3 == target2) {
					answer2_1 = val1;
					answer2_2 = val2;
					answer2_3 = val3;
				}
			}

		}
	}
	auto stop = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << answer1_1 * answer1_2 << endl;
	cout << (answer1_1 * answer1_2 == 437931) << endl;
	cout << answer2_1 * answer2_2 * answer2_3 << endl;
	cout << (answer2_1 * answer2_2 * answer2_3 == 157667328 )<< endl;

	cout << duration.count() << endl;

}