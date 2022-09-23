#include "rotate_by_angles.h"


    vector<vector<float> > Rotate_by_angles::out(vector<float>& angles)
    {
    vector<vector<float> > rotation_mat (3, (vector<float> (3, 0)));

        for(size_t i = 0; i < angles.size(); i++)
        {angles[i] *= 3.1415926 / 180;}

    rotation_mat[0][0] = cos(angles[0])*cos(angles[1]);
    rotation_mat[0][1] = sin(angles[0])*cos(angles[1]);
    rotation_mat[0][2] = -sin(angles[1]);
    rotation_mat[1][0] = cos(angles[0])*sin(angles[1])*sin(angles[2])-sin(angles[0])*cos(angles[2]);
    rotation_mat[1][1] = sin(angles[0])*sin(angles[1])*sin(angles[2])+cos(angles[0])*cos(angles[2]);
    rotation_mat[1][2] = cos(angles[1])*sin(angles[2]);
    rotation_mat[2][0] = cos(angles[0])*sin(angles[1])*cos(angles[2])+sin(angles[0])*sin(angles[2]);
    rotation_mat[2][1] = sin(angles[0])*sin(angles[1])*cos(angles[2])-cos(angles[0])*sin(angles[2]);
    rotation_mat[2][2] = cos(angles[1])*cos(angles[2]);
    return rotation_mat;
    }
