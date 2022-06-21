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

#include "rotate_by_axis.h"

    vector<vector<float> >& Rotate_by_axis::out(vector<vector<float> >& rotation_mat, const vector<float>& axis, float angle, const bool& verbosity)
    {
    vector<float> unit_axis (3, 0);

        if(sqrt(pow(axis[0],2)+pow(axis[1],2)+pow(axis[2],2)) > 0)
        {unit_axis[0] = axis[0]/sqrt(pow(axis[0],2)+pow(axis[1],2)+pow(axis[2],2));
        unit_axis[1] = axis[1]/sqrt(pow(axis[0],2)+pow(axis[1],2)+pow(axis[2],2));
        unit_axis[2] = axis[2]/sqrt(pow(axis[0],2)+pow(axis[1],2)+pow(axis[2],2));}

    angle *= 3.1415926 / 180;
    if(verbosity == true)
    {cout <<"ax " << unit_axis[0] << " " << unit_axis[1] << " " << unit_axis[2];
    cout << " " << sqrt(pow(unit_axis[0],2)+pow(unit_axis[1],2)+pow(unit_axis[2],2));
    cout << " angle " << angle << " " << rotation_mat.size() << " " << rotation_mat[0].size() << endl;}

    rotation_mat[0][0] = pow(unit_axis[0],2)*(1-cos(angle))+cos(angle);
    rotation_mat[0][1] = unit_axis[1]*unit_axis[0]*(1-cos(angle))+unit_axis[2]*sin(angle);
    rotation_mat[0][2] = unit_axis[2]*unit_axis[0]*(1-cos(angle))-unit_axis[1]*sin(angle);

    rotation_mat[1][0] = unit_axis[0]*unit_axis[1]*(1-cos(angle))-unit_axis[2]*sin(angle);
    rotation_mat[1][1] = pow(unit_axis[1],2)*(1-cos(angle))+cos(angle);
    rotation_mat[1][2] = unit_axis[2]*unit_axis[1]*(1-cos(angle))+unit_axis[0]*sin(angle);

    rotation_mat[2][0] = unit_axis[0]*unit_axis[2]*(1-cos(angle))+unit_axis[1]*sin(angle);
    rotation_mat[2][1] = unit_axis[1]*unit_axis[2]*(1-cos(angle))-unit_axis[0]*sin(angle);
    rotation_mat[2][2] = pow(unit_axis[2],2)*(1-cos(angle))+cos(angle);
    return rotation_mat;
    }
