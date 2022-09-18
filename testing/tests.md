# Minishell Tests

This is a master table of tests for the 42 project Minishell. Minishell output should be compared to Bash behavior.

Leading and trailling spaces in the output are denoted with the `█` character.

## CD

| Status| Test						| Bash								| Minishell					|
|-------|---------------------------|-----------------------------------|---------------------------|
| OK	|`cd ../../../../../..`		|`pwd` shows `/`					|`pwd` shows `/`			|
| OK	|`cd /home/user/`			|`pwd` shows `/home/user`			|`pwd` shows `/home/user`	|
| OK	|`cd $HOME`					|`pwd` shows `/home/user`			|`pwd` shows `/home/user`	|
| OK	|`cd $HOME/Documents`      	|`pwd` shows `/home/user/Documents`	|No such directory			|
| OK	|`unset HOME`, then `cd` 	|HOME not set + exit 1				|HOME not set				|
| ERROR	|`export HOME=` then `cd`	|No error msg, + exit 0				|No such directory			|
| OK	|`cd /t /w`					|Too many arguments + exit 1		|Too many arguments			|
| OK	|`cd ./fakepath`			|No such directory + exit 1			|No such directory			|
| OK	|`cd -`						|Return to OLDPWD, print CWD		|Return to OLDPWD, print CWD|
| ERROR	|`mkdir a`; `mkdir a/b`; `cd a/b`; `rm -r ../../a`; `cd ..`	|Error msg but still go back a directory, update PWD and OLDPWD, exit 0 | |

## ECHO

| Status| Test						| Bash				| Minishell			|
|-------|---------------------------|-------------------|-------------------|
| OK	|`echo -n -n -nnnn -nnnnm`	|`-nnnnm`           |`-nnnnm`			|
| OK	|`echo a	-nnnnma`		|`a -nnnnma`		|`a -nnnnma`		|
| OK	|`echo -n -nnn hello -n`	|`hello -n`			|`hello -n`			|
| OK	|`echo a	hello -na`		|`a hello -na`		|`a hello -na`		|

## EXPORT

| Status| Test						| Bash								| Minishell							|
|-------|---------------------------|-----------------------------------|-----------------------------------|
| OK	|`export ""`				|Not a valid identifier				|Not a valid identifier				|
| OK	|`export 42`				|Not a valid identifier				|Not a valid identifier				|
| OK	|`export =`					|Not a valid identifier				|Not a valid identifier				|
| OK	|`export hello`				|`env \| grep hello` shows nothing	|`env \| grep hello` shows nothing	|
| OK	|`export var=foo`			|`env \| grep var=` shows var		|`env \| grep var=` shows var		|
| OK	|`export $var=test`			|`env \| grep foo=` shows `foo=test`|`env \| grep foo=` shows `foo=test`|
| OK	|`echo $var $foo`			|`foo test`							|`foo test`							|

## UNSET

On some tests, ? because Bash used to write error messages for unset, but no longer does.

| Status| Test							| Bash							| Minishell						|
|-------|-------------------------------|-------------------------------|-------------------------------|
| OK	|`unset PATH`					|`echo $PATH` shows `(newline)`	|`echo $PATH` shows `(newline)`	|
| OK	|`ls` (after `unset PATH`)		|No such file or directory		|No such file or directory		|
| ?		|`unset "" test`				|?								|Not a valid identifier			|
| ?		|`unset =`						|?								|Not a valid identifier			|
| OK	|`unset FAKEVAR`				|Does nothing					|Does nothing					|
| OK	|`export var1=test`				|`env \| grep var` shows var1	|`env \| grep var` shows var1	|
| OK	|`unset var` (following `var1`)	|Does not delete `var1`			|Does not delete `var1`			|

## ENV

| Status| Test										| Bash				| Minishell			|
|-------|-------------------------------------------|-------------------|-------------------|
| OK	|`env` then `export d=3 a=12 c=0` then `env`|					|Vars not sorted	|

## EXIT

