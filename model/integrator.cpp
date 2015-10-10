#include "integrator.h"
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

void Integrator::computeBoundsAndSize(vector<Point3>& bounds, float& size)
{
	int min=points[0][0];
	int max=min;
	for(int i = 0; i < points.size(); i++) {
		for(int j = 0; j < 3; j++) {
			if(points[i][j]<min) {
				min=points[i][j];
			}
			if(points[i][j]>max) {
				max=points[i][j];
			}
		}
	}
	bounds.push_back(Point3(min,min,min));
	bounds.push_back(Point3(max,max,max));
	cout << "Min bound: "  << bounds[0] << "Max bound: " << bounds[1];
	size=max-min;
}
void Integrator::oneStep()
{
	float size=0;
	vector<Point3> bounds;
	computeBoundsAndSize(bounds,size);
	Octree tree=Octree(bounds,size);
	for(int i = 0; i < points.size(); i++) {
		tree.insert(points[i],masses[i],i);
	}
	tree.computeCenterOfMass();
	vector<Point3> acc;
	for(int i = 0; i < points.size(); i++) {
		acc.push_back(tree.computeAcc(points[i],i));
	}
	updatePositions(acc);
}
void Integrator::updatePositions(const vector<Point3>& acc)
{
	for(int i = 0; i < points.size(); i++) {
		if(firstIteration) {
			points[i]+=dt*vel[i]+0.5*pow(dt,2)*acc[i];
		}
		else {
			Point3 tmp=points[i];
			points[i]+=points[i]-pointsOld[i]+pow(dt,2)*acc[i];
			pointsOld[i]=tmp;
		}
	}
}
Integrator::Integrator(vector<Point3> points, vector<Point3> vel, vector<float> radii, float dt)
{
    this->points = points;
	this->pointsOld=points;
    this->vel = vel;
    this->radii = radii;
    for(int i = 0; i < points.size(); i++) {
	this->masses.push_back(pow(radii[i], 3));
    }
    this->firstIteration = true;
    this->dt = dt;
}
void Integrator::mainLoop(int n)
{
	for (int i=0; i<n; i++) {
		oneStep();
		cout << points[0];
	}
}