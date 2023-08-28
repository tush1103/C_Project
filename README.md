# Rewriting Shell Commands In C

## Description
A simple implementation of some of the shell commands using C.

## Features
Set of implemented built-in functionalities:

```bash
cat file_name
```
- reads content of the file and gives it as output.
 
```bash
cat - file_name
```
 - allows to input content into the file.
  
```bash
cat -- file_name
```
- allows to append content into the file.
  
```bash
echo text_to_echo
```
- displays arguments as the standard output.

```bash
ls directory_path
```
- lists files and directories within the specified file

```bash
pwd
```
- prints name of the current working directory

```bash
head number_of_lines file_name
```
- prints specified number of lines from the file starting from the head of the file.

```bash
tail number_of_lines file_name
```
- prints specified number of lines from the file starting fron the tail of the file.


## Prerequisites

```bash
Linux/unix system
C compiler
```

## Execution commands

```bash
gcc -o myshell myshell.c

./myshell
```

## Improvements
- Working on implementing more shell commands.
