# Minishell Tests

This is a master table of tests for the 42 project Minishell. Minishell output should be compared to Bash behavior. "Expected" column shows Bash output, "Output" column shows our Minishell output.

Leading and trailling spaces in the output are denoted with the `█` character.

## Parsing Tests


### Variable expansion

| Status| Test					| Bash				| Minishell			|
|-------|-----------------------|-------------------|-------------------|
| OK	|`echo $USER`			|`username`			|`username`			|
| OK	|`echo $`				|`$`				|`$`				|
| OK	|`echo $""`				|`(newline)`		|`(newline)`		|
| ERROR |`echo $$$USER`			|`26153username`	|`$$username`		|
| ERROR	|`echo $$USER`			|`26153USER`		|`$username`		|
| OK	|`echo $USER$USER`		|`usernameusername`	|`usernameusername`	|
| OK	|`echo $USER""$USER`	|`usernameusername`	|`usernameusername`	|
| OK	|`echo $USER" "$USER`	|`username username`|`username username`|
| OK	|`echo test$1test`		|`testtest`			|`testtest`			|
| OK	|`echo test$FAKE_VAR`	|`test`				|`test`				|
| ERROR	|`echo "$USER>>"`		|`username>>`		|`(newline)`		|
| OK	|`echo "$USER11111ffjf"`|`(newline)`		|`(newline)`		|
| ERROR |`echo $\"echo`			|`"echo`			|syntax error		|
| ERROR |`echo "test$<test"`	|`test$<test`		|`test`				|
| ERROR |`echo test$<test`		|test: no such file	|`test$`			|
| ERROR	|`echo "test$-r"`		|`testhimBHsr`		|`test`				|
| ERROR |`echo "test$-?"`		|`testhimBHs?`		|`test`				|
| ERROR	|`echo $-1$USER`		|`himBHs1username`	|`username`			|
| OK	|`echo $1`				|`(newline)`		|`(newline)`		|
| OK	|`echo "$1"`			|`(newline)`		|`(newline)`		|
| OK	|`echo $"USER"`			|`USER`				|`USER`				|
| OK	|`echo $'USER'`			|`USER`				|`USER`				|
| ERROR	|`echo $NULL test`		|`test`				|`█test`			|


### Quote handling

| Status| Test					| Bash				| Minishell			|
|-------|-----------------------|-------------------|-------------------|
| OK    |`ec""ho test`			|`test` 			|`test` 			|
| OK	|`""echo test`			|`test`				|`test`				|
| OK	|`echo"" test`			|`test`				|`test`				|
| OK	|`echo "" test`			|`█test`			|`█test`			|
| OK	|`echo $USE""R`			|`R`				|`R`				|
| OK	|`echo ""$USER`			|`username`			|`username`			|
| OK	|`echo "$"USER`			|`$USER`			|`$USER`			|
| OK	|`echo  $""USER`		|`USER`				|`USER`				|
| OK	|`ec''ho test`			|`test`				|`test`				|
| OK	|`''echo test`			|`test`				|`test`				|
| OK	|`echo'' test`			|`test`				|`test`				|
| OK	|`echo '' test`			|`█test`			|`█test`			|
| OK	|`echo $USE''R`			|`R`				|`R`				|
| OK	|`echo ''$USER`			|`username`			|`username`			|
| OK	|`echo '$'USER`			|`$USER`			|`$USER`			|
| OK	|`echo  $''USER`		|`USER`				|`USER`				|
| OK	|`echo "" "" "" test`	|`███test`			|`███test`			|
| OK	|`echo """""" test`		|`█test`			|`█test`			|
| OK	|`echo $USER"" ''`		|`username`			|`username`			|
| OK	|`ls ""`				|cannot acces ''	|cannot access ''	|
| OK	|`ls '"`				|syntax error msg	|syntax error msg	|
| OK	|`ls "'`				|syntax error msg	|syntax error msg	|
| OK	|`ls " "`				|cannot access ' '	|cannot access ' '	|
| OK	|`ls " ' "`				|cannot access " ' "|cannot access " ' "|
| OK	|`"ls"`					|normal `ls` output	|normal `ls` output	|
| OK	|`l"s"`					|normal `ls`output	|normal `ls` output	|
| OK	|`ls"" -la`				|normal output		|normal output		|
| OK	|`ls "" -la`			|cannot access ''	|cannot access ''	|
| OK	|`ls """"-la`			|normal output		|normal output		|
| OK	|`ls ""-la`				|normal output		|normal output		|
| OK	|`echo test""test`		|`testtest`			|`testtest`			|
| OK	|`echo test"" test`		|`test test`		|`test test`		|
| OK	|`echo test ""test`		|`test test`		|`test test`		|
| OK	|`echo test "'"test`	|`test 'test`		|`test test`		|
| OK	|`echo "\|" ls`			|`\| ls`			|`\| ls`			|
| OK	|`echo '"abc"'`			|`"abc"`			|`"abc"`			|
| Ok	|`echo '  "abc" '`		|`██"abc"█`			|`██"abc"█`			|
| OK	|`echo "'abc'"`			|`'abc'`			|`'abc'`			|
| OK	|`echo " $ " \| cat -e`	|`█$ $`				|`█$ $`				|
| ERROR	|`echo $:$= \| cat -e`	|`$:$=$`			|`$=$`				|
| OK	|`export FOO=' " '`		|`env` shows `FOO`	|`env` shows `FOO` 	|
| ERROR	|`echo "$FOO" \| cat -e`|`█" $`				|`██$`				|
| OK	|`echo "\x"`			|`\x`				|`\x`				|
| ERROR	|`echo "\\x"`			|`\x`				|`\\x`				|
| ERROR	|`echo "\\\x"`			|`\\x`				|`\\\x`				|

