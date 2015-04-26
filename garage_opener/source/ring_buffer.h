/*
 * ring_buffer.h
 *
 *  Created on: Jul 24, 2014
 *      Author: Rick
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include "stm32f4xx.h"

// RingBuffer
#define RBUFSIZE 1024
typedef struct {
	int16_t buffer[RBUFSIZE];
	uint16_t head;
	uint16_t tail;
	uint16_t count;
	uint8_t overflow;
} ringBuffer;

void ringbuffer_init(ringBuffer *_this);
int16_t ringbuffer_get(ringBuffer *_this);
int8_t ringbuffer_put(ringBuffer *_this, const int16_t data);
uint8_t ringbuffer_full(ringBuffer *_this);
uint8_t ringbuffer_empty(ringBuffer *_this);


// Audio RingBuffer
#define ARBUFSIZE 2048
typedef struct {
	uint16_t buffer[ARBUFSIZE];
	uint16_t head;
	uint16_t tail;
	uint16_t count;
	uint8_t overflow;
} audioRingBuffer;

void audioRingbuffer_init(audioRingBuffer *_this);
uint16_t audioRingbuffer_get(audioRingBuffer *_this);
int8_t audioRingbuffer_put(audioRingBuffer *_this, const uint16_t data);
uint8_t audioRingbuffer_full(audioRingBuffer *_this);
uint8_t audioRingbuffer_empty(audioRingBuffer *_this);

#endif /* RING_BUFFER_H_ */
