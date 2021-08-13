/* thor.c */

#include "hammer.h"
#include "url.h"

#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s [options] URL\n", PROGRAM_NAME);
    fprintf(stderr, "    -n N   How many times to hammer the URL\n");
    exit(status);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* TODO: Parse command line arguments */
    int num=1;
    char* url=argv[1];
    PROGRAM_NAME=argv[0];

    if (argc<2){
      usage(1);
    }
    else{
      if(strcmp(argv[1], "-h")==0){
        usage(0);
      }
      else if(strcmp(argv[1], "-n")==0){
        num= atoi(argv[2]);
        url= argv[3];
      }
      else if(strcmp(argv[1], "-?")==0){
        usage(1);
      }
    }

    /* TODO: Parse URL */
    URL* u= url_parse(url);

    /* TODO: Hammer URL */
    bool status= hammer(u, stdout, num);
    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
