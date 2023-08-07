# Simple Shell

The simple_shell is a basic recreation of the sh shell, written in C. It's designed to offer fundamental functionalities akin to standard shells. However, it's important to note that this project is a simplified version and is not yet complete.

## Features
### Environment Variable Management

+ Extraction: Retrieve the value of a specific environment variable (_getenv.c).
+ Copy: Create a duplicate of the environment variables for manipulation (environ_cpy.c).
+ Setting & Unsetting: Modify environment variables with functions like _setenv and _unsetenv (setenv.c).

### Built-in Commands

+ Exit: Terminate the shell session (exit_bul).
+ Environment Display: Showcase all environment variables (env_bul).
+ Directory Change: Navigate between directories (_cd).
+ Set & Unset Environment Variables: Modify environment variables directly (setenv.c).

### Command Execution

+ User Commands: Execute user-specified commands and verify their existence (funcs.c, execute_commands).
+ Path Handling: Identify if user input is a path and locate the complete path to a file (functions.c).
+ Tokenization: Break down user input into separate commands and arguments (tokenize.c).
+ Main Execution Loop: A continuous loop that captures and processes user input, handling signals and forking processes for command execution (shell.c).

### String Utilities

+ A suite of string manipulation functions, including comparison, copying, concatenation, and tokenization (string_funcs.c, more_string_funcs.c).

### Additional Utilities

+ Display the shell prompt, manage fork errors, and handle pre-execution steps (more_funcs.c, shell_execution_funcs.c).

### Structure & Definitions (shell.h)

+ The header file contains necessary includes, struct definitions (like builtins), and declarations for a myriad of utility functions. These range from string operations to command execution and error handling.

### Usage

+ To utilize the simple_shell, compile the source files using ```gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh``` and execute the resulting binary. The shell will then prompt you for commands, allowing for an interactive session.
