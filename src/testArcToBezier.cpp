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


// testArcToBezier.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "arcToBezier.h"

int main()
{
	
	
	vector<tuple<point, point, point>> triplets;
	
	//SVG string literal: M 15 55 A 28 34 72 0 0 75 76
	triplets = arcToBezier(15, 55, 28, 34, 72, 0, 0, 75, 76); //****NOTE: Original code placed
															  //end coordinates after the move 
															  //coordinates, i.e. this:
															  //arcToBezier(15, 55, 75, 76, 28, 34, 72, 0, 0); 
															  //                     /\ /\              /\ /\
															  //Modified here to map to 
															  //to the SVG variable order
	tuple<point, point, point> tuplePoints;
	vector<tuple<point, point, point>>::iterator it;

	for (it = triplets.begin(); it < triplets.end(); it++)
	{
		tuplePoints = *it;

		point pt1 = get<0>(tuplePoints);
		point pt2 = get<1>(tuplePoints);
		point pt3 = get<2>(tuplePoints);
		cout << pt1.x << "," << pt1.y << " " << pt2.x << "," << pt2.y << " " << pt3.x << "," << pt3.y << "\n";
	}

	cin.get();
		//arcToBezier(double px, double py, double cx, double cy, double	rx, double ry, \
			double xAxisRotation = 0, int	largeArcFlag = 0, int sweepFlag = 0);
	return 0;
}