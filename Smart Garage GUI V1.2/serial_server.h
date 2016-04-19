#pragma once
#include <windows.h>
#define BAUD_RATE CBR_9600
typedef struct serial_server_s serial_server_t;

typedef enum SERIAL_SERVER_STATUS {SERIAL_SERVER_OK, SERIAL_SERVER_SEND_ERROR, SERIAL_SERVER_READ_ERROR} SERIAL_SERVER_STATUS;
SERIAL_SERVER_STATUS getLastError();

serial_server_t * serial_server_new(int com_port);
int serial_server_send_bytes(serial_server_t * server, char message[], size_t size);
int serial_server_read_bytes(serial_server_t * server, char buffer[], size_t size);
void serial_server_delete(serial_server_t * server);
