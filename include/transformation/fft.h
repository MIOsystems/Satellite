/*
 * fft.h
 *
 *  Created on: 12 May 2021
 *      Author: Patrick
 */

#ifndef FFT_H_
#define FFT_H_

#include <include/util/types.h>
#include <include/util/math_utility.h>

#define N 32
#define K N - 1

typedef enum
{
	FFT_SUCCESS = 0U,
	FFT_INPUT_FULL,
	FFT_NOT_READY,
} FFTStatus_e;

typedef struct
{
	cplxf buffIn[N];
	cplxf buffOut[N];
	f32 out[N];
	u8 inputCounter;
} FFT_t;

void fftCreate(FFT_t* fft);
u8 fftAddChannels(FFT_t* fft, f32 ax, f32 ay, f32 az);
u8 fftUpdate(FFT_t* fft, f32 ax, f32 ay, f32 az);
void fftCycle(f32 *buff, f32 *out, i32 n, i32 step);


#endif /* FFT_H_ */
