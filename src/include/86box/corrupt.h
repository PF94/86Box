/*
 * Corruptor for 86box
 *
 * By Chaziz/Gamerappa
 */
#ifndef EMU_CORRUPT_H
#define EMU_CORRUPT_H

extern double g_corrupt_gpu_colors;

#define CORRUPT(x, probability) \
    corrupt(&(x), sizeof(x), (probability))

extern void corrupt(void*, size_t, double);

void corrupt_set_gpu_colors(double probability);

#endif /*EMU_CORRUPT_H*/