#include <iostream>
#include <myvector.h>
#include <mystack.h>
#include <myqueue.h>
#include <mylist.h>
//#include <mymap.h>
int main()
{
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"*************************MyVector*************************"<<endl;
    MyVector<int> myVector_one;
    for(int i = 0; i<50; i++)
        myVector_one.push_back(i);

    myVector_one.pop_back();
    myVector_one.pop_back();
    myVector_one.pop_back();
    myVector_one.pop_back();

    cout <<"Capacity myVector_one: "<<myVector_one.capacity()<<endl;
    cout<<"Size myVector_one: "<<myVector_one.size()<<endl;

    cout<<endl;

    for(int i=0;i<myVector_one.size();i++)
        cout << " " << myVector_one[i];

    cout << endl << endl;

    cout << "vector_two:" << endl;

    cout << "vector_two = vector_one"<<endl;


    MyVector<int> myVector_two=myVector_one;
    cout <<"Capacity myVector_two: "<<myVector_two.capacity()<<endl;
    cout<<"Size myVector_two: "<<myVector_two.size()<<endl;
    for(int i=0;i<myVector_two.size();i++)
        cout << " " << myVector_two[i];

    cout<<endl;
    cout<<endl;

    MyVector<int> myVector_three(50,16);
    cout<<"myVector_three(30,30)"<<endl;
    for(int i=0;i<myVector_three.size();i++)
        cout << " " << myVector_three[i];

    cout<<endl;
    cout<<endl;


    cout<<"----------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"**************************MyList**************************"<<endl;
    MyList<int> firstTry;
    cout<<"MyList<int> firstTry  \n"<<endl;
    firstTry.add_front(100);
    firstTry.add_front(170);
    firstTry.add_front(150);
    firstTry.add_front(205);
    firstTry.add_front(199);

    cout<<"List size : ";
    cout << firstTry.size() << endl;

    cout << "Initial contents:  \n "<< firstTry;
    firstTry.unique();
    cout << "\n" <<"After firstTry.unique():  \n "<< firstTry;
    firstTry.sort();
    cout << "\n" << "After firstTry.sort():   \n"<< firstTry;

    cout<<endl;
    cout<<endl;

    firstTry.insert(4,55);
    firstTry.insert(1,95);
    firstTry.insert(2,95);

    firstTry.show();


    cout<<endl;
    cout<<"MyList<int> firstTry"<<endl;
    cout<<"List size : ";
    cout<<firstTry.size()<<endl;
    firstTry.show();
    cout<<endl;

    firstTry.set(0,45);

    firstTry.show();
    MyList<string> secondTry;

    cout<<"MyList<int> secondTry \n"<<endl;
    cout << "-- push_front push_back test --" << endl;
        secondTry.push_back("one");
        secondTry.push_back("two");
        secondTry.push_back("three");
        secondTry.push_back("four");
        secondTry.push_back("five");
        secondTry.push_back("six");
        secondTry.push_front("zero");
        secondTry.push_front("neg-one");
        secondTry.push_back("six");
        

cout << endl;

    cout<<"----------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"*************************MyStack*************************"<<endl;
    //stack::push/pop
    MyStack<int> first_stack;
    int sum(10);
    for (int i=0; i<7; ++i)
        first_stack.push(i);
    cout << "Popping out elements...";
    while (!first_stack.isEmpty())
    {
sum += first_stack.getTop();
        first_stack.pop();
    }
    cout << "total:"<< sum << '\n';
    //stack::push/top
    MyStack<int> second_stack;
    second_stack.push(10);
    second_stack.push(20);
    second_stack.push(30);
    second_stack.push(40);

    cout<<"Stack size: "<<second_stack.size()<<endl;
    second_stack.print();
    cout<<endl;
    cout << "MyStack.pop() is now: \n";
    second_stack.pop();
     cout<<"Stack pop()"<<endl;
    second_stack.pop();
    second_stack.pop();
    cout<<"Stack size: "<<second_stack.size()<<endl;
    second_stack.print();
    // stack::empty
    MyStack<string> third_stack;
    third_stack.push("hello");
    third_stack.pop();
    third_stack.pop();
    third_stack.print();

    cout<<"----------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"*************************MyQueue************************"<<endl;
    MyQueue<int> queue;
        queue.push_back(7);
        queue.push_back(8);
        queue.push_back(9);
        queue.push_back(10);
        queue.push_back(11);
        cout<<"Queue size: "<<queue.size()<<endl;
        queue.show();
        cout<<"Queue.pop()"<<endl;
        queue.pop();
        MyQueue<double> queue_1;
        queue_1.push_back(5);
        queue_1.push_back(10);
        queue_1.push_back(15);
        queue_1.push_back(20);
        queue_1.push_back(25);
        queue_1.push_back(30);
        queue_1.push_back(35);
        queue_1.show();

cout<<"----------------------------------------------------------"<<endl;
cout<<endl;
cout<<endl;
cout<<"----------------------------------------------------------"<<endl;}
//cout<<"*************************MyMap************************"<<endl;
//MyMap <string,int> map;
//map.put("Smith", 30);
//map.put("Anderson", 31);
//map.put("Lewis", 29);
//map.put("Cook", 29);
//map.put("Smith", 65);

//cout << "Entries in map: " << map.toString(30) << endl;
//cout << "The age for " << "Lewis is " <<
//map.get("Lewis") << endl;
//cout << "Is Smith in the map? " <<
//(map.containsKey("Smith") ? "true" : "false") << endl;
//cout << "Is age 33 in the map? " <<
//(map.containsValue(33) ? "true" : "false") << endl;

//map.remove("Smith");
//cout << "Entries in map: " << map.toString(25) << endl;

//map.clear();
//cout << "Entries in map: " << map.toString() << endl;
//   return 0;
//}
