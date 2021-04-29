/**
 * @file        cobs.h
 * @brief       C functions for COBS (Consistent Overhead Byte Stuffing)
 * @author      m2enu
 * @date        2021/04/29
 * @copyright   Copyright (c) 2021 m2enu
 * @par         License
 *              https://github.com/m2enu/cobs/blob/main/LICENSE
 */
#ifndef COBS_H_INCLUDED
#define COBS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

/**
 * @brief       Encode src to dst by COBS algorithm
 * @param[out]  dst     output encoded buffer
 * @param[in]   src     input buffer to be encode
 * @param[in]   length  buffer length in bytes
 * @return      Encoded buffer length in bytes
 * @retval      (0)     Encode failed
 * @retval      (>0)    Encode succeeded
 * @note        Never output the delimiter byte
 */
size_t cobs_encode(uint8_t * dst, const uint8_t * src, size_t length);

/**
 * @brief       Decode src to dst by COBS algorithm
 * @param[out]  dst     output decoded buffer
 * @param[in]   src     input buffer to be decode
 * @param[in]   length  buffer length in bytes
 * @return      Decoded buffer length in bytes
 * @retval      (0)     Decode failed
 * @retval      (>0)    Encode succeeded
 * @note        Stop decoding if delimiter byte is found.
 */
size_t cobs_decode(uint8_t * dst, const uint8_t * src, size_t length);

#ifdef __cplusplus
}
#endif

#endif

