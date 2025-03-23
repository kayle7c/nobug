#ifndef __RINGBUFFER_H
#define __RINGBUFFER_H
#include "stm32f10x.h"

enum ringbuffer_state
{
    RINGBUFFER_EMPTY,
    RINGBUFFER_FULL,
    RINGBUFFER_HALFFULL,
};

struct ringbuffer
{
		uint8_t *ringbuffer;
	
		uint16_t read_mirror:1;
		uint16_t read_index:15;
	
		uint16_t write_mirror:1;
		uint16_t write_index:15;
	
		int16_t buffer_size;
};

void ky_ringbuffer_init(struct ringbuffer* rb,uint8_t* pool,int16_t size);
int ky_ringbuffer_getchar(struct ringbuffer* rb,uint8_t* ch);
int ky_ringbuffer_putchar(struct ringbuffer* rb,uint8_t ch);
int ky_ringbuffer_isempty(struct ringbuffer* rb);


#endif