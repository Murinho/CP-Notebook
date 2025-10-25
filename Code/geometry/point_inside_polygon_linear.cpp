// Checa si un punto dado esta DENTRO, FUERA o en FRONTERA con un poligono
string checkPointInsidePolygon(vector <Point> P, Point point, int n){ 
	P[0] = point;
	ll count = 0;
	if (n < 3) return "OUTSIDE";
	fore(i,1,n+1){
		int j = (i == n ? 1 : i+1);
		if(P[i].x <= P[0].x && P[0].x < P[j].x && P[0].cross(P[i], P[j]) < 0) count++;
		else if(P[j].x <= P[0].x && P[0].x < P[i].x && P[0].cross(P[j], P[i]) < 0)  count++;
		
		if ((min(P[i].x,P[j].x) <= point.x && point.x <= max(P[i].x,P[j].x)) && (min(P[i].y,P[j].y) <= point.y && point.y <= max(P[i].y,P[j].y)) && point.cross(P[i],P[j]) == 0){
			return "BOUNDARY";
		}
	}
	if (count%2 == 1) return "INSIDE";
	return "OUTSIDE";
}