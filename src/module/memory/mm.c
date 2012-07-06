#include <stdlib.h>
#include "mm.h"

void init_engine_mm()
{

}

void engine_mm_free(void* ptr)
{
	free(ptr);
}
