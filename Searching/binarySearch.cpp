#include <iostream>
using namespace std;


int binarySearch(int arr[], int start, int end, int num){
    int mid = (start + end)/2;

    //if element not present in the array
    if(start > end)
     return -1;

    if(num == arr[mid])
     return mid;
     
    if(num > arr[mid])
     return binarySearch(arr,mid+1,end,num);
    if(num < arr[mid])
     return binarySearch(arr, start, mid -1, num);
    return 0;

}

int main(){

    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << binarySearch(arr, 0, n, 11);
}