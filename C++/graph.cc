/*
 * ===========================================================================
 *
 *       Filename:  graph.cc
 *
 *    Description: I am trying to implement all (most) of the graph
 *                 algorihms... Just to cement my C++ fundamentals. It
 *                 will also reinforce my graph-knowledge.
 *
 *                 TODO: the adjacency list/matrix is still with
 *                 pointers, I shall prefer to totally avoid pointers.
 *                 But then, I'll do it in the future.
 *
 *                 This one contains, different shortest paths,
 *                 traversals, network flow (well, finding augmented
 *                 paths, of course).
 *
 *                 Would like to implement bipartite, maximum matching.
 *                 Also, my own version of the same and do a lot of
 *                 testing.
 *
 *        Version:  1.0
 *        Created:  03/08/13 22:16:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Sadanandan (GS ZZ9 Plural Zα), sandeep.nellayi, gmx.de
 *        Company:  Personal Files.
 *
 * ===========================================================================
 */

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <sstream>
#include <limits>

using namespace std;

static int MinDistance(vector<int> &d, vector<bool> &st);

class Edge
{
    public:
        int start;
        int end;
        int weight;
        int capacity;

        Edge(int u, int v, int w = 1, int c = 0) :
            start(u), end(v), weight(w), capacity(c) {}

        ~Edge()
        {
//            cout << "Edge from " << start << " to " << end << " is dieing" << endl;
        }

        // not creating copy const.
};

class Vertex
{
    public:
        int id;
        string name;
        vector<int> adj;
        vector<Edge> outs;

        Vertex(int vid, string vname) : id(vid), name(vname) { }

        ~Vertex()
        {
//            cout << "Vertex " << id << " is dieing" << endl;
        }

        void AddEdge(Edge e)
        {
            adj.push_back(e.end);
            outs.push_back(Edge(e));
        }
};

class Graph
{
    public:
        string name;
        vector<Vertex> V;
        vector<Edge> E;
        map<string, int> vnames;
        bool directed;

        static int Unreachable()
        {
            return numeric_limits<int>::max() / 2;
        }

        Graph(string str = "Graph", bool dir = false) : name(str), directed(dir) { }

        Graph(vector<Vertex> v, vector<Edge> e) : V(v), E(e) {}

        Graph(Graph& G) : name(G.name), V(G.V), E(G.E) {}

        int VertexCount()
        {
            return V.size();
        }

        string RandomVertex()
        {
            return V[rand() % VertexCount()].name;
        }

        int ** AdjMat(bool capacity = false)
        {
            // create array.
            int ** adjm = new int*[V.size()];
            for( unsigned int i = 0 ; i < V.size() ; i += 1 )
                adjm[i] = new int[V.size()];

            // fill it with zero.
            for( unsigned int i = 0 ; i < V.size() ; i += 1 )
                for( unsigned int j = 0 ; j < V.size() ; j += 1 )
                    adjm[i][j] = (capacity || (i == j)) ? 0 : Unreachable();

            // fill it with data.
            for( unsigned int i = 0 ; i < V.size() ; i += 1 )
            {
                vector<Edge> outs = V[i].outs;
                for(vector<Edge>::iterator it = outs.begin(); it != outs.end(); it++)
                {
                    Edge e = *it;
                    adjm[e.start][e.end] = (capacity) ? e.capacity : e.weight;
                }
            }
            return adjm;
        }

        vector<vector<pair<int, int> > > AdjList(bool capacity = false)
        {
            vector<vector<pair<int, int> > > adjlst;
            for( unsigned int i = 0 ; i < V.size() ; i += 1 )
            {
                vector<pair<int, int> > adjs;
                vector<Edge> outs = V[i].outs;
                for(vector<Edge>::iterator it = outs.begin(); it != outs.end(); it++)
                {
                    Edge e = *it;
                    adjs.push_back(make_pair<int, int>(e.end, (capacity ? e.capacity : e.weight)));
                }
                adjlst.push_back(adjs);
            }
            return adjlst;
        }

