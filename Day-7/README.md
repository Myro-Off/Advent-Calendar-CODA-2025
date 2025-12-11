# 🎁 Gift Registry Refactoring

Une mission de **Clean Code** pour aider les elfes à moderniser leur registre de cadeaux. Ce projet consiste à auditer, nettoyer et refactoriser un code legacy (PHP) en suivant les standards modernes et les recommandations de linters professionnels.

![Language](https://img.shields.io/badge/Language-PHP_8.2-blue.svg)
![Day](https://img.shields.io/badge/Day-7-red.svg)
![Tool](https://img.shields.io/badge/Linter-SonarQube_for_IDE-orange.svg)
![Quality](https://img.shields.io/badge/Quality-Clean_Code-green.svg)

> 🎅 **Challenge :** Ce projet est la solution du **Jour 7** du calendrier de l'avent [Coda School Advent 2025](https://coda-school.github.io/advent-2025/).
> *"Il ne suffit pas qu'un code marche — il doit aussi être propre, cohérent et maintenable."*

## 📋 Description

Le code original des elfes (`Gift-trash.php`) fonctionnait (à peu près), mais était rempli de bugs latents, de code mort et de violations des standards PSR.
Ce projet a pour but de :
1.  **Auditer** le code existant avec SonarLint.
2.  **Corriger** les bugs critiques (boucles infinies, variables indéfinies).
3.  **Moderniser** la syntaxe (Typage strict, PHP 8+ features).
4.  **Standardiser** le style (PSR-12).

J'ai donc effectué les correctifs sur `Gift-clean.php`, en suivant les indications du Linter ci-dessous :
## 🚨 Rapport d'Audit (Linter)

Voici un extrait des **20 problèmes** identifiés par le linter avant le refactoring, classés par sévérité :

| Sévérité | Règle (ID) | Problème détecté | Action corrective |
|:--------:| :--- | :--- | :--- |
|    🔴    | `php:S6600` | Remove the parentheses from this "print" call. | Parenthèses supprimées. |
|    🔴    | `php:S5797` | Condition always constant (`false`). | Bloc supprimé (Code mort). |
|    🔴    | `php:S1145` | Remove this "if" statement. | Bloc supprimé (lié au code mort ci-dessus). |
|    🔴    | `php:S1763` | Delete this unreachable code. | Suppression du `echo` après le `return`. |
|    🟠    | `php:S101` | Rename class "giftRegistry" to match regex. | Renommé en **`GiftRegistry`** (PascalCase). |
|    🟠    | `php:S116` | Rename field "$LastUpdated" to match regex. | Renommé en **`$lastUpdated`** (camelCase). |
|    🟠    | `php:S1784` | Explicitly mention the visibility (x5). | Ajout de **`public`** / **`private`** sur toutes les méthodes. |
|    🟠    | `php:S1481` | Remove unused local variables (`$counter`, `$temp`). | Variables supprimées. |
|    🟠    | `php:S1764` | Identical sub-expressions (`$child == $child`). | Logique corrigée et simplifiée. |
|    🟠    | `php:S1226` | Introduce new variable instead of reusing param. | Variable locale renommée dans la boucle. |
|    🟠    | `php:S1125` | Remove literal "true" boolean value. | Simplifié `if ($found == true)` en `if ($found)`. |
|    🟠    | `php:S1781` | Write "TRUE" constant in lower case. | Remplacé par **`true`**. |
|    🟠    | `php:S1066` | Merge this if statement with enclosing one. | Conditions fusionnées. |
|    🟠    | `php:S1793` | Replace "else if" by "elseif". | Bloc supprimé (car code mort), mais noté. |
|    🟠    | `php:S113`  | Add a new line at the end of this file. | Saut de ligne ajouté à la fin. |

## 🚀 Pistes d'Amélioration (Going Further)

Au-delà des correctifs du linter, voici comment nous aurions pu moderniser l'architecture :

* **DTO vs Tableaux :** Remplacer les tableaux associatifs fragiles par une classe `Gift` dédiée (Data Transfer Object).
* **Typage Fort :** Activer `declare(strict_types=1)` et typer toutes les propriétés/arguments (PHP 8+).
* **Exceptions :** Remplacer les `print` par de vraies `Exception` pour bloquer les données invalides.
* **Anti-Magic Numbers :** Remplacer les chiffres bruts (7, 42...) par des constantes explicites (`const SCORE_...`).
* **Encapsulation :** Passer la propriété `$gifts` en `private` pour empêcher sa modification directe depuis l'extérieur.