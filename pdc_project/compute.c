#include "compute.h"
#include <pthread.h>
#include <omp.h>
#include <stdlib.h>

#define NUM_THREADS 4

// Define the global variables here
float* inventory = NULL;
int current_num_items = 0;

// --- 1. LINEAR APPROACH ---
void process_linear() {
    for (int i = 0; i < current_num_items; i++) {
        inventory[i] = (inventory[i] * 1.05) + (inventory[i] * 0.18);
    }
}

// --- 2. PTHREADS APPROACH ---
typedef struct {
    int start_index;
    int end_index;
} ThreadData;

void* process_chunk(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->start_index; i < data->end_index; i++) {
        inventory[i] = (inventory[i] * 1.05) + (inventory[i] * 0.18);
    }
    pthread_exit(NULL);
}

void process_pthreads() {
    pthread_t threads[NUM_THREADS];
    ThreadData t_data[NUM_THREADS];
    int chunk_size = current_num_items / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        t_data[i].start_index = i * chunk_size;
        t_data[i].end_index = (i == NUM_THREADS - 1) ? current_num_items : (i + 1) * chunk_size;
        pthread_create(&threads[i], NULL, process_chunk, (void*)&t_data[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

// --- 3. OPENMP APPROACH ---
void process_openmp() {
    #pragma omp parallel for num_threads(NUM_THREADS)
    for (int i = 0; i < current_num_items; i++) {
        inventory[i] = (inventory[i] * 1.05) + (inventory[i] * 0.18);
    }
}