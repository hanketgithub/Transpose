//
//  transpose.h
//  Transpose
//
//  Created by Hank Lee on 7/30/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#ifndef ___transpose_h____
#define ___transpose_h____


extern int transpose
(
 const uint32_t    width,
 const uint32_t    height,
 uint8_t     dst_u_et_v[width * height / 4][2],
 const uint8_t     src_u_et_v[2][width * height / 4]
);


#endif
