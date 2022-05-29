#include <iostream>
using namespace std;
template < class T >
void swap(int&a, int&b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}
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
int main(){
    int a[5] = {7, 6, 5,3,9};
    mySort(a, 0,4);
    for(int i = 0; i< 5; i++){
        cout << a[i] <<"  ";
    }
    cout << endl;
    return 0;
}
