Directory Structure:
/Task2 -> class_def.hpp - Classes implemented uptil task 2
/Task3-4 -> class_def.hpp - Classes defined for all tasks
	 -> class_def.cpp - Classes implemented for all tasks
	 -> timer.hpp - Timer class from previous hw for performance eval
	 -> main.cpp - main function call for grid generation/ performace eval

To compile: (Linux)
/Task2 - g++ -o main main.cpp 
/Task3-4 - g++ -o main main.cpp class_def.cpp

To plot: (Linux)
python3 plotdomain.py 

Note:
- Adjust grid divisions using #defines in main.cpp
