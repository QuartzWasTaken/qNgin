#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cjson/cJSON.h>

#include "raylib.h"

#include "tileUtils.h"
#include "Tile.h"
#include "Tilemap.h"
#include "TextureManager.h"


t_tileTypeMap tileTypeMap = {
    {"TILE_EMPTY", 0},
    {"TILE_GROUND", 1},
    {"TILE_ERROR", -1}
};

t_textureMap textureMap;

void printVector(const std::vector<Tile>& vec) // allègrement généré
{
    std::cout << "[ ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << "]\n";
}

void print2DVector(const std::vector<std::vector<Tile>>& matrix)
{
    for (const auto& row : matrix) {
        printVector(row);
    }
}

void bindTextures(Tilemap& t, const TextureManager& texManager) // ahahahhahhazhziehfizuherizhfiehfi j'adore les pointeurs
{
    auto& listeTiles = t.getListe();  // acces non const (important)

    for (size_t y = 0; y < listeTiles.size(); y++)
    {
        for (size_t x = 0; x < listeTiles[y].size(); x++)
        {
            int tileType = listeTiles[y][x].getType();

            listeTiles[y][x].setTexture(texManager.getTexture(tileType));
        }
    }
}

std::string readFileToString(const std::string& filename)
{
    std::ifstream inFile(filename);
    std::ostringstream buffer;
    buffer << inFile.rdbuf(); // normalement y a un RAII (Resource Allocation Is Initialisation : implique un destructeur)
    return buffer.str();
}


// Tilemap contient des tiles contenues dans une variable grille
// TIle : texture (pour le moment), puis collision

int jsonToGrid(Tilemap& t, const char* path) // écrit en C avant de passer au C++
{
    int status = 0;

    const cJSON* tilemap = NULL;

    std::string strPath(path);
    std::cout << "Chemin : " << strPath << std::endl;
    cJSON* f = cJSON_Parse(readFileToString(strPath).c_str());
    int height = 0;
    if(f == NULL) // si y a eu une erreur
    {
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL)
        {
            fprintf(stderr, "Erreur avant %s\n", error_ptr);
            goto end;
        }
    }

    tilemap = cJSON_GetObjectItemCaseSensitive(f, "tilemap");

    if(!cJSON_IsArray(tilemap))
    {
        fprintf(stderr, "Erreur : tilemap n'est pas un tableau\n");
        goto end;
    }

    height = cJSON_GetArraySize(tilemap);

    if(height <= 0)
    {
        fprintf(stderr, "Erreur : tilemap vide\n");
        goto end; // goto :glad:
    }

    for(int y = 0; y < height; y++) // initialiser la grille
    {
        cJSON* ligne = cJSON_GetArrayItem(tilemap, y);
        
        if(!cJSON_IsArray(ligne))
        {
            fprintf(stderr, "Erreur : la ligne n'est pas un tableau");
        }

        int colonnes = cJSON_GetArraySize(ligne);
        for(int x = 0; x < colonnes; x++)
        {
            cJSON* tile = cJSON_GetArrayItem(ligne, x);

            if(cJSON_IsNumber(tile))
            {
                printf("Tile à %d;%d : %d\n", x, y, tile->valueint);
                t.getListe()[y][x].setType(tile->valueint);
            }
            else
            {
                printf("Erreur avec la tile %d;%d : Mise du type à -1\n", x, y);
                t.getListe()[y][x].setType(-1);
            }
        }
    }
    
    //cJSON_ArrayForEach(tile, tiles) // itérer sur toutes les tiles
    //{

    //     cJSON* tilemap = 


    //     cJSON* type = cJSON_GetObjectItemCaseSensitive(tile, "type");
    //     cJSON* x = cJSON_GetObjectItemCaseSensitive(tile, "x");
    //     cJSON* y = cJSON_GetObjectItemCaseSensitive(tile, "y");

    //     if(!cJSON_IsNumber(x) || !cJSON_IsNumber(y))
    //     {
    //         status = 0;
    //         goto end; // goto :glad:
    //     }

    //     int xPos = x->valueint;
    //     int yPos = y->valueint;
    //     int tType = -1;
    //     std::string sType = type->valuestring; // convertir du type cjson vers int
    //     if(tileTypeMap.find(sType) != tileTypeMap.end()) // trouver l'entier correspondant dans la textureMap
    //     {
    //         tType = tileTypeMap.find(sType)->second;
    //     }
        
    //     t.getListe()[yPos][xPos].setType(tType); // assigner le bon type à la case correspondante
    //     printf("xPos : %d\n", xPos);
    //     printf("yPos : %d\n", yPos);
    //     printf("tType : %d\n", tType);
    // }

    end:
        cJSON_Delete(f);
        print2DVector(t.getListe());
        return status;
}