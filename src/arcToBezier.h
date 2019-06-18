/*
Original work Copyright (c) 2017, Colin Meinke
Modified work Copyright 2019 Pterylae Systems pterylae.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/


#include <iostream>
#include <tuple>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

#define _USE_MATH_DEFINES

struct point
{
	double x, y;
};

const double pi = 3.14159265358979323846; //hack - not getting access to M_PI
const double TAU = pi * 2;
tuple<point, point, point> threePt;

const point mapToEllipse(double, double, double, double, double, double, double, double);
tuple<point, point, point> approxUnitArc(double, double);
const double vectorAngle(double, double, double, double);
const tuple <double, double, double, double> getArcCenter(double, double, double, double, double, double, int, \
	int, double, double, double, double);
vector<tuple<point, point, point>>arcToBezier(double, double, double, double, double, int, int, double, double);