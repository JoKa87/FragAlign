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

#include "logprint.h"

using namespace std;

    void Logprint::out(const vector<float>& lognumbers, const string& logstr, const Params& params, const bool& init)
    {
        if(init == true)
        {
        ofstream logfile;
        logfile.open((params.run_dir + "\\" + "log.txt").c_str());
        logfile << "> new log is initialized." << endl;
        logfile.close();
        }

        if(init == false)
        {
        ifstream in_logfile;
        in_logfile.open((params.run_dir + "\\" + "log.txt").c_str());
        vector<string> lines;
        string line;

            while(getline(in_logfile, line))
            {lines.push_back(line);}

        in_logfile.close();

        ofstream out_logfile;
        out_logfile.open((params.run_dir + "\\" + "log.txt").c_str());

            for(size_t i = 0; i < lines.size(); i++)
            {out_logfile << lines[i] << endl;}

            for(size_t i = 0; i < lognumbers.size(); i++)
            {out_logfile << lognumbers[i] << " ";}

        out_logfile << endl;
        out_logfile << logstr << endl;
        out_logfile.close();
        }

    return;
    }

