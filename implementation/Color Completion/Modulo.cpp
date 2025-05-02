#include<bits/stdc++.h>
using namespace std;

void GreedyColorCompletion(vector<pair<float, int>>& intervals, int k);
void GreedyColorCompletion2(vector<pair<float, int>>& intervals, int k);

int main(){
    int n;
    cout << "Enter the number of intervals: ";
    cin >> n;
    
    int k;
    cout << "Enter the chromatic number: ";
    cin >> k;

    vector<pair<float, int>> intervals(n);
    cout << "Enter the intervals: ";
    for(int i=0;i<n;i++){
        cin >> intervals[i].first;
    }

    cout << "Enter the colors of first k intervals: ";
    for(int i=0;i<k;i++){
        cin >> intervals[i].second;
    }

    int flag = n/k - 1;
    int chunk = 0;
    while(flag > 0){
        vector<pair<float, int>> temp(2*k);
        for(int i=chunk*k;i<chunk*k + 2*k;i++){
            temp[i-chunk*k] = intervals[i];
        }
        GreedyColorCompletion(temp, k);
        for(int i=chunk*k;i<chunk*k + 2*k;i++){
            intervals[i] = temp[i-chunk*k];
        }
        chunk++;
        flag--;
    }

    if((float)n/k - chunk > 0){
        vector<pair<float, int>> temp(n-chunk*k);
        for(int i=chunk*k;i<n;i++){
            temp[i-chunk*k] = intervals[i];
        }
        GreedyColorCompletion2(temp, k);
        for(int i=chunk*k;i<n;i++){
            intervals[i] = temp[i-chunk*k];
        }
    }

    // now print the colors assigned to the intervals
    cout << "Colors assigned to the intervals: ";
    for(int i=0;i<n;i++){
        cout << intervals[i].second << " ";
    }

    return 0;
}

void GreedyColorCompletion(vector<pair<float, int>>& intervals, int k){
    vector<bool> isColorUsed(k+1, false);
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
}

void GreedyColorCompletion2(vector<pair<float, int>> &intervals, int k){
    vector<bool> isColorUsed(k+1, false);
    int numOfColorsUsed = 0;
    int n = intervals.size();
    
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
    for(int i=0;(i<k-numOfColorsUsed) && (k+i<n);i++){
        while(isColorUsed[it]) it++;
        intervals[k+i].second = it;
        isColorUsed[it] = true;
        it++;
    }

    // now assign colors to the rest of the intervals using c(Ii) = c(Ii−k)
    for(int i=2*k-numOfColorsUsed;i<n;i++){
        intervals[i].second = intervals[i-k].second;
    }
}

/*
Some sample input

16
4
1 2 3.5 4 4.4 4.8 5 5.5 5.6 6 7 8 8.5 9 9.3 9.6
4 2 3 1

13
5
1 2 3 3.2 3.4 3.6 3.8 4 4.5 5 6 7 8
4 1 2 3 5

13
5
1 2 3 3.2 3.4 3.6 3.8 4 4.5 4.8 6 7 8
4 1 2 3 5

*/