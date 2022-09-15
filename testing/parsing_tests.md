# Parsing Tests
## Test list

* **Expected** column is Bash output.
* **Output** columnn is Minishell's output.

### Variable expansion

| Status| Test					| Expected			| Output			|
|-------|-----------------------|-------------------|-------------------|
| OK	|`echo $USER`			| `username`		|`username`			|
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
| OK	|`echo "$USER11111fjfjfjf"`|`(newline)`		|`(newline)`		|
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
| OK	|`echo $NULL test`		|` test`			|` test`			|


### Quote handling

| Status| Test					| Expected			| Output			|
|-------|-----------------------|-------------------|-------------------|
| OK    |`ec""ho test`			|`test` 			|`test` 			|
| OK	|`""echo test`			|`test`				|`test`				|
| OK	|`echo"" test`			|`test`				|`test`				|
| OK	|`echo "" test`			|` test`			|` test`			|
| OK	|`echo $USE""R`			|`R`				|`R`				|
| OK	|`echo ""$USER`			|`username`			|`username`			|
| OK	|`echo "$"USER`			|`$USER`			|`$USER`			|
| OK	|`echo  $""USER`		|`USER`				|`USER`				|
| OK	|`ec''ho test`			|`test`				|`test`				|
| OK	|`''echo test`			|`test`				|`test`				|
| OK	|`echo'' test`			|`test`				|`test`				|
| OK	|`echo '' test`			|` test`			|` test`			|
| OK	|`echo $USE''R`			|`R`				|`R`				|
| OK	|`echo ''$USER`			|`username`			|`username`			|
| OK	|`echo '$'USER`			|`$USER`			|`$USER`			|
| OK	|`echo  $''USER`		|`USER`				|`USER`				|
| OK	|`echo "" "" "" test`	|`   test`			|`   test`			|
| OK	|`echo """""" test`		|` test`			|` test`			|
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
| ERROR |`echo test "'"test`	|`test 'test`		|`test test`		|
| OK	|`echo "\|" ls`			|`\| ls`			|`\| ls`			|
| ERROR	|`echo '"abc"'`			|`"abc"`			|`abc`				|
| ERROR	|`echo '  "abc" '`		|` "abc"`			|`abc`				|
| ERROR	|`echo " $ " \| cat -e`	|` $ $`				|`$$`				|
| ERROR	|`echo $:$= \| cat -e`	|`$:$=$`			|`$=$`				|
| OK	|`export FOO=' " '`		|					|					|
| ERROR	|`echo " $FOO " \| cat -e`|`  "  $`			|`$`				|

### Pipe tests

| Status| Test										| Expected			| Output			|
|-------|-------------------------------------------|-------------------|-------------------|
| OK	|`echo test \|cat`							|`test`				|`test`				|
| OK	|`echo test \|\|\| cat`						|syntax error		|syntax error		|
| OK	|`export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8`	|					|					|
| ERROR	|`echo "$A'$B"'$C"$D'$E'"$F"'"'$G'$H"`		|`1'2$C"$D5"$F"'7'8`|`$C"$D"$F`			|


---
Thanks to okushnir for tests.