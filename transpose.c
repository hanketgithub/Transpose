//
//  transpose.c
//  Transpose
//
//  This version of algorithm uses 2-D arrays to operate.
//
//  Created by Hank Lee on 7/30/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

struct timeval  tv1, tv2;

int transpose
(
  const uint32_t    width,
  const uint32_t    height,
        uint8_t     dst_u_et_v[width * height / 4][2],
  const uint8_t     src_u_et_v[2][width * height / 4]
)
{
    int i, j;
    
    gettimeofday(&tv1, NULL);

    #pragma omp parallel for
    for (i = 0; i < 2; i++)
    {
        #pragma omp parallel for
        for (j = 0; j < width * height / 4; j++)
        {          
            dst_u_et_v[j][i] = src_u_et_v[i][j];
        }
    }

    gettimeofday(&tv2, NULL);
    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));
         
    return 0;
}
