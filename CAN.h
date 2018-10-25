/****************************************Copyright (c)****************************************************
**                            *** *** *** Co.,LTD.
**
**                            http://www.***.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  DWIN.h
** Latest modified Date:       2014-1-6
** Latest Version:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 AndyLiu
** Created date:               2015-3-19
** Version:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:                AndyLiu
** Modified date:              2015-3-19
** Version:
** Descriptions:
**
*********************************************************************************************************/


#ifndef __CAN_H_
#define __CAN_H_

#include "AllHand.h"

#ifdef   IN_CAN_GLOBALS
#define  IN_CAN_EXT
#else
#define  IN_CAN_EXT  extern
#endif




//#include "LPC177x_8x.h"

/*********************************************************************************************************
**               C++代码兼容                                                                            
*********************************************************************************************************/

/*********************************************************************************************************
**                    Fpclk=48MHz CAN标准波特率值                                                       
*********************************************************************************************************/
//#define BPS_1000K   0x50005
//#define BPS_800K    0x2000B
//#define BPS_500K    0x5000B
//#define BPS_250K    0x50017
//#define BPS_125K    0x5002F
//#define BPS_100K    0x5003B
//#define BPS_50K     0x50077
//#define BPS_20K     0x5012B
//#define BPS_10K     0x50257
//#define BPS_5K      0x2F01E0

/*********************************************************************************************************
**                    Fpclk=60MHz CAN标准波特率值                                                       
*********************************************************************************************************/
#define BPS_1000K   0x160005
#define BPS_800K    0x2E0003
#define BPS_500K    0x2F0005
#define BPS_250K    0x2F000B
#define BPS_125K    0x2F0017
#define BPS_100K    0x1B0027
#define BPS_50K     0x2F003B
#define BPS_20K     0xFF0077
#define BPS_10K     0xFF00EF
#define BPS_5K      0xFF01DF

#define CANOFFSET   0x4000
#define RGE(Address)    (*((volatile unsigned long*)Address))
#define CANAPP_GLOBAL   extern


 
/*********************************************************************************************************
**   定义 CAN 报文收发项 结构体:
*********************************************************************************************************/
typedef struct _MessageDetail
{
    unsigned char LEN;
    unsigned char FF;                                                   /* 是否标准帧                   */
    unsigned int CANID;                                                 /* 长度与FF有关                 */
    unsigned int DATAA;
    unsigned int DATAB;
}MessageDetail;


typedef struct                //dc_batter
{
  
	 uint16_t  Set_Voltage   ;       //设置电源电压
	 uint16_t    Set_Current   ;       //设置电源电流
	 uint8_t  Set_Statue    ;        //设置状态 1开始设置参数  0设置成功或是初始   英可瑞 设置状态 1开始设置参数  0设置成功或是初始
	 uint8_t  Set_Statue0    ;       //设置状态 1开始设置参数  0设置成功或是初始   英可瑞 设置状态 1开始设置参数  0设置成功或是初始
	 uint8_t  Set_Statue1    ;       //设置状态 1开始设置参数  0设置成功或是初始   英可瑞 设置状态 1开始设置参数  0设置成功或是初始
	 uint8_t  swithch        ;       //监控状态1   电池需要开启的状态             英可瑞   电池需要开启的状态
	 uint8_t  flag           ;       //电池开关标志  
	
	 uint16_t Out_Voltage    ;       //电源模块输出电压  
	 uint16_t Out_Current    ;       //电源模块输出电流
	
	 uint32_t batter_statuts ;       //电源模块当前状态  
	
	 
}Charge_batter ;


/*********************************************************************************************************
**   定义 CANMOD 寄存器:
1.This register controls the basic operating mode of the CAN Controller. 
2.Bits not listed read as 0 and should be written as 0.
*********************************************************************************************************/
typedef union   _canmod_
{
    unsigned long DWord;
    struct {
        unsigned int    RM      :1;                                     /* 定义RM位(复位位)             */
        unsigned int    LOM     :1;                                     /*定义LOM位(只听模式位)         */

        /*
        * 定义STM位 "0"发送的信息必须被应答才被认可
        * "1"自测试模式,CANCMR的SRR位一起使用，可以达到自发自收的效果
        */
        unsigned int    STM     :1; 
        /*
         * 定义TPM位 "0"3个发送缓冲区的优先级由各自的CAN ID决定
         * "1"3个发送缓冲区的优先级由各自的Tx优先级域决定
         */
        unsigned int    TPM     :1;
                
        unsigned int    SM      :1;                                     /* 定义SM位(睡眠模式位)         */

        unsigned int    RPM     :1;
        /*
        * 定义RPM位 "0"如果传输的是显性位，Rx和Tx脚为低电平
        * "1"翻转极性模式--如果传输的是显性位，Rx脚为高电平
        */
        unsigned int    RSV1    :1;                                     /* 保留位                       */
        unsigned int    TM      :1;                                     /* 定义TM位(测试模式)           */
        unsigned int    RSV24   :24;                                    /* 保留位                       */
    }Bits;
}REG_CANMOD;

