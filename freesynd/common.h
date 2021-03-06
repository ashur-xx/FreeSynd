/************************************************************************
 *                                                                      *
 *  FreeSynd - a remake of the classic Bullfrog game "Syndicate".       *
 *                                                                      *
 *   Copyright (C) 2005  Stuart Binge  <skbinge@gmail.com>              *
 *   Copyright (C) 2005  Joost Peters  <joostp@users.sourceforge.net>   *
 *   Copyright (C) 2006  Trent Waddington <qg@biodome.org>              *
 *                                                                      *
 *    This program is free software;  you can redistribute it and / or  *
 *  modify it  under the  terms of the  GNU General  Public License as  *
 *  published by the Free Software Foundation; either version 2 of the  *
 *  License, or (at your option) any later version.                     *
 *                                                                      *
 *    This program is  distributed in the hope that it will be useful,  *
 *  but WITHOUT  ANY WARRANTY;  without even  the implied  warranty of  *
 *  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  *
 *  General Public License for more details.                            *
 *                                                                      *
 *    You can view the GNU  General Public License, online, at the GNU  *
 *  project's  web  site;  see <http://www.gnu.org/licenses/gpl.html>.  *
 *  The full text of the license is also included in the file COPYING.  *
 *                                                                      *
 ************************************************************************/

#ifndef COMMON_H
#define COMMON_H

#include <cstring>
#include <cassert>

#include "singleton.h"
#include "keys.h"

// TODO: Add a configuration scheme to allow setting these during runtime
#define MENU_SCREEN_WIDTH       320
#define MENU_SCREEN_HEIGHT      200
#define GAME_SCREEN_WIDTH       640
#define GAME_SCREEN_HEIGHT      400

#define STUB_FUNC               printf("STUB: %s\n", __PRETTY_FUNCTION__)

// TODO: Convert these to const int's -- we are using C++, yes? :-)
#define PIXELS_PER_BLOCK        8
#define COLOR_BYTES_PER_BLOCK   (PIXELS_PER_BLOCK / 2)
#define ALPHA_BYTES_PER_BLOCK   (PIXELS_PER_BLOCK / 8)
#define BLOCK_LENGTH            (COLOR_BYTES_PER_BLOCK + ALPHA_BYTES_PER_BLOCK)

typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed long int32;
typedef unsigned long uint32;

inline int ceil8(int v) {
    if (v <= 0)
        return 0;

    int t = 0;

    while (t < v)
        t += 8;

    return t;
}

inline uint16 READ_LE_UINT16(const uint8 *data) {
    return (data[1] << 8) | data[0];
}

inline uint32 READ_LE_UINT32(const uint8 *data) {
    return (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
}

inline uint16 READ_BE_UINT16(const uint8 *data) {
    return (data[0] << 8) | data[1];
}

inline uint32 READ_BE_UINT32(const uint8 *data) {
    return (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
}

inline uint32 mirror(uint32 value, int count) {
    uint32 top = 1 << (count - 1), bottom = 1;

    while (top > bottom) {
        uint32 mask = top | bottom;
        uint32 masked = value & mask;

        if (masked != 0 && masked != mask)
            value ^= mask;

        top >>= 1;
        bottom <<= 1;
    }

    return value;
}

inline uint32 bitValue(const uint32 value, int index) {
    return (value >> index) & 1;
}

inline bool bitSet(const uint32 value, int index) {
    return bitValue(value, index) == 0 ? false : true;
}

inline bool bitClear(const uint32 value, int index) {
    return !bitSet(value, index);
}

#endif
