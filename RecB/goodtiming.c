#include <stdio.h>
#include <time.h>

void function_to_time(void);

int main(void) {
   time_t tend, tstart;
   char buffer[26];
   struct tm* tm_info;

   tstart = time(NULL);
   function_to_time();
   tend = time(NULL);
   tm_info = localtime(&tend);
   strftime(buffer, 26, "%c \n", tm_info);
   printf("The time before was %sThe time after  was %s\n", ctime(&tstart), buffer);
   return 0;
}