        void PrintAdjacencyMatrix(bool capacity = false)
        {
            int ** adjm = AdjMat(capacity);
            PrintAdjacencyMatrix(adjm);
            DeleteAdjm(adjm);
        }

        void PrintAdjacencyMatrix(int ** adjm)
        {
            cout << name << endl;

            for(unsigned int i = 0 ; i < V.size() ; i += 1 )
                cout << ((i == 0) ? "     " : "") << V[i].name << " ";
            cout << endl;

            for(unsigned int i = 0 ; i < V.size() ; i += 1 )
            {
                cout << V[i].name << " ";
                for(unsigned int j = 0 ; j < V.size() ; j += 1 )
                {
                    int value = adjm[i][j];
                    int unreachable = Unreachable();
                    if ((value == unreachable) || (value == 0))
                        cout << "   -"  << " ";
                    else
                        cout << setw(4) << value  << " ";
                }
                cout << endl;
            }
            cout << endl;
        }

        int AddVertex(string name)
        {
            int id;
            if ((id = VertIndex(name)) != -1)
                return id;

            id = V.size();
            V.push_back(Vertex(id, name));
            vnames[name] = id;
            return id;
        }

        int VertIndex(string name, bool addifabsent = false)
        {
            map<string, int>::iterator it;
            if ((it = vnames.find(name)) != vnames.end())
                return it->second;

            if (addifabsent)
                return AddVertex(name);

            return -1;
        }

        void AddEdge(string uname, string vname, int weight = 1, int capacity = 0)
        {
            int id_u = VertIndex(uname, true);
            int id_v = VertIndex(vname, true);
            AddEdge(id_u, id_v, weight, capacity);
            if (!directed)
                AddEdge(id_v, id_u, weight, capacity);
        }

        void AddEdge(int u, int v, int w = 1, int c = 0)
        {
            V[u].AddEdge(Edge(u, v, w, c));
        }

        void PrintAdjacencyList(bool capacity = false)
        {
            vector<vector<pair<int, int> > > adjlst = AdjList(capacity);
            cout << name << endl;
            for(unsigned int i = 0 ; i < adjlst.size() ; i += 1 )
            {
                cout << V[i].name << ": ";
                vector<pair<int, int> > adjs = adjlst[i];
                for(unsigned int j = 0 ; j < adjs.size() ; j += 1 )
                {
                    pair<int, int> vw = adjs[j];
                    string name = V[vw.first].name;
                    cout << (j == 0 ? "" : ", ") << "(" << name << ", " << setw(2) << vw.second << ")";
                }
                cout << endl;
            }
            cout << endl;
        }

        void DFSr(int prev, int current, vector<bool> &visited, vector<int> &previous)
        {
            if (visited[current])
                return;

            cout << " -=> " << V[current].name;
            visited[current] = true;
            previous[current] = prev;

            for(unsigned int i = 0 ; i < V[current].adj.size() ; i += 1 )
            {
                int v = V[current].adj[i];
                DFSr(current, v, visited, previous);
            }
        }

        void DFS(string start, bool recurse = false)
        {
            vector<bool> visited(V.size(), false);
            vector<int> previous(V.size(), -1);

            if (recurse)
            {
                DFSr(-1, VertIndex(start), visited, previous);
                cout << endl;
                return;
            }

            stack<int> S;
            S.push(VertIndex(start));

            while (!S.empty())
            {
                int current = S.top();
                S.pop();

                if(visited[current])
                    continue;

                cout << " -=> " << V[current].name;
                visited[current] = true;

                for(unsigned int i = 0 ; i < V[current].adj.size() ; i += 1 )
                {
                    int v = V[current].adj[i];
                    if (!visited[v])
                    {
                        S.push(v);
                        previous[v] = current;
                    }
                }
            }
            cout << endl;
        }

        void BFS(string start)
        {
            vector<bool> visited(V.size(), false);
            vector<int> previous(V.size(), -1);

            queue<int> Q;
            Q.push(VertIndex(start));

            while (!Q.empty())
            {
                int current = Q.front();
                Q.pop();

                if(visited[current])
                    continue;

                cout << " -=> " << V[current].name;
                visited[current] = true;

                for(unsigned int i = 0 ; i < V[current].adj.size() ; i += 1 )
                {
                    int v = V[current].adj[i];
                    if (!visited[v])
                    {
                        Q.push(v);
                        previous[v] = current;
                    }
                }
            }
            cout << endl;
        }

