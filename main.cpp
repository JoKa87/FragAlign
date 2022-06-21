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
#include <thread>
#include <future>

#include "convert_sequence.h"
#include "eval.h"
#include "fileprint.h"
#include "get_fractions.h"
#include "get_path.h"
#include "get_stats.h"
#include "load.h"
#include "logprint.h"
#include "params.h"
#include "read_params.h"
#include "reconstruct.h"
#include "substitution.h"
#include "utils.h"

using namespace std;

    Run_result run(Params params, const string& path1, const string& path2)
    {
    Convert_sequence convert_sequence; Fileprint fileprint;
    Get_fractions get_fractions; Get_stats get_stats;
    Load load; Logprint logprint; Substitution substitution;
    Reconstruct reconstruct; Utils utils;

    Run_result run_result; Stats stats;
    vector<vector<float> > best_full_matrix1, best_full_matrix2;
    vector<vector<float> > best_matrix1, best_matrix2;
    float best_coverage, rmsd, best_rmsd = -1;
    int fraction1, best_fraction2;
    vector<long long int> checkpoints (10, 0); //*container for time storage
    checkpoints[0] = utils.get_time();

    Data input1 = load.out(params, path1, 1);
    Data input2 = load.out(params, path2, 2);
    Data output1, output2;

    if(input1.pdbstruct.pdb.size() == 0) input1.pdbstruct.pdb = utils.get_name_from_path(path1);
    if(input2.pdbstruct.pdb.size() == 0) input2.pdbstruct.pdb = utils.get_name_from_path(path2);

    vector<Best_value> ordered_best_values;

    //*convert string residue to index
    bool stopcheck = false;
    vector<int> converted_seq1 = convert_sequence.out(params, input1.pdbstruct.resnNvec);
    vector<int> converted_seq2 = convert_sequence.out(params, input2.pdbstruct.resnNvec);

    //*initialize substitution matrix for alignment calculation
    vector<vector<float> > substitution_mat = substitution.out(params);

    //*determine fraction sizes
    vector<size_t> fractionsizes;
    size_t center_fractionsize = min(input1.matrix.size(), input2.matrix.size())/2;
    if(center_fractionsize > params.fractionsize) center_fractionsize = params.fractionsize;

        for(size_t i = 0; i < params.fractionsizes; i++)
        {fractionsizes.push_back(center_fractionsize-5*(params.fractionsizes-1)/2+5*i);}

    bool mincheck = false;
        if(params.rmsd_mode.compare("BY_MINIMUM") == 0 || mincheck == true)
        {mincheck = true;
        params.rmsd_mode = "BY_SEQUENCE";}

        //*iterate through different fraction sizes
        for(size_t i = 0; i < fractionsizes.size(); i++)
        {
        params.fractionsize = fractionsizes[i];

            for(size_t j = 0; j < params.fractions && stopcheck == false; j++)
            {
                if(j > 0 && j >= ordered_best_values[0].fractions1.size())
                {stopcheck = true;}

                if(stopcheck == false)
                {ordered_best_values = get_fractions.out(ordered_best_values, params,
                                                         input1, input2, substitution_mat,
                                                         converted_seq1, converted_seq2, j);}

                //*iterate through fraction results
                //*conduct reconstruction for whole overlapping region
                //*determine RMSD
                for(size_t k = 0; k < ordered_best_values.size() && stopcheck == false; k++)
                {
                    if(ordered_best_values[k].best_param_history1.size() > 0)
                    {
                    output1 = reconstruct.out(input1, params, ordered_best_values[k].best_param_history1,
                                              0, input1.pdbstruct.residvec.size()-1, true, true, k);

                    output2 = reconstruct.out(input2, params, ordered_best_values[k].best_param_history2,
                                              0, input2.pdbstruct.residvec.size()-1, false, true, k);

                        if(mincheck == true)
                        {params.rmsd_mode = "BY_MINIMUM";}

                    stats = get_stats.out(-1, params, output1, output2, output1.matrix, output2.matrix,
                                         ordered_best_values[k].fraction1,
                                         ordered_best_values[k].best_fraction2, params.rmsd_mode, -1);

                        if(mincheck == true)
                        {params.rmsd_mode = "BY_SEQUENCE";}

                        if(best_rmsd == -1 || best_rmsd > stats.rmsd)
                        {best_coverage = stats.coverage;
                        best_rmsd = stats.rmsd;
                        best_matrix1 = output1.matrix;
                        best_matrix2 = output2.matrix;
                        best_full_matrix1 = output1.full_matrix;
                        best_full_matrix2 = output2.full_matrix;
                        fraction1 = ordered_best_values[k].fraction1;
                        best_fraction2 = ordered_best_values[k].best_fraction2;}
                    }
                }

            input1 = output1;
            input2 = output2;
            }

        ordered_best_values.clear();
        }

        //*print PDB if desired
        if(params.print_pdb == true && best_full_matrix1.size() > 0)
        {best_full_matrix1 = utils.transpose(best_full_matrix1);
        output1.pdbstruct.xvec = best_full_matrix1[0];
        output1.pdbstruct.yvec = best_full_matrix1[1];
        output1.pdbstruct.zvec = best_full_matrix1[2];
        best_full_matrix2 = utils.transpose(best_full_matrix2);
        output2.pdbstruct.xvec = best_full_matrix2[0];
        output2.pdbstruct.yvec = best_full_matrix2[1];
        output2.pdbstruct.zvec = best_full_matrix2[2];
        fileprint.out(output1.pdbstruct, output2.pdbstruct, params, 0, 1, true);}

    if(mincheck == true)
    {params.rmsd_mode = "BY_MINIMUM";}

    //*conduct final calculation with threshold (if chosen in parameter file)
    stats = get_stats.out(-1, params, output1, output2, best_matrix1, best_matrix2,
                         fraction1, best_fraction2, params.final_rmsd_mode, params.rmsd_cutoff);

    checkpoints[1] = utils.get_time();
    run_result.best_coverage = stats.coverage;
    run_result.best_rmsd = stats.rmsd;
    run_result.duration = checkpoints[1]-checkpoints[0];
    run_result.path1 = output1.pdbstruct.pdb;
    run_result.path2 = output2.pdbstruct.pdb;

        if(params.verbosity == 1 || params.verbosity == 2)
        {cout << "< " << run_result.path1 << "-" << run_result.path2;
        cout << ", best RMSD: " << run_result.best_rmsd;
        cout << ", best coverage: " << run_result.best_coverage << endl;
        cout << ", duration: " << run_result.duration << endl;}

    return run_result;
    }

    int main()
    {
    //*definitions for sub-programs
    Eval eval; Get_fractions get_fractions; Get_path get_path;
    Logprint logprint; Params params;
    Read_params read_params; Utils utils;

    logprint.out({}, "log initialized", params, true);
    vector<long long int> checkpoints (10, 0);

    //*read parameter file and replace default parameters (if present)
    Params updated_params = read_params.out();

    //*retrieve PDB files
    //*requires folder and file tag, default is ".pdb"
    get_path.default_dir = updated_params.data_dir;
    vector<string> paths = get_path.out(updated_params);

    vector<thread> run_threads;
    vector<Run_result> run_results;
    size_t progresscount = 0, showcount = 0;
    checkpoints[0] = utils.get_time();

        for(size_t i = 0; i < paths.size(); i++)
        {
            for(size_t j = i+1; j < paths.size(); j++)
            {
            progresscount++;
            showcount++;

                if(updated_params.multithreading == false)
                {run_results.push_back(run(updated_params, paths[i], paths[j]));}

                if(updated_params.multithreading == true)
                {auto future = async(run, updated_params, paths[i], paths[j]);
                run_results.push_back(future.get());}

                //*status message
                if(showcount == 100)
                {checkpoints[1] = utils.get_time();
                showcount = 0;
                cout << "< " << progresscount << " of " << paths.size()*paths.size()/2;
                cout << " after " << checkpoints[1]-checkpoints[0] << " seconds." << '\r';}
            }
        }

    //*evaluate results and print (if "true" is chosen)
    eval.out(updated_params, run_results, true);
    return 0;
    }

