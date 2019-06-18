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

#include "arcToBezier.h"

const point mapToEllipse(double x, double y, double rx, double ry, double cosphi, double sinphi, double centerx, double centery)
{
	x *= rx;
	y *= ry;

	const double xp = cosphi * x - sinphi * y;
	const double yp = sinphi * x + cosphi * y;
	point pt;
	pt.x = xp + centerx;
	pt.y = yp + centery;
	return pt;
}

tuple<point, point, point> approxUnitArc(double ang1, double ang2)
{
	// See http://spencermortensen.com/articles/bezier-circle/ for the derivation
	// of this constant.
	// Note: We need to keep the sign of ang2, because this determines the
	//       direction of the arc using the sweep-flag parameter.
	int direction;
	if (ang2 < 0)
		direction = -1;
	else
		direction = 1;

	const double c = 0.551915024494 * direction;

	const double x1 = cos(ang1);
	const double y1 = sin(ang1);
	const double x2 = cos(ang1 + ang2);
	const double y2 = sin(ang1 + ang2);

	point pt1, pt2, pt3;

	pt1.x = x1 - y1 * c;
	pt1.y = y1 + x1 * c;

	pt2.x = x2 + y2 * c;
	pt2.y = y2 - x2 * c;

	pt3.x = x2;
	pt3.y = y2;


	threePt = make_tuple(pt1, pt2, pt3);
	return threePt;
}

const double vectorAngle(double ux, double uy, double vx, double vy)
{
	double sign;
	if (ux * vy - uy * vx < 0)
		sign = -1;
	else
		sign = 1;

	const double umag = sqrt(ux * ux + uy * uy);
	const double vmag = sqrt(ux * ux + uy * uy);
	const double dot = ux * vx + uy * vy;

	double div = dot / (umag * vmag);

	if (div > 1)
	{
		div = 1;
	}

	if (div < -1)
	{
		div = -1;
	}

	return sign * acos(div);
}

const tuple <double, double, double, double> getArcCenter(double px, double	py, double cx, double cy, double rx, double	ry, int largeArcFlag, \
	int sweepFlag, double sinphi, double cosphi, double pxp, double pyp)
{

	const double rxsq = pow(rx, 2);
	const double rysq = pow(ry, 2);
	const double pxpsq = pow(pxp, 2);
	const double pypsq = pow(pyp, 2);

	double  radicant = (rxsq * rysq) - (rxsq * pypsq) - (rysq * pxpsq);

	if (radicant < 0)
	{
		radicant = 0;
	}

	radicant /= (rxsq * pypsq) + (rysq * pxpsq);
	if (largeArcFlag == sweepFlag)
		largeArcFlag = -1;
	else
		largeArcFlag = 1;

	radicant = sqrt(radicant) * largeArcFlag;

	const double centerxp = radicant * rx / ry * pyp;
	const double centeryp = radicant * -ry / rx * pxp;

	const double centerx = cosphi * centerxp - sinphi * centeryp + (px + cx) / 2;
	const double centery = sinphi * centerxp + cosphi * centeryp + (py + cy) / 2;

	const double vx1 = (pxp - centerxp) / rx;
	const double vy1 = (pyp - centeryp) / ry;
	const double vx2 = (-pxp - centerxp) / rx;
	const double vy2 = (-pyp - centeryp) / ry;

	double ang1 = vectorAngle(1, 0, vx1, vy1);
	double ang2 = vectorAngle(vx1, vy1, vx2, vy2);

	if (sweepFlag == 0 && ang2 > 0)
	{
		ang2 -= TAU;
	}

	if (sweepFlag == 1 && ang2 < 0)
	{
		ang2 += TAU;
	}

	return{ centerx, centery, ang1, ang2 };
}
vector<tuple<point, point, point>>arcToBezier(double px, double py, double rx, double ry, double xAxisRotation, \
	int	largeArcFlag, int sweepFlag, double cx, double cy)
{
	vector<tuple<point, point, point>> curves;

	if (rx == 0 || ry == 0) {
		return{};
	}

	const double sinphi = sin(xAxisRotation * TAU / 360);
	const double cosphi = cos(xAxisRotation * TAU / 360);

	const double pxp = cosphi * (px - cx) / 2 + sinphi * (py - cy) / 2;
	const double pyp = -sinphi * (px - cx) / 2 + cosphi * (py - cy) / 2;

	if (pxp == 0 && pyp == 0) {
		return{};
	}

	rx = abs(rx);
	ry = abs(ry);

	const double lambda = pow(pxp, 2) / pow(rx, 2) + pow(pyp, 2) / pow(ry, 2);

	if (lambda > 1) {
		rx *= sqrt(lambda);
		ry *= sqrt(lambda);
	}
	double centerx, centery, ang1, ang2;
	tie(centerx, centery, ang1, ang2) = getArcCenter(px, py, cx, cy, rx, ry, largeArcFlag, \
		sweepFlag, sinphi, cosphi, pxp, pyp);

	// If 'ang2' == 90.0000000001, then `ratio` will evaluate to
	// 1.0000000001. This causes `segments` to be greater than one, which is an
	// unecessary split, and adds extra points to the bezier curve. To alleviate
	// this issue, we round to 1.0 when the ratio is close to 1.0.
	double ratio = abs(ang2) / (TAU / 4);
	if (abs(1.0 - ratio) < 0.0000001)
	{
		ratio = 1.0;
	}

	const double segments = max(ceil(ratio), (double)1);

	ang2 /= segments;

	for (long i = 0; i < segments; i++) {
		curves.push_back(approxUnitArc(ang1, ang2));
		ang1 += ang2;
	}

	tuple <point, point, point> bezierPiece;
	vector<tuple<point, point, point>>::iterator ptr;
	vector<tuple<point, point, point>> tripletPoints;
	point pt1, pt2, pt3;

	for (ptr = curves.begin(); ptr < curves.end(); ptr++)
	{
		bezierPiece = *ptr;
		pt1 = get<0>(bezierPiece);
		pt2 = get<1>(bezierPiece);
		pt3 = get<2>(bezierPiece);

		pt1 = mapToEllipse(pt1.x, pt1.y, rx, ry, cosphi, sinphi, centerx, centery);
		pt2 = mapToEllipse(pt2.x, pt2.y, rx, ry, cosphi, sinphi, centerx, centery);
		pt3 = mapToEllipse(pt3.x, pt3.y, rx, ry, cosphi, sinphi, centerx, centery);

		tripletPoints.push_back(make_tuple(pt1, pt2, pt3));
	}


	return tripletPoints;
}