/**
 * @file: main.cpp
 * @author: jianfei.zhao
 * @description: print pyramid with given layer,default layer is 6
 * based on the code from homework0 and learn multi file
 */


#include <iostream>
#include "console.h"
#include "simpio.h"
#include "print.h"

using namespace std;

/* Constant Variable */
const int Layer = 6;

int main() {
    int value = 0;
    value = getInteger("Enter your own layer: ");
    printNumberPyramid(value ? value : Layer);
    return 0;
}
