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

#include "get_align_boxes.h"

using namespace std;

    vector<vector<vector<float> > > get_half_by_y(const vector<vector<vector<float> > >& full_box, const float& maxdist)
    {
    vector<vector<vector<float> > > half_by_y (2, (vector<vector<float> > (3, (vector<float> (8, 0)))));
    vector<float> startcoords = {full_box[0][0][0], full_box[0][1][0], full_box[0][2][0]};

        for(size_t i = 0; i < 2; i++)
        {
            if(i == 1)
            {startcoords = {full_box[0][0][0], full_box[0][1][0]+maxdist, full_box[0][2][0]};}

        half_by_y[i][0][0] = startcoords[0];
        half_by_y[i][1][0] = startcoords[1];
        half_by_y[i][2][0] = startcoords[2];
        half_by_y[i][0][1] = startcoords[0]+2*maxdist;
        half_by_y[i][1][1] = startcoords[1];
        half_by_y[i][2][1] = startcoords[2];
        half_by_y[i][0][2] = startcoords[0]+2*maxdist;
        half_by_y[i][1][2] = startcoords[1]+maxdist;
        half_by_y[i][2][2] = startcoords[2];
        half_by_y[i][0][3] = startcoords[0];
        half_by_y[i][1][3] = startcoords[1]+maxdist;
        half_by_y[i][2][3] = startcoords[2];
        half_by_y[i][0][4] = startcoords[0];
        half_by_y[i][1][4] = startcoords[1];
        half_by_y[i][2][4] = startcoords[2]-2*maxdist;
        half_by_y[i][0][5] = startcoords[0]+2*maxdist;
        half_by_y[i][1][5] = startcoords[1];
        half_by_y[i][2][5] = startcoords[2]-2*maxdist;
        half_by_y[i][0][6] = startcoords[0]+2*maxdist;
        half_by_y[i][1][6] = startcoords[1]+maxdist;
        half_by_y[i][2][6] = startcoords[2]-2*maxdist;
        half_by_y[i][0][7] = startcoords[0];
        half_by_y[i][1][7] = startcoords[1]+maxdist;
        half_by_y[i][2][7] = startcoords[2]-2*maxdist;
        }

    return half_by_y;
    }

    vector<vector<vector<float> > > get_half_by_x(const vector<vector<vector<float> > >& full_box, const float& maxdist)
    {
    vector<vector<vector<float> > > half_by_x (2, (vector<vector<float> > (3, (vector<float> (8, 0)))));
    vector<float>  startcoords = {full_box[0][0][0], full_box[0][1][0], full_box[0][2][0]};
    //cout << full_box.size() << " " << full_box[0].size() << " " << full_box[0][0].size() << endl;

        for(size_t i = 0; i < 2; i++)
        {
            if(i == 1)
            {startcoords = {full_box[0][0][0]+maxdist, full_box[0][1][0], full_box[0][2][0]};}

        half_by_x[i][0][0] = startcoords[0];
        half_by_x[i][1][0] = startcoords[1];
        half_by_x[i][2][0] = startcoords[2];
        half_by_x[i][0][1] = startcoords[0]+maxdist;
        half_by_x[i][1][1] = startcoords[1];
        half_by_x[i][2][1] = startcoords[2];
        half_by_x[i][0][2] = startcoords[0]+maxdist;
        half_by_x[i][1][2] = startcoords[1]+2*maxdist;
        half_by_x[i][2][2] = startcoords[2];
        half_by_x[i][0][3] = startcoords[0];
        half_by_x[i][1][3] = startcoords[1]+2*maxdist;
        half_by_x[i][2][3] = startcoords[2];
        half_by_x[i][0][4] = startcoords[0];
        half_by_x[i][1][4] = startcoords[1];
        half_by_x[i][2][4] = startcoords[2]-2*maxdist;
        half_by_x[i][0][5] = startcoords[0]+maxdist;
        half_by_x[i][1][5] = startcoords[1];
        half_by_x[i][2][5] = startcoords[2]-2*maxdist;
        half_by_x[i][0][6] = startcoords[0]+maxdist;
        half_by_x[i][1][6] = startcoords[1]+2*maxdist;
        half_by_x[i][2][6] = startcoords[2]-2*maxdist;
        half_by_x[i][0][7] = startcoords[0];
        half_by_x[i][1][7] = startcoords[1]+2*maxdist;
        half_by_x[i][2][7] = startcoords[2]-2*maxdist;
        }

    return half_by_x;
    }

    vector<vector<vector<float> > > get_half_by_z(const vector<vector<vector<float> > >& full_box, const float& maxdist)
    {
    vector<vector<vector<float> > > half_by_z (2, (vector<vector<float> > (3, (vector<float> (8, 0)))));
    vector<float> startcoords = {full_box[0][0][0], full_box[0][1][0], full_box[0][2][0]};

        for(size_t i = 0; i < 2; i++)
        {
            if(i == 1)
            {startcoords = {full_box[0][0][0], full_box[0][1][0], full_box[0][2][0]-maxdist};}

        half_by_z[i][0][0] = startcoords[0];
        half_by_z[i][1][0] = startcoords[1];
        half_by_z[i][2][0] = startcoords[2];
        half_by_z[i][0][1] = startcoords[0]+2*maxdist;
        half_by_z[i][1][1] = startcoords[1];
        half_by_z[i][2][1] = startcoords[2];
        half_by_z[i][0][2] = startcoords[0]+2*maxdist;
        half_by_z[i][1][2] = startcoords[1]+2*maxdist;
        half_by_z[i][2][2] = startcoords[2];
        half_by_z[i][0][3] = startcoords[0];
        half_by_z[i][1][3] = startcoords[1]+2*maxdist;
        half_by_z[i][2][3] = startcoords[2];
        half_by_z[i][0][4] = startcoords[0];
        half_by_z[i][1][4] = startcoords[1];
        half_by_z[i][2][4] = startcoords[2]-maxdist;
        half_by_z[i][0][5] = startcoords[0]+2*maxdist;
        half_by_z[i][1][5] = startcoords[1];
        half_by_z[i][2][5] = startcoords[2]-maxdist;
        half_by_z[i][0][6] = startcoords[0]+2*maxdist;
        half_by_z[i][1][6] = startcoords[1]+2*maxdist;
        half_by_z[i][2][6] = startcoords[2]-maxdist;
        half_by_z[i][0][7] = startcoords[0];
        half_by_z[i][1][7] = startcoords[1]+2*maxdist;
        half_by_z[i][2][7] = startcoords[2]-maxdist;
        }

    return half_by_z;
    }

    vector<vector<vector<float> > > get_quadrants(const vector<vector<vector<float> > >& init_box, const float& maxdist)
    {
    vector<vector<vector<float> > > quadrants (8*init_box.size(), (vector<vector<float> > (3, (vector<float> (8, 0)))));

        for(size_t i = 0; i < init_box.size(); i++)
        {
        vector<float> startcoords = {init_box[i][0][0], init_box[i][1][0], init_box[i][2][0]};

            for(size_t j = 0; j < 8; j++)
            {
                if(j == 1)
                {startcoords[0] = init_box[i][0][1]-maxdist;
                startcoords[1] = init_box[i][1][1];
                startcoords[2] = init_box[i][2][1];}

                if(j == 2)
                {startcoords[0] = init_box[i][0][2]-maxdist;
                startcoords[1] = init_box[i][1][2]-maxdist;
                startcoords[2] = init_box[i][2][2];}

                if(j == 3)
                {startcoords[0] = init_box[i][0][3];
                startcoords[1] = init_box[i][1][3]-maxdist;
                startcoords[2] = init_box[i][2][3];}

                if(j == 4)
                {startcoords[0] = init_box[i][0][4];
                startcoords[1] = init_box[i][1][4];
                startcoords[2] = init_box[i][2][4]+maxdist;}

                if(j == 5)
                {startcoords[0] = init_box[i][0][5]-maxdist;
                startcoords[1] = init_box[i][1][5];
                startcoords[2] = init_box[i][2][5]+maxdist;}

                if(j == 6)
                {startcoords[0] = init_box[i][0][6]-maxdist;
                startcoords[1] = init_box[i][1][6]-maxdist;
                startcoords[2] = init_box[i][2][6]+maxdist;}

                if(j == 7)
                {startcoords[0] = init_box[i][0][7];
                startcoords[1] = init_box[i][1][7]-maxdist;
                startcoords[2] = init_box[i][2][7]+maxdist;}

            quadrants[4*i+j][0][0] = startcoords[0];
            quadrants[4*i+j][1][0] = startcoords[1];
            quadrants[4*i+j][2][0] = startcoords[2];
            quadrants[4*i+j][0][1] = startcoords[0]+maxdist;
            quadrants[4*i+j][1][1] = startcoords[1];
            quadrants[4*i+j][2][1] = startcoords[2];
            quadrants[4*i+j][0][2] = startcoords[0]+maxdist;
            quadrants[4*i+j][1][2] = startcoords[1]+maxdist;
            quadrants[4*i+j][2][2] = startcoords[2];
            quadrants[4*i+j][0][3] = startcoords[0];
            quadrants[4*i+j][1][3] = startcoords[1]+maxdist;
            quadrants[4*i+j][2][3] = startcoords[2];
            quadrants[4*i+j][0][4] = startcoords[0];
            quadrants[4*i+j][1][4] = startcoords[1];
            quadrants[4*i+j][2][4] = startcoords[2]-maxdist;
            quadrants[4*i+j][0][5] = startcoords[0]+maxdist;
            quadrants[4*i+j][1][5] = startcoords[1];
            quadrants[4*i+j][2][5] = startcoords[2]-maxdist;
            quadrants[4*i+j][0][6] = startcoords[0]+maxdist;
            quadrants[4*i+j][1][6] = startcoords[1]+maxdist;
            quadrants[4*i+j][2][6] = startcoords[2]-maxdist;
            quadrants[4*i+j][0][7] = startcoords[0];
            quadrants[4*i+j][1][7] = startcoords[1]+maxdist;
            quadrants[4*i+j][2][7] = startcoords[2]-maxdist;
            }
        }

    return quadrants;
    }

    //*calculate boxes (cuboid- or cube-shaped)
    vector<vector<vector<vector<float> > > > Get_align_boxes::out(const vector<vector<float> >& matrix1,
                                                                  const vector<vector<float> >& matrix2)
    {
    vector<vector<vector<vector<float> > > > align_boxes;
    float maxdist = 0;

        //*determine start cube (exceeds dimension to fit all data)
        for(size_t i = 0; i < matrix1.size(); i++)
        {
        float dist = sqrt(pow((matrix1[i][0]), 2) + pow((matrix1[i][1]), 2) + pow((matrix1[i][2]), 2));

            if(maxdist == 0 || maxdist < dist)
            {maxdist = 1.5*dist;}
        }

        for(size_t i = 0; i < matrix2.size(); i++)
        {
        float dist = sqrt(pow((matrix2[i][0]), 2) + pow((matrix2[i][1]), 2) + pow((matrix2[i][2]), 2));

            if(maxdist == 0 || maxdist < dist)
            {maxdist = 1.5*dist;}
        }

    float x1 = -maxdist; float x2 = maxdist; float x3 = maxdist; float x4 = -maxdist;
    float x5 = -maxdist; float x6 = maxdist; float x7 = maxdist; float x8 = -maxdist;
    float y1 = -maxdist; float y2 = -maxdist; float y3 = maxdist; float y4 = maxdist;
    float y5 = -maxdist; float y6 = -maxdist; float y7 = maxdist; float y8 = maxdist;
    float z1 = maxdist; float z2 = maxdist; float z3 = maxdist; float z4 = maxdist;
    float z5 = -maxdist; float z6 = -maxdist; float z7 = -maxdist; float z8 = -maxdist;

    //*calculate coordinates for initial box
    vector<vector<vector<float> > > init_box {{{x1, x2, x3, x4, x5, x6, x7, x8},
                                              {y1, y2, y3, y4, y5, y6, y7, y8},
                                              {z1, z2, z3, z4, z5, z6, z7, z8}}};

    //*divide initial box along the three axes
    align_boxes.push_back(get_half_by_x(init_box, maxdist));
    align_boxes.push_back(get_half_by_y(init_box, maxdist));
    align_boxes.push_back(get_half_by_z(init_box, maxdist));

    vector<vector<vector<float> > > new_box = init_box;

        //*divide initial box into progressively downsized cubes
        for(size_t i = 0; i < 3; i++)
        {new_box = get_quadrants(new_box, maxdist/(pow(2,i)));
        align_boxes.push_back(new_box);}

    return align_boxes;
    }
