#include <windows.h>
#include <stdio.h>

void callArd(char byte_to_send)
{
     HANDLE hSerial;
     DCB dcbSerialParams = {0};
     COMMTIMEOUTS timeouts = {0};
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     fprintf(stderr, "Opening serial port...");
     hSerial = CreateFile(
                "\\\\.\\COM4", GENERIC_READ|GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    if (hSerial == INVALID_HANDLE_VALUE)
    {
            fprintf(stderr, "Error\n");
            return 1;
    }
    else fprintf(stderr, "OK\n");

    // Set device parameters (38400 baud, 1 start bit,
    // 1 stop bit, no parity)
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (GetCommState(hSerial, &dcbSerialParams) == 0)
    {
        fprintf(stderr, "Error getting device state\n");
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if(SetCommState(hSerial, &dcbSerialParams) == 0)
    {
        fprintf(stderr, "Error setting device parameters\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Set COM port timeout settings
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if(SetCommTimeouts(hSerial, &timeouts) == 0)
    {
        fprintf(stderr, "Error setting timeouts\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Send specified text (remaining command line arguments)
    DWORD byte_written;
    fprintf(stderr, "Sending byte...");
    if(!WriteFile(hSerial, byte_to_send, 1, &byte_written, NULL))
    {
        fprintf(stderr, "Error\n");
        CloseHandle(hSerial);
        return 1;
    }
    fprintf(stderr, "%d byte written\n", byte_written);
    fprintf(stderr, "OK\n");
}


