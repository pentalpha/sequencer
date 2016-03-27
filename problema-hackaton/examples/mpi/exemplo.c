#include <mpi.h>
#include <stdio.h>

int main(int argc, char*argv[]) {
  int mpi_thread = MPI_THREAD_MULTIPLE;
  int rank, size;
  MPI_Init_thread(&argc, &argv, &mpi_thread);

  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  printf("Hello world from process %d of %d\n", rank, size );

  MPI_Finalize();
  return 0;
}

