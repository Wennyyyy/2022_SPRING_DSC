#include <iostream>
#include "function.h"
using namespace std;
/*
6 2
7 6 8 9 10 2
3 6
1 4
*/

void LinkedList::reverse(int left, int right) {
    Node *posleft;
    Node *posright;
    Node *current = head;
    Node *firstprevious = NULL;
    Node *secondprevious = NULL;
    Node *temp = NULL;
    if(left == 1){
        firstprevious = NULL;
        posleft = current;
    }else{
        for(int i = 0; i < left-1; i++){
            current = current->next;
        }
        firstprevious = current;
        posleft = current->next;
    }

    current  = this->head;
    for(int i = 0; i < right-1; i++){
        current = current->next;
    }
    secondprevious = current;
    posright = current->next;
    current  = posleft;

    temp = firstprevious->next;
    secondprevious->next = firstprevious->next;
    secondprevious->next = temp;

    temp = posleft->next;
    posright->next = posleft->next;
    posright->next = temp;

    /*left++;
    right--;
    if( (right - left) >= 1){
        reverse(left,right);
    }*/

}
