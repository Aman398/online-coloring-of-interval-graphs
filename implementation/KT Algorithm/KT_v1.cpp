// implementation of the algorithm in the paper "A New Algorithm for the Chromatic Number of an Interval Graph" by Kierstead and Trotter

#include<bits/stdc++.h>
using namespace std;

void takeInput(vector<pair<int, int>> &intervals, int i);
void printIntervals(vector<pair<int, int>> intervals);
int computeLevel(vector<vector<pair<int, int>>> &levels, pair<int, int> newInterval);
void printLevels(vector<vector<pair<int, int>>> levels);

int main(){
    int n;
    cout << "Enter the number of intervals that will be coming: ";
    cin >> n;

    int k;
    cout << "Enter the final chromatic number of the graph: ";
    cin >> k;

    // I want to assign p(v) to each vertex, so I need a data structure to store them
    vector<vector<pair<int, int>>> levels(k);
    
    // I need a data structure which will store the color of each vertex
    map<pair<int, int>, int> color;

    vector<pair<int, int>> intervals;
    bool check = true;
    for(int i = 0; i < n; i++){
        takeInput(intervals, i + 1);

        // Compute p(v) for the new interval
        pair<int, int> newInterval = intervals.back();
        int level = computeLevel(levels, newInterval);
        
        if(level == 1e6)
            check = false;
        else
            levels[level].push_back(newInterval);

        // color[newInterval] = level;
    }
    
    if(!check){
        cout << "The intervals given are not valid as initial chromatic number given was wrong\n";
        return 0;
    }
    printIntervals(intervals);
    printLevels(levels);
    return 0;
}

void takeInput(vector<pair<int, int>> &intervals, int i){
    int a, b;
    cout << "Enter the " << i << " interval: ";
    cin >> a >> b;
    if(a > b){
        cout << "Invalid interval, please enter this entry again\n";
        takeInput(intervals, i);
        return;
    }
    intervals.push_back({a, b});
    return;
}

void printIntervals(vector<pair<int, int>> intervals){
    cout << "The intervals are: ";
    for(auto interval: intervals){
        cout << "[" << interval.first << " , " << interval.second << ") ";
    }
    cout << "\n";
}

int computeLevel(vector<vector<pair<int, int>>> &levels, pair<int, int> new_interval) {
    for (int i = 0; i < levels.size(); i++) {
        // Collect all intervals from levels 0 to i that intersect with the new interval
        set<pair<int, int>> subgraph_intervals;
        for (int j = 0; j <= i; j++) {
            for (auto &interval : levels[j]) {
                if (interval.second > new_interval.first && interval.first < new_interval.second) {
                    subgraph_intervals.insert(interval);
                }
            }
        }

        // Find the maximum clique size of this subgraph
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (const auto &interval : subgraph_intervals){
            if (!minHeap.empty() && minHeap.top() <= interval.first){
                minHeap.pop();
            }
            minHeap.push(interval.second);
        }
        if(minHeap.size() <= i)
            return i;
    }
    return 1e6;
}

void printLevels(vector<vector<pair<int, int>>> levels){
    cout << "The levels are: \n";
    for(int i = 0; i < levels.size(); i++){
        cout << "Level " << i << ": ";
        for(auto interval: levels[i]){
            cout << "[" << interval.first << " , " << interval.second << ") ";
        }
        cout << "\n";
    }
}