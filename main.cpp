#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_set>

// Creating the relevant data structures: edge and disjoint set 
struct Edge
{
    int v1;
    int v2;
    int cost;
    bool roadExists; 

    // Defining '<' operator so c++ knows to deal with edges based on cost
    // This is important because we need to sort the list of edges for Kruskal's algorithm
    bool operator<(const Edge& other) const{
        return cost < other.cost;
    }
};

struct disjoint_set
{
    std::vector<int> parent;
    // Constructor intialises parent vector with 'n' elements
    // Sets each node to be its own parent. Meaning initally each node is in its own set.  
    disjoint_set(int n) : parent(n){
        for(int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x){
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool merge(int x, int y){
        int px = find(x);
        int py = find(y);
        if (px == py)
        {
            return false;
        }
        parent[px] = py;
        return true;
    }
};

// Helper Functions
int intCost(char c){
    if('A' <= c && c <= 'Z') return c - 'A';
    return c - 'a' + 26;
}

std::vector<std::string> split(const std::string& s, char delimeter){
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(s);
    
    while(std::getline(ss, token, delimeter))
    {
        tokens.push_back(token);
    }
    
    return tokens;
}

int MST(std::string countries, std::string buildCosts, std::string destroyCosts){
    auto countryTokens = split(countries, ',');
    auto buildTokens = split(buildCosts, ',');
    auto destroyTokens = split(destroyCosts, ',');

    int N = countryTokens.size();
    std::vector<std::vector<int>> country(N, std::vector<int>(N));
    std::vector<std::vector<int>> build(N, std::vector<int>(N));
    std::vector<std::vector<int>> destroy(N, std::vector<int>(N));

    // Populate the matrices
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            country[i][j] = countryTokens[i][j] - '0';
            build[i][j] = intCost(buildTokens[i][j]);
            destroy[i][j] = intCost(destroyTokens[i][j]);
        }
    }

    // Next step is to create the edge list and then we can sort it 
    std::vector<Edge> edges;
    std::unordered_set<std::string> existingEdges;

    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (country[i][j] == 1)
            {
                edges.push_back({i, j, -destroy[i][j], true});
                existingEdges.insert(std::to_string(i) + "," + std::to_string(j));
            }
            else
            {
                edges.push_back({i, j, build[i][j], false});
            }
            
        }
        
    }

    std::sort(edges.begin(), edges.end());

    // Now we use Kruskal's to construct the MST
    disjoint_set ds(N);
    std::unordered_set<std::string> usedEdges;
    int totalCost = 0;

    for(auto& e : edges)
    {
        if(ds.merge(e.v1, e.v2)){
            if(!e.roadExists){
                totalCost += e.cost;
            }
            usedEdges.insert(std::to_string(e.v1) + "," + std::to_string(e.v2));
        }
    }

    // Destroy costs for existing edges that have not been used
    for (int i = 0; i < N; i++)
    {
        for (int j = i+1; j < N; j++)
        {
            if (country[i][j] == 1)
            {
                std::string k = std::to_string(i) + "," + std::to_string(j);
                if (usedEdges.find(k) == usedEdges.end())
                {
                    totalCost += destroy[i][j];
                }
                
            }
            
        }
        
    }
    
    return totalCost;
}

int main(){
    std::string countries;
    std::string buildCosts;
    std::string destroyCosts;

    std::getline(std::cin, countries, ' ');
    std::getline(std::cin, buildCosts, ' ');
    std::getline(std::cin, destroyCosts);

    std::cout << MST(countries, buildCosts, destroyCosts) << std::endl;

    return 0;
}