#include <iostream>
#include <myvector.h>
#include <mystack.h>
#include <myqueue.h>
#include <mylist.h>
#include <mymap.h>
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
    secondTry.push_front(secondTry);
    i = secondTry.begin();
    secondTry.insert(++i, 2 ) ;
    show("После вставки 1 и 2 в начало". secondTry ) ;
    i = secondTry.end();
    secondTry.insert(--i, 100);
    show("После вставки 100 перед последним". secondTry ) ;
    i = secondTry.begin(); х = *i; secondTry.pop_front();
    cout << "Удалили из начала" << х << endsecondTry;
    i = secondTry.end();
    x = *--i; secondTry.pop_back();
    cout << "Удалили с конца" << x << end<<secondTry;
    show("Cписок после удаления", secondTry ) ;
    secondTry.remove(76);
    show("После удаления элементов со значением 76". L);-
    secondTry.sort();
    show("После сортировки", secondTry );
    secondTry.unique();
    show("После unique". L ) ;
    MyList<int> thirdTry (secondTry);
    secondTry.reverse();
    show("После reverse", secondTry);
//    cout<<"MyList<int> secondTry \n"<<endl;
//    cout << "-- push_front push_back test --" << endl;
//        secondTry.push_back("one");
//        secondTry.push_back("two");
//        secondTry.push_back("three");
//        secondTry.push_back("four");
//        secondTry.push_back("five");
//        secondTry.push_back("six");
//        secondTry.push_front("zero");
//        secondTry.push_front("neg-one");
//        secondTry.push_back("six");
//        print(secondTry);

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
cout<<"----------------------------------------------------------"<<endl;
cout<<"*************************map_1************************"<<endl;
MyMap <string,int> map_1 = {{ "Beta", 2 }, ///явная инициализация map
                            { "Alpha", 1 },
                            { "Gamma", 3 }};

  ///присвоение элементам map новых значений
   map_1.at("Beta") = 0;
   map_1.at("Alpha") = 233;
   map_1.at("Gamma") = -45;

  cout << "map_1 contains:\n";
  for(auto it = map_1.begin(); it != map_1.end(); ++it)
  {
      cout << it->first << " : " << it->second << endl;///вывод на экран
  }

   map_1.clear();

   ///новая инициализация map_1
   map_1 = {{ "Mike", 40 },
            { "Walle", 999 },
            { "Cloude", 17 }};



   auto itMap = map_1.begin();///создаем итератор на начало myМap
   cout << "\nmap_1 after clear contains:\n";

   ///вывод на экран map_1 и myMultimap
   for(itMap = map_1.begin(); itMap++;)
   {
       cout << "\t" <<itMap->first << " : " << itMap->second << "\t\t\t\t" << endl;
   }
   return 0;
}
