#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H
#include <fstream>
#include <iostream>

#include "params.h"

using namespace std;

class Substitution
{
public:
vector<vector<float> > out(const Params& params);
};


#endif


