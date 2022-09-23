#ifndef ROTATE_BY_BOX_H
#define ROTATE_BY_BOX_H

#include "cross_product.h"
#include "multiply.h"
#include "rotate_by_angles.h"
#include "rotate_by_axis.h"
#include "shift.h"

using namespace std;

class Rotate_by_box
{
public:
vector<vector<float> > out(vector<vector<float> >& matrix1, vector<vector<float> >& matrix2,
                           vector<vector<float> >& param_history,
                           const vector<vector<vector<float> > >& align_boxes,
                           const size_t& it);
};

#endif


