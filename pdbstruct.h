#ifndef PDBSTRUCT_H
#define PDBSTRUCT_H
#include <string>
#include <vector>
using namespace std;

struct Pdbstruct
{
size_t exceptioncheck;
string atmtar;
string pdb;
vector<string> catvec;
vector<int> idvec;
vector<string> atmvec;
vector<string> resnvec;
vector<string> chnvec;
vector<int> residvec;
vector<float> xvec;
vector<float> yvec;
vector<float> zvec;
vector<int> poscountvec;
vector<string> res_info;

vector<int> poscountNvec;
vector<string> resnNvec;
vector<int> residNvec;
};

#endif


