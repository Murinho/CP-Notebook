void doit(){
	Point origin; // define the origin point (the anchor for the angular sorting)
	vector <Point> pts;

	// We will ignore the points the same as the origin
	vector <Point> cleaned_points;
	for(auto &point : pts){
		Point new_point = point;
		new_point.x -= origin.x;
		new_point.y -= origin.y;
		if (new_point.x == 0 && new_point.y == 0) continue;

		cleaned_points.pb(new_point);
	}

	sort(ALL(cleaned_points),angleCmp); // see Geometry Template 2D for angleCmp reference

	// Print the sorted points
	for (auto &point : cleaned_points){
		cout << point.x + origin.x << " " << point.y + origin.y << nl;
	}
}