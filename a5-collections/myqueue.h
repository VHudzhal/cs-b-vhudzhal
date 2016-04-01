#ifndef MYQUEUE
#define MYQUEUE
template <class T>
class MyQueue{
    class Node{
    public:
        T value;
        Node* next;
    private:
        bool isEmpty = true;
    };
    Node* begin, *end;
    int count;
private:
    T *value;
    bool isEmpty = true;
public:
    // Default constructor
    MyQueue(){
        begin = nullptr;
        end = nullptr;
        count = 0;
        value = new T[100];
    }
    // The copy constructor
    MyQueue(const MyQueue& sourceList): begin(nullptr),end(nullptr)
    {
        Node *tmp = sourceList.begin;
        while(tmp != nullptr){

            this->push(tmp->value);
            tmp = tmp->next;
        }
    }

    T front(){
        return begin->value;
    }

    T back(){
        return end->value;
    }

    void push_back(T i){
        count++;
        value[count] = i;
        isEmpty = false;
    }
    int size(){
        return count;
    }
    void pop(){
        if (count == -1){
            isEmpty = true;
        }
        if (!isEmpty){
            cout << "Pop front function\n";
            for (int i = 0; i < count; i++){
                value[i] = value[i + 1];
            }
            count--;
            show();
            cout << endl;
        }
        else
            cout << "vector is empty!" << endl;
    }

    void show(){
        cout << "There are elements in the vector:\n";
        for (int i = 0; i <= count; i++){
            cout << value[i] << "    ";
        }
        cout << "\n\n";
    }


    void clear() {
        while(!isEmpty())
            pop();
    }

    //Default destructor
    ~MyQueue(){
        while(begin != nullptr){
            Node *temp = begin->next;
            delete begin;
            begin = temp;
            delete[] value;
        }
    }
};
#endif//MYQUEUE
