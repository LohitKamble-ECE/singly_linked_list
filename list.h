#ifndef LIST_H
#define LIST_H
#include <stddef.h>  // size_t
typedef struct node {
  void *data;
  struct node *suc;
} node;
typedef struct list {
  node *beg;
  node *end;
  size_t size;
  void (*print)(const void *);
  int (*compare)(const void *, const void *);
} list;

extern list *construct(list *this_list, void (*print)(const void *),
                       int (*compare)(const void *, const void *));
extern list *destruct(list *this_list);
extern void print(list *this_list);
extern int insert_before(list *this_list, node *this_node, const void *data,
                         const size_t size);
extern int insert_after(list *this_list, node *this_node, const void *data,
                        const size_t size);
extern void reverse(list *this_list);
extern int remove_current(list *this_list, node *this_node);
extern int remove_all(list *this_list);
extern node *get_begin(list *this_list);
extern node *get_end(list *this_list);
extern size_t get_size(list *this_list);
extern int rotate_left(list *this_list, size_t n);
extern int rotate_right(list *this_list, size_t n);
extern node *node_at(list *this_list, size_t i);
extern node *find_key(list *this_node, void *data);
extern int insert_ascending(list *this_list, void *data, size_t size);
extern int insert_descending(list *this_list, void *data, size_t size);

#define is_empty(list) list->size == 0 ? true : false
#endif
