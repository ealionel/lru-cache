# LRU Cache

This repository is an example of implementation of LRU policy cache memory replacement in an operating system.

## Building

```
mkdir build
gcc -g -Wall main.c memory.c helper.c threads.c -o build/program -lpthread
```

## Configuration file

Configuration file must have the following format :

```
<nb_pages_in_main_memory> <size_of_page> <nb_pages_in_secondary_memory> <nb_child_threads> <amount_of_memory_access>
```

For example :

```
4 4096 256 10 100
```

## Usage

Program reads configuration via standard input. You can input your configuration file by doing the following :

```
./build/program < config
```

Or just via the console in stdin when running the program :

```
./build/program
4
4096
256
10
100
```

## Output example


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
