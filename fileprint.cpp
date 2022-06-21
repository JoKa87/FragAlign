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

using namespace std;

    template<class T> string to_string(const T& input)
    {
	stringstream inputstream;
	inputstream << input;
	return inputstream.str();
    }

    string get_spaces(const string& input, const size_t& max_spaces)
    {
    string spaces;
    //cout << "max_spaces " << max_spaces << " " << input.size() << " " << input << endl;

		for(size_t i = 0; i < max_spaces-input.size(); i++)
        {spaces += " ";}

    return spaces;
    }

    string get_round(const string& value, const size_t& digits)
    {
    string valuestr = to_string(value);
    string teststr = "";
    string testletter = "";
    size_t i = 0;
    size_t dotcheck = 0;
    size_t digitcount = 0;

        do
        {
        string testletter = valuestr.substr(i, 1);

            if(dotcheck == 0 || (dotcheck == 1 && digitcount < digits))
            {teststr += testletter;}

            if(dotcheck == 1)
            {digitcount++;}

            if(testletter.compare(".") == 0)
            {dotcheck = 1;}
        i++;
        } while(i < valuestr.size());

    return teststr;
    }

    void print(const Pdbstruct& pdbstruct, const Params& params, const string& tag,
               const size_t& fraction1, const size_t& fraction2, const bool& use_indices)
    {
    ofstream outfile;
    string outfilename;

        if(use_indices == false)
        {outfilename = tag + "_aligned" + ".pdb";}

        if(use_indices == true)
        {outfilename = tag + "_aligned_" + to_string(fraction1) + "-" + to_string(fraction2) + ".pdb";}

    outfile.open(params.run_dir+"\\"+outfilename.c_str());

        for(size_t i = 0; i < pdbstruct.catvec.size(); i++)
        {outfile << pdbstruct.catvec[i] << get_spaces(to_string(pdbstruct.idvec[i]), 11-pdbstruct.catvec[i].size());
        outfile << pdbstruct.idvec[i] << get_spaces(to_string(pdbstruct.atmvec[i]), 5);
        outfile << pdbstruct.atmvec[i] << get_spaces(to_string(pdbstruct.resnvec[i]), 4);
        outfile << pdbstruct.resnvec[i] << get_spaces(to_string(pdbstruct.chnvec[i]), 2);
        outfile << pdbstruct.chnvec[i] << get_spaces(to_string(pdbstruct.residvec[i]), 4);
        outfile << pdbstruct.residvec[i];
        outfile << get_spaces(get_round(to_string(pdbstruct.xvec[i]), 3), 12).c_str();
        outfile << get_round(to_string(pdbstruct.xvec[i]), 3);
        outfile << get_spaces(get_round(to_string(pdbstruct.yvec[i]), 3), 8).c_str();
        outfile << get_round(to_string(pdbstruct.yvec[i]), 3); //cout << get_spaces(to_string(pdbstruct.yvec[poscount]), 8) << "!" << endl;
        outfile << get_spaces(get_round(to_string(pdbstruct.zvec[i]), 3), 8).c_str();
        outfile << get_round(to_string(pdbstruct.zvec[i]), 3);
        outfile << get_spaces(to_string(1), 23) << pdbstruct.atmvec[i][0] << endl;}

    outfile.close();
    }

    void Fileprint::out(const Pdbstruct& pdbstruct1, const Pdbstruct& pdbstruct2, const Params& params,
                        const size_t& fraction1, const size_t& fraction2, const bool& use_indices)
    {
    print(pdbstruct1, params, pdbstruct1.pdb + "_" + pdbstruct2.pdb, fraction1, fraction2, use_indices);
    print(pdbstruct2, params, pdbstruct2.pdb + "_" + pdbstruct1.pdb, fraction1, fraction2, use_indices);
    return;
    }

