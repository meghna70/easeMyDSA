#include "vector.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vec_init(vec *v) {
  v->capacity = INITIAL_CAPACITY;
  v->data = (int *)malloc(v->capacity * sizeof(int));
  v->len = 0;
}

void vec_init_and_reserve(vec *v, int n) {
  assert(n > 0);

  v->capacity = n;
  v->data = (int *)malloc(v->capacity * sizeof(int));
  v->len = 0;
}

void vec_upsize(vec *v) {
  v->capacity *= 2;
  v->data = (int *)realloc(v->data, v->capacity * sizeof(int));
}

void vec_free(vec *v) {
  v->capacity = v->len = 0;
  free(v->data);
  v->data = NULL;
}

void vec_swap(vec *a, vec *b) {
  vec temp = *a;
  *a = *b;
  *b = temp;
}

void vec_copy(vec *dest, vec *src) {
  dest->capacity = src->capacity;
  dest->len = src->len;
  dest->data = (int *)malloc(dest->capacity * sizeof(int));
  memcpy(dest->data, src->data, dest->len * sizeof(int));
}

void vec_push(vec *v, int val) {
  if (v->len == v->capacity) {
    vec_upsize(v);
  }

  v->data[v->len++] = val;
}

void vec_shift(vec *v, int val) {
  if (v->len == v->capacity) {
    vec_upsize(v);
  }

  for (int i = v->len - 1; i >= 0; i--) {
    v->data[i + 1] = v->data[i];
  }

  v->data[0] = val;
  v->len++;
}

void vec_pop(vec *v) {
  assert(v->len > 0);

  v->len--;
}

void vec_unshift(vec *v) {
  assert(v->len > 0);

  v->len--;

  for (int i = 0; i < v->len; i++) {
    v->data[i] = v->data[i + 1];
  }
}

void vec_insert(vec *v, int pos, int val) {
  assert(pos >= 0 && pos <= v->len);

  if (v->len == v->capacity) {
    vec_upsize(v);
  }

  for (int i = v->len - 1; i >= pos; i--) {
    v->data[i + 1] = v->data[i];
  }

  v->data[pos] = val;
  v->len++;
}

void vec_erase(vec *v, int pos) {
  assert(pos >= 0 && pos < v->len);

  v->len--;

  for (int i = pos; i < v->len; i++) {
    v->data[i] = v->data[i + 1];
  }
}

void vec_fill(vec *v, int val) { vec_fill_range(v, 0, v->len, val); }
void vec_reverse(vec *v) { vec_reverse_range(v, 0, v->len); }
void vec_sort(vec *v) { vec_sort_range(v, 0, v->len); }

void vec_fill_range(vec *v, int start, int end, int val) {
  assert(start <= end);
  assert(start >= 0 && start <= v->len);
  assert(end >= 0 && end <= v->len);

  for (int i = start; i < end; i++) {
    v->data[i] = val;
  }
}

void vec_reverse_range(vec *v, int start, int end) {
  assert(start <= end);
  assert(start >= 0 && start <= v->len);
  assert(end >= 0 && end <= v->len);

  for (int i = start, j = end - 1; i < j; i++, j--) {
    int temp = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = temp;
  }
}

void vec_sort_range(vec *v, int start, int end) {
  assert(start <= end);
  assert(start >= 0 && start <= v->len);
  assert(end >= 0 && end <= v->len);

  if (end - start <= SORT_CUTOFF) {
    // printf("insert(%d %d)\n", start, end);
    // Use insertion sort for small arrays
    for (int i = start + 1; i < end; i++) {
      int curr = v->data[i];
      // Current element is inserted after v->data[j]
      int j = i - 1;
      while (j != start - 1 && v->data[j] > curr) {
        v->data[j + 1] = v->data[j];
        j--;
      }
      v->data[j + 1] = curr;
    }
  } else {
    // int selected = start + rand() % (end - start);
    // assert(selected >= start && selected < end);

    // // Move selected element to last
    // int temp = v->data[selected];
    // v->data[selected] = v->data[end - 1];
    // v->data[end - 1] = temp;

    // Partition
    int pos = start;
    for (int i = start; i < end - 1; i++) {
      if (v->data[i] < v->data[end - 1]) {
        int temp = v->data[pos];
        v->data[pos] = v->data[i];
        v->data[i] = temp;
        pos++;
      }
    }

    // Put pivot in correct place
    int temp = v->data[pos];
    v->data[pos] = v->data[end - 1];
    v->data[end - 1] = temp;

    // printf("sort(%d %d %d)\n", start, end, pos);

    // Recurse
    vec_sort_range(v, start, pos);
    vec_sort_range(v, pos + 1, end);
  }
}

int vec_cmp(vec *a, vec *b) {
  int limit = a->len < b->len ? a->len : b->len;
  for (int i = 0; i < limit; i++) {
    if (a->data[i] != b->data[i]) {
      return a->data[i] - b->data[i];
    }
  }

  if (a->len != b->len) {
    return a->len - b->len;
  }

  return 0;
}

int vec_count(vec *v, int val) {
  int count = 0;
  for (int i = 0; i < v->len; i++) {
    if (v->data[i] == val) {
      count++;
    }
  }
  return count;
}

int vec_lower_bound(vec *v, int val) {
  int it = -1;
  for (int step = v->len; step >= 1; step /= 2) {
    while ((it + step) < v->len && v->data[it + step] < val) {
      it += step;
    }
  }
  return it + 1;
}

int vec_upper_bound(vec *v, int val) {
  int it = -1;
  for (int step = v->len; step >= 1; step /= 2) {
    while ((it + step) < v->len && v->data[it + step] <= val) {
      it += step;
    }
  }
  return it + 1;
}

int vec_binary_search(vec *v, int val) {
  return vec_upper_bound(v, val) - vec_lower_bound(v, val);
}
