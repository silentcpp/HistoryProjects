// #############################################################################
// *****************************************************************************
//                  Copyright (c) 2007, Advantech eAutomation Corp.
//      THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY
//               INFORMATION WHICH IS THE PROPERTY OF ADVANTECH AUTOMATION CORP.
//
//    ANY DISCLOSURE, USE, OR REPRODUCTION, WITHOUT WRITTEN AUTHORIZATION FROM
//               ADVANTECH AUTOMATION CORP., IS STRICTLY PROHIBITED.
// *****************************************************************************
// #############################################################################
//
// File:    AdvCan.h
// Created: 5/10/2007
// Version: 1.0
// Description:  Defines data structures and function announces
// -----------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <winioctl.h>
#pragma pack(1)
/*****************************************************************************
DESCRIPTION: Standard baud  
*****************************************************************************/
#define CAN_TIMING_10K          10
#define CAN_TIMING_20K          20
#define CAN_TIMING_50K          50	
#define CAN_TIMING_100K         100
#define CAN_TIMING_125K         125
#define CAN_TIMING_250K         250
#define CAN_TIMING_500K         500	
#define CAN_TIMING_800K         800	
#define CAN_TIMING_1000K        1000

/*****************************************************************************
DESCRIPTION: Acceptance filter mode  
*****************************************************************************/
#define PELICAN_SINGLE_FILTER   1
#define PELICAN_DUAL_FILTER     0

/*****************************************************************************
DESCRIPTION: CAN data length  
*****************************************************************************/
#define DATALENGTH              8                       /* CAN data length */


/*****************************************************************************
DESCRIPTION: CAN frame flag 
*****************************************************************************/
#define MSG_RTR                 (1<<0)                  /* RTR Message */
#define MSG_OVR                 (1<<1)                  /* CAN controller Msg overflow error */
#define MSG_EXT                 (1<<2)                  /* Extended message format */
#define MSG_SELF                (1<<3)                  /* Message received from own tx */
#define MSG_PASSIVE             (1<<4)                  /* CAN Controller in error passive */
#define MSG_BUSOFF              (1<<5)                  /* CAN Controller Bus Off  */
#define MSG_BOVR                (1<<7)                  /* Receive buffer overflow */


/*****************************************************************************
DESCRIPTION: For CAN frame id. if flags of frame point out 
some errors(MSG_OVR, MSG_PASSIVE, MSG_BUSOFF, MSG_BOUR), 
then id of frame is equal to ERRORID
*****************************************************************************/
#define ERRORID                 0xffffffff


/*****************************************************************************
DESCRIPTION: CAN frame use by driver 
*****************************************************************************/
typedef struct {
    int                     flags;                  /* Flags, indicating or controlling special message properties */
    int                     cob;                    /* CAN object number, used in Full CAN */
    ULONG                   id;                     /* CAN message ID, 4 bytes  */
    short int               length;                 /* Number of bytes in the CAN message */
    UCHAR                   data[DATALENGTH];       /* Data, 0...8 bytes */
} canmsg_t;


/*****************************************************************************
DESCRIPTION: IOCTL code 
*****************************************************************************/
#define ADS_TYPE FILE_DEVICE_UNKNOWN
#define ADS_IOCTL_INDEX  0x950

/* IOCTL command request */
#define CAN_IOCTL_COMMAND \
    CTL_CODE(ADS_TYPE, ADS_IOCTL_INDEX,    METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_CAN_COMMAND CAN_IOCTL_COMMAND

/* IOCTL configuration request */
#define CAN_IOCTL_CONFIG \
    CTL_CODE(ADS_TYPE, ADS_IOCTL_INDEX+1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_CAN_CONFIG CAN_IOCTL_CONFIG

/* IOCTL status request */
#define CAN_IOCTL_STATUS \
    CTL_CODE(ADS_TYPE, ADS_IOCTL_INDEX+5, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_CAN_STATUS CAN_IOCTL_STATUS


/*****************************************************************************
DESCRIPTION: IOCTL command request parameter structure 
*****************************************************************************/
struct Command_par {
    int                     cmd;                    /* special driver command */
    int                     target;                 /* special configuration target */
    ULONG                   val1;                   /* 1. parameter  */
    ULONG                   val2;                   /* 2. parameter  */
    int                     error;                  /* return value */
    ULONG                   retval;                 /* return value */

};


/*****************************************************************************
DESCRIPTION: IOCTL command cmd targets
*****************************************************************************/
#define CMD_START               1                       /* Start chip */
#define CMD_STOP                2                       /* Stop chip */
#define CMD_RESET               3                       /* Reset chip */
#define CMD_CLEARBUFFERS        4                       /* Clear the receive buffer */


/*****************************************************************************
DESCRIPTION: IOCTL command request parameter structure
*****************************************************************************/
typedef struct Command_par Command_par_t ; 


/*****************************************************************************
DESCRIPTION: IOCTL configure cmd targets
*****************************************************************************/
#define CONF_ACC                0                       /* Acceptance code register and mask register*/
#define CONF_ACCM               1                       /* Acceptance mask only */
#define CONF_ACCC               2                       /* Acceptance code only */
#define CONF_TIMING             3                       /* Bit timing */
#define CONF_LISTEN_ONLY_MODE   8                       /* For SJA1000 PeliCAN */
#define CONF_SELF_RECEPTION     9                       /* Self reception */
#define CONF_TIMEOUT            13                      /* Configure read and write timeout one time */
#define CONF_ACC_FILTER         20                      /* Acceptance filter mode: 1-Single, 0-Dual*/

/*****************************************************************************
DESCRIPTION: IOCTL configuration request parameter structure
*****************************************************************************/
typedef struct Command_par  Config_par_t ; 


/*****************************************************************************
DESCRIPTION: IOCTL generic CAN controller status request parameter structure 
*****************************************************************************/
typedef struct {
    unsigned int            baud;                   /* Actual bit rate */
    unsigned int            status;                 /* CAN controller status register, address 2 */
    unsigned int            error_warning_limit;    /* The error warning limit, address 13 */
    unsigned int            rx_errors;              /* Content of RX error counter, address 14 */
    unsigned int            tx_errors;              /* Content of TX error counter, address 15 */
    unsigned int            error_code;             /* Content of error code register, address 12 */
    unsigned int            rx_buffer_size;         /* Size of rx buffer*/
    unsigned int            rx_buffer_used;         /* number of messages*/
    unsigned int            tx_buffer_size;         /* Size of tx buffer for wince, windows not use tx buffer*/
    unsigned int            tx_buffer_used;         /* Number of message for wince, windows not use tx buffer s*/
    ULONG                   retval;                 /* Return value*/
    unsigned int            type;                   /* CAN controller/driver type*/
    unsigned int            acceptancecode;         /* Acceptance code */
    unsigned int            acceptancemask;         /* Acceptance mask */
    unsigned int            acceptancemode;         /**< Acceptance Filter Mode: 1:Single 0:Dual */
    unsigned int            selfreception;          /* Self reception */
    unsigned int            readtimeout;            /* Read timeout */
    unsigned int            writetimeout;           /* Write timeout */
} CanStatusPar_t;

#pragma pack()
