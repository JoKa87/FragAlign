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

#include "substitution.h"

using namespace std;

    //*read substitution matrices and normalize (values between 0 and 1)
    vector<vector<float> > Substitution::out(const Params& params)
    {
    vector<vector<float> > substitution_mat;

        //*initialize matrix
        if(params.matrix.compare("ID") == 0)
        {
        substitution_mat = vector<vector<float> > (20, (vector<float> (20, 0)));

            for(size_t i = 0; i < substitution_mat.size(); i++)
            {substitution_mat[i][i] = 1;}
        }

        if(params.matrix.compare("PAM250") == 0 || params.matrix.compare("BLOSUM62") == 0)
        {
        substitution_mat = vector<vector<float> > (20, (vector<float> (20, -1)));
        string filepath;

            if(params.matrix.compare("PAM250") == 0)
            {filepath = params.run_dir+"\\substitution_matrix\\PAM250.txt";}

            if(params.matrix.compare("BLOSUM62") == 0)
            {filepath = params.run_dir+"\\substitution_matrix\\BLOSUM62.txt";}

        ifstream file;
        file.open(filepath.c_str());
        string line;
        size_t rowcount = 0;
        float maxvalue, minvalue;

            while(getline(file, line))
            {
            size_t spacecount = 0;
            size_t gapcheck = 0;
            string teststr = "";

                if(rowcount > 0)
                {
                    for(size_t i = 0; i < line.size(); i++)
                    {
                    string testletter = line.substr(i, 1);

                        if(testletter.compare(" ") != 0)
                        {teststr += testletter;}

                        if(testletter.compare(" ") == 0 || i == line.size()-1)
                        {spacecount++;
                        gapcheck = 1;}

                        if(gapcheck == 1 && spacecount > 1)
                        {
                        float testfloat = atof(teststr.c_str());
                        substitution_mat[rowcount-1][spacecount-2] = testfloat;
                        substitution_mat[spacecount-2][rowcount-1] = testfloat;
                        gapcheck = 0; teststr = "";

                            if(rowcount == 1 || testfloat < minvalue)
                            {minvalue = testfloat;}

                            if(rowcount == 1 || testfloat > maxvalue)
                            {maxvalue = testfloat;}
                        }

                        if(testletter.compare(" ") == 0 || i == line.size()-1)
                        {teststr = "";}
                    }
                }

            rowcount++;
            }

            if(!file.is_open())
            {cout << "< error occurred during reading of substitution matrices." << endl;
            cout << endl;}

            //*normalize substitution matrix
            for(size_t i = 0; i < substitution_mat.size(); i++)
            {
                for(size_t j = 0; j < substitution_mat[i].size(); j++)
                {substitution_mat[i][j] = (substitution_mat[i][j]-minvalue)/(maxvalue-minvalue);}
            }
        }

    return substitution_mat;
    }
