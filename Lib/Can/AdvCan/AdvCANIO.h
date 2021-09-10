// #############################################################################
// *****************************************************************************
//                  Copyright (c) 2009, Advantech Automation Corp.
//      THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY
//               INFORMATION WHICH IS THE PROPERTY OF ADVANTECH AUTOMATION CORP.
//
//    ANY DISCLOSURE, USE, OR REPRODUCTION, WITHOUT WRITTEN AUTHORIZATION FROM
//               ADVANTECH AUTOMATION CORP., IS STRICTLY PROHIBITED.
// *****************************************************************************

// #############################################################################
//
// File:    AdvCANIO.h
// Created: 4/8/2009
// Version: 1.0
// Description: Implements IO function about how to access CAN WDM&CE driver
//
// -----------------------------------------------------------------------------
#include "AdvCan.h"

#define SUCCESS                            0                                      //Status definition : success
#define OPERATION_ERROR                   -1                                      //Status definition : device error or parameter error
#define TIME_OUT                          -2                                      //Status definition : time out


/*****************************************************************************
*
*    acCanOpen
*
*    Purpose:
*        Open can port by name 
*		
*
*    Arguments:
*        PortName            - port name
*        synchronization     - TRUE, synchronization ; FALSE, asynchronous
*
*    Returns:
*        Hanlde of device 
*
*****************************************************************************/
HANDLE acCanOpen(TCHAR *PortName, BOOL synchronization=FALSE);

/*****************************************************************************
*
*    acCanClose
*
*    Purpose:
*        Close can port by handle 
*		
*
*    Arguments:
*        hDevice          - handle of device
*
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acCanClose(HANDLE hDevice);

/*****************************************************************************
*
*    acEnterResetMode
*
*    Purpose:
*        Enter reset mode.
*		
*
*    Arguments:
*        hDevice            - handle of device
*
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acEnterResetMode(HANDLE hDevice);

/*****************************************************************************
*
*    acEnterWorkMode
*
*    Purpose:
*        Enter work mode 
*		
*
*    Arguments:
*        hDevice        - handle of device
*
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acEnterWorkMode(HANDLE hDevice);

/*****************************************************************************
*
*    acClearRxFifo
*
*    Purpose:
*        Clear can port rx buffer by handle 
*		
*
*    Arguments:
*        hDevice        - handle of device
*
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acClearRxFifo(HANDLE hDevice);

/*****************************************************************************
*
*    acSetBaud
*
*    Purpose:
*        Set baudrate of the CAN Controller.The two modes of configuring
*     baud rate are custom mode and standard mode.
*     -   Custom mode
*         If Baud Rate value is user defined, driver will write the first 8
*         bit of low 16 bit in BTR0 of SJA1000.
*         The lower order 8 bit of low 16 bit will be written in BTR1 of SJA1000.
*     -   Standard mode
*         Target value     BTR0      BTR1      Setting value 
*           10K            0x31      0x1c      10 
*           20K            0x18      0x1c      20 
*           50K            0x09      0x1c      50 
*          100K            0x04      0x1c      100 
*          125K            0x03      0x1c      125 
*          250K            0x01      0x1c      250 
*          500K            0x00      0x1c      500 
*          800K            0x00      0x16      800 
*         1000K            0x00      0x14      1000 
*		
*
*    Arguments:
*        hDevice        - handle of device
*        nBaud          - baudrate will be set
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acSetBaud(HANDLE hDevice, unsigned int nBaud);

/*****************************************************************************
*
*    acSetBaudRegister
*
*    Purpose:
*        Configures baud rate by custom mode.
*		
*
*    Arguments:
*        hDevice        - handle of device
*        Btr0           - BTR0 register value.
*        Btr1           - BTR1 register value.
*    Returns:
*	 =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acSetBaudRegister(HANDLE hDevice, unsigned char Btr0, unsigned char Btr1);

/*****************************************************************************
*
*    acSetTimeOut
*
*    Purpose:
*        Set Timeout for read and write
*		
*
*    Arguments:
*        hDevice           - handle of device
*        ulReadTimeOut     - ms
*         ulWriteTimeOut   - ms
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acSetTimeOut(HANDLE hDevice, ULONG ulReadTimeOut, ULONG ulWriteTimeOut);

/*****************************************************************************
*
*    acSetSelfReception
*
*    Purpose:
*        Set Self Reception mode
*		
*
*    Arguments:
*        hDevice        - handle of device
*        bSelfFlag      - TRUE, open self reception; FALSE close self reception
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acSetSelfReception(HANDLE hDevice, BOOL bSelfFlag);

/*****************************************************************************
*
*    acSetListenOnlyMode
*
*    Purpose:
*        Set listen only mode
*	
*
*    Arguments:
*        hDevice            - Handle of device
*        bListerOnlyFlag    - TRUE, open only listen mode; FALSE, close only listen mode
*    Returns:
*        =0 succeeded; or <0 Failed 
*
*****************************************************************************/
int acSetListenOnlyMode( HANDLE hDevice, BOOL bListerOnlyFlag);

