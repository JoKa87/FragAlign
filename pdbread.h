#ifndef PDBREAD_H
#define PDBREAD_H
#include <string>
#include <vector>
#include "params.h"
#include "pdbstruct.h"

using namespace std;

class Pdbread
{
public:
string warningmode = "ON";
int pdbcheckmode;
Pdbstruct out(const Params& params, const string& path);
};

#endif

