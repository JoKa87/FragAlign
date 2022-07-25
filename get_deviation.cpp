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
#include "get_deviation.h"
#include "get_stats.h"
#include "load.h"
#include "multiply.h"
#include "rotate_by_angles.h"
#include "rotate_by_axis.h"
#include "rotate_by_box.h"
#include "rotate_by_pairs.h"
#include "shift.h"

    Deviation& Get_deviation::out(Deviation& deviation, const Params& params,
                                  const size_t& fraction1, const size_t& fraction2, const size_t& index)
    {
    //*definitions for sub-programs
    Get_align_boxes get_align_boxes; Get_stats get_stats;
    Multiply multiply; Rotate_by_angles rotate_by_angles;
    Rotate_by_axis rotate_by_axis; Rotate_by_box rotate_by_box;
    Rotate_by_pairs rotate_by_pairs; Shift shift;
    Data dummy1, dummy2; Stats stats;

    vector<vector<vector<vector<float> > > > align_boxes;
    vector<vector<float> > matrix2;
    vector<vector<float> > param_history1 (2, (vector<float> (5, 0)));
    vector<vector<float> > param_history2 (500, (vector<float> (5, 0)));
    float rmsd;

        //*section-wise transformations
        if(params.method1.compare("SECTION") == 0)
        {
        //*conduct initial translational shifts
        deviation.matrix1 = shift.out(deviation.matrix1, param_history1, {0, 0, 0}, false, true);

        deviation.best_matrix2 = shift.out(deviation.best_matrix2, param_history2, {0, 0, 0}, false, true);
        //*determine boxes for box-wise transformations
        //*box geometry is adapted to match matrix dimensions
        align_boxes = get_align_boxes.out(deviation.matrix1, deviation.best_matrix2);

        bool stopcheck = false, init = true;
        stats = get_stats.out(-1, params, dummy1, dummy2, deviation.matrix1, deviation.best_matrix2, 0, 0, params.rmsd_mode, -1);
        deviation.rmsd = stats.rmsd;
        size_t depth_stopcount = 0;
        size_t total_stopcount = 0;
        size_t box_it = 0;
        size_t i = 0;

            do
            {
            //*parameter history allows later transformation of whole structures
            size_t last_param_history_index = param_history2[0][0];
            //*conduct rotation and shift based on value distribution over boxes
            matrix2 = rotate_by_box.out(deviation.matrix1, deviation.best_matrix2, param_history2, align_boxes[box_it], 0);
            //*update RMSD as measure for alignment quality
            stats = get_stats.out(deviation.rmsd, params, dummy1, dummy2, deviation.matrix1, matrix2, 0, 0, params.rmsd_mode, -1);
            depth_stopcount++;

                //*delete entries from parameter history if updated RMSD is not lowest
                if(stats.rmsd >= deviation.rmsd && deviation.rmsd != -1)
                {
                    for(size_t j = last_param_history_index+1; j < param_history2[0][0]; j++)
                    {
                        for(size_t k = 0; k < param_history2[0].size(); k++)
                        {param_history2[j][k] = 0;}
                    }

                param_history2[0][0] = last_param_history_index;
                }

                //*overwrite indicators if updated RMSD is lowest
                if(stats.rmsd < deviation.rmsd || init == true)
                {deviation.rmsd = stats.rmsd;
                deviation.best_matrix2 = matrix2;
                deviation.best_param_history1 = param_history1;
                deviation.best_param_history2 = param_history2;
                total_stopcount = 0;
                init = false;}

                if(stats.rmsd / deviation.rmsd >= 1)
                {total_stopcount++;}

                if(depth_stopcount > params.max_depth_stopcount && box_it < align_boxes.size()-1)
                {box_it++;
                depth_stopcount = 0;}

                if(depth_stopcount > params.max_depth_stopcount && box_it == align_boxes.size()-1)
                {box_it = 0;
                depth_stopcount = 0;}

            i += params.boxwise_align_steps;
            } while(i < params.boxwise_align_it && total_stopcount < params.max_total_stopcount);
        }

        //*sequence-wise transformations
        if(params.method2.compare("PAIRWISE") == 0)
        {
            if(params.method1.compare("SECTION") != 0)
            {deviation.matrix1 = shift.out(deviation.matrix1, param_history1, {0, 0, 0}, false, true);
            deviation.best_matrix2 = shift.out(deviation.best_matrix2, param_history2, {0, 0, 0}, false, true);}

        bool stopcheck = false;
        size_t total_stopcount = 0;
        size_t i = 0;
            do
            {
            //*parameter history allows later transformation of whole structures
            size_t last_param_history_index = param_history2[0][0];
            //*conduct rotation based on value distribution by sequence comparison
            matrix2 = rotate_by_pairs.out(deviation.matrix1, deviation.best_matrix2, param_history2, params, i);
            //*update RMSD as measure for alignment quality
            stats = get_stats.out(deviation.rmsd, params, dummy1, dummy2, deviation.matrix1, matrix2, 0, 0, params.rmsd_mode, -1);

                //*delete entries from parameter history if updated RMSD is not lowest
                if(stats.rmsd >= deviation.rmsd && deviation.rmsd != -1)
                {
                    for(size_t j = last_param_history_index+1; j < param_history2[0][0]; j++)
                    {
                        for(size_t k = 0; k < param_history2[0].size(); k++)
                        {param_history2[j][k] = 0;}
                    }

                param_history2[0][0] = last_param_history_index;
                }

                if(param_history2[0][0] >= param_history2.size())
                {cout << "< warning. no. of maximum iterations is exceeded. program will crash. ";
                cout << "in order to proceed, reduce no. of iterations and run again." << endl;}

                //*overwrite indicators if updated RMSD is lowest
                if(stats.rmsd < deviation.rmsd || deviation.rmsd == -1)
                {deviation.rmsd = stats.rmsd;
                deviation.best_matrix2 = matrix2;
                deviation.best_param_history1 = param_history1;
                deviation.best_param_history2 = param_history2;
                total_stopcount = 0;}

                if(stats.rmsd / deviation.rmsd >= 1)
                {total_stopcount++;}

            i += params.seqwise_align_steps;
            } while(i < params.seqwise_align_it && i < matrix2.size() && total_stopcount < params.max_total_stopcount);
        }

    return deviation;
    }
