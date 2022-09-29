# minishell

<p align="center">
  <img src="https://github.com/mcombeau/mcombeau/blob/main/42_badges/minishelln.png" alt="Minishell 42 project badge"/>
</p>

Minishell is a 42 school team project to create a basic shell program in C.

## Status

Work in progress.

## Usage

Clone the repository with the [minitester](https://github.com/mcombeau/minitester-minishell-tester) submodule:
```
git clone --recurse-submodules git@github.com:mcombeau/minishell.git
```

To compile:

```shell
cd minishell && make
```

To run the program:

```shell
./minishell
```

A prompt will appear. You may enter your commands to be executed.

To run the included tester:
```shell
cd minitester/ && bash minitester.sh
```

## Supported features

Minishell is a miniature shell program based on Bash. Minishell supports:
* Prompt display
* Command history (up and down arrows)
* System executables available from the environment (`ls`, `cat`, `grep`, etc.)
* Local executables (`./minishell`)
* Builtin commands :
  * `echo` (and option `-n`)
  * `cd` (with only a relative or absolute path)
  * `pwd` (no options)
  * `export` (no options)
  * `unset` (no options)
  * `env` (no options or arguments)
  * `exit` (with exit number but no other options) 
* Pipes `|` which redirect output from one command to input for the next
* Redirections:
  * `>` redirects output
  * `>>` redirects output in append mode
  * `<` redirects input
  * `<< DELIMITER` displays a new prompt, reads user input until reaching `DELIMITER`, redirects user input to command input (does not update history)
* Environment variables (i.e. `$USER` or `$VAR`) that expand to their values.
  * `$?` expands to the exit status of the most recently executed foreground pipeline.
* User keyboard signals:
  * `ctrl-c` displays a new prompt line.
  * `ctrl-d` exits minishell
  * `ctrl-\` does nothing

However, Minishell does not support `\`, `;`, `&&`, `||`, or wildcards.

---
Made by aquesada and mcombeau
