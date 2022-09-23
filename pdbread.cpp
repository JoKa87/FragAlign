#include "pdbread.h"


    string str_remove(string str, string removeletters)
    {
    string short_str = "";

        for(size_t i = 0; i < str.size(); i++)
        {
        string letter = str.substr(i, 1);
        size_t matchcheck = 0;

            for(size_t j = 0; j < removeletters.size() && matchcheck == 0; j++)
            {
            string removeletter = removeletters.substr(j, 1);

                if(letter.compare(removeletter) == 0)
                {matchcheck = 1;}
            }

            if(matchcheck == 0)
            {short_str += letter;}
        }

    return short_str;
    }

    string str_remove_trailing(string str, string removeletters)
    {
    string short_str = "";

        for(size_t i = 0; i < str.size(); i++)
        {
        size_t trailcheck = 1;
        string letter = str.substr(i, 1);

            for(size_t j = 0; j < removeletters.size() && trailcheck == 1; j++)
            {
            string removeletter = removeletters.substr(j, 1);

                if(letter.compare(removeletter) == 0)
                {
                    for(size_t k = i; k < str.size() && trailcheck == 1; k++)
                    {
                    string testletter = str.substr(k, 1);

                        for(size_t l = 0; l < removeletters.size() && trailcheck == 1; l++)
                        {
                        removeletter = removeletters.substr(l, 1);

                            if(testletter.compare(removeletter) != 0)
                            {trailcheck = 0;}
                        }
                    }
                }

                if(letter.compare(removeletter) != 0)
                {trailcheck = 0;}
            }

            if(trailcheck == 0)
            {short_str += letter;}
        }

    return short_str;
    }

    bool is_canonical(const string& atm)
    {
    bool decision = false;
    vector<string> targets = {"C", "CA", "CG", "CG", "CD", "CD", "CB", "CB", "CZ", "CG", "CB",
                              "N", "ND1", "ND2", "NE", "NE1", "NE2", "NH1", "NH2", "NZ", "O",
                              "OD1", "OD2", "OE1", "OE2", "OG", "OG1", "OH", "SD", "SG"};

        for(size_t i = 0; i < targets.size() && decision == false; i++)
        {
            if(targets[i].compare(atm) == 0)
            {decision = true;}
        }

    return decision;
    }

    Pdbstruct Pdbread::out(const Params& params, const string& path)
    {
    Pdbstruct pdbstruct;
    pdbstruct.exceptioncheck = 0;

    string atm, resn, chn;
    int id, resid, poscount = 0;
    float x, y, z;
    int idtst = 0, headercheck = 0, pdbidmode = 0;
    int lastresid = -1;

    string line;
    ifstream pdbfile;
    pdbfile.open(path.c_str());
    vector<string> lines;

        while(getline(pdbfile, line))
        {lines.push_back(line);}

    size_t steps = 1;
    bool stopcheck = false;

        for(size_t i = 0; i < lines.size() && stopcheck == false; i+=steps)
        {
        line = lines[i];
        steps = 1;

            if(line.find("TER") == 0)
            {stopcheck = true;}

            if(line.size() > 4)
            {
                if(line.substr(0, 6).find("HEADER") == 0)
                {pdbstruct.pdb = line.substr(62, 4);
                if(params.verbosity == 1) cout << "< PDB ID: " << pdbstruct.pdb << endl;
                headercheck = 1;}
            }

            if(line.size() < 4)
            {continue;}

            if(line.size() > 20)
            {
            string atmtststr = line.substr(13, 3);
            atmtststr = str_remove(atmtststr, " ");
            bool atmcheck = false;

                //*test whether HETATM tag marks canonical amino acid
                //if(line.find("HETATM") == 0)
                //{atm = line.substr(13, 3);
                //atm = str_remove(atm, " ");
                //atmcheck = is_canonical(atm);}

                if(line.find("ATOM") == 0 || atmcheck == true)
                {
                string catstr = line.substr(0, 6);
                catstr = str_remove(catstr, " ");
                string idstr = line.substr(6, 5);
                id = atoi (idstr.c_str());
                atm = line.substr(13, 3);
                atm = str_remove(atm, " ");
                resn = line.substr(17, 4);
                resn = str_remove(resn, " ");
                chn = line.substr(21, 1);
                chn = str_remove(chn, " ");
                string residstr = line.substr(22, 4);
                resid = atoi(residstr.c_str());

                string xstr = line.substr(31, 8);
                x = atof (xstr.c_str());
                string ystr = line.substr(39, 8);
                y = atof (ystr.c_str());
                string zstr = line.substr(47, 8);
                z = atof (zstr.c_str());

                string res_info = line.substr(54, 24);

                    if(resid > 0)
                    {
                    poscount++;
                    pdbstruct.catvec.push_back(catstr);
                    pdbstruct.idvec.push_back(id);
                    pdbstruct.atmvec.push_back(atm);
                    pdbstruct.resnvec.push_back(resn);
                    pdbstruct.chnvec.push_back(chn);
                    pdbstruct.residvec.push_back(resid);
                    pdbstruct.xvec.push_back(x);
                    pdbstruct.yvec.push_back(y);
                    pdbstruct.zvec.push_back(z);
                    pdbstruct.poscountvec.push_back(poscount-1);
                    pdbstruct.res_info.push_back(res_info);

                        //*exception if different residues share residue ID (PDB 1a2c)
                        if(pdbstruct.resnvec.size() > 1 && pdbstruct.exceptioncheck == 0
                           && pdbstruct.resnvec[pdbstruct.resnvec.size()-1].compare(pdbstruct.resnvec[pdbstruct.resnvec.size()-2]) != 0
                           && pdbstruct.residvec[pdbstruct.residvec.size()-1] == pdbstruct.residvec[pdbstruct.resnvec.size()-2])
                        {cout << "< exception occurred: distinct residues share residue ID. PDB file is skipped." << endl;
                        pdbstruct.exceptioncheck = 1;}

                        if(atm.compare("N") == 0 && resid != lastresid)
                        {pdbstruct.poscountNvec.push_back(poscount-1);
                        pdbstruct.resnNvec.push_back(resn);
                        pdbstruct.residNvec.push_back(resid);
                        lastresid = resid;}
                    }

                    if(resid <= 0)
                    {cout << "< residue no. below 1 detected and ignored." << endl;}
                }
            }

            if(line.size() < 20)
            {continue;}
        }

    pdbfile.close();

    //*check current PDB for existing entry
    vector<string> pdbchecklinevec;
    ifstream pdbcheckin;
    pdbcheckin.open("C:\\tmp\\pdbcheck");
    int pdbcount = 0; string pdbcheckline;

        while(getline(pdbcheckin, pdbcheckline))
        {
        pdbchecklinevec.push_back(pdbcheckline);

            if(pdbcheckline.compare(pdbstruct.pdb) == 0)
            {pdbcount++;}
        }
    pdbcheckin.close();

        //*check if PDB ID is found in order to keep track of analyzed PDBs
        //*does not work for customized PDB files
        //*can be switched off using WARNING MODE
        if(headercheck == 0 && warningmode == "ON")
        {
        cout << endl;
        cout << "< PDB ID could not be found." << endl;
        cout << "< type '1' to continue calculation, type '2' to cancel." << endl;
        cout << "> ";

        string pdbidmodestr;
            do
            {
            cin >> pdbidmodestr;
            pdbidmode = atoi(pdbidmodestr.c_str());

                if(!(pdbidmode == 1 || pdbidmode == 2))
                {cout << endl;
                cout << "< wrong argument. try again!" << endl;
                cout << "< type '1' to continue re-calculation, type '2' to cancel." << endl;
                cout << "> ";}
            } while(!(pdbidmode == 1 || pdbidmode == 2));

            if(pdbidmode == 2)
            {cout << "< process canceled." << endl;
            exit(EXIT_FAILURE);}
        }

        //*check if PDB has been previously evaluated in order to avoid re-calculation
        //*can be switched off using WARNING MODE
        if(pdbcount >= 1 && headercheck == 1 && warningmode.compare("ON") == 0)
        {
        cout << endl;
        cout << "< PDB file has already been evaluated." << endl;
        cout << "< type '1' to continue re-calculation, type '2' to cancel." << endl;
        cout << "> ";

        string pdbcheckmodestr;
            do
            {
            cin >> pdbcheckmodestr; pdbcheckmode = atoi(pdbcheckmodestr.c_str());

                if(!(pdbcheckmode == 1 || pdbcheckmode == 2))
                {cout << endl;
                cout << "< wrong argument. try again!" << endl;
                cout << "< type '1' to continue re-calculation, type '2' to cancel." << endl;
                cout << "> ";}
            } while(!(pdbcheckmode == 1 || pdbcheckmode == 2));

            if(pdbcheckmode == 2)
            {cout << "< process canceled." << endl;
            exit(EXIT_FAILURE);}
        }

        //*create new entry if no entry exists yet
        if(pdbcount == 0 && headercheck == 1)
        {
        ofstream pdbcheckout;
        pdbcheckout.open(params.run_dir+"\\pdbcheck");
        pdbchecklinevec.push_back(pdbstruct.pdb);

            for(size_t j = 0; j < pdbchecklinevec.size(); j++)
            {pdbcheckout << pdbchecklinevec[j] << endl;}

        pdbcheckout.close();
        }

    return pdbstruct;
    }
