#include <iostream>
#include <vector>
#include <algorithm>
#include <list>


using namespace std;

//  �������� ����������� ���������� �������� �� ������� �������� �������, 
// ������� ���������� ����� ��� �������� ��������, 
// ���������� ��� ���� � ���������� ���������� ��������, 
// ���� ��� �������� �� ����� �������������

void cycle_sort(int arr[], int n)
{

    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) {
        int item = arr[cycle_start]; // ���������� ������ ������� ������� �������, ������� ����� ��������� �� ���������� �����
        int pos = cycle_start;       // ���������������� �������� �������� ��������

        for (int i = cycle_start + 1; i < n; i++) // �������� �� ���� ��������� ������ �� �������� ��������
            if (arr[i] < item)
                pos++;

        if (pos == cycle_start) // ���� ������� ��� �� ����� �������
            continue;

        while (item == arr[pos]) // ���� ���� ���������
            pos += 1;

        if (pos != cycle_start)  // ���������� ������� ������� �� ���������� �����
        {
            swap(item, arr[pos]);

        }

        while (pos != cycle_start) { // ��������� ��������
            pos = cycle_start;

            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i] < item)
                    pos += 1;

            while (item == arr[pos])
                pos += 1;

            if (item != arr[pos]) {
                swap(item, arr[pos]);
            }
        }
    }


}

// ���� ��� ������� ������ ������
void test01() {
    vector<int> arr = { 1, 2, 3, 4, 5, 6 };
    vector<int> expected = { 1, 2, 3, 4, 5, 6 };

    // ����������� ������ � ������ ��� �������� � ������� cycle_sort
    int* arr_ptr = arr.data();
    int n = arr.size();
    cycle_sort(arr_ptr, n);
    if (arr == expected) {
        cout << "Test1 passed" << endl;
    }
    else {
        cout << "Test1 failed" << endl;
    }
}

// ���� ��� �������� ������ ������
void test02() {
    vector<int> arr = { 3, 1, 4, 2, 5, 6 };
    vector<int> expected = { 1, 2, 3, 4, 5, 6 };

    // ����������� ������ � ������ ��� �������� � ������� cycle_sort
    int* arr_ptr = arr.data();
    int n = arr.size();

    cycle_sort(arr_ptr, n);
    if (arr == expected) {
        cout << "Test2 passed" << endl;
    }
    else {
        cout << "Test2 failed" << endl;
    }
}

// ���� ��� �������� ������ ������
void test03() {
    vector<int> arr = { 6, 5, 4, 3, 2, 1 };
    vector<int> expected = { 1, 2, 3, 4, 5, 6 };

    // ����������� ������ � ������ ��� �������� � ������� cycle_sort
    int* arr_ptr = arr.data();
    int n = arr.size();

    cycle_sort(arr_ptr, n);
    if (arr == expected) {
        cout << "Test3 passed" << endl;
    }
    else {
        cout << "Test3 failed" << endl;
    }
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}
// ������� ������: ����� ������, ������������ ���������� ����������� ����������, 
// ���������� = �(n); ���� �� ���� �������� 6 ���������, �� ���������� ������ � ������ ����� 
// ����� 6 * 4 + 4 * 4 (��� ���������� cycle_start, item, pos, i) = 40 ����

// �����������: ��������� ���������: O(n^2); ���������������� ���������: O(1)




// Tree sort - �������� ����������, ������������� � ���������� ��������� ������ ������
// ��������� ��� ������������� ���� ������; ����������� �������������� ���� � �������� ��������� � ������������� ��������� �� �������� ���� 
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {} // nullptr ������������ ��� ����������� ���������� ������� ��� ���������
};

// ������� ��� ������� ���� � BST
TreeNode* insert(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);            // ���� ������ ������, �� ������� ����� ���� � �������� ��������� � ���������� ���
    }
    if (value < root->value) {
        root->left = insert(root->left, value); // ���� �������� ������ �������� �������� ����, ���������� ��������� �������� � ����� ���������
    }
    else {
        root->right = insert(root->right, value);
    }
    return root;
}

