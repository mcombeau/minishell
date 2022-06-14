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

* ```printf```
* ```malloc```
* ```free```
* ```write```

## File Manipulation

* ```access```
* ```open```
* ```read```
* ```close```
* ```dup```
* ```dup2```
* ```unlink```

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

* ```execve```
* ```fork```
* ```wait```
* ```waitpid```
* ```wait3```
* ```wait4```
* ```pipe```

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

* ```stat```
* ```lstat```
* ```fstat```
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
