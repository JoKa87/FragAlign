#include "repremove.h"


    //*remove local repetitions in PDB structure
    Pdbstruct& Repremove::out(Pdbstruct& pdbstruct, const Repstruct& repstruct, const Params& params)
    {
    vector<vector<int> > localredidmat = repstruct.localredidmat;
    vector<vector<int> > localrepposmat = repstruct.localrepposmat;
    vector<size_t> erasevec;

        //*average redundant coordinates and remove local block-wise repetitions
        if(localredidmat[0].size() > 0)
        {
            for(size_t i = 0; i < localredidmat[0].size(); i++)
            {
            float xavg = 0;
            float yavg = 0;
            float zavg = 0;
            float eventcount = 0;
            size_t stopcheck = 0;
            size_t j = localredidmat[0][i];

                do
                {
                    if(pdbstruct.atmvec[j].compare("N") == 0
                        && pdbstruct.poscountvec[j] > localredidmat[1][i])
                    {stopcheck = 1;}

                    if(stopcheck == 0)
                    {
                    xavg += pdbstruct.xvec[j];
                    yavg += pdbstruct.yvec[j];
                    zavg += pdbstruct.zvec[j];
                    string refatm = pdbstruct.atmvec[j];
                    eventcount++;
                    size_t k = j+1;

                        do
                        {
                            if(pdbstruct.atmvec[k].compare(refatm) == 0)
                            {xavg += pdbstruct.xvec[k];
                            yavg += pdbstruct.yvec[k];
                            zavg += pdbstruct.zvec[k];
                            eventcount += 1;
                            erasevec.push_back(k);}
                        k++;
                        } while(k < localredidmat[1][i] && k < pdbstruct.idvec.size());

                    xavg /= eventcount;
                    yavg /= eventcount;
                    zavg /= eventcount;
                    pdbstruct.xvec[j] = xavg;
                    pdbstruct.yvec[j] = yavg;
                    pdbstruct.zvec[j] = zavg;
                    xavg = 0; yavg = 0; zavg = 0; eventcount = 0;
                    }
                j++;
                } while(stopcheck == 0 && j < pdbstruct.idvec.size()-1);
            }
        }

        //*average redundant coordinates and remove local intertwined repetitions
        if(localrepposmat.size() > 0)
        {
            for(size_t i = 0; i < localrepposmat.size() && localrepposmat[i].size() > 0; i++)
            {
            float xavg = 0;
            float yavg = 0;
            float zavg = 0;
            size_t eventcount = 0;

                for(size_t j = 0; j < localrepposmat[i].size(); j++)
                {
                    if(eventcount > 0)
                    {erasevec.push_back(localrepposmat[i][j]);}

                xavg += pdbstruct.xvec[localrepposmat[i][j]];
                yavg += pdbstruct.yvec[localrepposmat[i][j]];
                zavg += pdbstruct.zvec[localrepposmat[i][j]];
                eventcount++;
                }

            xavg /= (float) eventcount;
            yavg /= (float) eventcount;
            zavg /= (float) eventcount;
            pdbstruct.xvec[localrepposmat[i][0]] = xavg;
            pdbstruct.yvec[localrepposmat[i][0]] = yavg;
            pdbstruct.zvec[localrepposmat[i][0]] = zavg;
            }
        }

    //*remove redundant residues
    sort(erasevec.begin(), erasevec.end());
        for(size_t i = 0; i < erasevec.size(); i++)
        {pdbstruct.catvec.erase(pdbstruct.catvec.begin()+erasevec[erasevec.size()-1-i]);
        pdbstruct.idvec.erase(pdbstruct.idvec.begin()+erasevec[erasevec.size()-1-i]);
        pdbstruct.atmvec.erase(pdbstruct.atmvec.begin()+erasevec[erasevec.size()-1-i]);
        pdbstruct.resnvec.erase(pdbstruct.resnvec.begin()+erasevec[erasevec.size()-1-i]);
        pdbstruct.chnvec.erase(pdbstruct.chnvec.begin()+erasevec[erasevec.size()-1-i]);
        pdbstruct.residvec.erase(pdbstruct.residvec.begin()+erasevec[erasevec.size()-1-i]);
        pdbstruct.xvec.erase(pdbstruct.xvec.begin()+erasevec[erasevec.size()-1-i]);
        pdbstruct.yvec.erase(pdbstruct.yvec.begin()+erasevec[erasevec.size()-1-i]);
        pdbstruct.zvec.erase(pdbstruct.zvec.begin()+erasevec[erasevec.size()-1-i]);
        pdbstruct.poscountvec.erase(pdbstruct.poscountvec.begin()+erasevec[erasevec.size()-1-i]);}

    //*re-fill position count vectors
    for(size_t i = 0; i < pdbstruct.poscountvec.size(); i++)
    {pdbstruct.poscountvec[i] = i;}

    //*update N specific vectors
    pdbstruct.resnNvec.clear();
    pdbstruct.poscountNvec.clear();
    pdbstruct.residNvec.clear();

    for(size_t i = 0; i < pdbstruct.atmvec.size(); i++)
    {
        if(pdbstruct.atmvec[i].compare("N") == 0)
        {pdbstruct.resnNvec.push_back(pdbstruct.resnvec[i]);
        pdbstruct.poscountNvec.push_back(pdbstruct.poscountvec[i]);
        pdbstruct.residNvec.push_back(pdbstruct.residvec[i]);}
    }

    if(params.verbosity == 1) cout << "< " << erasevec.size() << " local repetitions have been removed." << endl;
    return pdbstruct;
    }
