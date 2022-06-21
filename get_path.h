#ifndef GET_PATH_H
#define GET_PATH_H
#include <vector>
#include "params.h"

using namespace std;

class Get_path
{
public:
bool overwrite = false;
string default_dir;
string message = "select file paths. confirm selection with '0'.";
vector<string> out(const Params& params);
};

#endif
