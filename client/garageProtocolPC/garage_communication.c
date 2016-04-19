#include "serial_server.h"
#include "garage_communication.h"
#include "garage_protocol.h"
#define arr_size(a) sizeof(a)/sizeof(a[0])
#define READ_BUFFER_SIZE 10
typedef struct garage_s
{
    serial_server_t * server;
} garage_s;
garage_t * garage_new(int com_port)
{
    serial_server_t * server = serial_server_new(com_port);
    garage_t * garage = malloc(sizeof(garage_s));
    garage->server = server;
    return garage;
}
static char send_receive_cycle(garage_t * garage, char message)
{
    char send_message[] = {message};
    serial_server_send_bytes(garage->server, send_message, arr_size(send_message));
    char buffer[READ_BUFFER_SIZE];
    serial_server_read_bytes(garage->server, buffer, arr_size(buffer));
    return buffer[0];
}
unsigned int garage_get_person_motion_status(garage_t * garage)
{
    return send_receive_cycle(garage, GET_PERSON_MOTION_STATUS);
}
unsigned int garage_get_car_motion_status(garage_t * garage)
{
    return send_receive_cycle(garage, GET_CAR_MOTION_STATUS);
}
unsigned int garage_get_car_presence_status(garage_t * garage)
{
    return send_receive_cycle(garage, GET_CAR_PRESENCE_STATUS);
}
unsigned int garage_get_door_status(garage_t * garage)
{
    return send_receive_cycle(garage, GET_DOOR_STATUS);
}
unsigned int garage_set_door_open(garage_t * garage)
{
    return send_receive_cycle(garage, SET_DOOR_OPEN);
}
unsigned int garage_set_door_close(garage_t * garage)
{
    return send_receive_cycle(garage, SET_DOOR_CLOSE);
}
void garage_delete(garage_t * garage)
{
    serial_server_delete(garage->server);
    free(garage);
}
