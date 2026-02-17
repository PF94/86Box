/*
 * Corruptor for 86box
 *
 * By Chaziz/Gamerappa
 */
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define HAVE_STDARG_H
#include <86box/86box.h>
#include <86box/corrupt.h>
#include <86box/random.h>

#ifdef ENABLE_CORRUPT_LOG
int corrupt_do_log = ENABLE_CORRUPT_LOG;

static void
corrupt_log(const char *fmt, ...)
{
    va_list ap;

    if (corrupt_do_log) {
        va_start(ap, fmt);
        pclog_ex(fmt, ap);
        va_end(ap);
    }
}
#else
#    define corrupt_log(fmt, ...)
#endif

/* define stuff here i guess */
double g_corrupt_gpu_colors = 0.0;

void corrupt(void *value, size_t size, double probability)
{
    if (!value || size == 0 || probability <= 0.0)
        return;

    if (probability > 1.0)
        probability = 1.0;

    // try to make this more gradual?
    probability = probability * probability;

    // chance
    double r = (double)random_generate() / (double)UINT32_MAX;
    if (r >= probability)
        return;

    uint8_t *bytes = (uint8_t *)value;
    size_t total_bits = size * 8u;

    size_t flips = 1;

    if (size > 1)
    {
        size_t max_extra = total_bits / 16u;
        if (max_extra > 0)
            flips += random_generate() % max_extra;
    }

    for (size_t i = 0; i < flips; ++i)
    {
        size_t bit_index  = random_generate() % total_bits;
        size_t byte_index = bit_index / 8u;
        uint8_t mask      = 1u << (bit_index % 8u);

        bytes[byte_index] ^= mask;
    }
}

void corrupt_set_gpu_colors(double probability)
{
    if (probability < 0.0) probability = 0.0;
    if (probability > 1.0) probability = 1.0;

    g_corrupt_gpu_colors = probability;
}