#include <iostream>
#include <cstdlib>
#include "function.h"
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
Node<T>::Node(T x,T y,T fence):x(x),y(y),fence(fence),next(NULL){
}

/*Node*/
// member function
// this is for you to compare the order of nodes
template < class T >
T Node<T>::compare(T x,T y){
    if( y < this->y ){//insert from front : -1
        return -1;
    }else if( y == this->y ){
        if( x < this-> x){
            return -1;
        }else if( x == this->x){
            return 0;
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

/*LinkedList*/
/*
 private:
    Node<T>* first;
    int length;
*/
// constructor
template <class T>
LinkedList<T>::LinkedList():first(NULL),length(0){
}

/*LinkedList*/
// member function
template <class T>
void LinkedList<T>::insert(T x, T y,T fence){
    Node<T> *newNode,
            *currentNode = this->first,
            *previousNode = NULL;
    if(this->first == NULL){ //還沒有node newnode就是第一個
        newNode = new Node<T>(x,y,fence);
        newNode->next = this->first;
        this->first = newNode;
        this->length++;
    }else{ //ensure whether the posisition is taken
        //search for(x,y)
        while( currentNode != NULL &&
               !(currentNode->x == x && currentNode->y == y) &&
               !(currentNode->y > y) &&
               !( y == currentNode->y && x < currentNode->x )     ){
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        if( !(currentNode == NULL) && currentNode->x == x && currentNode->y == y ){ //linkedlist有這個node
            if(fence == 1){
                currentNode->fence = 1;
            }
        }else{
            newNode = new Node<T>(x,y,fence);
            if(currentNode == this->first){
                newNode->next = this->first;
                this->first = newNode;
            }else{
                previousNode->next = newNode;
                newNode->next = currentNode;
            }
            this->length++;
        }
    }
}

/*LinkedList*/
template <class T>
void LinkedList<T>::deletion(T x, T y){
    Node<T> *currentNode = this->first,
            *previousNode = NULL;
    while( currentNode != NULL && !(currentNode->x ==x && currentNode->y ==y) ){
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    if( currentNode == NULL){
        //linkedlist中沒有要刪除的node or 已經是空的了
    }
    else if( currentNode == this->first){ //要刪除的node剛好在開頭
        if( !currentNode->fence ){
            this->first = currentNode->next;
            delete currentNode;
        }
    }else{
        if( !currentNode->fence ){
            previousNode->next = currentNode->next;
            delete currentNode;
        }
    }
}

/*LinkedList*/
//逐一訪問並印出
template <class T>
void LinkedList<T>::show(){
    cout<<"Display"<<endl;
    Node<T> *currentNode = this->first;
    while(currentNode != NULL){
        cout<<"("<<currentNode->x<<","<<currentNode->y<<")"<<endl;
        currentNode = currentNode->next;
    }
}


LinkedList<long long> linkedList;
/**  solving function  **/
void plant(long long x,long long y,int withFence){
    linkedList.insert(x,y,withFence);
}

void thief(long long x,long long y){
    linkedList.deletion(x-1,y);
    linkedList.deletion(x,y);
    linkedList.deletion(x+1,y);
    linkedList.deletion(x,y-1);
    linkedList.deletion(x,y+1);
}

void superThief(long long x,long long y){
    thief(x,y);
    linkedList.deletion(x+1,y+1);
    linkedList.deletion(x+1,y-1);
    linkedList.deletion(x-1,y-1);
    linkedList.deletion(x-1,y+1);
}

void display(){
    linkedList.show();
}
