#pragma once
#include "serial_server.h"
// requires serial_server module
typedef struct garage_s garage_t;

garage_t * garage_new(int com_port);
unsigned int garage_get_person_motion_status(garage_t * garage);
unsigned int garage_get_car_motion_status(garage_t * garage);
unsigned int garage_get_car_presence_status(garage_t * garage);
unsigned int garage_get_door_status(garage_t * garage);
unsigned int garage_set_door_open(garage_t * garage);
unsigned int garage_set_door_close(garage_t * garage);
void garage_delete(garage_t * garage);
