#include "reconstruct.h"


    Data Reconstruct::out(const Data& input, const Params& params, vector<vector<float> >& best_param_history,
                          size_t best_start_poscount, size_t best_end_poscount,
                          const bool& target, const bool& full_matrix, const size_t& index)
    {
    Shift shift; Utils utils; Transform_by_history transform_by_history;
    Data output = input;

    //*apply transformation history to whole target coordinates
    vector<float> shift_vector {best_param_history[1][1], best_param_history[1][2], best_param_history[1][3]};
    if(target == true) output.matrix = shift.out(output.matrix, best_param_history, shift_vector, true, false);
    else if(target == false) output.matrix = transform_by_history.out(output.matrix, best_param_history);

        //*full matrix includes all coordinates (not only target coordinates)
        //*used for final output
        if(full_matrix == true)
        {
        vector<vector<float> > full_matrix {output.pdbstruct.xvec, output.pdbstruct.yvec, output.pdbstruct.zvec};
        full_matrix = utils.transpose(full_matrix);

            if(target == true) full_matrix = shift.out(full_matrix, best_param_history, shift_vector, true, false);
            if(target == false) full_matrix = transform_by_history.out(full_matrix, best_param_history);

        full_matrix = utils.transpose(full_matrix);
        output.pdbstruct.xvec = full_matrix[0];
        output.pdbstruct.yvec = full_matrix[1];
        output.pdbstruct.zvec = full_matrix[2];
        output.full_matrix = utils.transpose(full_matrix);
        }

    return output;
    }
