
#include <stdint.h>
#include "LPC177x_8x.h"

/** \brief 生成ID为 x—y的标准帧组 
 *         默认选择CAN1
 */
#define STD_CAN_GRP(x, y)   \
    ((uint32_t)(((0 << 13) | (x)) << 16) | (((0 << 13) | (y))))

/** \brief 生成ID为 x—y的扩展帧组 */
#define EXT_CAN_GRP(x, y)   \
    ((uint64_t)((x) | (((uint64_t)(y)) << 32)))

#define CH_CAN1            (0UL)
#define CH_CAN2            (1UL)

/** \brief 选择标准滤波ID适用的通道 */
#define STD_CH_SEL(x)      ((x) << 13)

/** \brief 选择扩展滤波ID适用的通道 */
#define EXT_CH_SEL(x)      ((x) << 29)

typedef struct message_detail {
    uint8_t  len;

    /**
     *  0b00: 标准帧
     *  0b10: 扩展帧
     *  0b01: 远程帧
     *  0b11：远程帧
     */
    uint8_t  ff;
    uint32_t canid;  /* 长度与ff有关  */
    uint32_t dataa;
    uint32_t datab;
} message_detail_t;

typedef enum {
    LPC_BPS_1000K = 0x50002,
    LPC_BPS_800K  = 0x70002,
    LPC_BPS_500K  = 0x50005,
    LPC_BPS_250K  = 0x5000b,
    LPC_BPS_125K  = 0x50017,
    LPC_BPS_100K  = 0x70017,
    LPC_BPS_50K   = 0x5003b,
    LPC_BPS_20K   = 0x50095,
    LPC_BPS_10K   = 0x5012b,
} baud_sel_t;

typedef struct aftable {
    uint32_t  full_size;        /** FullCAN标识区大小 以ID个数计   */
    uint16_t *p_full_list;      /** 指向FullCAN ID列表的指针       */
    uint32_t  std_size;         /** 标准帧标识区大小 以ID个数计    */
    uint16_t *p_std_list;       /** 指向标准帧 ID列表的指针        */
    uint32_t  std_grp_size;     /** 标准帧组的组数                 */
    uint32_t *p_std_grp_list;   /** 指向标准帧 ID组列表的指针      */
    uint32_t  ext_size;         /** 扩展帧标识区大小 以ID个数计    */
    uint32_t *p_ext_list;       /** 指向扩展帧 ID列表的指针        */
    uint32_t  ext_grp_size;     /** 扩展帧组的组数                 */
    uint64_t *p_ext_grp_list;   /** 指向扩展帧 ID组列表的指针      */

} aftable_t;

#define init_aftable(aftable,                                  \
                     full_table,                               \
                     std_table,                                \
                     std_grp_table,                            \
                     ext_table,                                \
                     ext_grp_table)                            \
                                                               \
{                                                              \
    af_table.full_size = sizeof(full_table) / 2;               \
    af_table.p_full_list = full_table;                         \
    af_table.std_size = sizeof(std_table) / 2;                 \
    af_table.p_std_list = std_table;                           \
    af_table.std_grp_size = sizeof(std_grp_table) / 4;         \
    af_table.p_std_grp_list = std_grp_table;                   \
    af_table.ext_size = sizeof(ext_table) /4 ;                 \
    af_table.p_ext_list = ext_table;                           \
    af_table.ext_grp_size = sizeof(ext_grp_table) / 8;         \
    af_table.p_ext_grp_list = ext_grp_table;                   \
}


typedef enum {
    off_mode     = 0x1, /** 关闭模式，不接收报文   */
    bypass_mode  = 0x2, /** 旁路模式，接收所有报文 */
    full_run     = 0x4, /** FullCAN 运行模式       */
    normal_run   = 0x0, /** 普通运行模式           */
} af_mode_t;

///**
// *  \brief CAN端口的初始化
// */
//void lpc1700_can_init (uint8_t ch, uint32_t baud);

/**
 *  \brief 往CAN总线上发送数据
 *
 *  \param ch 使用的CAN通道 0-1 表示CAN1-CAN2
 *  \param buf_num 要使用的缓冲编号  0-2 表示使用1-3号缓冲
 *  \param message_can 指向要发送的CAN报文的指针
 *  \retval 0 发送成功
 *  \retval -1 发送失败
 */
//int lpc1700_can_data_send (uint8_t           ch,
//                           uint8_t           buf_num,
//                           message_detail_t *p_message);


/**
 *  \brief 接收CAN总线上的数据
 */
//int lpc1700_can_data_recv (uint8_t ch, message_detail_t *p_message);

/**
 *  \brief 接收FullCAN模式下的数据
 */
//int lpc1700_can_data_fcan_recv (uint8_t ch, message_detail_t *p_message);


/**
 *  \brief 验收滤波器配置
 *
 *  \param can_num CAN模块号   0-1 表示CAN1-CAN2
 *  \param mode 滤波模式
 *  \param p_table 滤波表格
 *
 *
 */
uint32_t lpc1700_can_af_config ( af_mode_t mode,
                                aftable_t *p_table);


/**
 *  \brief CAN波特率设置
 *  \note 重新设置波特率会要求复位相应的CAN模块
 */
//void lpc1700_can_baud_set (uint8_t ch, uint32_t baud);

