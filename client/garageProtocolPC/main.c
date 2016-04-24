#include "garage_communication.h"
#include <stdio.h>
int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        puts("Incompatible number of parameters");
        return EXIT_FAILURE;
    }
    unsigned int output;
    char * input = argv[1];
    garage_t * garage = garage_new(3);
    if(strcmp(input, "person_motion") == 0)
    {
        output = garage_get_person_motion_status(garage);
        printf("OUTPUT: %i", output);
    }
    else if(strcmp(input, "car_motion") == 0)
    {
        output = garage_get_car_motion_status(garage);
        printf("OUTPUT: %i", output);
    }
    else if(strcmp(input, "car_presence") == 0)
    {
        output = garage_get_car_presence_status(garage);
        printf("OUTPUT: %i", output);
    }
    else if(strcmp(input, "door_status") == 0)
    {
        output = garage_get_door_status(garage);
        printf("OUTPUT: %i", output);
    }
    else if(strcmp(input, "door_open") == 0)
    {
        output = garage_set_door_open(garage);
        printf("OUTPUT: %i", output);
    }
    else if(strcmp(input, "door_close") == 0)
    {
        output = garage_set_door_close(garage);
        printf("OUTPUT: %i", output);
    }
    else
    {
        puts("Incompatible command, try\n"
             "person_motion\n"
             "car_motion\n"
             "car_presence\n"
             "door_status\n"
             "door_open\n"
             "door_close\n");
        return EXIT_FAILURE;
    }
    garage_delete(garage);
    return EXIT_SUCCESS;
}
