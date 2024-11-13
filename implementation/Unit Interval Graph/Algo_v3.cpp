// implementation of the algorithm given in the research paper

#include<bits/stdc++.h>
using namespace std;

class Interval;
class UnitIntercalGraph;

void printIntrervals(UnitIntercalGraph G);
void printSortedIntervals(UnitIntercalGraph G);

class Interval{
    public:
        float start;
        float end;
        int color;
        Interval(float start, float end, int color = -1){
            this->start = start;
            this->end = end;
            this->color = color;
        }
};

class UnitIntercalGraph{
    public:
        vector<Interval> intervals;

        void addInterval(float start, float end, int color = -1){
            intervals.push_back(Interval(start, end, color));
        }

        UnitIntercalGraph constructG0(){
            UnitIntercalGraph G0;
            G0.addInterval(0, 1, 0);
            G0.addInterval(0.5, 1.5, 1);
            return G0;
        }

        UnitIntercalGraph recursiveConstruct(int i){
            if(i == 0)
                return constructG0();

            UnitIntercalGraph Gi_minus_1 = recursiveConstruct(i - 1);
            
            // now I want another Gi_minus_1 but its intervals should be shifted by 0.5 value of the last interval's end value
            UnitIntercalGraph Gi;
            float shift1 = 0;
            float shift2 = Gi_minus_1.intervals.back().end + 0.5 - Gi_minus_1.intervals[0].start;
            
            // construct Gi
            for(auto interval : Gi_minus_1.intervals){
                Gi.addInterval(interval.start + shift1, interval.end + shift1, interval.color);
            }
            for(auto interval : Gi_minus_1.intervals){
                Gi.addInterval(interval.start + shift2, interval.end + shift2, interval.color);
            }
            
            // in this way [a, b) and [b+1, c) will always receive same colors
            // now Introduce these 2 intervals: [b+0.25,b+1.25)and[c,c+1)
            shift1 = Gi_minus_1.intervals.back().end - 0.25;
            Gi.addInterval(shift1, shift1+1, -1);
            int n = Gi.intervals.size();
            shift2 = Gi.intervals[n-2].end - 0.5;
            Gi.addInterval(shift2, shift2+1, -1);

            n = Gi.intervals.size();
            // recolor the starting (n-2)/2 intervals
            for(int j = 0; j < (n-2)/2; j++){
                Gi.intervals[j].color = !Gi.intervals[j].color;
            }
            // now color the last 2 intervals
            Gi.intervals[n-2].color = Gi.intervals[0].color;
            Gi.intervals[n-1].color = !Gi.intervals[0].color;
            
            return Gi;
        }
};

int main(){
    int level;
    cout << "Enter the level of the graph: ";
    cin >> level;
    UnitIntercalGraph graph;
    UnitIntercalGraph G = graph.recursiveConstruct(level);
    
    // printIntrervals(G);
    // cout << "\n\n";
    
    // for checking if the output is correct or not
    // printSortedIntervals(G);
    return 0;
}

void printIntrervals(UnitIntercalGraph G){
    for(auto interval : G.intervals){
        cout << "[" << interval.start << ", " << interval.end << ") color: " << interval.color << endl;
    }
}

void printSortedIntervals(UnitIntercalGraph G){
    sort(G.intervals.begin(), G.intervals.end(), [](Interval a, Interval b){
        return a.start < b.start;
    });
    for(auto interval : G.intervals){
        cout << "[" << interval.start << ", " << interval.end << ") color: " << interval.color << endl;
    }
}