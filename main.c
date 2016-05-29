#include <time.h>

char*  time_to_string(time_t time, char * buffer);
int main ()
{
time_t rawtime;
char * buffer;
 buffer = time_to_string(rawtime,buffer);
printf("%s", buffer);
  return 0;
}

char*  time_to_string(time_t t, char * buffer){

  time_t rawtime = t;
  time ( &rawtime );
  buffer = ctime (&rawtime);
  return buffer;
}
