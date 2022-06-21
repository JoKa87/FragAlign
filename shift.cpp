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

#include "shift.h"

    vector<vector<float> >& Shift::out(vector<vector<float> >& matrix,
                                       vector<vector<float> >& param_history,
                                       const vector<float>& shift_vector,
                                       const bool& additive,
                                       const bool& write_history)
    {
        //*shift by subtraction of averages
        if(additive == false)
        {
        vector<float> avgs (3, 0);

            for(size_t i = 0; i < matrix[0].size(); i++)
            {
                for(size_t j = 0; j < matrix.size(); j++)
                {avgs[i] += matrix[j][i];}
            }

            for(size_t i = 0; i < matrix[0].size(); i++)
            {avgs[i] /= (float) matrix.size();}

            for(size_t i = 0; i < matrix[0].size(); i++)
            {
                for(size_t j = 0; j < matrix.size(); j++)
                {matrix[j][i] = matrix[j][i] + shift_vector[i] - avgs[i];}
            }

            //*collect transformation history for later reconstruction of whole structure
            if(write_history == true)
            {
            param_history[(int) param_history[0][0]+1][0] = 1;

                for(size_t i = 0; i < matrix[0].size(); i++)
                {param_history[(int) param_history[0][0]+1][i+1] = shift_vector[i] - avgs[i];}

            param_history[0][0]++;
            }
        }

        //*add specified shift vector
        if(additive == true)
        {
            for(size_t i = 0; i < matrix[0].size(); i++)
            {
                for(size_t j = 0; j < matrix.size(); j++)
                {matrix[j][i] = matrix[j][i] + shift_vector[i];}
            }

            //*collect transformation history for later reconstruction of whole structure
            if(write_history == true)
            {
            param_history[(int) param_history[0][0]+1][0] = 1;

                for(size_t i = 0; i < matrix[0].size(); i++)
                {param_history[(int) param_history[0][0]+1][i+1] = shift_vector[i];}

            param_history[0][0]++;
            }
        }

    return matrix;
    }
