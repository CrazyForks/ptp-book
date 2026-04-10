/**
 * @file ptp_message.h
 * @brief PTP消息结构定义 - IEEE 1588-2019
 */

#ifndef PTP_MESSAGE_H
#define PTP_MESSAGE_H

#include "ptp_common.h"

/* PTP消息头 - IEEE 1588-2019 Figure 35 (34 bytes) */
typedef struct {
    uint8_t  message_type;              /* Octet 0: 消息类型 */
    uint8_t  version_ptp;               /* Octet 1: PTP版本 */
    uint16_t message_length;            /* Octets 2-3: 消息长度 */
    uint8_t  domain_number;             /* Octet 4: 域号 */
    uint8_t  reserved1;                 /* Octet 5: 保留 */
    uint16_t flag_field;                /* Octets 6-7: 标志字段 */
    uint64_t correction_field;          /* Octets 8-15: 校正字段 */
    uint32_t reserved2;                 /* Octets 16-19: 保留 */
    ptp_port_identity_t source_port_identity;  /* Octets 20-29: 源端口ID */
    uint16_t sequence_id;               /* Octets 30-31: 序列号 */
    uint8_t  control_field;             /* Octet 32: 控制字段(legacy) */
    int8_t   log_message_interval;      /* Octet 33: 消息间隔 */
} __attribute__((packed)) ptp_header_t;

/* Sync消息 (44 bytes) - IEEE 1588-2019 Figure 39 */
typedef struct {
    ptp_header_t header;                /* 34 bytes */
    ptp_timestamp_t origin_timestamp;   /* 10 bytes */
} __attribute__((packed)) ptp_sync_msg_t;

/* Follow_Up消息 (44 bytes) - IEEE 1588-2019 Figure 40 */
typedef struct {
    ptp_header_t header;                      /* 34 bytes */
    ptp_timestamp_t precise_origin_timestamp; /* 10 bytes */
} __attribute__((packed)) ptp_follow_up_msg_t;

/* Delay_Req消息 (44 bytes) - IEEE 1588-2019 Figure 41 */
typedef struct {
    ptp_header_t header;                /* 34 bytes */
    ptp_timestamp_t origin_timestamp;   /* 10 bytes */
} __attribute__((packed)) ptp_delay_req_msg_t;

/* Delay_Resp消息 (54 bytes) - IEEE 1588-2019 Figure 42 */
typedef struct {
    ptp_header_t header;                /* 34 bytes */
    ptp_timestamp_t receive_timestamp;  /* 10 bytes */
    ptp_port_identity_t requesting_port_identity; /* 10 bytes */
} __attribute__((packed)) ptp_delay_resp_msg_t;

/* Clock Quality结构 (4 bytes) - IEEE 1588-2019 7.6.3.3 */
typedef struct {
    uint8_t  clock_class;                    /* Octet 0: 时钟等级 */
    uint8_t  clock_accuracy;                 /* Octet 1: 时钟精度 */
    uint16_t offset_scaled_log_variance;     /* Octets 2-3: 偏差缩放 */
} __attribute__((packed)) ptp_clock_quality_t;

/* Announce消息 (64 bytes) - IEEE 1588-2019 Figure 43 */
typedef struct {
    ptp_header_t header;                     /* 34 bytes */
    ptp_timestamp_t origin_timestamp;        /* 10 bytes */
    uint16_t current_utc_offset;             /* 2 bytes */
    uint8_t  reserved1;                      /* 1 byte */
    uint8_t  grandmaster_priority1;          /* 1 byte */
    ptp_clock_identity_t grandmaster_identity; /* 8 bytes */
    ptp_clock_quality_t grandmaster_clock_quality; /* 4 bytes */
    uint8_t  grandmaster_priority2;          /* 1 byte */
    uint16_t steps_removed;                  /* 2 bytes */
    uint8_t  time_source;                    /* 1 byte */
} __attribute__((packed)) ptp_announce_msg_t;

/* 函数声明 */
void ptp_init_header(ptp_header_t *hdr, uint8_t msg_type, 
                     uint16_t seq_id, const ptp_port_identity_t *port_id);

void ptp_init_sync(ptp_sync_msg_t *msg, uint16_t seq_id,
                   const ptp_port_identity_t *port_id);

void ptp_init_follow_up(ptp_follow_up_msg_t *msg, uint16_t seq_id,
                        const ptp_port_identity_t *port_id,
                        const struct timespec *ts);

void ptp_init_delay_req(ptp_delay_req_msg_t *msg, uint16_t seq_id,
                        const ptp_port_identity_t *port_id);

void ptp_init_delay_resp(ptp_delay_resp_msg_t *msg, uint16_t seq_id,
                         const ptp_port_identity_t *port_id,
                         const ptp_timestamp_t *ts,
                         const ptp_port_identity_t *req_port_id);

void ptp_init_announce(ptp_announce_msg_t *msg, uint16_t seq_id,
                       const ptp_port_identity_t *port_id,
                       const struct timespec *ts);

#endif /* PTP_MESSAGE_H */