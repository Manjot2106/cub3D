# cub3D

*Projet réalisé dans le cadre du cursus 42 par msingh et akaddo.*

Un moteur 3D en vue à la première personne, dans l'esprit de *Wolfenstein 3D*, écrit en C avec la **MiniLibX**. La scène est calculée par **raycasting** à partir d'une carte 2D décrite dans un fichier `.cub`.

## Compilation et lancement

Dépendances (Linux) : `make`, `cc`, `libx11-dev`, `libxext-dev`.

```bash
make                     # cub3D (partie obligatoire)
make bonus               # cub3D_bonus
./cub3D maps/good/subject_map.cub
./cub3D_bonus maps/good/door_bonus.cub
```

| Touche | Action |
|---|---|
| `W` `A` `S` `D` | avancer, aller à gauche, reculer, aller à droite |
| `←` `→` | tourner la caméra |
| Souris (bonus) | tourner la caméra |
| `E` (bonus) | ouvrir ou fermer une porte |
| `Échap` ou croix | quitter |

## Format du fichier `.cub`

```text
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
10N001
100001
111111
```

- `NO`, `SO`, `WE`, `EA` : textures `.xpm` des murs selon leur orientation.
- `F` et `C` : couleurs RVB du sol et du plafond (chaque composante entre 0 et 255).
- Carte : `1` mur, `0` sol, `N`/`S`/`E`/`W` position et orientation de départ du joueur (un seul joueur). La carte doit être fermée par des murs. Elle est toujours le dernier élément du fichier.
- Bonus : `D` porte, `B` tonneau animé (sprite).

Toute erreur affiche `Error` suivi d'un message précis : texture absente, en double, introuvable ou pas en `.xpm`, couleur invalide, carte ouverte, joueur absent ou multiple, caractère interdit, carte placée avant les éléments, etc. Le dossier `maps/bad/` contient un fichier par cas d'erreur.

## Fonctionnement

### Parsing (`src/parsing/`)

1. `read_file` charge le fichier en entier.
2. `parse_elements` lit les 6 identifiants dans n'importe quel ordre et refuse les doublons ou les manques (`parse_textures`, `parse_color`).
3. `extract_map` isole la carte, `parse_map` vérifie les caractères et trouve le joueur.
4. `validate_closed_map` vérifie que chaque case accessible est entourée : une case de sol ou de joueur ne doit jamais toucher le bord ni un espace vide.

### Raycasting (`src/render/`)

Pour chaque colonne de pixels de l'écran :

1. On calcule l'angle du rayon : l'angle du joueur, moins la moitié du champ de vision (`FOV`), plus un pas proportionnel au numéro de colonne.
2. **DDA** (*Digital Differential Analysis*) : le rayon avance case par case sur la grille, en choisissant à chaque pas le prochain bord vertical ou horizontal le plus proche, jusqu'à toucher un mur (`cast_ray.c`).
3. La distance trouvée est multipliée par `cos(angle_rayon - angle_joueur)` (`get_corrected_dist`) pour supprimer l'effet « fish-eye ». La hauteur de la colonne de mur est inversement proportionnelle à cette distance corrigée.
4. Le côté touché (nord, sud, est ou ouest) choisit la texture. La position exacte de l'impact donne la colonne de texture, et l'on échantillonne verticalement (`wall.c`).
5. Le plafond et le sol sont remplis avec leurs couleurs (`floor.c`). Toute l'image est dessinée dans un buffer puis affichée en une seule fois (`image.c`, `render_game.c`).

### Déplacements (`src/events/`)

Les touches activent des drapeaux (appui / relâchement). À chaque image, `player_update` applique les déplacements et rotations : les rotations modifient l'angle du joueur, les déplacements sont calculés avec `cos` et `sin` de cet angle. La **collision** est vérifiée séparément sur chaque axe (`can_move_to`), ce qui permet de glisser le long d'un mur au lieu de s'y bloquer.

### Bonus (`src_bonus/`)

- **Minimap** en haut à gauche, avec la position et la direction du joueur.
- **Portes** : le rayon les traite comme des murs tant qu'elles sont fermées. `E` ouvre ou ferme la porte en face du joueur, avec une animation.
- **Sprites** : tonneaux animés, triés du plus loin au plus proche et masqués par les murs grâce à un **z-buffer** (la distance du mur pour chaque colonne).
- **Rotation à la souris**, le curseur étant recentré à chaque image.

## Tests

Toutes les cartes de `maps/bad/` sont rejetées avec le bon message, et valgrind ne signale ni erreur ni fuite. Pour tester les deux cas de permissions, il faut d'abord retirer les droits de lecture, car git ne conserve pas le mode `000` :

```bash
chmod 000 maps/bad/forbidden.cub textures/test/forbidden.xpm
./cub3D maps/bad/forbidden.cub
./cub3D maps/bad/textures_forbidden.cub
```

## Ressources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [From Flat to Fantastic: How cub3D's Ray-Casting Engine Transforms 2D into 3D](https://medium.com/@elmehdielgarouaz/from-flat-to-fantastic-how-cub3ds-ray-casting-engine-transforms-2d-into-3d-647ff2f7fd4f)
- [Ray Casting in C](https://ismailassil.medium.com/ray-casting-c-8bfae2c2fc13)

### Usage de l'IA

L'IA a été utilisée uniquement pour comprendre le concept du raycasting, s'entraîner sur des exemples externes et aider au débogage.
