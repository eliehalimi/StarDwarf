# include "hash_table.h"
# include <string.h>
# include <stdio.h>
# include <assert.h>
uint32_t hash(char *data)
{
  uint32_t h = 0;
  for (size_t i = 0; data[i] != '\0'; ++i)
    {
      h += (uint32_t)data[i];
      h += h* 1024;
      h = (h ^ (h/64));
    }
  h += h*8;
  h = h ^ (h/2048);
  h += h*32768;
  
  return h;
}

struct htable *create_htable(size_t capacity)
{
  if (capacity < 1)
    return NULL;
  struct htable *htable = malloc(sizeof (struct htable));
  htable -> tab = malloc(capacity * sizeof(struct pair));
  htable -> size = 0;
  htable -> capacity = capacity;
  for (size_t i = 0; i < capacity; ++i)
    {
      htable->tab[i]= malloc(sizeof(struct pair));
      htable->tab[i]->key = NULL;
      htable->tab[i]->value = NULL;
      htable->tab[i]->next = NULL;
    }
  return htable;
}

struct pair *access_htable(struct htable *htable, char *key)
{
  struct pair *cur = htable -> tab [hash(key) %( htable -> capacity)];
  
  for (;cur != NULL; cur = cur -> next)
    {
      if (cur->key == NULL || (cur->key != NULL && strcmp(cur->key, key) ==0))
	return cur;
    }
  assert(0);
  return NULL;
}
int add_htable(struct htable *htable, char *key, void *value)
{

  if ((htable -> size)*100 / (htable -> capacity) > 75)
    {
      struct pair **tab_old = htable -> tab;
      
      htable -> capacity *= 2;
      htable -> size = 0;
      htable -> tab = malloc(htable -> capacity*sizeof(struct pair));
      
      for (size_t i = 0; i < htable->capacity; ++i)
	{
	  htable->tab[i]= malloc(sizeof(struct pair));
	  htable->tab[i]->key = NULL;
	  htable->tab[i]->value = NULL;
	  htable->tab[i]->next = NULL;
	}
      for (size_t i = 0; i < htable->capacity / 2 ; ++i)
	{
	  struct pair *cur = tab_old[i];
	  struct pair *next = NULL;
	  for (; cur != NULL;)
	    {
	      next = cur->next;
	      if (cur -> key)
		add_htable(htable, cur->key, cur->value);
	      free(cur);
	      cur = next;
	    }
	  free(cur);
	}
      free(tab_old);
    }
  
  struct pair *cur = htable->tab[hash(key) % (htable->capacity)];
  struct pair *new;

  if (cur->key == NULL)
    new = cur;
  else
    {
      for (;cur->next != NULL; cur = cur->next);
      cur->next = malloc(sizeof(struct pair));
      new = cur->next;
    }
  new -> hkey = hash(key);
  new -> key = key;
  new -> value = value;
  new -> next = NULL;
  htable -> size += 1;
  return 1;
}

void clear_htable(struct htable *htable)
{
  for (size_t i = 0; i < htable -> capacity; ++i)
    {
      struct pair *cur = htable -> tab[i];
      struct pair *next = NULL;
      for (;cur != NULL;)
	{
	  next = cur->next;
	  free(cur->value);
	  free(cur);
	  cur = next;
	}
    }
   htable -> size = 0;  
}

void free_htable(struct htable *htable)
{
  clear_htable(htable);
  free(htable->tab);
  free(htable);
}
