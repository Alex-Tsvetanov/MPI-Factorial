# MPI Factorial

```asciidoc
MPI command line application calculating factorial
--------------------------------------------------

1) Implement simple MPI application "mpi_factorial" in a way like you write production code (structured code with alignments, comments where needed, etc.).
2) The application calculates factorial of N (N!), N is defined as command line argument.
3) The application calculation is scaled over NP processors passed to utility mpirun
   $ mpirun -np <NP> mpi_factorial <N>
4) Each proccess instance calculates multiplication of individual 1/NP portion of factorial multipliers.
5) Root instance additianaly multiplies calculated parts from all instances and prints the final result value of N!.
6) Run the application by using:
   $ mpirun mpirun -np 4 mpi_factorial 100
      and
   $ mpirun mpirun -np 1 mpi_factorial 100
7) Send us the application source code, mpirun results, comment about N! results got from mpiruns with different NP parameters.
```