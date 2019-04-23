# Mortal-Kombat-Arena
"Un Jeu d'échec un peu mieux, je suis sur qu'Ed Boon serait fier et qu'il le publierait"

Projet en C : Tactics Arena

by EL KANDOUSSI Adnan COLIN Kévin AIT ATMANE Daris

Rapide description:

Tactics Arena est un jeu de stratégie tour par tour virtuel ou l'on joue en duel programmé en C. Son concept est proche de celui des échecs, mais il incorpore une certaine variété de pièces, ainsi qu'une part de hasard (les pièces disposent d'un certain nombre de vie, attaque, armure).

Règles du jeu:

Il existe 2 versions du jeu : 
	-mode terminal
	-mode SDL
Au lancement de l'executable, le programme se lancera par défault en terminal.
Pour lancer le mode SDL, il suffit de rajouter "-s" comme option après l'executable.

Le jeu se joue avec 2 joueurs sur un plateau de jeu carré de dimension 10 par 10. Chaque joueur possède sa propre armée composée de différentes unités, chaque pion possède ses propres caractéristiques/classe. Les joueurs peuvent déplacer leurs pions, réfléchir à leur stratégie, restaurer la santé et l'énergie de leurs pions et attaquer les pions adverses à leur portée.

Chaque unité peut lancer des sorts uniques à leurs classe. A chaque tour, le joueur peut décider de déplacer son unité, d'attaquer, de soigner avec un sort ou de passer son tour. 
