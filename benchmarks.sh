#mpic++ MPI/MPI-Factorial-naive-split.cpp lib/BigUInt.cpp -o main.exe -std=c++17
#mpic++ MPI/MPI-Factorial-optimized.cpp lib/BigUInt.cpp -o main-optimized.exe -std=c++17
#mpic++ MPI/MPI-Factorial-longdouble.cpp -o main-longdouble.exe -std=c++17
#g++ multithread/main.cpp lib/BigUInt.cpp -o main-multithread.exe -std=c++17 -pthread

echo -e "Factorial\tCores\tMethod\tReal\tUser\tSys";
for n in 10 100 10000 50000 ; do
    for cores in 1 2 4 8; do
        /usr/bin/time -f "$n!\t$cores\tMPI Standard factor separation\t%E\t%U\t%S" mpirun --allow-run-as-root -np $cores ./main.exe $n > /dev/null;
        /usr/bin/time -f "$n!\t$cores\tMPI Optimized factor separation\t%E\t%U\t%S" mpirun --allow-run-as-root -np $cores ./main-optimized.exe $n > /dev/null;
        /usr/bin/time -f "$n!\t$cores\tMPI long double Optimized factor separation\t%E\t%U\t%S" mpirun --allow-run-as-root -np $cores ./main-longdouble.exe $n > /dev/null;
        /usr/bin/time -f "$n!\t$cores\tMulti-thread Optimized factor separation\t%E\t%U\t%S" ./main-multithread.exe -np $cores -n $n > /dev/null;
        echo "";
    done;
done