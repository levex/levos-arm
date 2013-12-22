#include <stdint.h>

uint32_t __umodsi3(uint32_t num, uint32_t den)
{
        register uint32_t quot = 0, qbit = 1;

        if (den == 0)
        {
                return 0;        /* if trap returns... */
        }

        /* left-justify denominator and count shift */
        while ((int32_t) den >= 0)
        {
                den <<= 1;
                qbit <<= 1;
        }

        while (qbit)
        {
                if (den <= num)
                {
                        num -= den;
                        quot += qbit;
                }
                den >>= 1;
                qbit >>= 1;
        }

        return num;
}

uint32_t __udivsi3(uint32_t num, uint32_t den)
{
        uint32_t quot = 0, qbit = 1;

        if (den == 0)
        {
                return 0;        /* If trap returns... */
        }

        /* Left-justify denominator and count shift */
        while ((int32_t) den >= 0)
        {
                den <<= 1;
                qbit <<= 1;
        }

        while (qbit)
        {
                if (den <= num)
                {
                        num -= den;
                        quot += qbit;
                }
                den >>= 1;
                qbit >>= 1;
        }

        return quot;
}
