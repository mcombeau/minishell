# Execution tests
		
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

-->