# JMU_ETA_Fly on The Sea
[test]
@[TOC](目录：)

## 简介
2019集大电协 海洋航行器

工具     | 描述
-------- | -----
Altium Design|PCB设计
Keil|软件编程
123D Design|3D软件


## 目录说明
+——Marine craft

|---- 3D model: 【设计文档】

|----+ hardware:【电路设计】  

|       ├──Control V1.0【主控板】

|       ├──Control V2.0【主控电路板-最终版】

|       ├──Infrared reception【红外接收盘】

|       ├──Power Transfer【临时电源转接】

|---+ software:【软件设计】

|       ├──Craft

|       ├──remoted


## Hardware
- [x] 一体化红外接收盘
- [x]  船舶主控板
- 主控与外设描述

硬件     | 描述
-------- | -----
芯片信号  |STM32F103
串口  | ZIGBEE
蓝牙  | HC-05
舵机  | EMAX ES08MA
电机|380
显示|oled

- 端口定义

功能     | 端口
-------- | -----
红外盘接收  |A8.B13.B14.B15.C6.C7.C8.C9
蓝牙&串口  | USART2_TX -- A2  . USART2_RX -- A3
蓝牙&串口  | USART1_TX -- A9  . USART1_RX -- A10
舵机  | TIM2_CH2 -- A1
电机|TIM3_CH1 --B4 .   TIM3_CH2 -- B5
OLED|DC -- B6. RES -- B7 . D1 -- B8 . D0 -- B9

- 航行器主控板模块流程图
```mermaid gantt
graph LR
A[6V电源] -- 升压 --> B[12V电源]
A --稳压--> C[5V电源]
C --> D[红外]
C --> E[舵机]
C --稳压--> F[3.3V电源]
F-->G[芯片供电]
B -->H[驱动芯片]
H -->I[PWM驱动]
```



## Keil

