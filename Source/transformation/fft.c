/*
 * fft.c
 *
 *  Created on: 14 May 2021
 *      Author: Patrick
 */

#include <include/transformation/fft.h>

#include <stdio.h>
#include <math.h>
#include <string.h>

u16 buffOverFlowCheck = 0;

void fftCreate(FFT_t* fft)
{
	memset(fft->buffIn.x, 0, sizeof(cplxf) * N_DEF);
	memset(fft->buffIn.y, 0, sizeof(cplxf) * N_DEF);
	memset(fft->buffIn.z, 0, sizeof(cplxf) * N_DEF);
	memset(fft->buffOut.x, 0, sizeof(cplxf) * N_DEF);
	memset(fft->buffOut.y, 0, sizeof(cplxf) * N_DEF);
	memset(fft->buffOut.z, 0, sizeof(cplxf) * N_DEF);
	fft->state = FFT_CREATING_BUFFER;
}

u8 fftUpdate(FFT_t* fft)
{
	if(fft->state != FFT_BUFFER_READY)
	{
		return FFT_NOT_READY;
	}

	fftStart(fft);
	return FFT_SUCCESS;
}

void fftStart(FFT_t* fft)
{
	// copying input to a complex array
	for(int i = 0; i < N_DEF; i++)
	{
		fft->buffOut.x[i] = fft->buffIn.x[i];
		fft->buffOut.y[i] = fft->buffIn.y[i];
		fft->buffOut.z[i] = fft->buffIn.z[i];
	}

	fftRadix2(fft->buffIn.x, fft->buffOut.x, N_DEF, 1);
	fftRadix2(fft->buffIn.y, fft->buffOut.y, N_DEF, 1);
	fftRadix2(fft->buffIn.z, fft->buffOut.z, N_DEF, 1);
}


void fftRadix2(f32* x, cplxf * X, u32 N, u32 s)
{
    unsigned int k;
    double complex t;

    // At the lowest level pass through (delta T=0 means no phase).
    if (N == 1) {
        X[0] = x[0];
        return;
    }

    // Cooley-Tukey: recursively split in two, then combine beneath.
    fftRadix2(x, X, N/2, 2*s);
    fftRadix2(x+s, X + N/2, N/2, 2*s);

    for (k = 0; k < N/2; k++) {
        t = X[k];
        X[k] = t + cexpf(-2 * PI * I * k / N) * X[k + N/2];
        X[k + N/2] = t - cexpf(-2 * PI * I * k / N) * X[k + N/2];
    }
}

void fftAddData(FFT_t *fft, vec3f data)
{
	if(buffOverFlowCheck < N_DEF)
	{
		fft->buffIn.x[buffOverFlowCheck] = data.x / 9.81f;
		fft->buffIn.y[buffOverFlowCheck] = data.y / 9.81f;
		fft->buffIn.z[buffOverFlowCheck] = data.z / 9.81f;
		buffOverFlowCheck++;
		return;
	}
	buffOverFlowCheck = 0;
	fft->state = FFT_BUFFER_READY;
}

