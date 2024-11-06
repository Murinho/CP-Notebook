// Volume of a sphere.
ld volumeSphere(ld rad){ 
    return (4.0/3.0)*PI*rad*rad*rad;
}
 
// Volume of a sphere cap.
ld volumeCap(ld h, ld rad){
    return PI*h*h*(rad-(h/3.0));
}

// Area of a triangle given vertices A, B, and C
ld areaTriangle(Point A, Point B, Point C) {
    return fabs((A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2.0);
}

// Area of a circle
ld areaCircle(ld radius) {
    return PI * radius * radius;
}

// Area of a trapezoid given bases and height
ld areaTrapezoid(ld base1, ld base2, ld height) {
    return 0.5 * (base1 + base2) * height;
}

// Volume of a cone
ld volumeCone(ld radius, ld height) {
    return (PI * radius * radius * height) / 3.0;
}

// Volume of a cylinder
ld volumeCylinder(ld radius, ld height) {
    return PI * radius * radius * height;
}

// Volume of a rectangular prism
ld volumeRectPrism(ld length, ld width, ld height) {
    return length * width * height;
}

// Volume of a pyramid with a rectangular base
ld volumePyramid(ld length, ld width, ld height) {
    return (length * width * height) / 3.0;
}

// Area of a parallelogram given two vectors (base and height)
ld areaParallelogram(Point base, Point heightVec) {
    return fabs(base * heightVec);
}

// Perimeter of a polygon given vertices (assuming vertices are in order)
ld perimeterPolygon(vector<Point> &vertices) {
    ld perimeter = 0.0;
    fore(i, 0, sz(vertices)) {
        perimeter += vertices[i].dist(vertices[(i + 1) % sz(vertices)]);
    }
    return perimeter;
}

// Volume of a prism with base area and height
ld volumePrism(ld baseArea, ld height) {
    return baseArea * height;
}

// Surface area of a sphere
ld surfaceAreaSphere(ld radius) {
    return 4 * PI * radius * radius;
}

// Surface area of a cylinder
ld surfaceAreaCylinder(ld radius, ld height) {
    return 2 * PI * radius * (radius + height);
}
