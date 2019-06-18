# SVG arc to cubic bezier
A conversion to c++

A function that takes an SVG arc curve as input, and maps it to
one or more cubic bezier curves.
## Usage
To convert this SVG arc: M 15 55 A 28 34 72 0 0 75 76
use this sample code:

vector<tuple<point, point, point>> triplets;

triplets = arcToBezier(15, 55, 28, 34, 72, 0, 0, 75, 76); 
                      /*NOTE: Original code placed
															  //end coordinates after the move 
															  //coordinates, i.e. this:
															  //arcToBezier(15, 55, 75, 76, 28, 34, 72, 0, 0); 
															  //                     /\ /\              /\ /\
															  //Modified here to map to 
															  //to the SVG variable order

See the associated source files for a more complete solution
