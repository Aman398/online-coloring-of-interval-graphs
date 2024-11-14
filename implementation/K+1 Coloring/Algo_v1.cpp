#include <bits/stdc++.h>
using namespace std;

// Interval class with color and member functions
class Interval{
public:
    int start, end, color;

    Interval(int s, int e, int c) : start(s), end(e), color(c) {}

    // Function to classify intervals into S1, S2, and I
    static void classifyIntervals(const vector<Interval> &intervals, int p1, int p2,
                                  vector<Interval> &S1, vector<Interval> &S2, vector<Interval> &I){
        for (const auto &interval : intervals){
            if (interval.start <= p1 && interval.end > p1){
                S1.push_back(interval);
            }
            else if (interval.start <= p2 && interval.end > p2){
                S2.push_back(interval);
            }
            else{
                I.push_back(interval);
            }
        }
    }

    // Function to merge intervals from S1 and S2 based on color
    static vector<Interval> mergeIntervals(const vector<Interval> &S1, const vector<Interval> &S2, const vector<Interval> &I){
        unordered_map<int, pair<int, int>> colorMap; // Color -> Interval mapping
        vector<Interval> mergedArcs;

        // Add all S1 intervals to colorMap
        for (const auto &interval : S1){
            colorMap[interval.color] = {interval.start, interval.end};
        }

        // Check intervals in S2 and try to merge with S1 intervals of the same color
        for (const auto &interval : S2){
            int color = interval.color;
            if (colorMap.find(color) != colorMap.end()){
                // Merge the S1 interval with the current S2 interval
                auto &s1Interval = colorMap[color];
                mergedArcs.push_back(Interval(interval.start, s1Interval.second, color)); // [S2.start, S1.end) with color
                colorMap.erase(color);                                                    // Remove after merging to avoid duplicates
            }
            else{
                // No matching color found in S1, keep the interval as-is
                mergedArcs.push_back(interval);
            }
        }

        // Add remaining intervals from S1 that were not merged
        for (const auto &entry : colorMap){
            mergedArcs.push_back(Interval(entry.second.first, entry.second.second, entry.first));
        }

        // Add the intervals from the I set as-is
        for (const auto &interval : I){
            mergedArcs.push_back(interval);
        }

        return mergedArcs;
    }

    // Function to print intervals
    static void printCircularArcs(const vector<Interval> &mergedArcs){
        cout << "\nMerged Circular Arcs:" << endl;
        for (const auto &arc : mergedArcs){
            if (arc.start >= arc.end){
                cout << "[" << arc.start << ", " << arc.end << ") with color " << arc.color << " - circular arc" << endl;
            }
            else{
                cout << "[" << arc.start << ", " << arc.end << ") with color " << arc.color << endl;
            }
        }
    }
};

int main(){
    int n;
    cout << "Enter the number of intervals: ";
    cin >> n;

    vector<Interval> intervals;
    for (int i = 0; i < n; ++i){
        int start, end, color;
        cout << "Enter interval " << i + 1 << " (start end color): ";
        cin >> start >> end >> color;
        intervals.emplace_back(start, end, color);
    }

    // Input partition points
    int p1, p2;
    cout << "Enter partition point p1: ";
    cin >> p1;
    cout << "Enter partition point p2: ";
    cin >> p2;

    // Classify intervals into S1, S2, and I
    vector<Interval> S1, S2, I;
    Interval::classifyIntervals(intervals, p1, p2, S1, S2, I);

    // Merge S1 and S2 intervals based on colors
    vector<Interval> mergedArcs = Interval::mergeIntervals(S1, S2, I);

    // Print the final merged circular intervals
    Interval::printCircularArcs(mergedArcs);

    return 0;
}