# SVG arc to cubic bezier
A conversion from Javascript to C++. Based on this project:
**colinmeinke/svg-arc-to-cubic-bezier**

At its heart, this project is simply a function that takes an SVG arc curve as input, and maps it to
one or more cubic bezier curves.

A Visual Studio project is included to get you up and running as quickly as possible.
## Usage
Sample SVG arc: M 15 55 A 28 34 72 0 0 75 76 <br>
and associated code snippet:

**struct point 
{
 double x,y;
 };**

 **vector<tuple<point, point, point>> triplets;<br>
 triplets = arcToBezier(15, 55, 28, 34, 72, 0, 0, 75, 76);**

See the source files for a more complete solution.
