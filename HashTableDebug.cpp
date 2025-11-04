/**
 * HashTableDebug.cpp
 * Project 4 - Hash Table
 * CS 3100 - Adam Hume
 *
 * This is the file that is to be run for the purposes of debugging.
 * It will be built separately from HashTableTests, so code here is explicitly for debugging
 */
#include <iostream>

#include "HashTable.h"

int main() {
    cout << "Its testing time!" << endl;
    HashTable Bob = HashTable(8);
    Bob.insert("AAA", 1);
    cout << Bob << endl;
    Bob.insert("BBB", 2);
    cout << Bob << endl;
    Bob.insert("CCC", 3);
    cout << Bob << endl;
    Bob.insert("DDD", 4);
    cout << Bob << endl;
    Bob.insert("EEE", 5);
    cout << Bob << endl;
    Bob.insert("FFF", 5);
    cout << Bob << endl;
    Bob.insert("GGG", 5);
    cout << Bob << endl;
    Bob.remove("AAA");
    cout << Bob << endl;
    return 0;
}
