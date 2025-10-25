// Sort the points counterclockwise around a reference point
bool sort_ccw(const Point& p, const Point& a, const Point& b) {
	return atan2(a.y - p.y, a.x - p.x) < atan2(b.y - p.y, b.x - p.x);
}

// Find a face of the graph
vector<Point> find_face(map<Point, vector<Point>>& neighbors, const Point& u, const Point& v) {
	vector<Point> face;
	Point current = v, previous = u;

	face.pb(previous);
	while (true) {
		face.pb(current);
		vector<Point>& current_neighbors = neighbors[current];
		auto index = find(ALL(current_neighbors), previous) - current_neighbors.begin();
		int next_index = (index + 1) % sz(current_neighbors);
		Point next_vertex = current_neighbors[next_index];
		if (next_vertex.x == u.x && next_vertex.y == u.y) break;
		previous = current;
		current = next_vertex;
	}
	face.pb(u);
	return face;
}

// Find the outer edge of the graph
pair<Point, Point> find_outer_edge(map<Point, vector<Point>>& mp) {
	auto leftmost = min_element(ALL(mp), [](const pair<Point, vector<Point>>& a, const pair<Point, vector<Point>>& b) {
		return tie(a.first.x, a.first.y) < tie(b.first.x, b.first.y);
	})->first;

	vector<Point>& N_leftmost = mp[leftmost];
	sort(ALL(N_leftmost), [&leftmost](const Point& a, const Point& b) {
		return sort_ccw(leftmost, a, b);
	});

	Point u = N_leftmost[0];
	return {leftmost, u};
}

void doit(){
	int n; // n points.
	map<Point, vector<Point>> mp; //adjacency list.
	set<pair<Point, Point>> seen; //seen edges.

	for (int i = 0; i < n; ++i) {
		ll x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		Point p1 = {x1,y1}, p2 = {x2,y2};
		mp[p1].pb(p2);
		mp[p2].pb(p1);
	}

	for (auto& p : mp) {
		//Sort each adjacency list in counter-clockwise order.
		sort(ALL(p.second), [&p](const Point& a, const Point& b) {
			return sort_ccw(p.first, a, b);
		});
	}

	auto [p, q] = find_outer_edge(mp); 
	vector<Point> outer = find_face(mp, p, q);

	fore(i,0,sz(outer)-1) seen.insert({outer[i], outer[(i+1)%sz(outer)]});

	for (const auto& p : mp) { // find inner faces of the planar graph:
		for (const auto& q : p.second) {
			if (seen.count({p.first, q})) continue;
			seen.insert({p.first, q});
			vector<Point> face = find_face(mp, p.first, q);
			fore(i,0,sz(face)-1) seen.insert({face[i], face[(i+1)%sz(face)]});
		}
	}
}