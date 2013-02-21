#include <time.h>
#ifndef _random_
#define _random_
#define random(n) (rand() % (n))
#define randomize() (srand((unsigned)time(NULL)))
#endif
