#include "common.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void destroy(void *item)
{
	free(item);
    item = NULL;
}
