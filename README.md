# Rapport de projet 2048

## Auteurs

- Bozzi Menéndez Luca, luca.bozzi-menendez@etu-upsaclay.fr
- Lancelot Gabriel, gabriel.lancelot@universite-paris-saclay.fr


## Installation du projet

Pour installer les dépendances nécessaires au projet, suivez les instructions ci-dessous en fonction de votre système d'exploitation.

### Prérequis
Avant de commencer, assurez-vous d'avoir les éléments suivants installés :
- [WSL (Windows Subsystem for Linux)](https://learn.microsoft.com/fr-fr/windows/wsl/install) pour les utilisateurs Windows.
- Un compilateur C++ supportant C++17 (ou plus récent).
- [SDL2](https://wiki.libsdl.org/SDL2/Installation) pour la gestion des graphismes.

### Étape 1 : Cloner le dépôt
Clonez le dépôt Git contenant le projet :
```bash
git clone https://github.com/Gabriel-lct/2048.git
cd 2048
```

### Étape 2 : Installer les dépendances
```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-ttf-dev libncurses5-dev
```

## Démonstration

Notez comment on lance une commande shell en la préfixant d'un point
d'exclamation (mais cela ne permet pas l'interaction avec
l'utilisateur).

Suivons ensemble les étapes d'une partie de 2048.

Pour compiler le projet, vous pouvez exécuter la commande suivante :

```bash
make
```

Vous pourrez alors lancer le jeu depuis un terminal avec :
```
./2048
```
Dans le terminal, s'affiche alors les informations suivantes :

```	
Welcome to the 2048 Game.

Current board size: 4x4
Current key setting: ZQSD
Current score : 0
```

suivi des propositions suivantes :

```
Please select an option:
  1. CLI (Client Line Interface)
  2. GUI (Game User Interface)
  3. GA (Genetic Algorithm)
  4. OPTIONS
  5. RESET
  6. QUIT

Your option:
```

Les options sont détaillées ci-dessous :

| Option | Acronyme | Description |
| --- | --- | --- |
| `1` | CLI | Lance le jeu en mode console. |
| `2` | GUI | Lance le jeu en mode graphique. |
| `3` | GA | Lance l'algorithme génétique. |
| `4` | OPTIONS | Affiche les options disponibles. |
| `5` | RESET | Réinitialise le jeu. |
| `6` | QUIT | Quitte le jeu. |

### CLI -  Mode console

Pour lancer une partie en mode console, il suffit de taper `1`. Pour jouer, voir les commandes ci-dessous.

### GUI - Mode Graphique

Pour lancer une partie en mode graphique, il suffit de taper `2`. Pour jouer, voir les commandes ci-dessous.

### GA - Algorithme génétique

Pour lancer l'algorithme génétique, il suffit de taper `3`.

### Commandes
| Touche | Action |
| --- | --- |
| `q/w`, `flèche gauche` | Déplacer les tuiles vers la gauche. |
| `d/a`, `flèche droite` | Déplacer les tuiles vers la droite. |
| `z/s`, `flèche haut` | Déplacer les tuiles vers le haut. |
| `s/d`, `flèche bas` | Déplacer les tuiles vers le bas. |
| `a` | Lancer/arrêter l'IA. |
| `r` | Recommencer la partie. |
| `Echap` | Revenir au menu. |

### Options

| Option | Description |
| --- | --- |
| `Board Size` | Changer la taille de la grille de jeu (entre 2 et 20). |
| `Key Setting` | Sélectionner la disposition du clavier (ZQSD ou WASD). |
| `AI Depth` | Changer la profondeur de l'IA (entre 1 et 10). |

## Résumé du travail effectué

- Niveau 0 : 
  - Structure du jeu : réalisée, testée et documentée.
  - Compilation des fichiers : réalisée, testée et documentée.
  - Fonctionnalité du jeu : réalisée, testée et documentée.
  - Respect des règles : réalisée, testée et documentée.
  - Mise à jour du score : réalisée, testée et documentée.
  - Alignement des colonnes : réalisée, testée et documentée.

- Niveau 1 : 
  - Couleur console : réalisée, testée et documentée. Pas de difficultés particulières rencontrées. Utilisation de la bibliothèque `ncurses`.
  - Flèches clavier : réalisée, testée et documentée. Pas de difficultés particulières rencontrées. Utilisation de la bibliothèque `ncurses`.
  - Rafraîchissement écran : réalisée, testée et documentée. Pas de difficultés particulières rencontrées. Juste un clearConsole().
  - Structure score : réalisée, testée et documentée. Pas de difficultés particulières rencontrées. Stocké dans un struct.
- Niveau 2 : 
  - Makefile : réalisée, testée et documentée. Un peu de recherche sur internet aura permis de créer le MakeFile.
  - Gestionnaire de version : réalisée, testée et documentée. Aucune difficulté, le projet est disponible sur GitHub.
- Niveau 3 : 
  - IA : réalisée, testée et documentée. Voir section AI.
  - Variante (taille grille) : réalisée, testée et documentée.  Pas de difficultés particulières rencontrées.
  - SDL Integration : réalisée, testée et documentée. Voir section SDL.
  - Application : ahah, non.

#### Artificial Intelligence
Notre intelligence artificielle est basée sur l'algorithme Minimax, qui explore l'arbre des possibilités pour chaque coup avec une profondeur donnée. Pour évaluer la qualité de chaque coup, nous avons utilisé une fonction de récompense qui prend en compte plusieurs critères, tels que la valeur des tuiles, leur position, la présence de tuiles vides, etc. Cependant, nous n'avons pas réussi à déterminer les poids de cette fonction de récompense de manière satisfaisante. Nous avons donc implémenté un algorithme génétique pour optimiser ces poids, mais sans succès pour l'instant.

#### SDL Integration

Nous avons décidé d'utiliser la bibliothèque SDL pour l'interface graphique de notre jeu. Cela nous a permis de créer une version plus attrayante et interactive du jeu, avec des couleurs, des animations et des contrôles plus intuitifs. Cependant, l'intégration de SDL a été difficile, car il a fallu tout programmer manuellement, sans utiliser de bibliothèque tierce. Cela a demandé beaucoup de temps et d'efforts pour comprendre les mécanismes internes à la bibliotèque SDL, mais le résultat final en valait la peine.

#### Genetic Algorithm
Notre IA est défini par un génome de 5 valeurs, chacune de ces valeurs correspondant à un poids dans la fonction de récompense. Pour déterminer ces poids, nous avons utilisé un algorithme génétique. Cet algorithme génétique est composé de 4 étapes : la sélection, le croisement, la mutation et l'évaluation. La sélection est basée sur la roulette naturelle, le croisement est un croisement en un point, la mutation est une mutation uniforme et l'évaluation est basée sur le score obtenu par l'IA grâce à l'algorithme minimax de l'IA.
Précisons que pour chaque génome d'une population, un nombre défini de parties est joué et le score moyen est calculé. C'est ce score moyen qui est utilisé pour évaluer la performance de chaque génome.

## Organisation du travail

Pour ce projet, nous avons adopté une organisation assez simple mais efficace. Chacun travaillait de son côté, en se concentrant sur des aspects précis du projet. Nous avons utilisé GitHub pour centraliser et synchroniser notre travail, ainsi que LiveShare pour travailler de manière simultanée sur le même espace de travail.

Luca s’est principalement chargé de la logique interne du jeu, assurant que les règles soient bien respectées et que le comportement général soit fluide. Il a également travaillé sur l’affichage SDL pour rendre le jeu agréable visuellement. De son côté, Gabriel s’est concentré sur l’affichage en mode terminal, pour avoir une version simplifiée mais fonctionnelle du jeu. En plus de cela, il a conçu une IA capable de jouer automatiquement ainsi qu'un algorithme génétique qui permet l'optimisation de la détermination des poids utilisés dans par la fonction de récompense de l'IA.

Nous avons consacré environ quarante heures chacun à ce projet, réparties sur plusieurs semaines, souvent en soirée ou durant nos temps libres. Bien que nous ayons principalement travaillé de manière autonome, nous avons aussi échangé régulièrement pour discuter de nos idées, ajuster nos priorités et résoudre des problèmes ensemble.

## Prise de recul
L’un des principaux obstacles a été l’utilisation de SDL. Rien que l’installation s’est avérée complexe et frustrante, car il faut installer de nombreux fichiers de la bibliotèque SDL2 qui s'ont difficilement trouvable. Après avoir rencontré de nombreuses difficultés pour installer SDL sur Windows, nous avons décidé de passer à un environnement Linux. Ce changement a grandement facilité la tâche, car l'installation des dépendances et la configuration de SDL se sont avérées beaucoup plus simples et rapides sur Linux. Une fois cette étape passée, le développement avec SDL demandait de tout programmer manuellement, ce qui est puissant mais aussi très chronophage. Cela nous a appris l’importance de bien choisir les outils en fonction du projet, et de bien anticiper la phase d’installation et de configuration. 

Pour l’IA, la partie concernant l’algorithme Minimax n’a pas posé de grandes difficultés. En regardant quelques vidéos explicatives sur YouTube (environ trois ou quatre), le concept et son implémentation ont été assez clairs. Par contre, une grosse difficulté est survenue lorsqu’il a fallu déterminer les poids de la fonction de récompense pour guider l’IA. Malgré nos efforts, nous n’avons pas trouvé de solution satisfaisante à ce problème jusqu’à présent.

Si nous devions refaire ce projet, nous serions plus méthodiques dans notre approche. Pour SDL, nous testerions d’autres bibliothèques, ce qui aurait pu nous épargner des heures de configuration et de compréhension de SDL.
Pour l’IA, nous envisagerions d’approfondir les méthodes de réglage des poids, peut-être en utilisant des techniques de machine learning ou en consultant davantage de ressources. Cela nous permettrait de produire une IA plus performante et cohérente.

