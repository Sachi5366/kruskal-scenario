#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long w;
    int id; // optional: original index
    bool operator<(Edge const& other) const {
        return w < other.w;
    }
};

struct DSU {
    int n;
    vector<int> parent, rankv;
    DSU(int n): n(n), parent(n+1), rankv(n+1,0){
        for(int i=0;i<=n;i++) parent[i]=i;
    }
    int find(int x){
        if(parent[x]==x) return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int a, int b){
        a = find(a); b = find(b);
        if(a==b) return false;
        if(rankv[a]<rankv[b]) swap(a,b);
        parent[b]=a;
        if(rankv[a]==rankv[b]) rankv[a]++;
        return true;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    // Input format:
    // n m
    // m lines: u v w  (1-based node indices)
    if(!(cin >> n >> m)){
        cerr << "Invalid input\n";
        return 0;
    }

    vector<Edge> edges;
    edges.reserve(m);
    for(int i=0;i<m;i++){
        int u,v; long long w;
        cin >> u >> v >> w;
        if(u<1 || u>n || v<1 || v>n){
            cerr << "Node index out of range: " << u << " " << v << "\n";
            return 0;
        }
        edges.push_back({u,v,w,i+1});
    }

    sort(edges.begin(), edges.end()); // ascending by weight

    DSU dsu(n);
    long long mst_cost = 0;
    vector<Edge> mst_edges;
    for(auto &e : edges){
        if(dsu.unite(e.u, e.v)){
            mst_cost += e.w;
            mst_edges.push_back(e);
            if((int)mst_edges.size() == n-1) break; // early stop
        }
    }

    // Check connectedness: we must have exactly n-1 edges for a connected MST
    if((int)mst_edges.size() != n-1){
        cout << "Impossible to connect all cities (graph is disconnected)\n";
        return 0;
    }

    cout << "MST total cost: " << mst_cost << "\n";
    cout << "Edges in MST (u v weight):\n";
    for(auto &e : mst_edges)
        cout << e.u << " " << e.v << " " << e.w << "\n";

    return 0;
}
