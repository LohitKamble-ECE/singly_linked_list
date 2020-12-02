/**
 * Singly Linked-list Implementation
 *
 * Author: Lohit Kamble
 * Date  : Dec 3 2020
 * Time  : 01:55
 * System: Ubuntu 20.10
 */
#include "list.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Static Function Prototype.
static node *allocate_node(const void *data, const size_t size, node *suc);
static bool is_present(list *this_list, node *this_node);
static node *prev_node(list *this_list, node *this_node);

/**
 * Allocates the memory for the new node and initializes its member.
 * If it unalbe to do so, returns the NULL pointer.
 */
static node *allocate_node(const void *data, const size_t size, node *suc) {
  node *new_node = NULL;
  if ((new_node = (node *)malloc(sizeof(node)))) {
    if ((new_node->data = malloc(sizeof(size)))) {
      memmove(new_node->data, data, size);
      new_node->suc = (node *)suc;
    } else {
      free(new_node);
      new_node = NULL;
    }
  }
  return new_node;
}

/**
 * Check whether node present in the list or not.
 */
static bool is_present(list *this_list, node *this_node) {
  if (this_list) {
    node *trav = this_list->beg;
    while (trav) {
      if (trav == this_node) {
        return true;
      }
      trav = trav->suc;
    }
  }
  return false;
}

/**
 * Returns the address of previous node of 'this_node'.
 * If there happen to be no node present then returns the address of the
 * 'this_node'
 */
static node *prev_node(list *this_list, node *this_node) {
  if (this_list) {
    node *curr, *prev;
    prev = curr = this_list->beg;
    while (curr) {
      if (curr == this_node) {
        return prev;
      }
      prev = curr;
      curr = curr->suc;
    }
  }
  return NULL;
}

/**
 * Construct the list so that it is available to perform operation on it.
 */
list *construct(list *this_list, void (*print)(const void *),
                int (*compare)(const void *, const void *)) {
  if (!this_list) {
    if ((this_list = (list *)malloc(sizeof(list)))) {
      this_list->beg = NULL;
      this_list->end = NULL;
      this_list->size = 0;
      this_list->print = print;
      this_list->compare = compare;
    }
  }
  return this_list;
}

/**
 * Print the list.
 */
void print(list *this_list) {
  if (this_list) {
    node *trav = this_list->beg;
    while (trav) {
      this_list->print(trav->data);
      printf(" ");
      trav = trav->suc;
    }
    printf("\n");
  }
  return;
}

/**
 * Insert the new node before the 'this_node' into the list.
 * If the list is emtpy or the 'this_node' is NULL then insertion is at the
 * beginning of the list.
 */
int insert_before(list *this_list, node *this_node, const void *data,
                  const size_t size) {
  if (this_list) {
    if (!this_list->beg || !this_node || this_node == this_list->beg) {
      // Insertion at the head of the list.
      node *new_node = NULL;
      if ((new_node = allocate_node(data, size, this_list->beg))) {
        if (!this_list->beg) {
          this_list->end = new_node;
        }
        this_list->beg = new_node;
        ++this_list->size;
        return 0;
      }
    } else {
      // Insertion somewhere other than head of the list.
      node *curr, *prev;
      prev = curr = this_list->beg;
      while (curr != this_node) {
        if (!curr) {
          return -1;
        } else {
          prev = curr;
          curr = curr->suc;
        }
      }
      node *new_node;
      if ((new_node = allocate_node(data, size, this_node))) {
        prev->suc = new_node;
        ++this_list->size;
        return 0;
      }
    }
  }
  return -1;
}

/**
 * Insert the new node after the 'this_node' in the list.
 * If the list is empty then insertion is at the head of the list.
 * And if the 'this_node' is NULL then insertion is at the tail of the list.
 */
int insert_after(list *this_list, node *this_node, const void *data,
                 const size_t size) {
  if (this_list) {
    if (!this_list->beg) {
      // Insertion at the head of the list.
      if (insert_before(this_list, NULL, data, size) == 0) {
        return 0;
      } else {
        return -1;
      }
    } else if (!this_node || this_node == this_list->end) {
      // Insertion at the tail of the list.
      node *new_node = NULL;
      if ((new_node = allocate_node(data, size, NULL))) {
        this_list->end->suc = new_node;
        this_list->end = new_node;
        ++this_list->size;
        return 0;
      }
    } else {
      // Insertion somewhere other than head and tail of the list.
      if (is_present(this_list, this_node) == true) {
        node *new_node = NULL;
        if ((new_node = allocate_node(data, size, this_node->suc))) {
          this_node->suc = new_node;
          ++this_list->size;
          return 0;
        }
      }
    }
  }
  return -1;
}
/**
 * Internal implementation to reverse the list. The algorithm underlying these
 * uses the recursive calling technique it achieve the solution.
 */
node *__reverse(list *this_list, node *trav) {
  this_list->beg = trav;
  if (trav->suc) {
    node *temp = __reverse(this_list, trav->suc);
    temp->suc = trav;
  }
  trav->suc = NULL;
  this_list->end = trav;
  return trav;
}

