@echo off

g++ src/QE_solver.cpp src/main.cpp -O0 -o main.exe -DDEBUG
main.exe