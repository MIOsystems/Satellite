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
	if (fft->state != FFT_BUFFER_READY)
	{
		return FFT_NOT_READY;
	}

	fftStart(fft);

	return FFT_SUCCESS;
}

void fftStart(FFT_t* fft)
{
	// copying input to a complex array
	for (int i = 0; i < N_DEF; i++)
	{
		fft->buffOut.x[i] = fft->buffIn.x[i];
		fft->buffOut.y[i] = fft->buffIn.y[i];
		fft->buffOut.z[i] = fft->buffIn.z[i];
	}

	fftTransform(fft->buffIn.x, fft->buffOut.x, N_DEF, 1);
	fftTransform(fft->buffIn.y, fft->buffOut.y, N_DEF, 1);
	fftTransform(fft->buffIn.z, fft->buffOut.z, N_DEF, 1);
}

void fftTransform(cplxf *in, cplxf *out, u32 N, u32 step)
{
	// At the lowest level pass through (delta T=0 means no phase).
	if (N == 1)
	{
		out[0] = in[0];
		return;
	}

	// Cooley-Tukey: recursively split in two, then combine beneath.
	fftTransform(in, out, N / 2, 2 * step);
	fftTransform(in + step, out + N / 2, N / 2, 2 * step);
	cplxf t;
	for (u32 k = 0; k < N / 2; k++)
	{
		t = out[k];
		out[k] = t + cexpf(-2 * PI * I * k / N) * out[k + N / 2];
		out[k + N / 2] = t - cexpf(-2 * PI * I * k / N) * out[k + N / 2];
	}
}

void fftAddData(FFT_t *fft, vec3f data)
{
	if (buffOverFlowCheck < N_DEF)
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

