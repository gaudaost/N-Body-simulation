/*
 * octree.h
 *
 *  Created on: 8. okt. 2015
 *      Author: gaudaost
 */

#ifndef OCTREE_H_
#define OCTREE_H_
#include <vector>
#include "point3.h"

using namespace std;
class Octree
{
private:
    vector<Point3> bounds;
    Point3 center;
    vector<Octree*> children;
    vector<Point3> points;
    vector<int> indices;
    vector<float> masses;
    Point3 cm;
    float mass;
    bool leaf;
    int size;
    void insertPoint(const Point3& point, const float& mass, const int& index);

public:
    Octree(vector<Point3> bounds, int size);
    ~Octree();
    void insert(Point3 point, float mass, int index);
    void computeCenterOfMass();
    Point3 computeAcc(Point3 pos, int index);
};
#endif /* OCTREE_H_ */
