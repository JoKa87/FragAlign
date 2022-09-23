#ifndef UTILS_H
#define UTILS_H
#include <algorithm>
#include <bits/stdc++.h>
#include <ctime>
#include <iostream>
#include <sstream>

#include "params.h"

using namespace std;

class Utils
{
public:
vector<vector<float> >& add(vector<vector<float> >& matrix1, const vector<vector<float> >& matrix2);
vector<vector<float> >& divide(vector<vector<float> >& matrix1, const float& divisor);
float get_avg(const vector<float>& values);
string get_name_from_path(const string& path);
long long int get_time();
void get_performance(const long long int& time1, const long long int& time2,
                     const int& verbosity = 0, const string& message = "");
vector<size_t> get_sorted_indices(const Params& params, vector<float> values);
float get_var(const vector<float>& values, const float& avg);
template<class T> string to_string(const T& input);
vector<vector<float> > transpose(const vector<vector<float> >& matrix);
};

template<class T> string Utils::to_string(const T& input)
{
stringstream inputstream;
inputstream << input;
return inputstream.str();
}

#endif
