#include <time.h>
#include <string.h>
#include <stdio.h>

char*  time_to_string(time_t time, char * buffer);
int main ()
{
    time_t rawtime;
    rawtime = time ( NULL );
    char buffer[1000];
    strcpy(buffer ,time_to_string(rawtime,buffer));
    printf("%s", buffer);
    return 0;
}

char*  time_to_string(time_t t, char * buffer)
{
    struct tm *gm;
    gm = localtime(&t);
    sprintf(buffer, "%d/%d/%d   %d.%d" ,gm->tm_year+1900, gm->tm_mon+1,gm->tm_mday,gm->tm_hour,gm->tm_min);
    return buffer;
}
