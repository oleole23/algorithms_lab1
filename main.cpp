#include <iostream>
#include <math.h>
#include <chrono>
void Print(int** matrix, int n, int m){
    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            std::cout << matrix[i][j] << ' ';
        std::cout << '\n';
    }
}
int GenFirstWay(int** matrix, int m, int n){
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j){
            matrix[i][j] = (n / m * i + j) * 2;
        }
    int target = 2 * n + 1;
    return target;
}
int GenSecondWay(int** matrix, int m, int n){
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j){
            matrix[i][j] = (n / m * i * j) * 2;
        }
    int target = 16 * n + 1;
    return target;
}
int BinarySearch(int** matrix, int target, int m, int n) {
    for (int i = 0; i < m; ++i) {
        int first = 0;
        int last = n - 1;
        while (first <= last) {
            int middle = (first + last) / 2;
            if (target < matrix[i][middle]) {
                last = middle - 1;
            } else if (target > matrix[i][middle]) {
                first = middle + 1;
            } else
                return 1;
        }
    }
    return 0;
}
int Ladder(int** matrix, int target, int m, int n){
    int col = n - 1;
    int row = 0;
    while(col > 0 && row < m && matrix[row][col] != target){
        while ( col > 0 && matrix[row][col] > target ){
            col -= 1;
        }
        while (row < m && matrix[row][col] < target ){
            row += 1;
        }
    }
    if (row < m && col >= 0 && matrix[row][col] == target){
        return 1;
    }
    else {
        return 0;
    }
}
//int ExpLadder(int** matrix, int target, int m, int n){
//    int col = n - 1;
//    int row = 0;
//    int step = 0;
//    while(col > 0 && row < m && matrix[row][col] != target){
//        while ( col > 0 && matrix[row][col] > target ){
//            col -= 1;
//        }
//        if (step == 0) {
//            step = 1;
//            row += step;
//        }
//        while (step < m && row < m && matrix[row][col] <= target){
//            step *= 2;
//            row += step;
//        }
//        int first = row - step;
//        int last = row < m ? row: m - 1;
//        while (first <= last) {
//            int middle = (first + last) / 2;
//            if (target < matrix[middle][col]) {
//                last = middle - 1;
//            } else if (target > matrix[middle][col]) {
//                first = middle + 1;
//            } else
//                return 1;
//        }
//    }
//    if (row < m && matrix[row][col] == target) {
//        return 1;
//    }
//    else {
//        return 0;
//    }
//}
int ExpLadder(int** matrix, int target, int m, int n){
    int col = n - 1;
    int row = 0;
    int step = 0;
    while(col > 0 && row < m && matrix[row][col] != target){
        while (row < m && matrix[row][col] < target){
            row += 1;
        }
        if (row >= m)
            break;
        step = 1;
        col -= step;
        while (col > 0 && matrix[row][col] > target ){
            step *= 2;
            col -= step;
        }
        int last = col + step;
        int first = col > 0 ? col: 0;
        while (first <= last) {
            int middle = (first + last) / 2;
            if (target < matrix[row][middle]) {
                last = middle - 1;
            } else if (target > matrix[row][middle]) {
                first = middle + 1;
            } else
                return 1;
        }
    }
    if (col >= 0 && row < m && matrix[row][col] == target) {
        return 1;
    }
    else {
        return 0;
    }
}
int main(int argc, char* argv[]) {
    int n, m;
    double time = 0;
    for (int x = 1; x <= 13; ++x) {
        m = pow(2, x);
        n = pow(2, 13);
        int **matrix = new int *[m];
        for (int i = 0; i < m; ++i) {
            matrix[i] = new int[n];
        }

        int target;
        target = GenSecondWay(matrix, m, n);
        for(int iter = 0; iter < 100; iter++) {
            auto start = std::chrono::high_resolution_clock::now();
            ExpLadder(matrix, target, m, n);
            //BinarySearch(matrix, target, m, n);
            //Ladder(matrix, target, m, n);
            auto end = std::chrono::high_resolution_clock::now();
            double search_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            time += search_time;
        }
        std::cout<<time/1000000/100<<'\n';
        for (int i = 0; i < m; ++i) {
            delete matrix[i];
        }
        delete matrix;
    }
    return 0;
}
