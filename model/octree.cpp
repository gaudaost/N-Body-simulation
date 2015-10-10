#include "octree.h"
#include<math.h>

void Octree::insertPoint(const Point3& point, const float& mass, const int& index)
{
    int i;
    vector<Point3> boundsNew;
    if(point[2] > center[2]) {
	boundsNew.push_back(center);
	boundsNew.push_back(bounds[1]);
	if(point[0] > center[0] && point[1] > center[1]) {
	    i = 0;
	} else if(point[0] <= center[0] && point[1] > center[1]) {
	    i = 1;
	    boundsNew.at(0)[0] = bounds.at(0)[0];
	    boundsNew.at(1)[0] = center[0];
	} else if(point[0] <= center[0] && point[1] <= center[1]) {
	    i = 2;
	    boundsNew.at(0)[0] = bounds.at(0)[0];
	    boundsNew.at(1)[0] = center[0];
	    boundsNew.at(0)[1] = bounds.at(0)[1];
	    boundsNew.at(1)[1] = center[1];
	} else {
	    i = 3;
	    boundsNew.at(0)[1] = bounds.at(0)[1];
	    boundsNew.at(1)[1] = center[1];
	}
    } else {
	boundsNew.push_back(bounds[0]);
	boundsNew.push_back(center);
	if(point[0] > center[0] && point[1] > center[1]) {
	    i = 4;
	    boundsNew.at(1)[0] = bounds.at(1)[0];
	    boundsNew.at(0)[0] = center[0];
	    boundsNew.at(1)[1] = bounds.at(1)[1];
	    boundsNew.at(0)[1] = center[1];
	} else if(point[0] <= center[0] && point[1] > center[1]) {
	    i = 5;
	    boundsNew.at(1)[1] = bounds.at(1)[1];
	    boundsNew.at(0)[1] = center[1];
	} else if(point[0] <= center[0] && point[1] <= center[1]) {
	    i = 6;
	} else {
	    i = 7;
	    boundsNew.at(1)[0] = bounds.at(1)[0];
	    boundsNew.at(0)[0] = center[0];
	}
    }
    if(children[i] == nullptr) {
	children[i] = new Octree(boundsNew, size / 2);
    }
    children[i]->insert(point, mass, index);
}
Octree::Octree(vector<Point3> bounds, int size)
{
    this->size = size;
    leaf = true;
    this->bounds = bounds;
    for(int i = 0; i < 8; ++i) {
	children.push_back(nullptr);
    }
    center = (bounds[0] + bounds[1]) / 2;
    mass = 0;
}

Octree::~Octree()
{
    for(int i = 0; i < 8; ++i) {
	delete children[i];
    }
}

void Octree::insert(Point3 point, float mass, int index)
{
    points.push_back(point);
    masses.push_back(mass);
    indices.push_back(index);
    if(points.size() > 1) {
	leaf = false;
	if(points.size() == 2) {
	    insertPoint(points[0], masses[0], indices[0]);
	}
	insertPoint(point, mass, index);
    }
}

void Octree::computeCenterOfMass()
{
    if(leaf) {
	mass = masses[0];
	cm = points[0];
	return;
    }
    mass = 0;
    for(int i = 0; i < points.size(); ++i) {
	mass += masses[i];
	cm += masses[i] * points[i];
    }
    cm /= mass;
    for(int i = 0; i < 8; ++i) {
	if(children[i] != nullptr) {
	    children[i]->computeCenterOfMass();
	}
    }
}

Point3 Octree::computeAcc(Point3 pos, int index)
{
    if(leaf && indices[0] == index) {
	return Point3(0, 0, 0);
    }
    Point3 dist = cm - pos;
    float distNorm = dist.norm() + 0.1;
    float thresh = 1;
    if(leaf || size / distNorm < thresh) {
	return mass / (pow(distNorm, 3)) * dist;
    }

    Point3 acc(0, 0, 0);
    for(int i = 0; i < 8; ++i) {
	if(children[i] != nullptr) {
	    acc += children[i]->computeAcc(pos, index);
	}
    }
    return acc;
}
