#include "read_params.h"


    //*code snippet from "https://gist.github.com/karolisjan/f9b8ac3ae2d41ec0ce70f2feac6bdfaf"
    static string get_current_directory()
    {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");

	return string(buffer).substr(0, pos);
    }


    static bool str_to_bool(const string& teststr)
    {
    bool result;

        if(teststr.compare("false") == 0 || teststr.compare("False") == 0 || teststr.compare("FALSE") == 0)
        {result = false;}

        if(teststr.compare("true") == 0 || teststr.compare("True") == 0 || teststr.compare("TRUE") == 0)
        {result = true;}

        if(teststr.compare("false") != 0 && teststr.compare("False") == 0 && teststr.compare("FALSE") == 0
           && teststr.compare("true") != 0 && teststr.compare("True") != 0 && teststr.compare("TRUE") == 0)
        {cout << "< error occurred during conversion from string to boolean value." << endl;}

    return result;
    }


    static vector<string> str_to_list(const string& teststr)
    {
    vector<string> converted_list;
    string part_teststr;

        for(size_t i = 0; i < teststr.size(); i++)
        {
        string testletter = teststr.substr(i, 1);

            if(testletter.compare(",") != 0 && testletter.compare("{") != 0
               && testletter.compare("}") != 0 && testletter.compare(" ") != 0)
            {part_teststr += testletter;}

            if(testletter.compare(",") == 0 || testletter.compare("}") == 0)
            {converted_list.push_back(part_teststr);
            part_teststr = "";}
        }

    return converted_list;
    }


    Params Read_params::out()
    {
    vector<string> params_dict {"verbosity", "log", "multithreading", "print_pdb", "fraction_by_threshold", "rmsd_threshold",
                                "rmsd_threshold2", "score_threshold", "fractions", "fractionsize", "fractionsizes",
                                "fraction_step", "boxwise_align_it", "boxwise_align_steps", "max_depth_stopcount",
                                "max_total_stopcount", "rmsd_counts", "seqwise_align_it", "seqwise_align_steps",
                                "matrix", "method1", "method2", "data_dir", "run_dir", "filter", "rmsd_mode",
                                "final_rmsd_mode", "comb_steps", "target_coords", "rmsd_cutoff", "threads"};

    Params default_params; Params current_params;
    Get_path get_path;

    default_params.run_dir = get_current_directory();

    ifstream file;
    string filepath = default_params.run_dir+"\\params.txt";
    file.open(filepath.c_str());
    string line;
    vector<string> lines;

        while(getline(file, line))
        {lines.push_back(line);}

        if(!file.is_open())
        {cout << "< parameter file could not be opened! default values are used." << endl;
        cout << "< check entered file path: " << filepath << endl;
        return current_params;}

    file.close();

        //*iterate through parameter dictionary (by that, order in parameter file is irrelevant)
        for(int i = 0; i < params_dict.size(); i++)
        {
        size_t matchcheck = 0;

            for(int j = 0; j < lines.size() && matchcheck == 0; j++)
            {
                for(int k = 0; params_dict[i].size() < lines[j].size() && k < lines[j].size()-params_dict[i].size(); k++)
                {
                string teststr = lines[j].substr(k, params_dict[i].size());

                    if(teststr.compare(params_dict[i]) == 0)
                    {
                    matchcheck = 1;
                    teststr = "";

                        for(int l = k+params_dict[i].size()+3; l < lines[j].size(); l++)
                        {teststr += lines[j].substr(l, 1);}

                        if(i == 0)
                        {current_params.verbosity = atoi(teststr.c_str());}

                        if(i == 1)
                        {current_params.log = str_to_bool(teststr);}

                        if(i == 2)
                        {current_params.multithreading = str_to_bool(teststr);}

                        if(i == 3)
                        {current_params.print_pdb = str_to_bool(teststr);}

                        if(i == 4)
                        {current_params.fraction_by_threshold = str_to_bool(teststr);}

                        if(i == 5)
                        {current_params.rmsd_threshold = atof(teststr.c_str());}

                        if(i == 6)
                        {current_params.rmsd_threshold2 = atof(teststr.c_str());}

                        if(i == 7)
                        {current_params.score_threshold = atof(teststr.c_str());}

                        if(i == 8)
                        {current_params.fractions = atoi(teststr.c_str());}

                        if(i == 9)
                        {current_params.fractionsize = atoi(teststr.c_str());}

                        if(i == 10)
                        {current_params.fractionsizes = atoi(teststr.c_str());}

                        if(i == 11)
                        {current_params.fraction_step = atoi(teststr.c_str());}

                        if(i == 12)
                        {current_params.boxwise_align_it = atoi(teststr.c_str());}

                        if(i == 13)
                        {current_params.boxwise_align_steps = atoi(teststr.c_str());}

                        if(i == 14)
                        {current_params.max_depth_stopcount = atoi(teststr.c_str());}

                        if(i == 15)
                        {current_params.max_total_stopcount = atoi(teststr.c_str());}

                        if(i == 16)
                        {current_params.rmsd_counts = atoi(teststr.c_str());}

                        if(i == 17)
                        {current_params.seqwise_align_it = atoi(teststr.c_str());}

                        if(i == 18)
                        {current_params.seqwise_align_steps = atoi(teststr.c_str());}

                        if(i == 19)
                        {current_params.matrix = teststr;}

                        if(i == 20)
                        {current_params.method1 = teststr;}

                        if(i == 21)
                        {current_params.method2 = teststr;}

                        if(i == 22)
                        {current_params.data_dir = teststr;}

                        if(i == 23)
                        {current_params.run_dir = teststr;}

                        if(i == 24)
                        {current_params.filter = teststr;}

                        if(i == 25)
                        {current_params.rmsd_mode = teststr;}

                        if(i == 26)
                        {current_params.final_rmsd_mode = teststr;}

                        if(i == 27)
                        {current_params.comb_steps = atoi(teststr.c_str());}

                        if(i == 28)
                        {current_params.target_coords = str_to_list(teststr);}

                        if(i == 29)
                        {current_params.rmsd_cutoff = atof(teststr.c_str());}

                        if(i == 30)
                        {current_params.threads = atoi(teststr.c_str());}
                    }
                }
            }
        }

    return current_params;
    }
