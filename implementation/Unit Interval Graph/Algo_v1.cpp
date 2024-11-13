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

    // Find the correct position to insert `a` to keep `intervals` sorted
    auto pos = lower_bound(intervals.begin(), intervals.end(), a);
    intervals.insert(pos, a);
    return a;
}

void assignColor(vector<float> &intervals, map<float, int> &colors, float &interval){
    // find the position of the interval in the intervals vector
    auto pos = lower_bound(intervals.begin(), intervals.end(), interval);
    int index = pos - intervals.begin();

    if(index == 0){
        // if the interval is the only interval then color it with 0
        // or if the right interval does not overlaps with the current interval then color it with 0
        // or if the right interval is colored with 1 then color it with 0
        if((intervals.size() == 1) || (intervals[index + 1] - intervals[index] >= 1) || colors[intervals[index + 1]] == 1){
            colors[interval] = 0;
        }
        else{
            colors[interval] = 1;
        }
    }
    else if(index == intervals.size() - 1){
        // if the interval is the only interval then color it with 0
        // or if the left interval does not overlaps with the current interval then color it with 0
        // or if the left interval is colored with 1 then color it with 0
        if((intervals.size() == 1) || (intervals[index] - intervals[index-1] >= 1) || colors[intervals[index - 1]] == 1){
            colors[interval] = 0;
        }
        else{
            colors[interval] = 1;
        }
    }
    else{
        // if the left and right intervals are colored with the same color then color the current interval with the other color
        if(colors[intervals[index - 1]] == colors[intervals[index + 1]]){
            colors[interval] = !colors[intervals[index - 1]];
        }
        else{
            // if left and right interval both overlaps with the current interval and they have different colors then recolor one side completely
            if((intervals[index+1] - interval < 1) && (interval - intervals[index-1] < 1)){
                // recolor the side whose length is less
                if(index > intervals.size() - index){
                    // recolor the right side
                    for(int i = index + 1; i < intervals.size(); i++){
                        colors[intervals[i]] = (!(colors[intervals[i]]));
                    }
                }
                else{
                    // recolor the left side
                    for(int i = index - 1; i >= 0; i--){
                        colors[intervals[i]] = (!(colors[intervals[i]]));
                    }
                }
                // assign the color to the interval
                colors[interval] = !colors[intervals[index - 1]];
            }
            // if the left interval does not overlap with current interval
            else if(intervals[index+1] - interval < 1){
                colors[interval] = colors[intervals[index-1]];
            }
            // if the right interval does not overlap with current interval
            else{
                colors[interval] = colors[intervals[index+1]];
            }
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