/**
 * @file ptp_servo.h
 * @brief PI伺服控制器
 */

#ifndef PTP_SERVO_H
#define PTP_SERVO_H

#include <stdint.h>

/* PI控制器参数 */
#define SERVO_KP 0.7
#define SERVO_KI 0.3

/* 步进阈值（纳秒） - 10毫秒 */
#define SERVO_STEP_THRESHOLD 10000000LL

/* 伺服状态 */
typedef enum {
    SERVO_UNLOCKED,
    SERVO_JUMP,
    SERVO_LOCKED,
    SERVO_LOCKED_STABLE
} servo_state_t;

/* PI伺服结构 */
typedef struct {
    double kp;
    double ki;
    double integral;
    double last_freq;
    servo_state_t state;
    int count;
} pi_servo_t;

/* 函数声明 */
void pi_servo_init(pi_servo_t *s);
double pi_servo_sample(pi_servo_t *s, int64_t offset, servo_state_t *state);

#endif /* PTP_SERVO_H */