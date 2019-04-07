// Use Euclid Extended to find the solution of equation ax + by = gcd (a, b).
// Assuming the result is (x0, y0), the solution family of the equation will be (x_0 + kb / d, y_0-ka / d) with k∈Z.
// General equation ax + by = d only has solutions when d is divisible by gcd (a, b).
// a x + b y = gcd(a, b)
int extgcd(int a, int b, int &x, int &y) {
    int g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}
