#include <cstdio>
#include <cstdlib>
#include <omp.h>

constexpr size_t N = 4096;

/// Initialize array with ones
void init_array(int *data, size_t N) {
  for (size_t i = 0; i < N; i++)
    data[i] = 1;
}

/// Perform partial reduction of an array with sum operation
int reduce_sum(int *data, size_t block_size, size_t idx) {
  int sum = 0;
  size_t start_idx = idx * block_size;
  for (size_t i = 0; i < block_size; i++)
    sum += data[start_idx + i];
  return sum;
}

int main(int argc, char **argv) {
  int nworkers = omp_get_num_devices();
  int block_size = N / nworkers;
  int result = 0;

  int *data = new int[N];
  int *partial = new int[nworkers];

  init_array(data, N);

  printf("[HOST] Number of workers = %d\n", nworkers);
  printf("[HOST] Block size = %d\n", block_size);

  #pragma omp parallel
  #pragma omp single
  {
    // Send one block to each worker and perform partial sum
    for (int i = 0; i < nworkers; i++) {
      #pragma omp target nowait \
          map(to: data[i*block_size:block_size]) \
          map(tofrom: partial[i]) \
          depend(out: partial[i])
      partial[i] = reduce_sum(data, block_size, i);
    }

    // Reduce partial sums into final result
    #pragma omp target nowait \
        map(to: partial[:nworkers]) \
        depend(iterator(i=0:nworkers), in: partial[i]) \
        map(from: result) \
        depend(out: result)
    result = reduce_sum(partial, nworkers, 0);
  }

  printf("[HOST] Result = %d\n", result);

  delete[] data;
  delete[] partial;
  return 0;
}
