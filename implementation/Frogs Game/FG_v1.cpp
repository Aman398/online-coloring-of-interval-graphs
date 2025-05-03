#include<bits/stdc++.h>
using namespace std;

void input(int &n, int &k, vector<int> &sets);
int frogsGame(vector<int> &sets, int k);
int sumKConsecutive(const vector<int> &sets, int pos, int k, bool left);

int main() {
    int n, k;
    vector<int> sets(n);
    input(n, k, sets);

    int cost = frogsGame(sets, k);
    cout << "Total merging cost: " << cost << endl;

    return 0;
}

void input(int &n, int &k, vector<int> &sets){
    cout << "Enter number of sets (n): ";
    cin >> n;
    cout << "Enter merging parameter (k): ";
    cin >> k;

    if (k > n || k < 1) {
        cout << "Invalid input: k must be between 1 and n.\n";
        return;
    }

    sets.resize(n);
    cout << "Enter the size of each set:\n";
    for (int i = 0; i < n; i++) {
        cout << "Set " << i + 1 << ": ";
        cin >> sets[i];
    }
}


int frogsGame(vector<int> &sets, int k) {
    int total_cost = 0;

    while (sets.size() > 1) {
        int min_cost = numeric_limits<int>::max();
        int merge_index = -1;

        // Find the best pair of adjacent sets to merge
        for (int i = 0; i < sets.size() - 1; i++) {
            
            int left_sum = sumKConsecutive(sets, i, k, true);
            int right_sum = sumKConsecutive(sets, i + 1, k, false);
            
            // if there is no set in left or right side, we should not consider it
            if(left_sum == 0){
                int merge_cost = right_sum;
                if (merge_cost < min_cost) {
                    min_cost = merge_cost;
                    merge_index = i;
                }
            }
            else if(right_sum == 0){
                int merge_cost = left_sum;
                if (merge_cost < min_cost) {
                    min_cost = merge_cost;
                    merge_index = i;
                }
            }
            else{
                int merge_cost = min(left_sum, right_sum);
                if (merge_cost < min_cost) {
                    min_cost = merge_cost;
                    merge_index = i;
                }
            }
        }

        // Merge the selected sets
        sets[merge_index] += sets[merge_index + 1];
        sets.erase(sets.begin() + merge_index + 1);

        // Add the merge cost to the total cost
        total_cost += min_cost;
    }

    return total_cost;
}

// Function to compute the sum of k left/right elements from index `pos`
int sumKConsecutive(const vector<int> &sets, int pos, int k, bool left) {
    int sum = 0;
    int count = 0;
    
    if (left) {
        for (int i = pos - 1; i >= 0 && count < k; i--, count++) {
            sum += sets[i];
        }
    } else {
        for (int i = pos + 1; i < sets.size() && count < k; i++, count++) {
            sum += sets[i];
        }
    }
    // cout << sum << "\n";
    return sum;
}

// Example Input 1:
// 3
// 1
// 2
// 3
// 4

// Example input 2:
// 6
// 2
// 5
// 3
// 7
// 4
// 6
// 10