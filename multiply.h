#ifndef MULTIPLY_H
#define MULTIPLY_H
#include <vector>

using namespace std;

class Multiply
{
public:
vector<vector<float> > out(const vector<vector<float> >& matrix,
                           const vector<vector<float> >& rotation_mat);
};

#endif

