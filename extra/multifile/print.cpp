/**
 * @file: print.cpp
 * @author: jianfei.zhao
 * @description: implementation of printNumberPyramid
 */

#include "print.h"
#include <cmath>
#include <iostream>

using namespace std;

/**
 * print pyramid with number
 */
void printNumberPyramid(int layer) {
    for (int i = layer - 1; i >= 0; i--) {
        for (int j = 1 - layer; j < layer; j++) {
            int sum = abs(i) + abs(j);
            if (sum <= layer && sum == (layer - 1)) {
                cout << layer-i;
            } else if (sum <= layer && sum % 2 == (layer - 1) % 2 && i == 0) {
                cout << layer;
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}
