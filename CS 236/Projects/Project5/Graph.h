//
// Created by Isaac Hamm on 8/3/22.
//

#ifndef LAB4_GRAPH_H
#define LAB4_GRAPH_H

#include <algorithm>


class Graph {

private:
    map<unsigned int, set<unsigned int>> edges;
    map<unsigned int, bool> visited;
    vector<unsigned int> postorder;
    map<unsigned int, set<unsigned int>> forest; // this is where we'll store the SCCs

public:

    Graph() {}
    Graph(const map<unsigned int, set<unsigned int>> &edges, const map<unsigned int, bool> &visited,
          const vector< unsigned int> &postorder) : edges(edges), visited(visited), postorder(postorder) {}

    const map<unsigned int, set<unsigned int>> &getEdges() const { return edges; }
    const map<unsigned int, bool> &getVisited() const { return visited; }
    const vector<unsigned int> &getPostorder() const { return postorder; }
    const map<unsigned int, set<unsigned int>> &getForest() const { return forest; }
    void setEdges(const map<unsigned int, set<unsigned int>> &edges) { Graph::edges = edges; }
    void setVisited(const map<unsigned int, bool> &visited) { Graph::visited = visited; }
    void setPostorder(const vector<unsigned int> &postorder) { Graph::postorder = postorder; }
    void setForest(const map<unsigned int, set<unsigned int>> &forest) { Graph::forest = forest; }

    void toString() {
        string sep = "";

        cout << "Dependency Graph" << endl;
        for(auto x : edges) {
            cout << "R" << x.first << ":";
            sep = "";
            for(auto connector : x.second) {
                cout << sep << "R" << connector;
                sep = ",";
            }
            cout << endl;
        }
        cout << endl;
    }

    //this finds the postorder by calling DFSFP
    void reverseGraph() {
        Graph reverse;
        map<unsigned int, set<unsigned int>> reverseMap;

        for(auto x : this->edges) {
            if(x.second.empty()) {          // this is for nodes with no connections
                reverseMap[x.first];
            }
            for(auto connection : x.second) {
                    reverseMap[connection].insert(
                            x.first); // have to flip these -- this double for loop should make it work
            }
        }

        reverse.setEdges(reverseMap);

        this->postorder = reverse.depthFirstSearchForestPostorder();
    }

    //DFS Forest for Postorder – this is called in the reverseGraph function
    vector<unsigned int> depthFirstSearchForestPostorder() {
        forest.clear();             //empty the forest
        for(auto x : edges) {           //make sure visited are all false
            visited[x.first] = false;
        }

        for(auto x : edges) {
            if(!visited[x.first]) {                         //for all the non-visited nodes, do a DFSP
                depthFirstSearchPostorder(x.first);
            }
        }

        return postorder;
    }

    void depthFirstSearchPostorder(unsigned int vertex) {
        visited[vertex] = true;                             //mark vertex as visited so we don't come back to it
        for(auto neighbor : edges[vertex]) {
            if(!visited[neighbor]) {
                depthFirstSearchPostorder(neighbor);
            }
        }
        postorder.push_back(vertex);
    }

    void depthFirstSearchForestSCC() {
        forest.clear();
        for(auto x : edges) {
            visited[x.first] = false;
        }

        vector<unsigned int> reversePostorder = postorder;
        reverse(reversePostorder.begin(), reversePostorder.end());

        unsigned int counter = 0;
        for(auto order : reversePostorder) {
            if(!visited[order]) {
                set<unsigned int> tree;
                depthFirstSearchSCC(order, tree, counter);  // not sure if this is the most optimal way of adding to the graph, but it seems to work
                forest[counter] = tree;
                counter++;
            }
        }
    }

    // have to pass vertex so we know where we're at, tree so we can build it w/ recursion, and
    //      counter so that we can add the trees in order
    void depthFirstSearchSCC(unsigned int vertex, set<unsigned int>& tree, unsigned int counter) {
        visited[vertex] = true;
        tree.insert(vertex);
        for(auto neighbor : edges[vertex]) {
            if(!visited[neighbor]) {
                forest[counter].insert(neighbor);
                depthFirstSearchSCC(neighbor, tree, counter);
            }
        }
    }

};


#endif //LAB4_GRAPH_H
