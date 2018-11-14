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

using namespace std;

void primeResult (bool test){
    if (!test) std::cout<<"Composite";
    else std::cout << "Prime";
}
int main() {
    try {
        ll NUMBER = 1;
        cin >> NUMBER;
        bool test = true;
        
        test = Rabin_Miller(NUMBER);
        cout << "Rabin_Miller      ";
        primeResult (test);
        
        test = Lehmann(NUMBER);
        cout << "\nLehmannn          ";
        primeResult (test);
        
        test = Soloway_Strassen(NUMBER);
        cout << "\nSoloway_Strassen  ";
        primeResult (test);
        cout << endl;
        //================================================
        cout << " ==================================\n";
        string s1, s2;
        cin >> s1 >> s2;
        LongInt a(s1), b(s2), c(""), sum(""), sub("");
        LongDouble div("");
        sum = a + b;
        sub = a - b;       LongInt::m = new Karatsuba; c = a * b;
        cout << "Cook division: \n";
        div = a / b;
        cout << "sum = " << string(sum) << endl;
        cout << "sub = " << string(sub) << endl;
        cout << "div = " << string(div) << endl;
        
        cout << "Multiplication string: \n";
        
        LongInt::m = new Karatsuba;
        c = a * b;
        cout << "Karatsuba  " << string(c)<<endl;
        
        LongInt::m = new Strassen;
        c = a * b;
        cout << "Strassen   " << string(c)<<endl;
        
        LongInt::m = new Toom3;
        c = a * b;
        cout << "Toom3      " << string(c)<<endl;
        
        //================================================
        cout << " ==================================\n";
        string s;
        cin >> s;
        a = LongInt(s);
        cout << "1/" << s << "=" << string(a.inverse()) << endl;
        
        vector<int> v1 = {8,7,6,4,3};
        vector<int> v2 = {7, 5, 4};
        LongInt av(v1), bv(v2), cv(""), sumv(""), subv("");
        sumv = av + bv;
        subv = av - bv;
        cout << "sum = " << string(sumv) << endl;
        cout << "sub = " << string(subv) << endl;
        
        cout << "Multiplication vector: \n";
        
        LongInt::m = new Karatsuba;
        cv = av * bv;
        cout << "Karatsuba  " << string(cv)<<endl;
        
        LongInt::m = new Toom3;
        cv = av * bv;
        cout << "Toom3      " << string(cv)<<endl;
        
        LongInt::m = new Strassen;
        cv = av * bv;
        cout << "Strassen   " << string(cv)<<endl;
        //================================================
        cout << " ==================================\n";
        
        
        bool e = 0, ne = 1;
        bool ab = 0, ba = 1;
        bool aNb = 0, bNa = 1;
        
        if (a==b) {e = 1; ne = 0;}
        if (a>=b) {ab = 1;        }
        if (a > b) {aNb = 1; bNa = 0;}
        cout << "Testing results:" << endl;
        
        
        cout << "A == B:" << '\t' << e << endl;
        cout << "A != B:" << '\t' << ne << endl;
        cout << "A >= B:" << '\t' << ab << endl;
        cout << "A > B:" << '\t' << aNb << endl;
        cout << "A <= B:" << '\t' << ba << endl;
        cout << "A < B:" << '\t' << bNa << endl;
        
    }
    catch (const invalid_argument &ex){ std::cout << ex.what();}
    catch (...) { cout << "ERROR! Something is wrong!" << endl;}
    return 0;
}
