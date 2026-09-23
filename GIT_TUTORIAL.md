# Setup git sur windows

Lorsqu'un terme est entres '{}', il doit être remplacé.

[c'est quoi git?](https://www.youtube.com/watch?v=2ReR1YJrNOM) (vidéo)

[utiliser git](https://www.youtube.com/watch?v=8JJ101D3knE) (vidéo)

[git forking](https://www.youtube.com/watch?v=deEYHVpE1c8) (Vidéo)

[télécharger git](https://www.git-scm.com)

Si vous utilisez Mac ou Linux, manifestez-vous dans le discord.

# Terminologie

Repository
: Un repository est une base de données qui contient tout ce qui est relatif à un projet de programmation. C'est un espace partagé qui permet de travailler sur un projet commun.

Staging area
: Zone de stockage local de modifications.

Branches
: Une branche est un pointeur vers un commit à un moment donné. C'est tout.

Commit
: Un commit enregistre les modifications apportées dans 'staging area'.

Fork
: Fork c'est tout simplement copier un repo afin de le modifier plutôt que de modifier le repo original directement. Le fork reste lié au repo d'origine, ce qui permet de le modifier avec une pull request.

# Configurer git

### Nom d'utilisateur

`git config --global user.name "{Nom, Prénom}"`

### Email

`git config --global user.email {email}`

### VSCode comme éditeur princpal

`git config --global core.editor "code --wait"`

### Fork le repository du club de robotique

-> [ici](https://github.com/obr-code/Club_Robotique_Limoilou)

'Fork' -> 'Create a new fork'

Dans le terminal:

`git clone {SSH du fork}`

Le SSH est dans 'Code' sur votre fork.

`git remote add {SSH original}`

... ou simplement;

`git remote add git@github.com:obr-code/Club_Robotique_Limoilou.git`

### Faire une première Pull Request

Obtenir la version la plus récente du repository original:

`git fetch upstream`

Mettre à jour votre branche avec la version locale du repository original:

`git merge upstream/main`

Testez votre configuration en ouvrant 'programmers.txt' et en y rajoutant votre nom et prénom.

Ensuite;

`git add programmers.txt`

`git commit -m "premier commit de {Prénom Nom}"`

`git push origin main`

Finalement, ouvrir github et faire une pull request depuis votre fork.

# Commandes utiles

### Obtenir des informations sur une commande git

`git {commande} -h`

### Initialiser un nouveau répertoire

`git init`

### Ajouter des fichiers/dossiers -> staging area

`git add {path}`

**Important**: Le fichier doit être ajouté de nouveau s'il a subit de nouveaux changements locaux depuis qu'il a été ajouté pour la première fois.

**Important**: Pour update un fichier qui a été supprimé-

`git add {fichier_supprimé}`

### Modifier l'emplacement ou le nom d'un fichier

`git mv {ancien_path} {nouveau_path}`

### Obtenir le status actuel du dossier + staging area

`git status`

### Publier un commit

`git commit -m "{message}"`

### Clone

`git clone {SSH}`

**Important**: Choisir un message clair, simple et au présent. Utiliser l'anglais.
Ex: "Correct typos in GIT_TUTORIAL"

Si un message long est nécessaire: [cliquez_ici](https://youtu.be/8JJ101D3knE?t=1546)

### Gitignore

Gitignore permet d'isoler certains fichiers et dossiers localement. C'est une excellente pratique de programmation.

Pour ouvrir gitignore et y ajouter des fichiers:

`code .gitignore`