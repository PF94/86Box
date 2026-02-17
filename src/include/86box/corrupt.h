/*
 * Corruptor for 86box
 *
 * By Chaziz/Gamerappa
 */
#ifndef EMU_CORRUPT_H
#define EMU_CORRUPT_H

#include <stddef.h>

#define CORRUPTION_LIST(X) \
    X(gpu_colors)          \
    X(gpu_in)              \
    X(gpu_out)             \
    X(gpu_render)          \
    X(hdd_read)            \
    X(kb)                  \

#define DECLARE_EXTERN(name) \
    extern double g_corrupt_##name;

CORRUPTION_LIST(DECLARE_EXTERN)

#undef DECLARE_EXTERN

#define DECLARE_SETTER(name) \
    void corrupt_set_##name(double probability);

CORRUPTION_LIST(DECLARE_SETTER)

#undef DECLARE_SETTER

void corrupt(void *value, size_t size, double probability);

#define CORRUPT(x, probability) \
    corrupt(&(x), sizeof(x), (probability))

#define CORRUPT_BUF(x, size, probability) \
    corrupt((x), (size), (probability))

#endif /*EMU_CORRUPT_H*/