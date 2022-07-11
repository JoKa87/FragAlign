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

#include "convert_sequence.h"

    int resn_index_converter(const string& resn, const int& verbosity)
    {
    int aa_index = -1;
    vector<string> threelettercode {"ALA", "CYS", "ASP", "GLU", "PHE", "GLY", "HIS", "ILE",
                                    "LYS", "LEU", "MET", "ASN", "PRO", "GLN", "ARG", "SER",
                                    "THR", "VAL", "TRP", "TYR", "UNK"};
    size_t matchcheck = 0;

        for(size_t i = 0; i < threelettercode.size() && matchcheck == 0; i++)
        {
            if(threelettercode[i].compare(resn) == 0)
            {aa_index = i;
            matchcheck = 1;}
        }

        if(matchcheck == 0 && verbosity == 1)
        {cout << "< warning. unknown amino acid residue found with name " << resn << endl;}

    return aa_index;
    }

    vector<int> Convert_sequence::out(const Params& params, const vector<string>& sequence)
    {
    vector<int> converted_sequence;

        for(size_t i = 0; i < sequence.size(); i++)
        {converted_sequence.push_back(resn_index_converter(sequence[i], params.verbosity));}

    return converted_sequence;
    }
