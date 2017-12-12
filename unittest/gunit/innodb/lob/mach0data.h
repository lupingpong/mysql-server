/*****************************************************************************

Copyright (c) 2016, 2017 Oracle and/or its affiliates. All Rights Reserved.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Suite 500, Boston, MA 02110-1335 USA

*****************************************************************************/
#ifndef _mach0data_h_
#define _mach0data_h_

#include "lot0types.h"
#include "mtr0types.h"
#include "ut0dbg.h"
#include "ut0byte.h"

inline uint8_t mach_read_from_1(const byte *b) {
  ut_ad(b != nullptr);
  return ((uint8_t)(b[0]));
}

inline uint16_t mach_read_from_2(const byte *b) {
  return (((ulint)(b[0]) << 8) | (ulint)(b[1]));
}

inline void mach_write_to_1(byte *b, ulint n) { b[0] = (byte)n; }

inline void mach_write_to_2(byte *b, ulint n) {
  b[0] = (byte)(n >> 8);
  b[1] = (byte)(n);
}

inline void mach_write_to_4(byte *b, ulint n) {
  b[0] = (byte)(n >> 24);
  b[1] = (byte)(n >> 16);
  b[2] = (byte)(n >> 8);
  b[3] = (byte)n;
}

/** The following function is used to fetch data from 4 consecutive
bytes. The most significant byte is at the lowest address.
@param[in] b pointer to four bytes.
@return ulint integer */
inline ulint mach_read_from_4(const byte *b) {
  return (((ulint)(b[0]) << 24) | ((ulint)(b[1]) << 16) | ((ulint)(b[2]) << 8) |
          (ulint)(b[3]));
}

inline uint32_t mach_read_ulint(const byte *ptr, mlog_id_t type) {
  switch (type) {
  case MLOG_1BYTE:
    return (mach_read_from_1(ptr));
  case MLOG_2BYTES:
    return (mach_read_from_2(ptr));
  case MLOG_4BYTES:
    return (mach_read_from_4(ptr));
  default:
    break;
  }

  ut_error;
  return (0);
}

/** The following function is used to fetch data from 6 consecutive
bytes. The most significant byte is at the lowest address.
@param[in]      b       pointer to 6 bytes to read
@return 48-bit integer */
inline
ib_uint64_t
mach_read_from_6(
        const byte*     b)
{
        ut_ad(b != nullptr);

        return(ut_ull_create(mach_read_from_2(b), mach_read_from_4(b + 2)));
}

/** The following function is used to store data in 6 consecutive
bytes. We store the most significant byte to the lowest address.
@param[in]      b       pointer to 6 bytes where to store
@param[in]      id      48-bit integer to write */
inline
void
mach_write_to_6(
        byte*           b,
        ib_uint64_t     n)
{
        ut_ad(b != nullptr);

        mach_write_to_2(b, (ulint) (n >> 32));
        mach_write_to_4(b + 2, (ulint) n);
}


#endif // _mach0data_h_
