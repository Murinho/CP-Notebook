// Dados 2 puntos de una recta, devuelve los coeficientes de Ax + By + C = 0
vector <ld> equation_of_line(Point p1, Point p2){ 
	ld a = p1.y-p2.y;
	ld b = p2.x-p1.x;
	ld c = -(a*p1.x) - (b*p1.y);
	return {a,b,c};
}