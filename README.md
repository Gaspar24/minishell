# Minishell

## Overview
Minishell is a simplified implementation of a Unix shell, developed as a project for [your institution or program]. The aim of the project is to deepen the understanding of system-level programming in C and gain hands-on experience with process control, file I/O, and signal handling in a real-world environment.

The shell replicates core functionalities of Bash, including prompt display, command execution, redirections, pipes, and handling environment variables. It also includes a set of built-in commands and ensures robust handling of signals and special characters.

## Features

- **Interactive Prompt**: Displays a prompt when waiting for user input.
- **Command Execution**: Searches for and executes commands based on the `PATH` variable, supporting relative and absolute paths.
- **Redirections**: Supports input (`<`), output (`>`), output append (`>>`), and heredoc (`<<`) redirections.
- **Pipes**: Implements pipelines (`|`) where the output of one command is passed to the next as input.
- **Environment Variables**: Expands environment variables (`$VAR`) and supports `$?` for the exit status of the last command.
- **Signal Handling**: Manages `ctrl-C`, `ctrl-D`, and `ctrl-\` like Bash:
  - `ctrl-C`: Displays a new prompt.
  - `ctrl-D`: Exits the shell.
  - `ctrl-\`: Does nothing.
- **Quotes**: Handles single (`'`) and double (`"`) quotes, with specific behavior for metacharacters inside quotes.
- **Built-in Commands**:
  - `echo` with `-n` option
  - `cd` (relative and absolute paths only)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- **History**: Maintains a history of commands using `readline`.

## What I Learned

1. **System-Level Programming**: Gained in-depth knowledge of system calls like `fork`, `execve`, `pipe`, `dup2`, and more.
2. **Signal Handling**: Learned how to handle signals safely and effectively without relying on global data structures.
3. **Redirections and Pipes**: Implemented redirections and pipelines, understanding how to manipulate file descriptors and manage process synchronization.
4. **Environment Variables**: Understood how shells manage and expand environment variables.
5. **Memory Management**: Developed practices to avoid memory leaks, especially when integrating with external libraries like `readline`.
6. **Error Handling**: Improved skills in writing robust error handling for system calls and user inputs.

## Challenges Overcome

- **Signal Safety**: Managing signal handlers without using global variables was challenging but led to a deeper understanding of safe signal handling.
- **Redirections and Heredoc**: Implementing heredoc (`<<`) required careful management of temporary files and reading input until the delimiter.
- **Pipelines**: Synchronizing multiple processes in a pipeline was a complex task that required precise management of file descriptors and process IDs.
- **Quotes and Escaping**: Handling nested quotes and special character parsing required a robust tokenizer and parser design.
- **Memory Leaks**: Ensuring no memory leaks in custom code while handling dynamic allocations in a large project.

## How to Use

1. **Clone the Repository**:
   ```bash
   git clone <repository_url>
   cd minishell
   ```

2. **Compile the Shell**:
   Use the `Makefile` provided:
   ```bash
   make
   ```

3. **Run Minishell**:
   ```bash
   ./minishell
   ```

4. **Clean Up**:
   ```bash
   make clean
   make fclean
   ```

## External Functions Used
- `readline`, `add_history`, `rl_clear_history`
- File I/O: `open`, `read`, `write`, `close`
- Process Management: `fork`, `execve`, `wait`, `pipe`
- Signal Handling: `signal`, `sigaction`
- Others: `getcwd`, `chdir`, `strerror`, `perror`

## Requirements
- Only one global variable for signal handling.
- No memory leaks in custom code.
- Proper handling of edge cases for all functionalities.

## Resources
- [Readline Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [Unix Manual Pages](https://man7.org/linux/man-pages/)

---

Thank you for exploring this project! Feel free to contribute or suggest improvements by opening an issue or a pull request.
