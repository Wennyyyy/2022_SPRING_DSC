#include <iostream>
#include <cstdlib>
using namespace std;

/**Linked list(�s����C)�O�@�ر`������Ƶ��c�A
��ϥ�node(�`�I)�ӰO���B��ܡB�x�s���(data)�A
�çQ�ΨC��node����pointer���V�U�@��node�A�Ǧ�
�N�h��node��s�_�ӡA�Φ�Linked list�A�åHNULL
�ӥN��Linked list�����I**/
//Node<T> have a friend class LinkedList<T>;
//�����OB�i�H�s�����OA��bprivate�ϰ쪺���O����

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
    if(this->first == 0){ //�٨S��node newnode�N�O�Ĥ@��
        this->first = newNode;
        return;
    }
    Node *currentNode = this->first;
    while( currentNode->next != 0){
        currentNode = currentNode->next;
    }
    currentNode->next = newNode; //�N�s�����blinkedlist������
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
        //linkedlist���S���n�R����node or �w�g�O�Ū��F
    }
    else if( currentNode == this->first){ //�n�R����node��n�b�}�Y
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
//�v�@�X�ݨæL�X
template <class T>
void LinkedList<T>::show(){
    if(this->first == 0){
        //�S���F��n�L
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
