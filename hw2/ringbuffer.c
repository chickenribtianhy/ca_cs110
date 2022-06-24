#include "ringbuffer.h"
static size_t size;
/* Create a new ring buffer. */
ring_buffer *ring_buffer_new()
{
    /* initialization and malloc, resembles a constructor */
    ring_buffer *p = (ring_buffer *)malloc(sizeof(ring_buffer));
    p->capacity = RING_BUFFER_INIT_SIZE;
    /* both head and tail are initialized to 0, for both of them are ready positions to read from or write to */
    p->read_pos = p->write_pos = 0;
    p->content = (int *)malloc(sizeof(int) * p->capacity);
    /* denote the size of the buffer */
    size = 0;
    /* then p is the address of the finely created ring_buffer */
    return p;
}
/* Destroy the given ring buffer, free all resources allocated.*/
void ring_buffer_destroy(ring_buffer **buffer)
{
    ring_buffer *p = *buffer;
    /* normal check on pointer */
    if (buffer == NULL)
        return;
    /* normal check on pointer */
    if (*buffer == NULL)
        return;
    /* free both the content and the buffer itself*/
    free(p->content);
    free(p);
    /* reset pointer to the buffer (pointer) to NULL */
    *buffer = NULL;
}
/* Returns true if the given ring buffer is empty, false otherwise */
bool ring_buffer_is_empty(const ring_buffer *buffer)
{
    /* normal check on pointer */
    if (buffer == NULL)
        return false;
    /* since both head and tail are the ready positions, 
    the buffer appears empty as head==tail, just as in the initialization*/
    return (size == 0 && buffer->read_pos == buffer->write_pos);
}

/* Read an element from the ring buffer.*/
bool ring_buffer_read(ring_buffer *buffer, int *data)
{
    /* normal check on pointer */
    if (buffer == NULL || data == NULL)
        return false;
    /* if the buffer is empty then we can read nothing from it */
    if (ring_buffer_is_empty(buffer))
        return false;
    *data = buffer->content[buffer->read_pos];
    /* the buffer is a cycle, and we should ensure the position < capacity */
    buffer->read_pos = (buffer->read_pos + 1) % buffer->capacity;
    /* deduct on the size of the buffer */
    --size;
    return true;
}
/* this is a static function that helps to expand the capacity of the buffer */
static void ring_buffer_grow(ring_buffer *buffer)
{
    size_t i;
    /*  since we have to assign all data to a newly alloced array, 
        and realloc may lead to some error in content,
        so here i directly malloc a new array of content, 
        and copy from the former content array */
    int new_capacity;
    int *new_content;
    /* normal check on pointer */
    if (buffer == NULL)
        return;
    /* computing the new capacity, then malloc */
    if (buffer->capacity < 1024)
        /* expend the capacity by factor1 */
        new_capacity = buffer->capacity * RING_BUFFER_GROW_FACTOR1;
    else
        /* expend the capacity by factor2 */
        new_capacity = buffer->capacity * RING_BUFFER_GROW_FACTOR2;
    new_content = (int *)malloc(sizeof(int) * new_capacity);
    /* copy the data from the former content array to the new one, notice the index */
    for (i = 0; i < buffer->capacity; ++i)
        new_content[i] = buffer->content[(buffer->read_pos + i) % buffer->capacity];
    /*  and re-initialize head and tail, 
        make sure all data appear at the front segment of the content array */
    buffer->read_pos = 0;
    buffer->write_pos = buffer->capacity;
    /* don't forget to free the former content array */
    free(buffer->content);
    /* update the content pointer as well as the capacity */
    buffer->content = new_content;
    buffer->capacity = new_capacity;
}
/* Write an element which value is `data` to the ring buffer. */
bool ring_buffer_write(ring_buffer *buffer, const int data)
{
    /* normal check on pointer */
    if (buffer == NULL)
        return false;
    if (size == buffer->capacity)
        ring_buffer_grow(buffer);
    /* just write into the position, as is ensured that there is empty space for new data */
    buffer->content[buffer->write_pos] = data;
    buffer->write_pos = (buffer->write_pos + 1) % buffer->capacity;
    /* increment on the size of the buffer */
    ++size;

    return true;
}
/* Read "rdsize" elements from the ring buffer, and fill them to "data".*/
bool ring_buffer_read_multi(ring_buffer *buffer, size_t rdsize, int *data)
{
    size_t i;
    /* normal check on pointer */
    if (buffer == NULL || data == NULL)
        return false;
    /* loop for rdsize times for each datum */
    for (i = 0; i < rdsize; ++i)
        /* we can just read data one by one, as we have already implemented ring_buffer_read */
        if (!ring_buffer_read(buffer, data + i))
            /* if one read return false, then read_multi should also return false */
            return false;
    return true;
}
/* Write "wrtsize" elements to the ring buffer. The values to write are provided in "data". */
bool ring_buffer_write_multi(ring_buffer *buffer, size_t wrtsize, const int *data)
{
    size_t i;
    /* normal check on pointer */
    if (buffer == NULL || data == NULL)
        return false;
    /* loop for rdsize times for each datum */
    for (i = 0; i < wrtsize; ++i)
        /* we can just write data one by one, as we have already implemented ring_buffer_write */
        if (!ring_buffer_write(buffer, data[i]))
            /* if one write return false, then write_multi should also return false */
            return false;
    return true;
}
/* For every element in the ring buffer, apply "func" to it. */
bool ring_buffer_map(ring_buffer *buffer, map_func func)
{
    size_t i;
    /* normal check on pointer */
    if (buffer == NULL)
        return false;
    /* loop in the content array*/
    i = buffer->read_pos;
    while (i != buffer->write_pos)
    {
        /* implement the map_func to each element */
        buffer->content[i] = func(buffer->content[i]);
        i = (i + 1) % buffer->capacity; /* notice that the index should act as it's in a cycle */
    }
    /* return true when succeed */
    return true;
}
