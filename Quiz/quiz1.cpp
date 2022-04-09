#include<iostream>
#include <queue>
using namespace std;
int main(){
    int cases,col,ndata,x,spots,B,layers = 0;
    int maxlevel = 0,level,_size[spots];
    cin>>cases;
    while(cases > 0){
        cin>>spots>>B;
        queue<int> s[spots];
        int _size[spots]={0};
        for(int i=0;i<B;i++){
            cin>>col>>ndata;
            for(int j= 0;j<ndata;j++){
                cin>>x;
                s[col].push(x);
            }
        }
        //find max level
        for(int i = 0;i<spots;i++){
            _size[i] = s[i].size();
            if( maxlevel < _size[i] ) maxlevel = _size[i];
            else ;
        }
        cin>>layers;
        for(int i = 0;i<layers;i++){
            cin>>level;
            int cnt = level;
            if(level > maxlevel){
                cout<<"0"<<endl;
            }

            else{
                for(int j = 0;j < spots;j++){
                    while(level-- >0){
                        s[j].pop();
                    }
                    if(!s[j].empty()){
                        cout<<s[j].back();
                        s[j].pop();
                    }else cout<<"0";
                    if((j+1)!=spots) cout<<" ";
                    else cout<<endl;
                }
            }
        }
        cases--;
    }
    return 0;
}
