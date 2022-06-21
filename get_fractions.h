#ifndef GET_FRACTIONS_H
#define GET_FRACTIONS_H
#include <vector>

#include "load.h"
#include "params.h"

struct Best_value
{
int fraction1;
int best_fraction2;
size_t best_start_poscount1;
size_t best_start_poscount2;
size_t best_end_poscount1;
size_t best_end_poscount2;
float best_fraction_rmsd;
vector<size_t> fractions1;
vector<size_t> fractions2;
vector<vector<float> > best_param_history1;
vector<vector<float> > best_param_history2;
};

class Get_fractions
{
public:
vector<Best_value> out(const vector<Best_value> best_values, const Params& params,
                       const Data& input1, const Data& input2,
                       const vector<vector<float> >& substitution_mat,
                       const vector<int>& converted_seq1, const vector<int>& converted_seq2,
                       const size_t& it);
};

#endif
