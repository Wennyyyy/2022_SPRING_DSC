#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include "function.h"
using namespace std;
typedef unsigned int u32; //typedef: rename

// [TODO]: Implement all member functions in Node.
/*
    private:
        std::string id;
        u32 time;
*/
// Constructor
Node::Node(string id, u32 time){
    this-> id = id;
    this-> time =time;
}
// return time of the node
u32 Node::get_time(){
    return this->time;
}
// return id of the node
string Node::get_id(){
    return this->id;
}
// set time of the node
void Node::set_time(u32 time){
    this->time = time;
}

/*
Output streams use the insertion (<<) operator for standard types.
overload the << operator for Node.
*/
ostream& operator<<(ostream& os, Node& d){
    os << d.time;
    return os;
}

// [TODO]: Implement Operator Overloading for Node.
// Check if the time of node1 is equal to the time of node2.
bool operator== (Node& node1, Node& node2){
    if( node1.get_time() == node2.get_time() ){
        return 1;
    }else{
        return 0;
    }
}
// Check if the time of node1 is equal to the parameter time.
bool operator== (Node& node1, u32 time){
    if( node1.get_time() == time ){
        return 1;
    }else{
        return 0;
    }
}
// Check if the time of node1 is not equal to the time of node2.
bool operator!= (Node& node1, Node& node2){
    if( node1.get_time() != node2.get_time() ){
        return 1;
    }else{
        return 0;
    }
}
// Check if the time of node1 is not equal to the parameter time.
bool operator!= (Node& node1, u32 time){
    if( node1.get_time() != time ){
        return 1;
    }else{
        return 0;
    }
}

/*
Check if the time of node1 is less than the time of node2.
If the time of node1 is equal to node2, check if the id of node1 is less than the id of node2.
*/
bool operator< (Node& node1, Node& node2){
    if( node1.get_time() < node2.get_time() ){
        return 1;
    }else if( node1.get_time() == node2.get_time() ){
        if( node1.get_id() < node2.get_id() ){
            return 1;
        }else{
            return 0;
        }
    }else {
        return 0;
    }
}
// Check if the time of node1 is less than the parameter time.
bool operator< (Node& node1, u32 time){
    if( node1.get_time() < time ){
        return 1;
    }else{
        return 0;
    }
}
/*
Check if the time of node1 is greater than node2.
If the time of node1 is equal to node2, check if the id of node1 is greater than the id of node2.
*/
bool operator> (Node& node1, Node& node2){
    if( node1.get_time() > node2.get_time() ){
        return 1;
    }else if( node1.get_time() == node2.get_time() ){
        if( node1.get_id() > node2.get_id() ){
            return 1;
        }else{
            return 0;
        }
    }else {
        return 0;
    }
}
// Check if the time of node1 is greater than the parameter time.
bool operator> (Node& node1, u32 time){
    if( node1.get_time() > time ){
        return 1;
    }else{
        return 0;
    }
}

// Check if the time of node1 is not greater than node2.
bool operator<= (Node& node1, Node& node2){
    if( node1.get_time() <= node2.get_time() ){
        return 1;
    }else{
        return 0;
    }
}
// Check if the time of node1 is not greater than the parameter time.
bool operator<= (Node& node1, u32 time){
    if( node1.get_time() <= time ){
        return 1;
    }else{
        return 0;
    }
}

// Check if the time of node1 is not less than node2.
bool operator>= (Node& node1, Node& node2){
    if( node1.get_time() >= node2.get_time() ){
        return 1;
    }else{
        return 0;
    }
}
// Check if the time of node1 is not less than the parameter time.
bool operator>= (Node& node1, u32 time){
    if( node1.get_time() <= time ){
        return 1;
    }else{
        return 0;
    }
}

// Add the parameter time to the time of node.
void operator+= (Node& node1,u32 time){
    node1.set_time( node1.get_time() + time );
}

// [TODO]: Implement all member functions in BinaryHeap.

// get index of parent of node at index idx.
template < class T >
u32 BinaryHeap<T>::parent_idx(u32 idx){
    if( idx == 1){
        return 0;
    }else{
        return idx/2;
    }
}
// get index of left child of node at index idx.
template < class T >
u32 BinaryHeap<T>::left_idx(u32 idx){
    return 2*idx;
}
// get index of right child of node at index idx.
template < class T >
u32 BinaryHeap<T>::right_idx(u32 idx){
    return 2*idx+1;
}
// heapify from idx to root.
template < class T >
void BinaryHeap<T>::heapify_up(int idx){
    u32 parent_idx = this->parent_idx(idx);
    while(parent_idx > 0){
        u32 left_idx = this->left_idx(parent_idx);
        u32 right_idx = this->right_idx(parent_idx);
        if( right_idx > this->size() ){
            if( left_idx > this->size() ){

            }else{
                if( heap[left_idx] < heap[parent_idx] ){
                    T temp = heap[left_idx];
                    heap[left_idx] = heap[parent_idx];
                    heap[parent_idx] = temp;
                }
            }
        }else if( heap[left_idx] < heap[parent_idx] || heap[right_idx] < heap[parent_idx] ){
            if(heap[left_idx] < heap[right_idx]){
                T temp = heap[left_idx];
                heap[left_idx] = heap[parent_idx];
                heap[parent_idx] = temp;
            } else {
                T temp = heap[right_idx];
                heap[right_idx] = heap[parent_idx];
                heap[parent_idx] = temp;
            }
        }
        parent_idx = this->parent_idx(parent_idx);
    }
}
// heapify from idx to leaf.
template < class T >
void BinaryHeap<T>::heapify_down(int idx){
    u32 left_idx = this->left_idx(idx);
    u32 right_idx = this->right_idx(idx);
    while(this->size() >= left_idx){
        if(this->size() >= right_idx){
            if( heap[idx] > heap[left_idx] || heap[idx] > heap[right_idx] ){
                if(heap[left_idx] < heap[right_idx]){
                    T temp = heap[left_idx];
                    heap[left_idx] = heap[idx];
                    heap[idx] = temp;

                    idx = left_idx;
                } else {
                    T temp = heap[right_idx];
                    heap[right_idx] = heap[idx];
                    heap[idx] = temp;

                    idx = right_idx;
                }
            } else {
                break;
            }
        } else {
            if(heap[left_idx] < heap[idx]){
                T temp = heap[left_idx];
                heap[left_idx] = heap[idx];
                heap[idx] = temp;

                idx = left_idx;
            } else {
                break;
            }
        }
        left_idx = this->left_idx(idx);
        right_idx = this->right_idx(idx);
    }
}

