// Assuming no repetition of Intervals
// Assuming the balancing factor as 3/4

#include<bits/stdc++.h>
using namespace std;

typedef struct Graph{
    float lv;
    vector<pair<float, float>> Sv;
    Graph* left;
    Graph* right;
    vector<pair<float, float>> Iv;
    vector<int> PermutationL;
    vector<int> PermutationR;
    int numberOfVertices;
} Graph;

Graph* initializeGraph(int k);
Graph *addInterval(Graph *G, float u, float v);
Graph* updatePermutations(Graph *G, int u, int v);
void findLRSet(vector<pair<float, float>> &L, Graph* G, int u, int v, int endU);
void findColorsOfIntervals(vector<pair<float, float>> intervals, vector<int> &corrColors, Graph *G);
Graph *removeInterval(Graph *G, float u, float v);
Graph* fixGraph(Graph* G, int u, int v);
Graph *constructBalancedG(Graph *G, vector<pair<float, float>> &newIntervals);
int findColor(Graph *G, int u, int v);
int findIndex(Graph *G, int u, int v);
void printG(Graph *G, int level);

int main()
    {
        // chromatic number of a graph, it should be known as prior knowledge
        cout << "Enter the chromatic number of the graph: ";
        int k;
        cin >> k;

        // initializing the graph
        Graph *G = new Graph;
        G = initializeGraph(k);

        // operation: 0 for exit, 1 for query, 2 for adding interval, 3 for removing interval, 4 for printing graph
        while (1)
        {
            int operation;
            cout << "Enter the operation (0 to exit, 1 for query, 2 for adding interval, 3 for removing interval, 4 for printing graph): ";
            cin >> operation;

            if (operation == 0)
                break;

            else if (operation == 1)
            {
                float u, v;
                cout << "Enter the vertices (u, v) of interval whose color you want : ";
                cin >> u >> v;
                int color = findColor(G, u, v);
            }

            else if (operation == 2)
            {
                // add edge
                float u, v;
                cout << "Enter the vertices (u, v) of interval you want to add: ";
                cin >> u >> v;
                G = addInterval(G, u, v); // Assuming addEdge is a function that adds an edge to the graph
                G = fixGraph(G, u, v);
            }
            else if (operation == 3)
            {
                // remove edge
                float u, v;
                cout << "Enter the vertices (u, v) of interval you want to remove: ";
                cin >> u >> v;
                G = removeInterval(G, u, v); // Assuming removeEdge is a function that removes an edge from the graph
                G = fixGraph(G, u, v);
            }
            else if (operation == 4)
            {
                // print the graph
                cout << "Graph: " << endl;
                printG(G, 0);
            }
            else{
            cout << "Invalid operation" << endl;
        }
    }
}

Graph* initializeGraph(int k){
    Graph* G = new Graph;
    
    G->lv = 0;            // lv for root vertex
    
    G->left = NULL;
    G->right = NULL;

    G->numberOfVertices = 0;
    
    G->Sv.clear();
    G->Iv.clear();
    G->PermutationL.clear();
    G->PermutationR.clear();
    
    G->PermutationL.resize(k);
    G->PermutationR.resize(k);

    return G;
}

Graph *addInterval(Graph *G, float u, float v)
{
    // If the current node is NULL, create a new node and return it
    if(G == NULL){
        Graph* newNode = new Graph;
        newNode->lv = u; // Set the level to the midpoint of the interval
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->numberOfVertices = 1; // Initialize with one vertex
        newNode->Sv.push_back(make_pair(u, v)); // Add the interval to the list of intervals
        newNode->Iv.push_back(make_pair(u, v)); // Add the interval to the list of intervals
        return newNode;
    }
    
    G->numberOfVertices++; // Increment the number of vertices in the current node
    G->Iv.push_back(make_pair(u, v)); // Add the interval to the list of intervals
    
    if(G->lv >= u && G->lv < v){
        // If the current node's level is within the interval, add the interval to this node
        G->Sv.push_back(make_pair(u, v));
    }
    else if(G->lv < u){
        // If the current node's level is less than u, go to the right child
        G->right = addInterval(G->right, u, v);
    }
    else{
        // If the current node's level is greater than v, go to the left child
        G->left = addInterval(G->left, u, v);
    }

    G = updatePermutations(G, u, v);
    
    return G;
}

