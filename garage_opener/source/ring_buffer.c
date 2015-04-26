/*
 * ring_buffer.c
 *
 *  Created on: Jul 24, 2014
 *      Author: Rick
 */

#include "ring_buffer.h"

// RingBuffer
void ringbuffer_init(ringBuffer *_this) {
	_this->count = 0;
	_this->head = 0;
	_this->tail = 0;
	_this->overflow = 0;
}

int16_t ringbuffer_get(ringBuffer *_this) {
	int16_t data = 0;
	if (_this->count) {
		data = _this->buffer[_this->tail];
		_this->count--;
		_this->tail = (_this->tail + 1) % RBUFSIZE;
	}

	return data;
}

int8_t ringbuffer_put(ringBuffer *_this, const int16_t data) {
	uint16_t next_head = (_this->head + 1) % RBUFSIZE;
	//if (_this->count < RBUFSIZE) {
	if (next_head != _this->tail) {
		_this->count++;
		_this->buffer[_this->head] = data;
		_this->head = next_head;
		return 1;
	}
	_this->overflow = 1;
	return -1;
}

uint8_t ringbuffer_full(ringBuffer *_this) {
	return (_this->count >= RBUFSIZE);
}

uint8_t ringbuffer_empty(ringBuffer *_this) {
	return (_this->count == 0);
}

// Audio RingBuffer
void audioRingbuffer_init(audioRingBuffer *_this) {
	_this->count = 0;
	_this->head = 0;
	_this->tail = 0;
	_this->overflow = 0;
}

uint16_t audioRingbuffer_get(audioRingBuffer *_this) { // about 40 TMR2 clicks
	int16_t data = 0;
	if (_this->count) {
		data = _this->buffer[_this->tail];
		_this->count--;
		_this->tail = (_this->tail + 1) % ARBUFSIZE;
	}

	return data;
}
// about 31 TMR2 clicks
int8_t audioRingbuffer_put(audioRingBuffer *_this, const uint16_t data) {
	uint16_t next_head = (_this->head + 1) % ARBUFSIZE;
	//if (_this->count < RBUFSIZE) {
	if (next_head != _this->tail) {
		_this->count++;
		_this->buffer[_this->head] = data;
		_this->head = next_head;
		return 1;
	}
	_this->overflow = 1;
	return -1;
}

uint8_t audioRingbuffer_full(audioRingBuffer *_this) {
	return (_this->count >= ARBUFSIZE);
}

uint8_t audioRingbuffer_empty(audioRingBuffer *_this) {
	return (_this->count == 0);
}

