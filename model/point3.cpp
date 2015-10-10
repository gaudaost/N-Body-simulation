/*
 * point3.cpp
 *
 *  Created on: 8. okt. 2015
 *      Author: gaudaost
 */
#include "point3.h"
#include<math.h>

Point3::Point3(vector<float> point) {
	this->point = point;
}

Point3::Point3(float x, float y, float z) {
	point.push_back(x);
	point.push_back(y);
	point.push_back(z);
}

float Point3::norm() {
	return sqrt(point[0] * point[0] + point[1] * point[1] + point[2] * point[2]);
}

const float Point3::operator[](const int &i) const {
	return point[i];
}

float& Point3::operator[](const int &i) {
	return point[i];
}

void Point3::operator+=(const Point3 &p) {
	for (int i = 0; i < point.size(); ++i) {
		point[i] += p.point[i];
	}
}

Point3 Point3::operator+(const Point3 &p) {
	vector<float> out;
	for (int i = 0; i < point.size(); ++i) {
		out.push_back(point[i] + p.point[i]);
	}
	Point3 output(out);
	return output;
}

Point3 Point3::operator-(const Point3 &p) {
	vector<float> out;
	for (int i = 0; i < point.size(); ++i) {
		out.push_back(point[i] - p.point[i]);
	}
	Point3 output(out);
	return output;
}

Point3 operator*(const float &c, const Point3 &point) {
	vector<float> out;
	for (int i = 0; i < 3; ++i) {
		out.push_back(point[i] * c);
	}
	Point3 output(out);
	return output;
}

Point3 operator/(const Point3 &point, const float &c) {
	vector<float> out;
	for (int i = 0; i < 3; ++i) {
		out.push_back(point[i] / c);
	}
	Point3 output(out);
	return output;
}

void operator/=(Point3 &point, const float &c) {
	for (int i = 0; i < 3; ++i) {
		point[i] /= c;
	}
}

ostream& operator<<(ostream &out, const Point3 &point) {
	// Since operator<< is a friend of the Point class, we can access
	// Point's members directly.
	out << "[" << point[0] << "," << point[1] << "," << point[2] << "]" << endl;
	return out;
}

