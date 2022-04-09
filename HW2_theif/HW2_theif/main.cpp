#include <iostream>
#include <cstdlib>
using namespace std;

/**Linked list(連結串列)是一種常見的資料結構，
其使用node(節點)來記錄、表示、儲存資料(data)，
並利用每個node中的pointer指向下一個node，藉此
將多個node串連起來，形成Linked list，並以NULL
來代表Linked list的終點**/
//Node<T> have a friend class LinkedList<T>;
//使類別B可以存取類別A放在private區域的類別成員

/*Node
private:
    T x;
    T y;
    T fence;
    Node<T>* next;
*/
/*Node*/
// constructor
template < class T >
Node<T>::Node(T x,T y,T fence){
    this->x = x;
    this->y = y;
    this->fence = fence;
}

/*Node*/
// member function
// this is for you to compare the order of nodes
template < class T >
T Node<T>::compare(T x,T y){
}

/*LinkedList*/
/*
 private:
    Node<T>* first;
    int length;
*/
// constructor
template <class T>
LinkedList<T>::LinkedList():first(0),length(0){
}

/*LinkedList*/
// member function
template <class T>
void LinkedList<T>::insert(T x, T y,T fence){
    Node *newNode = new Node(x,y,fence);
    if(this->first == 0){ //還沒有node newnode就是第一個
        this->first = newNode;
        return;
    }
    Node *currentNode = this->first;
    while( currentNode->next != 0){
        currentNode = currentNode->next;
    }
    currentNode->next = newNode; //將新的接在linkedlist的尾巴
}

/*LinkedList*/
template <class T>
void LinkedList<T>::deletion(T x, T y){
    Node *currentNode = this->first,
         *previousNode = 0;
    while( currentNode != 0 && currentNode->x !=x && currentNode->y !=y){
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    if( currentNode == 0){
        //linkedlist中沒有要刪除的node or 已經是空的了
    }
    else if( currentNode == this->first){ //要刪除的node剛好在開頭
        this->first = currentNode->next;
        delete currentNode;
        currentNode = 0;
    }else{
        previousNode->next = currentNode->next;
        delete currentNode;
        currentNode = 0;
    }
}

/*LinkedList*/
//逐一訪問並印出
template <class T>
void LinkedList<T>::show(){
    if(this->first == 0){
        //沒有東西要印
        return;
    }
    Node *currentNode = first;
    while(currentNode != 0){
        cout<<"("<<currentNode->x<<","<<currentNode->y<<")"<<endl;
        currentNode = currentNode->next;
    }
}


Node<int> *node;
/**  solving function  **/
void plant(long long x,long long y,int withFence){
    node = Node(x,y,withFence);
}

void thief(long long x,long long y){
}

void superThief(long long x,long long y){
}

void display(){
}
