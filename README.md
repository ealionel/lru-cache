# Gestion de la mémoire

Exemple d'implémentation de l'algorithme LRU permettant de de remplacer des lignes de cache.

## Compilation

Le programme est compilé de la manière suivante :
```
mkdir build
gcc -g -Wall main.c memory.c helper.c threads.c -o build/program -lpthread
```

## Fichier de configuration

Le fichier de configuration doit avoir les champs suivants :

```
<nb_pages_memoire_principale> <taille_page> <nb_pages_memoire_secondaire> <nb_threads_fils> <nb_accès>
```

Donc par exemple

```
4 4096 256 10 100
```

## Utilisation


La configuration fait simplement des scanf sur l'entrée standard, c'est pourquoi, après avoir compilé le programme, on peut lancer le programme depuis la racine avec le fichier de configuration `config` de la manière suivante :

```
./build/program < config
```

Ou alors en rentrant manuellement la condfiguration dans le bon ordre dans l'entrée standard :

```
./build/program
4
4096
256
10
100
```

## Exemple

Un exemple de sortie du programme :

```
---------- Config -----------
frames:             10
page_size:          4096
nb_page_secondary:  256
nb_threads:         10
nb_access:          100
-----------------------------
Thread[1] :     5 / 100 hits
Thread[2] :     2 / 100 hits
Thread[3] :     2 / 100 hits
Thread[4] :     1 / 100 hits
Thread[5] :     3 / 100 hits
Thread[6] :     5 / 100 hits
Thread[7] :     2 / 100 hits
Thread[8] :     5 / 100 hits
Thread[9] :     5 / 100 hits
Thread[10]:     1 / 100 hits
-----------------------------
Total :     31 / 1000 hits
Hit Rate :  3.10%
```
