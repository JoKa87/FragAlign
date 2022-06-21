#ifndef CONVERT_SEQUENCE_H
#define CONVERT_SEQUENCE_H
#include <vector>

#include "params.h"

using namespace std;

class Convert_sequence
{
public:
vector<int> out(const Params& params, const vector<string>& sequence);
};


#endif
