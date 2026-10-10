#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int partition(int arr[],int low,int high){
    int randomIndex = low + rand() % (high-low+1);
    swap(arr[randomIndex],arr[high]);
    int pivot = arr[high];
    int i = low - 1;

    for(int j=low;j<high;j++){
        if (arr[j] <= pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}

int randomselect(int arr[],int low,int high,int k){
    if(low == high)
        return arr[low];
    int pivotindex = partition(arr,low,high);
    int rank = pivotindex - low +1;
    if(k == rank)
        return arr[pivotindex];
    if(k<rank)
        return randomselect(arr,low,pivotindex-1,k);
    return randomselect(arr,pivotindex+1,high,k-rank);
}

int main(){
    srand(time(0));
    int n;
    cout << "Enter number of elements:";
    cin >> n;
    int arr[n];
    cout << "Enter elements:" << endl;
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    int k;
    cout << "Enter K:";
    cin >> k;

    if(k<1||k>n){
        cout << "Invaild value of k";
        return 0;
    }
    int result = randomselect(arr,0,n-1,k);
    cout << "The" << k << "th element is: " << result << endl;
    return 0;
}