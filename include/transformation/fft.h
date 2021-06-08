/*
 * fft.h
 *
 *  Created on: 12 May 2021
 *      Author: Patrick
 */

#ifndef FFT_H_
#define FFT_H_

#include <include/math/vector.h>
#include <include/util/types.h>
#include <include/util/math_utility.h>
#include <include/util/error.h>
#include <Libraries/fft/kiss_fft.h>

#define FFT_N	256

typedef enum
{
	FFT_SUCCESS = 0U,
	FFT_INPUT_FULL,
	FFT_NOT_READY,
} FFTStatus_e;

typedef struct
{
	kiss_fft_cpx x[FFT_N];
	kiss_fft_cpx y[FFT_N];
	kiss_fft_cpx z[FFT_N];
} CmplxVec3fArray;

typedef struct
{
	CmplxVec3fArray bufferIn;
	CmplxVec3fArray bufferOut;
	kiss_fft_cfg cfg;
	u16 counter;
	FFTState_e state;
} FFT_t;

void fftCreate(FFT_t* fft);
u8 fftUpdate(FFT_t* fft);
void fftAddData(FFT_t *fft, Vec3f_t data);
void fftStart(FFT_t* fft);

#endif /* FFT_H_ */
