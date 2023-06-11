#include "lib.h"

int test() {
#if defined(DEBUG)
  return 1;
#else
  return 12;
#endif
}
