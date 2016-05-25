#include "car_check.h"
#include "libthread\thread.h"
#include "serial_server.h"
typedef struct car_check_args{
    int com_port;
    int * status;
} car_check_args;
static void * car_check(void * args);

void start_car_check(int com_port, int * status)
{
    car_check_args * data = (car_check_args *)malloc(sizeof(car_check_args));
	data->com_port = com_port;
	data->status = status;
    thread_create_args(car_check, data);
}
static void * car_check(void * args)
{
    car_check_args * data = (car_check_args *)args;
    while(1)
    {
        serial_server_t * car = serial_server_new(data->com_port);
        if(car != NULL)
		{
            *(data->status) = 0;
            serial_server_delete(car);
            Sleep(10000);
        }
        else
            *(data->status) = 1;
        Sleep(500);
    }
	return NULL;
}
