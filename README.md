[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7RAFczHS)
# Project 4 - HashTable

Project description can be found [in the repo](Project4_HashTable.pdf)

Place your complexity analysis below.

---
### Complexity Analysis

keep in mind that "N" is the capacity while "n" is the size
> Insert
> 
> Insert has (on average) a time complexity of O(1) as the hashmap will keep doubling in size to accomodate the data. However, this doubling of size has a time complexity of O(N). Additionally, in another the worst case scenario the hash function could keep colliding with other data, taking "n" steps which is still O(N)
>
> Average case O(1), Worst case O(N)

> Remove
> 
> Just like with insert, except a table resize will never happen when removing values. Although very unlikely a worst case time complexity of n is still possible, but still very unlikely
>
> Average case O(1), Worst case O(n)

> Contains
> 
> This function was built to access data the same way as it was put in, so its complexity is like with insert, without the table resize. Although very unlikely a worst case time complexity of n is still possible, but still very unlikely
>
> Average case O(1), Worst case O(n)

> Get
> 
> Get runs the same way as Contains, except it returns a key and a value. Thus it has the same time complexity
>
> Average case O(1), Worst case O(n)

> Operator[]
> 
> the overload for the [] operator runs the same way as Get, except it returns a reference to modify the original value. Thus it would have the same time complexity
>
> Average case O(1), Worst case O(n)



