/* library.c: string utilities library */

#include "str.h"

#include <ctype.h>
#include <string.h>

/**
 * Convert all characters in string to lowercase.
 * @param   s       String to convert
 **/
void	str_lower(char *s) {
  for (char*c =s; *c;c++){
    *c=tolower(*c);
  }
}

/**
 * Convert all characters in string to uppercase.
 * @param   s       String to convert
 **/
void	str_upper(char *s) {
  for (char*c =s; *c;c++){
    *c= toupper(*c);
  }
}

/**
 * Convert all characters in string to titlecase.
 * @param   s       String to convert
 **/
void	str_title(char *s) {
  for (char*c =s; *c;c++){
    if( isalpha(*c) && !isalpha(*(c-1)) ){
      *c= toupper(*c);
    }
    else{
      *c= tolower(*c);
    }
  }

}

/**
 * Removes trailing newline (if present).
 * @param   s       String to modify
 **/
void    str_chomp(char *s) {
  char *tail = s + strlen(s) -1;
  if (isspace(*tail)){
    *(s+strlen(s)-1) = '\0';
  }
}

/**
 * Removes whitespace from front and back of string (if present).
 * @param   s       String to modify
 **/
void    str_strip(char *s) {
  if(strlen(s)!=0){
    char *head = s;
    char *tail = s+strlen(s)-1;

    while(isspace(*head)){
      head++;
    }
    while(isspace(*tail)){
      tail--;
    }
    while(head<=tail){
      *s= *head;
      s++;
      head++;
    }
    *s='\0';
  }
}

/**
 * Reverses a string.
 * @param   s       String to reverse
 **/
void    str_reverse(char *s) {

    char *head = s;
    char *tail = s+strlen(s)-1;
    char temp;

    while (head<tail && *head && *tail){
      temp= *head;
      *head= *tail;
      *tail= temp;
      head++;
      tail--;
    }
}

/**
 * Replaces all instances of 'from' in 's' with corresponding values in 'to'.
 * @param   s       String to translate
 * @param   from    String with letter to replace
 * @param   to      String with corresponding replacment values
 **/
void    str_translate(char *s, char *from, char *to) {
  char *key= from; char *value= to;
  char table[128]={'\0'};
  while(*value && *key){
    table[*key-'\0']= *value;
    value++; key++;
  }

  for (char *c =s; *c;c++){
    if(table[*c-'\0'] != '\0'){
      *c= table[*c-'\0'];
    }

  }

}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
