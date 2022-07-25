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

#include "fileprint.h"
#include "utils.h"

using namespace std;


    static string get_spaces(const string& input, const size_t& max_spaces)
    {
    string spaces;

	for(size_t i = 0; i < max_spaces-input.size(); i++)
        {spaces += " ";}

    return spaces;
    }


    static string get_round(const string& value, const size_t& digits)
    {
    string teststr = "";
    string testletter = "";
    size_t i = 0;
    bool dot = false;
    size_t digitcount = 0;

        do
        {
        string testletter = value.substr(i, 1);

            if(dot == false || (dot == true && digitcount < digits))
            {teststr += testletter;}

            if(dot == true)
            {digitcount++;}

            if(testletter.compare(".") == 0)
            {dot = true;}
        i++;
        } while(i < value.size());

    return teststr;
    }


    static void print(const Pdbstruct& pdbstruct, const Params& params, const string& tag,
               const size_t& fraction1, const size_t& fraction2, const bool& use_indices)
    {
    Utils utils;
    ofstream outfile;
    string outfilename;

        if(use_indices == false)
        {outfilename = tag + "_aligned" + ".pdb";}

        if(use_indices == true)
        {outfilename = tag + "_aligned_" + utils.to_string(fraction1) + "-" + utils.to_string(fraction2) + ".pdb";}

    outfile.open(params.run_dir+"\\"+outfilename.c_str());

        for(size_t i = 0; i < pdbstruct.catvec.size(); i++)
        {outfile << pdbstruct.catvec[i] << get_spaces(utils.to_string(pdbstruct.idvec[i]), 11-pdbstruct.catvec[i].size());
        outfile << pdbstruct.idvec[i] << get_spaces(utils.to_string(pdbstruct.atmvec[i]), 5);
        outfile << pdbstruct.atmvec[i] << get_spaces(utils.to_string(pdbstruct.resnvec[i]), 4);
        outfile << pdbstruct.resnvec[i] << get_spaces(utils.to_string(pdbstruct.chnvec[i]), 2);
        outfile << pdbstruct.chnvec[i] << get_spaces(utils.to_string(pdbstruct.residvec[i]), 4);
        outfile << pdbstruct.residvec[i];
        outfile << get_spaces(get_round(utils.to_string(pdbstruct.xvec[i]), 3), 12).c_str();
        outfile << get_round(utils.to_string(pdbstruct.xvec[i]), 3);
        outfile << get_spaces(get_round(utils.to_string(pdbstruct.yvec[i]), 3), 8).c_str();
        outfile << get_round(utils.to_string(pdbstruct.yvec[i]), 3);
        outfile << get_spaces(get_round(utils.to_string(pdbstruct.zvec[i]), 3), 8).c_str();
        outfile << get_round(utils.to_string(pdbstruct.zvec[i]), 3);
        outfile << get_spaces(utils.to_string(1), 23) << pdbstruct.atmvec[i][0] << endl;}

    outfile.close();
    }


    void Fileprint::out(const Pdbstruct& pdbstruct1, const Pdbstruct& pdbstruct2, const Params& params,
                        const size_t& fraction1, const size_t& fraction2, const bool& use_indices)
    {
    print(pdbstruct1, params, pdbstruct1.pdb + "_" + pdbstruct2.pdb, fraction1, fraction2, use_indices);
    print(pdbstruct2, params, pdbstruct2.pdb + "_" + pdbstruct1.pdb, fraction1, fraction2, use_indices);
    return;
    }

