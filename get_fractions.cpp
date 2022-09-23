#include "get_fractions.h"


    vector<Best_value> Get_fractions::out(const vector<Best_value> best_values,
                                          const Params& params, const Data& input1, const Data& input2,
                                          const vector<vector<float> >& substitution_mat,
                                          const vector<int>& converted_seq1, const vector<int>& converted_seq2,
                                          const size_t& it)
    {
    //*definitions for sub-programs
    Get_deviation get_deviation; Utils utils;

    Deviation deviation;

    Best_value best_value, partial_best_value;
    vector<Best_value> ordered_best_values, ordered_partial_best_values;
    vector<size_t> fractions1, fractions2;
    vector<float> scores;

    float score, testscore, maxscore = -1, oldtestscore = -1;

    size_t fraction1, fraction2;
    size_t start_poscount1, start_poscount2;
    size_t end_poscount1, end_poscount2;

    deviation.matrix1 = vector<vector<float> > (params.fractionsize, (vector<float> (input1.matrix[0].size(), 0)));
    deviation.best_matrix2 = vector<vector<float> > (params.fractionsize, (vector<float> (input2.matrix[0].size(), 0)));

        //*determine best alignments given the fraction size
        //*for each fraction size conducted only once
        if(best_values.size() == 0)
        {
        bool stopcheck = false;
        size_t i = 0;
            do
            {
            size_t j = 0;
                do
                {
                float score = 0;

                    //*determine alignment score based on substitution matrix
                    for(size_t k = 0; k < params.fractionsize; k++)
                    {
                        if(converted_seq1[i+k] >= 0 && converted_seq1[i+k] < substitution_mat.size()
                            && converted_seq2[j+k] >= 0 && converted_seq2[j+k] < substitution_mat[0].size())
                        {score += substitution_mat[converted_seq1[i+k]][converted_seq2[j+k]];}
                    }

                testscore = (float) score / params.fractionsize;

                    //*register assigned fractions candidates based on maximum scores (preferred option)
                    if(params.fraction_by_threshold == false)
                    {
                        if(fractions1.size() == params.fractions)
                        {
                        float minvalue = -1;
                        size_t minindex;

                            for(size_t k = 0; k < scores.size(); k++)
                            {
                                if(minvalue == -1 || minvalue > scores[k])
                                {minvalue = scores[k];
                                minindex = k;}
                            }

                            if(minvalue < testscore && minindex == fractions1.size()-1)
                            {fractions1[minindex] = i;
                            fractions2[minindex] = j;
                            scores[minindex] = testscore;}

                            if(minvalue < testscore && minindex < fractions1.size()-1)
                            {fractions1[minindex] = fractions1[fractions1.size()-1];
                            fractions2[minindex] = fractions2[fractions2.size()-1];
                            scores[minindex] = scores[scores.size()-1];
                            fractions1[fractions1.size()-1] = i;
                            fractions2[fractions2.size()-1] = j;
                            scores[scores.size()-1] = testscore;}
                        }

                        if(fractions1.size() < params.fractions)
                        {scores.push_back(testscore);
                        fractions1.push_back(i);
                        fractions2.push_back(j);}
                    }

                    //*register assigned fractions candidates based on scoring threshold
                    else if(params.fraction_by_threshold == true
                       && oldtestscore >= params.score_threshold && testscore < oldtestscore
                       && (fractions1.size() == 0
                       || (fractions1.size() > 0 && i-fractions1[fractions1.size()-1] >= params.fraction_step)))
                    {
                    fractions1.push_back(i);
                    fractions2.push_back(j-1);

                        if(fractions1.size() == params.fractions)
                        {stopcheck = true;}
                    }

                oldtestscore = testscore;
                j++;
                } while(j+params.fractionsize < converted_seq2.size() && stopcheck == false);
            i++;
            } while(i+params.fractionsize < converted_seq1.size() && stopcheck == false);

        best_value.fractions1 = fractions1;
        best_value.fractions2 = fractions2;
        }

        if(best_values.size() > 0)
        {fractions1.push_back(best_values[0].fractions1[it]);
        fractions2.push_back(best_values[0].fractions2[it]);}

    fraction1 = fractions1[0];
    fraction2 = fractions2[0];
    best_value.best_fraction_rmsd = -1;
    partial_best_value.best_fraction_rmsd = -1;

    bool stopcheck = false;

        if(fraction1+params.fractionsize >= input1.matrix.size()
            || fraction2+params.fractionsize >= input2.matrix.size())
        {stopcheck = true;}

        //*initialize matrices based on fraction alignment
        for(size_t i = 0; i < params.fractionsize && stopcheck == false; i++)
        {
            for(size_t j = 0; j < input1.matrix[0].size(); j++)
            {
                if(i == 0 && j == 0)
                {start_poscount1 = input1.selected_indices[fraction1+i];
                start_poscount2 = input2.selected_indices[fraction2+i];}

            deviation.matrix1[i][j] = input1.matrix[fraction1+i][j];
            deviation.best_matrix2[i][j] = input2.matrix[fraction2+i][j];

                if(j == 0)
                {end_poscount1 = input1.selected_indices[fraction1+i];
                end_poscount2 = input2.selected_indices[fraction2+i];}
            }
        }

    //*pass chosen fractions for transformation calculations
    deviation = get_deviation.out(deviation, params, fraction1, fraction2, 0);

        if(deviation.rmsd < best_value.best_fraction_rmsd
            || best_value.best_fraction_rmsd == -1)
        {best_value.best_fraction_rmsd = deviation.rmsd;
        best_value.best_param_history1 = deviation.best_param_history1;
        best_value.best_param_history2 = deviation.best_param_history2;
        best_value.fraction1 = fraction1;
        best_value.best_fraction2 = fraction2;
        best_value.best_start_poscount1 = start_poscount1;
        best_value.best_start_poscount2 = start_poscount2;
        best_value.best_end_poscount1 = end_poscount1;
        best_value.best_end_poscount2 = end_poscount2;}

    ordered_best_values.push_back(best_value);

        if(best_values.size() > 0)
        {ordered_best_values[0].fractions1 = best_values[0].fractions1;
        ordered_best_values[0].fractions2 = best_values[0].fractions2;}

    return ordered_best_values;
    }
