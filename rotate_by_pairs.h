#ifndef ROTATE_BY_PAIRS_H
#define ROTATE_BY_PAIRS_H
#include <vector>

using namespace std;

class Rotate_by_pairs
{
public:
vector<vector<float> > out(vector<vector<float> >& matrix1, vector<vector<float> >& matrix2,
                           vector<vector<float> >& param_history, const Params& params, const size_t& it);
};

#endif
