/**
* HashTable.cpp
* Project 4 - Hash Table
* CS 3100 - Adam Hume
*
* This is the class file for the HashTable class. This file contains all the implementation
* for the functions within the HashTable header file.
*/

#include "HashTable.h"
#include <iostream>;

/* HashTableBucket()
* The default constructor with default bucket type of ESS.
*/
HashTableBucket::HashTableBucket() : BucketType(ESS)
{
    Key = "";
    Value = 0;
}

/* HashTableBucket(key, value)
* A parameterized constructor to initialize the key and value,
* sets bucket type to NORMAL by default.
*/
HashTableBucket::HashTableBucket(const string& key, const size_t& value) : BucketType(N)
{
    this->Value = value;
    this->Key = key;
}

/* load(key, value)
* A load method to load a key-value pair into a bucket,
* marks the bucket's type as NORMAL.
*/
void HashTableBucket::load(const std::string& key, const size_t& value)
{
    this->Value = value;
    this->Key = key;
    BucketType = N;
}

/* isEmpty()
* This method will return whether the bucket is empty, regardless of
* if it has had data placed in it or not.
*/
bool HashTableBucket::isEmpty() const
{
    return (BucketType < 2);
}

/* operator<<bucket
* overload of the stream insertion operator to print the bucket's contents.
*/
ostream& operator<<(ostream& os, const HashTableBucket& bucket)
{
    os << "<" << bucket.Key << ", " << bucket.Value << ">";
    return os;
}

/* HashTable(initCapacity)
* default constructor for the HashTable class
* initCapacity defaults to 8 if no value is entered
*/
HashTable::HashTable(size_t initCapacity) : Size(0)
{
    Capacity = initCapacity;

    //Fill the Hash table with empty buckets, while inserting the corresponding index to a random position in PRProbe
    for (size_t i = 0; i < Capacity - 1; i++)
    {
        Map.emplace_back();
        PRProbe.insert(PRProbe.begin() + rand() % (i + 1), i + 1);
    }
    Map.emplace_back();
    PRProbe.insert(PRProbe.begin(), 0);
}

/* insert(key, value)
* Inserts a new key-value pair into the table. Duplicate keys are NOT allowed.
* returns true if the insertion was successful. resizes the table if alpha is > 0.5.
*/
bool HashTable::insert(const string& key, const size_t& value)
{
    // setup for hashing function
    hash<string> hash;
    size_t i = 0;
    do
    {
        // run hashing function and check bucket type, incrementing i when a collision occurs
        // and terminating if a duplicate key is found
        size_t Probe = (hash(key) + PRProbe[i]) % Capacity;
        if (Map[Probe].BucketType == 2)
        {
            if (Map[Probe].Key == key) return false;
            i++;
        }
        else
        {
            //load key/value pair into bucket and check if this brings the hash table over half capacity
            //doubling it if thats the case
            Map[Probe].load(key, value);
            Size++;
            if (alpha() >= 0.5) resize();
            return true;
        }
    }
    while (i < Capacity);
    return false;
}

/* remove(key)
* If the key is in the table, remove will “erase” the key-value pair from the table.
* In this case, it just marks the bucket as empty (EAR)
*/
bool HashTable::remove(const string& key)
{
    hash<string> hash;
    size_t i = 0;
    do
    {
        //mark bucket as empty after removal if matching key pair on a normal bucket is found
        size_t Probe = (hash(key) + PRProbe[i]) % Capacity;
        if (Map[Probe].BucketType == 2 && Map[Probe].Key == key)
        {
            Map[Probe].BucketType = EAR;
            Size--;
            return true;
        }
        //check if bucket is empty since start, ending the loop prematurely if true;
        if (Map[Probe].BucketType == 0) return false;
        i++;
    }
    while (i < Capacity);
    return false;
}

/* contains(key)
* returns true if the key is in the table and false if it isn't.
*/
bool HashTable::contains(const string& key) const
{
    hash<string> hash;
    size_t i = 0;
    do
    {
        //if matching key found, return true. If Empty Since Start bucket found, return false
        size_t Probe = (hash(key) + PRProbe[i]) % Capacity;
        if (Map[Probe].BucketType == 2 && Map[Probe].Key == key) return true;
        if (Map[Probe].BucketType == 0) return false;
        i++;
    }
    while (i < Capacity);
    return false;
}

/* get(key)
* returns value associated with the key if it is in the hash table, or returns nullopt if it is not.
*/
optional<size_t> HashTable::get(const string& key) const
{
    hash<string> hash;
    size_t i = 0;
    do
    {
        //if matching key found, return value. If Empty Since Start bucket found, return nullopt
        size_t Probe = (hash(key) + PRProbe[i]) % Capacity;
        if (Map[Probe].BucketType == 2 && Map[Probe].Key == key) return Map[Probe].Value;
        if (Map[Probe].BucketType == 0) return nullopt;
        i++;
    }
    while (i < Capacity);
    return nullopt;
}

/*operator[key]
* returns a reference to the value associated with the key in the table.
* no safeguards if the value is not within the table however.
*/
size_t& HashTable::operator[](const string& key)
{
    hash<string> hash;
    size_t i = 0;
    do
    {
        //if matching key found, return value's reference. otherwise this will probably fail
        size_t Probe = (hash(key) + PRProbe[i]) % Capacity;
        if (Map[Probe].BucketType == 2 && Map[Probe].Key == key) return Map[Probe].Value;
        if (Map[Probe].BucketType == 0) break;
        i++;
    }
    while (i < Capacity);
}

/* keys()
* returns all keys within the table inside a vector.
*/
vector<string> HashTable::keys() const
{
    vector<string> Keys;
    for (size_t i = 0; i < Capacity; i++)
    {
        // loop through Hash Table and push the keys into a vector
        if (Map[i].BucketType == N) Keys.push_back(Map[i].Key);
        else Keys.push_back("");
    }
    return Keys;
}

/* alpha()
* returns load factor for the HashTable. an alpha of 1/2 necessitates resizing.
*/
double HashTable::alpha() const
{
    return static_cast<double>(Size) / Capacity;
}

/* capacity()
* returns capacity from Hashtable
*/
size_t HashTable::capacity() const
{
    return Capacity;
}

/* size()
* returns size from Hashtable
*/
size_t HashTable::size() const
{
    return Size;
}

/* resize()
* creates a hash table of double the size, and then adds all the buckets over one by one
* then copies all the variables over to the one running the function.
*/
void HashTable::resize()
{
    // create temporary hash table of double size
    HashTable Temp = HashTable(Capacity * 2);
    for (size_t i = 0; i < Capacity; i++)
    {
        // insert all non-empty buckets to temporary hash map
        if (Map[i].BucketType == 2)
        {
            Temp.insert(Map[i].Key, Map[i].Value);
        }
    }
    // copy over all new values from temporary hash map
    Map = Temp.Map;
    PRProbe = Temp.PRProbe;
    Capacity = Temp.Capacity;
}

/* operator<<hashTable
* overload of << operator to print out the contents of a hash table.
* uses formating:
* "Bucket 1: <value, key>"
* "Bucket 3: <value, key>"
* always in order
*/
ostream& operator<<(ostream& os, const HashTable& hashTable)
{
    for (size_t i = 0; i < hashTable.capacity(); i++)
    {
        if (hashTable.Map[i].BucketType == 2) os << "Bucket " << i << ": " << hashTable.Map[i] << endl;
    }
    return os;
}
