#include <iostream>
#include <vector>
#include <algorithm>
#include <list>


using namespace std;

//  алгоритм циклической сортировки проходит по каждому элементу массива, 
// находит правильное место для текущего элемента, 
// перемещает его туда и продолжает перемещать элементы, 
// пока все элементы не будут отсортированы

void cycle_sort(int arr[], int n)
{

    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) {
        int item = arr[cycle_start]; // переменная хранит текущий элемент массива, который будет перемещен на правильное место
        int pos = cycle_start;       // инициализируется индексом текущего элемента

        for (int i = cycle_start + 1; i < n; i++) // проходит по всем элементам справа от текущего элемента
            if (arr[i] < item)
                pos++;

        if (pos == cycle_start) // если элемент уже на своей позиции
            continue;

        while (item == arr[pos]) // если есть дубликаты
            pos += 1;

        if (pos != cycle_start)  // перемещаем текущий элемент на правильное место
        {
            swap(item, arr[pos]);

        }

        while (pos != cycle_start) { // зациклили действия
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

// тест для лучшего случая работы
void test01() {
    vector<int> arr = { 1, 2, 3, 4, 5, 6 };
    vector<int> expected = { 1, 2, 3, 4, 5, 6 };

    // Преобразуем вектор в массив для передачи в функцию cycle_sort
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

// тест для среднего случая работы
void test02() {
    vector<int> arr = { 3, 1, 4, 2, 5, 6 };
    vector<int> expected = { 1, 2, 3, 4, 5, 6 };

    // Преобразуем вектор в массив для передачи в функцию cycle_sort
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

// тест для среднего случая работы
void test03() {
    vector<int> arr = { 6, 5, 4, 3, 2, 1 };
    vector<int> expected = { 1, 2, 3, 4, 5, 6 };

    // Преобразуем вектор в массив для передачи в функцию cycle_sort
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
// подсчёт памяти: общая память, используемая алгоритмом циклической сортировки, 
// составляет = О(n); если на вход подавать 6 элементов, то занимаемая память в байтах будет 
// равна 6 * 4 + 4 * 4 (для переменных cycle_start, item, pos, i) = 40 байт

// асимптотика: временная сложность: O(n^2); пространственная сложность: O(1)




// Tree sort - алгоритм сортировки, заключающийся в построении двоичного дерева поиска
// Структура для представления узла дерева; конструктор инициализирует узел с заданным значением и устанавливает указатели на дочерние узлы 
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {} // nullptr используется для обозначения отсутствия объекта или указателя
};

// Функция для вставки узла в BST
TreeNode* insert(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);            // если дерево пустое, то создает новый узел с заданным значением и возвращает его
    }
    if (value < root->value) {
        root->left = insert(root->left, value); // если значение меньше значения текущего узла, рекурсивно вставляет значение в левое поддерево
    }
    else {
        root->right = insert(root->right, value);
    }
    return root;
}

// Функция для in-order обхода BST и заполнения отсортированного массива
void in_order(TreeNode* root, vector<int>& sortedArray) {
    if (root == nullptr) {
        return;
    }
    in_order(root->left, sortedArray);
    sortedArray.push_back(root->value);
    in_order(root->right, sortedArray);
}

// Функция для выполнения Tree Sort
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

// Тест для среднего случая работы алгоритма
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

// Тест для худшего случая работы алгоритма
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
// подсчёт памяти: 6 * 4 (память массива) + 6 * 20 (узлы дерева) + 8 * 5 (переменные) = 184 байта
// асимптотика: временная сложность = О(n log n); пространственная сложность = О(n)





// Функция для выполнения Bucket Sort
void bucket_sort(vector<float>& arr) {
    if (arr.empty()) {
        return;
    }

    // Найдем максимальное и минимальное значение в массиве
    float maxVal = *max_element(arr.begin(), arr.end());
    float minVal = *min_element(arr.begin(), arr.end());

    // Определим количество корзин
    int bucket_count = arr.size();

    // Создадим корзины
    vector<list<float>> buckets(bucket_count);

    // Распределим элементы по корзинам
    for (float value : arr) {
        int bucketIndex = static_cast<int>((value - minVal) / (maxVal - minVal) * (bucket_count - 1));
        buckets[bucketIndex].push_back(value);
    }

    // Сортируем элементы в каждой корзине
    for (auto& bucket : buckets) {
        bucket.sort();
    }

    // Объединяем элементы из всех корзин в один отсортированный массив
    int index = 0;
    for (const auto& bucket : buckets) {
        for (float value : bucket) {
            arr[index++] = value;
        }
    }
}

// Тест для среднего случая работы алгоритма
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

// Тест для худшего случая работы алгоритма
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
// подсчёт памяти: 6 * 4 (память массива) + 6 * 16 (корзины) + 6 * 12 (элементы в корзинах) + 8 * 5 (переменные) = 232 байта
// асимптотика: временная сложность = О(n * k); пространственная сложность = О(n)

