# Minishell
This is a minishell that supports the minimal features of Bash.

## What is a shell?
A shell is a command-line interface program that allows users to interact with the operating system. It acts as a mediator between the user and the underlying system by interpreting and executing commands the user enters. Shells can perform tasks such as running programs, managing files, and controlling processes. Common patterns of shells include interactive shells for direct command execution and scripting shells for executing a series of commands in scripts.

## What is Bash?
Bash (Bourne Again Shell) is a widely used Unix shell and command-line interpreter. It is an enhanced version of the original Bourne Shell (sh) and is the default shell on many Linux distributions. Bash offers numerous features, such as command history, job control, shell scripting capabilities, and programmable completion. It is powerful and user-friendly, making it popular among developers, system administrators, and casual users.

# Features
This minishell supports the following features:
- lexing and parsing input line
- searching path and executing a command
- pipe and redirection (including here-document)
- adding, modifying, deleting, and expanding environment variables
- wildcard `*` and `?` only for the current directory
- signal ctrl-c and ctrl-\
- `||`, `&&`, and `()` for the priority of evaluation
- some builtin commands (`cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`) 
- single/double quotations

# Unsupported features
- Background processes using & (e.g., command &).
- Advanced wildcard patterns (e.g., recursive **).
- Command substitution using backticks (e.g., `command`).
- Process substitution (e.g., <(command) or >(command)).
- Arithmetic evaluation (e.g., $((1+1))).
- Word splitting
- Job control (e.g., fg, bg, jobs).
- Aliases for commands (e.g., alias ll='ls -l').
- Multi-line commands using a backslash (e.g., command1 \ on one line).
- Custom prompt settings (e.g., PS1 formatting).
- Shell scripting or execution of script files directly (e.g., ./script.sh).
- Array or variable management beyond basic environment variables.
- Builtin commands like history or help.

# Contributors
- [kurrrru](https://github.com/kurrrru/)
- [mmiyahar1205](https://github.com/mmiyahar1205)

# Development time
2024/11/5 - 2024/12/3

# License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
