Directory Structure:
-> main.hpp 	- Main program file
-> plot.py 		- Python script to plot b values
-> taskflow 	- Taskflow threading library
-> utilities_v3/timer.hpp - Timing functions 

To compile: (Linux)
g++ -o main main.cpp -I taskflow/ -I utilities_v3/

To plot b values: (Linux)
python3 plot.py

