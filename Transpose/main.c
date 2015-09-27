//
//  main.c
//  
//
//  This version of uses 2-D arrays to operate on input images
//
//  Created by Hank Lee on 7/30/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "transpose.h"

int main(int argc, const char * argv[])
{
    int fd_in;
    int fd_out;
    
    ssize_t rd_sz;
    
    uint32_t width;
    uint32_t height;
    uint32_t frame_sz;
    
    uint8_t *frame;
    uint8_t *buffer;
    
    char *cp;
    char output_file_name[256];

    
    if (argc < 4)
    {
        printf("useage: %s [input_file] [width] [height]\n", argv[0]);
        
        return -1;
    }
    

    rd_sz       = 0;
    width       = 0;
    height      = 0;
    frame_sz    = 0;
    frame       = NULL;
    buffer      = NULL;
    cp          = NULL;
    memset(output_file_name, 0, sizeof(output_file_name));
    
    // get input file name from comand line
    fd_in = open(argv[1], O_RDONLY);
    
    // specify output file name
    cp = strchr(argv[1], '.');
    strncpy(output_file_name, argv[1], cp - argv[1]);
    strcat(output_file_name, "_nv12");
    strcat(output_file_name, cp);
    
    fd_out  = open(output_file_name, O_WRONLY | O_CREAT, S_IRUSR);
    
    width   = atoi(argv[2]);
    height  = atoi(argv[3]);
    
    frame_sz = width * height;
    
    frame = malloc(frame_sz * 3 / 2);
    buffer = malloc(frame_sz / 2);
    
    const uint8_t (*y_src)[width];
    const uint8_t (*uv_src)[width * height / 4];
          uint8_t (*uv_dst)[2];
          
    
    y_src = (const uint8_t (*)[width]) frame;
    uv_src = y_src + height;
    uv_dst = (uint8_t (*)[2]) buffer;
    
    printf("Processing: ");
    
    while (1)
    {
        rd_sz = read(fd_in, frame, frame_sz * 3 / 2);
        
        if (rd_sz == frame_sz * 3 / 2)
        {
            write(fd_out, y_src, frame_sz);
            
            transpose
            (
                width,
                height,
                uv_dst,
                uv_src
            );
            
            write(fd_out, buffer, frame_sz / 2);
        }
        else
        {
            break;
        }
        fputc('.', stdout);
        fflush(stdout);
    }
  
    close(fd_in);
    close(fd_out);
    
    printf("Done\n");
    printf("Output file: %s\n", output_file_name);
    
    return 0;
}
