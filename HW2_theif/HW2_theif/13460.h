#include <iostream>
#include <cstdlib>
using namespace std;

template <class T> class LinkedList;
template <class T> class Node;

template <class T>
class Node
{
public:
    friend class LinkedList<T>;
    //使類別A可以存取類別B放在private區域的類別成員

    // constructor
    Node(T x,T y,T fence);

    // member function
    // this is for you to compare the order of nodes
    T compare(T x,T y);

private:
    T x;
    T y;
    T fence;
    Node<T>* next;

};


template <class T>
class LinkedList
    {
        public:
            /// constructor
            LinkedList();

            /// member function
            void insert(T x, T y,T fence);


            void deletion(T x, T y);


            void show();

        private:
            Node<T>* first;
            int length;
    };

/**  solving function  **/
void plant(long long x,long long y,int withFence);

void thief(long long x,long long y);

void superThief(long long x,long long y);

void display();
