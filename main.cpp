#include <fstream>
#include <iostream>

#include "eval.h"
#include "get_path.h"
#include "logprint.h"
#include "read_params.h"
#include "run.h"

using namespace std;


    int main()
    {
    //*definitions for sub-programs
    Eval eval; Get_path get_path;
    Read_params read_params;

    //*read parameter file and replace default parameters (if present)
    Params updated_params = read_params.out();

    //*initialize log file to store progress (can be switched off)
    ofstream logfile;
    if(updated_params.log == true) Logprint logprint(&logfile, &updated_params, true);

    //*retrieve PDB files
    //*requires folder and file tag, default is ".pdb"
    get_path.default_dir = updated_params.data_dir;
    vector<string> paths = get_path.out(updated_params);

    //*conduct calculation
    Run run(&logfile, &updated_params);
    vector<Run_result> run_results = run.out(paths);

    //*evaluate results and print (if "true" is chosen)
    eval.out(updated_params, run_results, true);

    int exitmode;
    cout << endl;
    cout << "> type '0' to exit program." << endl;
    cout << "< ";
        do
        {cin >> exitmode;} while(exitmode != 0);

    return 0;
    }
