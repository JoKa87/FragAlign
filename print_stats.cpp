#include "print_stats.h"


    void Print_stats::out(const Params& updated_params, const vector<Run_result>& run_results,
                          const vector<vector<float> >& stats)
    {
    vector<string> params_dict {"verbosity", "log", "multithreading", "print_pdb", "fraction_by_threshold", "rmsd_threshold",
                                "rmsd_threshold2", "score_threshold", "fractions", "fractionsize", "fractionsizes",
                                "fraction_step", "boxwise_align_it", "boxwise_align_steps", "max_depth_stopcount",
                                "max_total_stopcount", "rmsd_counts", "seqwise_align_it", "seqwise_align_steps",
                                "matrix", "method1", "method2", "data_dir", "run_dir", "filter", "rmsd_mode",
                                "final_rmsd_mode", "comb_steps", "target_coords", "rmsd_cutoff", "threads"};

    ofstream outfile;
    string outfilepath = updated_params.run_dir+"\\alignment_stats.txt";
    outfile.open(outfilepath.c_str());

        //*print statistics (if n > 1)
        if(stats.size() > 0 && stats[0].size() > 0)
        {outfile << setprecision(4) << "evaluation results. avg. rmsd: " << stats[0][0];
        outfile << ", mean error: " << stats[0][1] << endl;
        outfile << setprecision(4) << "avg coverage: " << stats[1][0];
        outfile << ", mean error: " << stats[1][1] << endl;
        outfile << setprecision(4) << "avg duration: " << stats[2][0];
        outfile << ", mean error: " << stats[2][1] << endl;}

        //*print single results
        for(size_t i = 0; i < run_results.size(); i++)
        {
            if(run_results[i].best_rmsd != -1)
            {outfile << run_results[i].path1 << "-" << run_results[i].path2;
            outfile << ", RMSD: " << run_results[i].best_rmsd;
            outfile << ", coverage: " << run_results[i].best_coverage;
            outfile << ", duration: " << run_results[i].duration << endl;}

            if(run_results[i].best_rmsd == -1)
            {outfile << run_results[i].path1 << "-" << run_results[i].path2;
            outfile << ", RMSD: n.d.";
            outfile << ", coverage: n.d.";
            outfile << ", duration: " << run_results[i].duration << endl;}
        }

    outfile << endl;
    outfile << "< used parameters:" << endl;

        //*print used parameters
        for(int i = 0; i < params_dict.size(); i++)
        {
            if(i == 0)
            {outfile << params_dict[i] << " = " << updated_params.verbosity << endl;}

            if(i == 1)
            {outfile << params_dict[i] << " = " << updated_params.log << endl;}

            if(i == 2)
            {outfile << params_dict[i] << " = " << updated_params.multithreading << endl;}

            if(i == 3)
            {outfile << params_dict[i] << " = " << updated_params.print_pdb << endl;}

            if(i == 4)
            {outfile << params_dict[i] << " = " << updated_params.fraction_by_threshold << endl;}

            if(i == 5)
            {outfile << params_dict[i] << " = " << updated_params.rmsd_threshold << endl;}

            if(i == 6)
            {outfile << params_dict[i] << " = " << updated_params.rmsd_threshold2 << endl;}

            if(i == 7)
            {outfile << params_dict[i] << " = " << updated_params.score_threshold << endl;}

            if(i == 8)
            {outfile << params_dict[i] << " = " << updated_params.fractions << endl;}

            if(i == 9)
            {outfile << params_dict[i] << " = " << updated_params.fractionsize << endl;}

            if(i == 10)
            {outfile << params_dict[i] << " = " << updated_params.fractionsizes << endl;}

            if(i == 11)
            {outfile << params_dict[i] << " = " << updated_params.fraction_step << endl;}

            if(i == 12)
            {outfile << params_dict[i] << " = " << updated_params.boxwise_align_it << endl;}

            if(i == 13)
            {outfile << params_dict[i] << " = " << updated_params.boxwise_align_steps << endl;}

            if(i == 14)
            {outfile << params_dict[i] << " = " << updated_params.max_depth_stopcount << endl;}

            if(i == 15)
            {outfile << params_dict[i] << " = " << updated_params.max_total_stopcount << endl;}

            if(i == 16)
            {outfile << params_dict[i] << " = " << updated_params.rmsd_counts << endl;}

            if(i == 17)
            {outfile << params_dict[i] << " = " << updated_params.seqwise_align_it << endl;}

            if(i == 18)
            {outfile << params_dict[i] << " = " << updated_params.seqwise_align_steps << endl;}

            if(i == 19)
            {outfile << params_dict[i] << " = " << updated_params.matrix << endl;}

            if(i == 20)
            {outfile << params_dict[i] << " = " << updated_params.method1 << endl;}

            if(i == 21)
            {outfile << params_dict[i] << " = " << updated_params.method2 << endl;}

            if(i == 22)
            {outfile << params_dict[i] << " = " << updated_params.data_dir << endl;}

            if(i == 23)
            {outfile << params_dict[i] << " = " << updated_params.run_dir << endl;}

            if(i == 24)
            {outfile << params_dict[i] << " = " << updated_params.filter << endl;}

            if(i == 25)
            {outfile << params_dict[i] << " = " << updated_params.rmsd_mode << endl;}

            if(i == 26)
            {outfile << params_dict[i] << " = " << updated_params.final_rmsd_mode << endl;}

            if(i == 27)
            {outfile << params_dict[i] << " = " << updated_params.comb_steps << endl;}

            if(i == 28)
            {
            outfile << params_dict[i] << " = {";

                for(size_t j = 0; j < updated_params.target_coords.size(); j++)
                {
                outfile << updated_params.target_coords[j];

                    if(j < updated_params.target_coords.size()-1)
                    {outfile << ", ";}
                }

            outfile << "}"  << endl;
            }

            if(i == 29)
            { outfile << params_dict[i] << " = " << updated_params.rmsd_cutoff << endl;}

            if(i == 30)
            {outfile << params_dict[i] << " = " << updated_params.threads;}
        }

    outfile.close();
    return;
    }
