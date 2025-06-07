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
#include <iostream>


t_tileTypeMap tileTypeMap = {
    {"TILE_EMPTY", 0},
    {"TILE_GROUND", 1},
    {"TILE_ERROR", -1}
};

t_textureMap textureMap;

void printVector(const std::vector<Tile>& vec)
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
void buildTextureMap(t_textureMap* texMap, t_tileTypeMap typeMap) // TEXMAP : INT TEX   ;    TYPEMAP : STRING INT
{
    for(auto& pair : typeMap)
    {
        std::string texName = pair.first; // on recup le nom de la texture (en full maj vu que ça vient du json)

        std::string texNameLower = texName;

        for (char& c : texNameLower) // toupper mais pour un string c'est débile
        {
            c = std::tolower(static_cast<unsigned char>(c));
        }

        std::string filePath = "assets/" + texNameLower + ".png"; // ça marchera peutetre
        std::cout << "filePath : " << filePath << std::endl;
        (*texMap)[pair.second] = LoadTexture(filePath.c_str());
        if((*texMap)[pair.second].id != 0)
        {
            std::cout << "Texture actually loaded successfully" << std::endl;
            std::cout << (*texMap)[pair.second].id << std::endl;
        }
    }
}

void bindTextures(Tilemap& t, const t_textureMap& texMap)
{
    auto& listeTiles = t.getListe();  // non-const access

    for (size_t y = 0; y < listeTiles.size(); y++)
    {
        for (size_t x = 0; x < listeTiles[y].size(); x++)
        {
            int tileType = listeTiles[y][x].getType();

            auto it = texMap.find(tileType);
            std::cout << "Texture à bind :  ";
            std::cout << tileType << std::endl;
            if (it != texMap.end())
            {
                listeTiles[y][x].setTexture(&it->second);
            }
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

int jsonToGrid(Tilemap& t, const char* path)
{
    int status = 0;

    const cJSON* tile = NULL;
    const cJSON* tiles = NULL;

    std::string strPath(path);
    std::cout << "chemin : " << strPath << std::endl;
    cJSON* f = cJSON_Parse(readFileToString(strPath).c_str()); // un beau bazar
    if(f == NULL) // si y a eu une erreur (probable vu la tete de la ligne du dessus)
    {
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL)
        {
            fprintf(stderr, "Erreur avant %s\n", error_ptr);
            goto end;
        }
    }

    tiles = cJSON_GetObjectItemCaseSensitive(f, "tiles");

    cJSON_ArrayForEach(tile, tiles) // itérer sur toutes les tiles
    {
        cJSON* type = cJSON_GetObjectItemCaseSensitive(tile, "type");
        cJSON* x = cJSON_GetObjectItemCaseSensitive(tile, "x");
        cJSON* y = cJSON_GetObjectItemCaseSensitive(tile, "y");

        if(!cJSON_IsNumber(x) || !cJSON_IsNumber(y))
        {
            status = 0;
            goto end;
        }

        int xPos = x->valueint;
        int yPos = y->valueint;
        int tType = -1;
        std::string sType = type->valuestring; // convertir du type cjson vers int
        if(tileTypeMap.find(sType) != tileTypeMap.end()) // trouver l'entier correspondant dans la textureMap
        {
            tType = tileTypeMap.find(sType)->second;
        }
        
        t.getListe()[yPos][xPos].setType(tType); // assigner le bon type à la case correspondante
        printf("xPos : %d\n", xPos);
        printf("yPos : %d\n", yPos);
        printf("tType : %d\n", tType);
    }

    end:
        cJSON_Delete(f);
        print2DVector(t.getListe());
        return status;
}