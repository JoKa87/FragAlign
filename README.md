# FragXAlign
Tool for protein structure alignment based on fragment-wise comparison

## Scope
The alignment of protein structures is a prerequisite for a meaningful comparison of structural features.
**FragXAlign** was created to conduct pair-wise protein structure alignments, also for large datasets, and is based on the detection of best-aligning core fragments.

## Methodology
**FragXAlign** alignment comprises the following steps:
- select coordinates (typically *CA*)
- detect core fragments based on substitution matrices
- conduct pre-alignment based on averaged coordinates
- conduct sequence-wise alignment
- apply transformations to whole set of selected coordinates and calculate statistics
- apply transformations to all coordinates and print results

## Implementation
**FragXAlign** was developed in C++11 and built using mingw32-g++ compiler.
The executable runs on a Windows10 environment and was tested on two different machines.

## How to run
All parameters as well as data location can be specified using the *params.txt* file in the main directory.
For non-specified parameter, default values are used. The parameters are explained in the following:

**basic settings**
* *data_dir* specifies the data directory
* *run_dir* specifies the directory for data output and shall be identical with the main directory
* *filter* if all structure files within the data directory shall be selected, a file extension can be classified, e.g. *".pdb"*
* *verbosity* specifies console output, chose
     * *0* for none,
     * *1* for several console outputs like per-alignment performance and RMSD and PDB exceptions,
     * *2* for console output of per-alignment performance and RMSD
* *log* boolean that specifies logfile creation
* *multithreading* boolean that specifies run in multiple threads to speed up
* *print_pdb* boolean that specifies whether aligned structure shall be printed to file

**settings for PDB input and alignment calculation**
* *target_coords* specifies a list of atom types, e.g. *{CA}* *
* *matrix* specifies substitution matrix, up to now *PAM250* and *BLOSUM62* are included.

**settings for determination of fraction alignment**
* *fraction_by_threshold* if set to true, fractions are collected based on threshold
* *score_threshold* specifies score threshold if fraction_by_threshold is true,
     note that subsitution matrices are normalized (minimum is set to *0*, maximum is set to *1*)
* *fractions* specifies the no. fractions to be extracted*
* *fractionsize* specifies the medium size of the selected fractions (is automatically lowered with respect to input sizes)*
* *fractionsizes* specifies the no. of different fractions to be calculated (default is 40, 45, 50, 55, 60, if sequences fulfill size restriction*
* *fraction_step* specifies the gap between selected fraction (in order to avoid over-sampling of single region)

**basic settings for transformation calculations**
* *boxwise_align_it* specifies the no. of iterations for first-stage alignment*
* *boxwise_align_steps* specifies the stepsize for iterations for first-stage alignment*
* *seqwise_align_it* specifies the no. of iterations for second-stage alignment*
* *seqwise_align_steps* specifies the stepsize of iterations for second-stage alignment*

**settings for RMSD calculation**
* *rmsd_mode* available modes for RMSD calculation are *BY_MINIMUM* and *BY_SEQUENCE*
    * *BY SEQUENCE* is recommended
* *final_rmsd_mode* specifies how the RMSD is calculated during the final evaluation of the resulting alignment, available modes are:
     - *BY_MINIMUM* by which the minimum distance is calculated for each position while redundant pairs can occur
     - *BY_SEQUENCE* by which the distances are calculated sequence-wise
     - *BY_COMBINATION* by which minimum distances are determined but redundancies are avoided,
     in my estimation this allows the most accurate estimation for quality assessment
* *rmsd_cutoff* specifies the threshold below which two positions are considered to be aligned and thus included in RMSD calculation


\*these parameters are critical for calculation time

## Output
If *print_pdb* is true, the aligned files are printed as separate files and can be viewed with common PDB viewers, e.g. PyMol.
Additionally, the *alignment_stats.txt* file is printed, which contains information about the calculations
- if multiple alignments were conducted, average and standard error of RMSD and coverage are given along with the average calculation time
- RMSD, coverage and calculation time are given for each structure alignment
- the used parameters are printed for a comprehensive documentation

## Example
To illustrate the usage of **FragXAlign**, the following exaple is given.
The input and output files can be found in the *test files* sub-directory.
- input files: *pdb1a0f.ent, pdb1lpy.ent, pdb107I.ent* and *params.txt*
- output files:
  - alignment pair 1: *1A0F_1LPY_aligned.pdb*, *1LPY_1A0F_aligned.pdb*
  - alignment pair 2: *1A0F_107L_aligned.pdb*, *107L_1A0F_aligned.pdb*
  - alignment pair 3: *1LPY_107L_aligned.pdb*, *107L_1LPY_aligned.pdb*
  *alignment_stats.txt*

The latter summarizes the calculation results:
     evaluation results. avg. rmsd: 2.46, mean error: 1.359

     avg coverage: 0.4499, mean error: 0.4124

     avg duration: 2131, mean error: 217.7

Next, the results are given for each run. Here, the no. of fraction sizes was set to *5*:

     107L-1A0F, RMSD: 3.371, coverage: 0.2444, duration: 2379
     
     107L-1LPY, RMSD: 0.8972, coverage: 0.9247, duration: 2040

     1A0F-1LPY, RMSD: 3.111, coverage: 0.1806, duration: 1973

If, the no. of fraction sizes is reduced to just *1*, performance is significantly enhanced.

     107L-1A0F, RMSD: 3.131, coverage: 0.14, duration: 686
     
     107L-1LPY, RMSD: 0.8972, coverage: 0.9247, duration: 602

     1A0F-1LPY, RMSD: 3.19, coverage: 0.1438, duration: 702

Lastly, the used parameters are listed (not shown here).

The obtained alignment for the 107L-1LPY can be viewed in a PDB viewer (example picture was generated using PyMol Version 2.1.1. Schrödinger, LLC.).

![see structure alignment](https://github.com/JoKa87/FragAlign/tree/main/testfiles/1LPY_1071_alignment.png)
