#ifndef SHIFT_H
#define SHIFT_H
#include <vector>

using namespace std;

class Shift
{
public:
vector<vector<float> >& out(vector<vector<float> >& matrix, vector<vector<float> >& param_history,
                            const vector<float>& shift_vector, const bool& additive, const bool& write_history);
};

#endif
