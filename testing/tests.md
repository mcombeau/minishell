# Minishell Tests

This is a master table of tests for the 42 project Minishell. Minishell output should be compared to Bash behavior.

Status represents our Minishell project's execution results for each test:
* OK: the output is identical to Bash
* ERROR: the output differs from Bash when it should not. Must be fixed.
* DIFF: the output differs from Bash, but the result is acceptable (since Minishell does not implement all of the same functionality as Bash, for example, `\` and `;` do not exist in Minishell)
* CRASH: Minishell crashes. Must absolutely be fixed.
 

## Execution Tests

| Status| Test						| Bash						| Minishell					| Exit Code |
|-------|---------------------------|---------------------------|---------------------------|-----------|
| OK	|`ls`						|`ls` output				|`ls` output				| OK [0]	|
| OK	|`/usr/bin/ls`				|`ls` output				|`ls` output				| OK [0]	|
| OK	|`usr/bin/ls`				|no such file or dir		|no such file or dir		| OK [127]	|
| OK	|`./ls`						|no such file or dir		|no such file or dir		| OK [127]	|
| OK	|`hello`					|command not found			|command not found			| OK [127]	|
| OK	|`/usr/bin/hello`			|no such file or dir		|no such file or dir		| OK [127]	|
| OK	|`./hello`					|no such file or dir		|no such file or dir		| OK [127]	|
| OK	|`""`						|command not found			|command not found			| OK [127]	|
| DIFF	|`.`						|filename arg required		|command not found			| OK [127]	|
| OK	|`..`						|command not found			|command not found			| OK [127]	|
| OK	|`./`						|is a directory				|is a directory				| OK [126]	|
| OK	|`../`						|is a directory				|is a directory				| OK [126]	|
| OK	|`../existing_dir`			|is a directory				|is a directory				| OK [126]	|
| OK	|`../fake_dir`				|no such file or dir		|no such file or dir		| OK [127]	|
| OK	|`./Makefile`				|permission denied			|permission denied			| OK [126]	|
| OK	|`./does_not_exist`			|no such file or dir		|no such file or dir		| OK [127]	|
| OK	|`./minishell`				|executes new minishell		|executes new minishell		| OK [0]	|
| OK	|`minishell`				|command not found			|command not found			| OK [127]	|
| OK	|`.minishell`				|command not found			|command not found			| OK [127]	|

## CD

| Status| Test						| Bash								| Minishell					| Exit Code |
|-------|---------------------------|-----------------------------------|---------------------------|-----------|
| OK	|`cd ../../../../../..`		|`pwd` shows `/`					|`pwd` shows `/`			| OK [0]	|
| OK	|`cd /home/user/`			|`pwd` shows `/home/user`			|`pwd` shows `/home/user`	| OK [0]	|
| OK	|`cd $HOME`					|`pwd` shows `/home/user`			|`pwd` shows `/home/user`	| OK [0]	|
| OK	|`cd $HOME/Documents`      	|`pwd` shows `/home/user/Documents`	|No such directory			| OK [0]	|
| OK	|`unset HOME`, then `cd` 	|HOME not set						|HOME not set				| OK [1]	|
| OK	|`export HOME=` then `cd`	|No error msg						|No error msg				| OK [0]	|
| OK	|`cd /t /w`					|Too many arguments					|Too many arguments			| OK [1]	|
| OK	|`cd ./fakepath`			|No such directory					|No such directory			| OK [1]	|
| OK	|`cd -`						|Return to OLDPWD, print CWD		|Return to OLDPWD, print CWD| OK [0]	|
| OK	|`unset OLDPWD`; `cd -`		|OLDPWD not set;					|OLDPWD not set				| OK [1]	|
| ERROR	|`mkdir a`; `mkdir a/b`; `cd a/b`; `rm -r ../../a`; `cd ..`	|Error msg but still go back a directory, update PWD and OLDPWD, exit 0 | TODO | TODO |

## ECHO

| Status| Test						| Bash				| Minishell			| Exit Code |
|-------|---------------------------|-------------------|-------------------|-----------|
| OK	|`echo -n -n -nnnn -nnnnm`	|`-nnnnm`           |`-nnnnm`			| OK [0]	|
| OK	|`echo a	-nnnnma`		|`a -nnnnma`		|`a -nnnnma`		| OK [0]	|
| OK	|`echo -n -nnn hello -n`	|`hello -n`			|`hello -n`			| OK [0]	|
| OK	|`echo a	hello -na`		|`a hello -na`		|`a hello -na`		| OK [0]	|

## EXPORT

| Status| Test						| Bash								| Minishell							| Exit Code |
|-------|---------------------------|-----------------------------------|-----------------------------------|-----------|
| OK	|`export ""`				|Not a valid identifier				|Not a valid identifier				| OK [1]	|
| OK	|`export 42`				|Not a valid identifier				|Not a valid identifier				| OK [1]	|
| OK	|`export =`					|Not a valid identifier				|Not a valid identifier				| OK [1]	|
| OK	|`export hello`				|`env \| grep hello` shows nothing	|`env \| grep hello` shows nothing	| OK [0]	|
| OK	|`export var=foo`			|`env \| grep var=` shows var		|`env \| grep var=` shows var		| OK [0]	|
| OK	|`export $var=test`			|`env \| grep foo=` shows `foo=test`|`env \| grep foo=` shows `foo=test`| OK [0]	|
| OK	|`echo $var $foo`			|`foo test`							|`foo test`							| OK [0]	|

## UNSET

On some tests, Bash used to write error messages for unset, but no longer does. Considering the DIFF as acceptable in this case.

| Status| Test							| Bash							| Minishell						| Exit Code |
|-------|-------------------------------|-------------------------------|-------------------------------|-----------|
| OK	|`unset PATH`					|`echo $PATH` shows `(newline)`	|`echo $PATH` shows `(newline)`	| OK [0]	|
| OK	|`ls` (after `unset PATH`)		|No such file or directory		|No such file or directory		| OK [127]	|
| DIFF	|`unset "" test`				|Does nothing					|Not a valid identifier			| DIFF [bash:0][mini:1]|
| DIFF	|`unset =`						|Does nothing					|Not a valid identifier			| DIFF [bash:0][mini:1]|
| OK	|`unset FAKEVAR`				|Does nothing					|Does nothing					| OK [0]	|
| OK	|`export var1=test`				|`env \| grep var` shows var1	|`env \| grep var` shows var1	| OK [0]	|
| OK	|`unset var` (following `var1`)	|Does not delete `var1`			|Does not delete `var1`			| OK [0]	|

## ENV

| Status| Test										| Bash				| Minishell			| Exit Code |
|-------|-------------------------------------------|-------------------|-------------------|-----------|
| OK	|`env` then `export d=3 a=12 c=0` then `env`|					|Vars not sorted	| OK [0]	|

## EXIT

| Status| Test							| Bash											| Minishell								| Exit Code |
|-------|-------------------------------|-----------------------------------------------|---------------------------------------|-----------|
| OK	|`exit 10`						|exits shell									|exits shell							| OK [10]	|
| OK	|`exit -10`						|exits shell									|exits shell							| OK [246]	|
| OK	|`exit abc`						|exits shell; error numeric arg required		|exits shell; numeric arg required		| OK [2]	|
| OK	|`exit --10`					|exits shell; error numeric arg required		|exits shell; numeric arg required		| OK [2]	|
| OK	|`exit ++10`					|exits shell; error numeric arg requited		|exits shell; numeric arg required		| OK [2]	|
| OK	|`exit < Makefile`				|exits shell									|exits shell							| OK [0]	|
| OK	|`exit > test`					|exits shell; write exit to terminal, file empty|exits shell; write to term; file empty	| OK [0]	|
| OK	|`ls \| exit`					|Does nothing (does not exit shell)				|Does nothing (does not exit shell)		| ERR [bash:0][mini:141]	|
| OK	|`ls > file \| exit`			|`ls` output in `file` (does not exit shell)	|`ls` output in `file` (no exit shell)	| OK [0]	|
| OK	|`sleep 5 \| exit`				|Sleeps 5 seconds (does not exit shell)			|Sleeps 5 seconds (does not exit shell)	| OK [0]	|
| OK	|`ls -l > x \| exit \| wc -l`	|Output `0`; file `x` contains `ls` (no exit)	|Output `0`; file `x` has `ls` (no exit)| OK [0]	|
| OK	|`exit \| ls`					|`ls` output (does not exit shell)				|`ls` output (does not exit shell)		| OK [0]	|

## Pipe tests

| Status| Test										| Bash									| Minishell								| Exit Code |
|-------|-------------------------------------------|---------------------------------------|---------------------------------------|-----------|
| OK	|`cat \| cat \| cat \| ls`					|`ls` output then hangs, `enter` 3 times|Same as bash							| ERR [bash:0][mini:141]	|
| OK	|`cat Makefile \| grep a \| wc -l \| cd x`	|No such file or directory				|No such file or directory				| ERR [bash:0][mini:141]	|
| OK	|`cat Makefile \| grep a \| wc -l \| x`		|command not found						|command not found						| ERR [bash:0][mini:141]	|
| OK	|`echo test \|cat`							|`test`									|`test`									| OK [0]	|
| OK	|`echo test \|\|\| cat`						|syntax error							|syntax error							| OK [2]	|
| OK	|`export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8`	|`env` shows vars						|`env` shows vars						| OK [0]	|
| OK	|`echo "$A'$B"'$C"$D'$E'"$F"'"'$G'$H"`		|`1'2$C"$D5"$F"'7'8`					|`1'2$C"$D5"$F"'7'8`					| OK [0]	|
## Variable Expansion Tests

Leading and trailling spaces in the output are denoted with the `█` character.

| Status| Test					| Bash				| Minishell			|
|-------|-----------------------|-------------------|-------------------|
| OK	|`echo $USER`			|`username`			|`username`			|
| OK	|`echo $`				|`$`				|`$`				|
| OK	|`echo $""`				|`(newline)`		|`(newline)`		|
| DIFF	|`echo $$$USER`			|`26153username`	|`$$username`		|
| DIFF	|`echo $$USER`			|`26153USER`		|`$username`		|
| OK	|`echo $USER$USER`		|`usernameusername`	|`usernameusername`	|
| OK	|`echo $USER""$USER`	|`usernameusername`	|`usernameusername`	|
| OK	|`echo $USER" "$USER`	|`username username`|`username username`|
| OK	|`echo test$1test`		|`testtest`			|`testtest`			|
| OK	|`echo test$FAKE_VAR`	|`test`				|`test`				|
| OK	|`echo "$USER>>"`		|`username>>`		|`username>>`		|
| OK	|`echo "$USER11111ffjf"`|`(newline)`		|`(newline)`		|
| DIFF	|`echo $\"echo`			|`"echo`			|syntax error		|
| ERROR |`echo "test$<test"`	|`test$<test`		|`test<test`		|
| OK	|`echo test$<test`		|test: no such file	|test: no such file	|
| DIFF	|`echo "test$-r"`		|`testhimBHsr`		|`test-r`			|
| DIFF	|`echo "test$-?"`		|`testhimBHs?`		|`test-?`			|
| DIFF	|`echo $-1$USER`		|`himBHs1username`	|`-1username`		|
| OK	|`echo $1`				|`(newline)`		|`(newline)`		|
| OK	|`echo "$1"`			|`(newline)`		|`(newline)`		|
| OK	|`echo $"USER"`			|`USER`				|`USER`				|
| OK	|`echo $'USER'`			|`USER`				|`USER`				|
| ERROR	|`echo $NULL test`		|`test`				|`█test`			|
| OK	|`echo hello$USER`		|`hellousername`	|`hellousername`	|
| OK	|`echo hello$USERtest`	|`hello`			|`hello`			|
| OK	|`echo $USER.test`		|`username.test`	|`username.test`	|

## Quote Handling Tests

Leading and trailling spaces in the output are denoted with the `█` character.

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
| DIFF	|`echo "\\x"`			|`\x`				|`\\x`				|
| DIFF	|`echo "\\\x"`			|`\\x`				|`\\\x`				|

## Heredoc Tests
| Status| Test								| Bash							| Minishell						|
|-------|-----------------------------------|-------------------------------|-------------------------------|
| OK	|`<< END cat`; `$USER$USER`; `END`	|`usernameusername`				|`usernameusername`				|
| OK	|`<< END cat`; `$USER'$USER'`; `END`|`username'username'`			|`username'username'`			|
| OK	|`<< END cat`; `$USER"$USER"`; `END`|`username"username"`			|`username"username"`			|
| OK 	|`<< END cat`; `$USER $USER`; `END`	|`username username`			|`username username`			|
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
| OK	|`ls > p \| env > q`	|`p` contains `ls` output; `q` contains `env` output	|`p` contains `ls` out; `q` contains `env` out	|
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
| OK	|`echo 42 >o2 >>o1`		|`o1` contains `42`, `o2` empty							|`o1` contains `42`, `o2` empty					|
| CRASH	|`echo hello > k\ 1`	|Creates file "`k 1`"									|CRASH in parsing!!								|
| CRASH	|`echo test >f test1`	|Creates file `f` with contents `test test1`			|CRASH in parsing!!								|
| OK	|`fakecmd hello > z`	|Command not found, file `z` created					|Command not found, file `z` created			|


## Signal Tests

| Status| Test						| Bash								| Minishell							| Exit Code |
|-------|---------------------------|-----------------------------------|-----------------------------------|-----------|
| OK	|`ctrl+c`					|`^C` + new prompt on new line		|`^C` + new prompt on new line		| N/A		|
| OK	|`abc` + `ctrl + c`			|`abc^C` + new prompt				|`abc^C` + new prompt				| N/A		|
| OK	|`ctrl+d`					|print `exit` + exit shell			|print `exit` + exit shell			| OK [0]	|
| OK	|`abc` + `ctrl+d`			|does nothing						|does nothing						| N/A		|
| OK	|`ctrl+\`					|does nothing						|does nothing						| N/A		|
| OK	|`abc` + `ctrl+\`			|does nothing						|does nothing						| N/A		|
| OK	|`cat` + `enter` + `ctrl+c`	|interrupt cat; do not quit shell	|interrupt cat; do not quit shell	| OK [130]	|
| OK	|`cat` + `enter` + `ctrl+d`	|quit cat; do not quit shell		|quit cat; do not quit shell		| OK [0]	|
| OK	|`cat` + `enter` + `ctrl+\`	|quit cat; do not kill shell		|quit cat; do not quit shell		| OK [131]	|
## Other Syntax Error Tests
| Status| Test						| Bash					| Minishell				| Exit Code |
|-------|---------------------------|-----------------------|-----------------------|-----------|
| OK	|`\|`						|syntax error			|syntax error			| OK [2]	|
| OK	|`echo test ; \|`			|syntax error			|syntax error			| OK [2]	|
| OK	|`echo test > > out`		|syntax error			|syntax error			| OK [2]	|
| OK	|`echo hello > $fakevar`	|ambiguous redirect		|ambiguous redirect		| OK [1]	|
| OK	|`echo hello >> $fakevar`	|ambiguous redirect		|ambiguous redirect		| OK [1]	|
| OK	|`echo hello < $fakevar`	|ambiguous redirect		|ambiguous redirect		| OK [1]	|
| OK	|`cat < $fakevar`			|ambiguous redirect		|ambiguous redirect		| OK [1]	|
| OK	|`echo hello > $realvar`	|write to var file		|write to var file		| OK [0]	|
| OK	|`echo hello >> $realvar`	|append to var file		|append to var file		| OK [0]	|
| OK	|`< $realvar cat`			|read from var file		|read from var file		| OK [0]	|
| OK	|`echo hello >>> test`		|syntax error			|syntax error			| OK [2]	|
| OK	|`echo hello \| \|`			|syntax error			|syntax error			| OK [2]	|
| DIFF	|`echo hello \|;`			|syntax error			|command not found		| OK [127]	|
| DIFF	|`echo\ a`					|`echo a` cmd not found	|`echo\` cmd not found	| OK [127]	|

## Other Exit Status Tests
| Status| Test					| Bash						| Minishell					| Exit Code |
|-------|-----------------------|---------------------------|---------------------------|-----------|
| OK	|`fake_cmd`				|Command not found			|Command not found			| OK [127]	|
| OK	|`ls not_a_path`		|No such file or dir		|No such file or dir		| OK [2]	|
| OK	|`./not_executable_file`|Permission denied			|Permission denied			| OK [126]	|
| OK	|`cat clac 3`			|2 error msg				|2 error msg				| OK [1]	|
| OK	|`cd $?`				|Number: no such file or dir|Number: no such file..		| OK [1]	|
| OK	|`cat \|\|\|`			|syntax error				|syntax error				| OK [2]	|
| OK	|`echo "hell`			|unexpected EOF + syntax	|unexpected EOF + syntax	| OK [2]	|

---
Thanks to okushnir for help with tests.
