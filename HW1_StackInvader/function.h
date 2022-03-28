//#ifndef _FUNCTION_H_
//#define _FUNCTION_H_
#include "13453.h"
#include <stdlib.h>
//#include "function.h"
#include <iostream>
using namespace std;

template < class T >
BaseStack<T>::BaseStack():_top(-1),_capacity(20){
    this->_stack = new T[this->_capacity];
}
// Destructor
template < class T >
BaseStack<T>::~BaseStack(){
    delete[] this->_stack;
}
// Check if the stack is empty
template < class T >
bool BaseStack<T>::empty(){
    //if top == -1, true ; else false
    return (this->_top == -1);
}

// Return the size of the stack
template < class T >
int BaseStack<T>::size(){
    return this->_top+1;
}

// Return the top element
template < class T >
T& BaseStack<T>::top(){
    return this->_stack[this->_top]; //top element
}

// Insert a new element at top
template < class T >
void BaseStack<T>::push(const T& item){
    if (this->_top == this->_capacity - 1) {    // if stack is full, update capacity
        this->_capacity *= 2;
        T *_stack = new T[this->_capacity]; // create new one
        // copy elements to the new one
        for (int i = 0 ; i < this->_capacity/2; i++) {
            _stack[i] = this->_stack[i];
        }
        delete[] this->_stack;  //new/delete[]:�s��t�m
        this->_stack = _stack; //update the original to new pointer
    }
    this->_top++;
    this->_stack[this->_top] = item;
}

// Delete one element from top
template < class T >
void BaseStack<T>::pop(){
    if (this->empty())   return; //no element to pop
    _top--; //update
}

template < class T >
BaseQueue<T>::BaseQueue():_front(0),_rear(0),_capacity(2){
    _queue = new T[this->_capacity];
}
// Destructor
template < class T >
BaseQueue<T>::~BaseQueue(){
    delete[] this->_queue;
}
// Check if the queue is empty
template < class T >
bool BaseQueue<T>::empty(){
    return (this->_front == this->_rear);
}

// Return the size of the queue
template < class T >
int BaseQueue<T>::size(){
    return (this->_rear-this->_front+this->_capacity)%this->_capacity;
}

// Return the front element
template < class T >
T& BaseQueue<T>::front(){
    return this->_queue[this->_front];
}

// Insert a new element at rear
template < class T >
void BaseQueue<T>::push(const T& item){
    if ((this->_rear+1)%this->_capacity == this->_front) {
        T *_queue = new T[2*this->_capacity]; //create new one to update capacity
        int j = this->_front;
        for (int i = 0; i < this->_capacity-1; i++) {
            _queue[i] = this->_queue[j];
            j = (j+1)%this->_capacity;
        }
        this->_front = 0;
        this->_rear = this->_capacity-1;
        delete [] this->_queue;
        this->_queue = _queue;
        this->_capacity *= 2;
    }
    this->_queue[this->_rear] = item;
    this->_rear = (this->_rear+1)%this->_capacity;
}

// Delete one element from front
template < class T >
void BaseQueue<T>::pop(){
    if (this->empty()) {
        return;
    }
    else this->_front = (this->_front + 1) % this->_capacity;
}

// [TODO]: Implement the following 6 functions which are the core of the game.
// Loading the stage
BaseStack<int>* baseStack;
void InitialzeStage(int W, int H){
    if(W > 0) baseStack = new BaseStack<int>[W];
    else ;
    if(H> 0){
        while(H--){
            for(int j=0;j<W;j++){
                int x;
                cin>>x;
                baseStack[j].push(x);
            }
        }
    }
    else ;
}