// get number of element in heap.
template < class T >
u32 BinaryHeap<T>::size(){
    return this->heap.size() - 1;
}
// insert element to heap.
template < class T >
void BinaryHeap<T>::insert(T element){
    heap.push_back(element);
    this->heapify_up( this->size() );
}
// remove minimum element from heap.
template < class T >
void BinaryHeap<T>::del_min(){
    if( this->size() > 0){
        heap[1] = heap[this->size()];
        heap.pop_back();
        heapify_down(1);
    }
}
// get minimum element from heap.
template < class T >
T BinaryHeap<T>::get_min(){

    if( this->size() > 1 ){
        return heap[1];
    }
}

/*template < class T >
BinaryHeap<Node>::Manager<T>{
}*/

// [TODO]: Implement all member functions in Manager.
// A heap used to maintain the status of each TA
/*
    private:
        // A heap used to maintain the status of each TA
        BinaryHeap<T> taQue;
        // End time of office hour.
        u32 endTime;
        // Check if a task that takes $costTime time units can be completed before time $deadLine
        int finish_in_time(u32 costTime,u32 deadLine);
*/


template < class T >
Manager<T>::Manager(){
    endTime = 4294967295;
    T dummy = T("",0);
    this->taQue.heap.push_back(dummy);
}
// Check if a task that takes $costTime time units can be completed before time $deadLine
template < class T >
int Manager<T>::finish_in_time(u32 costTime,u32 deadLine){
    if(taQue.size() > 0){
        if( taQue.get_min().get_time() <= deadLine - costTime ){
            return 1;
        }else{
            return 0;
        }
    } else {
        return -1;
    }
}
// To handle the SET_ENDTIME instruction
// time complexity: O(n)
template < class T >
void Manager<T>::cmd_set_endTime(u32 endTime){
    if(this->taQue.size() > 1){
        if( taQue.heap[taQue.size()] > endTime ){
            cout<<"SET_ENDTIME FAIL"<<endl;
            return;
        }
    }
    this->endTime = endTime;
    cout<<"SET_ENDTIME SUCCESS"<<endl;
}
// To handle the ADD_TASK instruction
// time complexity: O(log n)
template < class T >
void Manager<T>::cmd_add_task(string taskName, u32 costTime){
    if( finish_in_time(costTime, this->endTime ) == 1 ){
        T mintimeTA = taQue.get_min();
        mintimeTA.set_time(mintimeTA.get_time() + costTime);
        taQue.del_min();
        taQue.insert(mintimeTA);
        cout<<"ADD_TASK "<<taskName<<": "<<mintimeTA.get_id()<<" AT "<<mintimeTA.get_time()<<endl;
    }else{
        cout<<"ADD_TASK "<<taskName<<": FAIL"<<endl;
    }
}
// To handle the ADD_TA instruction
// time complexity: O(log n)
template < class T >
void Manager<T>::cmd_add_ta(std::string id, u32 begin){
    if( begin < this->endTime ){
        T ta = T(id,begin);
        taQue.insert(ta);
        cout<<"ADD_TA SUCCESS"<<endl;
    }else{
        cout<<"ADD_TA FAIL"<<endl;
    }
}
// To handle the CHECK_INTIME instruction
   // time complexity: O(log n)
template < class T >
void Manager<T>::cmd_check_schedule(u32 costTime,u32 deadLine){
    int x = finish_in_time( costTime, deadLine );
    if(x == -1){
        cout<<"CHECK_SCHEDULE: NO TA WARNING!"<<endl;
    }else if(x == 0){
        cout<<"CHECK_SCHEDULE: OVERTIME WARNING!"<<endl;
    }else{
        if( deadLine <= this->endTime){
            cout<<"CHECK_SCHEDULE: CAN FINISH!"<<endl;
        }else{
            cout<<"CHECK_SCHEDULE: OVERTIME WARNING!"<<endl;
        }
    }
}
// To print out the final output required by the program
template < class T >
void Manager<T>::result(){
    u32 num = taQue.size();
    if( num > 0 ){
        T TA = taQue.get_min();
        u32  FINISH_TIME = TA.get_time();
        string TA_NAME = TA.get_id();
        taQue.del_min();
        while(taQue.size() > 0) {
            T new_TA = taQue.get_min();
            if(new_TA.get_time() == FINISH_TIME){
                if(new_TA.get_id() < TA_NAME){
                    TA_NAME = new_TA.get_id();
                }
            } else {
                break;
            }
            taQue.del_min();
        }
        cout<<"NUMBER_TA: "<<num<<endl;
        cout<<"EARLIEST FINIAH TA: "<<TA_NAME<<" AT "<<FINISH_TIME<<endl;
    }else if(num == 0){
        cout<<"NUMBER_TA: "<<num<<endl;
    }
}

template class Manager<Node>;
