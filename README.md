# 42sh

## BUGS

env:
env PATH=toto ls -> le PATH est trouver alors que ce ne devrait pas.
history P_UP P_DO

If a command is not found, the exit status shall be 127.

## expansion

backquote ok.
_ executer la chaine de caractere `command` dans un sous shell, récupérer le résultat de la sortie standard
dans une chaine de caractère (char par char pour rajouter un '\' devant les '"') puis ajouter le résultat
à la chaine de caractère principale. (ex: lol`ls`mdr => lol(resultat)mdr);

word splitting ok.
_ split par rapport a tous les blanks (' ', '\t', '\n') ET exception des '"' (ex:"lol mdr oups" => UNE seule chaine)

## BONUS:

	coloration syntaxique
	builtins readonly
	builtins printenv
	table de hash
	builtin declare
	prompt (PS)
	ctr+R
	cvx sys + interne
	completion historique
