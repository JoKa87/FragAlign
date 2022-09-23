#ifndef TRANSFORM_BY_HISTORY_H
#define TRANSFORM_BY_HISTORY_H

#include "multiply.h"
#include "rotate_by_axis.h"
#include "shift.h"

using namespace std;

class Transform_by_history
{
public:
vector<vector<float> >& out(vector<vector<float> >& matrix, vector<vector<float> >& param_history);
};

#endif

