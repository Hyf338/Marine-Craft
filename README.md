﻿# JMU_ETA_Fly on The Sea

<p align="center">
  <a href="https://img.shields.io/badge/language-C-brigreen.svg?style=flat-square"><img src="https://img.shields.io/badge/language-C-brigreen.svg?style=flat-square" alt="C"></a>
</p>

## 简介
2019集大电协 海洋航行器

工具     | 描述
-------- | -----
Altium Design|PCB设计
Keil|软件编程
123D Design|3D软件


## 目录说明
````
+——Marine craft
|---- 3D model: 【设计文档】
|----+ hardware:【电路设计】  
|       ├──Control V1.0【主控板】
|       ├──Control V2.0【主控电路板-最终版】
|       ├──Infrared reception【红外接收盘】
|       ├──Power Transfer【临时电源转接】
|---+ software:【软件设计】
|       ├──Craft【航行器程序】
|       ├──remoted【遥控器调试】
````

## 3D model
- 红外屏蔽罩3D模型设计
![3D信号屏蔽罩](/Docs/Pictures/infrared.png "信号屏蔽罩")



## Hardware
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

- [x]  船舶主控板

- 航行器主控板模块流程图

![流程图](/Docs/Pictures/flow.png "流程图")

- 航行器主控板

![主控板](/Docs/Pictures/Controller-Board.png "主控板")


- [x] 一体化红外接收盘

![一体化红外接收盘](/Docs/Pictures/Infrared-Board.png "一体化红外接收盘")



## Keil

