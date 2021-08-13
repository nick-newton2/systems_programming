/* http.c: HTTP Client Functions */

#include "http.h"
#include "macros.h"
#include "socket.h"
#include "url.h"

/**
 * Make a HTTP request to specified URL and write the contents of the response
 * to the specified stream.
 *
 * @param   url     Make a HTTP request to this URL.
 * @param   stream  Write the contents of response to this stream.
 * @return  -1 on error, otherwise the number of bytes written.
 **/
ssize_t http_get(const URL *url, FILE *stream) {
    /* TODO: Connect to remote host and port */
    /* TODO: Send request to server */
    /* TODO: Read response status from server */
    /* TODO: Read response headers from server */
    /* TODO: Read response body from server */
    /* TODO: Close connection */
    /* TODO: Return number of bytes written and check if it matches Content-Length */

    //Connect
    FILE *client_file=socket_dial(url->host, url->port);
    if (!client_file) {
      fprintf(stderr, "no connect bad name");
      return -1;
    }

    /* Send HTTP Request */
    fprintf(client_file, "GET /%s HTTP/1.0\r\n", url->path);
    fprintf(client_file, "Host: %s\r\n", url->host);
    fprintf(client_file, "\r\n");                   // Must end Request with empty line

    /* Read HTTP Response */
    /* TODO: Read response status from server */
    char buffer [BUFSIZ];
    if(fgets(buffer, BUFSIZ, client_file)){
      char *status;
      if((status= strstr(buffer, "200 OK"))==NULL){
        fprintf(stderr, "status not 200 OK\n");
        fclose(client_file);
        return -1;
      }
    }
    else{
      fprintf(stderr, "fail\n");
      fclose(client_file);
      return -1;
    }

    /* TODO: Read response headers from server */
    size_t content=0;
    while (fgets(buffer, BUFSIZ, client_file) && strlen(buffer)>2) {
      sscanf(buffer, "Content-Length: %lu", &content);
    }
    /* TODO: Read response body from server */
    size_t bytes_all=0;
    size_t bytes_read=0;
    while ((bytes_read = fread(buffer, sizeof(char), BUFSIZ, client_file))){
      bytes_all += fwrite(buffer, sizeof(char), bytes_read, stream);
    }

    /* Close socket */
    fclose(client_file);

    /* TODO: Return number of bytes written and check if it matches Content-Length */
    return (content>0) ? ((content==bytes_all) ? (bytes_all) : (-1)) : (bytes_all);

}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