| Status| Test										| Bash									| Minishell								|
|-------|-------------------------------------------|---------------------------------------|---------------------------------------|
| OK	|`ls \| exit`								|Does nothing (does not exit shell)		|Does nothing (does not exit shell)		|
| OK	|`sleep 5 \| exit`							|Sleeps 5 seconds (does not exit shell)	|Sleeps 5 seconds (does not exit shell)	|
| OK	|`ls -l \| exit \| wc -l`					|`0` (does not exit shell)				|`0` (does not exit shell)				|
| OK	|`exit \| ls`								|`ls` output (does not exit shell)		|`ls` output (does not exit shell)		|

## Pipe tests

| Status| Test										| Bash									| Minishell								|
|-------|-------------------------------------------|---------------------------------------|---------------------------------------|
| OK	|`cat \| cat \| cat \| ls`					|`ls` output then hangs, `enter` 3 times|Same as bash							|
| OK	|`cat Makefile \| grep a \| wc -l \| cd x`	|No such file or directory				|No such file or directory				|
| OK	|`cat Makefile \| grep a \| wc -l \| x`		|command not found						|command not found						|
| OK	|`echo test \|cat`							|`test`									|`test`									|
| OK	|`echo test \|\|\| cat`						|syntax error							|syntax error							|
| OK	|`export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8`	|`env` shows vars						|`env` shows vars						|
| OK	|`echo "$A'$B"'$C"$D'$E'"$F"'"'$G'$H"`		|`1'2$C"$D5"$F"'7'8`					|`1'2$C"$D5"$F"'7'8`					|
## Variable Expansion Tests

| Status| Test					| Bash				| Minishell			|
|-------|-----------------------|-------------------|-------------------|
| OK	|`echo $USER`			|`username`			|`username`			|
| OK	|`echo $`				|`$`				|`$`				|
| OK	|`echo $""`				|`(newline)`		|`(newline)`		|
| ERROR?|`echo $$$USER`			|`26153username`	|`$$username`		|
| ERROR?|`echo $$USER`			|`26153USER`		|`$username`		|
| OK	|`echo $USER$USER`		|`usernameusername`	|`usernameusername`	|
| OK	|`echo $USER""$USER`	|`usernameusername`	|`usernameusername`	|
| OK	|`echo $USER" "$USER`	|`username username`|`username username`|
| OK	|`echo test$1test`		|`testtest`			|`testtest`			|
| OK	|`echo test$FAKE_VAR`	|`test`				|`test`				|
| OK	|`echo "$USER>>"`		|`username>>`		|`username>>`		|
| OK	|`echo "$USER11111ffjf"`|`(newline)`		|`(newline)`		|
| ERROR |`echo $\"echo`			|`"echo`			|syntax error		|
| ERROR |`echo "test$<test"`	|`test$<test`		|`test<test`		|
| ERROR |`echo test$<test`		|test: no such file	|`test$`			|
| ERROR	|`echo "test$-r"`		|`testhimBHsr`		|`test-r`			|
| ERROR |`echo "test$-?"`		|`testhimBHs?`		|`test-?`			|
| ERROR	|`echo $-1$USER`		|`himBHs1username`	|`-1username`		|
| OK	|`echo $1`				|`(newline)`		|`(newline)`		|
| OK	|`echo "$1"`			|`(newline)`		|`(newline)`		|
| OK	|`echo $"USER"`			|`USER`				|`USER`				|
| OK	|`echo $'USER'`			|`USER`				|`USER`				|
| ERROR	|`echo $NULL test`		|`test`				|`█test`			|
| OK	|`echo hello$USER`		|`hellousername`	|`hellousername`	|
| OK	|`echo hello$USERtest`	|`hello`			|`hello`			|
| OK	|`echo $USER.test`		|`username.test`	|`username.test`	|

## Quote Handling Tests

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
| ERROR	|`echo $:$= \| cat -e`	|`$:$=$`			|`:$=$`				|
| OK	|`export FOO=' " '`		|`env` shows `FOO`	|`env` shows `FOO` 	|
| ERROR	|`echo "$FOO" \| cat -e`|`█" $`				|`██$`				|
| OK	|`echo "\x"`			|`\x`				|`\x`				|
| ERROR?|`echo "\\x"`			|`\x`				|`\\x`				|
| ERROR?|`echo "\\\x"`			|`\\x`				|`\\\x`				|

