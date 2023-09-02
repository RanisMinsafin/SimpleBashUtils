# Simple Bash Utils

Development of Bash text utilities: cat, grep.

## Table of Contents

1. [Introduction](#introduction)
2. [Project Details](#project-details)
    - [Development Language and Standards](#development-language-and-standards)
    - [Project Structure](#project-structure)
    - [Code Style](#code-style)
    - [Executable Programs](#executable-programs)
    - [Build Process](#build-process)
    - [Integration Tests](#integration-tests)
    - [Structured Programming](#structured-programming)
    - [Code Reusability](#code-reusability)
    - [Library Usage](#library-usage)
    - [Error Handling](#error-handling)
    - [Input Method](#input-method)
3. [Part 1: Working with the cat utility](#part-1-working-with-the-cat-utility)
4. [Part 2: Working with the grep utility](#part-2-working-with-grep-utility)
5. [Part 3: Bonus - Implementation of some grep utility flags](#part-3-bonus-implementation-of-some-grep-utility-flags)
6. [Part 4: Bonus - Implementation of grep utility flag combinations](#part-4-bonus-implementation-of-grep-utility-flag-combinations)

## Introduction

In this project, I have developed essential Bash utilities for working with C programming language texts: `cat` and `grep`. These utilities are commonly used in the Linux terminal and follow the POSIX.1-2017 standard.

## Project Details

### Development Language and Standards

- The programs were developed in C language of C11 standard using the GCC compiler.
- I adhered to the POSIX.1-2017 standard to ensure compatibility and portability.

### Project Structure

- The program code of the `cat` utility is located on the `develop` branch in the `src/cat/` directory.
- The program code of the `grep` utility is located on the `develop` branch in the `src/grep/` directory.

### Code Style

- When writing code, I followed the Google style guide to maintain consistency and readability.

### Executable Programs

- The programs are executable files with command line arguments.

### Build Process

- I used a Makefile for the build process, providing appropriate targets:
  - To build the `cat` utility: `cat`
  - To build the `grep` utility: `grep`

### Integration Tests

- Integration tests cover all flag variants and input values, ensuring that the utilities behave similarly to real Bash utilities.

### Structured Programming

- The programs were developed according to the principles of structured programming, ensuring maintainability and clarity.

### Code Reusability

- I avoided code duplication and promoted code reusability by using common modules, which can be found in the `src/common` folder.

### Library Usage

- I used only standard C libraries and adhered to modern practices, avoiding outdated and legacy language constructions and library functions.

### Error Handling

- I provided clear error messages in the case of errors to enhance user experience.

### Input Method

- Input via stdin is not required to be supported by the utilities.

## Part 1: Working with the cat utility

I have successfully developed the `cat` utility with support for all flags specified in the documentation.

### Part 2: Working with the grep utility

I have implemented the `grep` utility with support for the following flags: `-e`, `-i`, `-v`, `-c`, `-l`, and `-n`. I used pcre or regex libraries for regular expressions.

### Part 3: Bonus - Implementation of some grep utility flags

As a bonus, I have developed the `grep` utility with support for all flags, including: `-h`, `-s`, `-f`, and `-o`. I continued to use pcre or regex libraries for regular expressions.

### Part 4: Bonus - Implementation of grep utility flag combinations

As an additional bonus, I implemented the `grep` utility with support for all flags, including their _pair_ combinations (e.g., `-iv`, `-in`). I utilized pcre or regex libraries for regular expressions.
