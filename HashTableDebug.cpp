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

int main()
{
    cout << "Its testing time!" << endl;

    //create default hash table
    HashTable Bob = HashTable();

    //insert values checking hash table after each addition
    Bob.insert("AAA", 1);
    cout << Bob << endl;
    Bob.insert("BBB", 2);
    cout << Bob << endl;
    Bob.insert("CCC", 3);
    cout << Bob << endl;

    //testing if hash table will resize once
    Bob.insert("DDD", 4);
    cout << Bob << endl;
    Bob.insert("EEE", 5);
    cout << Bob << endl;
    Bob.insert("FFF", 6);
    cout << Bob << endl;
    Bob.insert("GGG", 7);
    cout << Bob << endl;

    //testing if hash table will resize twice
    Bob.insert("HHH", 8);
    cout << Bob << endl;

    //testing if duplicate elements appear
    Bob.insert("AAA", 9);
    cout << Bob << endl;
    return 0;
}
