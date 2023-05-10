/*
 * FS2011 Pro
 * Debugging module
 *
 * (C) 2022-2023 Gissio
 *
 * License: MIT
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>

void debugWait(uint32_t ms);
void debugBit(bool value);
void debugUInt32(uint32_t value);

#endif
