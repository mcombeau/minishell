# Builtin Tests

## CD

| Test                   | Status   | Details                        |
|------------------------|----------|--------------------------------|
|`cd ../../../../../..`  | OK       |`pwd` shows `/`                 |
|`cd /home/user42/`      | OK       |                                |
|`cd $HOME/Bureau`       | ERROR    |TODO: handle vars               |
|`unset HOME`, then `cd` | OK       |"HOME not set" + exit 1         |
|`export HOME=` then `cd`| ERROR    |No error msg, + exit 0 		 |
|`cd /t /w`              | OK       |"too many arguments" + exit 1   |
|`cd ./fakepath`  		 | OK		|"no such file or dir" + exit 1  |
|`cd -`					 | OK		|Return to OLDPWD, write CWD     |
|`mkdir a`; `mkdir a/b`; `cd a/b`; `rm -r ../../a`; `cd ..`	| ERROR	|Error msg but still go back a directory, update PWD and OLDPWD, exit 0 |

## ECHO

| Test                    | Status   | Details                        |
|-------------------------|----------|--------------------------------|
|`echo -n -n -nnnn -nnnnm`| ERROR    |Only print `-nnnnm`             |
|`echo a	-nnnnma`      | OK       |Print `a -nnnnma`               |
|`echo -n -nnn hello -n`  | ERROR    |Only print `hello -n`           |
|`echo a	hello -na`    | Ok       |Print `a hello -na`             |

## EXPORT

| Test                    | Status   | Details                        |
|-------------------------|----------|--------------------------------|
|

OK		EXPORT	export var=a ; export $var=test ; echo $var $a	a test			
OK		EXPORT	export $var=test avec var unset	message d'erreur		
OK		EXPORT	export la même variable	modifie la variable (si new value			
OK		EXPORT	export var puis export var=test	verifier pas de doublon			
OK		EXPORT	export "" test=a	export test=a et set $? à 1			
OK		EXPORT	export "" test=a puis env

## ENV

| Test                    | Status   | Details                        |
|-------------------------|----------|--------------------------------|
|`env` then `export d=3 a=12 c=0` then `env`| OK | Variables should not be sorted |




		
		
		
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
PAF		EXTRA	.	exit 2			"." est un built in (alias for source) --> pas à gerer
OK		INIT	env -i ./minishell	ouvre minishell dans un environement vierge			
OK		INIT	$SHLVL	doit être incrémenté a chaque lancement de minishell			
OK		INIT	env -i ./minishell puis echo $SHLVL	1			
OK		PARSING	""	command not found - $?=127			
PAF		PARSING	echo "\s" ; echo "\\s"	should have the exact same output
KO		PARSING	echo "test$<test"	output: test$<test
KO		PARSING	echo test$<test		cree un fichier		
PAF		PARSING	echo "12\""	12"			
OK		PARSING	echo "bip | bip ; coyotte > < \" "	[bip | bip ; coyotte >< " ]			
OK		PARSING	echo \>	>			
PAF		PARSING	echo $USER$var\$USER$USER\$USERtest$USER	user42$USERuser42$USERtestuser42			
PAF		PARSING	echo bonjour \; ls	bonjour ; ls			
OK		PARSING	$	command not found			
OK		PARSING	$LESS$VAR	-R: command not found			
OK		PARSING	..	cmd not found, exit 127			
OK		PARSING	echo '"abc"'	"abc"			
OK		PARSING	echo "'abc'"	['abc']			
OK		PARSING (séparateurs)	echo "" bonjour	[ bonjour]			
?		PARSING (séparateurs)	echo[TAB]a	résultat attendu: [a]			
PAF		PARSING (séparateurs)	echo\ a	echo a': cmd not found			
OK		PARSING (séparateurs)	export ""  et unset ""	erreur			
OK		PARSING (séparateurs)	export "test=ici"=coucou ; echo $test	test="ici=coucou"			
OK		PARSING (séparateurs)	export var="cat Makefile | grep >" ; echo $var	cat Makefile | grep >			
OK		PIPE	cat | cat | cat | ls	ligne ls et 3 retour a la ligne via Entrer			
OK		PIPE	cat Makefile | grep pr | head -n 5 | cd file_not_exit	file_not_exist: no such file... exit status: 1			
OK		PIPE	cat Makefile | grep pr | head -n 5 | hello	hello: cmd not found... exit status: 127			
OK		PIPE	ls | exit	n'affiche rien			
OK		PIPE	sleep 5 | exit	n'affiche rien (attend 5 sec)			
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
-		SIGNAUX	ctrl-\	exit 131 sur bin(ex : sleep 10)&line vide			
-		SIGNAUX	ctrl-C	exit 130 sur bin(ex : sleep 10)&line vide			
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
OK		SYNTHAX	|	"synthax error" & exit 2			
PAF		SYNTHAX	echo bonjour ; |	"synthax error" & exit 2			
OK		SYNTHAX	echo bonjour > > out	"synthax error" & exit 2			
KO*		SYNTHAX echo bonjour > $test	"redirection ambigue" & exit 1			
PAF		SYNTHAX	echo bonjour > $test w/ test="o1 o2"	"redirection ambigue" & exit 1			
OK		SYNTHAX	echo bonjour >>> test	"synthax error" & exit 2			
OK		SYNTHAX	echo bonjour | |	"synthax error" & exit 2			
PAF		SYNTHAX	echo bonjour |;	"synthax error" & exit 2			
OK		UNSET	unset PATH ; echo $PATH	\n			
OK		UNSET	unset PATH ; ls	bash: ls: No such file or directory. Exit 127			
OK		UNSET	unset "" test	unset test et set $? à 1			
OK		UNSET	unset =	erreur et set $? à 1			
OK		UNSET	unset PWD	(leak si on fait cd apres)			
OK		UNSET	unset var	var1 ne doit pas etre unset			
OK		export $var=s\ -la ; l$var				
OK		/bin/echo bonjour	affiche bonjour
OK		/home/user42/	

*AJOUTER MESSAGE D'ERREUR DANS PARSING (+ leak)