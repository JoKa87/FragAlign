#ifndef GET_DEVIATION_H
#define GET_DEVIATION_H
#include <string>
#include <vector>

#include "params.h"

using namespace std;

struct Deviation
{
float rmsd;
vector<vector<float> > matrix1;
vector<vector<float> > best_matrix2;
vector<vector<float> > best_param_history1;
vector<vector<float> > best_param_history2;
};

class Get_deviation
{
public:
Deviation& out(Deviation& deviation, const Params& params,
               const size_t& fraction1, const size_t& fraction2, const size_t& index);
};

#endif


