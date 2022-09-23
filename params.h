#ifndef PARAMS_H
#define PARAMS_H
#include <string>
#include <vector>

using namespace std;

struct Params
{
////*basic settings
//*directory for input files
string data_dir = "D:\\Eigene Dateien\\Programming\\C++\\function prediction\\align37\\";
//*directory for parameter file and output files
string run_dir = "D:\\Eigene Dateien\\Programming\\C++\\function prediction\\align37\\";
//string run_dir = "C:\\Users\\Administrator\\Documents\\programs\\alignment\\";
//*file tag for automated file selection
string filter = ".pdb";
//string run_dir = "C:\\Users\\Administrator\\Documents\\programs\\alignment\\";
//*level 0: no console output but progress status
//*level 1: several console outputs like per-alignment performance and RMSD and PDB exceptions
//*level 2: console output of per-alignment performance and RMSD
int verbosity = 1;
bool log = false;
bool multithreading = false;
bool print_pdb = false;
size_t threads = 6;

////*settings for PDB input and alignment calculation
//*target coordinates marked by atom identifier
vector<string> target_coords {"CA"};
//*substitution matrices to be selected: "PAM250", "BLOSUM62", and "ID"
//*"ID" mainly for testing purpose, perfect matches are set to 1, all other matches are set to 0
string matrix = "PAM250";

////*settings for determination of fraction alignment
//*if set to false, fractions are collected based on threshold (specified by "score_threshold")
bool fraction_by_threshold = false;
float score_threshold = 0.5;
//*no. fractions to be extracted from the sequences
size_t fractions = 20;
//*medium size for fractions
size_t fractionsize = 50;
//*no. of different fractions to be calculated (default is 40, 45, 50, 55, 60, if sequences fulfill size restriction
size_t fractionsizes = 5;
//*gap between selected fraction (in order to avoid over-sampling of single region)
size_t fraction_step = 10;

////*basic settings for transformation calculations
string method1 = "SECTION";
string method2 = "PAIRWISE";
//*threshold for early stopping
float rmsd_threshold = 2.0;
float rmsd_threshold2 = 2.0;
//*no. of non-topping transformation to conduct early-stopping
size_t max_total_stopcount = 10;

////*settings for box-wise transformations
size_t boxwise_align_it = 10;
size_t boxwise_align_steps = 5;
size_t max_depth_stopcount = 2;

////*settings for sequence-wise transformations
size_t seqwise_align_it = 3;
size_t seqwise_align_steps = 5;

////*settings for RMSD calculation
//*available modes for RMSD calculation are "BY_MINIMUM" and "BY_SEQUENCE"
string rmsd_mode = "BY_SEQUENCE";
string final_rmsd_mode = "BY_SEQUENCE";
//*indicates the no. of steps for local minimum search
size_t comb_steps = 12;
size_t rmsd_counts = 10;
//*only residue pairs < cutoff considered, put "-1" to switch off
float rmsd_cutoff = 3.0;
};

#endif