/*********************************************************************************************************
**   定义 CAN 帧结构体:
*********************************************************************************************************/
typedef struct _CANFRMAE
{
    unsigned long CANID;                                                   /* 帧ID                         */ 
    unsigned char LEN;                                                  /* 数据长度                     */
    unsigned char RTR;                                                  /* 远程帧标志                   */
    unsigned char FF;                                                   /* 扩展帧标志                   */
    unsigned char Data[8];                                              /* 帧数据                       */
}CANFRAME;

/*********************************************************************************************************
** Function name:  	unsigned char Enter_SWRst(unsigned char Ch);
** Descriptions:  	Ch:CAN控制器号，0表示第一路CAN,CAN控制器进入软件复位模式
** Returned value:      0：          失败
**                      1:           成功	
*********************************************************************************************************/
CANAPP_GLOBAL unsigned char Enter_SWRst(unsigned char Ch);

/**********************************************************************************************************
** Function name:       unsigned char Quit_SWRst(unsigned char Ch);
** Descriptions:        Ch:CAN控制器号，0表示第一路CAN,CAN控制器退出软件复位模式
** Returned value:      0：          失败
**                      1:           成功	
*********************************************************************************************************/
CANAPP_GLOBAL unsigned char Quit_SWRst(unsigned char Ch);

/*********************************************************************************************************
** Function name:   	unsigned char CAN_Init(unsigned char Ch, unsigned long Baud);
** Descriptions:        CAN控制器退出软件复位模式
** input parameters:    Ch:          CAN控制器号，0表示第一路CAN
**                      Baud:        CAN波特率值
** Returned value:      无
*********************************************************************************************************/
CANAPP_GLOBAL void CAN_Init(unsigned char Ch, unsigned long Baud);

/*********************************************************************************************************
** Function name:  	unsigned char writedetail(unsigned char LEN,unsigned char FF, unsigned int 
**                      ID, unsigned char *data);
** Descriptions: 	用户填写发送 帧信息
** input parameters:    LEN:         数据长度
**                      *data:       发送数据所在的数组 
** Returned value:      操作成功返回 1 失败返回 0
*********************************************************************************************************/
CANAPP_GLOBAL unsigned char writedetail(unsigned char LEN,unsigned char FF,
                                        unsigned int ID,unsigned char *data);

/*********************************************************************************************************
** Function name: 	unsigned char CANSend(unsigned char Ch, unsigned char BUFNum);
** Descriptions:        CAN控制器退出软件复位模式
** input parameters:    Ch:CAN控制器号，0表示第一路CAN
**                       BUFNum 选择缓冲区
                         MessageDetailT 报文的特征信息及数据
** Returned value:无
*********************************************************************************************************/
CANAPP_GLOBAL unsigned char CANSend(unsigned char Ch, unsigned char BUFNum);



CANAPP_GLOBAL void CAN1_WriteData(unsigned int ID,unsigned char CMD,unsigned char FUNCTION)  ;
 
//CANAPP_GLOBAL void CAN1_WriteData(unsigned long ID,unsigned char ADDR,unsigned char CMD,unsigned char FUNCTION) ;

CANAPP_GLOBAL void CAN2_WriteData(unsigned long ID, unsigned char datalen) ;

CANAPP_GLOBAL void CAN0_Data_Pro(void)  ;

CANAPP_GLOBAL void CAN1_Data_Pro(void)  ;

CANAPP_GLOBAL  void main_can0(void)   ;
CANAPP_GLOBAL  void main_can1(void)   ;

CANAPP_GLOBAL void CAN_var_init(void)  ;
 

#ifdef __cplusplus
}
#endif 
                                                                       /*  __cplusplus                 */
#endif

/********************************************************************************************************
**                                        End Of File                                                                             
********************************************************************************************************/
