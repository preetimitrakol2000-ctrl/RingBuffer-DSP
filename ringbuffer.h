#ifndef RINGBUFFER_H
#define RINGBUFFER_H

typedef struct {
    double* storage;
    int head;
    int tail;
    int count;
    int capacity;
} CircularBuffer;

CircularBuffer* init_buffer(int capacity);
void insert_telemetry(CircularBuffer* cb, double val);
double compute_window_mean(CircularBuffer* cb);
double compute_window_variance(CircularBuffer* cb, double mean);
void free_buffer(CircularBuffer* cb);

#endif
