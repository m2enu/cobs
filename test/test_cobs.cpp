/**
 * @file        test_cobs.cpp
 * @brief       Unit-test for COBS embedded
 * @author      m2enu
 * @date        2021/04/29
 * @copyright   Copyright (c) 2021 m2enu
 * @par         License
 *              https://github.com/m2enu/cobs/blob/main/LICENSE
 * @note        Used example on Wikipedia as test data.
 * @note        https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing
 */
#include <unity.h>
#include <stdint.h>
#include <stdlib.h>
#include "test_cobs.h"
#include "cobs.h"

/**
 * @brief       Get specified array size
 */
#define ARRAY_SIZE(x)   (sizeof(x) / sizeof(x[0]))

static uint8_t ans[512];  //!< Buffer for COBS encode/decode method
static size_t  n_ans;     //!< Buffer size of `ans`

/**
 * @brief       Execute COBS encode/decode testing by specified data
 * @param[in]   org     Original buffer to be encode
 * @param[in]   n_org   Original buffer size
 * @param[in]   enc     Encoded expected buffer
 * @param[in]   n_enc   Encoded expected buffer size
 */
static void exec_test(
    const uint8_t * org, size_t n_org,
    const uint8_t * enc, size_t n_enc)
{
    /* encode: org -> enc */
    n_ans = cobs_encode(ans, org, n_org);
    TEST_ASSERT_EQUAL(n_enc, n_ans);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(enc, ans, n_ans);
    /* decode: enc -> org */
    n_ans = cobs_decode(ans, enc, n_enc);
    TEST_ASSERT_EQUAL(n_org, n_ans);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(org, ans, n_ans);
}

/**
 * @brief       Test by example data 1
 */
static void test_cobs_1(void)
{
    static uint8_t org[] = {0x00U};
    static uint8_t enc[] = {0x01U, 0x01U};
    exec_test(org, ARRAY_SIZE(org), enc, ARRAY_SIZE(enc));
}

/**
 * @brief       Test by example data 2
 */
static void test_cobs_2(void)
{
    static uint8_t org[] = {0x00U, 0x00U};
    static uint8_t enc[] = {0x01U, 0x01U, 0x01U};
    exec_test(org, ARRAY_SIZE(org), enc, ARRAY_SIZE(enc));
}

/**
 * @brief       Test by example data 3
 */
static void test_cobs_3(void)
{
    static uint8_t org[] = {0x11U, 0x22U, 0x00U, 0x33U};
    static uint8_t enc[] = {0x03U, 0x11U, 0x22U, 0x02U, 0x33U};
    exec_test(org, ARRAY_SIZE(org), enc, ARRAY_SIZE(enc));
}

/**
 * @brief       Test by example data 4
 */
static void test_cobs_4(void)
{
    static uint8_t org[] = {0x11U, 0x22U, 0x33U, 0x44U};
    static uint8_t enc[] = {0x05U, 0x11U, 0x22U, 0x33U, 0x44U};
    exec_test(org, ARRAY_SIZE(org), enc, ARRAY_SIZE(enc));
}

/**
 * @brief       Test by example data 5
 */
static void test_cobs_5(void)
{
    static uint8_t org[] = {0x11U, 0x00U, 0x00U, 0x00U};
    static uint8_t enc[] = {0x02U, 0x11U, 0x01U, 0x01U, 0x01U};
    exec_test(org, ARRAY_SIZE(org), enc, ARRAY_SIZE(enc));
}

/**
 * @brief       Test by example data 6
 */
static void test_cobs_6(void)
{
    static uint8_t org[] = ORG_DATA_6;
    static uint8_t enc[] = ENC_DATA_6;
    exec_test(org, ARRAY_SIZE(org), enc, ARRAY_SIZE(enc));
}

/**
 * @brief       Test by example data 7
 */
static void test_cobs_7(void)
{
    static uint8_t org[] = ORG_DATA_7;
    static uint8_t enc[] = ENC_DATA_7;
    exec_test(org, ARRAY_SIZE(org), enc, ARRAY_SIZE(enc));
}

/**
 * @brief       Test by example data 8
 */
static void test_cobs_8(void)
{
    static uint8_t org[] = ORG_DATA_8;
    static uint8_t enc[] = ENC_DATA_8;
    exec_test(org, ARRAY_SIZE(org), enc, ARRAY_SIZE(enc));
}

/**
 * @brief       Invalid pattern testing on encode
 */
static void test_invalid_encode(void)
{
    size_t ret;
    static uint8_t org[] = {0x00U, 0x00U, 0x00U, 0x00U};

    /* Specify NULL as encode source */
    ret = cobs_encode(ans, NULL, 1);
    TEST_ASSERT_EQUAL(0, ret);

    /* Specify NULL as encode destination */
    ret = cobs_encode(NULL, org, 1);
    TEST_ASSERT_EQUAL(0, ret);

    /* Specify 0 as encode source length */
    ret = cobs_encode(ans, org, 0);
    TEST_ASSERT_EQUAL(0, ret);

    /* Specify the same buffer as encode source and destination */
    ret = cobs_encode(org, org, 1);
    TEST_ASSERT_EQUAL(0, ret);
}

/**
 * @brief       Invalid pattern testing on decode
 */
static void test_invalid_decode(void)
{
    size_t ret;
    static uint8_t org[] = {0x00U, 0x00U, 0x00U, 0x00U};

    /* Specify NULL as decode source */
    ret = cobs_decode(ans, NULL, 1);
    TEST_ASSERT_EQUAL(0, ret);

    /* Specify NULL as decode destination */
    ret = cobs_encode(NULL, org, 1);
    TEST_ASSERT_EQUAL(0, ret);

    /* Specify 0 as decode source length */
    ret = cobs_decode(ans, org, 0);
    TEST_ASSERT_EQUAL(0, ret);

    /* Specify the same buffer as decode source and destination */
    ret = cobs_decode(org, org, 1);
    TEST_ASSERT_EQUAL(0, ret);
}

/**
 * @brief       Unit test main
 */
int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_cobs_1                );
    RUN_TEST(test_cobs_2                );
    RUN_TEST(test_cobs_3                );
    RUN_TEST(test_cobs_4                );
    RUN_TEST(test_cobs_5                );
    RUN_TEST(test_cobs_6                );
    RUN_TEST(test_cobs_7                );
    RUN_TEST(test_cobs_8                );
    RUN_TEST(test_invalid_encode        );
    RUN_TEST(test_invalid_decode        );
    return UNITY_END();
}

