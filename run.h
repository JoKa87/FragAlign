#ifndef RUN_H
#define RUN_H
#include <future>
#include <thread>
#include <utility>

#include "convert_sequence.h"
#include "fileprint.h"
#include "get_fractions.h"
#include "get_stats.h"
#include "load.h"
#include "logprint.h"
#include "params.h"
#include "reconstruct.h"
#include "substitution.h"
#include "utils.h"

struct Run_result
{
int duration;
float best_coverage;
float best_rmsd;
string path1;
string path2;
};

class Run
{
protected:
Params* params;
ofstream* logfile;

public:
Run (ofstream* updated_logfile, Params* updated_params)
    {params = updated_params;
     logfile = updated_logfile;}
vector<Run_result> out(const vector<string>& paths);
~Run() {}
};

#endif // RUN_H