Graph *updatePermutations(Graph *G, int u, int v){
    // calculate begU, endU
    float begU = INT_MAX;
    float endU = INT_MIN;
    for(int i=0;i<G->Iv.size();i++){
        begU = min(begU, G->Iv[i].first);
        endU = max(endU, G->Iv[i].first);
    }

    // find set Lu, Ru
    vector<pair<float, float>> Lu, Ru;
    Graph *leftG = G->left;
    Graph *rightG = G->right;
    
    // Lu
    if(leftG){
        for(int i=0;i<leftG->Iv.size();i++){
            if(leftG->Iv[i].first <= begU && leftG->Iv[i].second > begU)
                Lu.push_back(leftG->Iv[i]);
        }
    }

    // Ru
    if(rightG){
        for(int i=0;i<rightG->Iv.size();i++){
            if(rightG->Iv[i].first <= begU && rightG->Iv[i].second > begU)
                Ru.push_back(rightG->Iv[i]);
        }
    }

    // find set L, R
    vector<pair<float, float>> L, R;
    findLRSet(L, G, u, v, endU);

    int usetSize = Lu.size();
    int rsetSize = Ru.size();
    vector<int>LuColors(usetSize);
    vector<int>RuColors(rsetSize);
    findColorsOfIntervals(Lu, LuColors, G);
    findColorsOfIntervals(Ru, RuColors, G);

    // now I have begU, endU, Lu, LuColors, Ru, RuColors, L, R
    



}

void findLRSet(vector<pair<float, float>> &L, vector<pair<float, float>> &R, Graph *G, int u, int v, int endU)
{
    if(G == NULL)
        return;

    for(int i=0;i<G->Sv.size();i++){
        if(G->Sv[i].first == u && G->Sv[i].second == v)
            return;
    }

    if(G->lv < u){
        if(G->left != NULL){
            if(G->left->lv < endU && endU <= G->lv){
                L.push_back({G->lv, G->left->lv});
            }
            return findLRSet(L,R, G->left, u, v, endU);
        }
    }
    if(G->lv >= v){
        if(G->right != NULL){
            if(G->lv < endU && endU <= G->right->lv){
                R.push_back({G->lv, G->right->lv});
            }
            return findLRSet(L,R, G->right, u, v, endU);
        }
    }
    return;
}

void findColorsOfIntervals(vector<pair<float, float>> intervals, vector<int> &corrColors, Graph *G){
    for(int i=0;i<intervals.size();i++){
        corrColors[i] = findColor(G, intervals[i].first, intervals[i].second);
    }
    return;
}

Graph *removeInterval(Graph *G, float u, float v)
{
    // If the current node is NULL, return NULL
    if(G == NULL){
        return NULL;
    }

    G->numberOfVertices--; // Decrement the number of vertices in the current node
    G->Iv.erase(remove_if(G->Iv.begin(), G->Iv.end(), [u, v](pair<float, float> interval) {
        return (interval.first == u && interval.second == v);
    }), G->Iv.end()); // Remove the interval from the list of intervals

    if(G->lv >= u && G->lv < v){
        // If the current node's level is within the interval, remove the interval from this node
        G->Sv.erase(remove_if(G->Sv.begin(), G->Sv.end(), [u, v](pair<float, float> interval) {
            return (interval.first == u && interval.second == v);
        }), G->Sv.end());
    }
    else if(G->lv < u){
        // If the current node's level is less than u, go to the right child
        G->right = removeInterval(G->right, u, v);
    }
    else{
        // If the current node's level is greater than v, go to the left child
        G->left = removeInterval(G->left, u, v);
    }

    // If the current node has no intervals left, delete it and return NULL
    if(G->Sv.empty() && G->Iv.empty()){
        delete G;
        return NULL;
    }
    // Otherwise, return the current node
    return G;
}

