# Gestion de la mémoire

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
``