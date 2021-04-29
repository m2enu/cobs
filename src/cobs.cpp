/**
 * @file        cobs.cpp
 * @brief       C functions for COBS (Consistent Overhead Byte Stuffing)
 * @author      m2enu
 * @date        2021/04/29
 * @copyright   Copyright (c) 2021 m2enu
 * @par         License
 *              https://github.com/m2enu/cobs/blob/main/LICENSE
 */
#include "cobs.h"

#define COBS_FAILED         (0)         //!< Return value on failed
#define COBS_DATA_ZERO      (0x00U)     //!< COBS zero data
#define COBS_DELIMITER      (0x00U)     //!< COBS delimiter

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
size_t cobs_encode(
          uint8_t * dst,
    const uint8_t * src,
          size_t    length
) {
    if (
           (dst == NULL)
        || (src == NULL)
        || (dst == src)
        || (length <= 0)
    ) {
        return COBS_FAILED;
    }

    const uint8_t * const src_end = src + length;
    uint8_t * ovr_ptr = dst;
    uint8_t * dst_ptr = dst + 1;
    uint8_t ovr_len = 1U;
    uint8_t src_val;
    while (src < src_end)
    {
        src_val = *src++;
        if (src_val == COBS_DELIMITER)
        {
            *ovr_ptr = ovr_len;
            ovr_ptr = dst_ptr++;
            ovr_len = 1U;
            if (src >= src_end)
            {
                break;
            }
        }
        else
        {
            *dst_ptr++ = src_val;
            ovr_len++;
            if (src >= src_end)
            {
                break;
            }
            else if (ovr_len == 0xFFU)
            {
                *ovr_ptr = ovr_len;
                ovr_ptr = dst_ptr++;
                ovr_len = 1U;
            }
        }
    }
    *ovr_ptr = ovr_len;

    return (dst_ptr - dst);
}

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
size_t cobs_decode(
          uint8_t * dst,
    const uint8_t * src,
          size_t    length
) {
    if (
           (dst == NULL)
        || (src == NULL)
        || (dst == src)
        || (length <= 0)
    ) {
        return COBS_FAILED;
    }

    const uint8_t * const src_end = src + length;
    uint8_t * dst_ptr = dst;
    uint8_t ovl_idx;
    uint8_t src_val;
    int i;
    while (src < src_end)
    {
        ovl_idx = *src++;
        if (ovl_idx == COBS_DELIMITER)
        {
            return COBS_FAILED;
        }

        ovl_idx--;
        if (ovl_idx > (src_end - src))
        {
            ovl_idx = src_end - src;
        }

        for (i = ovl_idx; i > 0; i--)
        {
            src_val = *src++;
            if (src_val == COBS_DELIMITER)
            {
                return COBS_FAILED;
            }
            *dst_ptr++ = src_val;
        }
        if (src >= src_end)
        {
            break;
        }
        else if (ovl_idx != 0xFEU)
        {
            *dst_ptr++ = COBS_DATA_ZERO;
        }
    }
    return dst_ptr - dst;
}

