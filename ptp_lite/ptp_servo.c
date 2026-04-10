/**
 * @file ptp_servo.c
 * @brief PI伺服控制器实现
 */

#include <stdlib.h>
#include <stdint.h>
#include "ptp_servo.h"

void pi_servo_init(pi_servo_t *s)
{
    s->kp = SERVO_KP;
    s->ki = SERVO_KI;
    s->integral = 0.0;
    s->last_freq = 0.0;
    s->state = SERVO_UNLOCKED;
    s->count = 0;
}

double pi_servo_sample(pi_servo_t *s, int64_t offset, servo_state_t *state)
{
    double freq_adj;
    
    /* 状态转换逻辑 */
    if (llabs(offset) > SERVO_STEP_THRESHOLD) {
        /* 大偏差：跳变 */
        s->state = SERVO_JUMP;
        s->integral = 0;
        s->count = 0;
    } else {
        /* 小偏差：渐进调整 */
        s->count++;
        if (s->count > 1) {
            s->state = SERVO_LOCKED;
        }
        if (s->count > 10) {
            s->state = SERVO_LOCKED_STABLE;
        }
    }
    
    /* PI控制 - 只在LOCKED状态使用 */
    if (s->state == SERVO_LOCKED || s->state == SERVO_LOCKED_STABLE) {
        s->integral += offset;
        freq_adj = -s->kp * offset - s->ki * s->integral;
    } else {
        freq_adj = 0;
    }
    
    *state = s->state;
    s->last_freq = freq_adj;
    
    return freq_adj;
}