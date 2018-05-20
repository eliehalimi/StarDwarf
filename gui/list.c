# include "list.h"
# include <string.h>
# include <stdio.h>
# include <assert.h>
struct list_char *list_create()
{ 
  struct list_char *list = malloc(sizeof(struct list_char));
  list -> next = NULL;
  list -> data = NULL;
  return list;
}

int list_is_empty (struct list_char *list)
{
  if (list -> next == NULL)
    return 1;
  return 0;
}

size_t list_len(struct list_char *list)
{
  int r = 0;
  if (list_is_empty(list))
    return 0;
  for (; list -> next != NULL; ++r)
    list = list -> next;
  return r;
}

void list_push(struct list_char *list, char *data)
{
  struct list_char *elm = malloc(sizeof(struct list_char));
  elm->data = malloc(20*sizeof(char));
  strcpy(elm->data, data);
  elm->next = list->next;
  list->next = elm;
}

struct list_char * list_find(struct list_char *list, char *data)
{
  
  for (struct list_char *cur = list->next; cur != NULL; cur = cur->next)
    {
      if (strcmp(cur->data, data) == 0)
	return cur;
    }
  return NULL;
}
void removeall_list(struct list_char *list)
{
  struct list_char *cur = list->next;
  list->next = NULL;
  struct list_char *next = NULL;
  for (; cur != NULL; cur = next)
    {
      next = cur->next;
      free(cur->data);
      free(cur);
    }

}
void free_list(struct list_char *list)
{
  struct list_char *cur = list->next;
  free(list);
  struct list_char *next = NULL;
  for (; cur != NULL; cur = next)
    {
      next = cur->next;
      free(cur->data);
      free(cur);
    }

}
