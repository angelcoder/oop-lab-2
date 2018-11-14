//
//  LongInt.cpp
//  oop-lab-2
//
//  Created by Anhelina Lohvina on 05.10.2018.
//  Copyright © 2018 Anhelina Lohvina. All rights reserved.
//

#include "LongInt.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <deque>
#include <cstdlib>
#include <list>
#include <cmath>
#include "LongDouble.hpp"
using namespace std;


LongInt::LongInt(std::string s, bool sign) {
    this->sign = sign;
    size = s.length();
    for (long i = size - 1; i >= 0; i--) {
        int x = s.at(i) - 48;  // 48 is the ASCII value of '0'
        digits.push_back(x);
    }
}
LongInt::LongInt(std::vector<int>& numVec, bool sign) {
    this->sign = sign;
    size = numVec.size();
    for (int i = 0; i < size; i++) digits.push_back(numVec[i]);
    long i = digits.size() - 1;
    while (i >=1 && digits.at(i) == 0) {
        digits.pop_back();
        size--;
        i--;
    }
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

LongInt& LongInt::operator=(const LongInt& other) & noexcept {
    if (this == &other) return *this;
    sign = other.sign;
    size = other.size;
    digits = {};
    for (int i = 0; i < size; i++) {
        this->digits.push_back(other[i]);
    }
    return *this;
}

LongInt& LongInt::operator=(LongInt&& other)& noexcept {
    if (this == &other) return *this;
    sign = other.sign;
    size = other.size;
    digits = {};
    for (int i = 0; i < size; i++) {
        this->digits.push_back(other.digits.at(i));
    }
    return *this;
}

LongInt LongInt::operator - (){
    LongInt New = *this;
    if(New.sign == 1) New.sign = 0;
    return New;
}

LongInt LongInt::operator+(const LongInt& other) const{
    if (size == 0) return other;
    if (other.getSize() == 0) return *this;
    if (sign != other.getSign()) {
        LongInt res("");
        if (sign) { res = *this - other;}
        else {res = other - *this;}
        return res;
    }
    int add = 0;
    long long minSize= std::min(size, other.size) ;
    long long maxSize = std::max(size, other.size);
    std::vector<int> newDigits;
    for (long long i = 0; i < minSize; i++) {
        int x = digits.at(i) + other.digits.at(i) + add;
        newDigits.push_back(x % 10);
        add = x / 10;
    }
    long pos = minSize;
    while (pos<maxSize) {
        int x;
        if (other.size > size) { x = other.digits.at(pos) + add;}
        else { x = digits[pos] + add;}
        newDigits.push_back(x % 10);
        add = x / 10;
        pos++;
    }
    if (add > 0) newDigits.push_back(add);
    return LongInt(newDigits);
    
}

LongInt sub(const LongInt& first, const LongInt& other) {
    int subtr = 0;
    long minSize = std::min(first.getSize(), other.getSize());
    long maxCap = std::max(first.getSize(), other.getSize());
    std::vector<int> newDigits;
    for (int i = 0; i < minSize; i++) {
        int x = first[i] - other[i] - subtr;
        subtr = 0;
        if (x < 0) {
            x += 10;
            subtr = 1;
        }
        newDigits.push_back(x);
    }
    int pos = int(minSize); // HAVE TO FIX IN THE FUTURE
    while (pos<maxCap) {
        int x;
        if (other.getSize() > first.getSize()) { x = other[pos] - subtr;}
        else { x = first[pos] - subtr;}
        subtr = 0;
        if (x < 0) {
            x += 10;
            subtr = 1;
        }
        newDigits.push_back(x);
        pos++;
    }
    return LongInt(newDigits);
}

LongInt LongInt::operator-(const LongInt& other) const{
    LongInt ans("");
    if (size == 0 || other.getSize()==0) ans = *this;
    else if (*this >= other) ans = sub(*this, other);
    else {
        ans = sub(other, *this);
        ans.setSign(false);
    }
    return ans;
}

LongInt LongInt::operator *(LongInt& other) { return m->mult(*this, other); }

//not working with the sign involved
bool LongInt::operator >=(const LongInt& other) const{
    // basic checks
    if (sign > other.sign) return true;
    if (sign < other.sign) return false;
    if (digitsNum() > other.digitsNum()) return true;
    if (digitsNum() < other.digitsNum()) return false;
    
    // per digit comparison
    for (int i = (int)digitsNum() - 1; i >= 0; --i){
        if (digits[i] > other.digits[i])
            return true;
        if (digits[i] < other.digits[i])
            return false;
    }
    return true;
}

bool LongInt::operator > (const LongInt& other) const{
    return (*this >= other) && (*this != other);
}
bool LongInt::operator < (const LongInt& other){
    return (*this <= other) && (*this != other);
}

bool LongInt::operator <= (const LongInt& other){
    
    return true;
}

//sign check isn't working
bool LongInt::operator ==(const LongInt& other) const {
    // basic checks
    if (sign != other.sign) return false;
    if (digitsNum() != other.digitsNum()) return false;
    // per digit comparison
    for (int i = 1; i <= digitsNum(); ++i)
        if (digits[digitsNum() - i] != other.digits[digitsNum() - i])
            return false;
    return true;
}

bool LongInt::operator != (const LongInt& other) const{
    return !(*this == other);
}

//NOT working with negatives yet
LongInt::operator std::string() const {
    std::string  res;
    for (int i = 0; i < size; i++)
        res += digits.at(i) + '0';
    if (!sign) res += '-';
    reverse(res.begin(), res.end());
    return res;
}

std::ostream& operator << (std::ostream& out, LongInt Number){
    out << (std::string)Number;
    return out;
}
LongInt abs(LongInt a) {
    LongInt New = a;
    New.sign = 1;
    return New;
}
void strip(LongInt& a) {
    while (a.size > 1 && a.digits.back() == 0) {
        a.size--;
        a.digits.pop_back();
    }
}

LongInt LongInt:: operator/(int n) const {
    std::string newStr="";
    int add = 0;
    for (long i = size - 1; i >= 0; i--) {
        int x = (add + digits[i]) / n;
        if (newStr!="" || x!=0)
            newStr=newStr+std::to_string(x);
        add = 10 * (add + digits[i] - x*n);
    }
    return LongInt(newStr, sign);
}

LongInt LongInt::multiply(int n) const {
    if (n == 0 || size==0) return LongInt("0");
    std::vector<int> newDigits;
    int add = 0;
    for (int i = 0; i < size; i++) {
        int x = digits.at(i)*n+add;
        newDigits.push_back(x % 10);
        add = x / 10;
    }
    if (add > 0) newDigits.push_back(add);
    return LongInt(newDigits);
}

//дописує в кінці числа x нульових розрядів
//if number is zero NO change
LongInt& LongInt::normalize(long x) {
    if (x <= 0) return *this;
    if (std::string(*this) == "0" || size==0) return *this;
    std::string newStr = std::string(*this);
    for (int i = 0; i < x; i++) newStr = newStr + "0";
    LongInt result(newStr);
    *this = result;
    return *this;
}

LongInt&  LongInt::moveDecimal(long x) {
    if (x <= 0) return *this;
    if (std::string(*this) == "0" || size==0) return *this;
    std::string newStr = std::string(*this);
    for (int i = 0; i < x; i++) newStr = newStr + "0";
    LongInt result(newStr);
    *this = result;
    return *this;
}

LongInt LongInt::operator -= (LongInt& other){
    LongInt New = *this - other;
    *this = New;
    return *this;
}
LongInt LongInt::operator >> (int n)
{
    LongInt New = *this;
    for (int i = 0; i < n; ++i)
        New.digits.erase(New.digits.begin());
    return New;
}

LongDouble LongInt::inverse(){
    LongDouble num(*this);
    LongDouble current(LongInt("1"), this->getSize());
    int accuracy = 2 * this->getSize() + 3;
    for (long i = 0; i < accuracy; i++)
        current = current * (LongDouble("2") - num * current);
    return current;
}

LongDouble LongInt::operator/ (LongInt& other) {
    LongDouble inverse = other.inverse();
    LongDouble New = LongDouble(*this)*inverse;
    return New;
}


LongInt LongInt::operator% (const int & y) {
    int t = y, r;
    LongInt p;
    p.sign = 1;
    if (t<0) { p.sign = 0; t = -t; }
    while (t) {
        r = t % 10;
        t = t / 10;
        p.digits.push_back(r);
    }
    p.digits.push_back(t);
    return (*this) % p;
}
