/*
 * goertzel.c
 *
 *  Created on: Mar 20, 2014
 *      Author: rick
 */
#include "goertzel.h"

/*
 * Zero Frequency -- Real time goertzel filter, two filters, one runs at a time
 * 		while the other is used for history
 *      @params: sample - Next sample from data collected
 *               freq - Frequency of the desired data
 *               sample_rate - Sample rate of the ADC
 *               reset - Number of results stored before switching filters
 *      @return: Normalized total power at each point
 */
float32_t tandem_RT_zero_goertzel_filter(int16_t sample, uint8_t reset) {
    float32_t power = 0.0;
    static float32_t s_prev[2] = {0.0, 0.0};
    static float32_t s_prev2[2] = {0.0, 0.0};
    static float32_t total_power[2] = {0.0, 0.0};
    static uint16_t N = 0;
    static uint16_t n[2] = {0,0};

    //float32_t coeff = 2 * arm_cos_f32(2*PI*ZERO_FREQ/sample_rate);
    float32_t s = 0.0;

    uint8_t active = 0;

    // First filter
    s = sample + COEFF_ZERO * s_prev[0] - s_prev2[0];
    s_prev2[0] = s_prev[0];
    s_prev[0] = s;
    n[0]++;

    // Second filter
    s = sample + COEFF_ZERO * s_prev[1] - s_prev2[1];
    s_prev2[1] = s_prev[1];
    s_prev[1] = s;
    n[1]++;

    N++;

    active = (N / reset) & 0x01;
    if (n[1-active] >= reset) {
        s_prev[1-active] = 0.0;
        s_prev2[1-active] = 0.0;
        total_power[1-active] = 0.0;
        n[1-active] = 0;
    }

    total_power[0] += sample*sample;
    total_power[1] += sample*sample;

    power = s_prev2[active] * s_prev2[active] + s_prev[active] * s_prev[active] - COEFF_ZERO * s_prev[active] * s_prev2[active];

    return power / (total_power[active] + 1e-7) / n[active];
}

/*
 *  @brief High pass filter that removes DC offset from ADC input -- uses bitshifting instead of multiply/divide.
 *  code based on http://openenergymonitor.org/emon/buildingblocks/digital-filters-for-offset-removal
 *  @params sample - current sample from ADC
 *           last_sample - previous sample from ADC
 *           shifted_filter - DC offset to be removed from signal
 *  @returns filtered_value - the ADC value minus the DC offset
 */
int16_t dc_offset_removal_filter(uint16_t sample, uint16_t lastSample, int32_t *pShiftedFilter){
    int32_t shiftedFCL;
    int16_t filteredValue;

    shiftedFCL = *pShiftedFilter + (int32_t)((sample - lastSample) << 5);
    *pShiftedFilter = shiftedFCL - (shiftedFCL >> 5);
    filteredValue = (*pShiftedFilter + 16) >> 5;

    return filteredValue;

}
