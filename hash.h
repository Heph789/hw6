#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        HASH_INDEX_T ret = 0;
        for (int i = 0; i < 5; ++i)
        {
            unsigned long long w = 0;
            if (size_t(i*6) >= k.size()) {
                continue;
            }
            
            unsigned char a[6];
            int stringRight = k.size()-1-(i*6);
            for (int j = 0; j < 6; ++j)
            {
                int sl = stringRight - j;
                if (sl < 0) a[j] = 0;
                else a[j] = letterDigitToNumber(k[sl]);
            }
            w = baseConversion(a, 0);
            ret += w*rValues[4-i];
        }

        return ret;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter > 96) return letter - 'a'; // is a lowercase letter
        if (letter > 64) return letter - 'A'; // is an uppercase letter
        return (letter - '0') + 26; // is a number
    }

    // Calculates the base conversion from base 36 to decimal (for up to 6 base 36 numbers)
    // for nums, the index corresponds to the 
    unsigned long long baseConversion(unsigned char a[6], int index) const
    {
        const unsigned char r = 36;
        if (index == 5) return a[5];
        return a[index] + r * baseConversion(a, index+1);
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
