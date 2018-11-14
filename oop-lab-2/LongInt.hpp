//
//  LongInt.hpp
//  oop-lab-2
//
//  Created by Anhelina Lohvina on 05.10.2018.
//  Copyright © 2018 Anhelina Lohvina. All rights reserved.
//

#ifndef LongInt_hpp
#define LongInt_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "Multer.hpp"
typedef unsigned long ulong;
//need to fix the sign

class LongDouble;

class LongInt {
protected:
    //unsigned long size = 0;
    bool sign = 1;  // 1 for positive
    // 0 for negative
    // 1 for 0!
public:
    unsigned long size = 0;
    std::vector<int> digits = {}; //list of digits of number
    static      Multer *m;
    
    //LongInt(long long);
    LongInt(std::vector<int>& numVec, bool sign=1);
    LongInt(std::string s="", bool sign = 1); //Will not exist after the sign is fixed
    //LongInt(string s); //this will be instead of the upper one
    LongInt(const LongInt& other) = default;
    LongInt(LongInt&& other) = default;
    
    ulong       getSize() const { return size;};
    bool        getSign() const { return sign;};
    void        setSign(bool sign) { this->sign = sign;};
    int         digitsNum() const {return (int)digits.size();}; //amount of digits in number
    int         operator[](int i) const { return digits.at(i);};
    
    LongInt     multiply(int n) const;
    LongInt&    normalize(long x);
    
    LongInt&    operator =(const LongInt& other) & noexcept ;
    LongInt&    operator =(LongInt&& other)& noexcept ;
    LongInt     operator +(const LongInt& other) const;
    LongInt     operator *(LongInt& other);
    LongInt     operator / (int n) const;    //pre: n - is a "digit"
                                             //pre: we are expected to get integer result
    bool        operator >=(const LongInt& other) const;
    bool        operator >(const LongInt& other) const;
    bool        operator <(const LongInt& other);
    bool        operator <=(const LongInt& other);
    bool        operator ==(const LongInt& other) const;
    bool        operator !=(const LongInt& other) const;
    
    LongInt&    moveDecimal(long x);
    
    operator bool() {return sign != 0;}
    operator std::string() const ;
    LongInt operator - ();
    
    friend std::ostream& operator << (std::ostream&, LongInt);
    friend LongInt abs(LongInt);
    friend void strip(LongInt&); //drops out leading zeros
    
    virtual ~LongInt() {};
    
    //LongInt     operator - (LongInt& other);
    //LongInt     operator += (LongInt);
    LongInt     operator -= (LongInt& other);
    
    LongInt operator >> (int n);
    
    LongInt operator-(const LongInt& other) const;
    
    LongDouble operator/(LongInt& other); //Cook's division
    LongDouble inverse();
    
    LongInt operator% (const int & y);
    
};



#endif /* LongInt_hpp */