/**
 * Reverse the entire list.
 */
void reverse(list *this_list) {
  __reverse(this_list, this_list->beg);
  return;
}

/**
 * Remove the currnet node i.e. 'this_node' from the list.
 * If the 'this_node' is NULL then removes the last node of the list.
 */
int remove_current(list *this_list, node *this_node) {
  if (this_list) {
    if (!this_node || this_node == this_list->end) {
      // Remove the last node present from the list.
      node *prev = prev_node(this_list, this_list->end);
      prev->suc = NULL;
      free(this_list->end->data);
      free(this_list->end);
      if (this_node == this_list->beg) {
        this_list->beg = NULL;
        this_list->end = NULL;
      } else {
        this_list->end = prev;
      }
      --this_list->size;
      return 0;
    } else if (this_node == this_list->beg) {
      this_list->beg = this_list->beg->suc;
      free(this_node->data);
      free(this_node);
      --this_list->size;
      return 0;
    } else {
      node *prev, *curr;
      prev = curr = this_list->beg;
      while (curr != this_node) {
        if (!curr) {
          return -1;
        } else {
          prev = curr;
          curr = curr->suc;
        }
      }
      prev->suc = curr->suc;
      free(curr->data);
      free(curr);
      --this_list->size;
      return 0;
    }
  }
  return -1;
}

/**
 * Remove all the node present in the list.
 */
int remove_all(list *this_list) {
  if (this_list) {
    while (this_list->beg) {
      remove_current(this_list, this_list->end);
    }
    return 0;
  }
  return -1;
}

/**
 * Deallocated the entire list.
 * It removes all the node present in the list and then deallocated the memory
 * of list itself.
 */
list *destruct(list *this_list) {
  if (this_list) {
    remove_all(this_list);
    free(this_list);
    this_list = NULL;
  }
  return this_list;
}

/**
 * Return the pointer to the first node of the list.
 */
node *get_begin(list *this_list) {
  if (this_list) {
    return this_list->beg;
  }
  return NULL;
}

/**
 * Return the pointer to the last node of the list.
 */
node *get_end(list *this_list) {
  if (this_list) {
    return this_list->end;
  }
  return NULL;
}

/**
 * Return the size of the list.
 */
size_t get_size(list *this_list) {
  if (this_list) {
    return this_list->size;
  }
  return 0;
}

/**
 * Return the address of node which is present at an index 'n'.
 */
node *node_at(list *this_list, size_t n) {
  if (this_list) {
    if (n < this_list->size) {
      size_t i = 0;
      node *trav = this_list->beg;
      while (trav) {
        if (i == n) {
          return trav;
        }
        trav = trav->suc;
        ++i;
      }
    }
  }
  return NULL;
}
/**
 * Return the address of node whose data part is equal to the 'data' passed to
 * this function.
 */
node *find_key(list *this_list, void *data) {
  if (this_list) {
    node *trav = this_list->beg;
    while (trav) {
      if (!this_list->compare(trav->data, data)) {
        return trav;
      }
      trav = trav->suc;
    }
  }
  return NULL;
}

/**
 * Shift the content of the list to left by 'n'.
 * where n must be greater than zero and must be less than number of node
 * present in the list.
 */
int rotate_left(list *this_list, size_t n) {
  if (this_list) {
    if (n > 0 && n < this_list->size) {
      node *temp = NULL;
      if ((temp = node_at(this_list, n - 1))) {
        this_list->end->suc = this_list->beg;
        this_list->beg = temp->suc;
        this_list->end = temp;
        this_list->end->suc = NULL;
        return 0;
      }
    }
  }
  return -1;
}

/**
 * Shift the content of the list to right by 'n'.
 * where n must be greater than zero and must be less than the number of node
 * present in the list.
 */
int rotate_right(list *this_list, size_t n) {
  if (this_list) {
    if (n > 0 && n < this_list->size) {
      if (rotate_left(this_list, this_list->size - n)) {
        return 0;
      }
    }
  }
  return -1;
}

/**
 * Insert the node in an ascending order.
 */
int insert_ascending(list *this_list, void *data, size_t size) {
  if (this_list) {
    node *trav = this_list->beg;
    while (trav) {
      if (this_list->compare(trav->data, data) >= 0) {
        insert_before(this_list, trav, data, size);
        return 0;
      }
      trav = trav->suc;
    }
    insert_after(this_list, trav, data, size);
    return 0;
  }
  return -1;
}

/**
 * Insert the node in an descending order.
 */
int insert_descending(list *this_list, void *data, size_t size) {
  if (this_list) {
    node *trav = this_list->beg;
    while (trav) {
      if (this_list->compare(trav->data, data) <= 0) {
        insert_before(this_list, trav, data, size);
        return 0;
      }
      trav = trav->suc;
    }
    insert_after(this_list, trav, data, size);
    return 0;
  }
  return -1;
}
