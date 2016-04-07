#ifndef MYSTACK
#define MYSTACK
#include <conio.h>
#include <cstdlib>

using namespace std;
// Implementation of a stack-based linked list(LIFO).
template <class T>

class MyStack{
    class Node{
    public:
        T value;
        Node *next;
    };
    Node *top;
    int countElem;

public:

    //Default constructor
    MyStack(){
        top = nullptr;
        countElem = 0;
    }
    //Destructor
    ~MyStack(){
        while(top != nullptr){
            Node *temp = top->next;
            delete top;
            top = temp;
        }
    }

    // Adding an element to the top of the stack
    void push(T elem){
        Node *tmp = new Node;
        tmp->value = elem;
        if(top == nullptr){
            tmp->next = nullptr;
            top = tmp;
        }
        else{
            tmp->next = top;
            top = tmp;
        }
        countElem++;    }

    // Removing an item from the top of the stack.
    void pop(){
        if(isEmpty()){
            cout<<"Empty Stack!!!"<<endl;
            exit(EXIT_FAILURE);
        }
        else{
            Node *temp = top->next;
            if(countElem > 0) {
                if(temp != nullptr){
                    delete top;
                    top = temp;
                    countElem--;
                }
                else{
                    delete top;
                    countElem = 0;
                }
            }
        }
    }


    // Getting the value of the top element of the stack.
    T getTop(){
        return top->value;
    }

    //Stack size.
    int size(){
        return countElem;
    }

    // Clear the stack.
    void clear() {
        while(!isEmpty())
            pop();
    }


    // Is the stack empty.
    bool isEmpty(){
        if(countElem == 0){
            return true;
        }
        else{
            return false;
        }
    }

    // Display stack.
    void print(){
        Node *temp = top;
        while(temp != nullptr){
            cout<<temp -> value<<" ";
            temp = temp->next;
        }
        cout<<endl;

    }
};

#endif//MYSTACK
