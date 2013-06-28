
#ifndef QKSORT_H
#define QKSORT_H

#include <stdlib.h>
#include <string.h>

int qksort(void *data, int len, int esize, int i, int k, int (*cmp)(const void *, const void *));

#endif