// ������� ��� in-order ������ BST � ���������� ���������������� �������
void in_order(TreeNode* root, vector<int>& sortedArray) {
    if (root == nullptr) {
        return;
    }
    in_order(root->left, sortedArray);
    sortedArray.push_back(root->value);
    in_order(root->right, sortedArray);
}

// ������� ��� ���������� Tree Sort
void tree_sort(vector<int>& arr) {
    if (arr.empty()) {
        return;
    }

    TreeNode* root = nullptr;
    for (int value : arr) {
        root = insert(root, value);
    }

    vector<int> sortedArray;
    in_order(root, sortedArray);

    arr = sortedArray;
}

// ���� ��� �������� ������ ������ ���������
void test01() {
    vector<int> arr = { 3, 1, 4, 2, 5, 6 };
    vector<int> expected = { 1, 2, 3, 4, 5, 6 };

    tree_sort(arr);

    if (arr == expected) {
        cout << "Test1 passed" << endl;
    }
    else {
        cout << "Test1 failed" << endl;
    }
}

// ���� ��� ������� ������ ������ ���������
void test02() {
    vector<int> arr = { 6, 5, 4, 3, 2, 1 };
    vector<int> expected = { 1, 2, 3, 4, 5, 6 };

    tree_sort(arr);

    if (arr == expected) {
        cout << "Test2 passed" << endl;
    }
    else {
        cout << "Test2 failed" << endl;
    }
}

int main() {
    test01();
    test02();
    return 0;
}
// ������� ������: 6 * 4 (������ �������) + 6 * 20 (���� ������) + 8 * 5 (����������) = 184 �����
// �����������: ��������� ��������� = �(n log n); ���������������� ��������� = �(n)





// ������� ��� ���������� Bucket Sort
void bucket_sort(vector<float>& arr) {
    if (arr.empty()) {
        return;
    }

    // ������ ������������ � ����������� �������� � �������
    float maxVal = *max_element(arr.begin(), arr.end());
    float minVal = *min_element(arr.begin(), arr.end());

    // ��������� ���������� ������
    int bucket_count = arr.size();

    // �������� �������
    vector<list<float>> buckets(bucket_count);

    // ����������� �������� �� ��������
    for (float value : arr) {
        int bucketIndex = static_cast<int>((value - minVal) / (maxVal - minVal) * (bucket_count - 1));
        buckets[bucketIndex].push_back(value);
    }

    // ��������� �������� � ������ �������
    for (auto& bucket : buckets) {
        bucket.sort();
    }

    // ���������� �������� �� ���� ������ � ���� ��������������� ������
    int index = 0;
    for (const auto& bucket : buckets) {
        for (float value : bucket) {
            arr[index++] = value;
        }
    }
}

// ���� ��� �������� ������ ������ ���������
void test01() {
    vector<float> arr = { 0.3, 0.1, 0.4, 0.2, 0.5, 0.6 };
    vector<float> expected = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6 };

    bucket_sort(arr);

    if (arr == expected) {
        cout << "Test1 passed" << endl;
    }
    else {
        cout << "Test1 failed" << endl;
    }
}

// ���� ��� ������� ������ ������ ���������
void test02() {
    vector<float> arr = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
    vector<float> expected = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };

    bucket_sort(arr);

    if (arr == expected) {
        cout << "Test2 passed" << endl;
    }
    else {
        cout << "Test2 failed" << endl;
    }
}

int main() {
    test01();
    test02();
    return 0;
}
// ������� ������: 6 * 4 (������ �������) + 6 * 16 (�������) + 6 * 12 (�������� � ��������) + 8 * 5 (����������) = 232 �����
// �����������: ��������� ��������� = �(n * k); ���������������� ��������� = �(n)

