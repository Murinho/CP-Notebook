bool doIntersect(Point p1, Point q1, Point p2, Point q2){ //Checa si 2 lineas se intersectan o no.
	int o1 = p1.cross(q1, p2);
	int o2 = p1.cross(q1, q2);
	int o3 = p2.cross(q2, p1);
	int o4 = p2.cross(q2, q1);
  
	if (o1 != o2 && o3 != o4) return true;
	if (o1 == 0 && p2.onSegment(p1, q1)) return true;
	if (o2 == 0 && q2.onSegment(p1, q1)) return true;
	if (o3 == 0 && p1.onSegment(p2, q2)) return true;
	if (o4 == 0 && q1.onSegment(p2, q2)) return true;
  
	return false; 
}