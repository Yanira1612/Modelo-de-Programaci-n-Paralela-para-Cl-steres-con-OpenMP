#include <cstdio>
#include <cstdlib>

int producer() {
  int value = rand() % 11;
  printf("[WORKER] value (initial) = %d\n", value);
  return value;
}

int square(int value) {
  return value * value;
}

int add_one(int value) {
  return value + 1;
}

void display(int value) {
  printf("[WORKER] value (final) = %d\n", value);
}

int main(int argc, char **argv) {
  int value = 999;

  #pragma omp parallel
  #pragma omp single
  {
    #pragma omp target nowait depend(out : value) map(from : value)
    value = producer();

    #pragma omp target nowait depend(inout : value) map(tofrom : value)
    value = square(value);

    #pragma omp target nowait depend(inout : value) map(tofrom : value)
    value = add_one(value);

    #pragma omp target nowait depend(in : value) map(to : value)
    display(value);

    printf("[=HOST=] value (inside region) = %d\n", value);
  }

  printf("[=HOST=] value (outside region) = %d\n", value);
  return 0;
}
