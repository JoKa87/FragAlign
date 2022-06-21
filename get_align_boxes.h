#ifndef GET_ALIGN_BOXES_H
#define GET_ALIGN_BOXES_H
#include <vector>

using namespace std;

class Get_align_boxes
{
public:
vector<vector<vector<vector<float> > > > out(const vector<vector<float> >& matrix1,
                                             const vector<vector<float> >& matrix2);
};

#endif

