/*
 * list.h : Linked lists
 */
#include <stdlib.h>
  
struct list_char {
  struct list_char *next;
  char *data;
};

struct list_char *list_create();
 
int list_is_empty(struct list_char *list);

size_t list_len(struct list_char *list);
 
void list_push(struct list_char *list, char *data);

struct list_char* list_find(struct list_char *list, char *data);

void removeall_list(struct list_char *list);

void free_list(struct list_char *list);
