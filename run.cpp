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
#include "fileprint.h"
#include "get_fractions.h"
#include "get_stats.h"
#include "load.h"
#include "logprint.h"
#include "params.h"
#include "reconstruct.h"
#include "run.h"
#include "substitution.h"
#include "utils.h"

using namespace std;

    static Run_result run(Params* params, ofstream* logfile, const string& path1, const string& path2)
    {
    Logprint logprint(logfile, params);

    //*create local copy of parameters
    Params current_params = *params;
    Convert_sequence convert_sequence; Fileprint fileprint;
    Get_fractions get_fractions; Get_stats get_stats;
    Load load; Substitution substitution;
    Reconstruct reconstruct; Utils utils;

    Run_result run_result; Stats stats;
    vector<vector<float> > best_full_matrix1, best_full_matrix2;
    vector<vector<float> > best_matrix1, best_matrix2;
    float best_coverage, rmsd, best_rmsd = -1;
    int fraction1, best_fraction2;
    vector<long long int> checkpoints (10, 0); //*container for time storage
    checkpoints[0] = utils.get_time();

    Data input1 = load.out(current_params, path1, 1);
    Data input2 = load.out(current_params, path2, 2);
    Data output1, output2;

    if(input1.pdbstruct.pdb.size() == 0) input1.pdbstruct.pdb = utils.get_name_from_path(path1);
    if(input2.pdbstruct.pdb.size() == 0) input2.pdbstruct.pdb = utils.get_name_from_path(path2);

    vector<Best_value> ordered_best_values;

    //*convert string residue to index
    bool stopcheck = false;
    vector<int> converted_seq1 = convert_sequence.out(current_params, input1.pdbstruct.resnNvec);
    vector<int> converted_seq2 = convert_sequence.out(current_params, input2.pdbstruct.resnNvec);

    //*initialize substitution matrix for alignment calculation
    vector<vector<float> > substitution_mat = substitution.out(current_params);

    //*determine fraction sizes
    vector<size_t> fractionsizes;
    size_t center_fractionsize = min(input1.matrix.size(), input2.matrix.size())/2;
    if(center_fractionsize > current_params.fractionsize) center_fractionsize = current_params.fractionsize;

        for(size_t i = 0; i < current_params.fractionsizes; i++)
        {fractionsizes.push_back(center_fractionsize-5*(current_params.fractionsizes-1)/2+5*i);}

    bool mincheck = false;

        if(current_params.rmsd_mode.compare("BY_MINIMUM") == 0 || mincheck == true)
        {mincheck = true;
        current_params.rmsd_mode = "BY_SEQUENCE";}

        //*iterate through different fraction sizes
        for(size_t i = 0; i < fractionsizes.size(); i++)
        {
        current_params.fractionsize = fractionsizes[i];

            for(size_t j = 0; j < current_params.fractions && stopcheck == false; j++)
            {
                if(j > 0 && j >= ordered_best_values[0].fractions1.size())
                {stopcheck = true;}

                if(stopcheck == false)
                {ordered_best_values = get_fractions.out(ordered_best_values, current_params,
                                                         input1, input2, substitution_mat,
                                                         converted_seq1, converted_seq2, j);}

                //*iterate through fraction results
                //*conduct reconstruction for whole overlapping region
                //*determine RMSD
                for(size_t k = 0; k < ordered_best_values.size() && stopcheck == false; k++)
                {
                    if(ordered_best_values[k].best_param_history1.size() > 0)
                    {
                    output1 = reconstruct.out(input1, current_params, ordered_best_values[k].best_param_history1,
                                              0, input1.pdbstruct.residvec.size()-1, true, true, k);

                    output2 = reconstruct.out(input2, current_params, ordered_best_values[k].best_param_history2,
                                              0, input2.pdbstruct.residvec.size()-1, false, true, k);
                        if(mincheck == true)
                        {params->rmsd_mode = "BY_MINIMUM";}

                    stats = get_stats.out(-1, current_params, output1, output2, output1.matrix, output2.matrix,
                                         ordered_best_values[k].fraction1,
                                         ordered_best_values[k].best_fraction2, params->rmsd_mode, -1);

                        if(mincheck == true)
                        {current_params.rmsd_mode = "BY_SEQUENCE";}

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
        if(params->print_pdb == true && best_full_matrix1.size() > 0)
        {best_full_matrix1 = utils.transpose(best_full_matrix1);
        output1.pdbstruct.xvec = best_full_matrix1[0];
        output1.pdbstruct.yvec = best_full_matrix1[1];
        output1.pdbstruct.zvec = best_full_matrix1[2];
        best_full_matrix2 = utils.transpose(best_full_matrix2);
        output2.pdbstruct.xvec = best_full_matrix2[0];
        output2.pdbstruct.yvec = best_full_matrix2[1];
        output2.pdbstruct.zvec = best_full_matrix2[2];
        fileprint.out(output1.pdbstruct, output2.pdbstruct, current_params, 0, 1, true);}

    if(mincheck == true)
    {params->rmsd_mode = "BY_MINIMUM";}

    //*conduct final calculation with threshold (if chosen in parameter file)
    stats = get_stats.out(-1, current_params, output1, output2, best_matrix1, best_matrix2,
                         fraction1, best_fraction2, params->final_rmsd_mode, current_params.rmsd_cutoff);

    checkpoints[1] = utils.get_time();
    run_result.best_coverage = stats.coverage;
    run_result.best_rmsd = stats.rmsd;
    run_result.duration = checkpoints[1]-checkpoints[0];
    run_result.path1 = output1.pdbstruct.pdb;
    run_result.path2 = output2.pdbstruct.pdb;

        if(params->verbosity == 1 || params->verbosity == 2)
        {cout << "< " << run_result.path1 << "-" << run_result.path2;
        cout << ", best RMSD: " << run_result.best_rmsd;
        cout << ", best coverage: " << run_result.best_coverage << endl;
        cout << ", duration: " << run_result.duration << endl;}

        if(params->log == true)
        {logprint.out(run_result.path1 + "-" + run_result.path2);
        logprint.out(" best RMSD: " + utils.to_string(run_result.best_rmsd));
        logprint.out(" best coverage: " + utils.to_string(run_result.best_coverage));
        logprint.out(" duration: " + utils.to_string(run_result.duration));}

    return run_result;
    }


    void start(vector<vector<Run_result> >& run_results, Params* params, ofstream* logfile,
               const vector<string>& paths, const vector<vector<size_t> >& thread_indices)
    {
    vector<Run_result> temp;

        for(size_t i = 0; i < thread_indices[0].size(); i++)
        {Run_result run_result = run(params, logfile, paths[thread_indices[0][i]], paths[thread_indices[1][i]]);
        temp.push_back(run_result);}

    run_results.push_back(temp);
    }


    vector<Run_result> Run::out(const vector<string>& paths)
    {
    Utils utils;
    vector<Run_result> out;
    vector<vector<Run_result> > run_results;
    size_t progresscount = 0, showcount = 0;

    vector<long long int> checkpoints (10, 0);
    checkpoints[0] = utils.get_time();

        if(params->multithreading == false)
        {
            for(size_t i = 0; i < paths.size(); i++)
            {
                for(size_t j = i+1; j < paths.size(); j++)
                {
                progresscount++;
                showcount++;
                out.push_back(run(params, logfile, paths[i], paths[j]));

                //*status message
                checkpoints[1] = utils.get_time();
                showcount = 0;
                cout << "< " << progresscount << " of " << paths.size()*paths.size()/2;
                cout << " after " << checkpoints[1]-checkpoints[0] << " seconds." << '\r';
                }
            }
        }

        if(params->multithreading == true)
        {
        //*get index list for multi-threading
        vector<vector<size_t> > indices (2, vector<size_t> (0, 0));

            for(size_t i = 0; i < paths.size(); i++)
            {
                for(size_t j = i+1; j < paths.size(); j++)
                {indices[0].push_back(i);
                indices[1].push_back(j);}
            }

        if(params->threads > thread::hardware_concurrency()) params->threads = thread::hardware_concurrency();
        if(params->threads > indices[0].size()) params->threads = indices[0].size();

        vector<vector<vector<size_t> > > thread_indices (params->threads,
                                                        (vector<vector<size_t> > (2,
                                                        (vector<size_t> (0, 0)))));
        size_t threadcount = 0, totalcount = 0;
        size_t stepsize = indices[0].size() / params->threads;
        if(stepsize == 0) stepsize = 1;

            for(size_t i = 0; i < (indices[0].size()-indices[0].size() / params->threads);
                              i += stepsize)
            {
                for(size_t j = 0; j < stepsize; j++)
                {thread_indices[threadcount][0].push_back(indices[0][i+j]);
                thread_indices[threadcount][1].push_back(indices[1][i+j]);
                totalcount++;}

            threadcount++;
            }

        threadcount = 0;
            for(size_t i = totalcount; i < indices[0].size(); i++)
            {thread_indices[threadcount][0].push_back(indices[0][i]);
            thread_indices[threadcount][1].push_back(indices[1][i]);
            threadcount++;}

        vector<thread> run_threads;

            for(size_t i = 0; i < params->threads; i++)
            {run_threads.push_back(thread(start, ref(run_results), params, logfile, paths, thread_indices[i]));}

            for(auto& th: run_threads)
            {th.join();}
        }

        for(size_t i = 0; i < run_results.size(); i++)
        {
            for(size_t j = 0; j < run_results[i].size(); j++)
            {out.push_back(run_results[i][j]);}
        }

    return out;
    }
