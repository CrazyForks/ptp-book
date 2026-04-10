/**
 * @file ptp_common.h
 * @brief PTP公共定义和类型
 * 
 * 轻量级PTP实现 - 教学版本
 * 支持E2E延迟测量、UDP/IPv4传输、软件时间戳
 * 
 * @version 1.0.0
 * @date 2026-04-10
 */

#ifndef PTP_COMMON_H
#define PTP_COMMON_H

#include <stdint.h>
#include <time.h>
#include <endian.h>

/* 版本信息 */
#define PTP_LITE_VERSION "1.0.0"
#define PTP_LITE_VERSION_DATE "2026-04-10"

/* PTP时间戳：48位秒 + 32位纳秒 */
typedef struct {
    uint16_t seconds_msb;    /* 秒的高16位 */
    uint32_t seconds_lsb;    /* 秒的低32位 */
    uint32_t nanoseconds;    /* 纳秒部分 */
} __attribute__((packed)) ptp_timestamp_t;

/* 时间间隔：64位纳秒 */
typedef int64_t ptp_timeinterval_t;

/* 时钟ID：8字节 */
typedef uint8_t ptp_clock_identity_t[8];

/* 端口ID */
typedef struct {
    ptp_clock_identity_t clock_identity;
    uint16_t port_number;
} __attribute__((packed)) ptp_port_identity_t;

/* 消息类型 */
#define PTP_MSG_SYNC           0x0
#define PTP_MSG_DELAY_REQ      0x1
#define PTP_MSG_FOLLOW_UP      0x8
#define PTP_MSG_DELAY_RESP     0x9
#define PTP_MSG_ANNOUNCE       0xB

/* PTP版本 */
#define PTP_VERSION            2

/* 组播地址和端口 */
#define PTP_PRIMARY_MCAST      "224.0.1.129"
#define PTP_EVENT_PORT         319
#define PTP_GENERAL_PORT       320

/* 默认参数 */
#define PTP_DEFAULT_DOMAIN     0
#define PTP_DEFAULT_PRIORITY1  128
#define PTP_DEFAULT_PRIORITY2  128
#define PTP_DEFAULT_ANNOUNCE_INT  1
#define PTP_DEFAULT_SYNC_INT      0

/* 辅助函数：timespec转PTP时间戳 */
static inline void timespec_to_ptp(const struct timespec *ts,
                                   ptp_timestamp_t *ptp)
{
    uint64_t sec = (uint64_t)ts->tv_sec;
    ptp->seconds_msb = htobe16((uint16_t)(sec >> 32));
    ptp->seconds_lsb = htobe32((uint32_t)(sec & 0xFFFFFFFFULL));
    ptp->nanoseconds = htobe32((uint32_t)ts->tv_nsec);
}

/* 辅助函数：PTP时间戳转timespec */
static inline void ptp_to_timespec(const ptp_timestamp_t *ptp,
                                   struct timespec *ts)
{
    ts->tv_sec = ((uint64_t)be16toh(ptp->seconds_msb) << 32) |
                 be32toh(ptp->seconds_lsb);
    ts->tv_nsec = be32toh(ptp->nanoseconds);
}

#endif /* PTP_COMMON_H */