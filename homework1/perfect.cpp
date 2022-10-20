/**
 * @file: prefect.cpp
 * @author: jianfei.zhao
 * @description: calculate prefect number with 3 different way
 */
#include "console.h"
#include <iostream>
#include "testing/SimpleTest.h"
#include <cmath>
using namespace std;

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to sqrt(n), testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long smarterSum(long n) {
    if(n==1){
        return 0;
    }
    long range=static_cast<long>(floor(sqrt(n)));
    long total = 0;
    long division_result=0;
    for (long divisor = 1; divisor <= range; divisor++) {
        if (n % divisor == 0) {
            division_result=static_cast<long>(n/divisor);
            if(division_result==divisor||division_result==n){
                total += divisor;
            }else{
                 total += divisor+division_result;
            }
        }
    }
    return total;
}

/* This function does an search from 1 to floor(sqrt(n)) for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n == smarterSum(n));
}

/* This function does an search from 1 to floor(sqrt(n)) for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console. O(N.sqrt(N))
 */
void findPerfectsSmarter(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function searcg for nth Perfect number with Euclid way
 * It takes one argument `n` and list first to n-th Perfect number,
 * printing it to the console.
 */
long findNthPerfectEuclid(long n) {
    int count_prefect_number=0;
    int k=1;
    long result=0;
    long m=0;
    while( count_prefect_number<n){
        m=pow(2,k)-1;
        if(smarterSum(m)==1){
            // is prefect number
            result=(pow(2,k)-1)*(pow(2,k-1));
            count_prefect_number++;
        }
        k++;
    }
    return result;
}


/* * * * * * Test Cases * * * * * */

// test function divisorSum
PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

// test function isPerfect (equal test)
PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

// test function isPerfect (opposite test)
PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

// test function isPerfect (edge test)
PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

// test function isPerfect (equal test|stress test)
PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

// test function findPerfects (time test)
// 第一个参数是输入大小，用于标记计时结果，以区别于其他结果。第二个参数是要计算的表达式。
PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10000, findPerfects(10000));
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
}

STUDENT_TEST("More stress test of findPerfects") {
//    TIME_OPERATION(80000, findPerfects(80000));
//    TIME_OPERATION(160000, findPerfects(160000));
//    TIME_OPERATION(320000, findPerfects(320000));
//    TIME_OPERATION(500000, findPerfects(500000));
}

STUDENT_TEST("negetive input of isPerfect") {
     EXPECT(!isPerfect(-1));
     EXPECT(!isPerfect(-10));
     EXPECT(!isPerfect(-100));
}

STUDENT_TEST("smart-Confirm smarterSum of small inputs") {
    EXPECT_EQUAL(smarterSum(1), 0);
    EXPECT_EQUAL(smarterSum(6), 6);
    EXPECT_EQUAL(smarterSum(25), 6);
    EXPECT_EQUAL(smarterSum(36), 55);
}

// test function isPerfect (equal test)
PROVIDED_TEST("smart-Confirm 6 and 28 and 496 are perfect") {
    EXPECT(isPerfectSmarter(6));
    EXPECT(isPerfectSmarter(28));
    EXPECT(isPerfectSmarter(496));
}

STUDENT_TEST("smart- edge test") {
    EXPECT(!isPerfectSmarter(0));
    EXPECT(!isPerfectSmarter(1));
    EXPECT(!isPerfectSmarter(-1));
}


// test function findPerfects (time test)
// 第一个参数是输入大小，用于标记计时结果，以区别于其他结果。第二个参数是要计算的表达式。
STUDENT_TEST("smart- stress test ") {
    TIME_OPERATION(10000, findPerfectsSmarter(10000));
    TIME_OPERATION(20000, findPerfectsSmarter(20000));
    TIME_OPERATION(40000, findPerfectsSmarter(40000));
//    TIME_OPERATION(80000, findPerfectsSmarter(80000));
//    TIME_OPERATION(160000, findPerfectsSmarter(160000));
//    TIME_OPERATION(320000, findPerfectsSmarter(320000));
//    TIME_OPERATION(640000, findPerfectsSmarter(640000));
//    TIME_OPERATION(1280000, findPerfectsSmarter(1280000));
}

STUDENT_TEST("arithmetic test- findNthPerfectEuclid") {
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(1)));
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(3)));
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(5)));
}

STUDENT_TEST("equal test- findNthPerfectEuclid") {
    EXPECT_EQUAL(findNthPerfectEuclid(1), 6);
    EXPECT_EQUAL(findNthPerfectEuclid(2), 28);
    EXPECT_EQUAL(findNthPerfectEuclid(3), 496);
    EXPECT_EQUAL(findNthPerfectEuclid(4), 8128);
    EXPECT_EQUAL(findNthPerfectEuclid(5), 33550336);
}

STUDENT_TEST("edge test- findNthPerfectEuclid") {
    EXPECT_EQUAL(findNthPerfectEuclid(0), 0);
    EXPECT_EQUAL(findNthPerfectEuclid(-1), 0);
}

STUDENT_TEST("time test- findNthPerfectEuclid") {
    TIME_OPERATION(1, findNthPerfectEuclid(1));
    TIME_OPERATION(3, findNthPerfectEuclid(3));
    TIME_OPERATION(5, findNthPerfectEuclid(5));
}


