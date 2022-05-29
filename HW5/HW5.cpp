#include <iostream>
#include "function.h"
using namespace std;
//---------------<NOTE>-------------------
//1. When group i leaves at time Li,
//   group i is no longer considered to be in the food court at that time Li.
//2. If y groups arrive at the same time and x groups have already arrived before that,
//   they will be the x+1th ~ x+yth earliest groups. The order inside the y groups is not important.
//   Your program should return same value for the arrival times of the x+1th ~ x+yth earliest group,
//   that is, the time when the y groups arrive at.
//----------------------------------------

/*void swap(int&a, int&b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}*/
// TODO: Implement the sorting algorithm
template < class T >
void mySort(T arr[], int l, int r){
    int temp;
    if( l < r ){
        int pivot = arr[l];
        int left = l;
        int right = r + 1;
        while(1){
            while( left < r && arr[++left] < pivot);
            while( right > 0 && arr[--right] > pivot);

            if( left >= right ){
                break;
            }
            swap(arr[left], arr[r]);
            mySort(arr , l, right - 1);
            mySort(arr, right + 1, r);
        }
    }
}


// TODO: Implement the function to read input, process data, and output answers.
void solve(){
    int n;
    cin >> n;
    //===================================================
    // Read input
    //===================================================
    //P people, A arrive time, L leave time, S store name
    //---------------------------------------------------
    int P[n], A[n], L[n];
    string S[n];
    for(int i = 0; i < n; i++){
        cin >> P[i] >> A[i] >> L[i] >> S[i];
    }
#ifdef _WYNNE_DEBUG_
 for(int i = 0; i < n; i++){
    cout << "| People | arriveT| leaveT |     name     |" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "|" << setw(7) << P[i]
         << "|" << setw(7) << A[i]
         << "|" << setw(7) << L[i]
         << "|" << setw(14) << N[i]
         << endl;
    }
#endif  // _WYNNE_DEBUG_
    //===================================================
    // Sorting data
    //===================================================
    // four types of queries
    mySort(A, 0 , n);
    mySort(L, 0 , n);
    //mySort(S, 0 , n);


    //===================================================
    // Output answer
    //===================================================
    // four types of queries
    int m;
    while(m--){
        string operation;
        cin >> operation;
        if(operation == "TIME_ARRIVE"){
            // print an integer that represents the time the Kth earliest group arrives at.
            int K;
            cin >> K;
            cout << A[K];
        }else if(operation == "TRAFFIC_AT"){
            // print the number of people in the food court at the time T
            int T,sum;
            cin >> T;
            for(int i = 0; i < n; i++){
                if(A[i] < T && L[i] > T){
                    sum += P[i];
                }
            }
            cout << sum;
        }else if(operation == "MAX_TRAFFIC"){
            //print the time when there are the most people in the food court
            //and the number of the people in the food court at that time. Separate them with a whitespace.
            //multi --> provide the solution with earliest time of having maximum traffic.

        }else if(operation == "STORE_LIST"){
            //print the names of all the stores that appeared in the data.
            //Print them in lexicographical order and separate them with a space.
            //based on the ASCII code.
            //The smaller the code of a character is, the higher priority the character has to be sorted in the front.

        }else{
            cout<<"ERROR";
        }
        cout << endl;
    }
}
