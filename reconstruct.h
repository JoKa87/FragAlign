#ifndef RECONSTRUCT_H
#define RECONSTRUCT_H

#include "get_deviation.h"
#include "load.h"
#include "params.h"
#include "reconstruct.h"
#include "shift.h"
#include "transform_by_history.h"
#include "utils.h"

using namespace std;

class Reconstruct
{
public:
Data out(const Data& input, const Params& params, vector<vector<float> >& best_param_history,
         size_t best_start_poscount, size_t best_end_poscount,
         const bool& target, const bool& full_matrix, const size_t& index);
};

#endif
