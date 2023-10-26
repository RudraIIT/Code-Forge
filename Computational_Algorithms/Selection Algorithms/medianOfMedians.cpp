/*
    This code is of median of medians algorithm.
    Implemented for finding Kth largest and smallest element in Time Complexity: - O(N)
    This algorithm divides the array into groups of 5 and finds the median of each group.
    Then deterministically selects a pivot and identifies whether the selected value is the rank asked by the user 
    or not.
*/

#include<bits/stdc++.h>
using namespace std;

// This functions returns the index where the element currently picked should be 
// placed in the sorted position

int partition(vector<int> &nums,int low,int high,int medOfmedians){
    int idx;
    for(int i=low;i<high;i++){
        if(nums[i]==medOfmedians){
            idx = i;
            break;
        }
    }
    
    int pivot = nums[idx];
    swap(nums[idx],nums[high-1]);
    
    int j = low;

    for(int i = low;i<high-1;i++){
        if(nums[i]<=pivot){
            swap(nums[i],nums[j]);
            j++;
        }
    }

    swap(nums[j],nums[high-1]);
    // for(auto i:nums){
    //     cout<<i<<" ";
    // }
    // cout<<endl;
    return j;
}


int findMedian(vector<int> &nums,int low,int count){
    sort(nums.begin()+low,nums.begin()+low+count-1);
    return nums[low + count/2];// it returns the median of the given array
}

int KthSmallest(vector<int>& nums,int low,int high,int k){
    if(low>high) return -1;

    int n = high - low;
    int i;
    int grps = (n+4)/5;
    vector<int> median(grps);

    // diving array into groups of 5

    for(i=0;i<n/5;i++){
        median[i] = findMedian(nums,low+i*5,5);
    }

    if(i*5<n){
        median[i] = findMedian(nums,low+i*5,n%5);
        i++;
    }

    int medianOfMedians;

    if(i==1){
        medianOfMedians = median[i-1];// if size is 1 the median is the element itself
    }
    else{
        medianOfMedians = KthSmallest(median,0,i,i/2);// else call the medianOfMedians recursively
    }

    
    int pi = partition(nums,low,high,medianOfMedians);// the partition index of the current element
    // cout<<j<<endl;

    if(pi+1==k) return nums[pi];// if the partition index ,i.e , rank of the element is the one which has to be find, it returns the value

    else if(pi+1>k){
        return KthSmallest(nums,low,pi,k); // if pi+1 is greater than rank then the element resides in the left half
    }
    else{
        return KthSmallest(nums,pi+1,high,k);// else search for the right half
    }

    return -1;
}

int findKthLargest(vector<int> &nums,int k){
    return KthSmallest(nums,0,nums.size(),nums.size()-k+1);
}



int main(){
    int n,k;
    cin>>n>>k;//Enter the number of elements and the rank of the element to be found (kth largest element)

    vector<int> arr;

    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        arr.push_back(x);
    }
    
    cout<<findKthLargest(arr,k)<<endl;
    
}