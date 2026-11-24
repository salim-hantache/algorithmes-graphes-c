# Projet 2 — Algorithmes de graphes en C

## Objectif
Étudier BFS, DFS et Dijkstra sur un graphe non orienté pondéré.

## Compilation et exécution
Avec GCC :
```bash
gcc -std=c11 -Wall -Wextra -pedantic graph_algorithms.c -o graph_algorithms
./graph_algorithms
```
Sous Windows, lancer `graph_algorithms.exe` après compilation.

## Choix techniques
Listes d'adjacence chaînées, file pour BFS, récursion pour DFS, sélection
linéaire du sommet de distance minimale pour Dijkstra (`O(V^2 + E)`).

## Limites
Maximum 100 sommets. Dijkstra exige des poids non négatifs. Le DFS récursif
peut être limité par la pile sur de très grands graphes. Le graphe d'exemple
est défini dans `main`.

## À savoir expliquer
BFS contre DFS, file et récursion, listes contre matrice d'adjacence,
invariant de Dijkstra, gestion mémoire et complexités.
