## Lisp_Interpreter
This is an interpreter for lisp-like languages, created for a university project of the "Informatics and Computation" course in the second year of the computer engineering university in Genoa.
The project specifications can be found in the "Project_Spec" PDF.

## How to get started
All you need to do is create the executable file in the Project folder using the command:
```console
$ g++ -std=c++17 -o exe_file_name *.cpp
```
This executable will take a text file as input and perform lexical, semantic, and syntactic analysis. If the program internally passes these analyses, it will mean that it respects the grammar of the specifications and therefore it will be evaluated. 
The result will be sent to output.

## Test and run
In the LispInterpreter_TestFiles folder (a folder created by the professor to help us debug), you can find examples of programs to "test" the interpreter and check its correct functioning.
You can run and test the interpreter, located in the Project folder directory, using this command:
```console
$ ./exe_file_name ../LispInterpreter_TestFiles/txt_file_name
```

Have fun with your interpreter!
