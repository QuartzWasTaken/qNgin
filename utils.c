#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cjson/cJSON.h>
#include "utils.h"

const tileTypeMapping tileTypeMappings[] =
{
    { TILE_AIR,    "TILE_AIR"    },
    { TILE_GROUND, "TILE_GROUND" },
    { TILE_ERROR,  "TILE_ERROR"  }
};

const char* tileTypeStrings[] = 
{
    "TILE_AIR",
    "TILE_GROUND",
    "TILE_ERROR"
};

const size_t tileTypeMappingCount = sizeof(tileTypeMappings) / sizeof(tileTypeMappings[0]);

char* read_file_to_string(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    // Aller à la fin pour déterminer la taille du fichier
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    // Allouer un buffer (+1 pour \0)
    char* buffer = malloc(length + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // Lire le fichier dans le buffer
    size_t read_size = fread(buffer, 1, length, file);
    buffer[read_size] = '\0'; // Terminer par \0

    fclose(file);
    return buffer;
}

tileType stringToTileType(const char* str)
{
    for (size_t i = 0; i < tileTypeMappingCount; ++i) {
        if (strcmp(tileTypeMappings[i].name, str) == 0) {
            return tileTypeMappings[i].type;
        }
    }
    return TILE_ERROR;
}

const char* tileTypeToString(tileType type)
{
    for (size_t i = 0; i < tileTypeMappingCount; ++i) {
        if (tileTypeMappings[i].type == type) {
            return tileTypeMappings[i].name;
        }
    }
    return "TILE_ERROR";
}


int jsonToGrid(grid g, const char* path)
{
    int status = 0;

    const cJSON* tile = NULL;
    const cJSON* tiles = NULL;
    const cJSON* index = NULL;
    const cJSON* type = NULL;
    const cJSON* x = NULL;
    const cJSON* y = NULL;
    
    cJSON* f = cJSON_Parse(read_file_to_string(path));
    if(f == NULL) // Si y a eu une erreur
    {
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL)
        {
            fprintf(stderr, "Erreur avant %s\n", error_ptr);
            goto end;
        }
    }

    tiles = cJSON_GetObjectItemCaseSensitive(f, "tiles");

    cJSON_ArrayForEach(tile, tiles) // Itérer sur toutes les tiles
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
        tileType tType = stringToTileType(type->valuestring);
        
        g[yPos][xPos] = tType;
        printf("\n\n%d\n\n", g[yPos][xPos]);
    }

    end:
        cJSON_Delete(f);
        return status;
}
