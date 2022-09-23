#include "get_path.h"


    size_t pdb_to_idx(const string& teststr)
    {
    vector<string> alphanumericals = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    size_t index = 0;

        for(size_t i = 0; i < teststr.size(); i++)
        {
        string testletter = teststr.substr(i, 1);
        size_t matchcheck = 0;

            for(size_t j = 0; j < alphanumericals.size() && matchcheck == 0; j++)
            {
                if(testletter.compare(alphanumericals[j]) == 0)
                {index += pow(36, (3-i))*j;
                matchcheck = 1;}
            }
        }

    return index;
    }

    vector<string> Get_path::out(const Params& params)
    {
    vector<string> paths;
    vector<string> outfile_paths;
    string modestr;
    cout << "< type '1' to get alignment for all structures in folder." << endl;
    cout << "< type '2' to get alignment for specified structures." << endl;
    cout << "> ";
        do
        {
        cin >> modestr;

            if(modestr.compare("1") != 0 && modestr.compare("2") != 0)
            {cout << "< wrong argument. try again." << endl;}

        } while(modestr.compare("1") != 0 && modestr.compare("2") != 0);

    string dir;
    string dirstr, filestr;
    cout << "< enter directory. to use directory specified in parameter file, type '1'." << endl;
        do
        {
        cout << "> "; cin >> dirstr;

            if(dirstr.compare("1") == 0)
            {dir = default_dir;}

            else
            {dir = dirstr;}

        struct dirent *d;
        DIR *dir_p;
        dir_p = opendir(dir.c_str());

            if(dir_p != NULL && dirstr.compare("0") != 0)
            {
                //*iterate through specified data directory
                for(d = readdir(dir_p); d != NULL; d = readdir(dir_p))
                {
                string filename = d -> d_name;

                    if(filename.size() > params.filter.size() && filename.size() > 7)
                    {
                    string teststr = filename.substr(filename.size()-params.filter.size(), params.filter.size());

                            if(teststr.compare(params.filter) == 0)
                            {paths.push_back(dir+"\\"+filename);}
                    }
                }

            closedir(dir_p);
            }

            if(dir_p == NULL && dirstr.compare("0") != 0)
            {cout << "< error occurred during reading of directory. try again or type '0' to exit." << endl;}

        } while(dirstr.compare("0") != 0 && paths.size() == 0);

        if(modestr.compare("2") == 0)
        {
        paths.clear();
        cout << "< specify input files, type '0' to end selection." << endl;
            do
            {
            cout << "> "; cin >> filestr;

                //*test whether file exists
                if(filestr.compare("0") != 0)
                {
                ifstream testfile;
                testfile.open(filestr.c_str());

                    if(testfile.is_open())
                    {paths.push_back(dir+"\\"+filestr);}

                    else
                    {cout << "< error occurred during reading of file. try again or type '0' to exit." << endl;}
                }
            } while(filestr.compare("0") != 0);
        }

        if(paths.size() == 0)
        {exit(0);}

    return paths;
    }
