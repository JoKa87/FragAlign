#ifndef EVAL_H
#define EVAL_H
#include <vector>

#include "params.h"
#include "print_stats.h"

using namespace std;

class Eval
{
public:
void out(const Params& updated_params, const vector<Run_result>& run_results,
         const bool& print);
};

#endif