        void Dijkstra(string start)
        {
            Dijkstra(VertIndex(start));
        }

        void Dijkstra(int s)
        {
            vector<int> previous(V.size(), -1);
            vector<bool> st(V.size(), false);
            vector<int> dist(V.size(), numeric_limits<int>::max() / 2);
            dist[s] = 0;

            for(unsigned int i = 0 ; i < V.size() - 1 ; i += 1 )
            {
                int u = MinDistance(dist, st);
                st[u] = true;
                // the edges from u are to be use to adjune dist.
                vector<Edge> edges = V[u].outs;
                for(unsigned int j = 0 ; j < edges.size() ; j += 1 )
                {
                    int v = edges[j].end;
                    int w = edges[j].weight;
                    if (dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                        previous[v] = u;
                    }
                }
            }

            for( unsigned int i = 0 ; i < V.size() ; i += 1 )
                if (previous[i] != -1)
                    cout << " ==> [" << setw(4) << PrintDistPath(dist, previous, i) << "]" << endl;
        }

        int PrintDistPath(vector<int> &d, vector<int> &prev, int start)
        {
            // check for valid range of start.
            int previous = prev[start];
            if (previous == -1)
            {
                cout << " ==> " << V[start].name;
                return 0;
            }
            int pathweight = PrintDistPath(d, prev, previous);
            int weight = d[start] - d[previous];
            cout << " == (" << setw(4) << weight << ") ==> " << V[start].name;
            return pathweight + weight;
        }

        void BellmanFord(string start)
        {
            BellmanFord(VertIndex(start));
        }

        void BellmanFord(int s)
        {
            vector<int> previous(V.size(), -1);
            vector<bool> st(V.size(), false);
            vector<int> dist(V.size(), numeric_limits<int>::max() / 2);
            dist[s] = 0;
            for( unsigned int j = 0 ; j < V.size() ; j += 1 )
                for( unsigned int i = 0 ; i < V.size() ; i += 1 )
                    for(vector<Edge>::iterator it = V[i].outs.begin(); it != V[i].outs.end(); it++)
                    {
                        Edge edge = *it;
                        int u = edge.start;
                        int v = edge.end;
                        int w = edge.weight;
                        if (dist[u] + w < dist[v])
                        {
                            dist[v] = dist[u] + w;
                            previous[v] = u;
                        }
                    }

            // check for negative cycle.
            for( unsigned int i = 0 ; i < V.size() ; i += 1 )
                if (previous[i] != -1)
                    cout << " ==> [" << setw(4) << PrintDistPath(dist, previous, i) << "]" << endl;
        }

        void FloydWarshall()
        {
            int ** adjm = AdjMat();
            PrintAdjacencyMatrix(adjm);
            for( unsigned int k = 0 ; k < V.size() ; k += 1)
                for( unsigned int j = 0 ; j < V.size() ; j += 1)
                    for( unsigned int i = 0 ; i < V.size() ; i += 1)
                    {
                        int ik, kj, ij;
                        ik = adjm[i][k];
                        kj = adjm[k][j];
                        ij = adjm[i][j];
                        if (ik + kj < ij)
                            adjm[i][j] = ik + kj;
                    }
            PrintAdjacencyMatrix(adjm);
            DeleteAdjm(adjm);
        }

        void DFSspcl(int ** adjm, int s, vector<bool> &visited)
        {
            if (visited[s])
                return;

            visited[s] = true;
            for( unsigned int i = 0 ; i < V.size() ; i += 1 )
                if (!visited[i] && (adjm[s][i] > 0))
                    DFSspcl(adjm, i, visited);
        }

        void FordFulkerson(string start, string end, bool mincut = true)
        {
            int flow = FordFulkerson(VertIndex(start), VertIndex(end), mincut);
            cout << "Max flow from " << start << " to " << end << " is " << setw(4) << flow << endl;
        }

