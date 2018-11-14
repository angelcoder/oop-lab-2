//
//  main.cpp
//  oop-lab-2
//
//  Created by Anhelina Lohvina on 05.10.2018.
//  Copyright © 2018 Anhelina Lohvina. All rights reserved.
//

#include <iostream>
#include <exception>
#include "LongInt.hpp"
#include "LongDouble.hpp"
#include "Prime.hpp"

void primeResult (bool test){
    if (!test) std::cout<<"Composite";
    else std::cout << "Prime";
}
int main() {
    try {
        ll NUMBER = 1;
        std::cin >> NUMBER;
        bool test = true;
        
        test = Rabin_Miller(NUMBER);
        std::cout << "Rabin_Miller      ";
        primeResult (test);
        
        test = Lehmann(NUMBER);
        std::cout << "\nLehmannn          ";
        primeResult (test);
        
        test = Soloway_Strassen(NUMBER);
        std::cout << "\nSoloway_Strassen  ";
        primeResult (test);
        std::cout << std::endl;
        //================================================
        std::cout << " ==================================\n";
        std::string s1, s2;
        std::cin >> s1 >> s2;
        LongInt a(s1), b(s2), c(""), sum(""), sub("");
        LongDouble div("");
        sum = a + b;
        sub = a - b;       LongInt::m = new Karatsuba; c = a * b;
        std::cout << "Cook division: \n";
        div = a / b;
        std::cout << "sum = " << std::string(sum) << std::endl;
        std::cout << "sub = " << std::string(sub) << std::endl;
        std::cout << "div = " << std::string(div) << std::endl;
        
        std::cout << "Multiplication string: \n";
        
        LongInt::m = new Karatsuba;
        c = a * b;
        std::cout << "Karatsuba  " << std::string(c)<<std::endl;
        
        LongInt::m = new Strassen;
        c = a * b;
        std::cout << "Strassen   " << std::string(c)<<std::endl;
        
        LongInt::m = new Toom3;
        c = a * b;
        std::cout << "Toom3      " << std::string(c)<<std::endl;
        
        //================================================
        std::cout << " ==================================\n";
        std::string s;
        std::cin >> s;
        a = LongInt(s);
        std::cout << "1/" << s << "=" << std::string(a.inverse()) << std::endl;
        
        std::vector<int> v1 = {8,7,6,4,3};
        std::vector<int> v2 = {7, 5, 4};
        LongInt av(v1), bv(v2), cv(""), sumv(""), subv("");
        sumv = av + bv;
        subv = av - bv;
        std::cout << "sum = " << std::string(sumv) << std::endl;
        std::cout << "sub = " << std::string(subv) << std::endl;
        
        std::cout << "Multiplication vector: \n";
        
        LongInt::m = new Karatsuba;
        cv = av * bv;
        std::cout << "Karatsuba  " << std::string(cv)<<std::endl;
        
        LongInt::m = new Toom3;
        cv = av * bv;
        std::cout << "Toom3      " << std::string(cv)<<std::endl;
        
        LongInt::m = new Strassen;
        cv = av * bv;
        std::cout << "Strassen   " << std::string(cv)<<std::endl;
        //================================================
        std::cout << " ==================================\n";
        
        
        bool e = 0, ne = 1;
        bool ab = 0, ba = 1;
        bool aNb = 0, bNa = 1;
        
        if (a==b) {e = 1; ne = 0;}
        if (a>=b) {ab = 1;        }
        if (a > b) {aNb = 1; bNa = 0;}
        std::cout << "Testing results:" << std::endl;
        
        
        std::cout << "A == B:" << '\t' << e << std::endl;
        std::cout << "A != B:" << '\t' << ne << std::endl;
        std::cout << "A >= B:" << '\t' << ab << std::endl;
        std::cout << "A > B:" << '\t' << aNb << std::endl;
        std::cout << "A <= B:" << '\t' << ba << std::endl;
        std::cout << "A < B:" << '\t' << bNa << std::endl;
        
    }
    catch (const std::invalid_argument &ex){ std::cout << ex.what();}
    catch (...) { std::cout << "ERROR! Something is wrong!" << std::endl;}
    return 0;
}
