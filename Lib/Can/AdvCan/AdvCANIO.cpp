#include "AdvCANIO.h"

HANDLE acCanOpen(TCHAR *PortName, BOOL synchronization)
{
    HANDLE hDevice;
    TCHAR CanName[20] = TEXT("\\\\.\\");
    _tcscat(CanName, PortName);
    hDevice = NULL;
    if(synchronization)
    {
        hDevice = CreateFile(CanName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    }
    else{
        hDevice = CreateFile(CanName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
            NULL);
    }

    return hDevice;
}

int acCanClose(HANDLE hDevice)
{
    if (hDevice != INVALID_HANDLE_VALUE)
    {
        if(!CloseHandle(hDevice))
            return OPERATION_ERROR;

    }
    return SUCCESS;
}

int acEnterResetMode(HANDLE hDevice)
{
    Command_par_t cmd;
    BOOL flag;
    ULONG ulOutLen;

    cmd.cmd = CMD_STOP;	
    flag = DeviceIoControl (hDevice,
        (ULONG)CAN_IOCTL_COMMAND,
        &cmd,
        sizeof(Command_par_t),
        NULL,
        0,
        &ulOutLen,
        0
        );
    if(!flag)
    {
        return OPERATION_ERROR;
    }

    return SUCCESS;
}

int acEnterWorkMode(HANDLE hDevice)
{
    Command_par_t cmd;
    BOOL flag;
    ULONG ulOutLen;

    cmd.cmd = CMD_START;	
    flag = DeviceIoControl (hDevice,
        (ULONG)CAN_IOCTL_COMMAND,
        &cmd,
        sizeof(Command_par_t),
        NULL,
        0,
        &ulOutLen,
        0
        );
    if(!flag)
    {
        return OPERATION_ERROR;
    }

    return SUCCESS;
}

int acClearRxFifo(HANDLE hDevice)
{
    Command_par_t cmd;
    BOOL flag;
    ULONG ulOutLen;

    cmd.cmd = CMD_CLEARBUFFERS;	
    flag = DeviceIoControl (hDevice,
        (ULONG)CAN_IOCTL_COMMAND,
        &cmd,
        sizeof(Command_par_t),
        NULL,
        0,
        &ulOutLen,
        0
        );
    if(!flag)
    {
        return OPERATION_ERROR;
    }

    return SUCCESS;
}

int acSetBaud(HANDLE hDevice, unsigned int nBaud)
{
    Config_par_t config;
    BOOL flag;
    ULONG  ulOutLen;

    config.target = CONF_TIMING;
    config.val1 = nBaud;
    flag = DeviceIoControl (hDevice,
        (ULONG)CAN_IOCTL_CONFIG,
        &config,
        sizeof(Config_par_t),
        NULL,
        0,
        &ulOutLen,
        0
        );
    if(!flag)
    {
        return OPERATION_ERROR;
    }

    return SUCCESS;
}

int acSetBaudRegister(HANDLE hDevice, unsigned char Btr0, unsigned char Btr1)
{
    unsigned int BaudRateValue = Btr0 * 256;
    BaudRateValue += Btr1;
    return acSetBaud(hDevice, BaudRateValue);
}

int acSetTimeOut(HANDLE hDevice, ULONG ulReadTimeOut, ULONG ulWriteTimeOut)
{
    Config_par_t config;
    BOOL flag;

    ULONG ulOutLen;
    config.target = CONF_TIMEOUT;
    config.val2 = ulReadTimeOut;
    config.val1 = ulWriteTimeOut;
    flag = DeviceIoControl (hDevice,
        (ULONG)CAN_IOCTL_CONFIG,
        &config,
        sizeof(Config_par_t),
        NULL,
        0,
        &ulOutLen,
        0
        );
    if(!flag)
    {
        return OPERATION_ERROR;
    }

    return SUCCESS;
}

int acSetSelfReception(HANDLE hDevice, BOOL bSelfFlag)
{
    Config_par_t config;
    BOOL flag;
    ULONG ulOutLen;

    config.target = CONF_SELF_RECEPTION;
    if(bSelfFlag)
        config.val1 = 1;
    else
        config.val1 = 0;
    flag = DeviceIoControl (hDevice,
        (ULONG)CAN_IOCTL_CONFIG,
        &config,
        sizeof(Config_par_t),
        NULL,
        0,
        &ulOutLen,
        0
        );
    if(!flag)
    {
        return OPERATION_ERROR;
    }

    return SUCCESS;
}

int acSetListenOnlyMode(
                        HANDLE hDevice,
                        BOOL   bListerOnlyFlag
                        )
{
    Config_par_t config;
    BOOL flag;
    ULONG  ulOutLen;

    config.target = CONF_LISTEN_ONLY_MODE;
    if(bListerOnlyFlag)
        config.val1 = 1;
    else
        config.val1 = 0;
    flag = DeviceIoControl (hDevice,
        (ULONG)CAN_IOCTL_CONFIG,
        &config,
        sizeof(Config_par_t),
        NULL,
        0,
        &ulOutLen,
        0
        );
    if(!flag)
    {
        return OPERATION_ERROR;
    }

    return SUCCESS;   
}

int acSetAcceptanceFilterMode(
                              HANDLE hDevice,
                              int   nFilterMode
                              )
{
    Config_par_t config;
    BOOL flag;

    ULONG  ulOutLen;

    config.target = CONF_ACC_FILTER;
    config.val1 = nFilterMode;

    flag = DeviceIoControl (hDevice,
        (ULONG)CAN_IOCTL_CONFIG,
        &config,
        sizeof(Config_par_t),
        NULL,
        0,
        &ulOutLen,
        0
        );
    if(!flag)
    {
        return OPERATION_ERROR;
    }

    return SUCCESS;   
}



int acSetAcceptanceFilterCode(HANDLE hDevice, ULONG ulAcceptanceCode)
{
    Config_par_t config;
    BOOL flag;

    ULONG ulOutLen;

    config.target = CONF_ACCC;
    config.val1   = ulAcceptanceCode;
    flag = DeviceIoControl (hDevice,
        (ULONG)CAN_IOCTL_CONFIG,
        &config,
        sizeof(Config_par_t),
        NULL,
        0,
        &ulOutLen,
        0
        );
    if(!flag)
    {
        return OPERATION_ERROR;
    }

    return SUCCESS;
}

int acSetAcceptanceFilterMask(HANDLE hDevice, ULONG ulAcceptanceMask)
{
    Config_par_t config;
    BOOL flag;
    ULONG ulOutLen;



    config.target = CONF_ACCM;
    config.val1   = ulAcceptanceMask;
    flag = DeviceIoControl (hDevice,
        (ULONG)CAN_IOCTL_CONFIG,
        &config,
        sizeof(Config_par_t),
        NULL,
        0,
        &ulOutLen,
        0
        );
    if(!flag)
    {
        return OPERATION_ERROR;
    }

    return SUCCESS;
}

int acSetAcceptanceFilter(HANDLE hDevice, ULONG ulAcceptanceCode, ULONG ulAcceptanceMask)
{
    Config_par_t config;
    BOOL flag;
    ULONG ulOutLen;

    config.target = CONF_ACC;
    config.val1   = ulAcceptanceMask;
    config.val2   = ulAcceptanceCode;
    flag = DeviceIoControl (hDevice,
        (ULONG)CAN_IOCTL_CONFIG,
        &config,
        sizeof(Config_par_t),
        NULL,
        0,
        &ulOutLen,
        0
        );
    if(!flag)
    {
        return OPERATION_ERROR;
    }

    return SUCCESS;
}


int acCanWrite(HANDLE hDevice, canmsg_t *pbyData, ULONG ulWriteCount, ULONG *pulNumberofWritten, OVERLAPPED *ov)
{
    ULONG ulErr = 0;

    *pulNumberofWritten = 0;
    BOOL flag = WriteFile(hDevice, pbyData, ulWriteCount, pulNumberofWritten, ov);
    if (flag)
    {
        if(ulWriteCount > *pulNumberofWritten)
            return TIME_OUT;
        return SUCCESS;
    }
    else
    {
        ulErr = GetLastError();
        if ( ulErr == ERROR_IO_PENDING )
        {
            if( GetOverlappedResult( hDevice, ov, pulNumberofWritten, TRUE ) )         //retrieves the results of overlapped operation
            { 
                if( ulWriteCount > *pulNumberofWritten)
                    return TIME_OUT;
                else
                    return SUCCESS;
            }
            else
                return OPERATION_ERROR;
        }
        else
            return OPERATION_ERROR;
    }
}

int acCanRead(HANDLE hDevice, canmsg_t *pbyData, ULONG ulReadCount, ULONG *pulNumberofRead, OVERLAPPED *ov)
{
    ULONG ulErr = 0;

    *pulNumberofRead = 0;
    BOOL flag = ReadFile(hDevice, pbyData, ulReadCount, pulNumberofRead, ov);
    if (flag)
    {
        if(*pulNumberofRead == 0)
            return TIME_OUT;
        return SUCCESS;	
    }
    else{
        ulErr = GetLastError();
        if ( ulErr == ERROR_IO_PENDING )
        {
            if ( GetOverlappedResult( hDevice, ov, pulNumberofRead, TRUE ) )    //retrieves the results of overlapped operation
            {
                if(*pulNumberofRead == 0)
                {
                    return TIME_OUT;
                }
                else
                {
                    return SUCCESS;
                }
            }
            else
                return OPERATION_ERROR;
        }
        else return OPERATION_ERROR;
    }
}

int acGetStatus(HANDLE hDevice, CanStatusPar_t * CanStatus)
{
    ULONG			dwOutLen;


    int flag = DeviceIoControl (hDevice,
        (ULONG)CAN_IOCTL_STATUS,
        NULL,
        0,
        CanStatus,
        sizeof(CanStatusPar_t),
        &dwOutLen,
        0
        );
    if(!flag)
    {
        return OPERATION_ERROR;
    }
    return SUCCESS;
}

BOOL acClearCommError(HANDLE hDevice, ULONG *ulErrorCode)
{
    COMSTAT State;
    return ClearCommError(hDevice, ulErrorCode, &State);
}

BOOL acSetCommMask(HANDLE hDevice, ULONG ulEvtMask)
{
    return SetCommMask(hDevice, ulEvtMask);
}

BOOL acGetCommMask(HANDLE hDevice, ULONG *ulEvtMask)
{
    return GetCommMask(hDevice, ulEvtMask);
}

int acWaitEvent(HANDLE hDevice, canmsg_t *pbyData, ULONG ulReadCount, ULONG *pulNumberofRead, ULONG *ErrorCode, OVERLAPPED *ov)
{
    ULONG Code = 0;
    int nRet = OPERATION_ERROR;

    if (WaitCommEvent(hDevice, &Code, ov) == TRUE)
    {
        if ((Code & EV_RXCHAR) != 0)
        {
            nRet = acCanRead(hDevice, pbyData, ulReadCount, pulNumberofRead, ov);
        }
        if ((Code & EV_ERR) != 0)
        {
            nRet = OPERATION_ERROR;
            acClearCommError(hDevice, ErrorCode);
        }
    }
    else
    {
        ULONG ulErr = GetLastError();
        if (ERROR_IO_PENDING == ulErr)
        {
            if (GetOverlappedResult(hDevice, ov, pulNumberofRead, TRUE))
            {
                if ((Code & EV_RXCHAR) != 0)
                {
                    nRet = acCanRead(hDevice, pbyData, ulReadCount, pulNumberofRead, ov);
                }
                if ((Code & EV_ERR) != 0)
                {
                    nRet = OPERATION_ERROR;
                    acClearCommError(hDevice, ErrorCode);
                }
            }
        }
    }

    return nRet;
}

