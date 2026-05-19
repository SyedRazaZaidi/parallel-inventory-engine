#ifndef COMPUTE_H
#define COMPUTE_H

// Declare global variables as "extern" so both files can share them
extern float* inventory;
extern int current_num_items;

// Declare the computation functions
void process_linear();
void process_pthreads();
void process_openmp();

#endif