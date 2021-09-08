#ifndef DS_LIB_VECTOR
#define DS_LIB_VECTOR

#define INITIAL_CAPACITY 64
#define SORT_CUTOFF 8

typedef struct vec {
  int capacity;
  int len;
  int *data;
} vec;

void vec_init(vec *v);
void vec_init_and_reserve(vec *v, int n);
void vec_upsize(vec *v);
void vec_free(vec *v);
void vec_swap(vec *a, vec *b);
void vec_copy(vec *dest, vec *src);

void vec_push(vec *v, int val);
void vec_shift(vec *v, int val);
void vec_pop(vec *v);
void vec_unshift(vec *v);

void vec_insert(vec *v, int pos, int val);
void vec_erase(vec *v, int pos);

void vec_fill(vec *v, int val);
void vec_reverse(vec *v);
void vec_sort(vec *v);

void vec_fill_range(vec *v, int start, int end, int val);
void vec_reverse_range(vec *v, int start, int end);
void vec_sort_range(vec *v, int start, int end);

int vec_cmp(vec *a, vec *b);
int vec_count(vec *v, int val);
int vec_lower_bound(vec *v, int val);
int vec_upper_bound(vec *v, int val);
int vec_binary_search(vec *v, int val);

#endif
