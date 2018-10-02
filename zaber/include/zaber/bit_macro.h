#pragma once

#define BIT(n) (1 << (n))

#define BIT_SET(y, mask) (y |= (mask))
#define BIT_CLEAR(y, mask) (y &= ~(mask))
#define BIT_FLIP(y, mask) (y ^= (mask))
