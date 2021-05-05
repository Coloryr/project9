#ifndef PID_h
#define PID_h

#include "main.h"

#define Motor_Kp 10.0 //比例，越大杆的控制就约灵敏
#define Motor_Kd 10.0 //微分，越大小球越快趋于静止
#define Motor_Ki 10.0 //积分，消除静态误差，使小球距离目标位置的偏差越小，越大则对静态误差的反应越灵敏

float balance(float distance, float target);

#endif
