#ifndef LOAD_H
#define LOAD_H

#include "logprint.h"
#include "params.h"
#include "pdbstruct.h"
#include "pdbread.h"
#include "repdetect.h"
#include "repremove.h"

using namespace std;

struct Data
{
vector<size_t> selected_indices;
vector<vector<float> > full_matrix;
vector<vector<float> > matrix;
Pdbstruct pdbstruct;
};

class Load
{
public:
Data out(const Params& params, const string& path, const size_t& index);
};

#endif

