// Assuming no repetition of Intervals

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
void printG(Graph* G);

int main(){
    // chromatic number of a graph, it should be known as prior knowledge
    cout << "Enter the chromatic number of the graph: ";
    int k;
    cin >> k;

    // initializing the graph
    Graph* G = new Graph;
    G = initializeGraph(k);

    // operation: 0 for exit, 1 for query, 2 for add edge, 3 for remove edge, 4 for printing graph
    while(1){
        int operation;
        cout << "Enter the operation (0 to exit, 1 for query, 2 for add edge, 3 for remove edge, 4 for printing graph): ";
        cin >> operation;
        
        if(operation == 0) 
            break; 

        else if(operation == 1){
        
        }

        else if(operation == 2){
            // add edge
            float u, v;
            cout << "Enter the vertices (u, v): ";
            cin >> u >> v;
            G = addInterval(G, u, v); // Assuming addEdge is a function that adds an edge to the graph
        }
        else if(operation == 3){
            // remove edge
            float u, v;
            cin >> u >> v;
            // G = removeInterval(G, u, v); // Assuming removeEdge is a function that removes an edge from the graph
        }
        else if(operation == 4){
            // print the graph
            cout << "Graph: " << endl;
            printG(G);
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
    
    G->PermutationL.resize(k+1);
    G->PermutationR.resize(k+1);

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
    
    return G;
}

/*
Test case to check the addInterval function:
3
2
1 2
2
1 2.5
2
0.5 1.5
2
0.5 0.8 
2
2 3
2
0.4 1
4
0
*/

void printG(Graph* G){
    if(G == NULL){
        cout << "Nothing more to print" << endl;
        return;
    }

    cout << "lv: " << G->lv << endl;
    
    cout << "Sv: ";
    for(auto interval : G->Sv){
        cout << "[" << interval.first << ", " << interval.second << "] ";
    }
    cout << endl;
    
    cout << "numberOfVertices: " << G->numberOfVertices << endl;
    
    cout << "Iv: ";
    for(auto interval : G->Iv){
        cout << "[" << interval.first << ", " << interval.second << "] ";
    }
    cout << endl;

    cout << "Left Tree:\n";
    printG(G->left);

    cout << "Right Tree:\n";
    printG(G->right);

    return;
}
