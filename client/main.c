#include <windows.h>
#include <stdio.h>

int main()
{
    char byte_to_send; // 1 -ON, 0 - OFF
    char command[10];
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    int isWorking = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 20;
    pos.Y = 0;
    while(1)
    {
        while(1)
        {
            printf("Enter the command\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            printf(">>");
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_GREEN);
            gets(command);
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
            if(!strcmp(command, "start"))
            {
                if(!isWorking)
                {
                    isWorking = 1;
                    byte_to_send = 1;
                    break;
                }
                else
                {
                    printf("The engine is working");
                    getch();
                    system("cls");
                }
            }
            else
                if(!strcmp(command, "stop"))
                {
                    if(isWorking)
                    {
                        isWorking = 0;
                        byte_to_send = 0;
                        SetConsoleCursorPosition(hConsole, pos);
                        break;
                    }
                    else
                    {
                        printf("The engine is already stopped");
                        getch();
                        system("cls");
                    }
                }
                else
                    if(!strcmp(command, "exit"))
                    {
                        // Close serial port
                        fprintf(stderr, "Closing serial port...");
                        if (CloseHandle(hSerial) == 0)
                        {
                            fprintf(stderr, "Error\n");
                            return 1;
                        }
                        return EXIT_SUCCESS;
                    }
                    else
                    {
                        printf("Enter correct command");
                        getch();
                        system("cls");
                    }
            }
    // Open the highest available serial port number
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
    if(!WriteFile(hSerial, byte_to_send, 5, &byte_written, NULL))
    {
        fprintf(stderr, "Error\n");
        CloseHandle(hSerial);
        return 1;
    }
    fprintf(stderr, "%d byte written\n", byte_written);
    fprintf(stderr, "OK\n");
    getch();
    system("cls");
    }
    return 0;
}

