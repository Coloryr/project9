#include "iic.h"
#include "cmsis_os2.h"

// #define SCL_HIGH() LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_6);  //时钟线置高
// #define SCL_LOW() LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_6); //时钟线置低

// #define SDA_HIGH() LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);  //数据线置高
// #define SDA_LOW() LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_7); //数据线置低
// #define SDA_READ LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_7)    //读数据时的pin脚定义，输入PB7口

// #define SDA_IN() LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_7, LL_GPIO_MODE_INPUT);   //清零和设置输入模式
// #define SDA_OUT() LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT); //清零和设置输出模式

// /*
// 函数名：void I2C_START(void);
// 作用：通讯开始信号
// 输入参数：无
// 输出参数：无
// */

// void delay_us(uint32_t a)
// {
// 	a =a *20;
// 	while(a--);
// }

// void I2C_START()
// {
//     SDA_OUT();  //设置pin脚的方向是输出，意味着主机向从机发数据了
//     SCL_HIGH(); //先拉高时钟线
//     SDA_HIGH(); //再拉高数据线

//     delay_us(2); //延迟2us，延迟是有必要的，参照I2C协议写的
//     SDA_LOW();   //拉低数据线，触发通讯

//     delay_us(2); //延迟2us
//     SCL_LOW();   //拉低时钟线，方便数据线上的数据变化
//     delay_us(2); //延迟2us
// }

// /*
// 函数名：void I2C_STOP（void）;
// 作用：通讯终止信号
// 输入参数：无
// 输出参数：无
// */
// void I2C_STOP()
// {
//     SDA_OUT();  //设置pin脚的方向是输出，意味着主机向从机发数据了
//     SDA_LOW();  //先拉底数据线
//     SCL_HIGH(); //再拉高时钟线

//     delay_us(2); //延迟2us
//     SDA_HIGH();  //拉高数据线，终止通讯
//     delay_us(2); //延迟2us
// }

// /*
// 函数名：void I2C_Ack(void);
// 作用：模拟主机应答
// 输入参数：无
// 输出参数：无
// */

// void I2C_Ack()
// {
//     SCL_LOW(); //SCL线先置低，方便数据线上变化数据
//     SDA_IN();  //SCL端口变成输入模式
//     SDA_LOW(); //SDA线置低，代表响应应答
//     delay_us(2);
//     SCL_HIGH(); //SCL钳住数据，数据不可变
//     delay_us(2);
//     SCL_LOW();  //结束响应的时段
//     SDA_HIGH(); //CPU释放数据总线
// }

// /*
// 函数名：void I2C_NAck(void);
// 作用：模拟主机非应答
// 输入参数：无
// 输出参数：无
// */

// void I2C_NAck()
// {
//     SCL_LOW();  //SCL线先置低，方便数据线上变化数据
//     SDA_IN();   //SCL端口变成输入模式
//     SDA_HIGH(); //SDA线置高，代表不响应应答
//     delay_us(2);
//     SCL_HIGH(); //SCL钳住数据，数据不可变
//     delay_us(2);
//     SCL_LOW();  //结束响应的时段
//     SDA_HIGH(); //CPU释放数据总线
// }

// uint8_t I2C_Wait_Ack()
// {
//     uint8_t ucErrTime = 0; //记录超时的计数参数
//     SDA_IN();              //SDA设为输入，说明主机现在处于接收数据状态，等待从机发送数据
//     SDA_HIGH();
//     delay_us(1);
//     SCL_HIGH();
//     delay_us(1);
//     while (SDA_READ) //非应答时进入此状态
//     {
//         ucErrTime++;         //计数加
//         if (ucErrTime > 250) //计数大于250说明无响应，终止通讯
//         {
//             I2C_STOP();
//             return 1;
//         }
//     }
//     SCL_LOW(); //拉低时钟线，等待数据变化
//     delay_us(1);
//     return 0;
// }

