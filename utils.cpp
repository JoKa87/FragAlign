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

#include "utils.h"

    vector<vector<float> >& Utils::add(vector<vector<float> >& matrix1, const vector<vector<float> >& matrix2)
    {
        for(size_t i = 0; i < matrix1.size(); i++)
        {
            for(size_t j = 0; j < matrix1[0].size(); j++)
            {matrix1[i][j] += matrix2[i][j];}
        }

    return matrix1;
    }

    vector<vector<float> >& Utils::divide(vector<vector<float> >& matrix1, const float& divisor)
    {
        for(size_t i = 0; i < matrix1.size(); i++)
        {
            for(size_t j = 0; j < matrix1[0].size(); j++)
            {matrix1[i][j] /= divisor;}
        }

    return matrix1;
    }

    float Utils::get_avg(const vector<float>& values)
    {
    float avg = 0;

        for(size_t i = 0; i < values.size(); i++)
        {avg += values[i];}

        if(values.size() > 0)
        {avg /= (float) values.size();}

    return avg;
    }

    string Utils::get_name_from_path(const string& path)
    {
    string filename;
    string teststr;
    size_t i = 0;
        do
        {
        string testletter = path.substr(i, 1);

            if(testletter.compare("\\") != 0)
            {teststr += testletter;}

            if(testletter.compare("\\") == 0)
            {teststr = "";}

        i++;
        } while(i < path.size());

    return teststr;
    }

    long long int Utils::get_time()
    {
    const auto now = chrono::system_clock::now();
    const auto nowAsTimeT = chrono::system_clock::to_time_t(now);
    const auto nowMs = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch());
    stringstream nowSs;
    nowSs << nowMs.count();
    string nowMs_str = nowSs.str();
    return atoll(nowMs_str.c_str());
    }

    void Utils::get_performance(const long long int& time1, const long long int& time2,
                                const int& verbosity, const string& message)
    {
        if(verbosity == 1)
        {cout << "< time elapsed for " << message << " " << time2-time1 << " ms." << endl;}
    }

    vector<vector<float> > Utils::transpose(const vector<vector<float> >& matrix)
    {
    vector<vector<float> > out (matrix[0].size(), (vector<float> (matrix.size(), 0)));

        for(size_t i = 0; i < matrix.size(); i++)
        {
            for(size_t j = 0; j < matrix[0].size(); j++)
            {out[j][i] = matrix[i][j];}
        }

    return out;
    }

    float Utils::get_var(const vector<float>& values, const float& avg)
    {
    float var = 0;

        for(size_t i = 0; i < values.size(); i++)
        {var += pow((avg-values[i]),2);}

    return var;
    }

    vector<size_t> Utils::get_sorted_indices(const Params& params, vector<float> values)
    {
    vector<size_t> sorted_indices;

        for(size_t i = 0; i < values.size(); i++)
        {sorted_indices.push_back(i);}

        for(size_t i = 0; i < values.size(); i++)
        {
            for(size_t j = 0; j < values.size()-1; j++)
            {
            float value1 = values[values.size()-1-j];
            float value2 = values[values.size()-2-j];
            size_t index1 = sorted_indices[sorted_indices.size()-1-j];
            size_t index2 = sorted_indices[sorted_indices.size()-2-j];

                if(value1 < value2)
                {values[values.size()-1-j] = value2;
                values[values.size()-2-j] = value1;
                sorted_indices[sorted_indices.size()-1-j] = index2;
                sorted_indices[sorted_indices.size()-2-j] = index1;}
            }
        }

        //for(size_t i = 0; i < sorted_indices.size(); i++)
        //{cout << sorted_indices[i] << " " << values[i] << endl;}

    return sorted_indices;
    }
