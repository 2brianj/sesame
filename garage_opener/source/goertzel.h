/*
 * goertzel.h
 *
 *  Created on: Mar 20, 2014
 *      Author: rick
 */

#ifndef GOERTZEL_H_
#define GOERTZEL_H_

#include "arm_math.h"
#include "tim.h"
#include "ring_buffer.h"

// Frequencies seem to be half?
//#define ZERO_FREQ 2400
#define ZERO_FREQ 5000
//#define ONE_FREQ 1200
//#define ONE_FREQ 2400
//#define POSITIVELIMIT 0.3
//#define NEGATIVELIMIT -0.3
//#define UPPERBOUND 	0.15
//#define LOWERBOUND 	-0.15
//#define BPS	1200
//#define BITLENGTH	SAMPLERATE/BPS // Sample rate divided by bits per second
//#define NUMFILTERS 	16
#define COEFF_ZERO (2 * arm_cos_f32(2*PI*ZERO_FREQ/SAMPLERATE))
//#define COEFF_ONE (2 * arm_cos_f32(2*PI*ONE_FREQ/SAMPLERATE))
//#define COEFF_ZERO (2 * arm_cos_f32(2*PI*ZERO_FREQ/12000))
//#define COEFF_ONE (2 * arm_cos_f32(2*PI*ONE_FREQ/12000))

/* prototype functions */
float32_t tandem_RT_zero_goertzel_filter(int16_t sample, uint8_t reset);
int16_t dc_offset_removal_filter(uint16_t sample, uint16_t lastSample, int32_t *pShiftedFilter);

#endif /* GOERTZEL_H_ */
