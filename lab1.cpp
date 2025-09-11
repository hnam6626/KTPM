#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

int solveQuartic(double a, double b, double c, double x[]) {
    if (a == 0 && b == 0 && c == 0) {
        return -1;
    }

    if (a == 0 && b == 0) {
        return 0;
    }

    if (a == 0) {
        double y = -c / b;
        if (y < 0) return 0;
        x[0] = sqrt(y);
        x[1] = -sqrt(y);
        return 2;
    }

    double delta = b * b - 4 * a * c;
    if (delta < 0) return 0;

    double y1 = (-b + sqrt(delta)) / (2 * a);
    double y2 = (-b - sqrt(delta)) / (2 * a);

    int count = 0;
    if (y1 >= 0) {
        x[count++] = sqrt(y1);
        x[count++] = -sqrt(y1);
    }
    if (y2 >= 0 && y2 != y1) {
        x[count++] = sqrt(y2);
        x[count++] = -sqrt(y2);
    }

    return count;
}

// Hàm helper để so sánh double với epsilon
bool approxEqual(double a, double b, double eps = 1e-6) {
    return fabs(a - b) < eps;
}

// Unit tests
void runTests() {
    double x[4];
    int n;

    // Test 1: Infinite
    n = solveQuartic(0, 0, 0, x);
    assert(n == -1);

    // Test 2: No solution
    n = solveQuartic(0, 0, 1, x);
    assert(n == 0);

    // Test 3: 2 solutions
    n = solveQuartic(0, 1, -1, x);
    assert(n == 2);
    assert(approxEqual(x[0], 1.0) && approxEqual(x[1], -1.0) || approxEqual(x[0], -1.0) && approxEqual(x[1], 1.0));

    // Test 4: No solution
    n = solveQuartic(0, 1, 1, x);
    assert(n == 0);

    // Test 5: 4 solutions
    n = solveQuartic(1, -5, 6, x);
    assert(n == 4);
    // Kiểm tra giá trị (sort để dễ assert)
    vector<double> roots = {x[0], x[1], x[2], x[3]};
    sort(roots.begin(), roots.end());
    assert(approxEqual(roots[0], -sqrt(3)) && approxEqual(roots[1], -sqrt(2)) &&
           approxEqual(roots[2], sqrt(2)) && approxEqual(roots[3], sqrt(3)));

    // Test 6: 2 solutions
    n = solveQuartic(1, 0, -1, x);
    assert(n == 2);
    assert(approxEqual(x[0], 1.0) && approxEqual(x[1], -1.0) || approxEqual(x[0], -1.0) && approxEqual(x[1], 1.0));

    // Test 7: No solution
    n = solveQuartic(1, 2, 3, x);
    assert(n == 0);

    // Test 8: 2 solutions (double root y)
    n = solveQuartic(1, -2, 1, x);
    assert(n == 2);
    assert(approxEqual(x[0], 1.0) && approxEqual(x[1], -1.0) || approxEqual(x[0], -1.0) && approxEqual(x[1], 1.0));

    cout << "All tests passed! Program is correct." << endl;
}

int main() {
    runTests();
    return 0;
}
