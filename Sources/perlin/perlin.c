//
//  noise_test.c
//  testingSwift
//
//  Created by menangen on 11.07.18.
//  Copyright (c) 2018 menangen. All rights reserved.
//
#import "perlin.h"

#include <unistd.h>

#define NUM_OF_THREADS 4

uint16_t getNumCores() {
    long count;
#ifdef _SC_NPROCESSORS_ONLN
    /* Many systems using sysconf() */
    count = sysconf(_SC_NPROCESSORS_ONLN);
#else
    /* IRIX */
    count = sysconf(_SC_NPROC_ONLN);
#endif

    return (uint16_t)count;
}

struct perlinData
{
    int x;
    uint16_t height, width;
};

void *processArray(void* arg)
{
    
    struct perlinData* me = (struct perlinData*)arg;
    
    //printf("..Get int in address: %p \n", arg);
    printf("-> Spawn thread %i \n-> Width: %i, Height: %i \n", me->x, me->width, me->height);
    
    pthread_exit(NULL);
}

uint16_t get_noise() {
    pthread_t threads[NUM_OF_THREADS];
    
    for (int i = 0; i < NUM_OF_THREADS; i++) {
        
        struct perlinData* threadParams = malloc( sizeof(struct perlinData) );
        
        threadParams -> height = 300;
        threadParams -> width = 650;
        
        threadParams -> x = 1 + i;
        /*
        printf("[Allocate] data in address: %p \n", me);
        printf("x = %i\n", me->x);
        */
        pthread_create(&threads[i], NULL, processArray, threadParams);
        
        printf("[Creating] %i thread \n", i);
    }
    
    return getNumCores();
};

int8_t isAVX(void) {
    static
    int8_t
    CPU_FEATURE = -1;
    
    __builtin_cpu_init();
    
    printf("CPU supports ");
    
    if (CPU_SSE2) {
        printf("SSE 2 ");
    }
    if (CPU_SSE3) {
        printf("SSE 3 ");
    }
    
    if (CPU_SSE41) {
        printf("SSE 4.1 ");
        CPU_FEATURE = 0;
    }
    if (CPU_SSE42) {
        printf("SSE 4.2 ");
        CPU_FEATURE = 1;
    }
    if (CPU_AVX) {
        printf("AVX ");
        CPU_FEATURE = 2;
    }
    if (CPU_AVX2) {
        printf("AVX2 ");
        CPU_FEATURE = 3;
    }
    if (CPU_AVX512) {
        printf("AVX512 (!)");
        CPU_FEATURE = 4;
    }
    printf("\n");
    return CPU_FEATURE;
}
