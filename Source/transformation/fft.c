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
	memset(fft->bufferIn.x, 0, sizeof(CmplxVec3fArray));
	memset(fft->bufferIn.y, 0, sizeof(CmplxVec3fArray));
	memset(fft->bufferIn.z, 0, sizeof(CmplxVec3fArray));
	fft->counter = 0;
	fft->state = FFT_CREATING_BUFFER;
	fft->cfg = kiss_fft_alloc(FFT_N, 0, NULL, NULL);
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

void fftAddData(FFT_t *fft, vec3f data)
{
	if (fft->counter < FFT_N)
	{
		fft->bufferIn.x[fft->counter].r = data.x / GRAVITY_CONST;
		fft->bufferIn.x[fft->counter].i = 0;
		fft->bufferIn.y[fft->counter].r = data.y / GRAVITY_CONST;
		fft->bufferIn.y[fft->counter].i = 0;
		fft->bufferIn.z[fft->counter].r = data.z / GRAVITY_CONST;
		fft->bufferIn.z[fft->counter].i = 0;
		fft->counter++;
		return;
	}
	fft->counter = 0;
	fft->state = FFT_BUFFER_READY;
}
