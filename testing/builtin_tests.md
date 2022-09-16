# Builtin Tests
## TODO

* variable expansion for cd builtin
* variable expansion for export builtin

## CD

| Status| Test						| Expected							| Output					|
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

## ECHO

| Status| Test						| Expected			| Output			|
|-------|---------------------------|-------------------|-------------------|
| OK	|`echo -n -n -nnnn -nnnnm`	|`-nnnnm`           |`-nnnnm`			|
| OK	|`echo a	-nnnnma`		|`a -nnnnma`		|`a -nnnnma`		|
| OK	|`echo -n -nnn hello -n`	|`hello -n`			|`hello -n`			|
| OK	|`echo a	hello -na`		|`a hello -na`		|`a hello -na`		|

<!--
PAF		PARSING	echo "\s" ; echo "\\s"	should have the exact same output
KO		PARSING	echo "test$<test"	output: test$<test
KO		PARSING	echo test$<test		cree un fichier		
PAF		PARSING	echo "12\""	12"			
OK		PARSING	echo "bip | bip ; coyotte > < \" "	[bip | bip ; coyotte >< " ]			
OK		PARSING	echo \>	>			
PAF		PARSING	echo $USER$var\$USER$USER\$USERtest$USER	user42$USERuser42$USERtestuser42			
PAF		PARSING	echo bonjour \; ls	bonjour ; ls
-->

## EXPORT


| Status| Test						| Expected							| Output						|
|-------|---------------------------|-----------------------------------|-------------------------------|
| ERROR	|`export ""`				|Not a valid identifier				|`(newline)`					|
| ERROR	|`export 42`				|Not a valid identifier				|`(newline)`					|
| OK	|`export var=foo`			|`env \| grep var=` shows var		|`env \| grep var=` shows var	|
| ERROR	|`export $var=test`			|`env \| grep foo=` shows `foo=test`	|`env \| grep foo=` shows nothing|
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

## UNSET
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

## ENV

| Status| Test						| Expected			| Output			|
|-------|---------------------------|-------------------|-------------------|
| OK	|`env` then `export d=3 a=12 c=0` then `env`||Vars not sorted		|


---
Thanks to okushnir for tests.