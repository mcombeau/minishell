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

<!--
OK		PIPE	cat | cat | cat | ls	ligne ls et 3 retour a la ligne via Entrer			
OK		PIPE	cat Makefile | grep pr | head -n 5 | cd file_not_exit	file_not_exist: no such file... exit status: 1			
OK		PIPE	cat Makefile | grep pr | head -n 5 | hello	hello: cmd not found... exit status: 127			
OK		PIPE	ls | exit	n'affiche rien			
OK		PIPE	sleep 5 | exit	n'affiche rien (attend 5 sec)
-->

### Redirection Tests

<!--
OK		REDIR	<a cat <b <c	seul le contenu de c est affiché			
OK		REDIR	<a cat <b <c      avec b n'existe pas (ou pas les droits)	rien n'est affiché. message d'erreur concernant b			
OK		REDIR	> test | echo blabla; rm test	blabla			
OK		REDIR	>a cat <b >>c 	a est créé vide. c recoit le contenu de b			
OK		REDIR	>a ls >b >>c >d	a, b, c et d sont créés. seul d recoit la redirection de ls			
OK		REDIR	>a ls <machin >>c >d     avec machin n'exite pas	a est créé, il ne recoit pas la redirection (fichier vide). c et d non créés			
OK		REDIR	>file	créé file (vide)			quand pas de commande, doit quand meme faire le redir
OK		REDIR	cat -e > test1 < test2	meme si test2 n'existe pas test1 doit être créé			
OK		REDIR	cat < test	aucun fichier ou dossier de ce type			
OK		REDIR	echo 2 > out1 >> out2	efface out1			
OK		REDIR	echo 2 >> out1 > out2	n'efface pas out1			
PAF		REDIR	echo bonjour > test\ 1	creation du fichier "test 1"			
OK		REDIR	echo test > file test1	= echo test test1 > file			
OK		REDIR	not_cmd bonjour > salut	create file but error msg on standard entry		
-->

### Signal Tests

<!--
-		SIGNAUX	ctrl-\	exit 131 sur bin(ex : sleep 10)&line vide			
-		SIGNAUX	ctrl-C	exit 130 sur bin(ex : sleep 10)&line vide	
-->

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



