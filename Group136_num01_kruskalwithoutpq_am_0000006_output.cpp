// *********************************************************
// Program: Group136_num01_kruskalwithoutpq_am_0000006_input_files.cpp
// Course: TCP2101 ALGORITHM DESIGN & ANALYSIS
// Class: TC1L
// Trimester: 2220
// Member_1: 1191200692 | Hafiey Daniel Bin Nor' Azman | 1191200692@student.mmu.edu.my | 012-3090244
// Member_2:  |  |  |
// Member_3:  |  |  |
// Member_4:  |  |  |
// *********************************************************
// Task Distribution
// Member_1:  - Question 1 - Question 2
// Member_2:  -
// Member_3:  -
// Member_4:  -
// *********************************************************
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = INT_MAX;
const int n = 6; // n number of vertices

struct Edge {
    int src, dest, weight;
};

vector<Edge> edges;
vector<int> parent(n);

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int findParent(int vertex) {
    if (parent[vertex] == vertex)
        return vertex;
    return findParent(parent[vertex]);
}

void unionSets(int vertex1, int vertex2) {
    int parent1 = findParent(vertex1);
    int parent2 = findParent(vertex2);
    parent[parent2] = parent1;
}

void kruskalMST() {
    auto start = chrono::system_clock::now(); // take start time

    int totalWeight = 0;
    vector<Edge> mst;
    vector<bool> visited(n, false); // track visited vertices

    // Sort edges in ascending order of weights
    sort(edges.begin(), edges.end(), compareEdges);

    // Initialize parent array
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // Find MST by iterating over all edges
    for (const Edge& edge : edges) {
        int parent1 = findParent(edge.src);
        int parent2 = findParent(edge.dest);

        // Add edge to MST if it doesn't form a cycle
        if (parent1 != parent2) {
            mst.push_back(edge);
            totalWeight += edge.weight;
            unionSets(parent1, parent2);
        }
    }

    // Open output file
    ofstream output("kruskalwithoutpq_am_0000006_output.txt");

    // Show and write to the file
    cout << n << endl;
    output << n << endl;
    for (int i = 0; i < n; ++i) {
        cout << i << " " << char('A' + i) << endl;
        output << i << " " << char('A' + i) << endl;
    }

    for (const Edge& edge : mst) {
        cout << char('A' + edge.src) << "-" << char('A' + edge.dest) << " " << edge.weight << endl;
        output << char('A' + edge.src) << "-" << char('A' + edge.dest) << " " << edge.weight << endl;
    }

    cout << totalWeight << endl;
    output << totalWeight << endl;

    auto end = chrono::system_clock::now();
    chrono::duration<double> duration = end - start;
    cout << duration.count() << "s" << endl;
    output << duration.count() << "s" << endl;

    // Close the output file
    output.close();
}

int main() {
    // Read input file
    ifstream input("kruskalwithoutpq_am_0000006_input.txt");

    // Read number of vertices
    int numVertices;
    input >> numVertices;

    // Vertex names (optional)
    vector<char> vertexNames(numVertices);
    for (int i = 0; i < numVertices; i++) {
        int index;
        char name;
        input >> index >> name;
        vertexNames[index] = name;
    }

    // Read edges and weights
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            string weight;
            input >> weight;
            if (weight != "i" && i < j) {
                if (weight == "-")
                    weight = "INF";
                edges.push_back({ i, j, stoi(weight) });
            }
        }
    }

    input.close();

    kruskalMST();

    return 0;
}

