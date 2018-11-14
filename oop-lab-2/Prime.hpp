//
//  Prime.hpp
//  Lab 2 opyty
//
//  Created by Anhelina Lohvina on 30.10.2018.
//  Copyright © 2018 Anhelina Lohvina. All rights reserved.
//

#ifndef Prime_hpp
#define Prime_hpp

#include <stdio.h>

typedef long long ll;
long long powermod(ll base, ll exponent, ll modulus);

bool   commonIsPrime(ll n);
bool   Rabin_Miller(ll p);
bool   Lucas_Lehmer(ll p);
bool   Lehmann(ll p);
bool   Soloway_Strassen(ll p);
#endif /* Prime_hpp */