Graph* fixGraph(Graph* G, int u, int v){
    if(G == NULL){
        return NULL;
    }
    if(G->lv == 0){
        G->right = fixGraph(G->right, u, v);
        return G;
    }

    int curr = G->numberOfVertices;
    int left = G->left ? G->left->numberOfVertices : 0;
    int right = G->right ? G->right->numberOfVertices : 0;

    if((max(left, right)) > ((3 * curr) / 4)){
        // Rebalance the tree
        // the intervals which I have to rebalance are already in Sv, sort them first and store in new vector
        vector<pair<float, float>> newIntervals = G->Iv;
        sort(newIntervals.begin(), newIntervals.end(), [](pair<float, float> a, pair<float, float> b) {
            return a.first < b.first;
        });
        
        G = constructBalancedG(G, newIntervals);
        return G;
    }
    else if(G->lv >= u && G->lv < v)
        return G;
    
    // check in the path if any vertex is imbalance
    if(G->lv >= v)
        G->left = fixGraph(G->left, u, v);
    else if(G->lv < u)
        G->right = fixGraph(G->right, u, v);
    return G;
}

Graph* constructBalancedG(Graph* G, vector<pair<float, float>>& newIntervals){
    int n = newIntervals.size();
    if(n == 0)
        return NULL;
    
    // Create a new node with the new level
    Graph* newNode = new Graph;
    int newLv = newIntervals[n/2].first;
    newNode->lv = newLv;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->numberOfVertices = newIntervals.size();
    newNode->Iv = newIntervals; 
    newNode->Sv.clear();

    // Split the intervals into left and right based on the new level
    vector<pair<float, float>> leftIntervals, rightIntervals;
    for(auto interval : newIntervals){
        if(interval.second <= newLv){
            leftIntervals.push_back(interval);
        }
        else if(interval.first > newLv){
            rightIntervals.push_back(interval);
        }
        else{
            newNode->Sv.push_back(interval);
        }
    }

    // Recursively construct the left and right subtrees
    newNode->left = constructBalancedG(newNode->left, leftIntervals);
    newNode->right = constructBalancedG(newNode->right, rightIntervals);

    return newNode;
}

int findColor(Graph *G, int u, int v){
    int index = findIndex(G, u, v);

    if(index == -1)
        return -1;
    
    int color = G->PermutationR[index];

    while(1){
        if(G == NULL)
            return -1;

        // if interval is in Sv then we are done
        if ((G->Sv.size() > index) && (G->Sv[index].first == u) && (G->Sv[index].second == v)){
            return color;
        }
        
        // if interval is in left tree, then left's permutation, else right's permutation.
        if(G->lv >= v){
            color = G->PermutationL[index];
            G = G->left;
        }
        else{
            color = G->PermutationR[index];
            G = G->right;
        }
    }
}

int findIndex(Graph *G, int u, int v){
    if(G == NULL)
        return -1;
    
    // search for (u, v) in G->Sv
    for(int i=0;i<G->Sv.size();i++){
        if(G->Sv[i].first == u && G->Sv[i].second == v)
            return i;
    }

    if(G->lv >= v)
        return findIndex(G->left, u, v);
    
    return findIndex(G->right, u, v);
}

void printG(Graph *G, int level)
{
    if(G == NULL){
        for(int i=0;i<=level;i++)
            cout << "\t";
            cout << "NULL" << endl;
            return;
        }
        
    for(int i=0;i<=level;i++)
        cout << "\t";
    cout << "lv: " << G->lv << endl;
        
    for(int i=0;i<=level;i++)
        cout << "\t";
    cout << "Sv: ";
    for(auto interval : G->Sv){
        cout << "[" << interval.first << ", " << interval.second << "] ";
    }
    cout << endl;

    for (int i=0;i<=level;i++)
        cout << "\t";
    cout << "numberOfVertices: " << G->numberOfVertices << endl;

    for (int i=0;i<=level;i++)
        cout << "\t";
    cout << "Iv: ";
    for(auto interval : G->Iv){
        cout << "[" << interval.first << ", " << interval.second << "] ";
    }
    cout << endl;

    for (int i=0;i<=level;i++)
        cout << "\t";
    cout << "Left Tree:\n";
    printG(G->left, level+1);

    for (int i=0;i<=level;i++)
        cout << "\t";
    cout << "Right Tree:\n";
    printG(G->right, level+1);

    return;
}