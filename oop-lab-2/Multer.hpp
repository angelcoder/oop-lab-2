//
//  Multer.hpp
//  oop-lab-2
//
//  Created by Anhelina Lohvina on 05.10.2018.
//  Copyright © 2018 Anhelina Lohvina. All rights reserved.
//

#ifndef Multer_hpp
#define Multer_hpp

#include <stdio.h>
#include "LongInt.hpp"
#include "Multer.hpp"

class LongInt;

class Multer {
public:
    virtual LongInt mult(LongInt& first, LongInt& second)=0;
};

class Multiplication : public Multer {
public:
    LongInt mult(LongInt& a, LongInt& b) override;
};

class Karatsuba : public Multer {
public:
    LongInt mult(LongInt& a, LongInt& b) override;
};

class Toom3 : public Multer {
public:
    LongInt mult(LongInt& a, LongInt& b);
};

class Strassen : public Multer {
public:
    LongInt mult(LongInt& a, LongInt& b);
};
class Shonhage: public Multer {
public:
    LongInt mult(LongInt& a, LongInt& b);
};


#endif /* Multer_hpp */
