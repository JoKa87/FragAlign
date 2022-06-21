#ifndef READ_PARAMS_H
#define READ_PARAMS_H
#include <vector>

#include "params.h"

using namespace std;

class Read_params
{
public:
string default_dir;
string filename;
Params out();
};

#endif


