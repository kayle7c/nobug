#include "stm32f10x.h"
#include "ringbuffer.h"

#define ALIGN_DOWN(size, align)      ((size) & ~((align) - 1))

void ringbuffer_init(struct ringbuffer* rb,uint8_t* pool,int16_t size)
{
		rb->read_mirror=0;
		rb->write_mirror=0;
		rb->read_index=0;
		rb->write_index=0;
	
		rb->ringbuffer=pool;
		rb->buffer_size = ALIGN_DOWN(size, 4);
}

int ringbuffer_getchar(struct ringbuffer* rb,uint8_t* ch)
{
		*ch=rb->ringbuffer[rb->read_index];
	
		if(rb->read_index==rb->buffer_size-1)
		{
				rb->read_index=0;
		}
		else
		{
				rb->read_index++;
		}
		return 1;
}

int ringbuffer_putchar(struct ringbuffer* rb,uint8_t ch)
{
		rb->ringbuffer[rb->write_index]=ch;
	
		if(rb->write_index==rb->buffer_size-1)
		{
				rb->write_index=0;
		}
		else
		{
				rb->write_index++;
		}
		return 1;
}

int kringbuffer_isempty(struct ringbuffer* rb)
{
		return rb->write_index==rb->read_index;
}