#ifndef REPDETECT_H
#define REPDETECT_H
#include <iostream>

#include "params.h"
#include "pdbstruct.h"

using namespace std;

struct Repstruct
{
vector<vector<int> > localredidmat;
vector<vector<int> > localrepposmat;
};

class Repdetect
{
public:
Repstruct out(const Pdbstruct& pdbstruct, const Params& params);
};

#endif
