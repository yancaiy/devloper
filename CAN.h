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
**               C++�������                                                                            
*********************************************************************************************************/

/*********************************************************************************************************
**                    Fpclk=48MHz CAN��׼������ֵ                                                       
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
**                    Fpclk=60MHz CAN��׼������ֵ                                                       
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
**   ���� CAN �����շ��� �ṹ��:
*********************************************************************************************************/
typedef struct _MessageDetail
{
    unsigned char LEN;
    unsigned char FF;                                                   /* �Ƿ��׼֡                   */
    unsigned int CANID;                                                 /* ������FF�й�                 */
    unsigned int DATAA;
    unsigned int DATAB;
}MessageDetail;


typedef struct                //dc_batter
{
  
	 uint16_t  Set_Voltage   ;       //���õ�Դ��ѹ
	 uint16_t    Set_Current   ;       //���õ�Դ����
	 uint8_t  Set_Statue    ;        //����״̬ 1��ʼ���ò���  0���óɹ����ǳ�ʼ   Ӣ���� ����״̬ 1��ʼ���ò���  0���óɹ����ǳ�ʼ
	 uint8_t  Set_Statue0    ;       //����״̬ 1��ʼ���ò���  0���óɹ����ǳ�ʼ   Ӣ���� ����״̬ 1��ʼ���ò���  0���óɹ����ǳ�ʼ
	 uint8_t  Set_Statue1    ;       //����״̬ 1��ʼ���ò���  0���óɹ����ǳ�ʼ   Ӣ���� ����״̬ 1��ʼ���ò���  0���óɹ����ǳ�ʼ
	 uint8_t  swithch        ;       //���״̬1   �����Ҫ������״̬             Ӣ����   �����Ҫ������״̬
	 uint8_t  flag           ;       //��ؿ��ر�־  
	
	 uint16_t Out_Voltage    ;       //��Դģ�������ѹ  
	 uint16_t Out_Current    ;       //��Դģ���������
	
	 uint32_t batter_statuts ;       //��Դģ�鵱ǰ״̬  
	
	 
}Charge_batter ;


/*********************************************************************************************************
**   ���� CANMOD �Ĵ���:
1.This register controls the basic operating mode of the CAN Controller. 
2.Bits not listed read as 0 and should be written as 0.
*********************************************************************************************************/
typedef union   _canmod_
{
    unsigned long DWord;
    struct {
        unsigned int    RM      :1;                                     /* ����RMλ(��λλ)             */
        unsigned int    LOM     :1;                                     /*����LOMλ(ֻ��ģʽλ)         */

        /*
        * ����STMλ "0"���͵���Ϣ���뱻Ӧ��ű��Ͽ�
        * "1"�Բ���ģʽ,CANCMR��SRRλһ��ʹ�ã����Դﵽ�Է����յ�Ч��
        */
        unsigned int    STM     :1; 
        /*
         * ����TPMλ "0"3�����ͻ����������ȼ��ɸ��Ե�CAN ID����
         * "1"3�����ͻ����������ȼ��ɸ��Ե�Tx���ȼ������
         */
        unsigned int    TPM     :1;
                
        unsigned int    SM      :1;                                     /* ����SMλ(˯��ģʽλ)         */

        unsigned int    RPM     :1;
        /*
        * ����RPMλ "0"��������������λ��Rx��Tx��Ϊ�͵�ƽ
        * "1"��ת����ģʽ--��������������λ��Rx��Ϊ�ߵ�ƽ
        */
        unsigned int    RSV1    :1;                                     /* ����λ                       */
        unsigned int    TM      :1;                                     /* ����TMλ(����ģʽ)           */
        unsigned int    RSV24   :24;                                    /* ����λ                       */
    }Bits;
}REG_CANMOD;

/*********************************************************************************************************
**   ���� CAN ֡�ṹ��:
*********************************************************************************************************/
typedef struct _CANFRMAE
{
    unsigned long CANID;                                                   /* ֡ID                         */ 
    unsigned char LEN;                                                  /* ���ݳ���                     */
    unsigned char RTR;                                                  /* Զ��֡��־                   */
    unsigned char FF;                                                   /* ��չ֡��־                   */
    unsigned char Data[8];                                              /* ֡����                       */
}CANFRAME;

/*********************************************************************************************************
** Function name:  	unsigned char Enter_SWRst(unsigned char Ch);
** Descriptions:  	Ch:CAN�������ţ�0��ʾ��һ·CAN,CAN���������������λģʽ
** Returned value:      0��          ʧ��
**                      1:           �ɹ�	
*********************************************************************************************************/
CANAPP_GLOBAL unsigned char Enter_SWRst(unsigned char Ch);

/**********************************************************************************************************
** Function name:       unsigned char Quit_SWRst(unsigned char Ch);
** Descriptions:        Ch:CAN�������ţ�0��ʾ��һ·CAN,CAN�������˳������λģʽ
** Returned value:      0��          ʧ��
**                      1:           �ɹ�	
*********************************************************************************************************/
CANAPP_GLOBAL unsigned char Quit_SWRst(unsigned char Ch);

/*********************************************************************************************************
** Function name:   	unsigned char CAN_Init(unsigned char Ch, unsigned long Baud);
** Descriptions:        CAN�������˳������λģʽ
** input parameters:    Ch:          CAN�������ţ�0��ʾ��һ·CAN
**                      Baud:        CAN������ֵ
** Returned value:      ��
*********************************************************************************************************/
CANAPP_GLOBAL void CAN_Init(unsigned char Ch, unsigned long Baud);

/*********************************************************************************************************
** Function name:  	unsigned char writedetail(unsigned char LEN,unsigned char FF, unsigned int 
**                      ID, unsigned char *data);
** Descriptions: 	�û���д���� ֡��Ϣ
** input parameters:    LEN:         ���ݳ���
**                      *data:       �����������ڵ����� 
** Returned value:      �����ɹ����� 1 ʧ�ܷ��� 0
*********************************************************************************************************/
CANAPP_GLOBAL unsigned char writedetail(unsigned char LEN,unsigned char FF,
                                        unsigned int ID,unsigned char *data);

/*********************************************************************************************************
** Function name: 	unsigned char CANSend(unsigned char Ch, unsigned char BUFNum);
** Descriptions:        CAN�������˳������λģʽ
** input parameters:    Ch:CAN�������ţ�0��ʾ��һ·CAN
**                       BUFNum ѡ�񻺳���
                         MessageDetailT ���ĵ�������Ϣ������
** Returned value:��
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
