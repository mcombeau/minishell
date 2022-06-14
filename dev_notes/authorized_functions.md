# Authorized Functions

## Readline and History

* ```readline```: Displays a prompt and waits for input. Mallocs and returns the inputted line.
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
* ```isatty```: Tests whether a file descriptor refers to a terminal
* ```ttyname```: Returns the name of a terminal
* ```ttyslot```: Finds the slot of the current user's terminal in some file

## Directories

* ```getcwd```
* ```chdir```
* ```opendir```
* ```readdir```
* ```closedir```

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
