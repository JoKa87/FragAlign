#include "rotate_by_pairs.h"


    static float deg_(float rad)
    {rad = (rad/3.1415926) * 180;
    return rad;}


    vector<vector<float> > Rotate_by_pairs::out(vector<vector<float> >& matrix1, vector<vector<float> >& matrix2,
                                                vector<vector<float> >& param_history, const Params& params, const size_t& it)
    {
    Cross_product cross_product; Get_stats get_stats; Multiply multiply;
    Rotate_by_axis rotate_by_axis; Shift shift;
    Data dummy1, dummy2; Stats stats;

    vector<vector<float> > rotation_matrix_ccw (3, (vector<float> (3, 0)));
    vector<vector<float> > rotation_matrix_clw (3, (vector<float> (3, 0)));

    vector<vector<float> > best_rotated_matrix2 = matrix2;
    vector<vector<float> > rotated_matrix2 = matrix2;
    vector<float> avg_coords (3, 0);
    vector<float> rot_ax;
    size_t coords_sum = 0;
    float rmsd, best_rmsd = -1, best_angle;

    vector<size_t> paired_indices;

        for(size_t i = it; i < matrix1.size(); i++)
        {paired_indices.push_back(i);}

        for(size_t i = 0; i < it; i++)
        {paired_indices.push_back(i);}

        for(size_t mode = 0; mode < 1; mode++)
        {
            for(size_t i = 0; i < paired_indices.size(); i++)
            {
            float x1 = matrix1[paired_indices[i]][0];
            float x2 = matrix1[paired_indices[i]][1];
            float x3 = matrix1[paired_indices[i]][2];
            float y1 = best_rotated_matrix2[paired_indices[i]][0];
            float y2 = best_rotated_matrix2[paired_indices[i]][1];
            float y3 = best_rotated_matrix2[paired_indices[i]][2];
            vector<vector<float> > y_ext {{y1, y2, y3}};

                if(mode == 0
                    && sqrt((pow(x1,2) + pow(x2,2) + pow(x3,2)))*sqrt((pow(y1,2) + pow(y2,2) + pow(y3,2))) != 0
                    && (x1*y1+x2*y2+x3*y3) / (sqrt((pow(x1,2) + pow(x2,2) + pow(x3,2)))*sqrt((pow(y1,2) + pow(y2,2) + pow(y3,2)))) <= 1
                    && (x1*y1+x2*y2+x3*y3) / (sqrt((pow(x1,2) + pow(x2,2) + pow(x3,2)))*sqrt((pow(y1,2) + pow(y2,2) + pow(y3,2)))) >= -1)
                {
                //*determine rotational axis
                float angle = acos((x1*y1+x2*y2+x3*y3) / (sqrt((pow(x1,2) + pow(x2,2) + pow(x3,2)))*sqrt((pow(y1,2) + pow(y2,2) + pow(y3,2)))));
                rot_ax = cross_product.out(matrix1[paired_indices[i]], best_rotated_matrix2[paired_indices[i]]);

                //*create rotation matrix for clockwise and counter-clockwise rotation
                rotation_matrix_ccw = rotate_by_axis.out(rotation_matrix_ccw, rot_ax, deg_(angle), false);
                rotation_matrix_clw = rotate_by_axis.out(rotation_matrix_clw, rot_ax, -deg_(angle), false); //radians(360)

                //*conduct matrix multiplication for clockwise and counter-clockwise rotation
                vector<vector<float> > rotated_matrix_ccw = multiply.out(y_ext, rotation_matrix_ccw);
                vector<vector<float> > rotated_matrix_clw = multiply.out(y_ext, rotation_matrix_clw);

                //*compare distances and choose lowest
                float dist_ccw = sqrt(pow((rotated_matrix_ccw[0][0]-x1),2)
                                    + pow((rotated_matrix_ccw[0][1]-x2),2)
                                    + pow((rotated_matrix_ccw[0][2]-x3),2));

                float dist_clw = sqrt(pow((rotated_matrix_clw[0][0]-x1),2)
                                    + pow((rotated_matrix_clw[0][1]-x2),2)
                                    + pow((rotated_matrix_clw[0][2]-x3),2));

                    if(dist_ccw <= dist_clw)
                    {rotated_matrix2 = multiply.out(best_rotated_matrix2, rotation_matrix_ccw);
                    best_angle = deg_(angle);}

                    else if(dist_ccw > dist_clw)
                    {rotated_matrix2 = multiply.out(best_rotated_matrix2, rotation_matrix_clw);
                    best_angle = -deg_(angle);}
                }

            stats = get_stats.out(best_rmsd, params, dummy1, dummy2, matrix1, rotated_matrix2, 0, 0, params.rmsd_mode, -1);

                if((best_rmsd == -1 || stats.rmsd < best_rmsd) && rot_ax.size() == 3)
                {best_rmsd = stats.rmsd;
                best_rotated_matrix2 = rotated_matrix2;
                param_history[(int) param_history[0][0]+1][0] = 3;
                param_history[(int) param_history[0][0]+1][1] = best_angle;
                param_history[(int) param_history[0][0]+1][2] = rot_ax[0];
                param_history[(int) param_history[0][0]+1][3] = rot_ax[1];
                param_history[(int) param_history[0][0]+1][4] = rot_ax[2];
                param_history[0][0]++;}
            }
        }

    return best_rotated_matrix2;
    }

