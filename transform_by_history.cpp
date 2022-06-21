#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <algorithm>
#include <windows.h>
#include <tlhelp32.h>
#include <bits/stdc++.h>
#include <ctime>

#include "multiply.h"
#include "rotate_by_axis.h"
#include "shift.h"
#include "transform_by_history.h"

using namespace std;

    float _deg_(float rad)
    {rad = (rad/3.1415926) * 180;
    return rad;}

    vector<vector<float> >& Transform_by_history::out(vector<vector<float> >& matrix,
                                                      vector<vector<float> >& param_history)
    {
    Multiply multiply; Rotate_by_axis rotate_by_axis; Shift shift;
    vector<vector<float> > rotation_matrix (3, (vector<float> (3, 0)));
    //cout << "sizes " << param_history.size() << endl;

        for(size_t i = 1; i < param_history[0][0]; i++)
        {
        //cout << "i " << i << " " << param_history[i][0] << " " << param_history[i][1];
        //cout << " " << param_history[i][2] << " " << param_history[i][3] << endl;
            if(param_history[i][0] == 1)
            {
            matrix = shift.out(matrix, param_history,
                               {param_history[i][1], param_history[i][2], param_history[i][3]},
                               true, false);
            }

            if(param_history[i][0] == 2 || param_history[i][0] == 3)
            {
            vector<float> rot_ax {param_history[i][2], param_history[i][3], param_history[i][4]};
            rotation_matrix = rotate_by_axis.out(rotation_matrix, rot_ax,
                                                 param_history[i][1], false);
            matrix = multiply.out(matrix, rotation_matrix);
            }
        }

    return matrix;
    }
