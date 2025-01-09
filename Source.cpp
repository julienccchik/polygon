#include <iostream>
#include <vector>
#include <numeric>


using namespace std;

bool partitioning_check(const vector<int>& arr, int index, int current_sum, int target) {
	if (current_sum == target) {
		return true;
	}
	if (current_sum > target || index < 0) {
		return false;
	}
	return partitioning_check(arr, index - 1, current_sum, target) || partitioning_check(arr, index - 1, current_sum + arr[index], target);
}

// написали функцию для проверки, можно ли разделить массив на две части с равной суммой

vector<vector<int>> partition(const vector<int>& arr) {
    vector<vector<int>> result;
    int totalSum = accumulate(arr.begin(), arr.end(), 0);

    if (totalSum % 2 != 0) {
        return result; // нельзя разделить на две части с равной суммой
    }

    int target = totalSum / 2;

    if (!partitioning_check(arr, arr.size() - 1, 0, target)) {
        return result; // нельзя разделить на две части с равной суммой
    }

    vector<int> part1, part2;
    vector<int> currentPart;

    find_subset(arr, arr.size() - 1, 0, target, currentPart, part1);

    for (int num : arr) {
        if (find(part1.begin(), part1.end(), num) == part1.end()) {
            part2.push_back(num);
        }
    }

    result.push_back(part1);
    result.push_back(part2);
    return result;
}
// написали функцию для разделения массива на две части с равной суммой

void find_subset(const vector<int>& arr, int index, int current_sum, int target, vector<int>& current_part, vector<int>& part1) {
	if (current_sum == target) {
		part1 = current_part;
		return;
	}
	if (current_sum > target || index < 0) {
		return;
	}
	current_part.push_back(arr[index]);
	find_subset(arr, index - 1, current_sum + arr[index], target, current_part, part1);
	current_part.pop_back();
	find_subset(arr, index - 1, current_sum, target, current_part, part1);
}

// написали вложенную функцию для нахождения подмножества с заданной суммой
void test01() {

    vector<int> arr = { 1, 5, 3, 5, 2, 5 };
    vector<vector<int>> result = partition(arr);

    if (!result.empty()) {
        vector<int> Part1 = { 1, 5, 5 };
        vector<int> Part2 = { 3, 2, 5 };

        if (result[0] == Part1 && result[1] == Part2) {
            cout << "Test1 passed" << endl;
        }
        else {
            cout << "Test1 failed" << endl;
        }
    }
}
    int main() {
        setlocale(LC_ALL, "rus");
        test01();
        return 0;
    }