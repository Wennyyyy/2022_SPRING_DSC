#include <iostream>
#include <queue>
int n,m,k,roomnum;
using namespace std;
int check(int a[],int num){
    int cnt = 0;
    for(int i = 0;i < n;i++){
        if(a[i] == i){
            cnt++;
        }

        if(cnt == num){
            return 1;
            break;
        }
    }
    return 0;
}
int main(){
    priority_queue <int> pq;
    string command;
    cin >> n;
    int reserve[n] = {0};
    //n rooms
    for(int i = 0;i < n;i++){
        reserve[i] = i;
        pq.push(i);
    }
    cin >>m;
    for(int j=0;j<m;j++){
        cin >> command;
        if(command == "RESERVE"){
            cin >> k;
            if( k > pq.size() ){
                cout<< "RESERVE: no vacant rooms"<<endl;
            }else if(check(reserve,k) == 0){
                cout<< "RESERVE: no vacant rooms"<<endl;
            }else {
                cout<<"RESERVE: reserve room ";
                for(int p = 0;p < k;p++){
                    int num = pq.top();
                    cout<<num;
                    reserve[num] = -1;
                    if( p+1 != k){
                        cout<<",";
                    }
                    pq.pop();
                }
                cout<<endl;
            }
        }
        else if(command == "UNRESERVE"){
            cin >> roomnum;
            int pqsize = pq.size();
                if( reserve[roomnum] == -1 ){
                    reserve[roomnum] = roomnum;
                    pq.push(roomnum);
                    cout<<"UNRESERVE: unreserved room "<<roomnum<<endl;
                }else{
                    cout<<"UNRESERVE: "<<roomnum<<" has not been reserved"<<endl;
                }
        }

        /*cout<<"---------------"<<endl;
        for(int i = 0;i < n;i++){
            cout<<"room "<<i<<" :"<<reserve[i]<<endl;
        }
        cout<<"---------------"<<endl;*/

    }
    return 0;
}
