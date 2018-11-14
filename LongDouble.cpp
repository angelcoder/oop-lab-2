//
//  LongDouble.cpp
//  Lab 2 opyty
//
//  Created by Anhelina Lohvina on 14.11.2018.
//  Copyright © 2018 Anhelina Lohvina. All rights reserved.
//

#include "LongDouble.hpp"

LongDouble::LongDouble(string s, bool sign_) {
    int pos = s.length() - 1;
    while (pos >= 0 && pos > s.find(".") && s.at(pos) == '0') {
        s.erase(s.begin() + pos, s.end());
        pos--;
    }
    if (s.find(".") != -1) decim = s.length() - s.find(".") - 1;
    if (s.find(".")!=-1) s.erase(s.find("."), 1);
    myLong = LongInt(s, sign_);
}

LongDouble::LongDouble(LongInt myLong_, int decim_) {
    string str = string(myLong_);
    int deleted0 = 0;
    long long pos = str.length() - 1;
    while (pos>=0 && str.at(pos) == '0' && pos>=str.length()-decim_) {
        pos--; deleted0++;
    }
    if (pos+1<str.length())
        str.erase(str.begin()+pos + 1, str.end());
    decim = decim_ - deleted0;
    myLong = LongInt(str, myLong_.getSign());
}
int LongDouble::getDecim() const{ return decim; }

LongDouble::operator string() const {
    string str = string(myLong);
    if (decim<str.length())
        str.insert(str.begin()+str.length() - decim, '.');
    else {
        while (str.length() < decim)
            str = "0" + str;
        str = "0." + str;
    }
    return str;
}
LongDouble LongDouble::operator+(const LongDouble& other)const {
    int newDecim = max(decim, other.getDecim());
    LongInt x = myLong;
    x.moveDecimal(newDecim - decim);
    LongInt y = other.myLong;
    y.moveDecimal(newDecim - other.getDecim());
    return LongDouble(x+y, newDecim);
}

LongDouble operator-(const LongDouble& first, const LongDouble& other) {
    int newDecim = max(first.getDecim(), other.getDecim());
    LongInt x = first.myLong;
    x.moveDecimal(newDecim - first.getDecim());
    LongInt y = other.myLong;
    y.moveDecimal(newDecim - other.getDecim());
    return LongDouble(x - y, newDecim);
}

LongDouble LongDouble::operator *(const LongDouble& other) {
    int newDecim = max(decim, other.getDecim());
    LongInt x = myLong;
    x.moveDecimal(newDecim - decim);
    LongInt y = other.myLong;
    y.moveDecimal(newDecim - other.getDecim());
    return LongDouble(x*y, 2*newDecim);
}
string deletePoint(string s) {
    if (s.find(".")!=-1)
        s.erase(s.find("."), 1);
    return s;
}
LongDouble LongDouble::doubleResize(int x) {
    string str = string(*this);
    int pos = str.find_first_of(".,") + x;
    if (pos >= str.length()) {
        return this->doubleResize(str.length() - str.find_first_of(".,") - 1);
    }
    int lastDig = str.at(pos + 1);
    str.erase(str.begin() + pos + 1, str.end());
    if (lastDig>= 5) {
        return LongDouble(str, myLong.getSign())+LongDouble(LongInt("1"), x);
    }
    return LongDouble(str, myLong.getSign());
}
