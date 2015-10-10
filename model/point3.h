/*
 * point3.h
 *
 *  Created on: 8. okt. 2015
 *      Author: gaudaost
 */

#ifndef POINT3_H_
#define POINT3_H_

#include <vector>
#include <iostream>

using namespace std;

class Point3 {
private:
	vector<float> point;
public:
	Point3(vector<float>);
	Point3(float, float, float);
	Point3():Point3(0,0,0){}
	float norm();
	const float operator[](const int&) const;
	float& operator[](const int&);
	void operator+=(const Point3&);
	Point3 operator+(const Point3&);
	Point3 operator-(const Point3&);
};
Point3 operator*(const float&, const Point3&);
Point3 operator/(const Point3&, const float&);
void operator/=(Point3&, const float&);
ostream& operator<<(ostream&, const Point3&);

#endif /* POINT3_H_ */
