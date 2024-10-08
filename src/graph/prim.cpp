#include "../template.h"

typedef uint32_t    u32;

#define U32MAX UINT32_MAX

using namespace std;

// weighted edge
typedef pair<u32, u32> wedge;

u32 prim(const vector<vector<wedge>> &graph) {
    const auto min_cmp = [](const wedge& a, const wedge& b) {
        return a.second > b.second;
    };
    priority_queue<wedge, vector<wedge>, decltype(min_cmp)> pq{min_cmp};
    vector<bool> visited(graph.size());
    vector<u32> min_dist(graph.size(), U32MAX);
    min_dist[0] = 0;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        wedge cur = pq.top();
        pq.pop();
        if (visited[cur.first]) {
            continue;
        }
        visited[cur.first] = true;

        for (const wedge adj : graph[cur.first]) {
            if (visited[adj.first]) {
                continue;
            }
            if (min_dist[adj.first] <= adj.second) {
                continue; 
            }
            min_dist[adj.first] = adj.second;
            pq.push(adj);
        }
    }
    u32 acc = 0;
    for (u32 v : min_dist) acc += v;
    return acc;
}

// tests
int ReadFromStd(void) {
    u32 nof_v, nof_e, v, u, w;

    scanf("%u %u", &nof_v, &nof_e);

    vector<vector<wedge>> graph(nof_v);

    for (u32 i = 0; i < nof_e; ++i) {
        scanf("%u %u %u", &v, &u, &w);
        graph[v].emplace_back(u, w);
        graph[u].emplace_back(v, w);
    }

    printf("%u\n", prim(graph));
    
    return 0;
}
