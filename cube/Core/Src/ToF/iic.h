#ifndef IIC_h
#define IIC_h

#include "main.h"

void I2C_Configuration();                                                                     //端口配置初始化
void I2C_START();                                                                             //通讯信号开始函数
void I2C_STOP();                                                                              //通讯信号结束函数
void I2C_Ack();                                                                               //主机应答函数
void I2C_NAck();                                                                              //主机非应答函数
uint8_t I2C_Wait_Ack();                                                                       //主机等待应答函数
void I2C_SEND(uint8_t byte);                                                                  //主机发送单个字节函数
uint8_t I2C_READ();                                                                           //主机读取单个字节函数
void I2C_SEND_BYTE(uint8_t slaveaddr, uint8_t registeraddr, uint8_t byte);                    //发送到具体从机地址及相关寄存器一个字节
void I2C_SEND_BYTES(uint8_t slaveaddr, uint8_t registeraddr, uint8_t *pbuffer, uint16_t num); //发送一串数据给具体从机的相关寄存器
uint8_t I2C_READ_BYTE(uint8_t slaveaddr, uint8_t registeraddr); //读取具体从机的相关寄存器一串字节
void I2C_READ_BYTES(uint8_t slaveaddr, uint8_t registeraddr, uint8_t *pbuffer, uint16_t num); //读取具体从机的相关寄存器一串字节

#endif
