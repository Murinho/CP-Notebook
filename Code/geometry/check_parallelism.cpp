bool checkParallelism(Point p1, Point p2, Point p3, Point p4){ //(p1 -- p2) es una linea (p3 -- p4) es la otra linea.
	Point pr1 = {p2.x-p1.x,p2.y-p1.y};
	Point pr2 = {p4.x-p3.x,p4.y-p3.y};
	double cp = (pr1*pr2);
	return abs(cp) < EPS; //son paralelas si su producto cruz = 0.
}