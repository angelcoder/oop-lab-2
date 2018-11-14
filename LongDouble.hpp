//
//  LongDouble.hpp
//  Lab 2 opyty
//
//  Created by Anhelina Lohvina on 14.11.2018.
//  Copyright © 2018 Anhelina Lohvina. All rights reserved.
//

#ifndef LongDouble_hpp
#define LongDouble_hpp

#include <stdio.h>
#include "LongInt.hpp"
class LongDouble{
public:
    LongDouble(string s="", bool sign_ = true);
    LongDouble(LongInt myLong_, int decim_=0);
    LongDouble operator+(const LongDouble& other) const;
    LongDouble operator *(const LongDouble& other);
    operator string() const;
    int getDecim() const;
    friend LongDouble operator-(const LongDouble& first, const LongDouble& other);
    LongDouble doubleResize(int x); //leaves only x decimal points
private:
    LongInt myLong; //long integer=long real*10^decim
    int decim=0; //number of digits after decimal point
};

#endif /* LongDouble_hpp */