        bool AugPath(int ** resiGraph, int s, int t, vector<int> &previous)
        {
            vector<bool> visited(V.size(), false);
            queue<int> Q;
            Q.push(s);
            visited[s] = true;
            previous[s] = -1;

            while(!Q.empty())
            {
                int u = Q.front();
                Q.pop();

                for( unsigned int v = 0 ; v < V.size() ; v += 1 )
                    if (!visited[v] && (resiGraph[u][v] > 0))
                    {
                        Q.push(v);
                        previous[v] = u;
                        visited[v] = true;
                        if (u == t)
                            return true;
                    }
            }
            return visited[t];
        }

        int FordFulkerson(int s, int t, bool mincut)
        {
            PrintAdjacencyMatrix(true);
            int ** adjm = AdjMat(true);
            vector<int> previous(V.size(), -1);

            int maxflow = 0;

            while (AugPath(adjm, s, t, previous))
            {
                int u, v, path_flow = Unreachable();
                for ( v = t; v != s; v = previous[v])
                {
                    u = previous[v];
                    path_flow = min(path_flow, adjm[u][v]);
                }

                for ( v = t; v != s; v = previous[v])
                {
                    u = previous[v];
                    adjm[u][v] -= path_flow;
                    adjm[v][u] += path_flow;
                }

                maxflow += path_flow;
            }

            if (mincut)
            {
                vector<bool> visited(V.size(), false);
                DFSspcl(adjm, s, visited);

                // get the original graph.
                int ** origAdjm = AdjMat(false);

                for( unsigned int i = 0 ; i < V.size() ; i += 1 )
                {
                    bool linestart = true;
                    for( unsigned int j = 0 ; j < V.size() ; j += 1 )
                        if (visited[i] && !visited[j] && (origAdjm[i][j] != Unreachable()))
                        {
                            cout << (linestart ? V[i].name + ": ": ", ") << " " << V[j].name;
                            linestart = false;
                        }
                    if (!linestart)
                        cout << endl;
                }
                DeleteAdjm(origAdjm);
            }

            DeleteAdjm(adjm);
            return maxflow;
        }

        void DeleteAdjm(int ** adjm)
        {
            for(unsigned int i = 0; i < V.size(); i++)
                delete [] adjm[i];
            delete [] adjm;
        }
};