### Pipe tests

| Status| Test										| Bash				| Minishell			|
|-------|-------------------------------------------|-------------------|-------------------|
| OK	|`echo test \|cat`							|`test`				|`test`				|
| OK	|`echo test \|\|\| cat`						|syntax error		|syntax error		|
| OK	|`export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8`	|`env` shows vars	|`env` shows vars	|
| OK	|`echo "$A'$B"'$C"$D'$E'"$F"'"'$G'$H"`		|`1'2$C"$D5"$F"'7'8`|`1'2$C"$D5"$F"'7'8`|

### Other Syntax errors
| Status| Test					| Bash					| Minishell				|
|-------|-----------------------|-----------------------|-----------------------|
| OK	|`\|`					|syntax error			|syntax error			|
| OK	|`echo test ; \|`		|syntax error			|syntax error			|
| OK	|`echo test > > out`	|syntax error			|syntax error			|
| ERROR?|`echo hello > $fakevar`|ambiguous redirect		|no such file or dir	|
| ERROR	|`echo hello > $realvar`|write to var file		|no such file or dir	|
| OK	|`echo hello >>> test`	|syntax error			|syntax error			|
| OK	|`echo hello \| \|`		|syntax error			|syntax error			|
| ERROR |`echo hello \|;`		|syntax error			|command not found		|
| ERROR	|`echo\ a`				|`echo a` cmd not found	|`echo\` cmd not found	|


## Execution Tests

### Pipe Tests



### Redirection Tests



### Signal Tests



### CD

| Status| Test						| Bash								| Minishell					|
|-------|---------------------------|-----------------------------------|---------------------------|
| OK	|`cd ../../../../../..`		|`pwd` shows `/`					|`pwd` shows `/`			|
| OK	|`cd /home/user/`			|`pwd` shows `/home/user`			|`pwd` shows `/home/user`	|
| OK	|`cd $HOME`					|`pwd` shows `/home/user`			|`pwd` shows `/home/user`	|
| ERROR	|`cd $HOME/Documents`      	|`pwd` shows `/home/user/Documents`	|No such directory			|
| OK	|`unset HOME`, then `cd` 	|HOME not set + exit 1				|HOME not set				|
| ERROR	|`export HOME=` then `cd`	|No error msg, + exit 0				|No such directory			|
| OK	|`cd /t /w`					|Too many arguments + exit 1		|Too many arguments			|
| OK	|`cd ./fakepath`			|No such directory + exit 1			|No such directory			|
| OK	|`cd -`						|Return to OLDPWD, print CWD		|Return to OLDPWD, print CWD|
| ERROR	|`mkdir a`; `mkdir a/b`; `cd a/b`; `rm -r ../../a`; `cd ..`	|Error msg but still go back a directory, update PWD and OLDPWD, exit 0 | |

### ECHO

| Status| Test						| Bash				| Minishell			|
|-------|---------------------------|-------------------|-------------------|
| OK	|`echo -n -n -nnnn -nnnnm`	|`-nnnnm`           |`-nnnnm`			|
| OK	|`echo a	-nnnnma`		|`a -nnnnma`		|`a -nnnnma`		|
| OK	|`echo -n -nnn hello -n`	|`hello -n`			|`hello -n`			|
| OK	|`echo a	hello -na`		|`a hello -na`		|`a hello -na`		|



### EXPORT


| Status| Test						| Bash								| Minishell							|
|-------|---------------------------|-----------------------------------|-----------------------------------|
| OK	|`export ""`				|Not a valid identifier				|Not a valid identifier				|
| OK	|`export 42`				|Not a valid identifier				|Not a valid identifier				|
| OK	|`export =`					|Not a valid identifier				|Not a valid identifier				|
| OK	|`export hello`				|`env \| grep hello` shows nothing	|`env \| grep hello` shows nothing	|
| OK	|`export var=foo`			|`env \| grep var=` shows var		|`env \| grep var=` shows var		|
| OK	|`export $var=test`			|`env \| grep foo=` shows `foo=test`|`env \| grep foo=` shows `foo=test`|
| OK	|`echo $var $foo`			|`foo test`							|`foo test`							|

### UNSET

On some tests, ? because Bash used to write error messages for unset, but no longer does.

| Status| Test						| Bash								| Minishell							|
|-------|---------------------------|-----------------------------------|-----------------------------------|
| OK	|`unset PATH`				|`echo $PATH` shows `(newline)`		|`echo $PATH` shows `(newline)`		|
| OK	|`ls` (after `unset PATH`)	|No such file or directory			|No such file or directory			|
| ?		|`unset "" test`			|?									|Not a valid identifier				|
| ?		|`unset =`					|?									|Not a valid identifier				|
| OK	|`unset FAKEVAR`			|Does nothing						|Does nothing						|
| OK	|`export var1=test`			|`env \| grep var` shows var1		|`env \| grep var` shows var1		|
| OK	|`unset var` (following `var1`)|Does not delete `var1`			|Does not delete `var1`				|

### ENV

| Status| Test						| Bash				| Minishell			|
|-------|---------------------------|-------------------|-------------------|
| OK	|`env` then `export d=3 a=12 c=0` then `env`||Vars not sorted		|




---
Thanks to okushnir for help with tests.