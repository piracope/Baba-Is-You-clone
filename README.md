# Baba Is You

Implémentation en C++ du jeu Baba Is You créé par Arvi Teikari.

Vous trouverez le code source ainsi que les tests unitaires dans
le dossier `BabaEstToi/`. Le rapport d'analyse se trouve dans le
dossier `Modélisation/`, accompagné du schéma UML du projet.

## Déviations par rapport à l'analyse

### Général

Des surcharges d'opérateurs ont été ajoutées pour faciliter
l'affichage, ainsi que des méthodes to_string.

### Game

La classe Façade Game a été renommée en Baba... parce que.

### FileManager

L'implémentation prévue de FileManager était un Singleton qui lirait
au démarrage du jeu l'entièreté des fichiers. Récupérer un niveau ne
ferait donc que récupérer une des string gardées en mémoire.

Toutefois, il est beaucoup plus intéressant de lire les niveaux à 
mesure qu'ils sont rencontrés dans le jeu, et non en une fois. Étant
donné que le stockage des niveaux en RAM n'est plus nécessaire, il
n'est plus non plus requis de cette classe d'être un Singleton. Il ne
s'agit plus que d'une classe utilitaire qui lit et écrit des fichiers.

### Level
#### Représentation du plateau

Nous passons d'une unordered_multimap à une multimap. Utiliser une
unordere_mutimap aurait nécessité de créer une fonction de hachage pour
la classe Position, et cela dépasse nos compétences. Passer à une
multimap triée nécessite une fonction de comparaison, mais celle-ci
est triviale à implémenter. Cela permet aussi de trier les éléments
sur le plateau de façon à rendre l'affichage plus aisé.

#### Position

Afin de représenter plus généralement un vecteur, un couple (x, y),
ses champs sont devenus signés. Ces changements sont aussi reflétés
dans les dimensions des niveaux.

#### `getPlayerObjects`

Cette méthode étant originellement tout le temps utilisée avec
`getAllOfType`, `getPlayerObjects` retourne à présent tous les
`GameObjects` contrôlables par le joueur, et non seulement les
types.

#### `getState`

Cette méthode retournait à l'origine une version textuelle de l'état
du niveau pour but d'être utilisée tant dans la sauvegarde que
dans l'affichage. Cela violait la séparation des compétences puisque
le modèle participait à la construction de la vue, et rendait cette
vue plus compliquée puisqu'elle devait parser une string.

#### Ajout de méthodes privées utilitaires

Lors du développement, de nombreux morceaux de codes ont été 
factorisés dans leurs propres méthodes. 
Celles-ci sont `moveTile`, `removeTile`, `mutateAll` et `processRule`

### Énumérations

Des valeurs d'énumération ont été ajoutées car présentes dans les
5 premiers niveaux : `(TEXT_)LAVA` et `BEST`.

### GameObject

La notion d'héritage a finalement été rejetée. La classe dérivée Text
n'avait pas assez d'utilité que pour justifier son existence. Ainsi,
la récupération du type décrit par un objet TEXT se fait via une
fonction privée non-membre de la classe Level, le seul endroit où
cette information est requise.

Pouvoir spécifier la catégorie d'un objet via son constructeur étant 
trop dangereux, la catégorie de l'objet est déduite de son type,
via une map.

Une surcharge d'opérateur ont été ajoutés pour comparer un GameObject
à un autre.

## Bugs connus

* L'aspect BEST est défini mais n'est pas implémenté.

## Améliorations possibles

* L'application des règles dépend de l'ordre interne à la map les contenant,
ordre qui n'est pas garanti. Ce serait mieux de le rendre plus déterministe.

* L'utilisation d'une multimap étant beaucoup plus obscure que prévu,
il serait intéressant d'envisager de refactoriser le code pour utiliser
une map de vector à la place.

* Le chemin où trouver les niveaux est hardcodé dans la classe Level,
dans la constante START_OF_PATH. Il serait intéressant d'avoir cette
donnée dans un fichier de configuration, tel qu'un .env ou un 
config.properties comme vu en ATLG4.

* Le code pourrait être factorisé un peu plus.

* L'affichage de plusieurs éléments sur une même position est non déterministe.
Nous affichons à une certaine position le dernier élément apparaissant à celle-ci,
mais rien ne garantit que l'ordre dans lequel se trouveront les éléments
au sein d'une position est le même que leur ordre d'apparition. Ainsi, des objets 
ayant moins d'importance pour le joueur pourraient se retrouver cachés.
On pourrait coder en dur une priorité dans la vue... ou s'assurer que la vue
graphique ait des sprites transparents, ce qui réglerait le problème.

## Auteurs

* Ayoub Moufidi (58089)
* Zeki Ozkara (58143)
