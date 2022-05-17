#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include <cstdlib>
#include <stack>
#include <string>

int N,R;
int index[101][101];
double graph[101][101];
int prev_node[101][101];
int next_node[101][101];
bool state[101][101];
double optimal_flow[101][101];
using namespace std;

void path(int N){
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
        {
            d[i][j] = w[i][j];
            next[i][j] = j;
        }

    for (int i=0; i<N; i++){
        d[i][i] = 0;
    }

    for (int k=0; k<9; k++){
        for (int i=0; i<9; i++){
            for (int j=0; j<9; j++){
                if (d[i][k] + d[k][j] < d[i][j]){
                    d[i][j] = d[i][k] + d[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}
void print(int node, int t) {
    cout << node;
    if (node != t){
        find_path(next[node][t], t);
        cout << " -> "
    }
}
stack<int> optimal_path_time(int destination, int prev_node[][101]){
    stack<int> final_path;
    int times = N;
    while(times > 1){
        if(prev_node[times][destination] == prev_node[times-1][destination]){
            times--;
        }else{
            break;
        }
    }
    while(times > 0){
        int temp = index[destination][R];
        final_path.push(temp);
        destination = prev_node[times][destination];
        times--;
    }
    final_path.push(index[0][R]);
    return final_path;
}

int main(){

    cin >> N >> R;
    stack<int> ans;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            double temp;
            cin >> temp;
            index[i][j] = j;
            if( temp == 0){
                graph[i][j] == 0;
            }else{
                graph[i][j] = abs ( round(log2(temp)*100) / 100.0 );
            }
        }
    }
    //build optimal chart
    for(int i = 0; i < N; i++){
        if(graph[1][i] != 0){
            prev_node[1][i] = R;
            optimal_flow[1][i] = graph[R][i];
            next_node[1][i] = i;
        }else{
            prev_node[1][i] = -1;
            optimal_flow[1][i] = 0;
            next_node[1][i] = i;
        }
    }
    for(int i = 2; i <= N; i++){
        for(int j = 0;j < N; j++){
            if( !graph[i][j] ){
                prev_node[i][j] = prev_node[i-1][j];
                optimal_flow[i][j] = optimal_flow[i-1][j];
                next_node[i][j] = next_node[i-1][j];
                if(j != R){
                    for(int k = 0; k < N; k++){
                        if( k != j && !optimal_flow[i-1][k] ){
                            double new_flow = optimal_flow[i-1][k] + graph[k][j];
                            if(new_flow > optimal_flow[i][j]){
                                prev_node[i][j] = k;
                                optimal_flow[i][j] = new_flow;
                            }else if(new_flow == optimal_flow[i-1][k] && next_node[i-1][k] < next_node[i][j]){
                                prev_node[i][j] = k;
                                next_node[i][j] = next_node[i-1][k];
                            }
                        }
                    }
                }

            }else{
                prev_node[i][j] = -1;
                optimal_flow[i][j] = 0;
                next_node[i][j] = j;
            }
        }
    }

            cout<<"---------------------------"<<endl;
    for(int i = 0; i < N; i++){
        for(int j = 0;j < N; j++){
            cout<< optimal_flow[i][j] <<" ";
        }
        cout << endl;
    }

            cout<<"---------------------------"<<endl;
    cout<< "The origin is: " << R << endl;
    //process output
    for(int i = 1; i < N; i++){
        ans = optimal_path_time(i, prev_node);
        if(!ans.empty()){
            int first;
            first  = ans.top();
            int flag;
            ans.pop();
            while(!ans.empty()){
                int then;
                then = ans.top();
                if( first == then ) {
                    break;
                }else{
                    if(flag){
                        cout << "0 -> " << first;
                        flag = 0;
                    }
                    cout <<" -> " <<next_node;
                    ans.pop();
                }
            }
            cout << endl;
        }
    }



    return  0;
}
