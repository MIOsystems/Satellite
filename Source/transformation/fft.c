/*
 * fft.c
 *
 *  Created on: 14 May 2021
 *      Author: Patrick
 */

#include <include/transformation/fft.h>

#include <math.h>
#include <complex.h>

#include <stdlib.h>

u8 buffOverFlowCheck = 0;

void fftCreate(FFT_t* fft)
{
	memset(fft->raw, 0, sizeof(f32) * N);
	memset(fft->buffIn, 0, sizeof(f32) * N);
	memset(fft->buffOut, 0, sizeof(f32) * N);
	memset(fft->out, 0, sizeof(f32) * N);
}

u8 fftUpdate(FFT_t* fft, f32 data)
{
	if(buffOverFlowCheck >= N)
	{
		buffOverFlowCheck = 0;
		return;

	}
	fft->raw[buffOverFlowCheck] = data;
	buffOverFlowCheck++;

//
//	fftCycle(fft->buffIn, fft->buffOut, N, 1);
//
//	for(size_t i = 0; i < N; i++)
//	{
//		if (!cimag(fft->buffIn[i]))
//		{
//			fft->out[i] = crealf(fft->buffOut[i]);
//		}
//		else
//		{
//
//		}
//	}
	return FFT_SUCCESS;

}

void fftCycle(f32 *buff, f32 *out, i32 n , i32 step)
{
	if(step < n) {
		fftCycle(out, buff, n, step * 2);
		fftCycle(out + step, buff + step, n, step * 2);

		for (int i = 0; i < n; i += 2 * step) {
			cplxf t = cexp(-I * M_PI * i / n) * out[i + step];
			buff[i / 2]     = out[i] + t;
			buff[(i + n)/2] = out[i] - t;
		}
	}

}

