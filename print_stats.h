#ifndef PRINT_STATS_H
#define PRINT_STATS_H
#include <vector>

#include "params.h"

using namespace std;

struct Run_result
{
int duration;
float best_coverage;
float best_rmsd;
string path1;
string path2;
};

class Print_stats
{
public:
void out(const Params& updated_params, const vector<Run_result>& run_results,
         const vector<vector<float> >& stats);
};

#endif
