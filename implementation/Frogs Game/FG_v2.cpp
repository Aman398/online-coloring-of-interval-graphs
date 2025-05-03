#include<bits/stdc++.h>
using namespace std;

void initializeSums(vector<vector<int>> &sets, int k);
int frogsGame(vector<vector<int>> &sets, int k);
void input(int &n, int &k, vector<vector<int>> &sets);

int main() {
    int n, k;
    vector<vector<int>> sets(n, vector<int>(3)); // Each set stores [size, left k-sum, right k-sum]

    input(n, k, sets);

    initializeSums(sets, k);

    int cost = frogsGame(sets, k);
    cout << "Total merging cost: " << cost << endl;
    return 0;
}

void input(int &n, int &k, vector<vector<int>> &sets){
    cout << "Enter number of sets (n): ";
    cin >> n;
    cout << "Enter merging parameter (k): ";
    cin >> k;
    
    if (k > n || k < 1) {
        cout << "Invalid input: k must be between 1 and n.\n";
        return;
    }

    sets.resize(n, vector<int>(3)); // Each set stores [size, left k-sum, right k-sum]
    cout << "Enter the size of each set:\n";
    for (int i = 0; i < n; i++) {
        cout << "Set " << i + 1 << ": ";
        cin >> sets[i][0];
    }
}

// Function to initialize left and right k-sums
void initializeSums(vector<vector<int>> &sets, int k) {
    int n = sets.size();
    
    // Compute left k-sums
    for (int i = 0; i < n; i++) {
        sets[i][1] = 0;
        for (int j = 1; j <= k && (i - j) >= 0; j++) {
            sets[i][1] += sets[i - j][0];
        }
    }
    
    // Compute right k-sums
    for (int i = 0; i < n; i++) {
        sets[i][2] = 0;
        for (int j = 1; j <= k && (i + j) < n; j++) {
            sets[i][2] += sets[i + j][0];
        }
    }
}

int frogsGame(vector<vector<int>> &sets, int k) {
    int total_cost = 0;
    
    while (sets.size() > 1) {
        int min_cost = numeric_limits<int>::max();
        int merge_index = -1;

        // Find the best pair to merge
        if(sets.size() == 2){
            merge_index = 0;
            break;
        }
        for (int i = 0; i < sets.size() - 1; i++) {
            int left_sum = sets[i][1];
            int right_sum = sets[i + 1][2];
            int merge_cost;
            
            if (left_sum == 0) {
                merge_cost = right_sum;
            } else if (right_sum == 0) {
                merge_cost = left_sum;
            } else {
                merge_cost = min(left_sum, right_sum);
            }
            
            if (merge_cost < min_cost) {
                // cout << merge_cost << "  " << i << "\n";
                min_cost = merge_cost;
                merge_index = i;
            }
        }

        // Merge the sets at merge_index
        sets[merge_index][0] += sets[merge_index + 1][0];
        sets.erase(sets.begin() + merge_index + 1);
        
        // Update k-sums after merging
        initializeSums(sets, k);

        total_cost += min_cost;
    }
    return total_cost;
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