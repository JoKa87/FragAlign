#ifndef GET_STATS_H
#define GET_STATS_H
#include <vector>

#include "load.h"
#include "params.h"

using namespace std;

struct Stats
{
float coverage;
float rmsd;
};

class Get_stats
{
public:
Stats out(const float& best_rmsd, const Params& params, const Data& input1, const Data& input2,
          const vector<vector<float> >& matrix1, const vector<vector<float> >& matrix2,
          const int& fraction1, const int& best_fraction2, const string& rmsd_mode, const float& rmsd_cutoff);
};

#endif

