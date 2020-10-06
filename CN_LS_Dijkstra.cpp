#include<bits/stdc++.h>
using namespace std;

const int INF = 0x7f7f7f7f;

typedef pair< int , char > pic;
unordered_map< char , int > dist;
unordered_map< char , char > parent;

void dijkstra(unordered_map<char , vector< pair< char , int > > > &adjacentList, char source)
{
    priority_queue< pic, vector< pic >, greater<pic> > pq;
    pq.push(make_pair(0,source));
    dist[source]=0;
    while(!pq.empty())
    {
        pic top = pq.top(); pq.pop();

        for(auto x : adjacentList[top.second])
        {
            if(dist[x.first]>top.first+x.second)
            {
                dist[x.first]=top.first+x.second;
                parent[x.first]=top.second;
                pq.push(make_pair(dist[x.first],x.first));
            }
        }
    }
    return;
}

char immediate_parent(char x,char source)
{
    if(parent[x]==source) return x;
    else return immediate_parent(parent[x],source);
}

int main()
{
    #ifdef TarekHasan
        freopen("input.txt","r",stdin);
    #endif // TarekHasan

    int vertices, edges; cin >> vertices >> edges;
    unordered_map< char , vector< pair< char , int > > > adjacentList;
    for(int i=0;i<edges;i++)
    {
        char u,v; int w;
        cin >> u >> v >> w;
        adjacentList[u].push_back(make_pair(v,w));
        adjacentList[v].push_back(make_pair(u,w));
    }

    char source; cin >> source;

    for(auto x : adjacentList) dist[x.first]=INF;
    dijkstra(adjacentList,source);


    for(auto x : dist)
        cout << x.first << " " << x.second << endl;

    /*for(auto x : parent)
        cout << x.first << " " << x.second << endl;*/

    cout << "Forwarding Table for " << source << " ::\n";
    for(auto x : adjacentList)
    {
        if(x.first==source) continue;
        cout << x.first << " -> " << "( " << source << " , " << immediate_parent(x.first,source) << " )\n";
    }

    return 0;
}


/*
6 10
u x 1
u v 2
u w 5
v w 3
v x 2
w x 3
w z 5
w y 1
x y 1
y z 2
u
*/