/*****************************************************************************
*
*    acSetAcceptanceFilterMode
*
*    Purpose:
*        Set acceptance filter mode
*	
*
*    Arguments:
*        hDevice         - Handle of device
*        nFilterMode     - PELICAN_SINGLE_FILTER, single filter mode; PELICAN_DUAL_FILTER, dule filter mode
*    Returns:
*        =0 succeeded; or <0 Failed 
*
*****************************************************************************/
int acSetAcceptanceFilterMode( HANDLE hDevice, int nFilterMode );


/*****************************************************************************
*
*    acSetAcceptanceFilterCode
*
*    Purpose:
*        Set acceptance code
*		
*
*    Arguments:
*        hDevice              - handle of device
*        ulAcceptanceCode		- acceptance code
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acSetAcceptanceFilterCode(HANDLE hDevice, ULONG ulAcceptanceCode);

/*****************************************************************************
*
*    acSetAcceptanceFilterMask
*
*    Purpose:
*        Set acceptance mask
*		
*
*    Arguments:
*        hDevice              - handle of device
*        ulAcceptanceMask     - accept mask code
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acSetAcceptanceFilterMask(HANDLE hDevice, ULONG ulAcceptanceMask);

/*****************************************************************************
*
*    acSetAcceptanceFilter
*
*    Purpose:
*        Set acceptance code and Mask
*		
*
*    Arguments:
*        hDevice                 - handle of device
*        ulAcceptanceCode        - acceptance code
*        ulAcceptanceMask        - acceptance mask
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acSetAcceptanceFilter(HANDLE hDevice, ULONG ulAcceptanceCode, ULONG ulAcceptanceMask);

/*****************************************************************************
*
*    acCanWrite
*
*    Purpose:
*        Write can msg
*		
*
*    Arguments:
*        hDevice                      - handle of device
*        pbyData                      - data buffer
*        ulWriteCount                 - msgs number
*        pulNumberofWritten           - real msgs have written
*        ov                           - synchronization event
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acCanWrite(HANDLE hDevice, canmsg_t *pbyData, ULONG ulWriteCount, ULONG *pulNumberofWritten, OVERLAPPED *ov);

/*****************************************************************************
*
*    acCanRead
*
*    Purpose:
*        Read can message
*		
*
*    Arguments:
*        hDevice           - handle of device
*        pbyData           - data buffer
*        ulReadCount       - msg number of data buffer size
*        pulNumberofRead   - real msgs have read
*        ov                - synchronization event
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acCanRead(HANDLE hDevice, canmsg_t *pbyData, ULONG ulReadCount, ULONG *pulNumberofRead, OVERLAPPED *ov);

/*****************************************************************************
*
*    acGetStatus
*
*    Purpose:
*        Get driver current status
*		
*
*    Arguments:
*        hDevice           - handle of device
*        CanStatus         - status buffer
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acGetStatus(HANDLE hDevice, CanStatusPar_t * CanStatus);

/*****************************************************************************
*
*    acClearCommError
*
*    Purpose:
*        Execute ClearCommError of AdvCan.
*		
*
*    Arguments:
*        hDevice           - handle of device
*        ErrorCode         - error code if the CAN Controller occur error
* 
* 
*    Returns:
*        TRUE SUCCESS; or FALSE failure 
*
*****************************************************************************/
BOOL acClearCommError(HANDLE hDevice, ULONG *ulErrorCode);

/*****************************************************************************
*
*    acSetCommMask
*
*    Purpose:
*        Execute SetCommMask.
*		
*
*    Arguments:
*        hDevice           - handle of device
*        EvtMask           - event type
* 
* 
*    Returns:
*        TRUE SUCCESS; or FALSE failure 
*
*****************************************************************************/
BOOL acSetCommMask(HANDLE hDevice, ULONG ulEvtMask);

/*****************************************************************************
*
*    acGetCommMask
*
*    Purpose:
*        Execute GetCommMask.
*		
*
*    Arguments:
*        hDevice         - handle of device
*        EvtMask         - event type
* 
* 
*    Returns:
*        TRUE SUCCESS; or FALSE failure 
*
*****************************************************************************/
BOOL acGetCommMask(HANDLE hDevice, ULONG *ulEvtMask);

/*****************************************************************************
*
*    acWaitEvent
*
*    Purpose:
*        Wait can message or error of the CAN Controller.
*		
*
*    Arguments:
*        hDevice              - handle of device
*        pbyData              - buffer for read
*        nReadCount           - msgs number
*        pulNumberofRead      - real msgs have read
*        ErrorCode            - return error code when the CAN Controller has error
*        ov                   - synchronization event
* 
*    Returns:
*        =0 SUCCESS; or <0 failure 
*
*****************************************************************************/
int acWaitEvent(HANDLE hDevice, canmsg_t *pbyData, ULONG ulReadCount, ULONG *pulNumberofRead, ULONG *ErrorCode, OVERLAPPED *ov);


