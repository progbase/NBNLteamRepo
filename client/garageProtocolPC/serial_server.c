#include <windows.h>
#include <stdio.h>
#include "serial_server.h"

typedef struct serial_server_s{
    HANDLE hSerial;
} serial_server_s;

static SERIAL_SERVER_STATUS status = SERIAL_SERVER_OK;
serial_server_t * serial_server_new(int com_port)
{
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    char com_path[100];
    sprintf(com_path, "\\\\.\\COM%i", com_port);
    //fprintf(stderr, "Opening serial port...");
    hSerial = CreateFile(
                com_path, GENERIC_READ|GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    if (hSerial == INVALID_HANDLE_VALUE)
    {
            //fprintf(stderr, "Error\n");
            return NULL;
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (GetCommState(hSerial, &dcbSerialParams) == 0)
    {
        //fprintf(stderr, "Error getting device state\n");
        CloseHandle(hSerial);
        return NULL;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if(SetCommState(hSerial, &dcbSerialParams) == 0)
    {
        //fprintf(stderr, "Error setting device parameters\n");
        CloseHandle(hSerial);
        return NULL;
    }

    // Set COM port timeout settings
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if(SetCommTimeouts(hSerial, &timeouts) == 0)
    {
        //fprintf(stderr, "Error setting timeouts\n");
        CloseHandle(hSerial);
        return NULL;
    }
    serial_server_t * server = malloc(sizeof(serial_server_s));
    server->hSerial = hSerial;
    return server;
}
int serial_server_send_bytes(serial_server_t * server, char message[], size_t size)
{
    DWORD byte_written;
    //fprintf(stderr, "Sending byte...");
    if(!WriteFile(server->hSerial, message, size, &byte_written, NULL))
    {
        //fprintf(stderr, "Error\n");
        status = SERIAL_SERVER_SEND_ERROR;
        return 1;
    }
    return 0;
}
int serial_server_read_bytes(serial_server_t * server, char buffer[], size_t size)
{
   return ReadFile(
        server->hSerial,
        buffer,
        size,
        NULL,NULL);
}
void serial_server_delete(serial_server_t * server)
{
    CloseHandle(server->hSerial);
    free(server);
}

SERIAL_SERVER_STATUS getLastError()
{
    return status;
}
