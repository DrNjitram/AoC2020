#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <chrono> 
#include <set>

using namespace std;

void solutionvect(vector<int> numbers) {
	int answer1;
	int answer2;
	int min = 9999;
	int target1;
	int target2;
	vector<int> second_numbers;

	for (int& val : numbers) {
		if (val < min) min = val;
	}

	min = 2020 - min;

	for (int& val : numbers) {
		if (val <= min) {
			second_numbers.push_back(val);
		}
	}

	numbers = second_numbers;

	for (int& val1 : numbers) {
		if (val1 > min) continue;
		target1 = 2020 - val1;
		for (int& val2 : numbers) {

			if (val2 == target1) {
				answer1 = val1 * val2;
				continue;
			}
			else if (val1 + val2 > min) {
				continue;
			}

			target2 = 2020 - val1 - val2;
			for (int& val3 : numbers) {
				if (val3 == target2) {
					answer2 = val1 * val2 * val3;
				}
			}

		}
	}

	//cout << answer1 << endl;
	//cout << (answer1 == 437931) << endl;
	//cout << answer2 << endl;
	//cout << (answer2 == 157667328) << endl;
}

void solutionset(set<int> numbers) {
	int answer1;
	int answer2;
	int target1;
	int target2;
	set<int> second_numbers;

	int min = 2020 - *numbers.begin();

	for (const int& val : numbers) {
		if (val <= min) {
			second_numbers.insert(val);
		}
	}

	numbers = second_numbers;

	for (const int& val : numbers) {
		if (val > min) continue;
		target1 = 2020 - val;
		for (const int& val2 : numbers) {


			if (val2 == target1) {
				answer1 = val * val2;
				continue;
			}
			else if (val + val2 > min) {
				continue;
			}

			target2 = 2020 - val - val2;

			if (numbers.find(target2) != numbers.end())
				answer2 = val * val2 * target2;
		}
	}

	//cout << answer1 << endl;
	//cout << (answer1 == 437931) << endl;
	//cout << answer2 << endl;
	//cout << (answer2 == 157667328) << endl;
}


int main() {

	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_1.txt");

	stringstream buffer;
	buffer << input.rdbuf();
	istringstream is(buffer.str());

	set<int> numberss;
	vector<int> numbersv;

	int n;
	int iters = 100;

	while (is >> n) {
		numbersv.push_back(n);
		numberss.insert(n);
	}

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < iters; i++) {
		solutionvect(numbersv);
	}

	auto stop = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	cout << "Vect: " << duration.count()/ iters << endl;


	start = chrono::high_resolution_clock::now();
	
	for (int i = 0; i < iters; i++) {
		solutionset(numberss);
	}

	stop = chrono::high_resolution_clock::now();

	duration = chrono::duration_cast<chrono::microseconds>(stop - start);



	cout << "Set: " << duration.count() / iters << endl;

}

