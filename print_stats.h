#ifndef PRINT_STATS_H
#define PRINT_STATS_H
#include <fstream>
#include <iomanip>

#include "params.h"
#include "run.h"

using namespace std;

class Print_stats
{
public:
void out(const Params& updated_params, const vector<Run_result>& run_results,
         const vector<vector<float> >& stats);
};

#endif
