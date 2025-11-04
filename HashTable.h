/**
 * HashTable.h
 * Project 4 - Hash Table
 * CS 3100 - Adam Hume
 *
 * This is the header file for the HashTable class. It contains the variable and function
 * declarations, both public and private.
 */

#ifndef PROJECT4_SEQUENCE_H
#define PROJECT4_SEQUENCE_H
#include <string>
#include <vector>
#include <optional>
using namespace std;

//bt = Bucket Type
//ESS = Empty Since Start, EAR = Empty After Removal, N = Normal
enum bt {ESS, EAR, N};

class HashTableBucket {
private:

public:
    string Key;
    size_t Value;
    bt BucketType;

    HashTableBucket();
    HashTableBucket(const string& key, const size_t& value);
    void load(const std::string& key, const size_t& value);
    bool isEmpty() const;
    friend ostream& operator<<(ostream& os, const HashTableBucket& bucket);

};
class HashTable {
private:
    size_t Alpha;
    size_t Capacity;
    size_t Size;
    vector<size_t> PRProbe;

public:
    vector<HashTableBucket> Map;
    HashTable(size_t initCapacity = 8);
    bool insert(const string& key, const size_t& value);
    bool remove(const string& key);
    bool contains(const string& key) const;
    optional<size_t> get(const string& key) const;
    size_t& operator[](const string& key);
    vector<string> keys() const;
    double alpha() const;
    size_t capacity() const;
    size_t size() const;
    friend ostream& operator<<(ostream& os, const HashTable& hashTable);

};

#endif //PROJECT3_SEQUENCE_H