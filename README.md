# 🍪 Elf Calorie Battle

Un outil performant écrit en **C** pour analyser les provisions caloriques d'une expédition d'Elfes. Ce projet parse, agrège et classe les données pour déterminer quels Elfes transportent le plus de calories.

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Day](https://img.shields.io/badge/Day-4-red.svg)

> 🎅 **Challenge :** Ce projet est la solution du **Jour 4** du calendrier de l'avent [Coda School Advent 2025](https://coda-school.github.io/advent-2025/).

## 📋 Description

Ce programme lit un fichier de données brut contenant des noms d'Elfes et des listes d'items caloriques. Il :
1.  **Parse** le fichier ligne par ligne de manière sécurisée.
2.  **Agrège** les calories pour chaque Elfe.
3.  **Trie** les résultats par ordre décroissant (Tri Rapide).
4.  **Affiche** le grand vainqueur ainsi que le total du Top 3.

## 🚀 Démo

Voici à quoi ressemble la sortie du programme dans le terminal :

```text
--- COOKIE BATTLE RESULTS ---

🍪 WINNER: Legolas with 72000 calories!
🥈 RUNNERS UP: Thranduil (68000) and Elrond (64000)

🎁 TOTAL POWER (Top 3): 204000 calories
```

## 🛠️ Installation & Utilisation

Le projet inclut un `Makefile` pour simplifier la compilation.

### Prérequis
* Un compilateur C (GCC recommandé)
* Make

### Commandes

1.  **Compiler le projet :**
    ```bash
    make
    ```

2.  **Lancer le programme :**
    ```bash
    make run
    ```

3.  **Nettoyer les fichiers de build :**
    ```bash
    make clean
    ```

## 📄 Format des Données

Le programme attend un fichier nommé `data` à la racine du projet.
Le format doit respecter la structure suivante :

* **Nom** (Ligne de texte)
* **Calories** (Une ou plusieurs lignes de chiffres)
* **Ligne vide** (Séparateur entre deux Elfes)

**Exemple de fichier `data` :**
```text
Legolas
1000
2000
3000

Thranduil
5000
6000

Elrond
10000