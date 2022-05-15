#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <list>
using namespace std;
int N, flag = 1,i,j;
class Tourism{
    public:
        string Name;
        int Index;
        int PS;
        bool State;
};
Tourism tourism[101];
int Time[101][101];
double Tendency[101][101];
int start_pos;
int pre_idx[101];



class Graph_SP{             // SP serves as Shortest Path
private:
    int num_vertex;
    vector< list <pair<int,int> > > AdjList;
    vector<int> previous, distance;
    vector<bool> visited;
public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        AdjList.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);

    void InitializeSingleSource(int Start);     // 以Start作為起點
    void Relax(int X, int Y, int weight);       // edge方向：from X to Y

    void Dijkstra(int Start = 0);        // 需要Min-Priority Queue
};
void Graph_SP::Dijkstra(int Start){

    InitializeSingleSource(Start);

    visited.resize(num_vertex, false);   // initializa visited[] as {0,0,0,...,0}

    while (!minQueue.IsHeapEmpty()) {
        int u = minQueue.ExtractMin();
        for (std::list<std::pair<int, int>>::iterator itr = AdjList[u].begin();
             itr != AdjList[u].end(); itr++) {

            Relax(u, (*itr).first, (*itr).second);
            minQueue.DecreaseKey((*itr).first, distance[(*itr).first]);
        }
    }
    std::cout << "\nprint previous:\n";
    PrintDataArray(previous);
    std::cout << "\nprint distance:\n";
    PrintDataArray(distance);
}
void Graph_SP::InitializeSingleSource(int Start){

    distance.resize(num_vertex);
    previous.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
        distance[i] = Max_Distance;
        previous[i] = -1;
    }
    distance[Start] = 0;
}
void Graph_SP::Relax(int from, int to, int weight){

    if (distance[to] > distance[from] + weight) {
        distance[to] = distance[from] + weight;
        previous[to] = from;
    }
}
void Graph_SP::AddEdge(int from, int to, int weight){

    AdjList[from].push_back(make_pair(to,weight));
}


void SET_ORIGIN(string place_name){
    for(int i = 0; i < N; i++){
        if( place_name == tourism[i].Name && tourism[i].State == 1){
            start_pos = i;
            cout << place_name << " is the new origin" << endl;
            break;
        }
        if(i == N-1){
            cout << "Fail to reset the origin" << endl;
        }
    }
}
void MARK_STATE(string place_name, int status){
    string ss[2] = {"close","open"};
    for( i = 0; i < N; i++){
        if( place_name == tourism[i].Name ){
            if( tourism[i].State != status ){
                tourism[i].State = status;
            }else{
                cout << "Fail to " << ss[status] << " " << place_name << endl;
            }
        }
    }
}
void OPTIMAL_PATH(){

}
void SP(int num,int start){
    int dist[num];
    bool s[i]; //visited (short)
    for(int i = 0; i < num; i++){
        s[i] = false;
        dist[i] = Time[start][i];
    }
    s[start] = true;
    dist[start] = 0;
    for(int i = 0; i < num-1; i++){

    }
}
int main(){
    cin >> N;
    for( i = 0; i < N; i++){
        cin >> tourism[i].Index >> tourism[i].Name >> tourism[i].PS;
        tourism[i].State = 1;
    }
    for( i = 0; i < N; i++){
        for( j = 0; j < N; j++){
            cin >> Time[i][j];
        }
    }
    for( i = 0; i < N; i++){
        for( j = 0; j < N; j++){
            cin >> Tendency[i][j];
        }
    }
    while(flag){
        string place_name;
        string command;

        cin >> command;
        if(command == "SET_ORIGIN "){
            cin >> place_name;
            SET_ORIGIN(place_name);

        }else if(command == "MARK_STATE"){
            string status;
            cin >> status;
            if ( status == "CLOSE" ){
                while( cin >> place_name ){
                MARK_STATE(place_name, 0);
                }
            }else{
                while( cin >> place_name ){
                    MARK_STATE(place_name, 1);
                }
            }
        }else if(command == "OPTIMAL_PATH"){

        }else if(command == "LIMITED_PATH"){

        }else if(command == "END_OF_INSTRUCTION"){
            flag = 0;
            cout << "Stop receiving instructions" <<endl;
        }
    }
    return 0;
}
