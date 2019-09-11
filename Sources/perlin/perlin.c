//
//  noise_test.c
//  testingSwift
//
//  Created by menangen on 11.07.18.
//  Copyright (c) 2018 menangen. All rights reserved.
//
#import <stdio.h>
#import <stdlib.h>
#import <stdint.h>

#import <pthread.h>

#import "perlin.h"

#ifdef __APPLE__
    #import <sys/sysctl.h>
#else
    #import <sys/sysinfo.h>
#endif

#define NUM_OF_THREADS 4

uint16_t getNumCores() {
    uint16_t count;
#ifdef __APPLE__
    int nm[2];
    size_t len = 4;
    
    
    nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);
    
    if(count < 1) {
        nm[1] = HW_NCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);
        if(count < 1) { count = 1; }
    }
    
    printf("\n\tCPU: %i, %i \n\n", HW_NCPU, count);
#else
    
    printf("This system has %d processors configured and %d processors available.\n",
    get_nprocs_conf(), get_nprocs());
    
    count = get_nprocs();
#endif
    return count;
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
        
        //printf("[Allocate] data in address: %p \n", me);
        //printf("x = %i\n", me->x);
        
        pthread_create(&threads[i], NULL, processArray, threadParams);
        
        printf("[Creating] %i thread \n", i);
    }
    
    return getNumCores();
};
