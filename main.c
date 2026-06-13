#include <stdio.h>
#include "ringbuffer.h"

int main() {
    printf("📡 Activating RingBuffer-DSP Micro-Engine...\n\n");

    // Initialize a sliding window buffer with a capacity of 4 elements
    CircularBuffer* stream_buffer = init_buffer(4);

    // Simulate real-time streaming data values
    printf("📥 Ingesting Telemetry Packets: 12.5V, 13.1V, 12.8V, 12.6V\n");
    insert_telemetry(stream_buffer, 12.5);
    insert_telemetry(stream_buffer, 13.1);
    insert_telemetry(stream_buffer, 12.8);
    insert_telemetry(stream_buffer, 12.6);

    double mean = compute_window_mean(stream_buffer);
    double variance = compute_window_variance(stream_buffer, mean);
    printf("   📊 Window Metrics: Current Mean = %.2fV | Variance = %.4f\n\n", mean, variance);

    // Overwrite event: Adding more data wraps around and drops the oldest value (12.5)
    printf("📥 Ingesting New Packet (Triggers Overwrite): 14.5V\n");
    insert_telemetry(stream_buffer, 14.5);

    mean = compute_window_mean(stream_buffer);
    variance = compute_window_variance(stream_buffer, mean);
    printf("   🔮 Updated Window Metrics: Current Mean = %.2fV | Variance = %.4f\n", mean, variance);

    free_buffer(stream_buffer);
    return 0;
}
