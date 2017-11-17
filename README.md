# 42sh


Expansion:
{
..
Command Substitution:
	_ `command`: fork pour envoyer la commande en rappelant un nouveau shell puis ecrire le resultat sur la sortie standard
	squeeze la partie edition de ligne pour mettre la commande dans le lexer puis faire la suite du programme avec un exit.
	Modifie:
	_ lexer: _les '`' sont des séparateur.
			 _apres des '`' le mot suivant est une commande.
			 _brackets! $(`cmd) => LEX_LOOP => $(`cmd)`) => LEX_OK
}
