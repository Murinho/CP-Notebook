const ll maxn = 2e5+10;
deque <int> q; //monotonic deque keeping maximums in front.

void add(int x){ 
	while(!q.empty() && q.back() < x) q.pop_back();
	q.pb(x);
}

void remove(int x){
	if (!q.empty() && q.front() == x) q.pop_front();
}

void clear(){
	while(!q.empty()) q.pop_back();
}

int getBest(){ return q.front(); }
