/* duplicates.c */

#include "hash.h"
#include "macros.h"
#include "table.h"

#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Structures */

typedef struct {
    bool count;
    bool quiet;
} Options;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s paths...\n", PROGRAM_NAME);
    fprintf(stderr, "    -c     Only display total number of duplicates\n");
    fprintf(stderr, "    -q     Do not write anything (exit with 0 if duplicate found)\n");
    exit(status);
}

/**
 * Check if path is a directory.
 * @param       path        Path to check.
 * @return      true if Path is a directory, otherwise false.
 */
bool is_directory(const char *path) {
  struct stat pa;
  stat(path, &pa);

  if(S_ISDIR(pa.st_mode)==1)
    return true;
  else return false;

}

/**
 * Check if file is in table of checksums.
 *
 *  If quiet is true, then exit if file is in checksums table.
 *
 *  If count is false, then print duplicate association if file is in
 *  checksums table.
 *
 * @param       path        Path to file to check.
 * @param       checksums   Table of checksums.
 * @param       options     Options.
 * @return      0 if Path is not in checksums, otherwise 1.
 */
size_t check_file(const char *path, Table *checksums, Options *options) {
  char d[HEX_DIGEST_LENGTH];
  Value val;

  if(hash_from_file(path, d)){
    if(table_search(checksums, d) && options->quiet)
      exit(0);

    else if(table_search(checksums, d) && !(options->count))
      printf("%s is a duplicate of %s\n", path, table_search(checksums, d)->string);

    else if(table_search(checksums, d))
      return 1;

    val.string= (char *) path;
    table_insert(checksums, d, val, STRING);
    return 0;
  }

  return 0;
}

/**
 * Check all entries in directory (recursively).
 * @param       root        Path to directory to check.
 * @param       checksums   Table of checksums.
 * @param       options     Options.
 * @return      Number of duplicate entries in directory.
 */
size_t check_directory(const char *root, Table *checksums, Options *options) {
  DIR *d= opendir(root);
  char buf[BUFSIZ];
  size_t s=0;

  if(!d)
    return EXIT_FAILURE;

  for(struct dirent *dir= readdir(d); dir; dir= readdir(d)){
    if (streq(dir->d_name, ".") || streq(dir->d_name, ".."))
      continue;

    sprintf(buf, "%s/%s", root, dir->d_name);

    if(is_directory(buf))
      s += check_directory(buf, checksums, options);
    else
      s += check_file(buf, checksums, options);
  }

  closedir(d);
  return s;

}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */
    Options o= {false, false};
    //o.quiet=false;
    //o.count=false;

    Table *checksums= table_create(0);
    size_t s=0;
    int scount=0;
    char directory[argc-1][BUFSIZ];


    PROGRAM_NAME= argv[0];
    if(argc < 2 || strcmp(argv[1], "-h")==0)
      usage(0);

    /* Check each argument */
    else{
      for (int i=1; i<argc;i++){
        //char *arg= argv[i];
        if (strcmp(argv[i],"-q")==0)
          o.quiet=true;
        else if (strcmp(argv[i],"-c")==0)
          o.count=true;

        else{
          strcpy(directory[scount], argv[i]);
          scount++;
        }

      } //for bracket
    }

    for (int j=0; j<scount; j++){
      if(is_directory(directory[j]))
        s += check_directory(directory[j], checksums, &o);
      else
        s += check_file(directory[j], checksums, &o);
    }

    /* Display count if necessary */
    if(o.count)
      printf("%lu\n", s);

    table_delete(checksums);

    if(o.quiet)
      return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
