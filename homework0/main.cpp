/**
 * @file: main.cpp
 * @author: jianfei.zhao
 * @description: print pyramid with given layer,default layer is 6
 */


#include <iostream>
#include "console.h"
#include "simpio.h"
#include <cmath>
using namespace std;

/* Constant Variable */
const int Layer = 6;

/* Function Prototype */
void printNumberPyramid(int layer);


int main() {
    int value = 0;
    value = getInteger("Enter your own layer: ");
    printNumberPyramid(value ? value : Layer);
    return 0;
}

/* Function Implementation */
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