static int MinDistance(vector<int> &d, vector<bool> &st)
{
    int min_dst = numeric_limits<int>::max();
    int min_idx;

    for(unsigned int i = 0 ; i < d.size() ; i += 1 )
        if (!st[i]  && (d[i] < min_dst))
        {
            min_dst = d[i];
            min_idx = i;
        }

    return min_idx;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

	// the following are various places in and around my turf/territory
	// in Thrissur, Kerala, India. And the distances are in kilometres
	// and the 'capacity' of the road is based on it's width and
	// 'quality'
    Graph G("thattakam", true);

    G.AddEdge("amba", "bish",  1,  4);
    G.AddEdge("amba", "high",  3,  3);
    G.AddEdge("amba", "mann",  5,  9);
    G.AddEdge("bell", "nadu",  2, 11);
    G.AddEdge("bini", "nbus",  2,  5);
    G.AddEdge("bini", "stat",  1,  6);
    G.AddEdge("bish", "amba",  1,  4);
    G.AddEdge("bish", "mukk",  3,  4);
    G.AddEdge("bish", "zooo",  1,  2);
    G.AddEdge("cldy", "kdk_",  8, 16);
    G.AddEdge("cldy", "shak", 30,  9);
    G.AddEdge("cldy", "vel_", 13,  4);
    G.AddEdge("gvr_", "ijk_", 24, 11);
    G.AddEdge("gvr_", "pknm", 25, 12);
    G.AddEdge("high", "muni",  1, 11);
    G.AddEdge("high", "post",  1,  2);
    G.AddEdge("ijk_", "gvr_", 24, 11);
    G.AddEdge("ijk_", "kdk_", 11,  8);
    G.AddEdge("ijk_", "koka", 20, 12);
    G.AddEdge("ijk_", "pkd_", 14,  6);
    G.AddEdge("kdk_", "cldy",  8, 16);
    G.AddEdge("kdk_", "ijk_", 11,  8);
    G.AddEdge("kdk_", "nly_",  4, 14);
    G.AddEdge("kdk_", "vel_",  8,  5);
    G.AddEdge("koka", "bell",  1,  3);
    G.AddEdge("koka", "post",  2,  2);
    G.AddEdge("koka", "west",  5,  2);
    G.AddEdge("mann", "amba",  5,  9);
    G.AddEdge("mann", "cldy", 26, 15);
    G.AddEdge("mann", "mukk",  2,  8);
    G.AddEdge("mann", "nly_", 15, 15);
    G.AddEdge("mukk", "bish",  3,  4);
    G.AddEdge("mukk", "mann",  2,  8);
    G.AddEdge("muni", "bell",  1, 11);
    G.AddEdge("muni", "post",  1,  5);
    G.AddEdge("mup_", "vel_",  9,  3);
    G.AddEdge("nadu", "bini",  2,  7);
    G.AddEdge("nadu", "patt",  2,  5);
    G.AddEdge("nadu", "west",  3,  5);
    G.AddEdge("nbus", "bini",  2,  5);
    G.AddEdge("nbus", "zooo",  3,  5);
    G.AddEdge("nly_", "ijk_", 13,  5);
    G.AddEdge("nly_", "kdk_",  4, 14);
    G.AddEdge("nly_", "pkd_",  4, 14);
    G.AddEdge("nly_", "shak", 18, 13);
    G.AddEdge("patt", "nbus",  2,  5);
    G.AddEdge("patt", "pknm",  2,  7);
    G.AddEdge("patt", "shor", 22,  8);
    G.AddEdge("pkd_", "mup_",  9,  7);
    G.AddEdge("pkd_", "nly_",  3, 13);
    G.AddEdge("pkd_", "shak", 14, 11);
    G.AddEdge("pknm", "gvr_", 30, 10);
    G.AddEdge("pknm", "patt",  2,  7);
    G.AddEdge("plkd", "mann", 60, 15);
    G.AddEdge("plkd", "shor", 40,  9);
    G.AddEdge("post", "high",  1,  2);
    G.AddEdge("post", "koka",  2,  2);
    G.AddEdge("post", "muni",  1,  5);
    G.AddEdge("post", "shak",  2,  4);
    G.AddEdge("shak", "cldy", 30,  9);
    G.AddEdge("shak", "koka",  2,  5);
    G.AddEdge("shor", "gvr_", 31,  7);
    G.AddEdge("shor", "nbus", 22,  8);
    G.AddEdge("shor", "plkd", 40,  9);
    G.AddEdge("stat", "amba",  4,  3);
    G.AddEdge("stat", "bish",  3,  3);
    G.AddEdge("stat", "high",  1, 11);
    G.AddEdge("stat", "zooo",  2,  4);
    G.AddEdge("vel_", "cldy", 13,  4);
    G.AddEdge("west", "koka",  5,  1);
    G.AddEdge("west", "nadu",  3,  5);
    G.AddEdge("west", "pknm",  3,  3);
    G.AddEdge("zooo", "nbus",  3,  5);
    G.AddEdge("zooo", "stat",  2,  4);

    cout << "----------" << endl;
    G.DFS(G.RandomVertex());
    G.BFS(G.RandomVertex());
    cout << "----------" << endl;
    G.DFS(G.RandomVertex(), true);
    G.BFS(G.RandomVertex());
    cout << "----------" << endl;
    G.PrintAdjacencyMatrix();
    G.PrintAdjacencyList();
    cout << "----------" << endl;
    G.Dijkstra(G.RandomVertex());
    cout << "----------" << endl;
    G.BellmanFord(G.RandomVertex());
    G.BellmanFord(G.RandomVertex());
    cout << "----------" << endl;
    G.FloydWarshall();
    G.FordFulkerson(G.RandomVertex(), G.RandomVertex(), true);
    return 0;
}
