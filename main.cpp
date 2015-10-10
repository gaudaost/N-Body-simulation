#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <chrono>
#include <math.h>
#include "model/point3.h"
#include "model/integrator.h"
#include "view.h"
using namespace std;
using namespace std::chrono;

float randFloat(float min, float max) {
	return min
			+ static_cast<float>(rand())
					/ (static_cast<float>(RAND_MAX / (max - min)));
}

Point3 randVec(float min, float max) {
	Point3 output;
	for (int i = 0; i < 3; ++i) {
		output[i] = randFloat(min, max);
	}
	return output;
}
int main(int argc, char** argv) {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	srand(time(NULL));
	vector<Point3> points;
	vector<Point3> vel;
	vector<float> radii;
	float dt=0.1;
	int nPoints=100;
	for (int i = 0; i < nPoints; ++i) {
		points.push_back(randVec(-500,500));
		vel.push_back(randVec(-50,50));
		radii.push_back(randFloat(0,20));
	}
	Integrator integrator=Integrator(points,vel,radii,dt);
	integrator.mainLoop(1000000);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = std::chrono::duration_cast < std::chrono::milliseconds
			> (t2 - t1).count() / 1000.0;
	cout << duration;
	return 0;
}
