#ifndef READ_PARAMS_H
#define READ_PARAMS_H

#include <dirent.h>
#include <windows.h>

#include "get_align_boxes.h"
#include "get_path.h"
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


