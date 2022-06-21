#ifndef FILEPRINT_H
#define FILEPRINT_H
#include <vector>

#include "params.h"
#include "pdbstruct.h"

using namespace std;

class Fileprint
{
public:
void out(const Pdbstruct& pdbstruct1, const Pdbstruct& pdbstruct2, const Params& params,
         const size_t& fraction1, const size_t& fraction2, const bool& use_indices);
};

#endif

