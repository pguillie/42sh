# 42sh

## alias

stockage: variable type array

! ATTENTION
!	boucle infinies: des qu'on retombe sur un element
!	qu'on a deja rencontré, on s'arrete.

## exit status (command)

If a command is not found, the exit status shall be 127.

If the command name is found, but it is not an executable utility,
the exit status shall be 126.

If a command fails during word expansion or redirection,
its exit status shall be greater than zero.

Internally, for purposes of deciding whether a command exits
with a non-zero exit status, the shell shall recognize
the entire status value retrieved for the command by the
equivalent of the wait() function WEXITSTATUS macro.

When reporting the exit status with the special parameter '?',
the shell shall report the full eight bits of exit status available.

The exit status of a command that terminated because
it received a signal shall be reported as greater than 128.

## variables

Initialisation du shell:
	- récupération des variables exportées par le process pere
	- création des variables manquantes
	  > variables de configuration
	  	. columns
		. shell_name
		. PSn
	  > ~/.rc
	- termcaps

| IMPORTANT
|	ordre important - ex: si PS1 est present dans l'env, il sera
|	remplacé par le PS1 de notre shell, mais restera dans l'env.

Variable:
	- name
	- value
	- flags

! ATTENTION
!	voir impact des pipe/subshell
!	sur la manipulation des variables

Génerer l'environnement a chaque fois qu'on en a
besoin a partir des flags 'export'.

idees variables:
	PIPESTATUS (array)
	
