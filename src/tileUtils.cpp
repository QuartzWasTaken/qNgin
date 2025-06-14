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

int writeStringToFile(std::string input, const std::string& filename)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        // Handle error if file couldn't be opened
        return 1;
    }

    outFile << input; // write the string content to the file

    // File is automatically closed when outFile goes out of scope
    return 0;
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

    end:
        cJSON_Delete(f);
        print2DVector(t.getListe());
        return status;
}

std::string gridToJson(Tilemap t)
{
    std::string output;
    const std::vector<std::vector<Tile>> tiles = t.getListe();
    int type;
    cJSON* container = cJSON_CreateObject();
    cJSON* tilemap = cJSON_CreateArray();

    if(tilemap == NULL)
    {
        std::cout << "Erreur dans la création de l'objet tilemap" << std::endl;
        goto end;
    }

    for (const auto& row : t.getListe())
    {
        cJSON* jsonRow = cJSON_CreateArray();

        for (Tile val : row)
        {
            cJSON_AddItemToArray(jsonRow, cJSON_CreateNumber(val.getType()));
        }

        cJSON_AddItemToArray(tilemap, jsonRow);
    }

    cJSON_AddItemToObject(container, "tilemap", tilemap);
    output = cJSON_Print(container);

    end:
    cJSON_Delete(tilemap);
    return output;

}