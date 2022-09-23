#include "eval.h"


    //*calculate average and variance
    vector<float> get_stats(const vector<float>& values)
    {
    Utils utils;
    vector<float> stats;

        if(values.size()-1 != 0)
        {float avg = utils.get_avg(values);
        float var = utils.get_var(values, avg);
        stats.push_back(avg);
        stats.push_back(sqrt(var/(values.size()-1)));}

    return stats;
    }


    //*evaluate alignment results
    void Eval::out(const Params& updated_params, const vector<Run_result>& run_results, const bool& print)
    {
    Print_stats print_stats;

    vector<vector<float> > stats;
    vector<float> best_rmsds, best_coverages, durations;
    vector<float> best_rmsds_stats, best_coverages_stats, durations_stats;

        for(size_t i = 0; i < run_results.size(); i++)
        {
            if(run_results[i].best_rmsd != -1)
            {best_rmsds.push_back(run_results[i].best_rmsd);}

            else
            {best_rmsds.push_back(0);}
        }

    best_rmsds_stats = get_stats(best_rmsds);
    stats.push_back(best_rmsds_stats);

        for(size_t i = 0; i < run_results.size(); i++)
        {
            if(run_results[i].best_coverage != -1)
            {best_coverages.push_back(run_results[i].best_coverage);}

            else
            {best_coverages.push_back(0);}
        }

    best_coverages_stats = get_stats(best_coverages);
    stats.push_back(best_coverages_stats);

        for(size_t i = 0; i < run_results.size(); i++)
        {durations.push_back(run_results[i].duration);}

    durations_stats = get_stats(durations);
    stats.push_back(durations_stats);

        //*print alignment results
        if(run_results.size() > 0 && print == true)
        {print_stats.out(updated_params, run_results, stats);
        cout << "< results were printed to file." << endl;}

    return;
    }
