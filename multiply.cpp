#include "multiply.h"


    vector<vector<float> > Multiply::out(const vector<vector<float> >& matrix,
                                          const vector<vector<float> >& rotation_mat)
    {
    vector<vector<float> > out (matrix.size(), vector<float> (matrix[0].size(), 0));

        for(size_t i = 0; i < rotation_mat[0].size(); i++)
        {
            for(size_t j = 0; j < matrix.size(); j++)
            {
                for(size_t k = 0; k < rotation_mat.size(); k++)
                {out[j][i] += rotation_mat[i][k]*matrix[j][k];}
            }
        }

    return out;
    }
