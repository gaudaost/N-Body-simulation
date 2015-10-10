#include "point3.h"
#include "octree.h"

class Integrator
{
private:
    vector<Point3> points;
    vector<Point3> pointsOld;
    vector<Point3> vel;
    vector<float> radii;
    vector<float> masses;
    float dt;
    bool firstIteration;

    void computeBoundsAndSize(vector<Point3>& bounds, float& size);
    void oneStep();
    void updatePositions(const vector<Point3>& acc);

public:
    Integrator(vector<Point3> points, vector<Point3> vel, vector<float> radii, float dt);
    void mainLoop(int n);
};