<!--
KO		PARSING	echo "test$<test"	output: test$<test
KO		PARSING	echo test$<test		cree un fichier		
PAF		PARSING	echo "12\""	12"			
OK		PARSING	echo "bip | bip ; coyotte > < \" "	[bip | bip ; coyotte >< " ]			
OK		PARSING	echo \>	>			
PAF		PARSING	echo $USER$var\$USER$USER\$USERtest$USER	user42$USERuser42$USERtestuser42			
PAF		PARSING	echo bonjour \; ls	bonjour ; ls
-->

### EXPORT


| Status| Test						| Bash								| Minishell						|
|-------|---------------------------|-----------------------------------|-------------------------------|
| ERROR	|`export ""`				|Not a valid identifier				|`(newline)`					|
| ERROR	|`export 42`				|Not a valid identifier				|`(newline)`					|
| OK	|`export var=foo`			|`env \| grep var=` shows var		|`env \| grep var=` shows var	|
| ERROR	|`export $var=test`			|`env \| grep foo=` shows `foo=test`|`env \| grep foo=` shows nothing|
| ERROR	|`echo $var $foo`			|`foo test`							|`(newline)`					|

<!--			
OK		EXPORT	export $var=test avec var unset	message d'erreur		
OK		EXPORT	export la même variable	modifie la variable (si new value			
OK		EXPORT	export var puis export var=test	verifier pas de doublon			
OK		EXPORT	export "" test=a	export test=a et set $? à 1			
OK		EXPORT	export "" test=a puis env

OK		PARSING (séparateurs)	export ""  et unset ""	erreur			
OK		PARSING (séparateurs)	export "test=ici"=coucou ; echo $test	test="ici=coucou"			
OK		PARSING (séparateurs)	export var="cat Makefile | grep >" ; echo $var	cat Makefile | grep >
-->

### UNSET
<!--
OK		UNSET	unset PATH ; echo $PATH	\n			
OK		UNSET	unset PATH ; ls	bash: ls: No such file or directory. Exit 127			
OK		UNSET	unset "" test	unset test et set $? à 1			
OK		UNSET	unset =	erreur et set $? à 1			
OK		UNSET	unset PWD	(leak si on fait cd apres)			
OK		UNSET	unset var	var1 ne doit pas etre unset			
OK		export $var=s\ -la ; l$var				
OK		/bin/echo bonjour	affiche bonjour
OK		/home/user42/	
-->

### ENV

| Status| Test						| Bash				| Minishell			|
|-------|---------------------------|-------------------|-------------------|
| OK	|`env` then `export d=3 a=12 c=0` then `env`||Vars not sorted		|


<!--	
OK		PARSING	""	command not found - $?=127			
			
OK		PARSING	$	command not found			
OK		PARSING	$LESS$VAR	-R: command not found			
OK		PARSING	..	cmd not found, exit 127	
	
OK		EXIT STATUS	cd random_cmd ; echo $?	Doit afficher le code erreur de cd : 1			
OK		EXIT STATUS	cd random_cmd ; cd $?	exit 1 (deux erreurs affichées)			
OK		EXIT STATUS	./file_that_is_not_an_executable	permission denied -> exit status = 126			
OK		EXIT STATUS	cat bla	1			
OK		EXIT STATUS	file_name	cmd not found (pbm avec stat() pour les binaires) - exit 127			
OK		EXIT STATUS	not_cmd	cmd not found -> exit status = 127			
OK		EXIT STATUS	export test=a ; echo $test	affiche le contenu de test			
OK		EXIT STATUS	ls bonjour ; echo $?	2			
			
PAF		EXTRA	echo ~	/home/user42			facultatif
PAF		EXTRA	export var=te"st PUIS echo $var	Multiligne			Pas à gérer
PAF		EXTRA	export var=te"st ; echo $var	Multiligne			Pas à gérer
PAF		EXTRA	.	exit 2			"." est un built in (alias for source) > pas à gerer
OK		INIT	env -i ./minishell	ouvre minishell dans un environement vierge			
OK		INIT	$SHLVL	doit être incrémenté a chaque lancement de minishell			
OK		INIT	env -i ./minishell puis echo $SHLVL	1
		
PAF		SUBST	export var="  truc"; echo $var	[truc]			
PAF		SUBST	export var="truc  "; echo $var | cat -e	[truc]			
OK		SUBST	echo "$tests""Makefile"	[Makefile]			
OK		SUBST	echo "$tests"Makefile	[Makefile]			
OK		SUBST	echo "$tests" "Makefile"	[ Makefile]			
OK		SUBST	echo "$tests" Makefile 		[ Makefile]
OK		SUBST	$bla (non-export)	retour a la ligne, exit 0			
OK		SUBST	echo $var bonjour ($var non export)	[bonjour]			
OK		SUBST	export $var (var non export)	affiche export			
PAF		SUBST	export test=123\" ; echo $test	123"			
PAF		SUBST	export test=123\\ ; echo $test	123\			
PAF		SUBST	export test=123\' ; echo $test ; echo $test	123' 123'			
PAF		SUBST	export test="  foo    bar  " ; echo $test	[foo bar]			word spliting
PAF		SUBST	export test="  foo    bar  " ; echo ab$test	[ab foo bar]			word spliting
PAF		SUBST	export test="  foo    bar  " ; echo "ab"$test	[ab foo bar]			word spliting
PAF		SUBST	export test=" foo   bar " ; echo ab"$test" | cat -e	[ ab foo   bar ]			pas de word splitng
PAF		SUBST	export test=" foo   bar " ; echo "$test"	[ foo   bar ]			pas de word splitng
PAF		SUBST	export test=" foo   bar " ; echo ""$test""	[ foo bar ]			word splitng
PAF		SUBST	export test=" foo   bar " ; echo """$test"""	[ foo   bar ]			pas de word splitng
PAF		SUBST	export var= s\ -la ; l$var	equivalent à ls -al			word spliting (meme si l'espace est escaped, on split)
OK		SUBST	export var=at ; c$var Makefile	equivalent a cat Makefile			
OK		SUBST	export loop='bonjour$loop' ; echo $loop	bonjour$loop			
?		SUBST & REDIR	export test="file1 file2" ; >$test	$test: ambiguous redir			Si le word spliting du redir "expands to more than one word", error ambiguous redir
OK		SUBST & REDIR	export test="file1 file2" ; >"$test"	[file1 file2] created			Si guillemets ("$test"), pas de word spliting
?		SUBST & REDIR	export test="file1 file2" ; >$test >hey	$test: ambiguous redir, hey n'est pas créé			
?		SUBST & REDIR	export test="file1 file2" ; >hey >$test	$test: ambiguous redir, hey est créé			

-->

---
Thanks to okushnir for help with tests.