/* matmult.c 

   Test program to do matrix multiplication on large arrays.
 
   Intended to stress virtual memory system.
   
   Ideally, we could read the matrices off of the file system,
   and store the result back to the file system!
 */

#include <stdio.h>
#include <syscall.h>

/* You should define DIM to be large enough that the arrays
   don't fit in physical memory.

    Dim       Memory
 ------     --------
     16         3 kB
     64        48 kB
    128       192 kB
    256       768 kB
    512     3,072 kB
  1,024    12,288 kB
  2,048    49,152 kB
  4,096   196,608 kB
  8,192   786,432 kB
 16,384 3,145,728 kB */
#define DIM 128

int A[DIM][DIM];
int B[DIM][DIM];
int C[DIM][DIM];

int
main (void)
{
  int i, j, k;

  /* Initialize the matrices. */
  for (i = 0; i < DIM; i++)
    for (j = 0; j < DIM; j++)
      {
	A[i][j] = i;
	B[i][j] = j;
	C[i][j] = 0;
      }

  /* Multiply matrices. */
  for (i = 0; i < DIM; i++)	
    for (j = 0; j < DIM; j++)
      for (k = 0; k < DIM; k++)
	C[i][j] += A[i][k] * B[k][j];

  /* Done. */
  exit (C[DIM - 1][DIM - 1]);
}
