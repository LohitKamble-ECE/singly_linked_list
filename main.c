#include <stdio.h>

#include "list.h"

void print_int(const void *);
int compare_int(const void *a, const void *b);
int main(void) {
  list *p = NULL;
  p = construct(p, print_int, compare_int);
  int d = 1;
  insert_after(p, NULL, &d, sizeof(int));
  print(p);
  d++;
  insert_after(p, NULL, &d, sizeof(int));
  print(p);
  d++;
  insert_after(p, NULL, &d, sizeof(int));
  print(p);
  d++;
  insert_after(p, NULL, &d, sizeof(int));
  print(p);
  d++;
  insert_after(p, NULL, &d, sizeof(int));
  print(p);
  d++;
  insert_after(p, NULL, &d, sizeof(int));
  print(p);
  d++;
  insert_after(p, NULL, &d, sizeof(int));
  print(p);
  d++;
  insert_after(p, NULL, &d, sizeof(int));
  print(p);
  p = destruct(p);
  return 0;
}
void print_int(const void *p) {
  printf("%d ", *(int *)p);
  return;
}
int compare_int(const void *a, const void *b) { return *(int *)a - *(int *)b; }
