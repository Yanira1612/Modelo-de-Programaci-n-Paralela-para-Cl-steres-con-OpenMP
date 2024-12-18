#include "../common/Timer.h"
#include <cstdio>

size_t fib_serial(size_t N) {
  if (N < 2)
    return 1;

  size_t i = fib_serial(N - 1);
  size_t j = fib_serial(N - 2);
  return i + j;
}

size_t fib_parallel_impl(size_t N) {
  if (N < 2)
    return 1;

  size_t i, j;
#pragma omp task shared(i)
  i = fib_parallel_impl(N - 1);
#pragma omp task shared(j)
  j = fib_parallel_impl(N - 2);
#pragma omp taskwait
  return i + j;
}

size_t fib_parallel(size_t N) {
  size_t result;
#pragma omp parallel
#pragma omp single
  result = fib_parallel_impl(N);
  return result;
}

#define FIB_SERIAL(N)                                                          \
  do {                                                                         \
    printf("fib_serial(" #N ") = %ld\n", fib_serial(N));                       \
  } while (0)

#define FIB_PARALLEL(N)                                                        \
  do {                                                                         \
    printf("fib_parallel(" #N ") = %ld\n", fib_parallel(N));                   \
  } while (0)

int main(int argc, char **argv) {
  {
    Timer t("Serial");
    FIB_SERIAL(35);
  }
  {
    Timer t("Parallel");
    FIB_PARALLEL(35);
  }
  return 0;
}
