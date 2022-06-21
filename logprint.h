#ifndef LOGPRINT_H
#define LOGPRINT_H
#include <string>

#include "params.h"

using namespace std;

class Logprint
{
public:
void out(const vector<float>& lognumbers, const string& logstr, const Params& params, const bool& init);
};

#endif

