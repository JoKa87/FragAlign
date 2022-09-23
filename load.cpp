#include "load.h"


    Data Load::out(const Params& params, const string& path, const size_t& index)
    {
    Pdbread pdbread; Repdetect repdetect; Repremove repremove;
    Data input;

    //*read PDB file, warning mode is a switch for messages on
    //*(1) already evaluated PDB files, and
    //*(2) PDB files without "PDB" tag
    //*    if PDB tag is not present in PDB file, PDB ID is generated from file name
    pdbread.warningmode = "OFF";
    input.pdbstruct = pdbread.out(params, path);
    //*detect local repetitions in PDB structure
    Repstruct repstruct = repdetect.out(input.pdbstruct, params);
    //*remove local repetitions in PDB structure
    input.pdbstruct = repremove.out(input.pdbstruct, repstruct, params);
    int last_resid = -1;

        //*iterate through PDB coordinates and select for target coordinates (default is "CA")
        for(size_t i = 0; i < input.pdbstruct.xvec.size(); i++)
        {
        vector<float> tempvec (0, 0);
        vector<float> full_tempvec (0, 0);
        full_tempvec.push_back(input.pdbstruct.xvec[i]);
        full_tempvec.push_back(input.pdbstruct.yvec[i]);
        full_tempvec.push_back(input.pdbstruct.zvec[i]);
        input.full_matrix.push_back(full_tempvec);

            for(size_t j = 0; j < params.target_coords.size(); j++)
            {
                if(input.pdbstruct.atmvec[i].compare(params.target_coords[j]) == 0
                   && input.pdbstruct.catvec[i].compare("ATOM") == 0
                   && input.pdbstruct.residvec[i] != last_resid)
                {tempvec.push_back(input.pdbstruct.xvec[i]);
                tempvec.push_back(input.pdbstruct.yvec[i]);
                tempvec.push_back(input.pdbstruct.zvec[i]);
                input.selected_indices.push_back(i);
                input.matrix.push_back(tempvec);
                last_resid = input.pdbstruct.residvec[i];}
            }
        }

    return input;
    }
