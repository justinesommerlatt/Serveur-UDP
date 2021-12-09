# Serveur-UDP
Travail de Réseau, serveur UDP

Sujet de TP réalisé en intégralité (question 6 incluse)


Afin de lancer le programme et également de tester s’il fonctionne bien la démarche à suivre est la suivante : 
- ouvrir un terminal depuis le code où nous allons préciser la plage des ports en écoute.
Dans la question 3 on souhaite écouter sur les ports 2000 et 2002, la commande à saisir dans le terminal est donc ./serverupd 2000 2002
« serverupd » est le nom du fichier du code, « 2000 » est le début de la plage des ports et « 2002 » la fin de la plage des ports en écoute 
—> (si on avait souhaité écouter les ports de 2000 à 2020 la commande aurait été ./serverupd 2000 2020

- il faut ensuite ouvrir deux autres terminaux dans lesquels il va falloir taper la commande : 
* dans le premier terminal on tape la commande nc -u -l 2001
* dans le deuxième terminal on tape la commande nc -u -l 2003
Ces deux terminaux vont attendre les réponses sur les ports 2001 et 2003 

- il faut enfin ouvrir deux autres terminaux dans lesquels nous allons taper le message à envoyer : 
* dans le premier terminal on tape la commande nc -u localhost 2000 
on écrit ensuite le message désiré puis on valide
* dans le deuxième terminal on tape la commande nc -u localhost 2002
on écrit ensuite le message désiré puis on valide
Cela va permettre d’envoyé le message tapé sur le serveur au port indiqué dans la commande


Le ou les messages envoyés vont donc s’afficher dans le 1er terminal que l’on a ouvert (celui qui contient la commande ./serverupd 2000 2002) en précisant quel est son port d’envoi et son port de destination 
La réponse au message du port 2000  (respectivement 2002) s’affichera dans le terminal commençant par la commande nc -u -l 2001 (respectivement nc -u -l 2003) 

