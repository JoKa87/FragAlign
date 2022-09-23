#ifndef ROTATE_BY_PAIRS_H
#define ROTATE_BY_PAIRS_H

#include "cross_product.h"
#include "get_stats.h"
#include "multiply.h"
#include "load.h"
#include "rotate_by_axis.h"
#include "shift.h"

using namespace std;

class Rotate_by_pairs
{
public:
vector<vector<float> > out(vector<vector<float> >& matrix1, vector<vector<float> >& matrix2,
                           vector<vector<float> >& param_history, const Params& params, const size_t& it);
};

#endif
