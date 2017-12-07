# 42sh

## BUGS


## LEAKS

!!:s illegal (normalement fix)

## expansion

backquote ok.
_ executer la chaine de caractere `command` dans un sous shell, récupérer le résultat de la sortie standard
dans une chaine de caractère (char par char pour rajouter un '\' devant les '"') puis ajouter le résultat
à la chaine de caractère principale. (ex: lol`ls`mdr => lol(resultat)mdr);

word splitting ok.
_ split par rapport a tous les blanks (' ', '\t', '\n') ET exception des '"' (ex:"lol mdr oups" => UNE seule chaine)

## BONUS:

	cvx sys + interne
	prompt (PS)
	ctr+R
	completion historique
	table de hash
	coloration syntaxique
	builtin declare
	builtin readonly
	builtin printenv
