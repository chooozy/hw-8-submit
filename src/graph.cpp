#include "graph.h"

void error(string msg) {
    cerr << "Error: " << msg << endl;
    exit(1);
}

string get_arg(int argc, char *argv[], string def) {
    return argc > 1 ? argv[1] : def;
}

void file_to_graph(string filename, Graph& G) {
    ifstream in(filename);
    if (!in.is_open())
        error("Could not open file: " + filename);
    in >> G;
}

Graph Graph::sort_edges() const {
    Graph sorted = *this;
    std::sort(sorted.begin(), sorted.end(),
        [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        });
    return sorted;
}

VertexList Graph::edges_from(Vertex vertex) const {
    VertexList neighbors;
    for (const Edge& e : *this) {
        if (e.u == vertex) neighbors.push_back(e.v);
    }
    return neighbors;
}

VertexList Graph::edges_from_reverse(Vertex vertex) const {
    VertexList neighbors;
    for (int i = size() - 1; i >= 0; i--) {
        const Edge& e = (*this)[i];
        if (e.u == vertex) neighbors.push_back(e.v);
    }
    return neighbors;
}

int sum_weights(const EdgeList& L) {
    return accumulate(L.begin(), L.end(), 0,
        [](int total, const Edge& e) { return total + e.weight; });
}

DisjointSet::DisjointSet(int numVertices) {
    subsets.resize(numVertices);
    for (int i = 0; i < numVertices; i++)
        makeSet(i);
}

void DisjointSet::makeSet(Vertex x) {
    subsets[x].parent = x;
}

Vertex DisjointSet::findSet(Vertex x) {
    if (subsets[x].parent != x)
        subsets[x].parent = findSet(subsets[x].parent);
    return subsets[x].parent;
}

void DisjointSet::unionSets(Vertex x, Vertex y) {
    Vertex rx = findSet(x);
    Vertex ry = findSet(y);
    if (rx == ry) return;
    subsets[ry].parent = rx;
}

VertexList dfs(const Graph& graph, Vertex startVertex) {
    VertexList result;
    vector<bool> visited(graph.numVertices, false);
    stack<Vertex> S;

    S.push(startVertex);

    while (!S.empty()) {
        Vertex v = S.top(); S.pop();
        if (visited[v]) continue;
        visited[v] = true;
        result.push_back(v);

        VertexList neighbors = graph.edges_from_reverse(v);
        for (int i = neighbors.size() - 1; i >= 0; i--) {
            if (!visited[neighbors[i]])
                S.push(neighbors[i]);
        }
    }
    return result;
}

VertexList bfs(const Graph& graph, Vertex startVertex) {
    VertexList result;
    vector<bool> explored(graph.numVertices, false);
    queue<Vertex> Q;

    explored[startVertex] = true;
    Q.push(startVertex);

    while (!Q.empty()) {
        Vertex v = Q.front(); Q.pop();
        result.push_back(v);

        for (Vertex w : graph.edges_from(v)) {
            if (!explored[w]) {
                explored[w] = true;
                Q.push(w);
            }
        }
    }
    return result;
}

EdgeList Kruskals(const Graph& G) {
    EdgeList mst;
    Graph sorted = G.sort_edges();
    DisjointSet ds(G.numVertices);

    for (const Edge& e : sorted) {
        if (ds.findSet(e.u) != ds.findSet(e.v)) {
            mst.push_back(e);
            ds.unionSets(e.u, e.v);
        }
    }
    return mst;
}
