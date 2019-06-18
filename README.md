# SVG arc to cubic bezier
A conversion from Javascript to C++

A function that takes an SVG arc curve as input, and maps it to
one or more cubic bezier curves.
## Usage
Sample SVG arc: M 15 55 A 28 34 72 0 0 75 76
and associated code snippet:

struct point
{
double x,y
};

vector<tuple<point, point, point>> triplets;
triplets = arcToBezier(15, 55, 28, 34, 72, 0, 0, 75, 76); 

See the associated source files for a more complete solution
