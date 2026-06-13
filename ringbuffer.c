#include <stdlib.h>
#include "ringbuffer.h"

CircularBuffer* init_buffer(int capacity) {
    CircularBuffer* cb = (CircularBuffer*)malloc(sizeof(CircularBuffer));
    cb->storage = (double*)malloc(capacity * sizeof(double));
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
    cb->capacity = capacity;
    return cb;
}

void insert_telemetry(CircularBuffer* cb, double val) {
    cb->storage[cb->head] = val;
    cb->head = (cb->head + 1) % cb->capacity; // Wrap-around logic

    if (cb->count < cb->capacity) {
        cb->count++;
    } else {
        // Buffer is full; tail advances to overwrite the oldest sample
        cb->tail = (cb->tail + 1) % cb->capacity;
    }
}

double compute_window_mean(CircularBuffer* cb) {
    if (cb->count == 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < cb->count; i++) {
        int idx = (cb->tail + i) % cb->capacity;
        sum += cb->storage[idx];
    }
    return sum / cb->count;
}

double compute_window_variance(CircularBuffer* cb, double mean) {
    if (cb->count <= 1) return 0.0;
    double sum_sq_diff = 0.0;
    for (int i = 0; i < cb->count; i++) {
        int idx = (cb->tail + i) % cb->capacity;
        double diff = cb->storage[idx] - mean;
        sum_sq_diff += diff * diff;
    }
    return sum_sq_diff / cb->count;
}

void free_buffer(CircularBuffer* cb) {
    free(cb->storage);
    free(cb);
}
