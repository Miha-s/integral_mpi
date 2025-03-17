
integral_open_mp: integral_open_mp.cpp
	g++ -O0 -o integral_open_mp integral_open_mp.cpp -fopenmp -lm

integral_mpi: integral_mpi.cpp
	mpic++ -O0 -o integral_mpi integral_mpi.cpp -lm

integral_sequential: integral_sequential.cpp
	g++ -O0 -o integral_sequential integral_sequential.cpp -lm

run_integral_mpi: integral_mpi
	mpirun --use-hwthread-cpus -np 4 ./integral_mpi $(DIVISIONS)