# RingBuffer-DSP

A hardware-optimized Digital Signal Processing (DSP) streaming engine written in pure C99 for memory-constrained IoT nodes. By utilizing a contiguous **Circular Ring Buffer**, this subsystem calculates rolling statistical features (Mean and Variance) over a sliding time window without shifting elements or causing memory leaks.

## 📊 Algorithmic Architecture
* **Data Structure:** Fixed-size Circular Queue using Head/Tail index wrapping.
* **Time Complexity:** $O(1)$ constant-time insertions and window updates.
* **Memory Footprint:** Fully static layout, preventing runtime heap fragmentation on bare-metal microcontrollers.

## 📦 Compilation & Execution
```bash
gcc main.c ringbuffer.c -o ring_dsp -lm
./ring_dsp
