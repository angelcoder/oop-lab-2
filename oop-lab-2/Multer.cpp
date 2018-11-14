//
//  Multer.cpp
//  oop-lab-2
//
//  Created by Anhelina Lohvina on 05.10.2018.
//  Copyright © 2018 Anhelina Lohvina. All rights reserved.
//

#include "LongInt.hpp"
//#include "LongDouble.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <complex>
using namespace std;

Multer* LongInt::m = nullptr;

void extend_vec(std::vector<int>& v, size_t len) {
    while (len & (len - 1)) ++len;
    v.resize(len);
}

LongInt Multiplication::mult(LongInt& a, LongInt& b) {
    LongInt result;
    for (int i = 0; i < b.getSize(); i++) {
        LongInt newLongInt = a.multiply(b[i]);
        newLongInt.normalize(i);
        result = result + newLongInt;
    }
    return result;
}

//pre: a, b>=0
LongInt KarFunction(LongInt& a, LongInt& b) {
    long aSize = a.getSize(), bSize = b.getSize();
    LongInt res;
    auto n = std::max(aSize, bSize);
    // add zeros
    while (a.digitsNum() != n) a.digits.push_back(0);
    while (b.digitsNum() != n) b.digits.push_back(0);
    //basic cases
    if (aSize == 0 || bSize == 0) return LongInt("", 1);
    if (bSize == 1) {
        int n = b[0];
        res = a.multiply(n);
        return res;
    }
    if (aSize == 1) {
        int n = a[0];
        res = b.multiply(n);
        return res;
    }
    // recursive calls
    long m = n / 2;
    std::vector<int> u0, u1, v0, v1;
    for (int i = 0; i < m; ++i){
        u0.push_back(a.digits[i]);
        v0.push_back(b.digits[i]);
    }
    for (long i = m; i < n; ++i){
        u1.push_back(a.digits[i]);
        v1.push_back(b.digits[i]);
    }
    LongInt A(u0), B(u1), C(v0), D(v1);
    LongInt res_, res1, res2, res0;
    res1 = A + B;
    res2 = C + D;
    res_ = KarFunction(res1, res2);
    res1 = KarFunction(A, C);
    res2 = KarFunction(B, D);
    res0 = res_ - (res1+res2);
    res0.moveDecimal(m);
    res2.moveDecimal(2 * m);
    return res0 + res1 + res2;
}

LongInt Karatsuba::mult(LongInt& a, LongInt& b) {
    return KarFunction(a, b);
}


void split3(const LongInt& myLong, LongInt& D2, LongInt& D1, LongInt& D0, long maxCap) {
    std::string myStr = std::string(myLong);
    std::string d2, d1, d0;
    long len = myStr.length();
    if (len <= maxCap * 2)
        d2 = "";
    else
        d2 = myStr.substr(0, len - 2 * maxCap);
    if (len <= maxCap)
        d1 = "";
    else if (len <= maxCap * 2)
        d1 = myStr.substr(0, len - maxCap);
    else
        d1 = myStr.substr(len - 2 * maxCap, maxCap);
    if (len <= maxCap)
        d0 = myStr;
    else
        d0 = myStr.substr(len - maxCap, maxCap);
    D2 = LongInt(d2);
    D1 = LongInt(d1);
    D0 = LongInt(d0);
}

LongInt Toom3Multi(const LongInt& m, const LongInt& n);
LongInt Multiplication1 (LongInt& a, LongInt& b) {
    LongInt result;
    for (int i = 0; i < b.getSize(); i++) {
        LongInt newLongInt = a.multiply(b[i]);
        newLongInt.normalize(i);
        result = result + newLongInt;
    }
    return result;
}

void productPolynomial(LongInt *w, LongInt& m2, LongInt& m1, LongInt& m0,
                       LongInt& n2, LongInt& n1, LongInt& n0) {
    LongInt M, N;
    //polynomial = x0
    /* t=0 */w[0] = Toom3Multi(m0, n0);       //w(0) = p(0)q(0)
    M = m2 + m1 + m0;
    N = n2 + n1 + n0;                         //polynomial = m2 + m1 + m0
    /* t=1 */w[1] = Toom3Multi(M, N);         //r(1) = p(1)q(1)
    M = m2.multiply(4) + m1.multiply(2) + m0;
    N = n2.multiply(4) + n1.multiply(2) + n0; //polynomial =(4*x2 + 2*x1 + x0)
    /* t=2 */w[2] = Toom3Multi(M, N);         //r(2) = p(2)q(2)
    
    M = m2.multiply(9) + m1.multiply(3) + m0;
    N = n2.multiply(9) + n1.multiply(3) + n0; //polynomial =(9*x2 + 3*x1 + x0)
    /* t=3 */w[3] = Toom3Multi(M, N);         //w(3) = p(3)q(3)
    //polynomial =  m2
    /* t=∞ */w[4] = Toom3Multi(m2, n2);       //r(∞) = p(∞)q(∞)
}



