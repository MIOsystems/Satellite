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
#include <include/data/vector.h>

#define N_DEF 128  // SAMPLE RATE PER 1 SECONDS
//#define K N_DEF - 1

typedef enum
{
	FFT_SUCCESS = 0U,
	FFT_INPUT_FULL,
	FFT_NOT_READY,
} FFTStatus_e;

typedef enum
{
	FFT_CREATING_BUFFER,
	FFT_BUFFER_READY,
	FFT_SENDING,
} FFTState_e;

// Complex float
typedef struct
{
	cplxf x[N_DEF];
	cplxf y[N_DEF];
	cplxf z[N_DEF];
} Vec3fi;

typedef struct
{
	Vec3fi buffIn;
	Vec3fi buffOut;
	FFTState_e state;
} FFT_t;

void fftCreate(FFT_t* fft);
u8 fftUpdate(FFT_t* fft);
void fftAddData(FFT_t *fft, vec3f data);
void fftStart(FFT_t* fft);
void fftTransform(cplxf *in, cplxf *out, u32 N, u32 step);
void fftCreatePacket(FFT_t *fft, f32 *x, f32 *y, f32 *z);


#endif /* FFT_H_ */
