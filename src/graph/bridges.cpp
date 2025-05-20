vector<vector<int>> adj; // Lista de adjacência do grafo
vector<pair<int, int>> bridges; // Armazena as pontes encontradas
vector<int> disc, low; // Tempos de descoberta e menores tempos alcançáveis
int timer = 0; // Contador de tempo para a DFS

void findBridges(int u, int parent = -1) {
    disc[u] = low[u] = timer++;
    
    for (int v : adj[u]) {
        if (v == parent) continue; // Ignora o pai na árvore DFS
        
        if (disc[v] == -1) { // Vértice não visitado
            findBridges(v, u);
            low[u] = min(low[u], low[v]);
            
            // Verifica se é ponte
            if (low[v] > disc[u]) {
                bridges.push_back({u, v});
            }
        } else {
            // Vértice já visitado (aresta de retorno)
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main() {
   
    // Executa o algoritmo para cada componente conexa
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            findBridges(i);
        }
    }
    
    // Imprime as pontes encontradas
    cout << "Pontes encontradas:\n";
    for (auto [u, v] : bridges) {
        cout << u << " - " << v << endl;
    }
    
    return 0;
}