//
//  LongDouble.hpp
//  oop-lab-2
//
//  Created by Anhelina Lohvina on 30.10.2018.
//  Copyright © 2018 Anhelina Lohvina. All rights reserved.
//

#ifndef LongDouble_hpp
#define LongDouble_hpp

#include <stdio.h>
#include "LongInt.hpp"

class LongDouble{
public:
    LongDouble(std::string s="", bool sign_ = true);
    LongDouble(LongInt myLong_, int decim_=0);
    LongDouble operator+(const LongDouble& other) const;
    LongDouble operator *(const LongDouble& other);
    operator std::string() const;
    int getDecim() const;
    friend LongDouble operator-(const LongDouble& first, const LongDouble& other);
    LongDouble doubleResize(int x); //leaves only x decimal points
private:
    LongInt myLong;
    int decimal_point=0; 
};

#endif /* LongDouble_hpp */
