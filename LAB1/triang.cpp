#include"triang.h"
#include <iostream>

float find_nulif(float a, float b) {
    return -b / a;
}

void triang(Matrix& matrix, int iter_no1, int iter_no2) {
    iter_no1+=iter_no2;
    float nulifier = find_nulif(matrix.get_element(iter_no2, iter_no2), matrix.get_element(iter_no1 + 1, iter_no2));
    //cout << "nulif " << nulifier << endl; //debug
    for (auto i = iter_no2; i < matrix.get_row(); i++) {
        matrix.set_element(iter_no1 + 1, i, matrix.get_element(iter_no2, i) * nulifier + matrix.get_element(iter_no1 + 1, i));
    }
}

