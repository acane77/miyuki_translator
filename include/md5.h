/*! \file md5.h */

#ifndef md5_h
#define md5_h

// https://github.com/Zunawe/md5-c
// modified by Acane

#include <stdio.h>
#include <stdint.h>
#include "ac_common.h"

typedef struct{
    uint64_t size;        // Size of input in bytes
    uint32_t buffer[4];   // Current accumulation of hash
    uint8_t input[64];    // Input to be used in the next step
    uint8_t digest[16];   // Result of algorithm
}MD5Context;

ACANE_EXTERN_C_START

void md5Init(MD5Context *ctx);
void md5Update(MD5Context *ctx, const uint8_t *input, size_t input_len);
void md5Finalize(MD5Context *ctx);
void md5Step(uint32_t *buffer, uint32_t *input);

uint8_t* md5String(const char *input);
uint8_t* md5File(FILE *file);

ACANE_EXTERN_C_END

#endif /* md5_h */
