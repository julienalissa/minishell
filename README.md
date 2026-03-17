This project has been created as part of 42 curriculum by Jualissa Ludebarn

Minishell
Description
The goal of this project is to create a simplified shell, a command line interpreter inspired by Bash and compliant with POSIX standards. It provides a controlled environment where users can execute commands, manage processes, and handle complex command lines.

Key features implemented include:

Command execution: Running external binaries found in the system PATH or through absolute/relative paths.

Builtin commands: Replicating essential shell functions like echo, cd, pwd, export, unset, env, and exit.

Pipes (|): Connecting the output of one command to the input of the next.

Redirections: Supporting input (<), output (>), append (>>), and Here-doc (<<) operators.

Logical Operators: Handling && and || for conditional command execution.

Abstract Syntax Tree (AST): Using an AST to parse and prioritize complex instructions, including support for parentheses () to manage operator priority.

Signal handling: Managing interrupts like Ctrl-C, Ctrl-D, and Ctrl-\ to mimic real shell behavior.

Instructions

Compilation
The project uses a Makefile for compilation. To build the executable, run:

make
This will generate the minishell binary at the root of the repository.

Execution
Once compiled, you can launch the shell by running:

./minishell
Usage
Inside Minishell, you can type commands just like in Bash:

minishell > ls -la | grep "src" > output.txt
minishell > cat output.txt
minishell > exit

Resources
Documentation & Articles

The Open Group Base Specifications (POSIX): Official documentation for shell command language.

GNU Bash Manual: For understanding standard shell behavior and builtin implementation.

CS 42 Projects: General peer-to-peer learning documentation on process management and file descriptors.

https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b
https://42-cursus.gitbook.io/guide/3-rank-03/minishell


Youtube: Oceano

AI Usage
AI (Large Language Models) was used during this project to assist with the following tasks:

Debugging Memory Leaks: Assistance in identifying lost blocks in the Abstract Syntax Tree (AST) and tokenization process during complex pipe executions.

Logic Verification: Helping to structure the logic for process synchronization and signal propagation.

Documentation: Help in structuring and phrasing this README.md file in English.
