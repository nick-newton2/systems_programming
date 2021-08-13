/* hammer.c: Hammer Functions */

#include "hammer.h"
#include "http.h"
#include "timestamp.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Make n HTTP requests to the specified url, while writing the contents of the
 * request to the specified stream.
 *
 * Each HTTP request must be performed by a separate child process.
 *
 * @param   url         Make HTTP requests to this URL.
 * @param   stream      Write the contents of each response to this stream.
 * @param   n           The number of HTTP requests to make.
 * @return  True if all children were successful.
 **/
bool	hammer(const URL *url, FILE *stream, size_t n) {
    /* TODO: Spawn children.
     * Each child must do the following:
     *  1. Make a HTTP request to given URL.
     *  2. Time the HTTP request.
     *  3. Print the bandwidth if any data was written to stderr.
     *  4. Exit with success if the HTTP request was successful.
     **/

     double start= timestamp();
     for (int i=0; i<n; i++){
       pid_t pid =fork();
       if(pid<0){
         return false;
       }
       if(pid==0){
         double before=timestamp();
         ssize_t bytes_written= http_get(url, stream);
         double after=timestamp();
         double bandwidth= bytes_written / 1048576.0 / (after-before);

         if(bytes_written>=0){
           fprintf(stderr, "Bandwidth: %0.21lf MB/s\n", bandwidth);
           exit(0);
         }
         else{
           exit(1);
         }
       }
     }

    /* TODO: Wait for children. */
    int stat=0;
    int child_stat=0;
    for(int i=0; i<n;i++){
      while(wait(&child_stat)<0);
      stat += child_stat;
    }

    /* TODO: Print elapsed time to stderr. */
    double time_elapsed = timestamp()-start;
    fprintf(stderr, "Elapsed time: %0.2lf seconds\n", time_elapsed);
    return stat;
  }



/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
