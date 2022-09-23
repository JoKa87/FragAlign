#include "cross_product.h"

    vector<float> Cross_product::out(const vector<float>& vector1, const vector<float>& vector2)
    {
    vector<float> out (3, 0);
    out[0] = (vector1[1]*vector2[2])-(vector1[2]*vector2[1]);
    out[1] = (vector1[2]*vector2[0])-(vector1[0]*vector2[2]);
    out[2] = (vector1[0]*vector2[1])-(vector1[1]*vector2[0]);
    return out;
    }
