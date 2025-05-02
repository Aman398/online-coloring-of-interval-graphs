// Assume color assigned is from 1 to k

#include<bits/stdc++.h>
using namespace std;

int main(){
    // chromatic number 
    int k;
    cout << "Enter the chromatic number: ";
    cin >> k;

    // number of intervals
    vector<pair<float, int>> intervals(2*k);

    // input intervals, only start is needed as it is unit interval graph
    cout << "Enter the intervals: ";
    for(int i=0;i<2*k;i++){
        cin >> intervals[i].first;
    }

    // now take the colors assigned to initial k intervals
    cout << "Enter the colors of first k intervals: ";
    for(int i=0;i<k;i++){
        cin >> intervals[i].second;
    }

    // now check how many intervals are intersecting the kth interval and what color is assigned to them
    vector<bool>isColorUsed(k+1);
    int numOfColorsUsed = 0;
    for(int i=0;i<k-1;i++){
        if( (intervals[i].first + 1 > intervals[k-1].first) && (intervals[i].first + 1 < intervals[k-1].first + 1) ){
            isColorUsed[intervals[i].second] = true;
            numOfColorsUsed++;
        }
    }
    isColorUsed[intervals[k-1].second] = true; // color of kth interval is also used
    numOfColorsUsed++;
    
    // now assign colors to next (k - numOfColorsUsed) intervals using colors which are not used
    int it = 1;
    for(int i=0;i<k-numOfColorsUsed;i++){
        while(isColorUsed[it]) it++;
        intervals[k+i].second = it;
        isColorUsed[it] = true;
        it++;
    }

    // now assign colors to the rest of the intervals using c(Ii) = c(Ii−k)
    for(int i=2*k-numOfColorsUsed;i<2*k;i++){
        intervals[i].second = intervals[i-k].second;
    }

    // now print the colors assigned to the intervals
    for(int i=0;i<2*k;i++){
        cout << intervals[i].second << " ";
    }

    return 0;
}

/*
Some sample inputs

5
1 2 3 3.2 3.4 3.6 3.8 4 5 6
1 2 3 4 5

5
1 2 3 3.2 3.4 3.6 3.8 4 5 6
4 1 2 5 3

9
1 2 3 4 4.2 4.4 4.6 4.8 4.9 5 5.05 5.06 5.07 5.5 6 7 8 9
5 4 6 7 8 2 3 9 1

9
1 2 3 4 4.2 4.4 4.6 4.8 6 6.05 6.06 6.07 6.5 7 8 9 10 11
5 4 6 7 8 2 3 9 1

*/