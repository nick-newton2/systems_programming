/* main.c: string library utility */

#include "str.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char *PROGRAM_NAME = NULL;

/* Flags */

enum {
    /* TODO*: Enumerate Flags */
    STRIP= 1<<0,
    REVERSE= 1<<1,
    LOWER= 1<<2,
    UPPER= 1<<3,
    TITLE= 1<<4
};

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s SOURCE TARGET\n\n", PROGRAM_NAME);
    fprintf(stderr, "Post Translation filters:\n\n");
    fprintf(stderr, "   -s      Strip whitespace\n");
    fprintf(stderr, "   -r      Reverse line\n");
    fprintf(stderr, "   -l      Convert to lowercase\n");
    fprintf(stderr, "   -u      Convert to uppercase\n");
    fprintf(stderr, "   -t      Convert to titlecase\n");
    exit(status);
}

void translate_stream(FILE *stream, char *source, char *target, int flag) {
    /* TODO: Process each line in stream by performing transformations */
    char buf [BUFSIZ];
    while (fgets(buf, BUFSIZ, stream) != NULL){
      str_chomp(buf);

      str_translate(buf, source, target);

      if (flag & STRIP){
        str_strip(buf);
      }
      if(flag & REVERSE ){
        str_reverse(buf);
      }
      if(flag & LOWER){
        str_lower(buf);
      }
      if(flag & UPPER) {
        str_upper(buf);
      }
      if (flag & TITLE){
        str_title(buf);
      }
      printf("%s\n", buf);
    }


}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* TODO: Parse command line arguments */
    int flag =0;
    char *source= "";
    char *target="";
    PROGRAM_NAME= argv[0];

    if(argc<2){
      translate_stream(stdin, source, target, flag);
    }

    else if (strcmp(argv[1], "-h")==0){
        usage(0);
    }

    else{
      for (int i=1; i<argc; i++){

        if (strcmp(argv[i], "-s")==0){
          flag |= STRIP;
        }
        else if (strcmp(argv[i], "-r")==0){
          flag |= REVERSE;
        }
        else if (strcmp(argv[i], "-l")==0){
          flag |= LOWER;
        }
        else if (strcmp(argv[i], "-u")==0){
          flag |= UPPER;
        }
        else if (strcmp(argv[i], "-t")==0){
          flag |= TITLE;
        }
        else{
          source= argv[i];
          target= argv[i+1];
          i++;
        }
      }
    }

    /* TODO: Translate Stream */
    translate_stream(stdin, source, target, flag);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
