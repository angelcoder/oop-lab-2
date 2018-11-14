//
//  Prime.cpp
//  Lab 2 opyty
//
//  Created by Anhelina Lohvina on 19.10.2018.
//  Copyright © 2018 Anhelina Lohvina. All rights reserved.
//

#include "Prime.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

//I  term: congruent to 1
//II term: NOT congruent to -1 (n-1)
// >>>>> N is composite and a is a witness

bool commonIsPrime(ll n) {
    ll num = sqrt(n) + 1;
    if (n % 2 == 0 && n!=2) return false;
    for (ll i = 3; i < num; i+=2)
        if (n%i == 0) return false;
    return true;
}

//Modular Exponentiation
// (a^exp) % n
ll powermod(ll a, ll exp, ll n){
    ll temp;
    if (exp == 0) return 1;
    if (exp == 1) return (a % n);
    if (exp % 2 == 0){
        temp = powermod(a, exp / 2, n);
        return (temp * temp) % n;
    }
    else{
        temp = powermod(a, (exp - 1) / 2, n);
        temp = (temp * temp) % n;
        temp = (temp * a) % n;
        return temp;
    }
}

bool Rabin_Miller(ll p){
    //basic cheks
    if (p == 2) return true;
    if ((p % 2==0) || p==1) return false;
    srand((unsigned int)time(nullptr));
    ll n = p - 1, s = 0;
    while (n % 2 == 0){ ++s; n >>= 1;} // p - 1 = (2 ** s) * t
    ll wintessNum = log(p) / log(2) + 1;
    
    for (int i = 0; i < wintessNum; ++i){
        ll a = rand() % (p - 3) + 2; // a є [2; p-2]
        ll x = (powermod(a, n, p));
        if (x == 1 || x == p - 1) continue;
        
        ll j = 0;
        for (; j < s; ++j){
            x = (x * x) % p;
            if (x == 1) return false;
            if (x == p - 1) break;
        }
        if (j == s && x != p - 1) return false;
    }
    return true;
}

// works for numbers less than 32
// determines whether the number is Mersenne prime
// p is prime <=> it's Mp is prime
// do for LongInt
bool Lucas_Lehmer(ll p){
    //basic cheks
    if (p == 2) return true;
    if ((p % 2==0) || p==1) return false;
    ll S=4;
    ll k=1;
    ll M = (1 << p) - 1;
    while (k!= p-1) {
        S = ((S * S) - 2) % M;
        k++;
    }
    if (S == 0) return true;
    else return false;
}
//probability count
bool Lehmann(ll p){
    //basic cheks
    if (p == 1) std::cout<<"Not composite and not";
    if (p == 2) return true;
    if ((p % 2==0) || p==1) return false;
    srand((unsigned int)time(nullptr));
    for (int i = 0; i < 30; ++i){
        ll a = rand() % (p - 1) + 1; // a < p
        // a is a witness of p being prime
        ll b = powermod(a, (p - 1) / 2, p);
        ll res = (p + b) % p;
        if (res!= 1 && res != p - 1) // p is definitely not a prime
            return false;
    }
    return true;// If r=1 or –1 the likelihood that p is not prime is at most than 50 percent
    // Repeat this algorithm t times, if the calculation equals to 1 or –1 but does not always equal to 1,
    // Probability that p is a prime after k iterations of Lehmann test can be expressed as p = 1 - 1/(2^k)
}
ll gcd(ll a, ll b){
    // Everything divides 0
    if (a == 0) return b;
    if (b == 0) return a;
    // base case
    if (a == b) return a;
    // a is greater
    if (a > b) return gcd(a-b, b);
    return gcd(a, b-a);
}

// Jacobi's symbol
ll J(ll a, ll b){
    ll r=1;
    if (a<0) {
        a = -a;
        if (b % 4 == 3) r=-r;
    }
    do{
        ll t=0;
        while (a % 2 == 0) {
            t+=1;
            a/=2;
        }
        
        if (t % 2 == 1) {
            if ((b % 8 == 3) || (b % 8 == 5)) r=-r;
        }
        if ((a % 4 ) == 3 && (b % 4 ) == 3) {r=-r;}
        ll c=a;
        a = b % c;
        b=c;
    } while(a!=0);
    return r;
}
bool Soloway_Strassen(ll p){
    //basic cheks
    if (p == 2) return true;
    if ((p % 2==0) || p==1) return false;
    srand((unsigned int) time(nullptr));
    for (int i = 0; i < 30; ++i){
        ll a = rand() % (p - 1) + 1; // a < p
        if (gcd(a, p) > 1) return false;
        ll j = powermod(a, (p - 1) / 2, p);
        ll _j = J(a, p);
        if ((j + p) % p != (_j + p) % p)
            return false;
    }
    return true;
}
