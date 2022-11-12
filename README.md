# minishell

<p align="center">
  <img src="https://github.com/mcombeau/mcombeau/blob/main/42_badges/minishelle.png" alt="Minishell 42 project badge"/>
</p>

Minishell is a 42 school team project to create a basic shell program in C. It implements redirections and pipes, as well as environment variable expansions and the `cd`, `echo`, `env`, `exit`, `export`, `pwd` and `unset` builtin commands.

## Status

Validated 11/11/2022. Grade: 99%.

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

## Supported Features

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
### Useful Resources for the Minishell Project

:us: Articles in English about the concepts tackled in this project: 

* [Creating and Killing Child Processes in C](https://www.codequoi.com/en/creating-and-killing-child-processes-in-c/)
* [Pipe: an Inter-Process Communication Method](https://www.codequoi.com/en/pipe-an-inter-process-communication-method/)
* [Sending and Intercepting a Signal in C](https://www.codequoi.com/en/sending-and-intercepting-a-signal-in-c/)
* [Handling a File by its Descriptor in C](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)
* [Errno and Error Management in C](https://www.codequoi.com/en/errno-and-error-management-in-c/)

:fr: Articles en français sur les concepts abordés dans ce projet :

* [Créer et tuer des processus fils en C](https://www.codequoi.com/creer-et-tuer-des-processus-fils-en-c/)
* [Pipe : une méthode de communication inter-processus](https://www.codequoi.com/pipe-une-methode-de-communication-inter-processus/)
* [Envoyer et intercepter un signal en C](https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/)
* [Manipuler un fichier à l’aide de son descripteur en C](https://www.codequoi.com/manipuler-un-fichier-a-laide-de-son-descripteur-en-c/)
* [Errno et la gestion d’erreur en C](https://www.codequoi.com/errno-et-la-gestion-derreur-en-c/)

Other useful links:

* [Bash reference manual](https://www.gnu.org/software/bash/manual/bash.html)
* Introduction to Systems Programming: a Hands-on Approach, [Chapter 5. Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
* [Stephen Brennan's Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
* The Open Group Base Specifications, [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
* [A Guide to Unix Shell Quoting](https://rg1-teaching.mpi-inf.mpg.de/unixffb-ss98/quoting-guide.html)
* [Austin Tripp's Quick Tutorial on Bash Quotes](https://www.austintripp.ca/blog/2019/07/18/bash-quotes)

---
Made by aquesada and mcombeau
