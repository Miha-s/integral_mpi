# Intro
This repository contains code to compare time execution of computing integral using sequential and parralel processing incorporating MPI and openMP


# Analysis
| Number of divisions | sequential (s) | OpenMP (s) | MPI (s) | Speedup OpenMP | Speedup MPI
| ----  | -----  |  -----  | ------- | ----- | ----
| 1M    | 6.78 s | 1.8 s   | 2.45 s  | 3.77  | 2.77 
| 5M    | 35.2 s | 9.34 s  | 10 s    | 3.77  | 3.52
| 10M   | 69.7 s | 18.91 s | 19.64 s | 3.68  | 3.55