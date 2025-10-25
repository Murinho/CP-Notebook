double f(double x){ return x; }
 
double ternary_search(double l, double r) { //use long doubles (ld) for more precision.                         
	double eps = 1e-9;
	while (r - l > eps) {
		double m1 = l + (r - l) / 3;
		double m2 = r - (r - l) / 3;
		double f1 = f(m1);
		double f2 = f(m2);     
		if (f1 < f2)
			l = m1;
		else
			r = m2;
	}
	return f(l);
} //to find the minimum of a function, invert the sign (-1) of the result of f(x)