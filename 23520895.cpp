#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

using namespace std;

const int N = 1000000; // 1 triệu phần tử

// ==================== 1. QUICKSORT ====================
void quickSort(vector<double>& a, int left, int right) {
    double pivot = a[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (left < j) quickSort(a, left, j);
    if (i < right) quickSort(a, i, right);
}

// ==================== 2. HEAPSORT ====================
void heapify(vector<double>& a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<double>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// ==================== 3. MERGESORT ====================
void merge(vector<double>& a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<double> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = a[left + i];
    for (int j = 0; j < n2; j++) R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<double>& a, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

// ==================== TAO DU LIEU ====================
void generateData() {
    srand(1337); // khoi tao seed

    for (int t = 1; t <= 10; t++) {
        vector<double> a(N);
        for (int i = 0; i < N; i++) {
            // sinh so thuc ngau nhien
            a[i] = (double)rand() / RAND_MAX * 2000000.0 - 1000000.0;
        }

        if (t == 1) {
            // Day 1: Tang dan
            sort(a.begin(), a.end());
        } else if (t == 2) {
            // Day 2: Giam dan
            sort(a.begin(), a.end(), greater<double>());
        }
        // Day 3-10: Ngau nhien

        string filename = "test" + to_string(t) + ".txt";
        ofstream fout(filename);
        for (int i = 0; i < N; i++) {
            fout << fixed << setprecision(4) << a[i] << " ";
        }
        fout.close();
        cout << "Da tao file " << filename << endl;
    }
}

int main() {
    cout << "Dang tao 10 file du lieu test..." << endl;
    generateData();

    cout << "\nBang ket qua do thoi gian (ms):\n";
    cout << "Du lieu\t\tQuickSort\tHeapSort\tMergeSort\tsort(C++)\n";

    double sum_quick = 0, sum_heap = 0, sum_merge = 0, sum_std = 0;

    for (int t = 1; t <= 10; t++) {
        string filename = "test" + to_string(t) + ".txt";
        ifstream fin(filename);
        vector<double> original(N);
        for (int i = 0; i < N; i++) {
            fin >> original[i];
        }
        fin.close();

        // 1. QuickSort
        vector<double> a1 = original;
        clock_t start = clock();
        quickSort(a1, 0, N - 1);
        clock_t end = clock();
        double t_quick = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

        // 2. HeapSort
        vector<double> a2 = original;
        start = clock();
        heapSort(a2);
        end = clock();
        double t_heap = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

        // 3. MergeSort
        vector<double> a3 = original;
        start = clock();
        mergeSort(a3, 0, N - 1);
        end = clock();
        double t_merge = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

        // 4. std::sort C++
        vector<double> a4 = original;
        start = clock();
        sort(a4.begin(), a4.end());
        end = clock();
        double t_std = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

        sum_quick += t_quick;
        sum_heap += t_heap;
        sum_merge += t_merge;
        sum_std += t_std;

        cout << t << "\t\t" << fixed << setprecision(2)
             << t_quick << "\t\t" << t_heap << "\t\t"
             << t_merge << "\t\t" << t_std << endl;
    }

    cout << "------------------------------------------------------------\n";
    cout << "Trung binh\t" << fixed << setprecision(2)
         << sum_quick / 10.0 << "\t\t" << sum_heap / 10.0 << "\t\t"
         << sum_merge / 10.0 << "\t\t" << sum_std / 10.0 << endl;

    return 0;
}
