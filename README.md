# 42sh

## changement a accepter:
/*
** sh_tab_multi ligne 55: proteger le while(.. && occ[j] && [array[i][j]] ..)
** peut causer un invalide read.
**
** sh_tab_find.c ligne 69: envoyer le resultat de S_ISDIR puis ligne 30 tester
** ce resultat pour envoyer directement "/" dans le strncat ou ne pas le faire.
**
** define PS1 "\\e[38;5;114m[\\@]\\e[0m \\e[38;5;74m\\w \\$\\e[0m "
** "\\e[0m" apres chaque couleur (permet d'éviter de la couleur partout
** en trop si le prompt pete, a cause de `declare` par ex :p).
*/

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
