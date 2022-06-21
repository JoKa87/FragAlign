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
#include "repdetect.h"

using namespace std;

    //*detect local repetitions in PDB structure
    Repstruct Repdetect::out(const Pdbstruct& pdbstruct, const Params& params)
    {
    Repstruct repstruct;
    vector<vector<int> > localredidmat (2, (vector<int> (0, 0)));
    vector<vector<int> > localrepposmat (0, (vector<int> (0, 0)));

    //* identify local in-blocks repetitions
    size_t entrycheck = 0;
        for(size_t i = 1; i < pdbstruct.residNvec.size(); i++)
        {
            //* condition introduced to selectively account for in-block repetitions
            if(pdbstruct.residNvec[i]-pdbstruct.residNvec[i-1] == 0 && entrycheck == 0
                && pdbstruct.poscountNvec[i]-pdbstruct.poscountNvec[i-1] > 1
                && pdbstruct.chnvec[pdbstruct.poscountNvec[i]].compare(pdbstruct.chnvec[pdbstruct.poscountNvec[i-1]]) == 0)
            {localredidmat[0].push_back(pdbstruct.poscountNvec[i-1]);
            entrycheck = 1;}

            if((pdbstruct.residNvec[i] != pdbstruct.residNvec[i-1] || i == pdbstruct.residNvec.size()-1) && entrycheck == 1)
            {localredidmat[1].push_back(pdbstruct.poscountNvec[i]);
            entrycheck = 0;}
        }

        if(localredidmat[0].size() != localredidmat[1].size())
        {cout << "< error occurred during determination of local repetitions." << endl;}

        if(localredidmat[0].size() > 0 && params.verbosity == 1)
        {
        cout << "> local repetitions detected at the following positions:" << endl;

            for(size_t i = 0; i < localredidmat[0].size(); i++)
            {cout << pdbstruct.resnvec[localredidmat[0][i]] << " " << pdbstruct.residvec[localredidmat[0][i]];
            cout << "-" << pdbstruct.atmvec[localredidmat[0][i]] << endl;}
        cout << endl;
        }

    //* identify intertwined local repetitions (presumably more relevant!)
    //* example (taken from 3UG9):
    //* ATOM    587  CA APHE A 133      18.135  29.323  19.086  0.50 53.59           C
    //* ATOM    588  CA BPHE A 133      18.043  29.259  19.083  0.50 53.67           C

    size_t stepcount = 1;
        for(int i = 0; i < pdbstruct.atmvec.size()-1; i += stepcount)
        {
            if(pdbstruct.atmvec[i].compare(pdbstruct.atmvec[i+1]) == 0 && pdbstruct.residvec[i] == pdbstruct.residvec[i+1]
                && pdbstruct.chnvec[i].compare(pdbstruct.chnvec[i-1]) == 0
                && i+1 < pdbstruct.residvec.size())
            {
            vector<int> localreppostempvec (0, 0);
            localreppostempvec.push_back(pdbstruct.poscountvec[i]);
            int j = 1;
                do
                {
                    if(pdbstruct.atmvec[i].compare(pdbstruct.atmvec[i+j]) == 0 && pdbstruct.residvec[i] == pdbstruct.residvec[i+j]
                        && i+j < pdbstruct.residvec.size())
                    {localreppostempvec.push_back(pdbstruct.poscountvec[i+j]);}

                j++;
                } while(i+j < pdbstruct.atmvec.size()
                    && pdbstruct.atmvec[i].compare(pdbstruct.atmvec[i+j]) == 0
                    && pdbstruct.residvec[i] == pdbstruct.residvec[i+j]);

            localrepposmat.push_back(localreppostempvec);
            stepcount = j;
            }

            if(pdbstruct.atmvec[i].compare(pdbstruct.atmvec[i+1]) != 0 || pdbstruct.residvec[i] != pdbstruct.residvec[i+1]
                && i+1 < pdbstruct.residvec.size())
            {stepcount = 1;}
        }

        if(localrepposmat.size() > 0 && params.verbosity == 1)
        {
        cout << "> local intertwined redundancies detected at the following positions:" << endl;
            for(size_t i = 0; i < localrepposmat.size(); i++)
            {
                if(localrepposmat[i].size() > 0)
                {
                    for(size_t j = 0; j < localrepposmat[i].size(); j++)
                    {cout << pdbstruct.resnvec[localrepposmat[i][j]] << " " << pdbstruct.residvec[localrepposmat[i][j]];
                    cout << "-" << pdbstruct.atmvec[localrepposmat[i][j]] << endl;}
                cout << endl;
                }
            }
        }

    repstruct.localredidmat = localredidmat;
    repstruct.localrepposmat = localrepposmat;
    return repstruct;
    }

