#include <Arduino.h>
#include "YX65491.h"

YX6549::YX6549()
{
    Serial2.begin(115200);
}

void YX6549::init()
{
    delay(2000);
    Serial2.write(0XA5);
    Serial2.write(0X55);
    Serial2.write(0X12);
    Serial2.write(0X0C);
    delay(100);

    Serial2.write(0XA5);
    Serial2.write(0X56);
    Serial2.write(0X01);
    Serial2.write(0XFC);
    delay(100);
}

void YX6549::read()
{
    Serial2.write(0XA5);
    Serial2.write(0X56);
    Serial2.write(0X01);
    Serial2.write(0XFC);
    delay(100);
    Serial2.readBytes(Re_buf, 17);
    if (Re_buf[0] == 0x5A && Re_buf[1] == 0x5A) //检查帧头，帧尾
    {
        gyro[0] = (Re_buf[4] << 8 | Re_buf[5]); //合成数据，去掉小数点后2位
        gyro[1] = (Re_buf[6] << 8 | Re_buf[7]);
        gyro[2] = (Re_buf[8] << 8 | Re_buf[9]);

        YPR[0] = (Re_buf[10] << 8 | Re_buf[11]) / 100; //合成数据，去掉小数点后2位
        YPR[1] = (Re_buf[12] << 8 | Re_buf[13]) / 100;
        YPR[2] = (Re_buf[14] << 8 | Re_buf[15]) / 100;
        Serial1.print("gyro:\t");
        Serial1.print(gyro[0]);
        Serial1.print("\t");
        Serial1.print(gyro[1]);
        Serial1.print("\t");
        Serial1.print(gyro[2]);
        Serial1.print("  ,YPR:\t");
        Serial1.print(YPR[2], DEC);
        Serial1.print("\t"); //显示航向
        Serial1.print(YPR[1], DEC);
        Serial1.print("\t");          //显示俯仰角
        Serial1.println(YPR[0], DEC); //显示横滚角

        delay(50);
    }
}