//IDEA:
//Splitting
//Evaluation : to evaluate p(·) and q(·) at various points
//Pointwise multiplication : multiply their values at these points to get points on the product polynomial.
//Interpolation : Finally interpolate to find its coefficients.
//One unusual point value that is frequently used is infinity, written ∞ or 1/0. To "evaluate" a polynomial p at infinity actually means to take the limit of p(x)/xdeg p as x goes to infinity. Consequently, p(∞) is always the value of its highest-degree coefficient (in the example above coefficient m2).

LongInt Toom3Multi(const LongInt& m, const LongInt& n) {
    if (m.getSize() == 0 || n.getSize() == 0) return LongInt("0");
    if (m.getSize() == 1) return n.multiply(m[0]);
    if (n.getSize() == 1) return m.multiply(n[0]);
    long maxSize = (std::max(m.getSize(), n.getSize()) + 2) / 3;
    LongInt m2, m1, m0, n2, n1, n0, Anew, Bnew;   //splitting in base 10: p(x) = m2 * x^2 + m1 * x1 + m0
    split3(m, m2, m1, m0, maxSize);                     //                      q(x) = n2 * x^2 + n1 * x1 + n0
    split3(n, n2, n1, n0, maxSize);
    //d[] - coefficients of new polynom after interpolation
    LongInt w[5], d[5]; //a polynomial of degree d is uniquely determined by d + 1 points. In our case it's 5!
    productPolynomial(w, m2, m1, m0, n2, n1, n0);
    /*Reverse Matrix
     0      0      0      0       1
     - 1/2    1/6    1/2   -1/6      2
     -1     1/2    1/2     0      -1
     1/2    1/3    -1     1/6     -2
     1      0      0      0       0
     
     
     
     0    0    0    0    1
     -1/6  1/2 -1/2  1/6  -6
     1  -5/2   2  -1/2    11
     -11/6  3   -3/2  1/3    -6
     1    0    0    0    0
     */
    
    d[4] = w[4];
    d[3] = (w[3] - w[0] + w[1].multiply(3) - w[2].multiply(3)) / 6 - w[4].multiply(6);
    d[2] = w[0] + w[2].multiply(2) + w[4].multiply(5) + w[4].multiply(6) - (w[1].multiply(5)+w[3]) / 2;
    d[1] = w[1].multiply(3) - w[4].multiply(6) + ((w[3] - w[0]).multiply(2) - (w[0] + w[2]).multiply(3).multiply(3))/6;
    d[0] =            w[0];
    LongInt res;
    res = d[0] + d[1].moveDecimal(maxSize) + d[2].moveDecimal(2 * maxSize) + d[3].moveDecimal(3 * maxSize) + d[4].moveDecimal(4 * maxSize);
    return res;
}

LongInt Toom3::mult(LongInt& m, LongInt& n) {
    return Toom3Multi(m, n);
}



#define PI 3.1415926535897932384626433832795028841971693993751
typedef complex<double> Complex;

// Fast Fourier Transform
void Furie(vector<Complex> & a, bool invert){
    int n = (int)a.size();
    if (n == 1)  return;
    for (int i = 1, j = 0; i < n; ++i){
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1){
        double ang = 2 * M_PI / len * (invert ? -1 : 1);
        Complex wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len){
            Complex w(1);
            for (int j = 0; j < len / 2; ++j){
                Complex u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (int i = 0; i < n; ++i)
            a[i] /= n;
}
LongInt  Strassen::mult(LongInt& first, LongInt& second){
    vector<Complex> fa(first.digits.begin(), first.digits.end()),
    fb(second.digits.begin(), second.digits.end());
    unsigned long n = 1, k = max(first.digits.size(), second.digits.size());
    while (n < k) n <<= 1;
    n <<= 1;
    fa.resize(n); fb.resize(n);
    Furie(fa, false); Furie(fb, false);
    for (int i = 0; i < n; ++i) fa[i] *= fb[i];
    Furie(fa, true);
    LongInt R("0", 1);
    
    for (int i = 0; i < n; ++i) {
        int s = R.digits.back() + int(fa[i].real() + 0.5) + 10;
        R.digits.back() = s % 10;
        R.digits.push_back(s / 10 - 1);
    }
    
    R.size = R.digits.size();
    strip(R);
    return R;
}