## Heredoc Tests
| Status| Test								| Bash							| Minishell						|
|-------|-----------------------------------|-------------------------------|-------------------------------|
| OK	|`<< END cat`; `$USER$USER`; `END`	|`usernameusername`				|`usernameusername`				|
| OK	|`<< END cat`; `$USER'$USER'`; `END`|`username'username'`			|`username'username'`			|
| OK	|`<< END cat`; `$USER"$USER"`; `END`|`username"username"`			|`username"username"`			|
| OK	|`<< END cat`; `helloEND`			|Heredoc keeps waiting for input|Heredoc keeps waiting for input|
| OK	|`<< END cat`; `ENDhello`			|Heredoc keeps waiting for input|Heredoc keeps waiting for input|
| OK	|`<< END cat`; `helloENDhello`		|Heredoc keeps waiting for input|Heredoc keeps waiting for input|
| ERROR |`< Makefile cat \| << END cat`		|Heredoc + cat execute			|syntax error					|

## Redirection Tests

| Status| Test					| Bash													| Minishell										|
|-------|-----------------------|-------------------------------------------------------|-----------------------------------------------|
| OK	|`< hello`				|hello: no such file or directory						|hello: no such file or directory				|
| OK	|`cat <t`				|t: no such file or directory							|t: no such file or directory					|
| OK	|`> x`					|`x` file created empty									|`x` file created empty							|
| OK	|`< Ma < Makefile cat`	|Ma: no such file or directory (no cat output)			|Ma: no such file or directory (no cat output)	|
| OK	|`echo "File A" > a`	|Create file `a` with contents `File A`					|Create file `a` with contents `File A`			|
| OK	|`echo "File B" >> b`	|Create file `b` with contents `File B`					|Create file `b` with contents `File B`			|
| OK	|`echo File C >c`		|Create file `c` with contents `File C`					|Create file `c` with contents `File C`			|
| OK	|`<a cat <b <c`			|`cat` shows contents of file `c` only					|`cat` shows contents of file `c` only			|
| OK	|`chmod 000 b`			|Remove rights to `b` file								|Remove rights to `b` file						|
| OK	|`<a cat <b <c`			|`b: Permission denied`, does not show `c`				|`b: Permission denied`, does not show `c`		|
| OK	|`chmod 644 b`; `rm a`	|Restore rights to `b` file, delete `a`					|Restore rights to `b` file, delete `a`			|
| OK	|`>a cat <b >>c`		|Create empty `a`, `c` gets contents of `b`				|Create empty `a`, `c` gets contents of `b`		|
| OK	|`rm a b c`				|Delete `a`, `b` and `c` files							|Delete `a`, `b` and `c` files					|
| OK	|`>a ls >b >>c >d`		|`a`, `b`, `c`, `d` created, `ls` ouput only in `d`		|`a`, `b`, `c`, `d` created, `ls` ouput only in `d`|
| OK	|`>a ls <e >>b >c`		|`e`: no such file; `a` created `b` and `c` not created	|`e`: no such file; `a` created `b` and `c` not created|
| OK	|`cat -e >t1 <t2`		|`t2`: no such file; `t1` created						|`t2`: no such file; `t1` created				|
| OK	|`echo 2 >o1 >>o2`		|`2` written to `o2`, `o1` empty						|`2` written to `o2`, `o1` empty				|
| OK	|`echo 42 >o2 >>o1`		|`o1` and `o2` contain the same thing					|`o1` and `o2` contain the same thing			|
| CRASH	|`echo hello > k\ 1`	|Creates file "`k 1`"									|CRASH in parsing!!								|
| CRASH	|`echo test >f test1`	|Creates file `f` with contents `test test1`			|CRASH in parsing!!								|
| OK	|`fakecmd hello > z`	|Command not found, file `z` created					|Command not found, file `z` created			|

## Signal Tests
## Other Syntax Error Tests
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

---
Thanks to okushnir for help with tests.
