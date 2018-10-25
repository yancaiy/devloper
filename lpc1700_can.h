
#include <stdint.h>
#include "LPC177x_8x.h"

/** \brief ����IDΪ x��y�ı�׼֡�� 
 *         Ĭ��ѡ��CAN1
 */
#define STD_CAN_GRP(x, y)   \
    ((uint32_t)(((0 << 13) | (x)) << 16) | (((0 << 13) | (y))))

/** \brief ����IDΪ x��y����չ֡�� */
#define EXT_CAN_GRP(x, y)   \
    ((uint64_t)((x) | (((uint64_t)(y)) << 32)))

#define CH_CAN1            (0UL)
#define CH_CAN2            (1UL)

/** \brief ѡ���׼�˲�ID���õ�ͨ�� */
#define STD_CH_SEL(x)      ((x) << 13)

/** \brief ѡ����չ�˲�ID���õ�ͨ�� */
#define EXT_CH_SEL(x)      ((x) << 29)

typedef struct message_detail {
    uint8_t  len;

    /**
     *  0b00: ��׼֡
     *  0b10: ��չ֡
     *  0b01: Զ��֡
     *  0b11��Զ��֡
     */
    uint8_t  ff;
    uint32_t canid;  /* ������ff�й�  */
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
    uint32_t  full_size;        /** FullCAN��ʶ����С ��ID������   */
    uint16_t *p_full_list;      /** ָ��FullCAN ID�б��ָ��       */
    uint32_t  std_size;         /** ��׼֡��ʶ����С ��ID������    */
    uint16_t *p_std_list;       /** ָ���׼֡ ID�б��ָ��        */
    uint32_t  std_grp_size;     /** ��׼֡�������                 */
    uint32_t *p_std_grp_list;   /** ָ���׼֡ ID���б��ָ��      */
    uint32_t  ext_size;         /** ��չ֡��ʶ����С ��ID������    */
    uint32_t *p_ext_list;       /** ָ����չ֡ ID�б��ָ��        */
    uint32_t  ext_grp_size;     /** ��չ֡�������                 */
    uint64_t *p_ext_grp_list;   /** ָ����չ֡ ID���б��ָ��      */

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
    off_mode     = 0x1, /** �ر�ģʽ�������ձ���   */
    bypass_mode  = 0x2, /** ��·ģʽ���������б��� */
    full_run     = 0x4, /** FullCAN ����ģʽ       */
    normal_run   = 0x0, /** ��ͨ����ģʽ           */
} af_mode_t;

///**
// *  \brief CAN�˿ڵĳ�ʼ��
// */
//void lpc1700_can_init (uint8_t ch, uint32_t baud);

/**
 *  \brief ��CAN�����Ϸ�������
 *
 *  \param ch ʹ�õ�CANͨ�� 0-1 ��ʾCAN1-CAN2
 *  \param buf_num Ҫʹ�õĻ�����  0-2 ��ʾʹ��1-3�Ż���
 *  \param message_can ָ��Ҫ���͵�CAN���ĵ�ָ��
 *  \retval 0 ���ͳɹ�
 *  \retval -1 ����ʧ��
 */
//int lpc1700_can_data_send (uint8_t           ch,
//                           uint8_t           buf_num,
//                           message_detail_t *p_message);


/**
 *  \brief ����CAN�����ϵ�����
 */
//int lpc1700_can_data_recv (uint8_t ch, message_detail_t *p_message);

/**
 *  \brief ����FullCANģʽ�µ�����
 */
//int lpc1700_can_data_fcan_recv (uint8_t ch, message_detail_t *p_message);


/**
 *  \brief �����˲�������
 *
 *  \param can_num CANģ���   0-1 ��ʾCAN1-CAN2
 *  \param mode �˲�ģʽ
 *  \param p_table �˲����
 *
 *
 */
uint32_t lpc1700_can_af_config ( af_mode_t mode,
                                aftable_t *p_table);


/**
 *  \brief CAN����������
 *  \note �������ò����ʻ�Ҫ��λ��Ӧ��CANģ��
 */
//void lpc1700_can_baud_set (uint8_t ch, uint32_t baud);

