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

void fftCreate(FFT_t* fft)
{
	memset(&fft->bufferIn, 0, sizeof(CmplxVec3fArray));
	fft->counter = 0;
	fft->state = FFT_CREATING_BUFFER;
	fft->cfg = kiss_fft_alloc(FFT_N, 0, NULL, NULL);
	fftHannWindowFunction(fft);
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
	// library call to create fft of input buffer and store it in output buffer
	kiss_fft(fft->cfg, fft->bufferIn.x, fft->bufferOut.x);
	kiss_fft(fft->cfg, fft->bufferIn.y, fft->bufferOut.y);
	kiss_fft(fft->cfg, fft->bufferIn.z, fft->bufferOut.z);
}

void fftAddData(FFT_t *fft, Vec3f_t data)
{
	if (fft->counter < FFT_N)
	{
		fft->bufferIn.x[fft->counter].r = fft->hann[fft->counter] * (data.x / GRAVITY_CONST);
		fft->bufferIn.x[fft->counter].i = 0;
		fft->bufferIn.y[fft->counter].r = fft->hann[fft->counter] * (data.y / GRAVITY_CONST);
		fft->bufferIn.y[fft->counter].i = 0;
		fft->bufferIn.z[fft->counter].r = fft->hann[fft->counter] * (data.z / GRAVITY_CONST);
		fft->bufferIn.z[fft->counter].i = 0;
		fft->counter++;
		return;
	}
	fft->counter = 0;
	fft->state = FFT_BUFFER_READY;
}

void fftHannWindowFunction(FFT_t *fft)
{
	f32 hann = 0;
	for(f32 i = 0; i < FFT_N; i++)
	{
		if(i == 128)
		{
			f32 temp = 2 * M_PI * (i / FFT_N);
			hann = 0.5f * (1- cos(temp));
		}
		hann = 0.5f * (1- cos(2 * M_PI * (i / FFT_N)));
		fft->hann[(int) i] = hann;
	}
}
