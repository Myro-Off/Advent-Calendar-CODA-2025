# 🌍 Elf Tracking System

Une mission de **Data Engineering** et de **Visualisation** pour préparer la tournée 2025. Ce projet extrait les données de la base elfique, corrige les coordonnées géographiques et génère une carte interactive pour localiser les 3 enfants les plus sages du monde.

![Language](https://img.shields.io/badge/Language-Python_3.10+-blue.svg)
![Day](https://img.shields.io/badge/Day-8-red.svg)
![Tools](https://img.shields.io/badge/Tools-Folium_%7C_Pandas_%7C_SQLite-green.svg)

> 🎅 **Challenge :** Ce projet est la solution du **Jour 8** du calendrier de l'avent [Coda School Advent 2025](https://coda-school.github.io/advent-2025/).
> *"Identifier les 3 enfants les plus sages et visualiser leur position précise sur une carte."*

## 📋 Description

Les données des enfants sont dispersées dans une base de données relationnelle (`kids.db`). De plus, les elfes utilisent leur propre système de coordonnées (métrique) différent du GPS standard.

Ce script réalise le pipeline suivant :
1.  **Extraction (ETL) :** Une requête SQL complexe avec des `JOINs` pour relier le score de sagesse (`behavior`), l'enfant, sa ville et ses coordonnées.
2.  **Transformation :** Conversion vectorisée des coordonnées du **Plan Elfique (EPSG:3857)** vers le standard **GPS (EPSG:4326)**.
3.  **Visualisation :** Génération d'une carte interactive avec cadrage automatique et étiquettes stylisées.

## 🚀 Démo

### 1. Extraction des Données
Voici le Top 3 identifié pour la tournée 2025 :

| First Name | City          | Latitude  | Longitude   |
|:-----------|:--------------|:----------|:------------|
| **Astrid** | Paris         | 48.875872 | 2.370207    |
| **Isha**   | Beijing       | 39.911644 | 116.391617  |
| **Omar**   | San Francisco | 37.790593 | -122.412131 |

### 2. Visualisation Cartographique
Une carte interactive est générée avec les 3 localisations :

*![](carte.png)*
> Les marqueurs verts indiquent la position précise. Une étiquette persistante affiche le nom, la ville et le score de sagesse.


### Si vous souhaitez accéder à la carte interactive conçue avec **Jupyter Notebook** directement, [cliquez ici](https://nbviewer.org/github/Myro-Off/Advent-Calendar-CODA-2025/blob/main/Day-8/main.ipynb) (ne fonctionne pas toujours à cause d'un nombre top élevé de requêtes vers l'API Github)
