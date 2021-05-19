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

void fftCreate(FFT_t* fft)
{
	for(u32 i = 0; i < N; i++)
	{
		fft->buffIn[i] = 0;
		fft->buffOut[i] = 0;
	}
	fft->inputCounter = 0;
}

u8 fftAddChannels(FFT_t* fft, f32 ax, f32 ay, f32 az)
{
	if(fft->inputCounter == N)
	{
		return FFT_INPUT_FULL;
	}
	fft->buffIn[fft->inputCounter]= ax + ay + az;
	fft->inputCounter++;
	return FFT_SUCCESS;

}

u8 fftUpdate(FFT_t* fft, f32 ax, f32 ay, f32 az)
{
	FFTStatus_e status = FFT_SUCCESS;
	status = fftAddChannels(fft, ax, ay, az);
	// if its not full skip the rest
	if(status == FFT_SUCCESS)
	{
		return FFT_NOT_READY;
	}

	// copying
	for(size_t i = 0; i < N; i++)
	{
		fft->buffOut[i] = fft->buffIn[i];
	}

	fftCycle(fft->buffIn, fft->buffOut, N, 1);

	for(size_t i = 0; i < N; i++)
	{
		if (!cimag(fft->buffIn[i]))
		{
			fft->out[i] = crealf(fft->buffOut[i]);
		}
		else
		{

		}
	}
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

