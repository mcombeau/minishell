# Authorized Functions

## Readline and History

* ```readline```: Displays a prompt and waits for input. Mallocs and returns the inputted line. - [man readline(3)](https://man7.org/linux/man-pages/man3/readline.3.html)
* ```add_history```: Saves a line in a history list of lines.
* ```rl_clear_history```: Clear the history list by deleting all of the entries
* ```rl_on_new_line```: Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
* ```rl_replace_line```: Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
* ```rl_redisplay```: Change what's displayed on the screen to reflect the current contents of rl_line_buffer.

Examples and documentation at [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/readline.html#SEC24).

## Basic Functions & System Calls

* ```printf```: Prints a formatted string to standard output - [man printf(3)](https://man7.org/linux/man-pages/man3/printf.3.html)
* ```write```: Writes characters to a file descriptor - [man write(2)](https://man7.org/linux/man-pages/man2/write.2.html)
* ```malloc```: Allocates memory on the heap - [man malloc(3)]()
* ```free```: Frees previously allocated memory - [man free(3)]()

## File Manipulation

* ```access```: Checks user's permissions for a file - [man access(2)](https://man7.org/linux/man-pages/man2/access.2.html)
* ```open```: Opens and possibly creates a file - [man open(2)](https://man7.org/linux/man-pages/man2/open.2.html)
* ```read```: Reads from a file descriptor - [man read(2)](https://man7.org/linux/man-pages/man2/read.2.html)
* ```close```: Closes a file descriptor - [man close(2)](https://man7.org/linux/man-pages/man2/close.2.html)
* ```dup```: Duplicates a file descriptor - [man dup(2)](https://man7.org/linux/man-pages/man2/dup.2.html)
* ```dup2```: Duplicates a file descriptor to a specific file descriptor - [man dup(2)](https://man7.org/linux/man-pages/man2/dup.2.html)
* ```unlink```: Deletes a name from the filesystem, and possibly the file it refers to - [man unlink(2)](https://man7.org/linux/man-pages/man2/unlink.2.html)
* ```stat```: Gets file status - [man stat(2)](https://man7.org/linux/man-pages/man2/lstat.2.html)
* ```lstat```: Gets file status, if file is symbolic link, get symbiloc link status - [man stat(2)](https://man7.org/linux/man-pages/man2/lstat.2.html)
* ```fstat```: Gets file status by file descriptor rather than pathname - [man stat(2)](https://man7.org/linux/man-pages/man2/lstat.2.html)

## TTY

TTY means "TeleTYpewriter", meaning the terminal. (See [TTY: The Definition and Its Uses](https://linuxhint.com/what-does-tty-stand-for/).)
* ```isatty```: Tests whether a file descriptor refers to a terminal - [man isatty(3)](https://man7.org/linux/man-pages/man3/isatty.3.html)
* ```ttyname```: Returns the name of a terminal - [man ttyname(3)](https://www.man7.org/linux/man-pages/man3/ttyname.3.html)
* ```ttyslot```: Finds the slot of the current user's terminal in some file - [man ttyslot(3)](https://www.man7.org/linux/man-pages/man3/ttyslot.3.html)

## Directories

* ```getcwd```: Gets the current working directory - [man getcwd(3)](https://www.man7.org/linux/man-pages/man3/getcwd.3.html)
* ```chdir```: Changes the working directory - [man chdir(2)](https://man7.org/linux/man-pages/man2/chdir.2.html)
* ```opendir```: Opens a directory - [man opendir(3)](https://man7.org/linux/man-pages/man3/opendir.3.html)
* ```readdir```: Reads a directory - [man readdir(3)](https://man7.org/linux/man-pages/man3/readdir.3.html)
* ```closedir```: Closes a directory - [man closedir(3)](https://man7.org/linux/man-pages/man3/closedir.3.html)

## Processes

* ```execve```: Executes a program, replaces calling process - [man execve(2)](https://man7.org/linux/man-pages/man2/execve.2.html)
* ```fork```: Creates a child process - [man fork(2)](https://man7.org/linux/man-pages/man2/fork.2.html)
* ```wait```: Waits for the first process to change states - [man wait(2)](https://man7.org/linux/man-pages/man2/wait.2.html)
* ```waitpid```: Waits for a specific process to change states - [man wait(2)](https://man7.org/linux/man-pages/man2/wait.2.html)
* ```wait3```:  The wait3() and wait4() system calls are similar to waitpid(2), but additionally return resource usage information about the child in the structure pointed to by rusage. - [man wait4(2)](https://man7.org/linux/man-pages/man2/wait3.2.html)
* ```wait4```:  See wait3.
* ```pipe```: Creates a pipe - [man pipe(2)](https://man7.org/linux/man-pages/man2/pipe.2.html)

### Signals

* ```signal```
* ```sigaction```
* ```sigemptyset```
* ```sigaddset```
* ```kill```
* ```exit```

## Error Handling

* ```strerror```
* ```perror```

## To Research

* ```ioctl```
* ```getenv```
* ```tcsetattr```
* ```tcgetattr```
* ```tgetent```
* ```tgetflag```
* ```tgetnum```
* ```tgetstr```
* ```tgoto```
* ```tputs```


# Useful resources

#### To get started :

* https://brennan.io/2015/01/16/write-a-shell-in-c/

* https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

#### To get familiar with bash :

* Bash reference manual :
https://www.gnu.org/software/bash/manual/bash.html
    
* Shell command language :
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html

* Management of multiple layers of quotes :
https://www.austintripp.ca/blog/2019/07/18/bash-quotes

    https://rg1-teaching.mpi-inf.mpg.de/unixffb-ss98/quoting-guide.html



