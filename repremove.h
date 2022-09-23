#ifndef REPREMOVE_H
#define REPREMOVE_H
#include <algorithm>

#include "params.h"
#include "pdbstruct.h"
#include "repdetect.h"

using namespace std;

class Repremove
{
public:
Pdbstruct& out(Pdbstruct& pdbstruct, const Repstruct& repstruct, const Params& params);
};

#endif
