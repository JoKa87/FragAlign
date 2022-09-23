#include "get_stats.h"


    void get_localmin(vector<vector<float> >& mindists,
                      vector<vector<int> >& minorders,
                      const Params& params,
                      const vector<vector<float> >& matrix1, const vector<vector<float> >& matrix2,
                      const size_t& i, const size_t& j, const size_t& steps)
    {
    Utils utils;
    vector<float> temp_mindists;
    vector<int> temp_minindices;
    size_t zero = 0;

        for(size_t k = max(zero, j-steps/2); k < matrix2.size() && k < max(zero, j-steps/2)+steps; k++)
        {
        float dist = pow(matrix1[i][0]-matrix2[k][0], 2)
                   + pow(matrix1[i][1]-matrix2[k][1], 2)
                   + pow(matrix1[i][2]-matrix2[k][2], 2);

            if(temp_mindists.size() == steps)
            {
            size_t maxindex;
            float maxdist = -1;

                for(size_t l = 0; l < temp_mindists.size(); l++)
                {
                    if(maxdist == -1 || maxdist < dist)
                    {maxdist = dist;
                    maxindex = l;}
                }

                if(maxdist > dist)
                {temp_mindists[maxindex] = dist;
                temp_minindices[maxindex] = k;}
            }

            if(temp_mindists.size() < steps)
            {temp_mindists.push_back(dist);
            temp_minindices.push_back(k);}
        }

    vector<size_t> get_sorted_indices = utils.get_sorted_indices(params, temp_mindists);
    vector<float> temp_sorted_mindists;
    vector<int> temp_sorted_minindices;

        for(size_t k = 0; k < get_sorted_indices.size(); k++)
        {temp_sorted_mindists.push_back(temp_mindists[get_sorted_indices[k]]);
        temp_sorted_minindices.push_back(temp_minindices[get_sorted_indices[k]]);}

        for(size_t k = 0; k < get_sorted_indices.size(); k++)
        {mindists[temp_sorted_minindices[k]][i] = temp_sorted_mindists[k];
        minorders[temp_sorted_minindices[k]][i] = k;}

    return;
    }

    Stats Get_stats::out(const float& best_rmsd, const Params& params, const Data& input1, const Data& input2,
                        const vector<vector<float> >& matrix1, const vector<vector<float> >& matrix2,
                        const int& fraction1, const int& best_fraction2, const string& rmsd_mode, const float& rmsd_cutoff)
    {
    Stats stats;
    stats.coverage = 0;
    stats.rmsd = -1;
    bool stopcheck = false;
    float rmsd = 0;

        if(rmsd_mode.compare("BY_COMBINATION") == 0)
        {
        vector<vector<float> > mindists (matrix2.size(), (vector<float> (matrix1.size(), -1)));
        vector<vector<int> > minorders (matrix2.size(), (vector<int> (matrix1.size(), -1)));
        float dist;
        size_t distcount = 0, alignment_count = 0;
        int step1 = 0, step2 = 0;
        int init_offset = 0, offset = 0, test_offset = 0;

             //*determine initial offset for given alignment (shall be preserved)
            if(input1.pdbstruct.residNvec.size() > 0)
            {init_offset = input1.pdbstruct.residNvec[fraction1] - input2.pdbstruct.residNvec[best_fraction2];}

            //*iterate through aligned structures in C-terminal direction
            for(int i = 0; stopcheck == false && i < min(matrix1.size()-fraction1-step1, matrix2.size()-best_fraction2-step2); i++)
            {
            alignment_count++;

                //*check for deviations from initial offset and correct if found
                if(input1.pdbstruct.residNvec.size() > 0)
                {
                offset = input1.pdbstruct.residNvec[fraction1+step1+i]-input2.pdbstruct.residNvec[best_fraction2+step2+i]-init_offset;

                    if(offset > 0)
                    {
                    size_t j = 0;
                        do
                        {
                        j++;
                        test_offset = input1.pdbstruct.residNvec[fraction1+step1+i]
                                      -input2.pdbstruct.residNvec[best_fraction2+step2+i+j];
                        } while(test_offset != init_offset && best_fraction2+step2+i+j < input2.pdbstruct.residNvec.size());

                    step2 += j;
                    }

                    else if(offset < 0)
                    {
                    size_t j = 0;
                        do
                        {
                        j++;
                        test_offset = input1.pdbstruct.residNvec[fraction1+step1+i+j]
                                      -input2.pdbstruct.residNvec[best_fraction2+step2+i];
                        } while(test_offset != init_offset && fraction1+step1+i+j < input1.pdbstruct.residNvec.size());

                    step1 += j;
                    }
                }

            get_localmin(mindists, minorders, params, matrix1, matrix2,
                         fraction1+step1+i, best_fraction2+step2+i, params.comb_steps);
            }

        step1 = 0; step2 = 0;

            //*iterate through aligned structures in N-terminal direction
            for(int i = 1; stopcheck == false && i < min(fraction1-step1, best_fraction2-step2); i++)
            {
            alignment_count++;
            offset = input1.pdbstruct.residNvec[fraction1-step1-i]-input2.pdbstruct.residNvec[best_fraction2-step2-i]-init_offset;

                //*check for deviations from initial offset and correct if found
                if(offset < 0)
                {
                size_t j = 0;
                    do
                    {
                    j++;
                    test_offset = input1.pdbstruct.residNvec[fraction1-step1-i]-input2.pdbstruct.residNvec[best_fraction2-step2-i-j];
                    } while(test_offset != init_offset && best_fraction2-step2-i-j > 0);

                step2 += j;
                }

                else if(offset > 0)
                {
                size_t j = 0;
                    do
                    {
                    j++;
                    test_offset = input1.pdbstruct.residNvec[fraction1-step1-i-j]-input2.pdbstruct.residNvec[best_fraction2-step2-i];
                    } while(test_offset != init_offset && fraction1-step1-i-j > 0);

                step1 += j;
                }

            get_localmin(mindists, minorders, params, matrix1, matrix2,
                         fraction1-step1-i, best_fraction2-step2-i, params.comb_steps);
            }

            //evaluate distance matrices
            for(size_t i = 0; i < minorders[0].size(); i++)
            {
            bool stopcheck = false;
            size_t j = 0;
                do
                {
                bool matchcheck = false;
                    for(size_t k = 0; k < minorders.size() && matchcheck == false; k++)
                    {
                        if(minorders[k][i] == j)
                        {
                        float mindist = mindists[k][i];
                        size_t minindex = i;

                            for(size_t l = 0; l < minorders[k].size(); l++)
                            {
                                if(mindist > mindists[k][l] && mindists[k][l] != -1)
                                {mindist = mindists[k][l];
                                minindex = l;}
                            }

                            if(i == minindex && sqrt(mindists[k][i]) < params.rmsd_cutoff)
                            {
                            rmsd += mindists[k][i];
                            distcount++;
                            stopcheck = true;

                                for(size_t l = 0; l < mindists.size(); l++)
                                {mindists[l][i] = -1;}

                                for(size_t l = 0; l < mindists[k].size(); l++)
                                {mindists[k][l] = -1;}
                            }

                            if(i == minindex && sqrt(mindists[k][i]) >= params.rmsd_cutoff)
                            {stopcheck = true;}

                        matchcheck = true;
                        }
                    }
                j++;
                } while(j < params.comb_steps && stopcheck == false);
            }

            if(distcount != 0)
            {stats.rmsd = (float) sqrt(rmsd / distcount);
            stats.coverage = (float) distcount / alignment_count;}
        }

        //*determine RMSD by finding minimum distance for each residue (not recommended, much slower)
        if(rmsd_mode.compare("BY_MINIMUM") == 0)
        {
        vector<float> mincoords (3, 0);
        size_t mindistcount = 0;
        size_t alignment_count = 0;
        size_t step = 1;//params.fractionsize / 10;

            for(size_t i = 0; stopcheck == false && i < matrix1.size(); i+=step)
            {
            alignment_count++;
            float mindist = -1;

                for(size_t j = 0; j < matrix2.size() && stopcheck == false; j++)
                {
                float dist = pow(matrix1[i][0]-matrix2[j][0], 2)
                           + pow(matrix1[i][1]-matrix2[j][1], 2)
                           + pow(matrix1[i][2]-matrix2[j][2], 2);

                    //*find minimum distance to possibly redundant residue
                    if(mindist == -1 || mindist > dist)
                    {mindist = dist;
                    mincoords[0] = matrix2[j][0];
                    mincoords[1] = matrix2[j][1];
                    mincoords[2] = matrix2[j][2];}

                    if(mindistcount >= params.rmsd_counts && (float) sqrt(rmsd/mindistcount) >= best_rmsd && best_rmsd != -1)
                    {stopcheck = true;}
                }

                if(rmsd_cutoff == -1 || (rmsd_cutoff != -1 && sqrt(mindist) < rmsd_cutoff))
                {rmsd += mindist;
                mindistcount++;}
            }

            if(mindistcount != 0)
            {stats.rmsd = (float) sqrt(rmsd/mindistcount);
            stats.coverage = (float) mindistcount / alignment_count;}
        }

        if(rmsd_mode.compare("BY_SEQUENCE") == 0)
        {
        float dist;
        size_t distcount = 0, alignment_count = 0;
        int step1 = 0, step2 = 0;
        int init_offset = 0, offset = 0, test_offset = 0;

             //*determine initial offset for given alignment (shall be preserved)
            if(input1.pdbstruct.residNvec.size() > 0)
            {init_offset = input1.pdbstruct.residNvec[fraction1] - input2.pdbstruct.residNvec[best_fraction2];}

            //*iterate through aligned structures in C-terminal direction
            for(int i = 0; stopcheck == false && i < min(matrix1.size()-fraction1-step1, matrix2.size()-best_fraction2-step2); i++)
            {
            alignment_count++;

                //*check for deviations from initial offset and correct if found
                if(input1.pdbstruct.residNvec.size() > 0)
                {
                offset = input1.pdbstruct.residNvec[fraction1+step1+i]-input2.pdbstruct.residNvec[best_fraction2+step2+i]-init_offset;

                    if(offset > 0)
                    {
                    size_t j = 0;
                        do
                        {
                        j++;
                        test_offset = input1.pdbstruct.residNvec[fraction1+step1+i]
                                      -input2.pdbstruct.residNvec[best_fraction2+step2+i+j];
                        } while(test_offset != init_offset && best_fraction2+step2+i+j < input2.pdbstruct.residNvec.size());

                    step2 += j;
                    }

                    else if(offset < 0)
                    {
                    size_t j = 0;
                        do
                        {
                        j++;
                        test_offset = input1.pdbstruct.residNvec[fraction1+step1+i+j]
                                      -input2.pdbstruct.residNvec[best_fraction2+step2+i];
                        } while(test_offset != init_offset && fraction1+step1+i+j < input1.pdbstruct.residNvec.size());

                    step1 += j;
                    }
                }

                if(fraction1+step1+i < matrix1.size() && best_fraction2+step2+i < matrix2.size())
                {dist = pow(matrix1[fraction1+step1+i][0]-matrix2[best_fraction2+step2+i][0], 2)
                            + pow(matrix1[fraction1+step1+i][1]-matrix2[best_fraction2+step2+i][1], 2)
                            + pow(matrix1[fraction1+step1+i][2]-matrix2[best_fraction2+step2+i][2], 2);}

                if(dist >= 0 && (rmsd_cutoff == -1 || (rmsd_cutoff != -1 && sqrt(dist) < rmsd_cutoff)))
                {rmsd += dist;
                distcount++;}

                if(distcount >= params.rmsd_counts && (float) sqrt(rmsd/distcount) >= best_rmsd && best_rmsd != -1)
                {stopcheck = true;}
            }

        step1 = 0; step2 = 0;

            //*iterate through aligned structures in N-terminal direction
            for(int i = 1; stopcheck == false && i < min(fraction1-step1, best_fraction2-step2); i++)
            {
            alignment_count++;
            offset = input1.pdbstruct.residNvec[fraction1-step1-i]-input2.pdbstruct.residNvec[best_fraction2-step2-i]-init_offset;

                //*check for deviations from initial offset and correct if found
                if(offset < 0)
                {
                size_t j = 0;
                    do
                    {
                    j++;
                    test_offset = input1.pdbstruct.residNvec[fraction1-step1-i]-input2.pdbstruct.residNvec[best_fraction2-step2-i-j];
                    } while(test_offset != init_offset && best_fraction2-step2-i-j > 0);

                step2 += j;
                }

                else if(offset > 0)
                {
                size_t j = 0;
                    do
                    {
                    j++;
                    test_offset = input1.pdbstruct.residNvec[fraction1-step1-i-j]-input2.pdbstruct.residNvec[best_fraction2-step2-i];
                    } while(test_offset != init_offset && fraction1-step1-i-j > 0);

                step1 += j;
                }

                if(fraction1-step1-i > 0 && best_fraction2-step2-i > 0)
                {dist = pow(matrix1[fraction1-step1-i][0]-matrix2[best_fraction2-step2-i][0], 2)
                            + pow(matrix1[fraction1-step1-i][1]-matrix2[best_fraction2-step2-i][1], 2)
                            + pow(matrix1[fraction1-step1-i][2]-matrix2[best_fraction2-step2-i][2], 2);}

                if(dist >= 0 && (rmsd_cutoff == -1 || (rmsd_cutoff != -1 && sqrt(dist) < rmsd_cutoff)))
                {rmsd += dist;
                distcount++;}

                if(distcount >= params.rmsd_counts && (float) sqrt(rmsd/distcount) >= best_rmsd && best_rmsd != -1)
                {stopcheck = true;}
            }

            if(distcount != 0)
            {stats.rmsd = (float) sqrt(rmsd / distcount);
            stats.coverage = (float) distcount / alignment_count;}
        }

    return stats;
    }
