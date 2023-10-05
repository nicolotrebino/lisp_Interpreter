## Lisp_Interpreter
This is an interpreter for lisp-like languages, created for a university project of the "Informatics and Computation" course in the second year of the computer engineering university in Genoa.
The project specifications can be found in the "Project_Spec" PDF.

## How to get started
All you need to do is create the executable file in the Project folder using the command:
```console
$ g++ -std=c++17 -o exe_file_name *.cpp
```
This executable will take a text file as input and perform lexical, semantic, and syntactic analysis. If the program internally passes these analyses, it will mean that it respects the grammar of the specifications and will therefore be evaluated.
The result will be sent as output on the terminal.

## Test and run
In the LispInterpreter_TestFiles folder (a folder created by the professor to help us debug), you can find examples of programs to "test" the interpreter and check its correct functioning.
You can run and test the interpreter, located in the Project folder directory, using this command:
```console
$ ./exe_file_name ../LispInterpreter_TestFiles/txt_file_name
```
You can also change the program output by changing the value of the DEBUG variable in the "lispInterpreter.cpp" file.

4 different debugging levels can be used:
* 0 --> the output will only be the evaluation of the program.
* 1 --> will display the evaluation of the program and the tokens created by the interpreter during the tokenization phase.
* 2 --> will display the evaluation of the program and the program read, i.e. (in a theoretical way) the syntax tree created during the parsing phase.
* 3 --> all possible outputs will be displayed, i.e. tokens, syntax tree, and program evaluation.

Have fun with your interpreter!
