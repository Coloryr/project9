#include "pid.h"

/*********
 * 控制杆的平衡
 * param - distance : 以右边的测距零点为原点，小球的横向距离
 * param - target : 目标位置，距离右边原点的距离
 * return : 返回需要转动的角度，包含方向
 *********/
float balance(float distance, float target)
{
    static float bias_add, bias_last;//误差累计  上一次计算得的误差
    float bias = target - distance; //计算误差：目标位置 - 小球位置
    float angle;
    bias_last = bias; //保存误差给下次用
    bias_add += bias;//对每次产生的误差进行累计
    if(bias_add >= 100) bias_add = 100;//对误差的累计进行限制，改变数值可以的到不同的速度
    if(bias_add <= -100) bias_add = -100; 
    angle = Motor_Kp * bias + Motor_Kd * (bias - bias_last) + Motor_Ki * bias_add;//计算应该转动的角度，当目标位置位于小球左边时，angle为正，逆时针转动，位于右边时相反
    return angle;
}