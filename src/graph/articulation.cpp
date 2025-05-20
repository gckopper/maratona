vector<vector<int>> graph;
vector<int> disc, low;
vector<bool> isArticulation;
int timeCounter = 0;
int articulationCount = 0;

void dfs(int u, int parent) {
    disc[u] = low[u] = ++timeCounter;
    int children = 0;

    for (int v : graph[u]) {
        if (v == parent) continue; // Ignora o pai na DFS

        if (disc[v] == -1) { // Se não foi visitado ainda
            children++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            // Verifica se é um ponto de articulação
            if (parent != -1 && low[v] >= disc[u] && !isArticulation[u]) {
                isArticulation[u] = true;
                articulationCount++;
            }
        } else {
            low[u] = min(low[u], disc[v]);
        }
    }

    // Caso especial: raiz da DFS com 2 ou mais filhos
    if (parent == -1 && children >= 2 && !isArticulation[u]) {
        isArticulation[u] = true;
        articulationCount++;
    }
}

int countArticulations(int n) {
    disc.assign(n, -1);
    low.assign(n, -1);
    isArticulation.assign(n, false);
    timeCounter = 0;
    articulationCount = 0;

    for (int i = 0; i < n; ++i) {
        if (disc[i] == -1) {
            dfs(i, -1); // Inicia DFS com pai -1 (raiz)
        }
    }

    return articulationCount;
}