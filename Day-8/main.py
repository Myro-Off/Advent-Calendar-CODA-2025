import sqlite3
import pandas as pd
import folium
from pyproj import Transformer

# --- 1. Extraction  ---
query = """
SELECT
    c.first_name, c.last_name, b.nice_score,
    ci.name AS city,
    ep.x_m AS elf_x, ep.y_m AS elf_y
FROM behavior b
JOIN children c ON b.child_id = c.id
JOIN households h ON c.household_id = h.id
JOIN cities ci ON h.city_id = ci.id
JOIN elf_plan ep ON c.id = ep.child_id
WHERE b.year = 2025
ORDER BY b.nice_score DESC
LIMIT 3;
"""

with sqlite3.connect('kids.db') as conn:
    df = pd.read_sql_query(query, conn)

# --- 2. Transformation Vectorisée (Plan Elfique -> GPS) ---
transformer = Transformer.from_crs("EPSG:3857", "EPSG:4326")

df['latitude'], df['longitude'] = transformer.transform(df['elf_x'].values, df['elf_y'].values)

print("------------- 🏆 TOP 3 KIDS 2025 -------------")
display(df[['first_name', 'city', 'latitude', 'longitude']])

# --- 3. Génération de la Carte ---
m = folium.Map(tiles="CartoDB positron")

# Préparation des limites pour le zoom auto
locations = df[['latitude', 'longitude']].values.tolist()

# --- HTML de l'étiquette ---
for _, row in df.iterrows():
    label_html = f"""
    <div style="
    font-family: Arial, sans-serif;
    text-align: center; width: 150px;
    background: rgba(255,255,255,0.95); border-radius: 8px; padding: 8px;
    box-shadow: 0 2px 5px rgba(0,0,0,0.2); border: 1px solid #ddd;
    ">
        <strong style="color: #2c3e50; font-size: 14px;">{row['first_name']} {row['last_name']}</strong><br>
        <div style="color: #7f8c8d; font-size: 11px; margin: 4px 0;">📍 {row['city'].upper()}</div>
        <div style="color: #27ae60; font-weight: bold; font-size: 12px;">★ Score: {row['nice_score']}</div>
    </div>
    """

    folium.Marker(
        location=[row['latitude'], row['longitude']],
        icon=folium.Icon(color="green", icon="star", prefix='fa'),
        tooltip=folium.Tooltip(label_html,
        permanent=True, direction='top',
        offset=[0, -40],
        sticky=False)
    ).add_to(m)

# Cadrage automatique
if len(locations) > 0:
    m.fit_bounds(locations, padding=[100, 100])

m
