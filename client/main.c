#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "protocol.h"

static printCommands();

int main()
{
    char command[10];
    HANDLE hSerial;
    int status = 0;
	size_t port = 3;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
    while(1)
    {
        while(1)
        {
            printf("'Smart Garage' console application 1.0");
            printCommands();
            printf("Enter the command\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            printf(">>");
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_GREEN);
            gets(command);
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
            if(!strcmp(command, "open"))
            {
                if(!status)
                {
                    status = 1;
                    serial_send_byte(OPEN, 3);
                    break;
                }
                else
                {
                    printf("The door is opened");
                    getch();
                    system("cls");
                }
            }
            else
                if(!strcmp(command, "close"))
                {
                    if(status)
                    {
                        status = 0;
                        serial_send_byte(CLOSE, 3);
                        break;
                    }
                    else
                    {
                        printf("The door is already closed");
                        getch();
                        system("cls");
                    }
                }
                else
                    if(!strcmp(command, "getStatus"))
                    {
                        if(!status)
                            {
                                printf("The door is closed");
                                getch();
                                system("cls");
                            }
                        else
                            {
                                printf("The door is opened");
                                getch();
                                system("cls");
                            }
                    }
                    else
                    if(!strcmp(command, "exit"))
                    {
                        // Close serial port
                        fprintf(stderr, "Closing serial port...");
						system("cls");
                        if (CloseHandle(hSerial) == 0)
                        {
                            fprintf(stderr, "Error\n");
                            return EXIT_FAILURE;
                        }
                        return EXIT_SUCCESS;
                    }
                    else
                    {
                        printf("Invalid Command");
                        getch();
                        system("cls");
                    }
            }
    getch();
    system("cls");
    }
    return 0;
}

static printCommands()
{
    COORD pos;
    pos.X = 30;
    pos.Y = 2;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, pos);
    printf("List of commands : \n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    pos.X = 30;
    pos.Y = 3;
    SetConsoleCursorPosition(hConsole, pos);
    printf("open  --  ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
    printf("Opening the door");
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    pos.X = 30;
    pos.Y = 4;
    SetConsoleCursorPosition(hConsole, pos);
    printf("close  --  ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
    printf("Closing the door");
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    pos.X = 30;
    pos.Y = 5;
    SetConsoleCursorPosition(hConsole, pos);
    printf("getStatus  --  ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
    printf("Getting status of the door");
	pos.X = 30;
    pos.Y = 6;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    SetConsoleCursorPosition(hConsole, pos);
    printf("exit  --  ");
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
    printf("Exitting from the application");
    pos.X = 0;
    pos.Y = 2;
    SetConsoleCursorPosition(hConsole, pos);
}
