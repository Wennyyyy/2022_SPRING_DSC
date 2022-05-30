#include <iostream>
#include "function.h"
using namespace std;
class Event{
    public:
        int time;
        long long int flow;
        friend bool operator< (Event& event1, Event& event2);
        friend bool operator> (Event& event1, Event& event2);
};
bool operator< (Event& event1, Event& event2){
    if( event1.time < event2.time ){
        return 1;
    }else{
        return 0;
    }
}
bool operator> (Event& event1, Event& event2){
    if( event1.time > event2.time ){
        return 1;
    }else{
        return 0;
    }
}

class Group{
    public:
        int A;
        long long int P;
        int L;
        friend bool operator< (Group& group1, Group& group2);
        friend bool operator> (Group& group1, Group& group2);
};
bool operator< (Group& group1, Group& group2){
    if( group1.A < group2.A){
        return 1;
    }else{
        return 0;
    }
}
bool operator> (Group& group1, Group& group2){
    if( group1.A > group2.A){
        return 1;
    }else{
        return 0;
    }
}
//---------------<NOTE>-------------------
//1. When group i leaves at time Li,
//   group i is no longer considered to be in the food court at that time Li.
//2. If y groups arrive at the same time and x groups have already arrived before that,
//   they will be the x+1th ~ x+yth earliest groups. The order inside the y groups is not important.
//   Your program should return same value for the arrival times of the x+1th ~ x+yth earliest group,
//   that is, the time when the y groups arrive at.
//----------------------------------------

// TODO: Implement the sorting algorithm
template < class T >
void mySort(T arr[], int l, int r){
    if( l < r ){
        T pivot = arr[l];
        int left = l;
        int right = r + 1;
        while(1){
            while( left < r && arr[++left] < pivot);
            while( right > 0 && arr[--right] > pivot);

            if( left >= right ){
                break;
            }
            swap(arr[left], arr[right]);

        }
        swap(arr[l], arr[right]);

        mySort(arr , l, right - 1);
        mySort(arr, right + 1, r);
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
    Group group[n];
    Event event[2*n+1];
    string S[n]; int j = 0;
    for(int i = 0; i < n; i++){
        cin >> group[i].P >> group[i].A >> group[i].L >> S[i];
        event[j].time = group[i].L;
        event[j].flow = -group[i].P;
        j++;
        event[j].time = group[i].A;
        event[j].flow = group[i].P;
        j++;
    }
#ifdef _WYNNE_DEBUG_
 for(int i = 0; i < n; i++){
    cout << "| People | arriveT| leaveT |     name     |" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "|" << setw(7) << group[i].P
         << "|" << setw(7) << group[i].A
         << "|" << setw(7) << group[i].L
         << "|" << setw(14) << S[i]
         << endl;
    }
#endif  // _WYNNE_DEBUG_
    //===================================================
    // Sorting data
    //===================================================
    mySort(group, 0 , n-1);
    mySort(S, 0 , n-1);
    mySort(event, 0, 2*n-1);




    //===================================================
    // Output answer
    //===================================================
    // four types of queries


    /*cout << "---------------------------------------\n";
        for(int i=0; i < n; i++){
            cout << " People: " << group[i].P
                 << " Arrive time: " <<group[i].A
                 << " Leave time:: " << group[i].L <<endl;
        }
    cout << "----------------------------------------\n";*/

    int m;
    cin >> m;
    while(m--){
        string operation;
        cin >> operation;
        if(operation == "TIME_ARRIVE"){
            // print an integer that represents the time the Kth earliest group arrives at.
            int K;
            cin >> K;
            cout << group[K-1].A;
        }else if(operation == "TRAFFIC_AT"){
            // print the number of people in the food court at the time T
            long long int sum = 0;
            int T;
            cin >> T;
            for(int i = 0; i < n; i++){
                if(group[i].A <= T ){
                    if( T < group[i].L ){
                        sum += group[i].P;
                    }
                }
            }
            cout << sum;
        }else if(operation == "MAX_TRAFFIC"){
            //print the time when there are the most people in the food court
            //and the number of the people in the food court at that time. Separate them with a whitespace.
            //multi --> provide the solution with earliest time of having maximum traffic.
            int temptime, maxtime;
            long long int tempflow = 0, maxflow = 0;
            for(int i = 0; i < 2*n; i++){
                temptime = event[i].time;
                tempflow += event[i].flow;
                if( tempflow > maxflow ){
                    maxflow = tempflow;
                    maxtime = temptime;
                }
            }

            /*cout << "-----------------------------------\n";
            for(int i=0; i<2*n; i++){
                cout << "time: " << event[i].time
                     << " flow: " << event[i].flow <<endl;
            }
            cout << "-------------------------------------\n";*/

            cout << maxtime << " " << maxflow;
        }else if(operation == "STORE_LIST"){
            //print the names of all the stores that appeared in the data.
            //Print them in lexicographical order and separate them with a space.
            //based on the ASCII code.
            //The smaller the code of a character is, the higher priority the character has to be sorted in the front.
            for(int i = 0; i < n; i++){
                cout << S[i];
                if( i+1 != n ) cout << " ";
            }
        }else{
            cout<<"ERROR";
        }
        cout << endl;
    }
}
