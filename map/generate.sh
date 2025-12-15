#!/bin/bash

# Générateur de maps aléatoires pour so_long
# Usage: ./generate_map.sh [width] [height] [num_collectibles]

# Paramètres par défaut
WIDTH=${1:-15}
HEIGHT=${2:-10}
NUM_COLLECTIBLES=${3:-5}
OUTPUT_FILE="./map_$(date +%s).ber"

# Validation des paramètres
if [ $WIDTH -lt 5 ] || [ $HEIGHT -lt 5 ]; then
    echo "Erreur: La map doit faire au minimum 5x5"
    exit 1
fi

if [ $NUM_COLLECTIBLES -lt 1 ]; then
    echo "Erreur: Il faut au moins 1 collectible"
    exit 1
fi

# Fonction pour générer la map
generate_map() {
    local w=$1
    local h=$2
    local collectibles=$3

    # Initialise la map avec des 0
    declare -a map
    for ((y=0; y<h; y++)); do
        map[$y]=""
        for ((x=0; x<w; x++)); do
            if [ $y -eq 0 ] || [ $y -eq $((h-1)) ] || [ $x -eq 0 ] || [ $x -eq $((w-1)) ]; then
                # Bordures = murs
                map[$y]="${map[$y]}1"
            else
                # Intérieur = sol ou mur aléatoire (20% de chance d'être un mur)
                if [ $((RANDOM % 100)) -lt 20 ]; then
                    map[$y]="${map[$y]}1"
                else
                    map[$y]="${map[$y]}0"
                fi
            fi
        done
    done

    # Place le joueur (P) à une position aléatoire valide
    while true; do
        px=$((RANDOM % (w-2) + 1))
        py=$((RANDOM % (h-2) + 1))
        char="${map[$py]:$px:1}"
        if [ "$char" = "0" ]; then
            map[$py]="${map[$py]:0:$px}P${map[$py]:$((px+1))}"
            break
        fi
    done

    # Place la sortie (E) à une position aléatoire valide
    while true; do
        ex=$((RANDOM % (w-2) + 1))
        ey=$((RANDOM % (h-2) + 1))
        char="${map[$ey]:$ex:1}"
        if [ "$char" = "0" ] && ! ([ $ex -eq $px ] && [ $ey -eq $py ]); then
            map[$ey]="${map[$ey]:0:$ex}E${map[$ey]:$((ex+1))}"
            break
        fi
    done

    # Place les collectibles (C) à des positions aléatoires valides
    placed=0
    max_attempts=1000
    attempts=0
    while [ $placed -lt $collectibles ] && [ $attempts -lt $max_attempts ]; do
        cx=$((RANDOM % (w-2) + 1))
        cy=$((RANDOM % (h-2) + 1))
        char="${map[$cy]:$cx:1}"
        if [ "$char" = "0" ]; then
            map[$cy]="${map[$cy]:0:$cx}C${map[$cy]:$((cx+1))}"
            placed=$((placed + 1))
        fi
        attempts=$((attempts + 1))
    done

    if [ $placed -lt $collectibles ]; then
        echo "Attention: Seulement $placed collectibles placés sur $collectibles demandés"
    fi

    # Écrit la map dans le fichier
    for ((y=0; y<h; y++)); do
        echo "${map[$y]}" >> "$OUTPUT_FILE"
    done
}

# Génère la map
echo "Génération d'une map ${WIDTH}x${HEIGHT} avec ${NUM_COLLECTIBLES} collectibles..."
generate_map $WIDTH $HEIGHT $NUM_COLLECTIBLES

echo "Map générée: $OUTPUT_FILE"
echo ""
echo "Contenu de la map:"
cat "$OUTPUT_FILE"
echo ""
echo "Stats:"
echo "- Taille: ${WIDTH}x${HEIGHT}"
echo "- Joueurs (P): $(grep -o P "$OUTPUT_FILE" | wc -l)"
echo "- Sorties (E): $(grep -o E "$OUTPUT_FILE" | wc -l)"
echo "- Collectibles (C): $(grep -o C "$OUTPUT_FILE" | wc -l)"
echo "- Murs (1): $(grep -o 1 "$OUTPUT_FILE" | wc -l)"
echo ""
echo "Pour tester: ./so_long $OUTPUT_FILE"
