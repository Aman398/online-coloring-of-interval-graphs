// if it is guranteed that the intervals are coming in a sorted way then we can use this approach

#include<bits/stdc++.h>
using namespace std;

float takeInput(vector<float> &intervals, int i);
void assignColor(vector<float> &intervals, map<float, int> &colors, float &interval);
void printIntervals(vector<float> intervals);
void printColors(map<float, int> colors);

int main(){
    int n;
    cout << "Enter the number of intervals that will be coming: ";
    cin >> n;

    // i don't need pair<int, int> as it is unit interval G, so if start time then I can say that it is [start, start+1)
    vector<float> intervals;
    int color = 0;
    map<float, int> colors;
    for (int i = 0; i < n; i++){
        float interval = takeInput(intervals, i + 1);
        assignColor(intervals, colors, interval);
    }
    printColors(colors);
}

float takeInput(vector<float> &intervals, int i){
    float a;
    cout << "Enter the " << i << " interval: ";
    cin >> a;
    intervals.push_back(a);
    return a;
}

void assignColor(vector<float> &intervals, map<float, int> &colors, float &interval){
    int index = intervals.size() - 1;
    if(index == 0){
        colors[interval] = 0;
    }
    else{
        if((interval - intervals[index - 1] >= 1) || (colors[intervals[index - 1]] == 1)){
            colors[interval] = 0;
        }
        else{
            colors[interval] = 1;
        }
    }
}

void printIntervals(vector<float> intervals){
    cout << "The intervals are: ";
    for(auto interval: intervals){
        cout << "[" << interval << " , " << interval + 1 << ") ";
    }
    cout << "\n";
}

void printColors(map<float, int> colors){
    cout << "The colors are: \n";
    for(auto interval: colors){
        cout << "[" << interval.first << " , " << interval.first + 1 << ") \t:\t" << interval.second << "\n";
    }
}