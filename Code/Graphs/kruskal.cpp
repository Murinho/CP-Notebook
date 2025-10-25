const int maxn = 1e5+5;

struct Edge{ ll a,b,c;}; //{Node1, Node2, Cost}.

vector <Edge> edges;

bool cmp(Edge e1, Edge e2){ return e1.c < e2.c;}

void doit(){
	// Initialize Union Find.
	// Read edges.
	ll totalw = 0; // total MST weight.
	sort(ALL(edges),cmp);
	for(auto edge : edges){
		if (bus(edge.a) != bus(edge.b)){
			join(edge.a,edge.b);
			totalw += edge.c;
		}
	}
}
