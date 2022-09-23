#ifndef ROTATE_BY_AXIS_H
#define ROTATE_BY_AXIS_H
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Rotate_by_axis
{
public:
vector<vector<float> >& out(vector<vector<float> >& rotation_mat, const vector<float>& axis,
                            float angle, const bool& verbosity);
};

#endif

