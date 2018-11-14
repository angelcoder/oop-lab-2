//
//  LongDouble.cpp
//  oop-lab-2
//
//  Created by Anhelina Lohvina on 30.10.2018.
//  Copyright © 2018 Anhelina Lohvina. All rights reserved.
//

#include "LongDouble.hpp"

LongDouble::LongDouble(std::string s, bool sign_) {
    int pos = s.length() - 1;
    while (pos >= 0 && pos > s.find(".") && s.at(pos) == '0') {
        s.erase(s.begin() + pos, s.end());
        pos--;
    }
    if (s.find(".") != -1) decimal_point = s.length() - s.find(".") - 1;
    if (s.find(".")!=-1) s.erase(s.find("."), 1);
    myLong = LongInt(s, sign_);
}

LongDouble::LongDouble(LongInt myLong_, int decim_) {
    std::string str = std::string(myLong_);
    int deleted0 = 0;
    long long pos = str.length() - 1;
    while (pos>=0 && str.at(pos) == '0' && pos>=str.length()-decim_) {
        pos--; deleted0++;
    }
    if (pos+1<str.length())
        str.erase(str.begin()+pos + 1, str.end());
    decimal_point = decimal_point - deleted0;
    myLong = LongInt(str, myLong_.getSign());
}
int LongDouble::getDecim() const{ return decimal_point; }

LongDouble::operator std::string() const {
    std::string str = std::string(myLong);
    if (decimal_point<str.length())
        str.insert(str.begin()+str.length() - decimal_point, '.');
    else {
        while (str.length() < decimal_point)
            str = "0" + str;
        str = "0." + str;
    }
    return str;
}
LongDouble LongDouble::operator+(const LongDouble& other)const {
    int newDecim = std::max(decimal_point, other.getDecim());
    LongInt x = myLong;
    x.moveDecimal(newDecim - decimal_point);
    LongInt y = other.myLong;
    y.moveDecimal(newDecim - other.getDecim());
    return LongDouble(x+y, newDecim);
}

LongDouble operator-(const LongDouble& first, const LongDouble& other) {
    int newDecim = std::max(first.getDecim(), other.getDecim());
    LongInt x = first.myLong;
    x.moveDecimal(newDecim - first.getDecim());
    LongInt y = other.myLong;
    y.moveDecimal(newDecim - other.getDecim());
    return LongDouble(x - y, newDecim);
}

LongDouble LongDouble::operator *(const LongDouble& other) {
    int newDecim = std::max(decimal_point, other.getDecim());
    LongInt x = myLong;
    x.moveDecimal(newDecim - decimal_point);
    LongInt y = other.myLong;
    y.moveDecimal(newDecim - other.getDecim());
    return LongDouble(x*y, 2*newDecim);
}
std::string deletePoint(std::string s) {
    if (s.find(".")!=-1)
        s.erase(s.find("."), 1);
    return s;
}

LongDouble LongDouble::doubleResize(int x) {
    std::string str = std::string(*this);
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