// void I2C_SEND(uint8_t byte)
// {
//     for (uint8_t t = 0; t < 8; t++) //按位显示状态，传输一个字节，也就是8位状态
//     {
//         if (byte & 0x80) //判断字节的最高位，如果为1，输出高电平，如果为0，输出低电平
//         {
//             SDA_HIGH();
//         }
//         else
//         {
//             SDA_LOW();
//         }
//         byte <<= 1; //移位操作，遍历总共的8位
//         delay_us(2);
//         SCL_HIGH(); //钳住数据，高电平数据线上的状态就改变不了了
//         delay_us(2);
//         SCL_LOW(); //置低位，为下次数据线上的状态改变做准备
//     }
// }

// uint8_t I2C_READ()
// {
//     uint8_t receive;
//     for (uint8_t i = 0; i < 8; i++)
//     {
//         SCL_LOW();   //scl拉低，sda总线变化
//         delay_us(2); //
//         SCL_HIGH();  //scl拉高，sda总线锁死

//         receive = (receive << 1) | SDA_READ; //读取数据总线的数据，按位来读取，从高位读到低位，移位顺延
//         delay_us(2);
//     }
//     return receive;
// }

// void I2C_SEND_BYTE(uint8_t slaveaddr, uint8_t registeraddr, uint8_t byte)
// {
//     I2C_START();            //通讯开始
//     I2C_SEND(slaveaddr);    //先发送从机的地址，寻址从机
//     I2C_Wait_Ack();         //得到回应，说明，电路中有这个外设器件
//     I2C_SEND(registeraddr); //寻址这个器件中的相关寄存器
//     I2C_Wait_Ack();         //得到回应，说明这个寄存器存在
//     I2C_SEND(byte);         //发送一个字节
//     I2C_Wait_Ack();         //等待回应
// }

// void I2C_SEND_BYTES(uint8_t slaveaddr, uint8_t registeraddr, uint8_t *pbuffer, uint16_t num)
// {
//     I2C_START();            //开始通讯
//     I2C_SEND(slaveaddr);    //寻址从机
//     I2C_Wait_Ack();         //等待回应
//     I2C_SEND(registeraddr); //寻址寄存器
//     I2C_Wait_Ack();         //等待回应

//     for (uint16_t t = 0; t < num; t++) //发送数组中的数据
//     {
//         I2C_SEND(*(pbuffer + t));
//         I2C_Wait_Ack(); //每发送一个字节，都需要一个应答
//     }
//     I2C_STOP(); //终止通讯
// }

// uint8_t I2C_READ_BYTE(uint8_t slaveaddr, uint8_t registeraddr)
// {
//     uint8_t temp;
//     I2C_START();            //开始通讯
//     I2C_SEND(slaveaddr);    //寻址从机
//     I2C_Wait_Ack();         //等待回应
//     I2C_SEND(registeraddr); //寻址寄存器
//     I2C_Wait_Ack();         //等待回应

//     delay_us(100);

//     I2C_START();             //重新通讯
//     I2C_SEND(slaveaddr + 1); //改为读数据
//     I2C_Wait_Ack();          //等待回应

//     temp = I2C_READ();
//     I2C_NAck();
//     I2C_STOP(); //通讯结束
//     return temp;
// }

// void I2C_READ_BYTES(uint8_t slaveaddr, uint8_t registeraddr, uint8_t *pbuffer, uint16_t num)
// {
//     I2C_START();            //开始通讯
//     I2C_SEND(slaveaddr);    //寻址从机
//     I2C_Wait_Ack();         //等待回应
//     I2C_SEND(registeraddr); //寻址寄存器
//     I2C_Wait_Ack();         //等待回应

//     delay_us(100);

//     I2C_START();             //重新通讯
//     I2C_SEND(slaveaddr + 1); //改为读数据
//     I2C_Wait_Ack();          //等待回应

//     for (uint16_t t = 0; t < num; t++) //存储数据
//     {
//         *(pbuffer + t) = I2C_READ();
//         if (t == num - 1) //字节没发完，必须给出应答，发完的给个非应答信号
//         {
//             I2C_Ack();
//         }
//         else
//         {
//             I2C_NAck();
//         }
//     }
//     I2C_STOP(); //通讯结束
// }
