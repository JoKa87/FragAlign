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

#include "cross_product.h"
#include "multiply.h"
#include "rotate_by_angles.h"
#include "rotate_by_axis.h"
#include "rotate_by_box.h"
#include "shift.h"

using namespace std;

    float deg(float rad)
    {rad = (rad/3.1415926) * 180;
    return rad;}

    vector<float> sort_coordinates (const vector<vector<vector<float> > >& align_boxes,
                                    const vector<vector<float> >& matrix, const size_t& it)
    {
    vector<float> box_coords;
    float coord1 = 0;
    float coord2 = 0;
    float coord3 = 0;
    float sum = 0;

        for(size_t i = 0; i < matrix.size(); i++)
        {
            if(matrix[i][0] >= align_boxes[it][0][0] && matrix[i][1] >= align_boxes[it][1][0] && matrix[i][2] <= align_boxes[it][2][0]
                && matrix[i][0] <= align_boxes[it][0][1] && matrix[i][1] >= align_boxes[it][1][1] && matrix[i][2] <= align_boxes[it][2][1]
                && matrix[i][0] <= align_boxes[it][0][2] && matrix[i][1] <= align_boxes[it][1][2] && matrix[i][2] <= align_boxes[it][2][2]
                && matrix[i][0] >= align_boxes[it][0][3] && matrix[i][1] <= align_boxes[it][1][3] && matrix[i][2] <= align_boxes[it][2][3]
                && matrix[i][0] >= align_boxes[it][0][4] && matrix[i][1] >= align_boxes[it][1][4] && matrix[i][2] >= align_boxes[it][2][4]
                && matrix[i][0] <= align_boxes[it][0][5] && matrix[i][1] >= align_boxes[it][1][5] && matrix[i][2] >= align_boxes[it][2][5]
                && matrix[i][0] <= align_boxes[it][0][6] && matrix[i][1] <= align_boxes[it][1][6] && matrix[i][2] >= align_boxes[it][2][6]
                && matrix[i][0] >= align_boxes[it][0][7] && matrix[i][1] <= align_boxes[it][1][7] && matrix[i][2] >= align_boxes[it][2][7])
            {coord1 += matrix[i][0];
            coord2 += matrix[i][1];
            coord3 += matrix[i][2];
            sum++;}
        }

        if(sum > 0)
        {box_coords.push_back(coord1 / sum);
        box_coords.push_back(coord2 / sum);
        box_coords.push_back(coord3 / sum);}

    return box_coords;
    }

    vector<vector<float> > Rotate_by_box::out(vector<vector<float> >& matrix1, vector<vector<float> >& matrix2,
                                              vector<vector<float> >& param_history,
                                              const vector<vector<vector<float> > >& align_boxes,
                                              const size_t& it)
    {
    Cross_product cross_product; Multiply multiply; Rotate_by_angles rotate_by_angles;
    Rotate_by_axis rotate_by_axis; Shift shift;
    vector<vector<float> > rotation_matrix_ccw (3, (vector<float> (3, 0)));
    vector<vector<float> > rotation_matrix_clw (3, (vector<float> (3, 0)));

    vector<vector<float> > rotated_matrix = matrix2;
    vector<vector<float> > box_coords;
    vector<float> avg_coords (3, 0);
    size_t coords_sum = 0;

        //*mode 1: shift calculation
        //*mode 2: rotation calculation
        for(size_t mode = 0; mode < 2; mode++)
        {
            for(size_t i = 0; i < align_boxes.size(); i++)
            {
            box_coords.clear();
            box_coords.push_back(sort_coordinates(align_boxes, matrix1, i));
            box_coords.push_back(sort_coordinates(align_boxes, rotated_matrix, i));

                if(box_coords[0].size() == 3 && box_coords[1].size() == 3)
                {
                float x1 = box_coords[0][0];
                float x2 = box_coords[0][1];
                float x3 = box_coords[0][2];
                float y1 = box_coords[1][0];
                float y2 = box_coords[1][1];
                float y3 = box_coords[1][2];
                vector<vector<float> > box_coords_ext {box_coords[1]};

                    if(mode == 0)
                    {avg_coords[0] += y1-x1;
                    avg_coords[1] += y2-x2;
                    avg_coords[2] += y3-x3;
                    coords_sum++;}

                    if(mode == 1
                        && sqrt((pow(x1,2) + pow(x2,2) + pow(x3,2)))*sqrt((pow(y1,2) + pow(y2,2) + pow(y3,2))) != 0
                        && (x1*y1+x2*y2+x3*y3) / (sqrt((pow(x1,2) + pow(x2,2) + pow(x3,2)))*sqrt((pow(y1,2) + pow(y2,2) + pow(y3,2)))) <= 1
                        && (x1*y1+x2*y2+x3*y3) / (sqrt((pow(x1,2) + pow(x2,2) + pow(x3,2)))*sqrt((pow(y1,2) + pow(y2,2) + pow(y3,2)))) >= -1)
                    {
                    //*determine rotational axis
                    float angle = acos((x1*y1+x2*y2+x3*y3) / (sqrt((pow(x1,2) + pow(x2,2) + pow(x3,2)))*sqrt((pow(y1,2) + pow(y2,2) + pow(y3,2)))));
                    vector<float> rot_ax = cross_product.out(box_coords[0], box_coords[1]);

                    //*create rotation matrix for clockwise and counter-clockwise rotation
                    rotation_matrix_ccw = rotate_by_axis.out(rotation_matrix_ccw, rot_ax, deg(angle), false);
                    rotation_matrix_clw = rotate_by_axis.out(rotation_matrix_clw, rot_ax, -deg(angle), false); //radians(360)

                    //*conduct matrix multiplication for clockwise and counter-clockwise rotation
                    vector<vector<float> > rotated_matrix_ccw = multiply.out(box_coords_ext, rotation_matrix_ccw);
                    vector<vector<float> > rotated_matrix_clw = multiply.out(box_coords_ext, rotation_matrix_clw);

                    //*compare distances and choose lowest
                    float dist_ccw = sqrt(pow((rotated_matrix_ccw[0][0]-x1),2)
                                          + pow((rotated_matrix_ccw[0][1]-x2),2)
                                          + pow((rotated_matrix_ccw[0][2]-x3),2));

                    float dist_clw = sqrt(pow((rotated_matrix_clw[0][0]-x1),2)
                                          + pow((rotated_matrix_clw[0][1]-x2),2)
                                          + pow((rotated_matrix_clw[0][2]-x3),2));

                        if(dist_ccw <= dist_clw)
                        {rotated_matrix = multiply.out(rotated_matrix, rotation_matrix_ccw);
                        param_history[(int) param_history[0][0]+1][0] = 2;
                        param_history[(int) param_history[0][0]+1][1] = deg(angle);
                        param_history[(int) param_history[0][0]+1][2] = rot_ax[0];
                        param_history[(int) param_history[0][0]+1][3] = rot_ax[1];
                        param_history[(int) param_history[0][0]+1][4] = rot_ax[2];
                        param_history[0][0]++;}

                        if(dist_ccw > dist_clw)
                        {rotated_matrix = multiply.out(rotated_matrix, rotation_matrix_clw);
                        param_history[(int) param_history[0][0]+1][0] = 2;
                        param_history[(int) param_history[0][0]+1][1] = -deg(angle);
                        param_history[(int) param_history[0][0]+1][2] = rot_ax[0];
                        param_history[(int) param_history[0][0]+1][3] = rot_ax[1];
                        param_history[(int) param_history[0][0]+1][4] = rot_ax[2];
                        param_history[0][0]++;}
                    }
                }
            }

            if(mode == 0)
            {avg_coords[0] /= (float) coords_sum;
            avg_coords[1] /= (float) coords_sum;
            avg_coords[2] /= (float) coords_sum;
            rotated_matrix = shift.out(rotated_matrix, param_history, avg_coords, false, true);}
        }

    return rotated_matrix;
    }