//Use Queue to store special bullets.
BaseQueue<int> baseQueue;
// Function for shooting a normal bullet
void ShootNormal(int col, int W){
    //kill enemy#2~4 get special bullets.
    //bullet#2:penetration bullet#3:pop 3 bullet#4:same
    while(!baseStack[col].empty()){
        if(baseStack[col].top() == 0){
            baseStack[col].pop();
        }
        else break;
    }
    if (!baseStack[col].empty()){
        if(baseStack[col].top() >= 2 && baseStack[col].top() <= 4 ){
            baseQueue.push(baseStack[col].top());
            baseStack[col].pop();
        }
        //enemy#5 generate new enemy
    else if(baseStack[col].top() == 5 ){
            baseStack[col].pop();
            int h[W],L,R,H = 1,p=3;
            //生成敵人左右界線
            if(col-2 >= 0) L = col-2;
            else L = 0;
            if(col+2 <= (W-1)) R = col+2;
            else R = W-1;
            //找生成敵人位置 H
            for(int i=L; i <= R; i++){
                if (i == col) h[i] = baseStack[i].size()+1;
                else h[i] = baseStack[i].size();
                H = max(h[i],H);
            }
            for(int i = L; i <= R; i++){
                p = 3;
                if(baseStack[i].size() != H){
                    while(baseStack[i].size() != H){
                        baseStack[i].push(0);
                    }
                }
                while( p > 0 ){
                    baseStack[i].push(1);
                    p--;
                }
            }

        }
        else {
            baseStack[col].pop();
        }
    }
}
const int SG = 2, P = 3, SB = 4;
// Function for shooting a special bullet
// bullet#2:penetration bullet#3:pop 3 bullet#4:same
void ShootSpecial(int col, int W){
    if(!baseQueue.empty()){
        if(baseQueue.front() == SG){
            int L=0,R=0;
            //generate attack range
            if((col-2) >= 0) L = col-2;
            else L = 0;
            if((col+2) <= (W-1)) R = col+2;
            else R = W-1;
            //shoot aimed collum
            ShootNormal(col,W);
            //shoot penetration
            for(int i = L; i<=R;i++){
                if ( i != col) ShootNormal(i,W);
            }
            baseQueue.pop();
        }
        else if(baseQueue.front() == P){

            for(int i= 0;i<3;i++){
                ShootNormal(col,W);
            }
            baseQueue.pop();
        }
        else if(baseQueue.front() == SB){

            int E;
            while(!baseStack[col].empty()){
                if(baseStack[col].top() == 0){
                    baseStack[col].pop();
                }
                else break;
            }
            if(!baseStack[col].empty()){
                E = baseStack[col].top();
            }
            while(!baseStack[col].empty()){
                if(baseStack[col].top() == E){
                    ShootNormal(col,W);
                }
                else if(baseStack[col].top() == 0){
                    baseStack[col].pop();
                }
                else{
                    break;
                }
            }
            baseQueue.pop();
        }
    }else{

    }
}

// Function that show the front row of the current stage
// Here, as the description on the OJ, you need to find the maximum level that contains any enemy.
// print the enemy types at that level for each column.
// print a underline "_" for a column that does not have a enemy at that level.
void FrontRow(int W){
    int H = 0,h[W]={0},cnt[W];
    for(int i=0; i < W; i++){
        while(!baseStack[i].empty()){
            if(baseStack[i].top() == 0){
                baseStack[i].pop();
            }
            else break;
        }
        if(!baseStack[i].empty()){
            h[i] = baseStack[i].size();
        }
        else h[i] = 0;
        H = max(h[i],H);
    }
    if(H>0){
        cout<<"FRONT_ROW, LEVEL:"<<H<<endl;
        for(int j= 0;j<W;j++){
            if((h[j])==H){
                if(baseStack[j].top() == 0) cout<<"_";
                else cout<<baseStack[j].top()<<""; //ASCII 48 = '0'
            }
            else cout<<"_";
            if((j+1) != W ) cout<<" ";
        }
        cout<<endl;
    }
    else{ }
}

// Print the end result of the stage.
void ShowResult(int W){
    cout<<"END_RESULT:"<<endl;
    int H = 0,h[W]={0},cnt[W]={0};
    /*for(int i=0; i < W; i++){
        h[i] = baseStack[i].size();
        for(int j=0;j<h[i];j++){
            if(baseStack[i].top() == 0){
                baseStack[i].pop();
                cnt[W]++;
            }
        }
        H = max(h[i]-cnt[i],H);
    }*/
    for(int i=0; i < W; i++){
        while(!baseStack[i].empty()){
            if(baseStack[i].top() == 0){
                baseStack[i].pop();
            }
            else break;
        }
        if(!baseStack[i].empty()){
            h[i] = baseStack[i].size();
        }
        else h[i] = 0;
        H = max(h[i],H);
    }
    char x[H][W] = {0};
    for(int i=H-1;i>=0;i--){
        for(int j= 0;j<W;j++){
            if((h[j])==i+1){
                if(baseStack[j].top() == 0) x[i][j] = '_';
                else if(baseStack[j].top() >0 && baseStack[j].top() < 6){
                    x[i][j] = baseStack[j].top()+48; //ASCII 48 = '0'
                }
                else x[i][j] = '_';
                baseStack[j].pop();
                h[j]--;
            }
            else x[i][j] = '_';
        }
    }
    for(int i=0;i<H;i++){
        for(int j=0; j<W; j++){
            cout<<x[i][j];
            if((j+1) != W) cout<<" ";
        }
        cout<<endl;
    }
}

// free the memory that allocated in the program.
void deleteStage(){
    //delete[] baseStack;
    delete[] baseStack;
    baseQueue.~BaseQueue();
}
//#endif // _FUNCTION_H_
