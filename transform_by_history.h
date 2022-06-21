#ifndef TRANSFORM_BY_HISTORY_H
#define TRANSFORM_BY_HISTORY_H
#include <vector>

using namespace std;

class Transform_by_history
{
public:
vector<vector<float> >& out(vector<vector<float> >& matrix, vector<vector<float> >& param_history);
};

#endif

