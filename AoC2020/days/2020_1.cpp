#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <chrono> 
#include <set>
#include <unordered_map>

using namespace std;

int solutionvect(vector<int> numbers) {
	int answer1;

	int min = 9999;
	int target1;
	int target2;
	vector<int> second_numbers;

	for (int& val : numbers) {
		if (val < min) min = val;
	}

	min = 2020 - min;

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
					return val1 * val2 * val3;
				}
			}

		}
	}

	//cout << answer1 << endl;
	//cout << (answer1 == 437931) << endl;
	//cout << answer2 << endl;
	//cout << (answer2 == 157667328) << endl;
}

int solutionmap(unordered_map<int, int> numbersmap) {
	int answer1 = 0;
	int answer2 = 0;
	int target1 = 0;
	int target2 = 0;

	int min = 2020 - min_element(numbersmap.begin(), numbersmap.end(),
		[](const auto& l, const auto& r) { return l.first < r.first; }) -> second;


	for (const auto& x : numbersmap) {
		if (x.first > min) continue;

		target1 = 2020 - x.first;

		if (numbersmap.find(target1) != numbersmap.end()) {
			answer1 = x.first * target1;
		}
		else {
			for (const auto& x2 : numbersmap) {
				if (x.first + x2.first > min) continue;

				target2 = 2020 - x.first - x2.first;
				 
				if (numbersmap.find(target2) != numbersmap.end())
					return x.first * x2.first * target2;
			}
		}
	}



	//cout << answer1 << endl;
	//cout << (answer1 == 437931) << endl;
	//cout << answer2 << endl;
	//cout << (answer2 == 157667328) << endl;
}


int solutionset(set<int> numbers) {
	int answer1;
	int answer2;
	int target1;
	int target2;
	set<int> second_numbers;

	int min = 2020 - *numbers.begin();


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
				return val * val2 * target2;
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

	vector<int> numbersv;
	unordered_map<int, int> numbersmap;
	set<int> numberss;

	int n;
	int iters = 1;

	while (is >> n) {
		numbersv.push_back(n);
		numbersmap.insert(pair<int, int>(n, 0));
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
		solutionmap(numbersmap);
	}

	stop = chrono::high_resolution_clock::now();

	duration = chrono::duration_cast<chrono::microseconds>(stop - start);



	cout << "Map: " << duration.count() / iters << endl;

	start = chrono::high_resolution_clock::now();

	for (int i = 0; i < iters; i++) {
		solutionset(numberss);
	}

	stop = chrono::high_resolution_clock::now();

	duration = chrono::duration_cast<chrono::microseconds>(stop - start);



	cout << "Set: " << duration.count() / iters << endl;

}

