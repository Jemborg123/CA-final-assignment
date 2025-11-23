# HOW TO RUN
We have included a makefile, thus installing make is a prerequisite.
GNU or similar c compiler is also needed.


## Compilation and execution
#### Windows
`make windows` to compile on a windows machine
This will generate a file `main.exe`
To run a `.bin` simply add your file as in argument e.g. `./main.exe string.bin`

#### Linux
`make linux` to compile on a unix based OS
This will generate a file `main.out`
To run a `.bin` simply add your file as in argument e.g. `./main.out string.bin`


## Program Validation
In order to test and make sure our program is running correctly we have made the files `readres.c` and `main.py`
### Single test file
#### Windows
Compiling `readres.c` with `make resread` and running `./resread.exe string.res` will compare the res file generated from our program with the res file supplied from the cae-lab repository, and show which lines are matching and which differ.

#### Linux
Compiling `readres.c` with `make resreadlinux` and running `./resread.out string.res` will compare the res file generated from our program with the res file supplied from the cae-lab repository, and show which lines are matching and which differ.

### Running all test files
(Python is needed for this part)
Given all the test task folders have been added to the root of the project, running `py main.py` will use the latest compiled version of the program to validate on each of the test and print which tests fail and which succeed.