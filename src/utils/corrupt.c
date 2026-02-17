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

/* generate globals */
#define DEFINE_GLOBAL(name) \
    double g_corrupt_##name = 0.0;

CORRUPTION_LIST(DEFINE_GLOBAL)

#undef DEFINE_GLOBAL

/* generate setters */
#define DEFINE_SETTER(name)                        \
    void corrupt_set_##name(double probability)    \
    {                                              \
        if (probability < 0.0) probability = 0.0; \
        if (probability > 1.0) probability = 1.0; \
        g_corrupt_##name = probability;            \
    }

CORRUPTION_LIST(DEFINE_SETTER)

#undef DEFINE_SETTER

void corrupt(void *value, size_t size, double probability)
{
    if (!value || size == 0 || probability <= 0.0)
        return;

    if (probability > 1.0)
        probability = 1.0;

    double p = probability;

    double p8 = p * p * p * p * p * p * p * p; // hah... this is stupid but it works

    double r = (double)random_generate() / (double)UINT32_MAX;
    if (r >= p8)
        return;

    uint8_t *bytes    = (uint8_t *)value;
    size_t total_bits = size * 8u;


    size_t max_flips = 1 + (size_t)((double)(total_bits - 1) * p8);
    size_t flips     = 1 + (max_flips > 1 ? random_generate() % max_flips : 0);

    for (size_t i = 0; i < flips; ++i)
    {
        size_t bit_index  = random_generate() % total_bits;
        size_t byte_index = bit_index / 8u;
        uint8_t mask      = (uint8_t)(1u << (bit_index % 8u));

        bytes[byte_index] ^= mask;
    }
}