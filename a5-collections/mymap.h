#ifndef MYMAP
#define MYMAP
#include <conio.h>
#include <cstdlib>
#include <iostream>
using namespace std;

// Implementation of a simply-connected linear type list(LIFO/FIFO).
template<class K, class V>
class MyMap{
    class Node{
    public:
        V value;
        Node *next;
    };

public:
    class my_iterator{
    private:
        * ptr;
    public:
        my_iterator(){}
        my_iterator(K * ptrVec) : ptr(ptrVec){}

        K & operator*(){
            return *ptr;
        }

        K * operator->(){
            return ptr;
        }

        my_iterator & operator++(){
            ++ptr;
            return *this;
        }

        my_iterator & operator++(int){
            my_iterator tmp = *this;
            ++ptr;
            return tmp;
        }

        my_iterator & operator--(){
            --ptr;
            return *this;
        }

        my_iterator & operator--(int){
            my_iterator tmp = *this;
            --ptr;
            return tmp;
        }

        bool operator==(my_iterator it){
            return ptr == it.ptr;
        }

        bool operator!=(my_iterator it){
            return ptr != it.ptr;
        }

    };
    my_iterator begin();
    my_iterator end();

    //MyMap(const MyMap&);
    MyMap& operator=(const MyMap&);
    V& operator[](const K& key);
    // Constructors ----------------------------------------------------------------------------

    // Default constructor
    MyMap(){}

    // The copy constructor
    MyMap(const MyMap& sourceList);

    //Destructor--------------------------------------------------------------------------------
    ~MyMap(){}
    //------------------------------------------------------------------------------------------
    // Methods---------------------------------------------------------------------------------
    void add(const K &key, const V &value);
    void push_back(const K &new_elem);
    void pop_back();
    void print(const MyMap& m);
    void insert(int index,const K & value);
    void remove(int index);


    int size();
};
template<class K, class V>
MyMap<K, V>& MyMap<K, V>::operator=(const MyMap& m) {



}

template<class K, class V>
V& MyMap<K, V>::operator[](const K& key) {

}

template<class K>
MyMap::print(const MyMap& m){
    foreach (MyMap::my_iterator &i, m) {
        cout << i.ptr;
    }
}


template<class K, class V>
MyMap::add(const K &key, const V &value){
    if (exists(key)) return false;
    cont.push_back(make_pair(key, value));
    return true;
}

#endif//MYMAP
