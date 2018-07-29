#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;
void printKMax(int arr[], int n, int k)
{
    deque<int> dQ;
    int i = 0;
    // Build the first subarray.
    for (; i<k; i++) {
        dQ.push_back(arr[i]);
        }
    // max_out will be the max element of each subarray.
    int max_out = *max_element(dQ.begin(), dQ.end());
    for (; i<n; i++) {
        cout << max_out << " ";
        // Move the subarray. Considering whether the first element
        // is max_out, I saved this element everytime. 
        int tmp = dQ.front();
        dQ.pop_front();
        dQ.push_back(arr[i]);
        // max_element is an expensive function, the program
        // tries its best to avoid using it.
        if (dQ.back()>max_out) {
            max_out = dQ.back();
        } else if (tmp==max_out) {
            max_out = *max_element(dQ.begin(), dQ.end());
            }
    }
    // This program didn't output the last max_out, so there it is.
    cout << max_out;
}

int main(){
    // Try to speed up cin/cout as fast as printf/scanf.
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while(t>0) {
        int n,k;
        cin >> n >> k;
        int i;
        int arr[n];
        for(i=0;i<n;i++)
        {
            cin>>arr[i];
        }
        printKMax(arr, n, k);
        cout << endl;
        t--;
    }
    return 0;
}
