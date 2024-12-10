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
git clone <URL_DU_DEPOT>
cd <NOM_DU_DOSSIER>
```

### Étape 2 : Installer les dépendances
```bash
sudo apt update
sudo apt install METTRE DEPENDANCES
```

## Résumé du travail effectué

:::{admonition} Consignes

Pour les questions «Aller plus loin» plus ouvertes, décrivez plus en
détail ce que vous avez choisi de réaliser. Précisez les difficultés
rencontrées, les choix d'implantation que vous avez fait, etc.

En plus du rapport, la documentation de chaque fonction dans le code
devra préciser son auteur et votre degré de confiance dans
l'implantation, ainsi que les éléments factuels motivant cette
confiance: présence de tests, bogues et limitations connus, etc.

:::

- Niveau 0 : 
  - Structure du jeu : réalisée, documentée, testée
  - Compilation des fichiers : réalisée, documentée, testée
  - Fonctionnalité du jeu : réalisée, documentée, testée
  - Respect des règles : réalisée, documentée, testée
  - Mise à jour du score : réalisée, documentée, testée
  - Alignement des colonnes : réalisée, documentée, testée.

- Niveau 1 : 
  - Couleur console : réalisée, documentée, testée. Pas de difficultés particulières rencontrées.
  - Flèches clavier : réalisée, documentée, testée. Pas de difficultés particulières rencontrées.
  - Rafraîchissement écran : réalisée, documentée, testée. Pas de difficultés particulières rencontrées.
  - Structure score : non réalisée
- Niveau 2 : 
  - Makefile : réalisée, document��e, testée. Un peu de recherche sur internet aura permis de créer le MakeFile.
  - Gestionnaire de version : réalisée, documentée, testée. Aucune difficulté, le projet est disponible sur GitHub.
- Niveau 3 : 
  - IA : réalisée, documentée, testée. Voir section IA.
  - Variante (taille grille) : réalisée, documentée, testée.  Pas de difficultés particulières rencontrées.
  - SDL Integration : réalisée, documentée, testée. Voir section SDL.
  - Application : ahah, non.

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
  1. CLI (Client L... Interface)
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

Pour lancer une partie en mode console, il suffit de taper `1` puis `Entrée`. Pour jouer, voir les commandes ci-dessous.

### GUI - Mode Graphique

Pour lancer une partie en mode graphique, il suffit de taper `2` puis `Entrée`. Pour jouer, voir les commandes ci-dessous.

### GA - Algorithme génétique

Pour lancer l'algorithme génétique, il suffit de taper `3` puis `Entrée`.

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
| `Board Size` | Changer la taille de la grille de jeu. |
| `Key Setting` | Sélectionner la disposition du clavier (ZQSD ou WASD). |


## Organisation du travail

:::{admonition} Consignes
Décrivez en quelques phrases comment vous vous êtes organisés pour
travailler sur le projet: nombre d'heures consacrées au projet,
répartition du travail dans le binôme, moyens mis en œuvre pour
collaborer, etc. Si vous avez bénéficié d'aide (en dehors de celle de
vos enseigants), précisez le.
:::

Pour ce projet, nous avons adopté une organisation assez simple mais efficace. Chacun travaillait de son côté, en se concentrant sur des aspects précis du projet. Nous avons utilisé GitHub pour centraliser et synchroniser notre travail.

Luca s’est principalement chargé de la logique interne du jeu, assurant que les règles soient bien respectées et que le comportement général soit fluide. Il a également travaillé sur l’affichage SDL pour rendre le jeu agréable visuellement. De son côté, Gabriel s’est concentré sur l’affichage en mode terminal, pour avoir une version simplifiée mais fonctionnelle du jeu. En plus de cela, il a conçu une IA capable de jouer automatiquement ainsi qu'un algorithme génétique qui permet l'optimisation de la détermination des poids utilisés dans par la fonction de récompense de l'IA. 


Nous avons consacré environ trente heures chacun à ce projet, réparties sur plusieurs semaines, souvent en soirée ou durant nos temps libres. Bien que nous ayons principalement travaillé de manière autonome, nous avons aussi échangé régulièrement pour discuter de nos idées, ajuster nos priorités et résoudre des problèmes ensemble.
+++

## Prise de recul

:::{admonition} Consignes
Décrivez en quelques phrases les difficultés rencontrées, ce que vous
avez appris à l'occasion du projet, le cas échéant comment vous vous y
prendriez si vous aviez à le refaire.
:::

L’un des principaux obstacles a été l’utilisation de SDL. Rien que l’installation s’est avérée complexe et frustrante, car il faut installer de nombreux fichiers de la bibliotèque SDL2 qui s'ont difficilement trouvable. Une fois cette étape passée, le développement avec SDL demandait de tout programmer manuellement, ce qui est puissant mais aussi très chronophage. Cela nous a appris l’importance de bien choisir les outils en fonction du projet, et de bien anticiper la phase d’installation et de configuration. 

Pour l’IA, la partie concernant l’algorithme Minimax n’a pas posé de grandes difficultés. En regardant quelques vidéos explicatives sur YouTube (environ trois ou quatre), le concept et son implémentation ont été assez clairs. Par contre, une grosse difficulté est survenue lorsqu’il a fallu déterminer les poids de la fonction de récompense pour guider l’IA. Malgré nos efforts, nous n’avons pas trouvé de solution satisfaisante à ce problème jusqu’à présent.

Si nous devions refaire ce projet, nous serions plus méthodiques dans notre approche. Pour SDL, nous testerions d’autres bibliothèques, ce qui aurait pu nous épargner des heures de configuration et de compréhension de SDL.
Pour l’IA, nous envisagerions d’approfondir les méthodes de réglage des poids, peut-être en utilisant des techniques de machine learning ou en consultant davantage de ressources. Cela nous permettrait de produire une IA plus performante et cohérente.

